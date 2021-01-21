cmake_minimum_required(VERSION 3.17)
project(ClassStructure)

set(CMAKE_CXX_STANDARD 11)

add_executable(ClassStructure main.cpp Bed.cpp Bed.h Component.cpp Component.h WithLed.cpp WithLed.h WithForceSensor.cpp WithForceSensor.h Chair.cpp Chair.h Column.cpp Column.h Door.cpp Door.h TableLamp.cpp TableLamp.h Wall.cpp Wall.h Fridge.cpp Fridge.h)