<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Log extends Model
{
    use HasFactory;

    protected $fillable = [
        'type_id',
        'description',
        'value',
    ];

    public function type() {
        return $this->belongsTo(SensorType::class, 'id', 'type_id');
    }
}
