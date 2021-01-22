make: main.cpp Socket_server.cpp Socket_threading.cpp
	g++ -std=c++11 -pthread -o server main.cpp Socket_server.cpp Socket_server.h \
	Socket_threading.h Socket_threading.cpp Components/Base/Component.h \
	Components/Base/Component.cpp Components/Base/WithLed.h \
	Components/Base/WithLed.cpp Components/Base/WithForceSensor.h \
	Components/Base/WithForceSensor.cpp Components/Bed.h \
	Components/Bed.cpp Components/Chair.h Components/Chair.cpp \
  Json_conversion.h Json_conversion.cpp -ljsoncpp
