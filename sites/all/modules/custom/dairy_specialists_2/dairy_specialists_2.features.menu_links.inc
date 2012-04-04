<?php
/**
 * @file
 * dairy_specialists_2.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function dairy_specialists_2_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: main-menu:calendar-event_date
  $menu_links['main-menu:calendar-event_date'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'calendar-event_date',
    'router_path' => 'calendar-event_date',
    'link_title' => 'Events Calendar',
    'options' => array(
      'attributes' => array(
        'title' => 'Calendar of events',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Events Calendar');
  t('Home');


  return $menu_links;
}
