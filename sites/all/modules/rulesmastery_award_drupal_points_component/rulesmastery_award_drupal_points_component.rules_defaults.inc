<?php
/**
 * @file
 * rulesmastery_award_drupal_points_component.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rulesmastery_award_drupal_points_component_default_rules_configuration() {
  $items = array();
  $items['rules_award_drupal_points'] = entity_import('rules_config', '{ "rules_award_drupal_points" : {
      "LABEL" : "Award Drupal points",
      "PLUGIN" : "rule set",
      "TAGS" : [ "Drupal points" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "account" : { "label" : "Account to award", "type" : "user" },
        "points" : { "label" : "Number of points", "type" : "integer" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "result" : { "points_new" : "Updated points" } },
            "DO" : [
              { "data_calc" : {
                  "USING" : {
                    "input_1" : [ "account:field-user-drupalpoints" ],
                    "op" : "+",
                    "input_2" : [ "points" ]
                  },
                  "PROVIDE" : { "result" : { "points_new" : "Updated points" } }
                }
              },
              { "data_set" : {
                  "data" : [ "account:field-user-drupalpoints" ],
                  "value" : [ "points-new" ]
                }
              },
              { "drupal_message" : { "message" : "The user [account:name] now has [account:field-user-drupalpoints] Drupal points!" } }
            ],
            "LABEL" : "Award Drupal points"
          }
        }
      ]
    }
  }');
  return $items;
}
