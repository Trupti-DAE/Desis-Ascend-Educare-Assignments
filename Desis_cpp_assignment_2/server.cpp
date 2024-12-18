#include <iostream>
#include <thread>
#include <map>
#include <mutex>
#include <fstream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;
#define PORT 7000 //defining the port number for the server --> anything > 1024 and  < 65535

mutex log_mutex; // mutex is used for thread safe logging
ofstream log_file("chat_log.txt"); //file to save chat messages
map<int, string> clients; // map that maps connected clients to their identifiers

void log_message(const string &message){ // Function that log messages to the file
    lock_guard<mutex> lock(log_mutex); //thread safe access to the log file
    log_file << message << endl;
    log_file.flush(); //ensures that the msg is immediately written
}

void handle_client(int client_socket){ // handles the connected client communications 
    char buffer[1024];
    while(true){
        memset(buffer, 0, 1024); //clearing the buffer
        int bytes_received = recv(client_socket, buffer, 1024, 0); //receiving msgs from the client

        if(bytes_received <= 0){ // when client is disconnected
            cout << "Client disconnected: " << client_socket << endl;
            log_message("Client disconnected: " + to_string(client_socket));
            close(client_socket); // closing the socket for this client
            clients.erase(client_socket); // removing the client
            break;
        }
        string message(buffer); // message to string
        log_message("Client " + to_string(client_socket) + ": " + message); // logging the message

        // dms between the clients
        // the format is clientID: message where the clientID is the id of the client to which we want to send the message
        size_t separator = message.find(':');
        if(separator != string::npos){
            //extracting receiver client id and the message
            int receiver_client = stoi(message.substr(0, separator));
            string dm_message = message.substr(separator + 1);
            if(clients.find(receiver_client) != clients.end()) send(receiver_client, dm_message.c_str(), dm_message.size(), 0);
            else{
                string error = "Client not found."; // if receiver is not there then telling the sender
                send(client_socket, error.c_str(), error.size(), 0);
            }
        }
    }
}

int main(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0); //creating a socket
    if(server_socket == 0){
        perror("Socket failed");
        exit(EXIT_FAILURE); //exiting if socket creation fails
    }
    //server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //accepts connection from any IP addreess
    server_addr.sin_port = htons(PORT); 

    //bind the socket to the specified adress and port
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE); //exit if fails
    }
    //starts listening for incoming connections
    if(listen(server_socket, 3) < 0){
        perror("Listen failed");
        exit(EXIT_FAILURE); //exit if listening fails
    }

    cout << "Server is running on port " << PORT << endl;

    //main loop that handles new client connections --> also accepts them
    while(true){
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if(client_socket < 0){
            perror("Accept failed");
            continue; //continue to next iteration if accept fails
        }
        //adding new client to the map
        clients[client_socket] = "Client" + to_string(client_socket);
        cout << "New connection: " << client_socket << endl;
        log_message("New connection: " + to_string(client_socket));
        //new thread to handle the client
        thread client_thread(handle_client, client_socket);
        client_thread.detach(); //detaching to allow independent execution
    }
    close(server_socket); //close the server socket
    return 0;
}