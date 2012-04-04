<?php
/**
 * @file
 * Enables users to upload files and create multiple corresponding nodes
 */

/**
 * Upload nodes admin view
 */

function upload_nodes_admin_view() {
  $manageable_targets = _upload_nodes_get_manageable_targets();
  $managed_targets = _upload_nodes_get_managed_targets();

  $header = array(t('Node type'), t('Field name'), t('Field type'), array('data' => t('Operations'), 'colspan' => 2));

  $rows = array();
  foreach ($manageable_targets as $target) {

    $row = array($target['type_label'], $target['field_label'], $target['field_type']);

    if (isset($managed_targets[$target['key']])) {
      $row[] = l(t('disable'), 'admin/config/media/upload-nodes/' . $target['key'] . '/disable');
      $row[] = l(t('edit'), 'admin/config/media/upload-nodes/' . $target['key'] . '/edit');
    }
    else {
      $row[] = l(t('enable'), 'admin/config/media/upload-nodes/' . $target['key'] . '/enable');
      $row[] = '';
    }

    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Enable a target
 */

function upload_nodes_admin_enable($node_type, $field_name) {
  $key = $node_type . '/' . $field_name;
  $managed_targets = _upload_nodes_get_managed_targets();

  if (!isset($managed_targets[$key])) {
    $manageable_targets = _upload_nodes_get_manageable_targets();

    if (isset($manageable_targets[$key])) {
      // Add target in managed targets
      $managed_targets[$key] = $manageable_targets[$key];
      // Default settings
      $managed_targets[$key]['settings']['edit phase'] = 1;

      variable_set('upload_nodes_targets', $managed_targets);
      _upload_nodes_targets_changed();
    }
    else {
      drupal_set_message(t('Field %field of %type is not manageable by Upload nodes.',
        array('%field' => $field_name, '%type' => $node_type)), 'error');
    }
  }
  drupal_goto('admin/config/media/upload-nodes');
}

/**
 * Disable a target
 */

function upload_nodes_admin_disable($node_type, $field_name) {
  $key = $node_type . '/' . $field_name;
  $managed_targets = _upload_nodes_get_managed_targets();

  if (isset($managed_targets[$key])) {
    unset($managed_targets[$key]);
    variable_set('upload_nodes_targets', $managed_targets);
    _upload_nodes_targets_changed();
  }
  drupal_goto('admin/config/media/upload-nodes');
}

/**
 * upload nodes admin edit form
 */

function upload_nodes_admin_edit_form($form, &$form_state, $type_name, $field_name) {
  if (!$target = _upload_nodes_get_target($type_name, $field_name))
    drupal_not_found();
  else {
    drupal_set_title(t('Upload nodes configuration for !field from !type',
        array('!type' => $target['type_label'], '!field' => $target['field_label'])), PASS_THROUGH);

    $form['upload_nodes_type_name'] = array(
      '#type' => 'value',
      '#value' => $type_name,
    );
    $form['upload_nodes_field_name'] = array(
      '#type' => 'value',
      '#value' => $field_name,
    );

    $form['edit_phase'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable edit phase after nodes creation.'),
      '#default_value' => $target['settings']['edit phase'],
    );

    $form['#tree'] = TRUE;
    $form['fields'] = array(
         '#type' => 'fieldset',
         '#title' => 'Fields',
         '#theme' => 'upload_nodes_admin_fieldset',
    );

    $field_info_instances = array('title' => array('field_name' => 'title', 'label' => t('Title'), ))
                            + field_info_instances('node', $type_name);

    foreach ($field_info_instances as $field_info_instance) {
      $field = $field_info_instance['field_name'];
      if ($field != $field_name) {
        if (isset($target['settings']['fields'][$field])) {
          $on_upload = $target['settings']['fields'][$field]['on_upload'];
          $on_edit = $target['settings']['fields'][$field]['on_edit'];
        }
        else {
          // Defaults
          $on_upload = 0;
          $on_edit = 1;
        }

        $form['fields'][$field]['name'] = array(
           '#markup' => $field_info_instance['label'],
        );

        $form['fields'][$field]['on_upload'] = array(
           '#type' => 'checkbox',
           '#title' => t('On upload form'),
           '#default_value' => $on_upload,
        );

        $form['fields'][$field]['on_edit'] = array(
           '#type' => 'checkbox',
           '#title' => t('On edit form'),
           '#default_value' => $on_edit,
        );
      }
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    return $form;
  }
}

/**
 * Theme function for field table in admin edit form
 */

function theme_upload_nodes_admin_fieldset($variables) {
  $form = $variables['form'];

  foreach (element_children($form) as $key) {
    $row = array();

    $field = $form[$key];
    unset($field['on_upload']['#title']);
    unset($field['on_edit']['#title']);

    $row[] = drupal_render($field['name']);

    $row[] = array(
      'class' => array('checkbox'),
      'data' => drupal_render($field['on_upload']),
    );

    $row[] = array(
      'class' => array('checkbox'),
      'data' => drupal_render($field['on_edit']),
    );

    $rows[] = $row;
  }

  return theme('table', array('header' => array('Field', 'On upload form', 'On edit form'), 'rows' => $rows));
}

/**
 * Submit callback for upload nodes admin edit form
 */

function upload_nodes_admin_edit_form_submit($form, &$form_state) {
  $type_name = $form_state['values']['upload_nodes_type_name'];
  $field_name = $form_state['values']['upload_nodes_field_name'];

  if (!$target = _upload_nodes_get_target($type_name, $field_name))
    drupal_not_found();
  else {
    $target['settings']['edit phase']  = $form_state['values']['edit_phase'];
    $target['settings']['fields']  = $form_state['values']['fields'];

    $managed_targets = _upload_nodes_get_managed_targets();
    $managed_targets[$type_name . '/' . $field_name] = $target;
    variable_set('upload_nodes_targets', $managed_targets);

    $form_state['redirect'] = 'admin/config/media/upload-nodes';
  }
}
