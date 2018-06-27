<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<header class="header" id="header" role="banner">
  <div class="header__inner">
    <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo mobile" id="logo-mobile"><img src="/sites/all/themes/custom/ipfa/logo-mobile.svg" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
  <?php endif; ?>
    <div class="menu-toggle">
      <span></span>
      <span></span>
      <span></span>
      <span></span>
    </div>
  <?php print render($page['header']); ?>
  <?php print render($page['navigation']); ?>
  </div>
</header>

<div id="page">
  <?php print $breadcrumb; ?>

  <?php if ($tabs) { ?>
    <div class='user-tabs container'>
      <?php print render($tabs); ?>
    </div>
  <?php } ?>

  <div id="main">
    <div id="content" class="column" role="main">
     <a href="#skip-link" id="skip-content" class="element-invisible">Go to top of page</a>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
        <?php if($messages):?>
        <div class='message container'>
        <?php print $messages; ?>
        </div>
        <?php endif; ?>
      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>
    </div>
  </div>
  <div class="row postscript">
    <div id="back-to-top"><button title="Back to top" class="back-to-top__link">Back to top</button></div>
  <?php print render($page['postscript']); ?>
  </div>
  <div class="footer">
    <div class="footer__inner">
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="footer__logo"><img src="/sites/all/themes/custom/ipfa/logo-mobile.svg" alt="<?php print t('Home'); ?>" class="footer__logo-image" /></a>
      <?php print render($page['footer']); ?>
    </div>
  </div>
</div>
