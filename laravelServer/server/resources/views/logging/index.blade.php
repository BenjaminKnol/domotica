<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Dashboard
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="grid grid-cols-1 md:grid-cols-2">
            <div class="max-w-7xl sm:px-6 lg:px-8">
                <div class="grid grid-cols-2 md:grid-cols-2">
                    @foreach($statuses as $status)
                        <div class="p-6 border-t border-gray-200 dark:border-gray-700 md:border-l bg-white shadow-sm sm:rounded-lg" style="margin-bottom: 0.85em; margin-right: 0.85rem">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder4" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', $status->type)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder4"></label>
                                        <input type="hidden" name="type" value="{{$status->type}}">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold text-gray-900 dark:text-white">Placeholder {{$status->type}}</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button {{$status->type}}
                                </div>
                            </div>
                        </div>
                    @endforeach
                </div>
            </div>
            <div class="max-w-7xl sm:px-6 lg:px-8">
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
                                <td>{{$log->created_at->format("j F Y, G:i:s")}}</td>
                                <td>
                                    <div class="buttons mr-auto flex">
                                        <a class="button bg-red-600 inline-flex rounded-r p-2 text-white"
                                           href="{{route('delete log', $log->id)}}">
                                            <i class="fas fa-trash fa-lg text-sm"></i>
                                        </a>
                                </td>
                            </tr>
                        @endforeach
                    </table>
                </div>
            </div>
        </div>

    </div>
</x-app-layout>
