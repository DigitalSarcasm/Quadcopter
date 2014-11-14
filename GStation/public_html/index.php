<?

//============================================================================================
// Security file and session variables
//============================================================================================
session_start();	

//============================================================================================
// Enable Error Reporting
//============================================================================================
error_reporting(E_ALL ^ E_NOTICE);
ini_set('display_errors', '1');

//============================================================================================
// MODEL
//============================================================================================
//require 'model/profile.php';
//$model = new profile();

if($_REQUEST['page'] != 'ajax_location'){
	
	$page_title = ' Ground station ';	
	$page_description = " Ground station navigation system ";	
	
	//Header

	include 'includes/php/header.php';
	//include "includes/php/menu.php"; 	

	if($_REQUEST['request'] == 'log_error')
	echo'<h2>log_error</h2>';
}

if($_REQUEST['page'] == "home" || !isset($_REQUEST['page'])){
	
		include'view/index.php';
}

else if($_REQUEST['page'] == 'ajax_location'){
	$_SESSION['longitude'] = $longitude = $_REQUEST['longitude'];
	$_SESSION['latitude'] = $latitude = $_REQUEST['latitude'];
	
	include'view/gstats.php';
}


//============================================================================================
// Error page
//============================================================================================

else{
	$error_message = "Unknow request ";
include_once'includes/php/error.php';	
}


//============================================================================================
// Footer page
//============================================================================================

if($_REQUEST['page'] != 'ajax_location')
require_once 'includes/php/footer.php';

?>
