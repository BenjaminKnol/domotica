<?php
/*
 * This file takes the data from the web page to the 
 * main of the C++ file.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 * Sources: 
 *		Explanation about JSON: https://www.w3schools.com/js/js_json_php.asp & 
 *								https://www.tutorialrepublic.com/php-tutorial/php-json-parsing.php
 *		Create a websocket:		https://www.codeproject.com/Tips/418814/Socket-Programming-in-PHP
 *		Basic PHP info:			https://www.w3schools.com/php/default.asp
 */
define("HOST", '172.16.0.1', true);
define("PORT", '9002', true);

function check_status() {	// Check if checkbox is selected or not. Selected = True (1) and Unselected = False (0).
	$status = isset($_POST['status'][0]) ? 1 : 0;
	return $status;
}
function check_id() {	// Check for selected ID
	$id = $_POST['type'];
	return $id;
}

function receive_data() {
	$data = array(check_id()=>check_status());	// Merge two variables into one array
	$send_data = json_encode($data);	// Parsing data from PHP to JSON
	switch(check_id()) {
		case 'bed':				// Placeholder 1 - BED_LED
			web_socket($send_data);
			break;
		case 'stoel':			// Placeholder 2 - DEUR
			web_socket($send_data);
			break;
		case 'koelkast':		// Placeholder 3 - KOELKAST
			web_socket($send_data);
			break;
		case 'muur': 			// Placeholder 4 - MUUR
			web_socket($send_data);
			break;
		case 'schemerlamp': 	// Placeholder 5 - SCHEMERLAMP
			web_socket($send_data);
			break;
		case 'deur':			// Placeholder 6 - STOEL
			web_socket($send_data);
			break;
		case 'zuil':			// Placeholder 7 - ZUIL
			web_socket($send_data);
			break;
		default:
			break;
	}
}

function web_socket($msg) {
	
// 1. Create Socket 
	$web_client = socket_create(AF_INET, SOCK_STREAM, 0);
	if (!($web_client = socket_create(AF_INET, SOCK_STREAM, 0))) {
		$errorcode = socket_last_error();
		$errormsg = socket_Strerror($errorcode);
	
		die("400 Bad Request: [$errorcode] $errormsg] \n");
	}

// 2. Connect to server
	if (!(socket_connect($web_client, HOST, PORT))) {
		$errorcode = socket_last_error();
		$errormsg = socket_Strerror($errorcode);
	
		die("503 Service Unavailable: [$errorcode] $errormsg] \n");
	}

// 3. Send data to C++
	if (!socket_send($web_client, $msg, strlen($msg), 0)) {
		$errorcode = socket_last_error();
		$errormsg = socket_strerror($errorcode);
     
		die("Could not send data: [$errorcode] $errormsg \n");
	}
}
// Call function
//receive_data(); 
?>



