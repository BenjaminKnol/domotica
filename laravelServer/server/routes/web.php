<?php

use App\Http\Controllers\LoggingController;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', 'App\Http\Controllers\Controller@index')->name('homepage');

Route::post('/options', 'App\Http\Controllers\Controller@changeOption')->name('options');
Route::post('/web_socket', 'App\Http\Controllers\webSocketController@receive_data')->name('web_socket'); // Parse and send data to C++

Route::get('/dashboard','LoggingController@index')->middleware(['auth'])->name('dashboard');

require __DIR__.'/auth.php';
