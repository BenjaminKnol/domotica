<?php

namespace App\Http\Controllers;

use App\Models\Log;
use Illuminate\Http\Request;
use App\Models\User;

define("HOST", '192.168.2.13');
define("PORT", '8080');

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

class webSocketController extends Controller
{
    function check_status() {	// Check if checkbox is selected or not. Selected = True (1) and Unselected = False (0).
        return request('status') === "on";
    }

    function check_id() {	// Check for selected ID
        return request('type');
    }

    function receive_data() {
        $data = collect([$this->check_id()=>$this->check_status()]);	// Merge two variables into one array
        $send_data = $data->toJson();
        switch($this->check_id()) {
            case '1':				// Placeholder 1 - BED_LED
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            case '2':			// Placeholder 2 - DEUR
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            case '3':		// Placeholder 3 - KOELKAST
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            case '4': 			// Placeholder 4 - MUUR
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            case '5': 	// Placeholder 5 - SCHEMERLAMP
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            case '6':			// Placeholder 6 - STOEL
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            case '7':			// Placeholder 7 - ZUIL
                $this->web_socket($send_data);
                Log::create([
                    'type' => $send_data->type,
                    'description' => $send_data->description,
                ]);
                break;
            default:
                break;
        }
        return;
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

            //don't know is this works would like someone to test this maybe

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
}
