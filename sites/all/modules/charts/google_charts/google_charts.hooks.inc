<?php
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Use Google Charts on your site.
 *
 * @note only hooks are here.
 */

/**
 * Implementation of hook_charts_info().
 *
 * Its a Charts module hook. It defines almost all aspects
 * of a chart provider, like its name, what types of charts
 * it can perform and what are the restrictions.
 */
function google_charts_charts_info() {
  return array(
    'google' => array(
      'file'    => drupal_get_path('module', 'google_charts') . '/google_charts.inc',
      'name'    => t('Google Chart'),
      'render'  => '_google_charts_render',
      'types'   => array('line2D', 'hbar2D', 'vbar2D', 'pie2D', 'pie3D', 'venn', 'scatter'),
    ),
  );
}

/**
 * Implementation of hook_chart_types().
 */
function google_charts_chart_types() {
  return array(
    'venn'    => t('Venn'),
    'scatter' => t('Scatter Plot'),
  );
}
