<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Logs
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <table class="p-6 bg-white border-b border-gray-200" s style="width: 100%">
                    <tr>
                        <th>ID</th>
                        <th>Type</th>
                        <th>Description</th>
                        <th>Gemeld op</th>
                        <th></th>
                    </tr>
                    @foreach($logs as $log)
                        <tr class="text-center">
                            <td>{{$log->id}}</td>
                            <td>{{$log->type}}</td>
                            <td>{{$log->description}}</td>
                            <td>{{$log->created_at->format("j F, Y, G:i:s")}}</td>
                            <td>
                                <div class="buttons mr-auto flex">
                                    <div class="button bg-blue-500 inline-flex rounded-l p-1">
                                        <a>
                                            <i class="fas fa-eye fa-lg"></i>
                                        </a>
                                    </div>
                                    <div class="button bg-green-400 inline-flex p-1">
                                        <a>
                                            <i class="fas fa-pencil fa-lg"></i>
                                        </a>
                                    </div>
                                    <div class="button bg-red-600 inline-flex rounded-r p-1">
                                        <a>
                                            <i class="fas fa-trash fa-lg"></i>
                                        </a>
                                    </div>
                                </div>
                            </td>
                        </tr>
                    @endforeach
                </table>
            </div>
        </div>
    </div>
</x-app-layout>
