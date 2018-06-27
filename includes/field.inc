<?php
/**
 * @file
 * Theme and preprocess functions for fields.
 */

/**
 * Implements hook_preprocess_field().
 */
function ipfa_preprocess_field(&$variables, $hook) {

  $field_name = $variables['element']['#field_name'];

  // Paragraph title.
  if ($field_name == "field_para_title") {
    $items = $variables['items'];
    foreach ($items as $key => $item) {
      $html_tag = array(
        '#tag' => 'h2',
        '#value' => $item['#markup'],
      );
      $item['#markup'] = theme('html_tag', array('element' => $html_tag));
      $items[$key] = $item;
    }
    $variables['items'] = $items;
  }

}
