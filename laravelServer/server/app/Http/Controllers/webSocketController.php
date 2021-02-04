<?php

namespace App\Http\Controllers;

use App\Models\Log;
use Illuminate\Http\Request;
use App\Models\User;
use App\Models\Status;

define("HOST", '127.0.0.1');
define("PORT", '9002');
define ("WEB_ID", "p0");

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
		$data = collect(["id"=>$this->check_id(), "status"=>$this->check_status(), 'guid'=>WEB_ID]);   // Merge three variables into one array
    $send_data = $data->toJson();
    $this->writeToCpp($send_data);
    Log::create([
        'type_id' => $this->check_id(),
        'value' => $this->check_status(),
    ]);
    // $send_data = $data->toJson();
    // $this->writeToCpp($send_data);
    // $this->readFrom();
    return;
    }

    // function readFrom() {
    //     // 1. Create a socket
    //     if (!($web_client = socket_create(AF_INET, SOCK_STREAM, 0))) {
    //         $errorcode = socket_last_error();
    //         $errormsg = socket_Strerror($errorcode);
    //
    //         die("400 Bad Request: [$errorcode] $errormsg] \n");
    //     }
    //     // 2. Connect to the server
    //     if (!(socket_connect($web_client, HOST, PORT))) {
    //         $errorcode = socket_last_error();
    //         $errormsg = socket_Strerror($errorcode);
    //
    //         //don't know is this works would like someone to test this maybe
    //
    //         die("503 Service Unavailable: [$errorcode] $errormsg] \n");
    //     }
    //     // 3. Read from the server
    //     $result = socket_read ($web_client, 1024) or die("Could not read server response\n");
    //     // 4. Close socket
    //     socket_close($web_client);
    //
    //     if ($result.contains("forgot to close door")) {
    //       Log::create([
    //           'type_id' => 3,
    //           'value' => 1,
    //       ]);
    //       $statuses = Status::all();
    //
    //       $status = new Status(3);
    //       $status->on = 1;
    //
    //       $currentStatus = $statuses->where('type', $status->type);
    //       if($currentStatus){
    //           foreach ($currentStatus as $stat)
    //           $stat->delete();
    //       }
    //       $status->save();
    //     }
    //     if ($result.contains("door closed")) {
    //       Log::create([
    //           'type_id' => 3,
    //           'value' => 0,
    //       ]);
    //       $statuses = Status::all();
    //
    //       $status = new Status(3);
    //       $status->on = 0;
    //
    //       $currentStatus = $statuses->where('type', $status->type);
    //       if($currentStatus){
    //           foreach ($currentStatus as $stat)
    //           $stat->delete();
    //       }
    //       $status->save();
    //     }
    // }

    function writeToCpp($msg) {
// 1. Create Socket
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
        if (!(socket_write($web_client, $msg, strlen($msg)))) {
            $errorcode = socket_last_error();
            $errormsg = socket_strerror($errorcode);

            die("Could not send data: [$errorcode] $errormsg \n");
        }
        socket_close($web_client);
    }
}
