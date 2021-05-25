#ifndef _SOCKET_PACKET_
#define _SOCKET_PACKET_
#include <iostream>
#include <functional>
namespace socket
{
    /*
        Gör något fint för att skicka skit
    */
    class packet
    {
    private:
        size_t numdata;
        char *data = nullptr;
    public:
        template<typename T>
        packet& operator<<(T obj) &
        {
            return *this;
        }
        packet() = default;
        ~packet();
    };
}
#endif