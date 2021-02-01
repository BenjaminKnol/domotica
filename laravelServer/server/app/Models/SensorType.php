<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class SensorType extends Model
{
    use HasFactory;
    protected $table = "sensor_type";

    protected $fillable = [
        'type_name',
        'value_description',
        'chart_type',
    ];

    public function log() {
        return $this->HasOne(Log::class);
    }
}
