<?php
/**
 * @file
 * Feed import class for parsing and processing content.
 */
class FeedImport {
  /**
   * A report about import process
   * -rescheduled
   * -updated
   * -new
   * -total
   * -time
   * -download
   * -errors
   */
  public static $report = array();

  /**
   * Feed import load feeds settings
   *
   * @param bool $enabled
   *   Load only enabled feeds
   * @param mixed $id
   *   Load feed by id or machine name
   *
   * @return array
   *   Feeds info
   */
  public static function loadFeeds($enabled = FALSE, $id = NULL) {
    static $feeds = NULL;
    static $enabled_feeds = NULL;
    if ($id == NULL) {
      if ($feeds != NULL) {
        return $enabled ? $enabled_feeds : $feeds;
      }
      $feeds = db_select('feed_import_settings', 'f')
                  ->fields('f', array('name', 'machine_name', 'url', 'time', 'entity_info', 'xpath', 'id', 'enabled'))
                  ->orderBy('enabled', 'DESC')
                  ->execute()
                  ->fetchAllAssoc('machine_name');
      foreach ($feeds as $name => &$feed) {
        $feed = (array) $feed;
        $feed['entity_info'] = unserialize($feed['entity_info']);
        $feed['xpath'] = unserialize($feed['xpath']);
        if ($feed['enabled']) {
          $enabled_feeds[$name] = &$feed;
        }
      }
      return $enabled ? $enabled_feeds : $feeds;
    }
    else {
      $feed = db_select('feed_import_settings', 'f')
                ->fields('f', array('name', 'machine_name', 'url', 'time', 'entity_info', 'xpath', 'id', 'enabled'))
                ->condition(((int) $id) ? 'id' : 'machine_name', $id, '=')
                ->range(0, 1)
                ->execute()
                ->fetchAll();
      if ($feed) {
        $feed = (array) reset($feed);
        $feed['entity_info'] = unserialize($feed['entity_info']);
        $feed['xpath'] = unserialize($feed['xpath']);
        return $feed;
      }
      else {
        return NULL;
      }
    }
  }

  /**
   * Save/update a feed
   *
   * @param array $feed
   *   Feed info array
   * @param bool $update
   *   Update feed if true, save if false
   */
  public static function saveFeed($feed, $update = FALSE) {
    if ($update) {
        db_update('feed_import_settings')
          ->fields(array(
            'enabled' => $feed['enabled'],
            'name' => $feed['name'],
            'machine_name' => $feed['machine_name'],
            'url' => $feed['url'],
            'time' => $feed['time'],
            'entity_info' => serialize($feed['entity_info']),
            'xpath' => serialize($feed['xpath']),
          ))
          ->condition('id', $feed['id'], '=')
          ->execute();
    }
    else {
      db_insert('feed_import_settings')
        ->fields(array(
          'enabled' => $feed['enabled'],
          'name' => $feed['name'],
          'machine_name' => $feed['machine_name'],
          'url' => $feed['url'],
          'time' => $feed['time'],
          'entity_info' => serialize($feed['entity_info']),
          'xpath' => serialize($feed['xpath']),
        ))
        ->execute();
    }
  }

  /**
   * Gets info about entities and fields
   *
   * @param string $entity
   *   Entity name
   *
   * @return array
   *   Info about entities
   */
  public static function getEntityInfo($entity = NULL) {
    static $fields = NULL;
    if (empty($fields)) {
      $info = array();
      $fields = _field_info_collate_fields(FALSE);
      if (isset($fields['fields'])) {
        $fields = $fields['fields'];
      }
      foreach ($fields as &$field) {
        $info[$field['field_name']] = array(
          'name' => $field['field_name'],
          'column' => key($field['columns']),
          'bundles' => array_keys($field['bundles']),
        );
        $field = NULL;
      }
      $fields = entity_get_info();
      foreach ($fields as $key => &$field) {
        if (empty($field['schema_fields_sql']['base table']) || !is_array($field['schema_fields_sql']['base table']) || empty($field['entity keys']['id'])) {
          unset($fields[$key]);
          continue;
        }
        $field = array(
          'name' => $key,
          'column' => $field['entity keys']['id'],
          'columns' => $field['schema_fields_sql']['base table'],
        );
        $field['columns'] = array_combine($field['columns'], array_fill(0, count($field['columns']), NULL));
        foreach ($info as &$f) {
          if (in_array($key, $f['bundles'])) {
            $field['columns'][$f['name']] = $f['column'];
          }
        }
      }
      unset($info);
    }
    if (!$entity) {
      return $fields;
    }
    else {
      return isset($fields[$entity]) ? $fields[$entity] : NULL;
    }
  }

  /**
   * Returns all available functions for processing a feed.
   */
  public static function processFunctions() {
    static $functions = NULL;
    if ($functions != NULL) {
      return $functions;
    }
    $functions = module_invoke_all('feed_import_process_info');
    // Well, check if functions really exists.
    foreach ($functions as $alias => &$func) {
      if (is_array($func['function'])) {
        if (!method_exists($func['function'][0], $func['function'][1])) {
          unset($functions[$alias]);
        }
      }
      else {
        if (!function_exists($func['function'])) {
          unset($functions[$alias]);
        }
      }
    }
    return $functions;
  }

