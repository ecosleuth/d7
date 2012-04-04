<?php

/**
 * Implements hook_field_formatter_info().
 */
function mediafront_field_formatter_info() {
  return array(
    'mediafront_player' => array(
      'label' => t('MediaFront Player'),
      'description' => t('Play this file using a MediaFront Preset.'),
      'field types' => array('file', 'text'),
      'settings' => array(
        'preset' => '',
        'preview' => ''
      )
    )
  );
}

/**
 * Implements hook_field_formatter_settings_form
 */
function mediafront_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state, $type = 'mediafront_player') {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();
  if ($display['type'] == $type) {

    // Add the perset selection.
    $element['preset'] = mediafront_preset_select_form($settings, 'preset');

    $options = array();
    $fields = field_info_instances($instance['entity_type'], $instance['bundle']);
    foreach ($fields as $name => $field) {
      $options[$name] = $field['label'];
    }

    // Set the image preview field for this player.
    $element['preview'] = array(
      '#title' => t('Preview Image Field'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $settings['preview']
    );
  }
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary
 */
function mediafront_field_formatter_settings_summary($field, $instance, $view_mode, $type = 'mediafront_player') {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';
  if ($display['type'] == $type) {
    $header = array('Setting', 'Value');
    $rows = array();
    foreach ($settings as $name => $value) {
      $rows[] = array($name, $value);
    }
    $summary = theme('table', array('header' => $header, 'rows' => $rows));
  }
  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function mediafront_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display, $type = 'mediafront_player') {
  $element = array();
  if ($display['type'] == $type) {
    $settings = $display['settings'];
    $element[] = array(
      '#theme' => $type,
      '#entity' => $entity,
      '#preset' => $settings['preset'],
      '#preview_field' => $settings['preview'],
      '#media_field' => $instance['field_name'],
      '#type' => $display['type']
    );
  }
  return $element;
}
?>