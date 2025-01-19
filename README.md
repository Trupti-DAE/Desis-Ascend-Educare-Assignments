# Desis-Ascend-Educare-Assignments
Contains code and details about the assignments being done as a part of the program.

## Assignment 3
All the details about each question is in respective questions' directory(Question 1, Question2, question3) 

## Assignment 2
Create a realtime chat system by making use of Sockets. The task for this assignment is to create a multi-user realtime chatting system using Sockets. The server and client will be talking to each other in real time for an infinite period until one of them is closed (by pressing Ctrl+C on the terminal). However, it is possible for one user to talk to multiple users (in DMs only, no group chats for now!) Also, all the chat messages from the server and client should be labeled and stored into a file for historical reference. Extra points if you make use of STL APIs like vectors, strings etc. Bigger props if you manage to use threads for saving data!

### Features
- Multi-client support: Multiple clients can connect to the server.
- Direct messaging: Send DMs to a specific client by typing their client ID followed by a colon and the message (e.g., 5:Heyy!).
- Message logging: The server logs all messages in a file named chat_log.txt.

### How to run and use
- Open a terminal.
  - Compile the server code.
    - g++ server.cpp -o server -pthread
    - ./server
- Open other terminals (one or multiple)
  - Compile the client code.
    - g++ client.cpp -o client -pthread
    - ./client
For multiple clients, connections will be there on the server side.

**Sending Messages:** After connecting, simply type your message and press Enter to send it to everyone.
- To send a private message to a specific client:
  - Use the format ClientID:YourMessage.
  - Example: 5:Hello, how are you?
  - This will send "Hello, how are you?" to the client with ID 5.
  
**Receiving Messages:** Any messages sent by other clients (or the server) will automatically appear in the terminal.

### Note
- Make sure the server is running before starting any clients.
- Use the IP address 127.0.0.1 to connect to the server (this means it's running on the same computer).
- If the client disconnects or the server shuts down, the connection will be lost.
