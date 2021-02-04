<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Log extends Model
{
    use HasFactory;

    protected $fillable = [
        'type',
        'description',
        'value',
    ];

    public function sensor_type() {
        return $this->belongsTo(SensorType::class, 'id', 'type_id');
    }
}
