<?php

namespace App\Http\Controllers;

use App\Models\Log;
use App\Models\Status;
use Illuminate\Http\Request;

class LoggingController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $logs = Log::all();
        $statuses = Status::all();
        return view('logging.index', compact(['logs', 'statuses']));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $log = Log::find($id);
        $allLogsWithType = Log::where('type_id', '=', $log->type_id)->get();
        $dates = [];
        $values = [];
        for ($i = 0; $i < count($allLogsWithType); $i++){
            $dates[$i] = $allLogsWithType[$i]->created_at->format("j F Y G:i");
            $values[$i] = $allLogsWithType[$i]->value;
        }
        $dates = json_encode($dates);
        $values = json_encode($values);
        return view("logging.show", compact(['log', 'allLogsWithType', 'dates', 'values']));
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        //
    }
}
