(function ($) {
  Drupal.behaviors.feed_import = {
    attach: function (context, settings) {
      var fsets = $('fieldset[id^="item_container_"]', context);
      var addevent = false;
      if (context == document) {
        // jQuery can't change it!
        //document.getElementById('edit-add-new-item').type = 'button';
        $('#edit-add-new-item').bind('click', function () {
          if ($('#edit-add-new-item-mode').attr('checked')) {
            $('#edit-add-new-item-field option:selected').remove();
          }
          else {
            var val = $('#edit-add-new-item-manual').val();
            $('#edit-add-new-item-field option[value="' + val + '"]').remove();
          }
          $('#edit-add-new-item-manual').val('');
        });
        addevent = true;
      }
      else if (fsets.length == 1) {
        addevent = true;
      }
      if (addevent) {
        // Get selects.
        $('select[name^="default_action_"]', fsets).each(function () {
          Drupal.behaviors.feed_import.checkSelectVisibility(this);
          $(this).bind('change', function() {
            Drupal.behaviors.feed_import.checkSelectVisibility(this);
          });
        });
      }
    },
    checkSelectVisibility: function (elem) {
      var val = $(elem).val();
      if (val == 'default_value' || val == 'default_value_filtered') {
        $('div[rel="' + $(elem).attr('name') + '"]').show();
      }
      else {
        $('div[rel="' + $(elem).attr('name') + '"]').hide();
      }
    }
  }
}
)(jQuery);
