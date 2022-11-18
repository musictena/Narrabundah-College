
//jQuery Ui: Tooltip
$(function() {
    $("#tooltip-1").tooltip();
 });

//jQuery UI: Datepicker for 'Update User'
$(document).ready(function () {
    $('input[user_enrol_date]').datepicker({   
        dateFormat: 'dd-mm-yy',
         minDate: '-0D',
         maxDate: '+28D',
    });
});
//jQuery UI: Datepicker for 'Update Book'
$(document).ready(function () {
    $('input[book_year]').datepicker({   
        dateFormat: 'dd-mm-yy',
         minDate: '-0D',
         maxDate: '+28D',
    });
});

//jQuery UI: Accordian for 'Admin Profile' 
$(function() {
    $( "#accordion-1" ).accordion();
 });

//jQuery Ui: Progress bar for 'Admin Profile' 
$(function() {
    var progressbar = $( "#progressbar-5" );
    progressLabel = $( ".progress-label" );
    $( "#progressbar-5" ).progressbar({
       value: false,
       change: function() {
          progressLabel.text( 
             progressbar.progressbar( "value" ) + "%" );
       },
       complete: function() {
          progressLabel.text( "Loading Completed!" );
       }
    });
    function progress() {
       var val = progressbar.progressbar( "value" ) || 0;
       progressbar.progressbar( "value", val + 1 );
       if ( val < 99 ) {
          setTimeout( progress, 100 );
       }
    }
    setTimeout( progress, 3000 );
 });

//jquery UI: Shake effect for 'Profile page'
 $(document).ready(function() {
    $('#box-1').click(function() {
       $( "#box-1" ).effect( "shake", {
          times: 6,
          distance: 100
       }, 3000, function() {
          $( this ).css( "background", "" );
       });
    });
 });

 //jQuery UI: Bounce effect for 'Profile page'
 $(document).ready(function() {
    $('#box-2').click(function() {
       $( "#box-2" ).effect("bounce",{
          times: 6,
          distance: 100
       }, 3000);
    });
 });







$('th').click(function(){
    var table = $(this).parents('table').eq(0)
    var rows = table.find('tr:gt(0)').toArray().sort(comparer($(this).index()))
    this.asc = !this.asc
    if (!this.asc){rows = rows.reverse()}
    for (var i = 0; i < rows.length; i++){table.append(rows[i])}
})
function comparer(index) {
    return function(a, b) {
        var valA = getCellValue(a, index), valB = getCellValue(b, index)
        return $.isNumeric(valA) && $.isNumeric(valB) ? valA - valB : valA.toString().localeCompare(valB)
    }
}
function getCellValue(row, index){ return $(row).children('td').eq(index).text() }