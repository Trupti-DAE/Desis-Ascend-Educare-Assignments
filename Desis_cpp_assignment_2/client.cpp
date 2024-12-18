#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#define PORT 7000 //defining the port number for the server --> anything > 1024 and  < 65535

void receive_messages(int socket){ //receiving messages from the server
    char buffer[1024];
    while(true){
        memset(buffer, 0, 1024); //clearing the buffer
        int bytes_received = recv(socket, buffer, 1024, 0); //receive a message from the server

        if(bytes_received <= 0){ //if server is disconnected
            cout << "Disconnected from server." << endl;
            close(socket); //closing the socket
            exit(EXIT_SUCCESS); //exit the program
        }
        //printingg the message received from the server
        cout << "Message: " << buffer << endl;
    }
}

int main(){
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0); //socket created 
    if(client_socket < 0){
        perror("Socket creation failed"); //exiting if socket creation fails
        return -1;
    }

    //set up the server address strcuture 
    server_addr.sin_family = AF_INET; //address family IPv4
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); //setting server IP to localhost


    //connecting to server
    if(connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed"); //exiting if connection fails
        return -1;
    }

    cout << "Connected to the server. Type 'ClientID:Message' to send a DM." << endl;

    thread recv_thread(receive_messages, client_socket); //thread to receive msgs from the server
    recv_thread.detach(); //detach the thread to allow independent execution 

    char buffer[1024];

    while(true){ // loop to send messages to the server
        memset(buffer, 0, 1024); //clear the buffer
        cin.getline(buffer, 1024); //read a line of input from the user
        send(client_socket, buffer, strlen(buffer), 0); //sending to the server
    }

    close(client_socket); //closing socket when done
    return 0;
}