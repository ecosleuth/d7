<?php
/**
 * Implements hook_field_formatter_info().
 */
function pdf_field_formatter_info() {
  return array(
    'pdf_default' => array(
      'label' => t('PDF default'),
      'field types' => array('file', 'pdf'),
    ),
    'pdf_thumbnail' => array(
      'label' => t('PDF first page'),
      'field types' => array('file', 'pdf'),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function pdf_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'pdf_default':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'pdf_formatter_default',
          '#file' => $item,
        );
      }
      break;
    case 'pdf_thumbnail':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'pdf_formatter_thumbnail',
          '#file' => $item,
        );
      }
      break;
  }
  return $element;
}

function theme_pdf_formatter_default($variables) {
  $file_url = url('/file/' . $variables['file']['fid']);

  $content = '<iframe name="pdf-reader" id="pdf-reader" frameborder="no" width="99%" height="600px" src="';
  $content .=  $file_url . '/fullscreen';
  $content .= '"></iframe>';
  return $content;
}

function theme_pdf_formatter_thumbnail($variables) {
  global $base_url;
  drupal_add_js('sites/all/libraries/pdf.js/build/pdf.js');
  $file = file_create_url($variables['file']['uri']);

  $worker_loader = url('pdf/worker_loader.js');
  $js = "PDFJS.workerSrc = '$worker_loader';";

  $js .= "'use strict';
    PDFJS.getPdf('$file', function getPdfHelloWorld(data) {
    var pdf = new PDFJS.PDFDoc(data);
    var page = pdf.getPage(1);
    var scale = 1.5;
    var canvas = document.getElementById('pdf');
    var context = canvas.getContext('2d');
    canvas.height = page.height * scale;
    canvas.width = page.width * scale;
    page.startRendering(context);});";

  drupal_add_js($js, array('type' => 'inline'));
  $output = '<canvas id="pdf" style="border:1px solid black;"/>';
  return $output;
}

