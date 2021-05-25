#ifndef _SERVER_
#define _SERVER_
#include "sensors.hpp"
#include <fstream>
#include <filesystem>
#include "server.hpp"
class server
{
private:
    std::ifstream conffile;
    std::vector<std::string> arguments;
public:
    server(int argc, char **argv)
    {
        arguments.reserve(argc);
        for(uint i = 0; argc; i++)
        {
            arguments.push_back(std::string(argv[i]));
        }
    }
    void handlerequest(const char **in);
    bool start();
    void daemon();
};
#endif