  /**
   * Error handler callback
   * This is setted with set_error_handling()
   */
  public static function errorHandler($errno, $errmsg, $file, $line) {
    // How many errors to display.
    $errors_left = &drupal_static(__CLASS__ . '::' . __FUNCTION__, 100);
    // Handle silenced errors with @.
    if (error_reporting() == 0) {
      return FALSE;
    }
    // Add error to reports.
    if ($errors_left > 0) {
      self::$report['errors'][] = array(
        'error' => $errmsg,
        'error number' => $errno,
        'line' => $line,
        'file' => $file,
      );
      $errors_left--;
    }
    // Throw an exception to be caught by a try-catch statement.
    throw new Exception('Uncaught Feed Import Exception', $errno);
  }

  /**
   * This function is choosing process function and executes it
   *
   * @param array $feed
   *   Feed info array
   */
  public static function processFeed(array $feed) {
    // Reset report.
    self::$report = array(
      'rescheduled' => 0,
      'updated' => 0,
      'new' => 0,
      'total' => 0,
      'start' => time(),
      'time' => 0,
      'parse' => 0,
      'errors' => array(),
    );

    // Check if entity save/load functions exists.
    if (self::checkFunctions($feed['entity_info']['#entity'])) {
      // Alter feed info before process.
      drupal_alter('feed_import_feed_info', $feed);
      // Set language as first element.
      if (isset($feed['xpath']['#items']['language'])) {
        $feed['xpath']['#items'] = array_merge(array('language' => NULL), $feed['xpath']['#items']);
      }
      // Set error handler.
      set_error_handler(array(__CLASS__, 'errorHandler'));

      $func = $feed['xpath']['#process_function'];
      $functions = self::processFunctions();
      if (!$func || !isset($functions[$func])) {
        // Get first function if there's no specified function.
        $func = self::processFunctions();
        $func = reset($func);
      }
      else {
        $func = $functions[$func];
      }
      $func = $func['function'];
      unset($functions);

      // Get property temp name to store hash value.
      self::$tempHash = variable_get('feed_import_hash_property', self::$tempHash);
      // Reset generated hashes
      self::$generatedHashes = array();

      // Give import time (for large imports).
      // Well, if safe mode is on this cannot be done so it may break import.
      if (!ini_get('safe_mode')) {
        set_time_limit(0);
      }
      // Call process function to get processed items.
      $items = call_user_func($func, $feed);
      // Parse report.
      self::$report['parse'] = time();
      // Save items.
      if (!empty($items)) {
        self::saveEntities($feed, $items);
      }
      // Restore error handler.
      restore_error_handler();
    }
    else {
      // Report that vital functions are missing.
      self::$report['errors'][] = array(
        'error' => t('Missing @entity_save() or @entity_load() function!', array('@entity' => $feed['entity_info']['#entity'])),
        'error number' => '',
        'line' => '',
        'file' => '',
      );
      // This will produce 0 seconds for parse.
      self::$report['parse'] = self::$report['start'];
    }
    // Set total time report.
    self::$report['time'] = time() - self::$report['start'];
    self::$report['parse'] -= self::$report['start'];
  }

  /**
   * Deletes items by entity id
   *
   * @param array $eids
   *   Entity ids keyed by entity name
   */
  public static function deleteItemsbyEntityId(array $eids) {
    if (empty($eids)) {
      return;
    }
    $chunk = variable_get('feed_import_update_ids_chunk', 1000);
    $q_delete = db_delete('feed_import_hashes');
    $conditions = &$q_delete->conditions();
    foreach ($eids as $entity => &$ids) {
      $q_delete->condition('entity', $entity, '=');
      $ids = array_chunk($ids, $chunk);
      foreach ($ids as &$id) {
        $q_delete->condition('entity_id', $id, 'IN')->execute();
        // Remove last IN condition.
        array_pop($conditions);
        $id = NULL;
      }
      $ids = NULL;
      // Remove entity condition.
      array_pop($conditions);
    }
  }

  /**
   * Delete entity by type and ids
   *
   * @param string $type
   *   Entity type (node, user, ...)
   * @param array $ids
   *   Array of entity ids
   *
   * @return array
   *   Array of deleted ids
   */
  public static function entityDelete($type, $ids) {
    $func = $type . '_delete_multiple';
    if (function_exists($func)) {
      try {
        call_user_func($func, $ids);
      }
      catch (Exception $e) {
        return array();
      }
      return $ids;
    }
    else {
      $func = $type . '_delete';
      if (function_exists($func)) {
        foreach ($ids as $k => &$id) {
          try {
            call_user_func($func, $id);
          }
          catch (Exception $e) {
            unset($ids[$k]);
          }
        }
        return $ids;
      }
    }
    unset($type, $ids);
    return array();
  }

  /**
   * Get expired items
   *
   * @param int $limit
   *   Limit the number of returned items
   *
   * @return array
   *   Array keyed with entity names and value entity_ids
   */
  public static function getExpiredItems($limit = NULL) {
    $results = db_select('feed_import_hashes', 'f')
                ->fields('f', array('entity', 'entity_id'))
                ->condition('expire', array(1, REQUEST_TIME), 'BETWEEN');

    if ($limit !== NULL) {
      $results->range(0, $limit);
    }
    $results = $results->execute()->fetchAll();

    if (empty($results)) {
      return $results;
    }
    $res = array();
    foreach ($results as &$result) {
      $res[$result->entity][] = $result->entity_id;
      $result = NULL;
    }
    unset($results);
    return $res;
  }

