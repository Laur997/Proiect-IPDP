//Class Login
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Login.h"


const char RETURN=10;
std::string path = "login_file.txt";



std::vector<std::string> split(std::string s, std::string delimiter) //split a string in pieces depending on delimiter
    {
        std::vector<std::string> result;
        int poz = 0; //start position for each word
        for(int i = 0; i < s.length()-1; i++)
        {
	        if(delimiter.compare(s.substr(i,1)) == 0)
	        {
		        result.push_back(s.substr(poz,i-poz));
		        poz = i+1; //position for the next word
	        }
        } 
        return result;

    }

bool Login::confirm_username(std::string name)
    {
        bool flag = false;
        std::vector<std::string> components;
        std::ifstream log_file;
        log_file.open(path);
        std::string line;
        while(std::getline(log_file, line))
        {	
           components =split(line,","); 
           if(components[0] == name)
		   {
			flag = true;
			break;
		   } 
        }
        log_file.close();
        return flag;  
    }    
    
bool Login::confirm_password(std::string username, std::string password)
    {  
        bool flag = false;
        std::ifstream log_file;
        log_file.open(path);
        std::string line;
        while(std::getline(log_file, line))
        {
            if( (line.find(username)) != std::string::npos)
            {
                flag = true;
                break;
            }
                
        }
        if(flag == true)
        {
            if(line.find(password) == std::string::npos )
            {
                flag = false;
            }
            
        }
        
        log_file.close();
        return flag;
    } 
    