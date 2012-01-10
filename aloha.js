( function ( window, undefined ) {
  var Aloha = window.Aloha || ( window.Aloha = {} );

  // Aloha settings
  Aloha.settings = settings.aloha.alohaSettings;

});

(function($) {
  Drupal.behaviors.alohaEditor = {
    attach: function (context, settings) {
      // Run only if aloha is required
      if (settings.aloha) {
        Aloha.ready(function() {
          Aloha.require( ['aloha', 'aloha/jquery'], function( Aloha, $) {
            // Load aloha for each editable content region
            for (var key in settings.aloha.regions) {
              Drupal.behaviors.alohaEditor.attachRegion(key, settings.aloha.regions[key]);
            }
          });
        });
      }
    },

    attachRegion:function (key, region) {
      // Retrieving container
      var $container = Aloha.jQuery('#aloha-container-' + key);
      // Setting up Aloha and events associated
      $container.aloha();
      $container.blur(function () {
        var html = jQuery(this).html();
        if (region.html != html) {
          region.html = html;
          Drupal.behaviors.alohaEditor.save(key, region);
        }
        $(this).removeClass('aloha-edit');
      });
      $container.focus(function () {

        $(this).addClass('aloha-edit');
      });

      // Store HTML
      region.html = $container.html();

      // Setting up exit even
      $(window).unload(function () {
        var html = $container.html();
        if (settings.aloha.regions[key].html != html) {
          Drupal.behaviors.alohaEditor.save(key, region);
        }
      });
    },

    save:function (key, region) {
      $.ajax({
        type:"POST",
        url:Drupal.settings.basePath + 'aloha/' + region.type + '/save',
        data: region,
        success:function (obj) {
          if (obj.status == 'saved') {
            var element = '<div class="aloha-status">' + Drupal.t('%title has been saved.', {'%title':obj.title}) + '</div>';
            $(element).insertBefore($('#aloha-container-' + key)).delay(1300).fadeOut(function () {
              $(this).remove();
            });
          }
        }
      });
    }

  };
}(jQuery));
