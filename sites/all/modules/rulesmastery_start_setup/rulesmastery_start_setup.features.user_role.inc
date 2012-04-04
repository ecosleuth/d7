<?php
/**
 * @file
 * rulesmastery_start_setup.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function rulesmastery_start_setup_user_default_roles() {
  $roles = array();

  // Exported role: level 1
  $roles['level 1'] = array(
    'name' => 'level 1',
    'weight' => '4',
  );

  // Exported role: level 2
  $roles['level 2'] = array(
    'name' => 'level 2',
    'weight' => '5',
  );

  // Exported role: level 3
  $roles['level 3'] = array(
    'name' => 'level 3',
    'weight' => '6',
  );

  // Exported role: level 4
  $roles['level 4'] = array(
    'name' => 'level 4',
    'weight' => '7',
  );

  // Exported role: level 5
  $roles['level 5'] = array(
    'name' => 'level 5',
    'weight' => '8',
  );

  // Exported role: level 6
  $roles['level 6'] = array(
    'name' => 'level 6',
    'weight' => '9',
  );

  // Exported role: level 7
  $roles['level 7'] = array(
    'name' => 'level 7',
    'weight' => '10',
  );

  return $roles;
}
