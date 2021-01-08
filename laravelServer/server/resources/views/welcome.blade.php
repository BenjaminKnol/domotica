<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <title>Laravel</title>

        <!-- Fonts -->
        <link href="https://fonts.googleapis.com/css2?family=Nunito:wght@400;600;700&display=swap" rel="stylesheet">
        <script src="https://kit.fontawesome.com/9e8d2c6531.js" crossorigin="anonymous"></script>

        <link rel="stylesheet" href="{{ asset('css/app.css') }}">
    </head>
    <body class="antialiased">
        <div class="relative flex items-top justify-center min-h-screen bg-gray-100 dark:bg-gray-900 sm:items-center sm:pt-0">
            @if (Route::has('login'))
                <div class="hidden fixed top-0 right-0 px-6 py-4 sm:block">
                    @auth
                        <a href="{{ url('/dashboard') }}" class="text-sm text-gray-700 underline">Dashboard</a>
                    @else
                        <a href="{{ route('login') }}" class="text-sm text-gray-700 underline">Login</a>

                        @if (Route::has('register'))
                            <a href="{{ route('register') }}" class="ml-4 text-sm text-gray-700 underline">Register</a>
                        @endif
                    @endauth
                </div>
            @endif

            <div class="max-w-6xl mx-auto sm:px-6 lg:px-8">
                <div class="flex justify-center pt-8 sm:justify-start sm:pt-0">
                    <i class="fas fa-home fa-5x"></i>
                    <h1 style="font-size: 3em; margin-left: 1em">Domotica</h1>
                </div>

                <div class="mt-8 bg-white dark:bg-gray-800 overflow-hidden shadow sm:rounded-lg">
                    <div class="grid grid-cols-1 md:grid-cols-2">
                        <div class="p-6">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder1" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 1)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder1"></label>
                                        <input type="hidden" name="type" value="1">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold">Bed</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button
                                </div>
                            </div>
                        </div>

                        <div class="p-6 border-t border-gray-200 dark:border-gray-700 md:border-t-0 md:border-l">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder2" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 2)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder2"></label>
                                        <input type="hidden" name="type" value="2">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold">Stoel</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button 2
                                </div>
                            </div>
                        </div>

                        <div class="p-6 border-t border-gray-200 dark:border-gray-700">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder3" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 3)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder3"></label>
                                        <input type="hidden" name="type" value="3">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold">Koelkast</div>
                            </div>
                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button 3
                                </div>
                            </div>
                        </div>

                        <div class="p-6 border-t border-gray-200 dark:border-gray-700 md:border-l">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder4" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 4)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder4"></label>
                                        <input type="hidden" name="type" value="4">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold text-gray-900 dark:text-white">Muur</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button 4
                                </div>
                            </div>
                        </div>

                        <div class="p-6 border-t border-gray-200 dark:border-gray-700 md:border-l">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder5" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 5)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder5"></label>
                                        <input type="hidden" name="type" value="5">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold text-gray-900 dark:text-white">Schemerlamp</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button 5
                                </div>
                            </div>
                        </div>

                        <div class="p-6 border-t border-gray-200 dark:border-gray-700 md:border-l">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder6" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 6)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder6"></label>
                                        <input type="hidden" name="type" value="6">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold text-gray-900 dark:text-white">Deur</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button 6
                                </div>
                            </div>
                        </div>

						<div class="p-6 border-t border-gray-200 dark:border-gray-700 md:border-l">
                            <div class="flex items-center">
                                <form method="post" action="{{ route('options') }}">
                                    <div class="onoffswitch">
                                        {{ csrf_field() }}
                                        <input type="checkbox" name="status" class="onoffswitch-checkbox" id="placeholder7" tabindex="0" onchange="this.form.submit()" {{ $statuses->where('type', 7)->where('on', true)->isNotEmpty() ? 'checked' : '' }}>
                                        <label class="onoffswitch-label" for="placeholder7"></label>
                                        <input type="hidden" name="type" value="7">
                                    </div>
                                </form>
                                <div class="ml-4 text-lg leading-7 font-semibold text-gray-900 dark:text-white">Zuil</div>
                            </div>

                            <div class="ml-12">
                                <div class="mt-2 text-gray-600 dark:text-gray-400 text-sm">
                                    Beschrijving placeholder button 7
                                </div>
                            </div>
                        </div>
                        @if($errors->any())
                            <div class="notification is-danger">
                                <ul>
                                    @foreach($errors->all() as $error)
                                        <li>{{ $error }}</li>
                                    @endforeach
                                </ul>
                            </div>
                        @endif
                    </div>
                </div>

                <div class="flex justify-center mt-4 sm:items-center sm:justify-between">
                    <div class="text-center text-sm text-gray-500 sm:text-left">
                        <div class="flex items-center">
                            <a href="#" class="ml-1 underline">
                                <i class="far fa-arrow-alt-circle-right fa-lg"></i> link placeholder
                            </a>
                            <a href="#" class="ml-1 underline">
                                <i class="fas fa-book fa-lg"></i> link_placeholder
                            </a>
                        </div>
                    </div>

                    <div class="ml-4 text-center text-sm text-gray-500 sm:text-right sm:ml-0">
                        placehold
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>
