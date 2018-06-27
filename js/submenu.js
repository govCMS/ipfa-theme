(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.submenu =  {
    attach: function() {

      // Add anchors to headings.
      $('#content').anchorific();

      stickybits('.pane-node-field-submenu', {
        useFixed: true,
        noStyles: true
      });

      // Activate sub menu items when viewing their anchor.
      $('.field-name-field-submenu a').on('click', function() {
        $('.field-name-field-submenu a').removeClass('active');
        $(this).addClass('active');

        var target = $(this.hash);
        if ($('body').hasClass('navbar-tray-open')) {
          $('html,body').stop().animate({
            scrollTop: target.offset().top - 139
          }, 'linear');
        }

        else if ($('body').hasClass('navbar-horizontal')) {
          $('html,body').stop().animate({
            scrollTop: target.offset().top - 99
          }, 'linear');
        }

        else {
          $('html,body').stop().animate({
            scrollTop: target.offset().top - 60
          }, 'linear');
        }

      });
    }
  };

  $( window ).scroll(function() {
    $('body').removeClass('submenu-is-sticky');
    if ($('.pane-node-field-submenu').hasClass('js-is-sticky')) {
      $('body').addClass('submenu-is-sticky');
    }
  });


})(jQuery, Drupal, this, this.document);
