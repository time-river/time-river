(function ($) {
  "use strict";
  var mainAPP = {
    main_fun: function () {
      $(window).scroll(function () {
        if ($(".navbar").offset().top > 50) {
          $(".navbar-fixed-top").addClass("navbar-pad-original");
        } else {
          $(".navbar-fixed-top").removeClass("navbar-pad-original");
        }
      });
    },
    initialization: function () {
      mainAPP.main_fun();
    }
  }
  $(document).ready(function () {
    mainAPP.main_fun();
  });
}(jQuery));
