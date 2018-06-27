<?php
/**
 * @file
 * Theme and preprocess functions for highcharts paragraphs.
 */

/**
 * Implements hook_preprocess_entity_ENTITY_TYPE_BUNDLE().
 */
function ipfa_preprocess_entity_paragraphs_item_slideshow(&$variables) {

  $entity = $variables['elements']['#entity'];
  $entity_type = $variables['entity_type'];
  $lang = $variables['elements']['#language'];
  $para_id_class = $variables['para_id_class'];

  // CSS selector that identifies the entity wrapper.
  $selector = '.' . $para_id_class;
  $options = array();

  // Add slideshow settings.
  $js_settings = array($selector => $options);
  drupal_add_js(array('paragraph_slideshow' => $js_settings), 'setting');

  // Add paragraph_slideshow js.
  drupal_add_js(drupal_get_path('theme', 'ipfa').'/js/paragraph_slideshow.js');

}
