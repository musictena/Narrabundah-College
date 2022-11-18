
//jQueryUI Widget: Autocomplete (jQueryUI 1)
$(function () {
   var availableTutorials = [
      "Digital Solutions",
      "Networking and Cybersecurity",
      "Robotic and Mechatronics",
   ];
   $("#automplete-1").autocomplete({
      source: availableTutorials
   });
});

//jQueryUI Widget: Accordian (jQueryUI 2)
$(function () {
   $("#accordion-1").accordion();
});

//jQueryUI Widget: Tooltip (jQueryUI 3)
$(function () {
   $('.tooltip-9').tooltip({
      items: 'a.tooltip-9',
      content: 'Robotics and Mechatronics, Digital Solutions',
      show: "slideDown", // show immediately
      open: function (event, ui) {
         ui.tooltip.hover(
            function () {
               $(this).fadeTo("slow", 0.5);
            });
      }
   });
});

//jQueryUI Widget: Datepicker (jQueryUI 4)
$(function () {
   $("#datepicker").datepicker();
});
//jQueryUI Widget: Tabs (jQueryUI 5)
$(function () {
   $("#tabs").tabs();
});

//jQueryUI Widget: Menu (jQueryUI 6)
$(function () {
   $("#menu-1").menu();
});

//jQueryUI Widget: Dialog (jQueryUI 7)
$(function () {
   $("#dialog-1").dialog({
      autoOpen: false,
   });
   $("#opener").click(function () {
      $("#dialog-1").dialog("open");
   });
});
//jQueryUI Widget: Spinner (jQueryUI 8)
$(function () {
   $("#spinner-1").spinner();

});

//jQueryUI Interactions: Sortable (jQueryUI 9)
$(function () {
   $("#sortable-1").sortable();
});

//jQueryUI Effects: Switch class (jQueryUI 10)
$(function () {
   $('#btnSwitch').click(function () {
      $(".NormalClass").switchClass("NormalClass", "LargeClass", 'fast');
      $(".LargeClass").switchClass("LargeClass", "NormalClass", 'fast');
      return false;
   });
});

//jQuery Chaining (jQuery 1) 
$(document).ready(function () {
   $("#chain").click(function () {
      $("p").css("color", "purple");
      $("p").fadeOut(1000);
      $("p").fadeIn(1000);
   });
});

//jQuery toggleClass() (jQuery 2)
$(document).ready(function () {
   $("#class").click(function () {
      $(".hello").toggleClass("big");
   });
});
//jQuery data() (jQuery 3)
$(document).ready(function () {
   $("#infobtn").click(function () {
      alert("Quoted by = " + $("#home").data("author-name"));
      alert("Quoted in = " + $("#home").data("year"));
   });
});

//jQuery dblclick (jQuery 4)
$(document).ready(function () {
   $("#divinfo").dblclick(function () {
      alert('Picture: 2011 Narrabundah Team for World Robotics Olympiad---www.abc.net.au/local/stories/2011/11/30/3380405.htm');
   });
});
