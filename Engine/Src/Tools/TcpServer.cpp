#include "NetWork.h"

namespace engine::tools
{
    TcpServer * TcpServer::create(const string & address, const unsigned port)
    {
        TcpServer * result = new TcpServer();
        if(!result->init(address, port)){
            delete result;
            result = nullptr;
        }
        return result;
    }

    const bool TcpServer::init(const string & address, const unsigned port)
    {
        if(!NetWork::init(address, port)){
            return false;
        }

        return true;
    }
}