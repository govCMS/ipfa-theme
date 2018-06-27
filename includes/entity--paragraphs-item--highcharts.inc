<?php
/**
 * @file
 * Theme and preprocess functions for highcharts paragraphs.
 */

/**
 * Implements hook_preprocess_entity_ENTITY_TYPE_BUNDLE().
 */
function ipfa_preprocess_entity_paragraphs_item_highcharts(&$variables) {

  $entity = $variables['elements']['#entity'];
  $entity_type = $variables['entity_type'];
  $lang = $variables['elements']['#language'];
  $para_id_class = $variables['para_id_class'];

  $highcarts_fields = array(
    'title' => 'field_highcharts_title',
    'subtitle' => 'field_highcharts_subtitle',
    'csv' => 'field_highcharts_csv',
    'y_axis' => 'field_highcharts_y_axis',
    'type' => 'field_highcharts_type',
  );

  // Get settings from highcharts fields.
  $field_values = array();
  foreach ($highcarts_fields as $key => $highcarts_field) {
    $field = field_get_items($entity_type, $entity, $highcarts_field);
    if ($field) {
      $field_values[$key] = $field[0]['value'];
    }
    else {
      $field_values[$key] = NULL;
    }
  }

  $settings = ipfa_highcharts_get_settings($field_values);

  // CSS selector that identifies the entity wrapper.
  $selector = '.' . $para_id_class . ' .field-name-field-highcharts-csv';

  // Add highcharts settings.
  $js_settings = array($selector => $settings);
  drupal_add_js(array('paragraph_highcharts' => $js_settings), 'setting');

  // Add highcharts library.
  drupal_add_js( drupal_get_path('theme', 'ipfa') . '/js/libraries/highcharts.min.js');

  // Add entity_background_parallax js.
  drupal_add_js(drupal_get_path('theme', 'ipfa') . '/js/paragraph_highcharts.js');

}

/*
 * Get settings required for a given chart type.
 *
 * @param string $type
 *  Chart type.
 *
 * @return array
 *  Array of settings.
 */
function ipfa_highcharts_type_settings($type = NULL) {

  $settings = array(
    'chart' => TRUE,
    'title' => TRUE,
    'subtitle' => TRUE,
    'xAxis' => TRUE,
    'yAxis' => TRUE,
    'series' => TRUE,
  );

  switch ($type) {
    case 'pie':
      $settings['xAxis'] = FALSE;
      $settings['yAxis'] = FALSE;
      break;
  }

  return $settings;

}

/*
 * Construct settings array.
 *
 * @param array $fields
 *  Field values.
 *
 * @return array
 *  Highcharts settings in array format.
 */
function ipfa_highcharts_get_settings($fields = array()) {

  $settings = ipfa_highcharts_type_settings($fields['type']);
  if (!$settings) {
    return FALSE;
  }

  $settings['chart'] = array(
    'type' => $fields['type'],
  );

  $settings['title'] = array(
    'text' => $fields['title'],
    'x' => -20
  );

  $settings['subtitle'] = array(
    'text' => $fields['subtitle'],
    'x' => -20
  );

  $settings['xAxis'] = ipfa_highcharts_get_x_axis($fields['csv'], $settings);

  $settings['yAxis'] = ipfa_highcharts_get_y_axis($fields['y_axis'], $settings);

  $settings['series'] = ipfa_highcharts_get_data_series($fields['csv'], $settings);

  return $settings;
}

/*
 * Get X-axis settings.
 *
 * @param string $csv
 *  Comma separated string.
 *
 * @param array $settings
 *  Highchart settings array.
 *
 * @return array
 *  X axis values in array format.
 */
function ipfa_highcharts_get_x_axis($csv = '', $settings = array()) {

  $x_axis = array('categories' => NULL);

  if (!$settings['xAxis']) {
    return $x_axis;
  }
  $lines = explode("\n", $csv);

  if ($lines) {
    $x_axis = str_getcsv($lines[0]);
    array_shift($x_axis);
    $x_axis['categories'] = $x_axis;
  }

  return $x_axis;
}

/*
 * Get Y-axis settings.
 *
 * @param string $title
 *  Y-axis title.
 *
 * @param array $settings
 *  Highchart settings array.
 *
 * @return array
 *  Y-axis settings in array format.
 */
function ipfa_highcharts_get_y_axis($title = '', $settings = array()) {

  if (!$settings['yAxis']) {
    $title = '';
  }
  return array(
    'title' => array(
      'text' => $title,
    ),
  );
}

/*
 * Get data series.
 *
 * @param string $csv
 *  Comma separated string.
 *
 * @param array $settings
 *  Highchart settings array.
 *
 * @return array
 *  Data series in array of objects.
 */
function ipfa_highcharts_get_data_series($csv = '', $settings = array()) {
  if ($settings['chart']['type'] == 'pie') {
    return ipfa_highcharts_get_data_series_pie($csv, $settings);
  }

  $series = array();

  $lines = explode("\n", $csv);

  array_shift($lines);

  foreach ($lines as $line) {
    $data = str_getcsv($line);
    $col_1 = array_shift($data);
    $data = array_map('intval', $data);
    $series[] = (object) array(
      'name' => $col_1,
      'data' => $data
    );
  }
  return $series;
}

/*
 * Get data series for pie chart.
 *
 * @param string $csv
 *  Comma separated string.
 *
 * @param array $settings
 *  Highchart settings array.
 *
 * @return array
 *  Data series in array of objects.
 */
function ipfa_highcharts_get_data_series_pie($csv = '', $settings = array()) {
  $values = array();

  $lines = explode("\n", $csv);

  $titles = array_shift($lines);
  $titles = str_getcsv($titles);

  $series = (object) array(
    'name' => $titles[0],
    'colorByPoint' => TRUE,
  );

  foreach ($lines as $line) {
    list($name, $y) = str_getcsv($line);
    $data['name'] = $name;
    $data['y'] = intval($y);
    $values[] = $data;
  }

  $series->data = $values;
  return array($series);
}
