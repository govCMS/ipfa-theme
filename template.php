<?php

/**
 * @file
 * Template file for ipfa zen.
 */

require_once dirname(__FILE__) . '/includes/entity.inc';
require_once dirname(__FILE__) . '/includes/field.inc';

/**
 * Implements template_preprocess_html().
 */
function ipfa_preprocess_html(&$vars) {

  /* Adds HTML5 placeholder shim */
  drupal_add_js(libraries_get_path('html5placeholder') . "/jquery.placeholder.js", 'file');
}

/**
 * Implements hook_form_alter().
 */
function ipfa_form_alter(&$form, &$form_state, $form_id) {

  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = 'Enter keywords...';
  }
}

/**
 * Implements hook_preprocess_page().
 */
function ipfa_preprocess_page(&$variables) {
}

/**
 * Implements hook_preprocess_region().
 */
function ipfa_preprocess_region(&$variables) {

}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function ipfa_preprocess_maintenance_page(&$variables) {

  $t_function = get_t();

  if (drupal_installation_attempted()) {
    $variables['logo'] = base_path() . drupal_get_path('theme', 'ipfa') . '/logo.png';
    // Override the site name, which will be "Drupal".
    // @todo: Dynamically rename "ipfa" using $conf.
    $variables['site_name'] = $t_function('Install ipfa');
    // @todo: Use this to style the installer appropriately.
    $variables['classes_array'][] = 'installer';
  }
  else {
    if (empty($variables['content'])) {
      $variables['content'] = $t_function('This web site is currently undergoing some maintenance and is unavailable.');
    }
  }
}

/**
 * Implements hook_preprocess_node().
 */
function ipfa_preprocess_node(&$variables) {

  // Slides get a special read more link.
  if ($variables['type'] == 'slide') {
    if (!empty($variables['field_read_more'][0]['url'])) {
      $variables['title_link'] = l($variables['title'], $variables['field_read_more'][0]['url']);
    }
    else {
      $variables['title_link'] = check_plain($variables['title']);
    }
  }
}

/**
 * Implements hook_process_node().
 */
function ipfa_process_node(&$variables) {

  // We only want to set these if Display Suite HASN'T already been used.
  // This allows us to control the defaults but let end-users override with
  // DS wherever necessary.
  // This happens in _process_node(), as DS doesn't do its thing till AFTER
  // _preprocess_node() has run.
  if (!isset($variables['rendered_by_ds']) || $variables['rendered_by_ds'] != TRUE) {

    // The ipfa node template includes a dynamic title tag. This defaults to
    // h2, if not set elsewhere.
    if (!isset($variables['title_tag']) || empty($variables['title_tag'])) {
      $variables['title_tag'] = 'h2';
    }

    if (isset($variables['view_mode'])) {

      // Compact view modes are intended to be embedded in views.
      if ($variables['view_mode'] == 'compact') {
        _ipfa_process_node_compact($variables);
      }

      // Limit image fields to 1 item only in teaser and compact modes.
      if ($variables['view_mode'] == 'compact' || $variables['view_mode'] == 'teaser') {
        _ipfa_process_node_compact_teaser($variables);
      }
    }
  }
}

/**
 * Private callback to process compact node view modes.
 *
 * @param array $variables
 *   Standard variables array
 */
function _ipfa_process_node_compact(&$variables) {
  // Compact items are wrapped in an h3, as there is usually an h2
  // preceding them (the view or pane title).
  $variables['title_tag'] = 'h3';
}

/**
 * Private callback to process compact and teaser node view modes.
 *
 * @param array $variables
 *   Standard variables array
 */
function _ipfa_process_node_compact_teaser(&$variables) {
  $fields = field_read_fields(array('entity_type' => 'node', 'bundle' => $variables['type']));
  foreach ($fields as $field_name => $field_settings) {
    if ($field_settings['type'] == 'image') {
      if (isset($variables['content'][$field_name])) {
        $children = element_children($variables['content'][$field_name]);
        if (!empty($children)) {
          $limited = $variables['content'][$field_name][0];
          foreach ($children as $child_index) {
            unset ($variables['content'][$field_name][$child_index]);
          }
          $variables['content'][$field_name][0] = $limited;
        }
      }
    }
  }

}


/**
 * Overrides zen_status_messages to fix a small bug with output.
 *
 * @deprecated
 *
 * @todo: This can be removed when http://drupal.org/node/2344165 is fixed.
 */
function ipfa_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"messages--$type messages $type\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul class=\"messages__list\">\n";
      foreach ($messages as $message) {

        // Fix is for this line only.
        $output .= '  <li class="messages__item">' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implements theme_form_required_marker().
 */
function ipfa_form_required_marker($variables) {
  // This is also used in the installer, pre-database setup.
  $t_function = get_t();
  $attributes = array(
    'class' => 'form-required',
    'title' => $t_function('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '>(' . $t_function('mandatory') . ')</span>';
}

/**
 * Adds accessibility attributes.
 */
function ipfa_preprocess_aria_invalid(&$variables) {
  if (!empty($variables['element']['#required'])) {
    $variables['element']['#attributes']['required'] = 'true';
  }
  if (isset($variables['element']['#parents']) && form_get_error($variables['element']) !== NULL && !empty($variables['element']['#validated'])) {
    $variables['element']['#attributes']['aria-invalid'] = 'true';
  }
}

/**
 * Implements hook_theme_registry_alter().
 */
function ipfa_theme_registry_alter(&$theme_registry) {

  // Add our accessibility preprocess to several theme functions.
  $theme_functions = array(
    'textfield',
    'password',
    'file',
    'textarea',
    'checkbox',
    'radio',
    'select',
    'emailfield',
    'numberfield',
    'rangefield',
    'searchfield',
    'telfield',
    'urlfield',
  );

  foreach ($theme_functions as $hook) {
    $theme_registry[$hook]['preprocess functions'][] = 'ipfa_preprocess_aria_invalid';
  }
}

function ipfa_js_alter(&$javascript) {
  // Swap out jQuery to use an updated version of the library.
  $javascript['misc/jquery.js']['data'] = 'http://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js';
}

