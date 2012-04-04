<?php
/**
 * @file
 * rulesmastery_base_for_vbo.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function rulesmastery_base_for_vbo_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'drupal_points';
  $view->description = 'Administrative view for handling Drupal points for users.';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Drupal points';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Drupal points';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer drupal points';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_user_drupalpoints' => 'field_user_drupalpoints',
  );
  $handler->display->display_options['style_options']['default'] = 'field_user_drupalpoints';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_user_drupalpoints' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: User: Drupal points */
  $handler->display->display_options['fields']['field_user_drupalpoints']['id'] = 'field_user_drupalpoints';
  $handler->display->display_options['fields']['field_user_drupalpoints']['table'] = 'field_data_field_user_drupalpoints';
  $handler->display->display_options['fields']['field_user_drupalpoints']['field'] = 'field_user_drupalpoints';
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_user_drupalpoints']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_user_drupalpoints']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_user_drupalpoints']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_user_drupalpoints']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_user_drupalpoints']['field_api_classes'] = 0;
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['rid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['rid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['rid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['rid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['rid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['rid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['rid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['rid']['hide_alter_empty'] = 1;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/people/drupalpoints';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Drupal points';
  $handler->display->display_options['menu']['description'] = 'Handle Drupal points for users';
  $handler->display->display_options['menu']['weight'] = '5';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['drupal_points'] = $view;

  return $export;
}
