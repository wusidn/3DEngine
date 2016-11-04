#include "TcpServer.h"
#include "LogManager.h"

namespace engine
{
    namespace tools
    {
        TcpServer & TcpServer::create(const unsigned port)
        {
            return create(DEFAULT_ADDR, port);
        }

        TcpServer & TcpServer::create(const string & address, const unsigned port, const unsigned poolSize, const unsigned loopInterval)
        {
            TcpServer & result = create();
            result.init(address, port, poolSize, loopInterval);
            return result;
        }

        const bool TcpServer::init(void)
        {
            if(!NetWork::init()){ return false; }

            return true;
        }

        const bool TcpServer::init(const string & address, const unsigned port, const unsigned poolSize, const unsigned loopInterval)
        {
            if(!bind(address, port)){ return false; }

            if(!listen(poolSize, loopInterval)){ return false; }

            return true;
        }

        void TcpServer::accept(const function<void (const int client, const struct sockaddr_in & clientInfo)> & callBack)
        {
            NetWork::accept(callBack);
        }

        void TcpServer::close(const function<void (const int client)> & callBack)
        {
            NetWork::close(callBack);
        }

        void TcpServer::recv(const function<void (const int client, const string & str)> & callBack)
        {
            NetWork::recv(callBack);
        }

        const bool TcpServer::send(const string & str) const
        {
            return send(-1, str);
        }

        const bool TcpServer::send(const int client, const string & str) const
        {
            return NetWork::send(client, str);
        }
    }
}