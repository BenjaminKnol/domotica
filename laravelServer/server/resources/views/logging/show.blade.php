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
                    <div>
                        <p id="lastGraphUpdate" style="text-align: right; font-size: small; color: lightsteelblue; padding-right: 3px;">last updated: {{date("G:i:s")}}</p>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4"></script>
    <script>
        let lineChart
        let i = 0;
        let arr = "{{$dates}}";
        let js_array = arr.replace(/&quot;/gm, "").replace("[", "").replace("]", "").split(",")
        console.log(js_array)
        let data = js_array;
        let result = {{$values}};
        let lineChartData = {
            labels: data,
            datasets: [{
                label: "{{$log->type->value_description}}",
                fill: false,
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: result,
                lineTension: 0,
            }]
        };

        window.onload = function () {
            let ctx = document.getElementById("canvas").getContext("2d");
            lineChart = new Chart(ctx, {
                type: '{{$log->type->chart_type}}',
                data: lineChartData,
                options: {
                    responsive: true,
                    title: {
                        display: true,
                        text: 'everytime a log with type {{$log->type->type_name}} happened'
                    }
                }
            })
        }
        let newValues;
        function loadDoc() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    const regex = /= (\[(-?[0-9]\d*,?)+\])/g;
                    let m;
                    while ((m = regex.exec(this.responseText)) !== null){
                        if (m.index === regex.lastIndex) {
                            regex.lastIndex++;
                        }
                        m.forEach((match, groupIndex) => {
                            if (groupIndex === 1){
                                newValues = JSON.parse(match);
                            }
                        });
                    }
                }
            };
            xhttp.open("GET", "{{route('show log', $log->id)}}", true);
            xhttp.send();
        }

        setInterval(function () {
            loadDoc();
            let d = new Date();
            let formatter = new Intl.DateTimeFormat('en', {day: 'numeric', month: 'long', year: 'numeric', hour: '2-digit', minute:'2-digit', hourCycle: 'h24'})
            let formatted = formatter.format(d).replace(",", "").replace(",", "");
            console.log(formatted);
            if ((lineChart.data.datasets[0].data.length < newValues.length)){
                lineChart.data.datasets[0].data = newValues;
                lineChart.data.labels.push(formatted.toString());
                lineChart.update();
                console.log("update");
            }
            document.getElementById("lastGraphUpdate").innerText = "last updated: " + d.getHours() + ":" + d.getMinutes() + ":" + d.getSeconds();
        }, 5000);
    </script>
</x-app-layout>
