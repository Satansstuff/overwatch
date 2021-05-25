#include "include/connection/packet.hpp"

using namespace socket;

packet::~packet()
{
    delete data;
}
