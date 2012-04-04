<?php
/**
 * @file
 * rulesmastery_level_up.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rulesmastery_level_up_default_rules_configuration() {
  $items = array();
  $items['rules_actions_on_account_update'] = entity_import('rules_config', '{ "rules_actions_on_account_update" : {
      "LABEL" : "Actions on account update",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Drupal points" ],
      "REQUIRES" : [ "rulesmastery_start_setup", "rules" ],
      "ON" : [ "user_presave" ],
      "DO" : [
        { "rulesmastery_load_levels" : { "PROVIDE" : { "level_config" : { "level_config" : "Drupal point levels" } } } },
        { "LOOP" : {
            "USING" : { "list" : [ "level-config" ] },
            "ITEM" : { "level" : "Current level" },
            "DO" : [
              { "component_rules_check_for_level_up" : {
                  "account_unsaved" : [ "account-unchanged" ],
                  "account_updated" : [ "account" ],
                  "limit" : [ "level:limit" ],
                  "roles" : [ "level:role" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_check_for_level_up'] = entity_import('rules_config', '{ "rules_check_for_level_up" : {
      "LABEL" : "Check for level up",
      "PLUGIN" : "rule",
      "TAGS" : [ "Drupal points" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "account_unsaved" : { "label" : "Unsaved account", "type" : "user" },
        "account_updated" : { "label" : "Updated account", "type" : "user" },
        "limit" : { "label" : "Point limit", "type" : "integer" },
        "roles" : { "label" : "Roles to add", "type" : "list\\u003Cinteger\\u003E" }
      },
      "IF" : [
        { "data_is" : {
            "data" : [ "account-updated:field-user-drupalpoints" ],
            "op" : "\\u003E",
            "value" : { "select" : "limit", "num_offset" : { "value" : "-1" } }
          }
        },
        { "data_is" : {
            "data" : [ "account-unsaved:field-user-drupalpoints" ],
            "op" : "\\u003C",
            "value" : [ "limit" ]
          }
        }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account-updated" ], "roles" : [ "roles" ] } }
      ]
    }
  }');
  return $items;
}
