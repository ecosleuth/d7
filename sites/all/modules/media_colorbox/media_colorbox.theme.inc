<?php
/**
 * @file
 * Media Colorbox theme functions.
 */

/**
 * Returns HTML for a Media Colorbox file field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: A build array.
 *   - entity_id: The entity ID.
 *   - field: The field data.
 *   - display_settings: The display settings.
 *   - langcode: The language code.
 *   - path: The path to the content.
 *   - title: The title of the content.
 *
 * @ingroup themeable
 */
function theme_media_colorbox($variables) {
  $entity_id = $variables['entity_id'];
  $field = $variables['field'];
  $field_name = isset($field['field_name']) ? $field['field_name'] : '';
  $settings = $variables['display_settings'];

 //switch to figure out where caption should come from
  switch ($settings['colorbox_caption']) {
    case 'title':
      $caption = $variables['title'];
      break;
    case 'mediafield':
      $caption = $variables['media_colorbox_caption'];
      break;
    default:
      $caption = '';
  }

  // Shorten the caption for the example styles or when caption shortening is active.
  $colorbox_style = variable_get('colorbox_style', 'default');
  $trim_length = variable_get('colorbox_caption_trim_length', 75);
  if ((variable_get('colorbox_caption_trim', 0)) && (drupal_strlen($caption) > $trim_length)) {
    $caption = drupal_substr($caption, 0, $trim_length - 5) . '...';
  }

  // Build the gallery id.
  switch ($settings['colorbox_gallery']) {
    case 'post':
      $gallery_id = 'gallery-' . $entity_id;
      break;
    case 'page':
      $gallery_id = 'gallery-all';
      break;
    case 'field_post':
      $gallery_id = 'gallery-' . $entity_id . '-' . $field_name;
      break;
    case 'field_page':
      $gallery_id = 'gallery-' . $field_name;
      break;
    case 'custom':
      $gallery_id = $settings['colorbox_gallery_custom'];
      break;
    default:
      $gallery_id = '';
  }

  $dimensions = explode('x', $settings['dimensions']);
  $initialWidth = $dimensions[0];
  $initialHeight = $dimensions[1];
  $output = theme('link', array(
    'text' => drupal_render($variables['item']),
    'path' => $variables['path'],
    'options' => array(
      'html' => TRUE,
      'attributes' => array(
        'title' => $caption,
        'class' => 'media-colorbox ' . $variables['item_class'],
        'style' => $variables['item_style'],
        'rel' => $gallery_id,
        'data-mediaColorboxInitialWidth' => $initialWidth,
        'data-mediaColorboxInitialHeight' => $initialHeight,
      ),
    ),
  ));
  return $output;
}
