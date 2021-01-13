/*
 * This file  ensures that the Raspberry Pi listen to the
 * connection from the Wemos D1 mini devices.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 */
#include "Socket_threading.h"

using namespace std;

Socket_threading::Socket_threading() {

}

void Socket_threading::operator()(string* message_ptr, int message_length, int child_socket) {
    read_message(message_ptr, message_length, child_socket);
}
// 5. Receive data.
int Socket_threading::read_message(string* buf, int length, int child_socket) {
    char buffer[length];
    memset((buffer), 0, (length));
    int status = (int)recv(child_socket, buffer, length-1, 0);
    if (status < 0) {
        printf("Read error\n");
    }
    *buf = string(buffer);

    shutdown(child_socket, 2);
    return status;
}
