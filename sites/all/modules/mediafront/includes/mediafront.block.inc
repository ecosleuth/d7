<?php
/**
 * Implementation of hook_block_info
 */
function mediafront_block_info() {

  // Define the media player block.
  $blocks['mediaplayer'] = array(
    'info' => t('Media Player')
  );

  // Return the blocks.
  return $blocks;
}

/**
 * Implementation of hook_block_configure
 */
function mediafront_block_configure($delta = '') {
  $form = array();
  if ($delta == 'mediaplayer') {
    $form['mediafront'] = array(
      '#type' => 'fieldset',
      '#title' => 'MediaFront Settings',
      '#description' => 'This is a special media player block that will allow you to place a media player preset within any block region on your website.  In addition, you can link to any view within that page to act as the playlist for this media player.'
    );

    $form['mediafront']['mediafront_block_preset'] = mediafront_preset_select_form(array('mediafront_preset' => variable_get('mediafront_block_preset', '')));

    // Get a list of all views
    $views = views_get_enabled_views();
    $options = array('' => 'none');
    foreach ($views as $view) {
      $options[$view->name] = $view->name;
    }

    // Link this block to a view display.
    $form['mediafront']['mediafront_block_playlist'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#title' => 'Link to View',
      '#description' => 'Select the view you would like to link to this media player.  This view must be on the same page as this player to be linked, and must include a visible Content Id (node Id) within the fields of the view display to work as expected.',
      '#options' => $options,
      '#default_value' => variable_get('mediafront_block_playlist', '')
    );

    // Link this block to a view display.
    $form['mediafront']['mediafront_block_playlist_exclude'] = array(
      '#type' => 'textarea',
      '#title' => 'Exclude View Display',
      '#description' => 'Provide any displays you would like to exclude from the selected view above.',
      '#default_value' => implode("\n", variable_get('mediafront_block_playlist_exclude', array()))
    );
  }
  return $form;
}

/**
 * Implementation of hook_block_save
 */
function mediafront_block_save($delta = '', $edit = array()) {
  if ($delta == 'mediaplayer') {
    variable_set('mediafront_block_preset', $edit['mediafront_block_preset']);
    variable_set('mediafront_block_playlist', $edit['mediafront_block_playlist']);
    $exclude = preg_split("/[\r\n]+/", $edit['mediafront_block_playlist_exclude']);
    $exclude = array_map(create_function('$item', 'return trim($item);'), array_filter($exclude));
    variable_set('mediafront_block_playlist_exclude', $exclude);
  }
}

/**
 * Implementation of hook_block_view
 */
function mediafront_block_view($delta = '') {
  $block = array();
  if ($delta == 'mediaplayer') {
    $block['subject'] = t('Media Player');
    $block['content'] = mediafront_block_content();
  }
  return $block;
}

/**
 * Content for the media player block.
 */
function mediafront_block_content() {
  $preset = variable_get('mediafront_block_preset', '');
  return $preset ? mediafront_get_player($preset) : '';
}


/**
 * Determine if we should show the views block.
 *
 * @param type $view
 * @return type
 */
function mediafront_block_show($view) {
  $exclude = variable_get('mediafront_block_playlist_exclude', array());
  $playlists = variable_get('mediafront_block_playlist', '');
  $enabled = is_array($playlists) ? isset($playlists[$view->name]) : ($playlists == $view->name);
  return $enabled && !in_array($view->current_display, $exclude);
}
