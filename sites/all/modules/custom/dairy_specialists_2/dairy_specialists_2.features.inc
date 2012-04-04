<?php
/**
 * @file
 * dairy_specialists_2.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dairy_specialists_2_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function dairy_specialists_2_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implements hook_node_info().
 */
function dairy_specialists_2_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('A date content type that is linked to a Views calendar.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'facility' => array(
      'name' => t('Facility'),
      'base' => 'node_content',
      'description' => t('A Facility or Location.  (Location is more general but is already in use in Drupal)

A Facility such as a Dairy, Vendor Site, Office or Shop, Special Event - Ptarmigan, Farm Show
Or the destination of a trip.'),
      'has_title' => '1',
      'title_label' => t('Facility/Location Name'),
      'help' => t('Enter any location - a dairy, office, shop, warehouse, location of a special event, vendor site, competitor site, etc.'),
    ),
    'menu_pane' => array(
      'name' => t('Menu Pane'),
      'base' => 'node_content',
      'description' => t('Contains the HTML text to create the menu panes in the Main Mucho Menu'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('The body is the only field of interest.
The html is displayed in the menu panes - it contains imbedded links
that constitute the menu selections.
The title and author are not displayed in the menu pane.
'),
    ),
  );
  return $items;
}

/**
 * Implements hook_default_profile2_type().
 */
function dairy_specialists_2_default_profile2_type() {
  $items = array();
  $items['family'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "family",
    "label" : "Family",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 0 }
  }');
  $items['interests'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "interests",
    "label" : "Interests",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 0 }
  }');
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : 1, "use_page" : 0 }
  }');
  $items['work_experience'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "work_experience",
    "label" : "Work Experience",
    "weight" : "0",
    "data" : { "registration" : 0, "use_page" : 0 }
  }');
  return $items;
}
