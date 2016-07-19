#include "UdpServer.h"


namespace engine::tools
{
    UdpServer * UdpServer::create(const string & address, const unsigned port)
    {
        UdpServer * result = new UdpServer();
        if(!result->init(address, port)){
            delete result;
            result = nullptr;
        }

        return result;
    }

    const bool UdpServer::init(const string & address, const unsigned port)
    {
        if(!NetWork::init(SOCK_DGRAM)){
            return false;
        }

        if(!bind(address, port)){
            return false;
        }
        
        return true;
    }
}