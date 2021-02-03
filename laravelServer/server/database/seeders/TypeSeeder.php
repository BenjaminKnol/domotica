<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class TypeSeeder extends Seeder {
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run() {
        DB::table( 'sensor_type' )->insert( [
            [
                'id'                => 1,
                'type_name'         => "Bed",
                'value_description' => "Patient ligt op bed"
            ],
            [
                'id'                => 2,
                'type_name'         => "Stoel",
                'value_description' => "Patient zit op stoel"
            ],
            [
                'id'                => 3,
                'type_name'         => "Koelkast",
                'value_description' => "temperature in °C"
            ],
            [
                'id'                => 4,
                'type_name'         => "Muur",
                'value_description' => "Verduistering over tijd"
            ],
            [
                'id'                => 5,
                'type_name'         => "Schemerlamp",
                'value_description' => "aan/uit over tijd"
            ],
            [
                'id'                => 6,
                'type_name'         => "Deur",
                'value_description' => "Open/dicht over tijd"
            ],
            [
                'id'                => 7,
                'type_name'         => "Zuil",
                'value_description' => "Alcohol meeting over tijd"
            ],
        ] );
    }
}
