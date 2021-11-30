/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_SOCKET_CLIENT_H
 #define CXX_SOCKET_CLIENT_H

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
 * @class SocketClient
 * 
 * @brief Handle socket client class
 * 
 */
class SocketClient : public SocketBase
{
public:
    /**
     * @brief Construct a new Socket Server object
     */
    SocketClient();

    /**
     * @brief Destroy the Socket Server object
     */
    virtual ~SocketClient();

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
    SocketClient(const SocketClient&);

    /**
     * @brief Operator =(Forbidden)
     */
    SocketClient& operator =(const SocketClient&);

};

/*---------------------------------------------------------------------------*/
// Namespace
}

/*---------------------------------------------------------------------------*/
 #endif // CXX_SOCKET_CLIENT_H
 /*EOF*/
