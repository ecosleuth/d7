<?php
/**
 * @file
 * dairy_specialists_2.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function dairy_specialists_2_user_default_roles() {
  $roles = array();

  // Exported role: Administrator
  $roles['Administrator'] = array(
    'name' => 'Administrator',
    'weight' => '2',
  );

  // Exported role: Competitor
  $roles['Competitor'] = array(
    'name' => 'Competitor',
    'weight' => '7',
  );

  // Exported role: Consultants
  $roles['Consultants'] = array(
    'name' => 'Consultants',
    'weight' => '8',
  );

  // Exported role: Customer
  $roles['Customer'] = array(
    'name' => 'Customer',
    'weight' => '4',
  );

  // Exported role: Editor
  $roles['Editor'] = array(
    'name' => 'Editor',
    'weight' => '3',
  );

  // Exported role: Employee
  $roles['Employee'] = array(
    'name' => 'Employee',
    'weight' => '5',
  );

  // Exported role: Government
  $roles['Government'] = array(
    'name' => 'Government',
    'weight' => '9',
  );

  // Exported role: Vendor
  $roles['Vendor'] = array(
    'name' => 'Vendor',
    'weight' => '6',
  );

  return $roles;
}
