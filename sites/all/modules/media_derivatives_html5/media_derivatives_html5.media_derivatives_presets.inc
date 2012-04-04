<?php
/**
 * @file
 * media_derivatives_html5.media_derivatives_presets.inc
 */

/**
 * Implementation of hook_media_derivatives_presets().
 */
function media_derivatives_html5_media_derivatives_presets() {
  $export = array();

  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->machine_name = 'html5_h264';
  $preset->engine = 'media_ffmpeg_simple';
  $preset->engine_settings = array(
    'ffmpeg_options' => '',
    'ffmpeg_out_options' => '-vcodec libx264 -vpre ipod640 -b 250k -bt 50k -acodec libfaac -ab 56k -ac 2 -s 480x320 -threads 0',
    'ffmpeg_extension' => 'mp4',
  );
  $preset->conditions = array(
    0 => 'file_type',
    1 => 'derivatives_of_derivatives',
  );
  $preset->conditions_settings = array(
    'type' => 'video',
    'encode_derivatives' => 0,
  );
  $preset->events = array(
    0 => 'file_insert',
  );
  $preset->events_settings = array();
  $preset->scheduler = 'scheduler_immediate';
  $preset->scheduler_settings = array();
  $preset->settings = array(
    'recursive_delete' => 1,
    'delete_source' => 0,
    'user' => '0',
    'type' => 0,
  );
  $export['html5_h264'] = $preset;

  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->machine_name = 'html5_ogg';
  $preset->engine = 'media_ffmpeg_simple';
  $preset->engine_settings = array(
    'ffmpeg_options' => '',
    'ffmpeg_out_options' => '-f ogg -vcodec libtheora -b 800k -g 300 -acodec libvorbis -ab 128k',
    'ffmpeg_extension' => 'ogv',
  );
  $preset->conditions = array(
    0 => 'file_type',
    1 => 'derivatives_of_derivatives',
  );
  $preset->conditions_settings = array(
    'type' => 'video',
    'encode_derivatives' => 0,
  );
  $preset->events = array(
    0 => 'file_insert',
  );
  $preset->events_settings = array();
  $preset->scheduler = 'scheduler_immediate';
  $preset->scheduler_settings = array();
  $preset->settings = array(
    'recursive_delete' => 1,
    'delete_source' => 0,
    'user' => '0',
    'type' => 0,
  );
  $export['html5_ogg'] = $preset;

  return $export;
}
