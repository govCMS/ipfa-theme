(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.submenu =  {
    attach: function() {

      // Add anchors to headings.
      $('#content').anchorific();

      stickybits('#header', {
        useFixed: true,
        noStyles: true
      });

      // Activate sub menu items when viewing their anchor.
      $('.field-name-field-submenu a').on('click', function() {
        $('.field-name-field-submenu a').removeClass('active');
        $(this).addClass('active');

        // Calculating scroll possition offset -x -y -z
        // (x=admin navbar, y=headerHeight, z=extra distance)
        var target = $(this.hash);
        var headerHeight = $('#header').outerHeight();

        if ($('body').hasClass('navbar-tray-open')) {
          $('html,body').stop().animate({
            scrollTop: target.offset().top - 79 - headerHeight - 10
          }, 'linear');
        }

        else if ($('body').hasClass('navbar-horizontal')) {
          $('html,body').stop().animate({
            scrollTop: target.offset().top - 39 - headerHeight - 10
          }, 'linear');
        }

        else {
          $('html,body').stop().animate({
            scrollTop: target.offset().top - headerHeight - 10
          }, 'linear');
        }

      });
    }
  };

  $( window ).scroll(function() {
    var scrollpos = $(document).scrollTop();
    var headerHeight = $('#header').outerHeight();
    $('#page').css('padding-top', 0);

    if(scrollpos > 0) {
      $('#page').css('padding-top', headerHeight);
    }
    else {
      $('#page').css('padding-top', 0);
    }
  });


})(jQuery, Drupal, this, this.document);
