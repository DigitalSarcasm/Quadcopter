



<script type="text/javascript">
	
	var map;
	
	var loc;

	
	function initialise(location)
	{
	loc = location;
	
	console.log(location);	
	
	var currentLocation = new google.maps.LatLng(location.coords.latitude, location.coords.longitude);
	
	var mapOptions = 
		{
	 	 center: currentLocation,
	  	 zoom: 15
		};
		
		map = new google.maps.Map(document.getElementById("map-canvas"),
	    mapOptions);
	    
	    var marker = new google.maps.Marker({
	    	position: currentLocation,
	    	map: map
	    });
	}
	
	$(document).ready(function()
	{
		navigator.geolocation.getCurrentPosition(initialise);
		exit();
	});
	
	function gstation(){
		
 $.ajax({
    url: 'index.php?page=ajax_location',
    type: 'post',
    data: 'longitude='+loc.coords.longitude+'&latitude='+ loc.coords.latitude,
    
    success: function(data) {
    	//window.location.reload();
     	stats();
    }
    });
	}
	
	function stats(){
	
			$('#overlay1').fadeIn('fast', function() {
				$('#box1').animate({
				'top' : '100px'
				}, 300);
			});
	}
	
	function exit(){

            $('#box1').animate({'top':'-1000px'},300,function(){
            	$('#overlay1').fadeOut('slow');
            	// $('.notify-status').css('background-color', 'white');
            });
            
           }
           
    function addQuad(){
    	
    }
    
    function switchQuad(){
    	
    }
    
    function removeQuad(num){
    	
    }
</script>

<!-- <div class="overlay" id="overlay2"  style=""></div> -->
	
		<div class="methaphore" style="height:60px;width: 100%;margin-top: 25px">
		<div class="icon">
			<a onclick=""> <img src="includes/img/battery.png" width="60px" height="60px" /></a>
		</div>
		
		<div class="icon">
			<a onclick=""> <img src="includes/img/config.png" width="60px" height="60px" /></a>
		</div>
		
		
		
	</div>
	
	<div id="map1"></div>
	<div  id="map-canvas" >
	</div>

	
	<div class="methaphore" style="height:100px;width: 100%">
		
		<div class="icon">
			<a onclick="addQuad()"> <img src="includes/img/addQuad.png" width="60px" height="60px" /></a>
		</div>
		
		<div class="icon">
			<a onclick="gstation()"> <img src="includes/img/gstation.png" width="60px" height="60px" /></a>
		</div>
		
		
		
		<div class="icon" style="float:right">
			<a onclick=""> <img alt="manual controle" src="includes/img/manual.png" width="60px" height="60px" /></a>
		</div>
		
	</div>
	
	<div class="overlay" id="overlay1"  style="z-index: 100"></div>
<div class="box" style="" id="box1" style="">
<button onclick="exit()" id="exit" style="color:white;background-color: black;height:20px;width:55px;" >Exit</button>
<div id='box-head'> <h2>Ground Station Status </h2> </div>
<div>
	
	<h2>Latitude :</h2><?= $_SESSION['latitude']?>
	<h2>Longitude :</h2><?= $_SESSION['longitude']?>
</div>
</div>
	
