(function ($) {

/**
 * Media Colorbox behavior.
 */
Drupal.behaviors.initMediaColorbox = {
  attach: function (context, settings) {
    if (!$.isFunction($.colorbox)) {
      return;
    }
    $('a.media-colorbox', context).once('init-media-colorbox', function() {
      // Merge Colorbox settings with Media Colorbox settings from data attributes.
      var mediaColorboxSettings = {initialWidth: String($(this).data('mediaColorboxInitialWidth')), 
        initialHeight: String($(this).data('mediaColorboxInitialHeight'))};
      var options = jQuery.extend({}, settings.colorbox);
      jQuery.extend(options, mediaColorboxSettings);
      $(this).colorbox(options);
    });
  }
};

})(jQuery);
