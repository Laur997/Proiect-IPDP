#include <iostream>
#include <sys/types.h>
#include <unistd.h> // for close() function
#include <sys/socket.h>
#include <netdb.h> // for NI_MAXHOST, NIMAXSERV, memset and getnameinfo
#include <arpa/inet.h> // for inet_ntop and inet_pton functions
#include <string.h>
#include <string>
#include <fstream>
#include "Login.h"
#define PORT 8080  
using namespace std;
 


std::string eraseLineTerminator(std::string s)
{   std::string toErase = "\n";
    int poz = s.find(toErase);
    if(poz != std::string::npos)
    {
        s.erase(poz,toErase.length());
    }
    return s;
}

int main()
{
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
 
    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
 
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
    close(listening);
 
   //Autentification part   
    Login login;
    char buf[4096];
    std::string username, password;
    bool confirmation;
    //receive username
    recv(clientSocket,buf, 4096,0); //get username
    username = eraseLineTerminator(std::string(buf)); //convert username to string + erase "\n" 
    confirmation = login.confirm_username(username); //confirm username
    if(confirmation)
    {
        send(clientSocket,"YES", sizeof("YES"),0);
    }
    else
    {
        send(clientSocket,"NOT", sizeof("NOT"),0);
    }


    //receive password
    recv(clientSocket,buf, 4096,0);
    password = eraseLineTerminator(std::string(buf));
    int tries = 0;
    confirmation = login.confirm_password(username, password);

    while(!confirmation && (tries <= 3)) // while confirmation is not good and the client still has tries do:
    {
        send(clientSocket,"NOT", sizeof("NOT"),0);
        recv(clientSocket,buf, 4096,0);
        password = eraseLineTerminator(std::string(buf));
        confirmation = login.confirm_password(username, password);
        tries++;
    }
    if(tries > 3)
    {
        close(clientSocket);
    }
    if(confirmation)
    {
        send(clientSocket,"YES", sizeof("YES"),0);
    }


  

 // While loop: accept and echo message back to client    
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }
 
        cout << string(buf) << endl;
       
        // Echo message back to client
        send(clientSocket, buf, bytesReceived+1, 0);
    }
 
    // Close the socket
    close(clientSocket);
 
    return 0;
}