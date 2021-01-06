<?php

namespace App\Http\Controllers;

use App\Models\Status;
use Illuminate\Foundation\Auth\Access\AuthorizesRequests;
use Illuminate\Foundation\Bus\DispatchesJobs;
use Illuminate\Foundation\Validation\ValidatesRequests;
use Illuminate\Routing\Controller as BaseController;

class Controller extends BaseController
{
    use AuthorizesRequests, DispatchesJobs, ValidatesRequests;

    public function changeOption(){
        $statuses = Status::all();
        request()->validate([
            'type' => 'required',
        ]);
        $status = new Status(request(['type']));
        if(request('status') === "on"){
            $status->on = 1;
        } else {
            $status->on =0;
        }
        $currentStatus = $statuses->where('type', $status->type);
        //dd($currentStatus);
        if($currentStatus){
            foreach ($currentStatus as $stat)
            $stat->delete();
        }
        $status->save();
        return redirect('/');
    }

    public function index(){
        $statuses = Status::all();
        return view('welcome', compact('statuses'));
    }
}
