(function ($) {
  Drupal.behaviors.viewsMediaBrowserLinks = {
    attach: function (context, settings) {
      // Applying the filters.
      $('a.exposed-button').click(function (){
        // Find the parent form.
        var parent_forms = $('a.exposed-button').parents('form');
        var parent_form = parent_forms[0];
        // Reset our filters.
        Drupal.settings.media.browser.library['filters'] = {};
        // Pull out all current settings.
        Drupal.settings.media.browser.library['filters'] = $.deparam($(parent_form).serialize());
        $('#media-browser-library-list').empty();
        var ui = {tab:{hash:'#media-tab-library'}, panel:'div#media-tab-library.media-browser-tab'};
        if (Drupal.behaviors.mediaLibrary.library) {
          var library = Drupal.behaviors.mediaLibrary.library;
          library.done = false;
          library.cursor = 0;
          library.mediaFiles = [];
          library.selectedMediaFiles = [];
          $('#scrollbox').unbind('scroll', library, library.scrollUpdater);
          library.loading = true;
          $('#media-browser-tabset').trigger('tabsselect', ui);
          $('#scrollbox').bind('scroll', library, library.scrollUpdater);
          // If completed, won't trigger anything, but don't want something bound twice.
        }
      });
    }
  };
})(jQuery);
