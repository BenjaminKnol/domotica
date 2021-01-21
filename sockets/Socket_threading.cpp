/*
 * TThis file ensures that the Raspberry Pi can listen to multiple
 * connections from clients and receive and / or send data.
 *
 * Authors:
 *    Michael Rotteveel
 *    Benjamin Thomas Knol
 *    Vireen Jagram
 *    Niek Hutten
 *    Noureddine Ait Jaa
 *
 * Used sources: https://www.geeksforgeeks.org/multithreading-in-cpp/     ---> Callable class
 */
#include "Socket_threading.h"

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

    // shutdown(child_socket, 2);
    return status;
}
