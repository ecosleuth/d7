<?php
/**
 * @file
 * media_derivatives_html5.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function media_derivatives_html5_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "media_derivatives" && $api == "media_derivatives_presets") {
    return array("version" => "1");
  }
}
