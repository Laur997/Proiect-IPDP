#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netdb.h> 
#include <string.h> 
#define PORT 8080 
using namespace std;
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the message : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n'); 
        
        send(sockfd, buff, sizeof(buff),0); 
        bzero(buff, sizeof(buff)); 
        recv(sockfd, buff, sizeof(buff),0); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main() 
{ 
    
    //Create socket 
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if(server == -1)
    {
        cerr << "Can't create socket" << endl;
        return -1;
    }
    
    //Bind the ip adress and the port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_addr.s_addr = inet_addr("127.0.0.1");
    hint.sin_port = htons(PORT);
    //Connect to the server
    if(connect(server, (sockaddr*)&hint,sizeof(hint)) != 0)
    {
        cerr << "Connection with the server failed" << endl;
    }
    else
    {
        cout<< "Connected to the server ....." << endl;
    }

    // function for chat 
    func(server); 
  
    // close the socket 
    close(server); 
} 