  /**
   * Get value with xpath
   *
   * @param SimpleXMLElement &$item
   *   Simplexmlobject to apply xpath on
   * @param string $xpath
   *   Xpath to value
   *
   * @return mixed
   *   A string or array of strings as a result of xpath function
   */
  public static function getXpathValue(&$item, $xpath) {
    // Handle invalid xpaths.
    try {
      $xpath = $item->xpath($xpath);
    }
    catch (Exception $e) {
      return NULL;
    }
    if (count($xpath) == 1) {
      $xpath = (array) reset($xpath);
      $count = count($xpath);
      if (isset($xpath['@attributes']) && $count > 1) {
        unset($xpath['@attributes']);
        $count--;
      }
      // Convert to array.
      $xpath = self::SimpleXmlToArray($xpath);
      if ($count == 1) {
        $xpath = reset($xpath);
      }
    }
    else {
      // Get multi-values.
      foreach ($xpath as $key => &$x) {
        // Convert to array.
        $x = self::SimpleXmlToArray($x);
        $count = count($x);
        if (isset($x['@attributes']) && $count > 1) {
          unset($x['@attributes']);
          $count--;
        }
        if ($count == 1) {
          $x = reset($x);
        }
        if (empty($x)) {
          unset($xpath[$key], $x);
        }
      }
      if (count($xpath) == 1) {
        $xpath = reset($xpath);
      }
    }
    return $xpath;
  }

  /**
   * Converts SimpleXml objects to array
   *
   * @param SimpleXmlElement $xml
   *   Object to convert.
   *
   * @return array
   *   Converted result
   */
  public static function SimpleXmlToArray($xml) {
    $xml = (array) $xml;
    // Remove comments.
    self::RemoveComment($xml);
    foreach ($xml as &$item) {
      if (!is_scalar($item)) {
        $item = self::SimpleXmlToArray($item);
        // Remove comments.
        self::RemoveComment($item);
      }
    }
    return $xml;
  }

  /**
   * Removes comment tags from xml array
   *
   * @param array &$xml
   *   Array where to remove comment
   */
  public static function RemoveComment(array &$xml) {
    if (isset($xml['comment'])) {
      if (empty($xml['comment'])) {
        unset($xml['comment']);
      }
      else {
        // Remove empty values.
        $xml['comment'] = array_filter($xml['comment'], 'count');
        switch (count($xml['comment'])) {
          case 0:
            unset($xml['comment']);
            break;
          case 1:
            $xml['comment'] = reset($xml['comment']);
            break;
          default:
            $xml['comment'] = array_values($xml['comment']);
            break;
        }
      }
    }
  }

  /**
   * Creates a hash using uniq, feed machine name and entity type
   *
   * @param string $uniq
   *   Unique item
   * @param string $feed_machine
   *   Feed machine name
   * @param string $entity
   *   Entity name
   *
   * @return string
   *   Hash value
   */
  protected static function createHash($uniq, $feed_machine, $entity) {
    return md5($uniq . '/' . $feed_machine . '/' . $entity);
  }

  /**
   * Gets entity ids from a hashes
   *
   * @param array &$hashes
   *   Array of hashes
   *
   * @return array
   *   Fetched hashes in database
   */
  protected static function getEntityIdsFromHash(array &$hashes) {
    return db_select('feed_import_hashes', 'f')
            ->fields('f', array('hash', 'entity', 'id', 'entity_id'))
            ->condition('hash', $hashes, 'IN')
            ->execute()
            ->fetchAllAssoc('hash');
  }

