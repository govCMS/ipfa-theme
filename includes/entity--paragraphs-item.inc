<?php
/**
* @file
* Theme and preprocess functions for paragraphs entity.
*/

/**
 * Implements hook_preprocess_entity_ENTITY_TYPE().
 */
function ipfa_preprocess_entity_paragraphs_item(&$variables) {

  $entity = $variables['elements']['#entity'];
  $entity_type = $variables['entity_type'];
  $bundle = $variables['elements']['#bundle'];
  $lang = $variables['elements']['#language'];

  // Paragraph item id class.
  $para_id_class = 'paragraphs-item-' . $entity->item_id;
  $variables['classes_array'][] = drupal_html_class($para_id_class);
  $variables['para_id_class'] = $para_id_class;

  // Paragraph classes.
  $classes = field_get_items($entity_type, $entity, 'field_para_class');
  if ($classes) {
    foreach ($classes as $class) {
      $variables['classes_array'][] = drupal_html_class('cp-' . $class['value']);
    }
  }

  // Breakout.
  $breakout = field_get_items($entity_type, $entity, 'field_para_breakout');
  if ($breakout && $breakout[0]['value']) {
    $variables['classes_array'][] = drupal_html_class('paragraph-breakout');
  }

  // Background color.
  // Adding CSS into the HTML head.
  $bg_color = field_get_items($entity_type, $entity, 'field_para_bg_color');
  if ($bg_color) {

    // Add class.
    $variables['classes_array'][] = 'eb-color';

    $selector = '.'.$para_id_class;
    drupal_add_css($selector . ' {background-color: ' . $bg_color[0]['value'] . ';}', 'inline');
  }

  // Background image.
  // Adding CSS into the HTML head.
  $bg_image = field_get_items($entity_type, $entity, 'field_para_bg_image');
  if ($bg_image) {
    // Background image url.
    $url = file_create_url($bg_image[0]['uri']);

    // Add class.
    $variables['classes_array'][] = 'eb-image';

    // CSS selector that identifies the entity wrapper.
    $selector = '.' . $para_id_class;
    drupal_add_css($selector . ' {background-image: url(' . $url . ');}', 'inline');

    // Add background style class.
    $bg_image_style = field_get_items($entity_type, $entity, 'field_para_bg_image_style');
    if ($bg_image_style) {
      $style_class = 'eb-image-' . drupal_clean_css_identifier($bg_image_style[0]['value']);
      $variables['classes_array'][] = drupal_html_class($style_class);
    }
  }

  // Background parallax.
  $parallax_image = field_get_items($entity_type, $entity, 'field_para_parallax_image');
  if ($parallax_image) {
    $image_url = file_create_url($parallax_image[0]['uri']);

    // Build options.
    $options = array(
      'imageSrc' => $image_url,
    );
    // Add speed if present.
    $speed = field_get_items($entity_type, $entity, 'field_para_parallax_speed');
    if ($speed) {
      $options['speed'] = $speed[0]['value'];
    }

    // CSS selector that identifies the entity wrapper.
    $selector = '.' . $para_id_class;

    // Add parallax settings.
    $js_settings = array($selector => $options);
    drupal_add_js(array('entity_background_parallax' => $js_settings), 'setting');

    // Add parallax library.
    drupal_add_js(drupal_get_path('theme', 'ipfa').'/js/parallax/parallax.js');

    // Add entity_background_parallax js.
    drupal_add_js(drupal_get_path('theme', 'ipfa').'/js/entity_background_parallax.js');

  }
  // Set entity preprocess functions for each bundle.
  $file = dirname(__FILE__) . '/entity';
  $file .= '--' . drupal_clean_css_identifier($entity_type);
  $file .= '--' . drupal_clean_css_identifier($bundle) . '.inc';
  if (file_exists($file)){
    require_once $file;
  }

  // Preprocess functions.
  $function = __FUNCTION__ . '_' . $bundle;
  if (function_exists($function)) {
    $function($variables);
  }

}

/**
 * Implements hook_field_display_ENTITY_TYPE_alter().
 *
 */
function ipfa_field_display_paragraphs_item_alter(&$display, $context) {

  // Render node and bean list entities in the selected value in field view mode.
  $field_name = $context['instance']['field_name'];
  if ($field_name == 'field_para_items_node' || $field_name == 'field_para_items_bean') {
    $entity = $context['entity'];
    $entity_type = $context['entity_type'];

    $view_mode = field_get_items($entity_type, $entity, 'field_para_view_mode');
    $display['settings']['view_mode'] = $view_mode[0]['value'];
  }

}
