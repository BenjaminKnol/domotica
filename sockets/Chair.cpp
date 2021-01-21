 //
// Created by nhutt on 18/01/2021.
//

#include "Chair.h"

#define WEBSERVER_ID 100

Chair::Chair() {

}
void Chair::chair(int unique_id, int status, int sock) {
 Socket_server socket;

 if (unique_id == WEBSERVER_ID) {
     rts_vibrator = status;
     // save received status in cached variable
 } else {
     if (rts_vibrator) {
       socket.send_message("reached", sock); // KET OP: Send_message verwacht een string maar rts_vibrator is een bool
     }
     // do stuff for wemos
 }
}
