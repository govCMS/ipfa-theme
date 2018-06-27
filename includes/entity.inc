<?php
/**
 * @file
 * Theme and preprocess functions for entities.
 */

require_once dirname(__FILE__) . '/entity--paragraphs-item.inc';

/**
 * Implements hook_preprocess_entity().
 */
function ipfa_preprocess_entity(&$variables) {

  // Set up preprocess functions for each entity type.
  $entity_type = $variables['entity_type'];

  $function = __FUNCTION__ . '_' . $entity_type;
  if (function_exists($function)) {
    $function($variables);
  }
}
