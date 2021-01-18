<?php

use App\Models\Log;
use Illuminate\Foundation\Inspiring;
use Illuminate\Support\Facades\Artisan;

/*
|--------------------------------------------------------------------------
| Console Routes
|--------------------------------------------------------------------------
|
| This file is where you may define all of your Closure based console
| commands. Each Closure is bound to a command instance allowing a
| simple approach to interacting with each command's IO methods.
|
*/

Artisan::command('inspire', function () {
    $this->comment(Inspiring::quote());
})->purpose('Display an inspiring quote');
Artisan::command('monthly-delete', function (){
    $currentDay = date("Y-m-d");
    $dateToDeleteFrom = date("Y-m-d", strtotime($currentDay."-1 Months"));
    $logs = Log::whereDate('created_at', '<=', $dateToDeleteFrom)->get();
    Log::whereDate('created_at', '<=', $dateToDeleteFrom)->delete();
    $this->comment(count($logs)." old log(s) deleted");
})->purpose('monthly delete logs');
