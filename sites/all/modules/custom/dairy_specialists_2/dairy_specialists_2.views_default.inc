<?php
/**
 * @file
 * dairy_specialists_2.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function dairy_specialists_2_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'ds_recent_comments';
  $view->description = 'Contains a block and a page to list recent comments; the block will automatically link to the page, which displays the comment body as well as a link to the node.';
  $view->tag = 'default';
  $view->base_table = 'comment';
  $view->human_name = 'DS Recent comments';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent comments';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = 5;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Comment: Content */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'comment';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Field: Comment: Title */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'comment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['label'] = '';
  $handler->display->display_options['fields']['subject']['link_to_comment'] = 1;
  /* Field: Comment: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'comment';
  $handler->display->display_options['fields']['timestamp']['field'] = 'changed';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'time ago';
  /* Sort criterion: Comment: Updated date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'comment';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'changed';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Content: article department */
  $handler->display->display_options['arguments']['field_article_department_tid']['id'] = 'field_article_department_tid';
  $handler->display->display_options['arguments']['field_article_department_tid']['table'] = 'field_data_field_article_department';
  $handler->display->display_options['arguments']['field_article_department_tid']['field'] = 'field_article_department_tid';
  $handler->display->display_options['arguments']['field_article_department_tid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['field_article_department_tid']['ui_name'] = 'Content: article department';
  $handler->display->display_options['arguments']['field_article_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_article_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_article_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_article_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_article_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_article_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_article_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_article_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_article_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_article_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_article_department_tid']['not'] = 0;
  /* Contextual filter: Content: blog department */
  $handler->display->display_options['arguments']['field_blog_department_tid']['id'] = 'field_blog_department_tid';
  $handler->display->display_options['arguments']['field_blog_department_tid']['table'] = 'field_data_field_blog_department';
  $handler->display->display_options['arguments']['field_blog_department_tid']['field'] = 'field_blog_department_tid';
  $handler->display->display_options['arguments']['field_blog_department_tid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['field_blog_department_tid']['ui_name'] = 'Content: blog department';
  $handler->display->display_options['arguments']['field_blog_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_blog_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_blog_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_blog_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_blog_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_blog_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_blog_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_blog_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_blog_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_blog_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_blog_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_blog_department_tid']['not'] = 0;
  /* Contextual filter: Content: book department */
  $handler->display->display_options['arguments']['field_book_department_tid']['id'] = 'field_book_department_tid';
  $handler->display->display_options['arguments']['field_book_department_tid']['table'] = 'field_data_field_book_department';
  $handler->display->display_options['arguments']['field_book_department_tid']['field'] = 'field_book_department_tid';
  $handler->display->display_options['arguments']['field_book_department_tid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['field_book_department_tid']['ui_name'] = 'Content: book department';
  $handler->display->display_options['arguments']['field_book_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_book_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_book_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_book_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_book_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_book_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_book_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_book_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_book_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_book_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_book_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_book_department_tid']['not'] = 0;
  /* Contextual filter: Content: event department */
  $handler->display->display_options['arguments']['field_event_department_tid']['id'] = 'field_event_department_tid';
  $handler->display->display_options['arguments']['field_event_department_tid']['table'] = 'field_data_field_event_department';
  $handler->display->display_options['arguments']['field_event_department_tid']['field'] = 'field_event_department_tid';
  $handler->display->display_options['arguments']['field_event_department_tid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['field_event_department_tid']['ui_name'] = 'Content: event department';
  $handler->display->display_options['arguments']['field_event_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_event_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_event_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_event_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_event_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_event_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_event_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_event_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_event_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_event_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_event_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_event_department_tid']['not'] = 0;
  /* Contextual filter: Content: forum department */
  $handler->display->display_options['arguments']['field_forum_department_tid']['id'] = 'field_forum_department_tid';
  $handler->display->display_options['arguments']['field_forum_department_tid']['table'] = 'field_data_field_forum_department';
  $handler->display->display_options['arguments']['field_forum_department_tid']['field'] = 'field_forum_department_tid';
  $handler->display->display_options['arguments']['field_forum_department_tid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['field_forum_department_tid']['ui_name'] = 'Content: forum department';
  $handler->display->display_options['arguments']['field_forum_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_forum_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_forum_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_forum_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_forum_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_forum_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate_options']['type'] = 'name';
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_forum_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_forum_department_tid']['not'] = 0;
  /* Contextual filter: Content: page department */
  $handler->display->display_options['arguments']['field_page_department_tid']['id'] = 'field_page_department_tid';
  $handler->display->display_options['arguments']['field_page_department_tid']['table'] = 'field_data_field_page_department';
  $handler->display->display_options['arguments']['field_page_department_tid']['field'] = 'field_page_department_tid';
  $handler->display->display_options['arguments']['field_page_department_tid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['field_page_department_tid']['ui_name'] = 'Content: page department';
  $handler->display->display_options['arguments']['field_page_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_page_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_page_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_page_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_page_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_page_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_page_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_page_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_page_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_page_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_page_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_page_department_tid']['not'] = 0;
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['relationship'] = 'nid';
  $handler->display->display_options['filters']['status_extra']['group'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['row_options']['separator'] = '&nbsp;';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['label'] = 'Reply to';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Comment: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'comment';
  $handler->display->display_options['fields']['timestamp']['field'] = 'changed';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'time ago';
  /* Field: Comment: Title */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'comment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['label'] = '';
  $handler->display->display_options['fields']['subject']['link_to_comment'] = 1;
  /* Field: Comment: Comment */
  $handler->display->display_options['fields']['comment']['id'] = 'comment';
  $handler->display->display_options['fields']['comment']['table'] = 'field_data_comment_body';
  $handler->display->display_options['fields']['comment']['field'] = 'comment_body';
  $handler->display->display_options['fields']['comment']['label'] = '';
  $handler->display->display_options['path'] = 'comments/recent';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['ds_recent_comments'] = $view;

  $view = new view;
  $view->name = 'ds_recent_content';
  $view->description = 'View recent posts - articles, pages, forum posts, etc.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'DS Recent Posts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent Posts';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = 0;
  $handler->display->display_options['row_options']['comments'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Event Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: article department */
  $handler->display->display_options['arguments']['field_article_department_tid']['id'] = 'field_article_department_tid';
  $handler->display->display_options['arguments']['field_article_department_tid']['table'] = 'field_data_field_article_department';
  $handler->display->display_options['arguments']['field_article_department_tid']['field'] = 'field_article_department_tid';
  $handler->display->display_options['arguments']['field_article_department_tid']['ui_name'] = 'Content: article department';
  $handler->display->display_options['arguments']['field_article_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_article_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_article_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_article_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_article_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_article_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_article_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_article_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_article_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_article_department_tid']['validate_options']['transform'] = '1';
  $handler->display->display_options['arguments']['field_article_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_article_department_tid']['not'] = 0;
  /* Contextual filter: Content: blog department */
  $handler->display->display_options['arguments']['field_blog_department_tid']['id'] = 'field_blog_department_tid';
  $handler->display->display_options['arguments']['field_blog_department_tid']['table'] = 'field_data_field_blog_department';
  $handler->display->display_options['arguments']['field_blog_department_tid']['field'] = 'field_blog_department_tid';
  $handler->display->display_options['arguments']['field_blog_department_tid']['ui_name'] = 'Content: blog department';
  $handler->display->display_options['arguments']['field_blog_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_blog_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_blog_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_blog_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_blog_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_blog_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_blog_department_tid']['not'] = 0;
  /* Contextual filter: Content: book department */
  $handler->display->display_options['arguments']['field_book_department_tid']['id'] = 'field_book_department_tid';
  $handler->display->display_options['arguments']['field_book_department_tid']['table'] = 'field_data_field_book_department';
  $handler->display->display_options['arguments']['field_book_department_tid']['field'] = 'field_book_department_tid';
  $handler->display->display_options['arguments']['field_book_department_tid']['ui_name'] = 'Content: book department';
  $handler->display->display_options['arguments']['field_book_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_book_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_book_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_book_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_book_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_book_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_book_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_book_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_book_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_book_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_book_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_book_department_tid']['not'] = 0;
  /* Contextual filter: Content: forum department */
  $handler->display->display_options['arguments']['field_forum_department_tid']['id'] = 'field_forum_department_tid';
  $handler->display->display_options['arguments']['field_forum_department_tid']['table'] = 'field_data_field_forum_department';
  $handler->display->display_options['arguments']['field_forum_department_tid']['field'] = 'field_forum_department_tid';
  $handler->display->display_options['arguments']['field_forum_department_tid']['ui_name'] = 'Content: forum department';
  $handler->display->display_options['arguments']['field_forum_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_forum_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_forum_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_forum_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_forum_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_forum_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_forum_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_forum_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_forum_department_tid']['not'] = 0;
  /* Contextual filter: Content: page department */
  $handler->display->display_options['arguments']['field_page_department_tid']['id'] = 'field_page_department_tid';
  $handler->display->display_options['arguments']['field_page_department_tid']['table'] = 'field_data_field_page_department';
  $handler->display->display_options['arguments']['field_page_department_tid']['field'] = 'field_page_department_tid';
  $handler->display->display_options['arguments']['field_page_department_tid']['ui_name'] = 'Content: page department';
  $handler->display->display_options['arguments']['field_page_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_page_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_page_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_page_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_page_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_page_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_page_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_page_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
    'forums' => 0,
    'facility_type' => 0,
    'facilityx' => 0,
    'gallery_collections' => 0,
    'tags' => 0,
    'test_vocabulary' => 0,
  );
  $handler->display->display_options['arguments']['field_page_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_page_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_page_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_page_department_tid']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Type: article, page, blog, book, forum */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Type: article, page, blog, book, forum';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
    'page' => 'page',
    'blog' => 'blog',
    'book' => 'book',
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'content/recent';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_type'] = 'h6';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  /* Field: Content: Event Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = 'Date';
  $handler->display->display_options['fields']['field_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_event_date']['element_type'] = 'em';
  $handler->display->display_options['fields']['field_event_date']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_event_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_event_date']['hide_empty'] = 1;
  $handler->display->display_options['fields']['field_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['settings'] = array(
    'format_type' => 'no_year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_event_date']['field_api_classes'] = 0;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
    'page' => 'page',
    'blog' => 'blog',
    'book' => 'book',
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $export['ds_recent_content'] = $view;

  $view = new view;
  $view->name = 'ds_taxonomy_term';
  $view->description = 'A view to emulate Drupal core\'s handling of taxonomy/term.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'DS Taxonomy term';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Has taxonomy term ID (with depth) */
  $handler->display->display_options['arguments']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['term_node_tid_depth']['exception']['title_enable'] = 1;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title_enable'] = 1;
  $handler->display->display_options['arguments']['term_node_tid_depth']['title'] = '%1';
  $handler->display->display_options['arguments']['term_node_tid_depth']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['term_node_tid_depth']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['term_node_tid_depth']['depth'] = '0';
  $handler->display->display_options['arguments']['term_node_tid_depth']['break_phrase'] = 1;
  /* Contextual filter: Content: Has taxonomy term ID depth modifier */
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['id'] = 'term_node_tid_depth_modifier';
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['table'] = 'node';
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['field'] = 'term_node_tid_depth_modifier';
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['exception']['title_enable'] = 1;
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['term_node_tid_depth_modifier']['specify_validation'] = 1;
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['group'] = 0;
  $handler->display->display_options['filters']['status_extra']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'taxonomy/term/%';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = 15;
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'taxonomy/term/%/%/feed';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $export['ds_taxonomy_term'] = $view;

  $view = new view;
  $view->name = 'ds_upcoming_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'DS Upcoming Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Upcoming Events';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = 'h6';
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  /* Field: Content: Event Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = 'Date';
  $handler->display->display_options['fields']['field_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_event_date']['element_type'] = 'em';
  $handler->display->display_options['fields']['field_event_date']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_event_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['settings'] = array(
    'format_type' => 'no_year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_event_date']['field_api_classes'] = 0;
  /* Sort criterion: Content: Event Date -  start date (field_event_date) */
  $handler->display->display_options['sorts']['field_event_date_value']['id'] = 'field_event_date_value';
  $handler->display->display_options['sorts']['field_event_date_value']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['sorts']['field_event_date_value']['field'] = 'field_event_date_value';
  /* Contextual filter: Filter by Department */
  $handler->display->display_options['arguments']['field_event_department_tid']['id'] = 'field_event_department_tid';
  $handler->display->display_options['arguments']['field_event_department_tid']['table'] = 'field_data_field_event_department';
  $handler->display->display_options['arguments']['field_event_department_tid']['field'] = 'field_event_department_tid';
  $handler->display->display_options['arguments']['field_event_department_tid']['ui_name'] = 'Filter by Department';
  $handler->display->display_options['arguments']['field_event_department_tid']['default_action'] = 'summary';
  $handler->display->display_options['arguments']['field_event_department_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_event_department_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_event_department_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_event_department_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_event_department_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_event_department_tid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['field_event_department_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_event_department_tid']['validate_options']['vocabularies'] = array(
    'departments' => 'departments',
  );
  $handler->display->display_options['arguments']['field_event_department_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_event_department_tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['field_event_department_tid']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['field_event_department_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_event_department_tid']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'created' => 'created',
  );
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Posted';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = 'h6';
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  /* Field: Content: Event Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = 'Date';
  $handler->display->display_options['fields']['field_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_event_date']['element_type'] = 'strong';
  $handler->display->display_options['fields']['field_event_date']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_event_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_event_date']['field_api_classes'] = 0;
  $handler->display->display_options['path'] = 'events/upcoming';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['row_options']['hide_empty'] = 1;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Event Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = '';
  $handler->display->display_options['fields']['field_event_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_event_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_event_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_event_date']['element_type'] = 'em';
  $handler->display->display_options['fields']['field_event_date']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_event_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_event_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_event_date']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_event_date']['settings'] = array(
    'format_type' => 'no_year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_event_date']['field_api_classes'] = 0;
  $export['ds_upcoming_events'] = $view;

  $view = new view;
  $view->name = 'view_facilities';
  $view->description = 'View the taxonomy vocabulary Facilities.  ';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'View Facilities';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'View Facilities';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_facilityx_location' => 'field_facilityx_location',
    'field_facilityx_type' => 'field_facilityx_type',
    'description' => 'description',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_facilityx_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'field_facilityx_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'description' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Facility Name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = 1;
  /* Field: : field_facilityx_location */
  $handler->display->display_options['fields']['field_facilityx_location']['id'] = 'field_facilityx_location';
  $handler->display->display_options['fields']['field_facilityx_location']['table'] = 'field_data_field_facilityx_location';
  $handler->display->display_options['fields']['field_facilityx_location']['field'] = 'field_facilityx_location';
  $handler->display->display_options['fields']['field_facilityx_location']['label'] = 'Location';
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_facilityx_location']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_facilityx_location']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_facilityx_location']['type'] = 'location_all';
  $handler->display->display_options['fields']['field_facilityx_location']['field_api_classes'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_facilityx_type']['id'] = 'field_facilityx_type';
  $handler->display->display_options['fields']['field_facilityx_type']['table'] = 'field_data_field_facilityx_type';
  $handler->display->display_options['fields']['field_facilityx_type']['field'] = 'field_facilityx_type';
  $handler->display->display_options['fields']['field_facilityx_type']['label'] = 'Facility Type';
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_facilityx_type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_facilityx_type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_facilityx_type']['hide_alter_empty'] = 0;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['description']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['description']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['description']['alter']['external'] = 0;
  $handler->display->display_options['fields']['description']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['description']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['description']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['description']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['description']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['description']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['description']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['description']['alter']['html'] = 0;
  $handler->display->display_options['fields']['description']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['description']['hide_alter_empty'] = 0;
  /* Field: Taxonomy term: Image */
  $handler->display->display_options['fields']['field_facilityx_image']['id'] = 'field_facilityx_image';
  $handler->display->display_options['fields']['field_facilityx_image']['table'] = 'field_data_field_facilityx_image';
  $handler->display->display_options['fields']['field_facilityx_image']['field'] = 'field_facilityx_image';
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_facilityx_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_facilityx_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_facilityx_image']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_facilityx_image']['settings'] = array(
    'colorbox_node_style' => 'ds_thumbnail',
    'colorbox_image_style' => '',
  );
  $handler->display->display_options['fields']['field_facilityx_image']['group_column'] = 'fid';
  $handler->display->display_options['fields']['field_facilityx_image']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_facilityx_image']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_facilityx_image']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_facilityx_image']['separator'] = ' ';
  $handler->display->display_options['fields']['field_facilityx_image']['field_api_classes'] = 0;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'facilityx' => 'facilityx',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'view-facilities';
  $export['view_facilities'] = $view;

  return $export;
}
