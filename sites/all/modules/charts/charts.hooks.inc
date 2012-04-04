<?php
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Transform DATA into INFORMATION using beautiful CHARTS.
 *
 * @note only cachable hooks are here.
 */

/**
 * Implementation of hook_chart_types().
 */
function charts_chart_types() {
  return array(
    'line2D'  => t('Line 2D'),
    'hbar2D'  => t('Horizontal Bar 2D'),
    'vbar2D'  => t('Vertical Bar 2D'),
    'pie2D'   => t('Pie 2D'),
    'pie3D'   => t('Pie 3D'),
  );
}

/**
 * Implementation of hook_menu().
 */
function charts_menu() {
  $items['admin/settings/charts'] = array(
    'access arguments'  => array('set default settings for charts'),
    'description'     => 'Set the default behaviour and look of all your charts',
    'page callback'   => 'drupal_get_form',
    'page arguments'  => array('_charts_settings_page'),
    'title'           => 'Charts'
  );
  return $items;
}

/**
 * Implementation of hook_perm().
 */
function charts_perm() {
  return array('set default settings for charts');
}

/**
 * Implementation of hook_theme().
 */
function charts_theme() {
  return array(
    'charts_settings_color' => array(
      'arguments' => array('form' => NULL),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function charts_views_api() {
  return array(
    'api' => 2,
    'path' => drupal_get_path('module', 'charts') . '/views',
  );
}
