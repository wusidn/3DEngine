#include "UdpClient.h"
#include <cstring>
#include <arpa/inet.h>
#include "LogManager.h"

namespace engine
{
    namespace tools
    {
        UdpClient & UdpClient::create(const string & address, const unsigned port)
        {
            UdpClient * result = new UdpClient();
            if(!result->init(address, port))
            {
                delete result;
                result = nullptr;
            }

            return *result;
        }

        const bool UdpClient::init(const string & address, const unsigned port)
        {
            if(!NetWork::init(SOCK_DGRAM)){ return false; }

            // //开启广播特性
            int optval = 1;
            setsockopt(socket_id, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int));

            memset(&sendToAddr, 0, sizeof(sendToAddr));
            sendToAddr.sin_family = AF_INET;
            sendToAddr.sin_port = htons(port);
            sendToAddr.sin_addr.s_addr = inet_addr(address.c_str());
            
            return true;
        }

        const bool UdpClient::send(const string & str) const
        {

            if(::sendto(socket_id, str.c_str(), str.length(), 0, (struct sockaddr * )&sendToAddr, sizeof(sendToAddr)) < 0){ return false; }

            return true;
        }
    }
}