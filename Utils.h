#ifndef EASYCHAT_UTILS_H
#define EASYCHAT_UTILS_H
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>


class Utils
{
public:    
    std::vector<std::string> split(std::string s, std::string delimiter);
    int getch();

};
#endif //EASYCHAT_UTILS_H