
/**
 * @file
 * Javascript for paragraph slideshow.
 */

(function($) {
    Drupal.behaviors.paragraphSlideshow = {
        attach: function(context) {
            var slideshows = Drupal.settings.paragraph_slideshow;
            $.each(slideshows, function(selector, options) {
                console.log(selector);
            });
        }
    };

})(jQuery);
