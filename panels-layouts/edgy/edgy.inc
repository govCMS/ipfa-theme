<?php
/**
 * @file
 * Defines the edgy layout
 *
 */

/**
 * Implementation of hook_panels_layouts().
 */
$plugin = array(
  'title' => t('Edgy Layout'),
  'category' => t('IPFA'),
  'icon' => 'edgy.png',
  'theme' => 'ipfa_layouts_edgy',
  'css' => 'edgy.css',
  'admin css' => 'edgy.admin.css',
  'regions' => array(
    'top' => t('Top'),
    'main' => t('Main'),
    'side1' => t('Side1'),
    'side2' => t('Side2'),
    'bottom' => t('Bottom'),
  ),
);
