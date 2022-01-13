/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_SOCKET_TCP_CLIENT_H
 #define CXX_SOCKET_TCP_CLIENT_H

/*---------------------------------------------------------------------------*/
// Include files

#include "SocketBase.h"
#include <pthread.h>

/*---------------------------------------------------------------------------*/
// Namespace
namespace sockettest
{

/*---------------------------------------------------------------------------*/
// Class define

/**
 * @class SocketTcpClient
 * 
 * @brief Handle socket client class
 * 
 */
class SocketTcpClient : public SocketBase
{
public:
    /**
     * @brief Construct a new Socket Server object
     */
    SocketTcpClient();

    /**
     * @brief Destroy the Socket Server object
     */
    virtual ~SocketTcpClient();

    /**
     * @brief init
     * 
     */
    virtual void init(const SocketReceiveMsgCallback& cb);

    /**
     * @brief init
     * 
     */
    virtual bool start();

    /**
     * @brief init
     * 
     */
    virtual bool stop();

    /**
     * @brief Send message
     * 
     * @param msg 
     * @param len 
     * @return true 
     * @return false 
     */
    virtual bool send(const char* msg, int len);

    /**
     * @brief On receive message
     * 
     * @param msg 
     * @param len 
     * @return true 
     * @return false 
     */
    virtual bool onReceive(const char* msg, int len);

private:

    /**
     * @brief init
     * 
     */
    static void* run(void* arg);

    /**
     * @brief Start connect socket
     * 
     */
    bool connectSocket();

private:
    // Members
    enum ClientStatus
    {
        E_CLIENT_STATUS_NONE = 0,
        E_CLIENT_STATUS_CONNECTING,
        E_CLIENT_STATUS_CONNECTED,
    };

    ClientStatus        m_eStatus;
    int                 m_iServerFd;

    pthread_t           m_th;

private:
    /**
     * @brief Copy constructor(Forbidden)
     */
    SocketTcpClient(const SocketTcpClient&);

    /**
     * @brief Operator =(Forbidden)
     */
    SocketTcpClient& operator =(const SocketTcpClient&);

};

/*---------------------------------------------------------------------------*/
// Namespace
}

/*---------------------------------------------------------------------------*/
#endif // CXX_SOCKET_TCP_CLIENT_H
/*EOF*/
