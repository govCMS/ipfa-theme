/**
 * @file
 * JS for Back To Top link.
 */

(function ($) {

  Drupal.behaviors.BackToTop = {
    attach: function (context, settings) {
      var backToTop = $('#back-to-top button');
      var backToTopParent = $('.postscript');

      // Toggle class on backToTop.
      $(function () {
        $(window).scroll(function () {
          isVisible();
          checkOffset();
        });
      });

      // Scroll smoothly to top on click.
      backToTop.click(function (event) {
        $('body,html').animate({
          scrollTop: 0
        }, 800);
        event.preventDefault();
      });

      function isVisible() {
        if ($(this).scrollTop() > 500) {
          backToTop.addClass('is-visible');
        } else {
          backToTop.removeClass('is-visible');
        }
      }

      function checkOffset() {
        if($(document).scrollTop() + window.innerHeight < backToTopParent.offset().top + backToTop.height())
          backToTop.addClass('is-fixed'); // restore when you scroll up
        if(backToTop.offset().top + backToTop.height()/2 >= backToTopParent.offset().top)
          backToTop.removeClass('is-fixed');
      }

    }
  };

})(jQuery);
