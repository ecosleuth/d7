<?php
/**
 * @file
 * dairy_specialists_2.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function dairy_specialists_2_taxonomy_default_vocabularies() {
  return array(
    'departments' => array(
      'name' => 'Departments',
      'machine_name' => 'departments',
      'description' => 'Departments or divisions within Dairy Specialists',
      'hierarchy' => '1',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'facility_type' => array(
      'name' => 'Facility Type',
      'machine_name' => 'facility_type',
      'description' => 'A type of facility - Dairy, Vendor, Office, Competitor, Special Event, etc.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'forums' => array(
      'name' => 'Forums',
      'machine_name' => 'forums',
      'description' => 'Forum navigation vocabulary',
      'hierarchy' => '1',
      'module' => 'forum',
      'weight' => '-10',
    ),
    'media_content' => array(
      'name' => 'Media Content',
      'machine_name' => 'media_content',
      'description' => 'Purpose: Image, Video, Document - of a Person (employee, customer), Vehicle, Product, Blueprint, Event, Equipment, Facility, etc',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'media_folders' => array(
      'name' => 'Media Folders',
      'machine_name' => 'media_folders',
      'description' => 'Use media folders to organize your media',
      'hierarchy' => '1',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
