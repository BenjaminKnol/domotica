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
 *
 * Used sources: https://www.bogotobogo.com/cplusplus/sockets_server_client.php  ---> Socket explanation.
 */
#include "Socket.h"

Socket::Socket() {
}
// 1. Create a socket with the socket() system call.
void Socket::createSocket() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("Could not create socket\n");
    } else {
        printf("Socket is created!\n");
    }

    // Define the server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;	// Any address
    server_address.sin_port = htons(PORT);

    /* 2. Bind the socket to an address using the bind() system call.
       For a server socket on the Internet, and address consists of a port number on the host machine. */
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listenToClient();
}

// 3. Listen for connections with the listen() system call.
void Socket::listenToClient() {
    listen(server_socket, NETWORK_QUEUE);
}

/* 4. Accept a connection with the accept() system call.
   This call typically blocks untill a client connects with the server. */
int Socket::acceptConnection() {
    printf("Waiting for incoming connection...\n");
    client_address_length = sizeof(client_address);
    int clientSocket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_length);
    if (clientSocket == -1) {
        printf("Error\n");
    } else {
        printf("Connection has been established\n");
    }
    return clientSocket;
}
/*
* The purpose of this function has the same principle as
* the 3-way handshaking whitin a TCP connection
*
* Example: 1. Syn, 2. Syn + Ack, 3. Achknowledge
*/
string Socket::identifyDevice(int clientSocket) {
    string id;
    char handshake_buffer[MESSAGE_LENGTH];
    // strcpy(handshake_buffer, "unique_id");
    // sendMessage(handshake_buffer, clientSocket); // Ask for unique_id

    if (readMessage(handshake_buffer, MESSAGE_LENGTH, clientSocket) < 0) { // receive unique_id from client
        cout << "Error reading handshake from: " << clientSocket << endl;
    }
    // cout << "ID: " << handshake_buffer << endl; // Only for DEBUG-purposes
    if (readFile(handshake_buffer)) {
        id = (string) handshake_buffer;
        strcpy(handshake_buffer, "Acknowledge\r");
        sendMessage(handshake_buffer, clientSocket); // Send Acknowledgement
    } else {
        cout << "Wrong ID on socket: " << clientSocket << endl;
        close(clientSocket);
    }
    return id;
}
// 5. Send and receive data.
    // read data
int Socket::readMessage(char* buf, int length, int child_socket) {
    bzero(buf,length);
    int status = (int)recv(child_socket, buf, length-1, 0);
    if (status < 0) {
        printf("Read error\n");
    }
    return status;
}
    // Send data
void Socket::sendMessage(char* msg, int clientSocket) {
    int len = (int)strlen(msg);
    int status = send(clientSocket, msg, len, 0);

    if (status < 0) {
        printf("Send error\n");
    }
}
// Read characters from id.txt file
bool Socket::readFile(string buffer) {
    fstream file; // 1. Create ifstream object
    string line;

    file.open("id");  // 2. Read file
    if(!file.is_open()) { // 3. Check if file exists (some error handeling)
        cout << "File does not exists.\n";
    }
    while (getline(file, line)) { // 4. Read all characters from file untill the end of the file.
      if (line[0] == '#') { // 4.1 Skip every line that starts with '#'
          continue;
      }
      if (line.find(buffer[0]) >= 0) {
          return true;
      }
    }
    return false;
}
