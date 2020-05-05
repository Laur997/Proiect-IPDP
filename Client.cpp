#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <string.h>
#include "Utils.h" 
#define PORT 8080
const char RETURN=10;
void func(int sockfd) 
{ 
    char buff[4096]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n'); 
        
        send(sockfd, buff, sizeof(buff),0); 
        bzero(buff, sizeof(buff)); 
        recv(sockfd, buff, sizeof(buff),0); 
        printf( "%s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 

void introd_password(int sockfd)
{   Utils utils;
    char buff[4096];
    char confirmation[5]; 
    bzero(buff, sizeof(buff)); 
    int n = 0;
    std::cout << "Introduce password:" << std::endl;
    while ((buff[n++] = utils.getch()) != RETURN)
    {
        std::cout<<"*";
    }
    send(sockfd, buff, sizeof(buff),0); 
    bzero(buff, sizeof(buff));
    bzero(confirmation, sizeof(confirmation));
    recv(sockfd,confirmation, 5, 0);
    if(std::string(confirmation) == "YES")
    {
        std::cout << "\nClient connected..."<<std::endl;
    }
    else
    {
        
        if(std::string(confirmation) == "NOT")
        {
            std::cout << "\nIncorrect password.....Try again!"<<std::endl;
            introd_password(sockfd);
        }
    }


    

}

void introd_username(int sockfd)
{   char buff[4096];
    char confirmation[5];
    bzero(buff, sizeof(buff)); 
    int n = 0;
    std::cout << "Introduce username:" << std::endl; 
    while ((buff[n++] = getchar()) != '\n');
    send(sockfd, buff, sizeof(buff),0); 
    bzero(buff, sizeof(buff));

    recv(sockfd,confirmation, 4, 0);
    if(std::string(confirmation) == "YES")
    {
        introd_password(sockfd);
    }
    else
    {   std::cout <<"This user does'n exist.....Try again!"<<std::endl;
        introd_username(sockfd);

    }


}






int main() 
{ 
    Utils utils;
    //Create socket 
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if(server == -1)
    {
        std::cerr << "Can't create socket" << std::endl;
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
        std::cerr << "Connection with the server failed" << std::endl;
    }
    else
    {
        std::cout<< "Connected to the server ....." << std::endl;
    }

//Autentification
    introd_username(server);
    //introd_password(server);
    
    func(server); 
  
    // close the socket 
    close(server); 
} 