<?php
/**
 * @file ipfa-layouts-normal.tpl.php
 */
$content_grid = "";
$side1_grid = "";
$side2_grid ="";

// all exists
  if((!empty($content['side1'])) &&
     (!empty($content['side2']))){
    $content_grid = "grid-6";
    $side1_grid = "grid-3";
    $side2_grid = "grid-3";
  } elseif((empty($content['side1'])) &&
           (empty($content['side2']))){
    $content_grid = "grid-12";
  } elseif((!empty($content['side1'])) &&
           (empty($content['side2']))){
    $side1_grid = "grid-4";
    $content_grid = "grid-8 region-main-side1";
  } elseif((empty($content['side1'])) &&
           (!empty($content['side2']))){
    $side2_grid = "grid-4";
    $content_grid = "grid-8 region-main-side2";
  }else{
    $content_grid = "grid-12";
    $side1_grid = "";
    $side2_grid ="";
  }
?>


<div class="gov-normal-layout clearfix" <?php if (!empty($css_id)) : print "id=\"$css_id\""; endif; ?>>

  <?php if (!empty($content['top'])) : ?>
    <div class="grid-12 region-top">
      <?php print $content['top'];?>
    </div>
  <?php endif; ?>

  <div class="clearfix">
    <div class="<?php print $content_grid; ?> region-main">
      <?php print $content['main'];?>
    </div>

    <?php if (!empty($content['side1'])) : ?>
      <div class="<?php print $side1_grid; ?> region-side side1">
      <?php print $content['side1'];?>
    </div>
    <?php endif; ?>

    <?php if (!empty($content['side2'])) : ?>
      <div class="<?php print $side2_grid; ?> region-side side2">
        <?php print $content['side2'];?>
      </div>
    <?php endif; ?>
  </div>

  <?php if (!empty($content['bottom'])) : ?>
    <div class="grid-12 region-bottom">
      <?php print $content['bottom'];?>
    </div>
  <?php endif; ?>

</div>