  /**
   * Checks if a variable has content
   *
   * @param mixed $var
   *   Variable to check
   *
   * @return bool
   *   TRUE if there is content FALSE otherwise
   */
  public static function hasContent(&$var) {
    if (is_scalar($var)) {
      if ((string) $var === '') {
        return FALSE;
      }
    }
    elseif (empty($var)) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Default actions when result is empty
   */
  public static function getDefaultActions() {
    return array(
      'default_value' => t('Provide a default value'),
      'default_value_filtered' => t('Provide a filtered default value'),
      'ignore_field' => t('Ignore this field'),
      'skip_item' => t('Skip importing this item'),
    );
  }

  /**
   * Create Entity object
   *
   * @param array &$feed
   *   Feed info array
   * @param object &$item
   *   Current SimpleXMLElement object
   *
   * @return object
   *   Created Entity
   */
  public static function createEntity(&$feed, &$item) {
    // Create new object to hold fields values.
    $entity = new stdClass();
    // Check if items must be monitorized and saved in hashes table.
    if ($feed['xpath']['#uniq']) {
      // Check if item already exists.
      $uniq = self::getXpathValue($item, $feed['xpath']['#uniq']);
      // Hash item can be a property so we must extract it.
      if (is_array($uniq)) {
        $uniq = isset($uniq[0]) ? $uniq[0] : reset($uniq);
      }
      // Create a hash to identify this item in bd.
      $entity->{self::$tempHash} = self::createHash($uniq, $feed['machine_name'], $feed['entity_info']['#entity']);
      // Add to hashes array.
      self::$generatedHashes[] = $entity->{self::$tempHash};
    }
    else {
      $entity->{self::$tempHash} = NULL;
    }
    // Set default language, this can be changed by language item.
    $entity->language = LANGUAGE_NONE;
    // Get all fields.
    foreach ($feed['xpath']['#items'] as &$field) {
      $i = 0;
      $aux = '';
      $count = count($field['#xpath']);
      // Check ONCE if we have to filter or prefilter field.
      $prefilter = !empty($field['#pre_filter']);
      $filter = !empty($field['#filter']);
      // Loop through xpaths until we have data, otherwise use default value.
      while ($i < $count) {
        if (!$field['#xpath'][$i]) {
          $i++;
          continue;
        }
        $aux = self::getXpathValue($item, $field['#xpath'][$i]);
        if ($prefilter) {
          $pfval = self::applyFilter($aux, $field['#pre_filter']);
          // If item doesn't pass prefilter than go to next option.
          if (!self::hasContent($pfval)) {
            $i++;
            continue;
          }
          unset($pfval);
        }
        // If filter passed prefilter then apply filter and exit while loop.
        if (self::hasContent($aux)) {
          if ($filter) {
            $aux = self::applyFilter($aux, $field['#filter']);
          }
          break;
        }
        $i++;
      }
      // If we don't have any data we take default action.
      if (!self::hasContent($aux)) {
        switch ($field['#default_action']) {
          // Provide default value.
          // This is also default action.
          case 'default_value':
          default:
            $aux = $field['#default_value'];
            break;
          // Provide default value before it was filtered.
          case 'default_value_filtered':
            $aux = self::applyFilter($field['#default_value'], $field['#filter']);
            break;
          // Skip this item by returning NULL.
          case 'skip_item':
            return NULL;
            break;
          // Don't add this field to entity.
          case 'ignore_field':
            continue 2;
            break;
        }
      }
      // Set field value.
      // If is object then don't set just column value, set object-array value.
      if ($field['#column']) {
        if (is_array($aux)) {
          $i = 0;
          foreach ($aux as &$auxv) {
            if (is_object($auxv)) {
              $auxv = (array) $auxv;
              $entity->{$field['#field']}[$entity->language][$i] = $auxv;
            }
            else {
              $entity->{$field['#field']}[$entity->language][$i][$field['#column']] = $auxv;
            }
            $i++;
          }
        }
        else {
          if (is_object($aux)) {
            $aux = (array) $aux;
            $entity->{$field['#field']}[$entity->language][0] = $aux;
          }
          else {
            $entity->{$field['#field']}[$entity->language][0][$field['#column']] = $aux;
          }
        }
      }
      else {
        // If this isn't a field then get only first value.
        if (is_array($aux) || is_object($aux)) {
          // This still can be array but if so then problem is elsewhere.
          $aux = reset($aux);
        }
        $entity->{$field['#field']} = $aux;
      }
      // No need anymore, free memory.
      unset($aux);
    }
    return $entity;
  }

  /**
   * Saves/updates all created entities
   *
   * @param array &$feed
   *   Feed info array
   * @param array &$items
   *   An array with entities
   */
  public static function saveEntities(&$feed, &$items) {
    // Get existing items for update.
    if (!empty(self::$generatedHashes)) {
      $ids = self::getEntityIdsFromHash(self::$generatedHashes);
      // Reset all generated hashes.
      self::$generatedHashes = array();
    }
    else {
      $ids = array();
    }
    // This sets expire timestamp.
    $feed['time'] = (int) $feed['time'];
    // Report data.
    self::$report['total'] += count($items);
    // Now we create real entityes or update existent.
    foreach ($items as &$item) {
      // Check if item is skipped.
      if ($item == NULL) {
        continue;
      }
      // Save hash and remove from item.
      $hash = $item->{self::$tempHash};
      unset($item->{self::$tempHash});
      // Check if item is already imported or is not monitorized.
      if ($hash !== NULL && isset($ids[$hash])) {
        $changed = FALSE;
        // Load entity.
        try {
          $entity = call_user_func(self::$functionLoad, $ids[$hash]->entity_id);
        }
        catch (Exception $e) {
          $item = NULL;
          unset($ids[$hash]);
          continue;
        }
        // If entity is missing then skip.
        if (empty($entity)) {
          $item = NULL;
          unset($ids[$hash]);
          continue;
        }
        $lang = $item->language;
        // Find if entity is different from last feed.
        foreach ($item as $key => &$value) {
          if (is_array($value)) {
            if (!isset($entity->{$key}[$lang]) || empty($entity->{$key}[$lang]) || count($entity->{$key}[$lang]) != count($value[$lang])) {
              $changed = TRUE;
              $entity->{$key} = $value;
            }
            elseif (count($value[$lang]) <= 1) {
              $col = isset($value[$lang][0]) ? key($value[$lang][0]) : '';
              if ($entity->{$key}[$lang][0][$col] != $value[$lang][0][$col]) {
                $changed = TRUE;
                $entity->{$key} = $value;
              }
              unset($col);
            }
            else {
              $col = key($value[$lang][0]);
              $temp = array();
              foreach ($entity->{$key}[$lang] as &$ev) {
                $temp[][$col] = $ev[$col];
              }
              if ($temp != $value[$lang]) {
                $changed = TRUE;
                $entity->{$key} = $value;
              }
              unset($temp, $col);
            }
          }
          else {
            if (!isset($entity->{$key}) || $entity->{$key} != $value) {
              $changed = TRUE;
              $entity->{$key} = $value;
            }
          }
        }
        $ok = TRUE;
        // Check if entity is changed and save changes.
        if ($changed) {
          try {
            call_user_func(self::$functionSave, $entity);
            // Set report about updated items.
            self::$report['updated']++;
          }
          catch (Exception $e) {
            $ok = FALSE;
          }
        }
        else {
          // Set report about rescheduled items.
          self::$report['rescheduled']++;
        }
        if ($ok) {
          // Add to update ids.
          self::updateIds($ids[$hash]->id);
        }
        // Free some memory.
        unset($ids[$hash], $entity, $lang);
      }
      else {
        // Mark as new.
        $item->{$feed['entity_info']['#table_pk']} = NULL;
        $ok = TRUE;
        try {
          // Save imported item.
          call_user_func(self::$functionSave, $item);
        }
        catch (Exception $e) {
          $ok = FALSE;
        }
        if ($ok) {
          // Check if is monitorized.
          if ($hash !== NULL) {
            $vars = array(
              $feed['machine_name'],
              $feed['entity_info']['#entity'],
              $item->{$feed['entity_info']['#table_pk']},
              $hash,
              $feed['time'] ? time() + $feed['time'] : 0,
            );
            // Insert into feed import hash table.
            self::insertItem($vars);
          }
          // Set report about new items.
          self::$report['new']++;
        }
      }
      // No need anymore.
      $item = NULL;
    }
    // No need anymore.
    unset($items, $ids);
    // Only monitorized items are inserted or updated.
    if (!empty($feed['xpath']['#uniq'])) {
      // Insert left items.
      self::insertItem(NULL);
      $vars = array(
        'expire' => $feed['time'] ? time() + $feed['time'] : 0,
        'feed_machine_name' => $feed['machine_name'],
      );
      // Update ids for existing items.
      self::updateIds($vars);
    }
  }

  /**
   * Filters a field
   *
   * @param mixed $field
   *   A string or array of strings containing field value
   * @param array $filters
   *   Filters to apply
   *
   * @return mixed
   *   Filtered value of field
   */
  protected static function applyFilter($field, $filters) {
    $field_param = variable_get('feed_import_field_param_name', '[field]');
    foreach ($filters as &$filter) {
      $filter['#function'] = trim($filter['#function']);
      // Check if function exists, support static functions.
      if (strpos($filter['#function'], '::') !== FALSE) {
        $filter['#function'] = explode('::', $filter['#function'], 2);
        if ($filter['#function'][0] == '') {
          $filter['#function'][0] = 'FeedImportFilter';
        }
        if (!method_exists($filter['#function'][0], $filter['#function'][1])) {
          continue;
        }
      }
      else {
        if (!function_exists($filter['#function'])) {
          continue;
        }
      }
      // Set field value.
      $key = array_search($field_param, $filter['#params']);
      $filter['#params'][$key] = $field;
      // Apply filter.
      try {
        $field = call_user_func_array($filter['#function'], $filter['#params']);
      }
      catch (Exception $e) {
        // Just report this error. Nothing to handle.
      }
      $filter = NULL;
    }
    return $field;
  }

  /**
   * Checks if entity functions exists
   *
   * @param string $entity
   *   Entity name
   *
   * @return bool
   *   TRUE if function exists, FALSE otherwise
   */
  protected static function checkFunctions($entity) {
    self::$functionSave = $entity . '_save';
    self::$functionLoad = $entity . '_load';
    return function_exists(self::$functionSave) && function_exists(self::$functionLoad);
  }

  /**
   * Insert imported item in feed_import_hashes
   *
   * @param mixed $values
   *   An array of values or NULL to execute insert
   */
  protected static function insertItem($values) {
    static $q_insert = NULL;
    static $q_insert_items = 0;
    if ($q_insert == NULL) {
      $q_insert = db_insert('feed_import_hashes')
                    ->fields(array('feed_machine_name', 'entity', 'entity_id', 'hash', 'expire'));
    }
    $q_insert_chunk = variable_get('feed_import_insert_hashes_chunk', 500);
    // Call execute and reset number of insert items.
    if ($values == NULL) {
      if ($q_insert_items) {
        $q_insert->execute();
        $q_insert_items = 0;
      }
      return;
    }
    // Set values.
    $q_insert->values($values);
    $q_insert_items++;
    if ($q_insert_items == $q_insert_chunk) {
      $q_insert->execute();
      $q_insert_items = 0;
    }
  }

  /**
   * Update imported items ids in feed_import_hashes
   *
   * @param mixed $value
   *   An int value to add id to list or an array containing
   *   info about update conditions to execute update
   */
  protected static function updateIds($value) {
    static $update_ids = array();
    if (is_array($value)) {
      if (empty($update_ids)) {
        return;
      }
      $q_update = db_update('feed_import_hashes')
                    ->fields(array('expire' => $value['expire']))
                    ->condition('feed_machine_name', $value['feed_machine_name'], '=');
      $conditions = &$q_update->conditions();
      // Split in chunks.
      $update_ids = array_chunk($update_ids, variable_get('feed_import_update_ids_chunk', 1000));
      foreach ($update_ids as &$ids) {
        $q_update->condition('id', $ids, 'IN')->execute();
        // Remove last IN condition.
        array_pop($conditions);
        $ids = NULL;
      }
      // Reset update ids.
      $update_ids = array();
    }
    else {
      // Add to list.
      $update_ids[] = (int) $value;
    }
  }

  /**
   * *****************************
   * Feed processors variables
   * *****************************
   */

  // Save function name (_save)
  public static $functionSave;
  // Load function name (_load)
  public static $functionLoad;
  // SimpleXMLElement class, you can use a class that extends default
  public static $simpleXMLElement = 'SimpleXMLElement';
  // Temporary property name for hash
  protected static $tempHash = '_feed_item_hash';
  // Generated Hashes
  protected static $generatedHashes = array();

  /**
   * *****************************
   * Feed processors
   * *****************************
   */

  /**
   * Imports and process a feed normally
   *
   * @param array $feed
   *   Feed info array
   *
   * @return array
   *   An array of objects
   */
  public static function processXML(array $feed) {
    // Load xml file from url.
    try {
      $xml = simplexml_load_file($feed['url'], self::$simpleXMLElement, LIBXML_NOCDATA);
    }
    catch (Exception $e) {
      return NULL;
    }
    // If there is no SimpleXMLElement object.
    if (!($xml instanceof self::$simpleXMLElement)) {
      return NULL;
    }
    $namespaces = &$feed['xpath']['#settings'];

    // Check for namespace settings.
    if (!empty($namespaces)) {
      foreach ($namespaces as $key => &$namespace) {
        if (!$namespace) {
          unset($namespaces[$key]);
          continue;
        }
        $namespace = explode(' ', $namespace, 2);
        if (count($namespace) != 2 || empty($namespace[0]) || empty($namespace[1])) {
          unset($namespaces[$key]);
          continue;
        }
        // Set namespace.
        $xml->registerXPathNamespace($namespace[0], $namespace[1]);
      }
    }
    else {
      $namespaces = array();
    }
    // Get items from root.
    $xml = $xml->xpath($feed['xpath']['#root']);
    // Get total number of items.
    $count_items = count($xml);
    // Check if there are items.
    if (!$count_items) {
      return NULL;
    }

    // Check feed items.
    if (empty($namespaces)) {
      foreach ($xml as &$item) {
        // Set this item value to entity, so all entities will be in $xml at end!
        $item = self::createEntity($feed, $item);
      }
    }
    else {
      foreach ($xml as &$item) {
        // Register namespaces.
        foreach ($namespaces as &$namespace) {
          $item->registerXPathNamespace($namespace[0], $namespace[1]);
        }
        // Set this item value to entity, so all entities will be in $xml at end!
        $item = self::createEntity($feed, $item);
      }
    }
    unset($feed);
    // Return created entities.
    return $xml;
  }

  /**
   *  Callback for validating processXML settings
   */
  public static function processXMLValidate($field, $value, $default) {
    if (strpos($field, ' ') === FALSE) {
      return $default;
    }
    return $value;
  }

  /**
   * Imports and process a huge xml in chunks
   *
   * @param array $feed
   *   Feed info array
   *
   * @return array
   *   An array of objects
   */
  public static function processXMLChunked(array $feed) {
    // This will hold all generated entities.
    $entities = array();
    // XML head.
    $xml_head = $feed['xpath']['#settings']['xml_properties'];
    // Bytes read with fread.
    $chunk_length = $feed['xpath']['#settings']['chunk_size'];
    // Items count.
    $items_count = $feed['xpath']['#settings']['items_count'];
    $current = 0;
    // Open xml url.
    try {
      $fp = fopen($feed['url'], 'rb');
    }
    catch (Exception $e) {
      return NULL;
    }
    // Preparing tags.
    $tag = explode('/', $feed['xpath']['#root']);
    $tag = trim(end($tag));
    $tag = array(
      'open' => '<' . $tag,
      'close' => '</' . $tag . '>',
      'length' => drupal_strlen($tag),
    );
    $tag['closelength'] = drupal_strlen($tag['close']);
    // This holds xml content.
    $content = '';
    // Read all content in chunks.
    while (!feof($fp)) {
      $content .= fread($fp, $chunk_length);
      // If there isn't content read again.
      if (!$content) {
        continue;
      }
      while (TRUE) {
        $openpos = strpos($content, $tag['open']);
        $openposclose = $openpos + $tag['length'] + 1;
        // Check for open tag.
        if ($openpos === FALSE || !isset($content[$openposclose])) {
          break;
        }
        elseif ($content[$openposclose] != ' ' && $content[$openposclose] != '>') {
          $content = substr($content, $openposclose);
          continue;
        }
        $closepos = strpos($content, $tag['close'], $openposclose);
        if ($closepos === FALSE) {
          break;
        }
        // We have data!
        $closepos += $tag['closelength'];

        // Create xml string.
        $item = $xml_head . substr($content, $openpos, $closepos - $openpos);
        // New content.
        $content = substr($content, $closepos - 1);
        // Create xml object.
        try {
          $item = simplexml_load_string($item, self::$simpleXMLElement, LIBXML_NOCDATA);
        }
        catch (Exception $e) {
          continue;
        }
        // Parse item.
        $item = $item->xpath($feed['xpath']['#root']);
        $item = reset($item);
        if (empty($item)) {
          continue;
        }
        // Create entity.
        $item = self::createEntity($feed, $item);
        // Put in entities array.
        $entities[] = $item;
        $current++;
        // Check if we have to save imported entities.
        if ($current == $items_count) {
          // Save entities.
          self::saveEntities($feed, $entities);
          // Delete imported items so far to save memory.
          $entities = array();
          // Reset counter.
          $current = 0;
        }
        // No need anymore.
        unset($item);
      }
    }
    // Close file.
    // If fp is not a resurce then catch warning.
    // Minimum chances for this to happen.
    try {
      fclose($fp);
    }
    catch (Exception $e) {
      // Nothing to handle here. Used for reporting error.
    }
    if (!empty($entities)) {
      // Save left entities.
      self::saveEntities($feed, $entities);
    }
    // Delete feed info.
    unset($feed);
    // Return NULL because we saved all entities.
    return NULL;
  }
  /**
   * Callback for validating processXMLChunked settings
   */
  public static function processXMLChunkedValidate($field, $value, $default = NULL) {
    switch ($field) {
      case 'xml_properties':
        $value = trim($value);
        if (!preg_match("/^\<\?xml (.*)\?\>$/", $value)) {
          return $default;
        }
        break;
      case 'chunk_size':
        $value = (int) $value;
        if ($value <= 0) {
          return $default;
        }
        break;
    }
    return $value;
  }

  /**
   * Imports and process a HTML page
   *
   * @param array $feed
   *   Feed info array
   *
   * @return array
   *   An array of objects
   */
  public static function processHTMLPage(array $feed) {
    // Create DOM Document.
    $xml = new DOMDocument();
    $xml->strictErrorChecking = FALSE;
    $xml->preserveWhiteSpace = FALSE;
    $xml->recover = TRUE;
    // Load HTML file from url.
    try {
      if ($feed['xpath']['#settings']['report_html_errors']) {
        $xml->loadHTMLFile($feed['url']);
      }
      else {
        @$xml->loadHTMLFile($feed['url']);
      }
    }
    catch (Exception $e) {
      // This try-catch is just to parse the HTML file. Nothing to handle.
    }
    // Normalize document.
    $xml->normalizeDocument();
    // Try to convert to xml.
    try {
      $xml = simplexml_import_dom($xml, self::$simpleXMLElement);
    }
    catch (Exception $e) {
      return NULL;
    }
    // If there is no SimpleXMLElement object.
    if (!($xml instanceof self::$simpleXMLElement)) {
      return NULL;
    }
    // Get items from root.
    $xml = $xml->xpath($feed['xpath']['#root']);
    // Get total number of items.
    $count_items = count($xml);
    // Check if there are items.
    if (!$count_items) {
      return NULL;
    }
    // Check feed items.
    foreach ($xml as &$item) {
      // Set this item value to entity, so all entities will be in $xml at end!
      $item = self::createEntity($feed, $item);
    }
    unset($feed);
    // Return created entities.
    return $xml;
  }

  /**
   * Callback for validating processHTMLPAge settings
   */
  public static function processHTMLPageValidate($field, $value, $default = NULL) {
    if ($field == 'report_html_errors') {
      if ($value != 0 && $value != 1) {
        return $default;
      }
    }
    return $value;
  }

  /**
   * Imports and process a CSV file
   * First line must contain column names!
   *
   * @param array $feed
   *   Feed info array
   *
   * @return array
   *   An array of objects
   */
  public static function processCSV(array $feed) {
    // Get $length, $delimiter, $enclosure, $escape and $use_column_names settings.
    extract($feed['xpath']['#settings']);
    // Open CSV file.
    try {
      $fp = fopen($feed['url'], 'rb');
    }
    catch (Exception $e) {
      return NULL;
    }
    // Here will be all items.
    $entities = array();
    // Create a single xml object to hold each row by updating row values.
    $xml = new self::$simpleXMLElement('<' . trim($feed['xpath']['#root'], '/') . '/>');
    // Get first line form file.
    $line = fgetcsv($fp, $length, $delimiter, $enclosure, $escape);
    if ($line === FALSE) {
      return NULL;
    }
    // Create child nodes.
    if (!$use_column_names) {
      foreach ($line as $index => &$col) {
        $xml->addChild('column', $col)
            ->addAttribute('index', $index + 1);
      }
      $entities[] = self::createEntity($feed, $xml);
    }
    else {
      foreach ($line as $index => &$col) {
        $child = $xml->addChild('column', NULL);
        $child->addAttribute('index', $index + 1);
        $child->addAttribute('name', $col);
      }
    }
    // Read file line by line.
    while (($line = fgetcsv($fp, 0, $delimiter, $enclosure, $escape)) !== FALSE) {
      $i = 0;
      // Update created xml with new values.
      foreach ($xml->children() as $child) {
        // Well, check if column exists before using it.
        $child[0] = isset($line[$i]) ? $line[$i] : NULL;
        unset($line[$i]);
        $i++;
      }
      // Add to entities.
      $entities[] = self::createEntity($feed, $xml);
      $line = NULL;
    }
    try {
      fclose($fp);
    }
    catch (Exception $e) {
      // Nothing to handle.
    }
    return $entities;
  }

  /**
   * Callback for validating processCSV settings
   */
  public static function processCSVValidate($field, $value, $default = NULL) {
    switch ($field) {
      case 'length':
        // Must be positive integer.
        if ((int) $value != $value || $value < 0) {
          return $default;
        }
        break;
      case 'use_column_names':
        if ($value != 0 && $value != 1) {
          return $default;
        }
        break;
      default:
        // Check delimiters.
        if (drupal_strlen($value) != 1) {
          return $default;
        }
        break;
    }
    return $value;
  }

  /**
   * Process large xml file with XmlReader
   *
   * @param array $feed
   *   Feed info array
   *
   * @return NULL
   *   Returns NULL because items are already processed
   */
  public static function processXMLReader(array $feed) {
    // Parse parent xpath.
    $feed['xpath']['#root'] = trim(trim($feed['xpath']['#root'], '/'));
    if (!preg_match('/([a-zA-Z\:]?)(?:\[@(\w+)[\s+]?(?:=[\s+]?["\']?(.*)?["\'])?\])?/', $feed['xpath']['#root'], $match)) {
      // If not a valid one then exit.
      return NULL;
    }
    // Create the xmlreader resource.
    $xml = new XMLReader();
    // Open XML file.
    try {
      if (!$xml->open($feed['url'], 'utf-8', (1 << 19) | LIBXML_NOCDATA)) {
        // If failed to open then exit.
        return NULL;
      }
    }
    catch (Exception $e) {
      return NULL;
    }
    // Get items count from settings.
    $items_count = $feed['xpath']['#settings']['items_count'];
    // This will hold created items.
    $entities = array();
    $current = 0;
    // Jump to first node.
    switch (count($match)) {
      case 2:
        $tag_name = $match[1];
        $attribute = $attribute_value = NULL;
        while ($xml->read() && $xml->name != $tag_name);
        break;
      case 3:
        $tag_name = $match[1];
        $attribute = $match[2];
        $attribute_value = NULL;
        while ($xml->read() && ($xml->name != $tag_name || $xml->getAttribute($attribute) === NULL));
        break;
      case 4:
        $tag_name = $match[1];
        $attribute = $match[2];
        $attribute_value = $match[3];
        while ($xml->read() && ($xml->name != $tag_name || $xml->getAttribute($attribute) != $attribute_value));
        break;
      default:
        // Close xml doc.
        try {
          $xml->close();
        }
        catch (Exception $e) {
          // Handle possible errors.
        }
        // Stop import.
        return NULL;
        break;
    }
    // No need anymore.
    unset($match);
    // Create the DomDocument used to convert to SimplexXmlElement.
    $doc = new DOMDocument();
    // Loop through all items.
    do {
      // Check for attribute.
      if ($attribute) {
        if ($attribute_value) {
          if ($xml->getAttribute($attribute) != $attribute_value) {
            continue;
          }
        }
        else {
          if ($xml->getAttribute($attribute) === NULL) {
            continue;
          }
        }
      }
      // Get dom node.
      try {
        $node = $xml->expand();
      }
      catch (Exception $e) {
        break;
      }
      if (!$node) {
        break;
      }
      // Create the xml node.
      $node = $doc->importNode($node, TRUE);
      // Add it to document.
      $doc->appendChild($node);
      // Convert it to simplexml.
      try {
        $item = simplexml_import_dom($doc, self::$simpleXMLElement);
      }
      catch (Exception $e) {
        $doc->removeChild($node);
        $item = $node = NULL;
        // Skip this item if xml is invalid.
        continue;
      }
      // Create entity object.
      $item = self::createEntity($feed, $item);
      // Remove from document and free memory.
      $doc->removeChild($node);
      $node = NULL;
      // Check if empty.
      if (empty($item)) {
        continue;
      }
      // Add to entities.
      $entities[] = $item;
      $current++;
      if ($current == $items_count) {
        // Save entities.
        self::saveEntities($feed, $entities);
        // Delete imported items so far to save memory.
        $entities = array();
        // Reset counter.
        $current = 0;
      }
      unset($item);
    }
    while ($xml->next($tag_name));
    // close xml file.
    try {
      $xml->close();
    }
    catch (Exception $e) {
      // Just report any possible errors.
    }
    // No need anymore.
    unset($xml, $doc, $node);
    // Save left entities.
    if (!empty($entities)) {
      self::saveEntities($feed, $entities);
    }
    // Delete feed info.
    unset($feed, $entities);
    // We processed all entities so we return null.
    return NULL;
  }

  /**
   * Callback for validating processXmlReader settings
   */
  public static function processXMLReaderValidate($field, $value, $default = NULL) {
    $value = (int) $value;
    if ($value <= 0) {
      return $default;
    }
    return $value;
  }
}
