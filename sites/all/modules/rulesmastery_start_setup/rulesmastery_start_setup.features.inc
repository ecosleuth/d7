<?php
/**
 * @file
 * rulesmastery_start_setup.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function rulesmastery_start_setup_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function rulesmastery_start_setup_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_flag_default_flags().
 */
function rulesmastery_start_setup_flag_default_flags() {
  $flags = array();
  // Exported flag: "Like".
  $flags['like'] = array(
    'content_type' => 'node',
    'title' => 'Like',
    'global' => '0',
    'types' => array(
      0 => 'topic',
      1 => 'tutorial',
    ),
    'flag_short' => 'Like this',
    'flag_long' => 'Click here if you like this content',
    'flag_message' => '',
    'unflag_short' => 'You like this!',
    'unflag_long' => 'Click here to stop liking it',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'module' => 'rulesmastery_start_setup',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  // Exported flag: "Spam comment".
  $flags['spam'] = array(
    'content_type' => 'comment',
    'title' => 'Spam comment',
    'global' => '0',
    'types' => array(
      0 => 'article',
      1 => 'page',
      2 => 'topic',
      3 => 'tutorial',
    ),
    'flag_short' => 'Mark as spam',
    'flag_long' => 'Click here to mark this comment as spam',
    'flag_message' => '',
    'unflag_short' => 'Remove spam flag',
    'unflag_long' => 'Click here to remove your spam flag',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'access_author' => '',
    'show_on_comment' => 1,
    'module' => 'rulesmastery_start_setup',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;
}

/**
 * Implements hook_node_info().
 */
function rulesmastery_start_setup_node_info() {
  $items = array(
    'topic' => array(
      'name' => t('Topic'),
      'base' => 'node_content',
      'description' => t('Topics are used to structure learning material on the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'tutorial' => array(
      'name' => t('Tutorial'),
      'base' => 'node_content',
      'description' => t('Tutorials help people learn different topics listed on the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
