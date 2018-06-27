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
  'title' => t('Normal Layout'),
  'category' => t('IPFA'),
  'icon' => 'normal.png',
  'theme' => 'ipfa_layouts_normal',
  'css' => 'normal.css',
  'admin css' => 'normal.admin.css',
  'regions' => array(
    'top' => t('Top'),
    'main' => t('Main'),
    'side1' => t('Side1'),
    'side2' => t('Side2'),
    'bottom' => t('Bottom'),
  ),
);
