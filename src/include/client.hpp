#ifndef _CLIENT_
#define _CLIENT_
#include <vector>
#include <string>
#include <iostream>
class client
{
private:
    std::vector<std::string> arguments;
    bool isloaded = false;
public:
    client(int argc, char **argv);
    ~client();
};
#endif