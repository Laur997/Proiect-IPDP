#include <iostream>
#include <string>
class User
{
private:
    std::string username;
public:
    void setUsername(std::string name);
    std::string getUsername();   
};