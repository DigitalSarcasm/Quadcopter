<title></title>
<!DOCTYPE html>

<html>
  <head>
  	<meta charset="utf-8" />
		
		<title>{{ title }}</title>
		<meta  name="description" content="<?= $page_description ?>" />
		
		<link rel="stylesheet" type="text/css"  href="stylesheets/style.css">
  	 <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/2.0.0/jquery.min.js"></script>
		<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.8/jquery-ui.min.js"></script>
    <script type="text/javascript"
      src="https://maps.googleapis.com/maps/api/js?">
    </script>
    
</head>
<body>
	<div id='wrapper'>
	<header id='header' style=""> <h4 style="font-size: 0.9em;"> <!-- Placez ici le contenu du pied de page -->
	Ground Station</h4>

</header> 

<!--body -->	



</script>


<script type=text/javascript>

	var map;
	var marker;
	var dmarker;
	var flightPath
	var flightPlanCoordinates = [];
	var destinationLocation;
	var loc;
	var dlat;
	var dlng;
	var currentLocation;
	var info = ""
	
	
	function positionSuccess(data){
	
		loc = data; 
		
		currentLocation = new google.maps.LatLng(data.coords.latitude, data.coords.longitude);
		
		var mapOptions = 
		{
		center : currentLocation,
		zoom : 15
		};
		
		map = new google.maps.Map(document.getElementById("map-canvas"),
	    mapOptions);
	    
	    marker = new google.maps.Marker({
	    	position: currentLocation,
	    	map: map,
	    	icon: './../images/ping.png'
	    });
	    
	google.maps.event.addListener(map, "click", function(event) {
    dlat = event.latLng.lat();
    dlng = event.latLng.lng();
    
    
   startMission(dlat,dlng);
   
	});
	
	flightPath = new google.maps.Polyline({
    path: flightPlanCoordinates,
    geodesic: true,
    strokeColor: '#FF0000',
    strokeOpacity: 1.0,
    strokeWeight: 2
  });    
	    
	exit();
	
	}
	

function gstation(){

		
  var sensorReading = $.get('/data');
 
}

	function exit(){

            $('#box1').animate({'top':'-1000px'},300,function(){
            	$('#overlay1').fadeOut('slow');
            	// $('.notify-status').css('background-color', 'white');
            });
            
           }
    // function exitMission(){
// 
            // $('.leftContainer').animate({'left':'-308px'},300,function(){
            	// $('#overlay1').fadeOut('slow');
            	// // $('.notify-status').css('background-color', 'white');
            // });
//             
            // document.getElementById("info").innerHTML = "";
//             
           // }
// 
//            
     function startMission(latitude, longitude){
    	
    		 info = "<button style='font-size: 0.9em;width:100%;color: white; margin: 0; padding: 0; outline: 0; text-decoration: none; box-sizing: border-box !important; -webkit-box-sizing: border-box !important; -moz-box-sizing: border-box !important; -ms-box-sizing: border-box !important;' onclick='exitMission()' id='w8-grey' name='w8-grey' class='w8-button grey' >Exit</button><h4 style='font-size: 0.9em;'>Destination Latitude: " + latitude + ", Destination Longitude: " + longitude + "</h3><img class='icon' onclick='addMark()' src='./../images/mark.png' width='40px' height='40px' /><img class='icon' onclick='addPath()' src='./../images/path.png' width='60px' height='60px' />";
     		
    		 document.getElementById("info").innerHTML = info;
     
     }
    
    function addPath(){
    
    flightPath.setMap(null);
    
  flightPlanCoordinates = [
    new google.maps.LatLng(loc.coords.latitude+0.000700, loc.coords.longitude),
    new google.maps.LatLng(dlat+0.000700,dlng),
  ];
  
    flightPath = new google.maps.Polyline({
    path: flightPlanCoordinates,
    geodesic: true,
    strokeColor: '#FF0000',
    strokeOpacity: 1.0,
    strokeWeight: 2
  });

  flightPath.setMap(map);
    }
    
    function addMark(){
    
   	 marker.setMap(null);
    
     destinationLocation = new google.maps.LatLng(dlat, dlng);
    
     marker = new google.maps.Marker({
	    	position: destinationLocation,
	    	map: map,
	    	icon: './../images/quad.png'
	    });
	 
	 
	 dmarker = new google.maps.Marker({
	    	position: currentLocation,
	    	map: map,
	    	icon: './../images/ping.png'
	    });
	    
	    
	  $('.leftContainer').animate({'left':'0px'},700,function(){
            	
            	$('#overlay1').fadeOut('slow');
            	// $('.notify-status').css('background-color', 'white');
      });
	    
    }
           
         function addQuad(num){
    		
	$('#map-canvas').animate({'left':'2500px'},300,function(){
            	
            	// $('.notify-status').css('background-color', 'white');
           });
		
			
    }
    
    function switchQuad(num){

       
			$('#map-canvas').animate({'left':'0px'},300,function(){
            	
            	// $('.notify-status').css('background-color', 'white');
           });
				
				
    }
    
    function removeQuad(num){
    	
    }

	function initialise(location)
	{
	loc = location;
	
	document.write(location);	

	}
	
	function test(data){
	document.write(data);
	}
	
	
	$(document).ready(function()
	{

	if (navigator.geolocation) {
		navigator.geolocation.getCurrentPosition(positionSuccess);
		console.log("good");
	} else {
		console.log("bad");
		//$('.map').text('Your browser is out of fashion, there\'s no geolocation!');
	}
	
	//gstation();
		
	});

    function takePicture(){
    
    $.get('/data');
    
    }    
	

