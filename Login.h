#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utils.h"

class Login
{
public:
    bool confirm_username(std::string name);
    bool confirm_password(std::string username, std::string password);
};