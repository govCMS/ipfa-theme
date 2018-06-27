(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.menuToggle = {
    attach: function(context, settings) {

      // Show the menu on click on hamburger icon.
      $('.menu-toggle').on('click', function () {
        $('.sf-main-menu').toggleClass('open');
        $(this).toggleClass('open');
      });

    }
  };

})(jQuery, Drupal, this, this.document);
