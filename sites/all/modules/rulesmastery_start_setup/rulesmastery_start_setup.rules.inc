<?php
/**
 * @file
 * Contains an action to fetch the level configuration for Drupal points. And a
 * data type that handles this configuration.
 */

/**
 * Implements hook_rules_data_info().
 */
function rulesmastery_start_setup_rules_data_info() {
  $data['rulesmastery_level'] = array(
    'label' => t('Drupal points level config'),
    'group' => t('Rules mastery'),
    'wrap' => TRUE,
    'property info' => array(
      'role' => array(
        'label' => t('role'),
        'type' => 'list<integer>',
      ),
      'limit' => array(
        'label' => t('point limit'),
        'type' => 'integer',
      ),
    ),
  );

  return $data;
}

/**
 * Implements hook_rules_action_info().
 */
function rulesmastery_start_setup_rules_action_info() {
  $actions['rulesmastery_load_levels'] = array(
    'label' => t('Load Drupal point levels'),
    'group' => t('Rules mastery'),
    'provides' => array(
      'level_config' => array(
        'type' => 'list<rulesmastery_level>',
        'label' => t('Drupal point levels'),
      ),
    ),
  );

  return $actions;
}

/**
 * Loads the level configuration for Drupal points in a format that Rules reads.
 * @see rulesmastery_get_levels()
 * @see hook_rules_action_info()
 */
function rulesmastery_load_levels() {
  // The array provided by rulesmastery_get_levels works fine with Rules, but
  // must be wrapped in an array telling the calling action the name of the
  // provided parameter.
  return array('level_config' => rulesmastery_get_levels());
}
