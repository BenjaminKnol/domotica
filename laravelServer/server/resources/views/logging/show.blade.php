<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Dashboard
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="grid grid-cols-1 md:grid-cols-2">
            <div class="max-w-7xl sm:px-6 lg:px-8">

            </div>
            <div class="max-w-7xl sm:px-6 lg:px-8">
                <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                   <canvas id="canvas" width="fit-content" height="100%">

                   </canvas>
                </div>
            </div>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
    <script>
        let arr = "{{$dates}}";
        let js_array = arr.replace(/&quot;/gm, "").replace("[", "").replace("]", "").split(",")
        console.log(js_array)
        let data = js_array;
        let result = {{$values}};
        let lineChartData = {
            labels: data,
            datasets: [{
                label: "{{$log->type->value_description}}",
                backgroundColor: "SteelBlue",
                data: result,
                cubicInterpolationMode: 'monotone'
            }]
        };

        window.onload = function (){
            let ctx = document.getElementById("canvas").getContext("2d");
            let lineChart = new Chart(ctx,{
                type: '{{$log->type->chart_type}}',
                data: lineChartData,
                options:{
                    responsive: true,
                    title: {
                        display: true,
                        text: 'everytime a log with type {{$log->type->type_name}} happened'
                    }
                }
            })
        }
    </script>
</x-app-layout>
