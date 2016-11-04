#include "UdpServer.h"
#include "LogManager.h"

#include <thread>
#include <unistd.h>

using namespace std;
namespace engine
{
    namespace tools
    {
        UdpServer & UdpServer::create(const unsigned port, const unsigned loopInterval)
        {
            return create("", port, loopInterval);
        }

        UdpServer & UdpServer::create(const string & address, const unsigned port, const unsigned loopInterval)
        {
            UdpServer * result = new UdpServer();
            if(!result->init(address, port, loopInterval))
            {
                delete result;
                result = nullptr;
            }

            return *result;
        }

        const bool UdpServer::init(const string & address, const unsigned port, const unsigned loopInterval)
        {
            if(!NetWork::init(SOCK_DGRAM)){ return false; }

            // //开启广播特性
            int optval = 1;
            setsockopt(socket_id, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int));

            if(!bind(address, port)){ return false; }
            
            if(!loopRecvFrom()){ return false; }
            
            return true;
        }

        void UdpServer::recvFrom(const function<void (const struct sockaddr_in * clientInfo, const string & str)> & callBack)
        {
            NetWork::recvFrom(callBack);
        }
    }
}