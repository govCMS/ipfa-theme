<?php
/**
 * @file ipfa-layouts-edgy.tpl.php
 */


?>


<div class="gov-edgy-layout clearfix" <?php if (!empty($css_id)) : print "id=\"$css_id\""; endif; ?>>
  <?php if (!empty($content['top'])) : ?>
	  <div class="region-top edgy-region">
	  <?php print $content['top'];?>
	  </div>
  <?php endif; ?>
  <?php if (!empty($content['main'])) : ?>
    <div class="region-main edgy-region">
    <?php print $content['main'];?>
	</div>
  <?php endif; ?>
  <?php if (!empty($content['side1'])) : ?>
    <div class='region-side edgy-side1 edgy-region'>
    <?php print $content['side1'];?>
	</div>
  <?php endif; ?>
  <?php if (!empty($content['side2'])) : ?>
    <div class='region-side edgy-side2 edgy-region'>
    <?php print $content['side2'];?>
  </div>
  <?php endif; ?>
  <?php if (!empty($content['bottom'])) : ?>
    <div class="region-bottom edgy-region">
    <?php print $content['bottom'];?>
    </div>
  <?php endif; ?>
</div>
