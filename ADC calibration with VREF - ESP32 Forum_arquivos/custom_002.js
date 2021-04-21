/*global $:false */

$(document).ready(function() {
                 
	// Animate the scroll to top

      $('.go-top').click(function(event) {
              event.preventDefault();
              $('html, body').animate({scrollTop: 0}, 'slow');
        });
      
   
	// Navbar Dropdowns

		$(function () {
		    $('#nav-main li.has-dropdown > a').click(function(evt) {
		        evt.stopPropagation(); //stops the document click action
		        $(this).parent('li').siblings().removeClass('clicked');
		        $(this).parent('li').toggleClass('clicked');
		    });

		    $(document).click(function() {
		        $('#nav-main li.has-dropdown > a').parent('li').removeClass('clicked'); //make all inactive
		    });

		    $('#nav-main > li.has-dropdown > a').click(function() {
		        $('.small-cube.has-dropdown > a').parent('li').removeClass('clicked'); //make all inactive
		    });

		    $('.small-cube.has-dropdown > a').click(function() {
		        $('#nav-main > li.has-dropdown > a').parent('li').removeClass('clicked'); //make all inactive
		    });

		    $('#nav-main li.has-dropdown > a').click(function(e) {
		    	e.preventDefault();//stops the document click jump
		    });	
		});

		$('#responsive-menu-button > a').click(function(e) {
			$('#nav-main').toggleClass('clicked');
		    e.preventDefault();//stops the document click jump
		});

	// Custom Tabs

      $('.s-tabs-header a').on('click', function(e)  {
        var currentAttrValue = $(this).attr('href');
 
        // Show/Hide Tabs
        $('.s-tabs ' + currentAttrValue).fadeIn(400).siblings().hide();
 
        // Change/remove current tab to active
       $(this).parent('li').addClass('activetab').siblings().removeClass('activetab');
 
        e.preventDefault();
      });

    // OP Tabs

      $('#page-tabs .tab a,.options-panel #tabs .tab a').on('click', function(e)  {
        var currentAttrValue = $(this).attr('href'); 
        // Show/Hide Tabs
        $('#page-tabs ' + currentAttrValue).show().siblings().hide(); 
        // Change/remove current tab to active
       $(this).parent('li').addClass('activetab').siblings().removeClass('activetab'); 
        e.preventDefault();
      });		
});

