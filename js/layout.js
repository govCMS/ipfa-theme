(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.layout = {
    attach: function() {
      // Add class to item lists representing the view mode it contains.
      var itemlist = $('.entity-paragraphs-item > .content');
      itemlist.each(function() {
        // When div has a class beginning with "view-mode-".
        if ($("div[class*=view-mode-]", this).attr("class")) {
          // Get view mode class.
          var viewModeClass = $("div[class*=view-mode-]", this).attr("class").match(/view-mode-[\w-]*\b/);
          // Add classes to parent item list.
          $(this).addClass('grid-12 ' + 'list-' + viewModeClass);
        }
      });
    }
  };

})(jQuery, Drupal, this, this.document);
