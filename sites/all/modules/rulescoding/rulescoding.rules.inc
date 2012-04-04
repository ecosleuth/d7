<?php

/**
 * @file
 * Functions loaded only on page loads where Rules is used.
 */


/**
 * Implement hook_rules_conditions_info
 */

function rulescoding_rules_condition_info() {
   $condition = array(
      'rulescoding_codition_any_word_in_text' => array(
          'label' => t('Any of words exists in long text'),
          'parameter' => array(
             'list_of_words' => array(
                'type' => 'list<text>',
                'label' => t('List of words to search for'),
             ),
             'haystack' => array(
                'type' => 'text',
                'label' => t('Text to search in'),
             ),
          ),
          'group' => t('Rules coding'),
       ),
   );
      
   return $condition;
}
 
/**
 * Condition callback to check if any of listed words appear in a long text.
 */

function rulescoding_codition_any_word_in_text($list_of_words, $haystack) {
// Search for the listed words, one by one.
   foreach ($list_of_words as $word) {
      if (stristr($haystack, $word)) {
         return TRUE;
      }
   }
                                 
// If we got this far, none of the listed words are present in the long text.
   return FALSE;
}


function rulescoding_rules_action_info() {
   $actions = array(
      'rulescoding_action_replace_words' => array(
         'label' => t('Replace all occurances of listed words'),
         'group' => t('Rules coding'),
         'parameter' => array(
            'word_list' => array(
               'type' => 'list<text>',
               'label' => t('Words to replace'),
            ),
            'replacement' => array(
               'type' => 'text',
               'label' => t('Text to replace with'),
            ),
            'long_text' => array(
               'type' => 'text',
               'label' => t('Text to do replacements in'),
            ),
         ),
         'provides' => array(
            'updated_text' => array(
               'type' => 'text',
               'label' => t('Updated text'),
            ),
         ),
      ),
   );
      
   return $actions;
}

/**
 * Action callback for replacing all occurances of certain words.
 */
function rulescoding_action_replace_words($words, $replacement, $haystack) {
   // For each word in the list, change all occurances to the replacement string.
   foreach ($words as $needle) {
      $haystack = str_replace($needle, $replacement, $haystack);
   }
                 
   return array(
      'updated_text' => $haystack,
   );
}


function rulescoding_rules_event_info() {
   $events = array(
      'rulescoding_event_save_words' => array(
         'label' => t('List of words is being saved'),
         'group' => t('Rules coding'),
         'variables' => array(
            'list_unchanged' => array(
               'type' => 'list<text>',
               'label' => t('Unsaved list'),
            ),
            'list_updated' => array(
               'type' => 'list<text>',
               'label' => t('Updated list'),
            ),
         ),
      ),
   );
   
   return $events;
}



