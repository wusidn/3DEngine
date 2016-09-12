#pragma once
#ifndef __UDP_CLIENT_H__
#define __UDP_CLIENT_H__

#include "NetWork.h"

namespace engine
{
    namespace tools
    {
        class UdpClient : public NetWork
        {
        public:
            static UdpClient & create(const string & address, const unsigned port);
            const bool send(const string & str) const;
        protected:
            
            const bool init(const string & address, const unsigned port);

        private:
            struct sockaddr_in sendToAddr;
        };
    }
}

#endif //__UDP_CLIENT_H__