</script>

<!-- <div class="overlay" id="overlay2"  style=""></div> -->
	
		<div class="methaphore" style="height:60px;width: 100%;margin-top: 25px;margin-bottom: 5px">
	
		<div class="icon">
			<a onclick=""> <img src="./../images/battery.png" width="60px" height="60px" /></a>
		</div>
		
		<div class="icon">
			<a onclick=""> <img src="./../images/config.png" width="60px" height="60px" /></a>
		</div>
		
			<div id="divider" style="margin-bottom: 0px">
	<img src="./../images/divider.jpg" />
</div>
		
	</div>
	
	
	
	
	
	<div style="margin-top: 5px" id="map1"></div>
	<div  id="map-canvas" >
		
	</div>
	<button onclick="switchQuad('1')" value="1" style="visibility: visible" id="fade_map1">Map1</button>
	<button onclick="switchQuad('2')" style="visibility: hidden" value="2" style="visibility: visible" id="fade_map1">Map2</button>
	<button onclick="switchQuad('3')" style="visibility: hidden" value="3" style="visibility: visible" id="fade_map1">Map3</button>
	<button onclick="switchQuad('4')" style="visibility: hidden" value="4" style="visibility: visible" id="fade_map1">Map4</button>
	
	<div class="overlay" id="overlay1"  style="z-index: 100"></div>
<div class="box" style="" id="box1" style="">
<button onclick="exit()" id="exit" style="color:white;background-color: black;height:20px;width:55px;" >Exit</button>
<div id='box-head'> <h2>Ground Station Status </h2> </div>
<div>
	
	<h2>Latitude :</h2><?= $_SESSION['latitude']?>
	<h2>Longitude :</h2><?= $_SESSION['longitude']?>
</div>
</div>







<!--footer -->	

<div id="footer" style="opacity: 1;">
    
    <div class="methaphore" style="">
		
		<!-- <div id="coord" class="leftContainer ">
	<h2> Would you like to start the mission </h2>
	<img src="./../images/Start.png" width="20px" height="20px" />
	</div>
		 -->
		 
		<div id='info' style='margin: 0px auto; width:500px;'> info </div>
		
		<!--<div class="icon">
			<a onclick="addQuad()"> <img src="./../images/addQuad.png" width="60px" height="60px" /></a>
		</div>-->
		
		<div class="icon">
			<a onclick="gstation()"> <img src="./../images/gstation.png" width="60px" height="60px" /></a>
		</div>
		
		<div class="icon">
			<a onclick="takePicture()"> <img src="./../images/camera.png" width="60px" height="60px" /></a>
		</div>
		
		<div class="icon" style="">
			<a onclick=""> <img alt="manual controle" src="./../images/manual.png" width="60px" height="60px" /></a>
		</div>
		
	</div>
     
</div>
<hr/>






</body>
</html>