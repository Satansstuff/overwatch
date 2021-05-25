
#include "include/server.hpp"
#include "include/client.hpp"

int main(int argc, char **argv)
{
    server s(argc, argv);
    client c(argc, argv);
    bool started = s.start();
    return EXIT_SUCCESS;
}