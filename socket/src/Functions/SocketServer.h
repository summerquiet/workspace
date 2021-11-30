/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_SOCKET_SERVER_H
 #define CXX_SOCKET_SERVER_H

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
 * @class SocketServer
 * 
 * @brief Handle socket server class
 * 
 */
class SocketServer : public SocketBase
{
public:
    /**
     * @brief Construct a new Socket Server object
     */
    SocketServer();

    /**
     * @brief Destroy the Socket Server object
     */
    virtual ~SocketServer();

    /**
     * @brief Init
     * 
     */
    virtual void init(const SocketReceiveMsgCallback& cb);

    /**
     * @brief Start
     * 
     */
    virtual bool start();

    /**
     * @brief Stop
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
     * @brief Run
     * 
     */
    static void* run(void* arg);

    /**
     * @brief Start socket server
     * 
     */
    bool startServer();

private:

    // Members
    enum ServerStatus
    {
        E_SERVER_STATUS_NONE = 0,
        E_SERVER_STATUS_STARTING,
        E_SERVER_STATUS_READY,
    };

    ServerStatus        m_eStatus;
    int                 m_iServerFd;
    int                 m_iClientFdList[8];

    pthread_t           m_th;

private:
    /**
     * @brief Copy constructor(Forbidden)
     */
    SocketServer(const SocketServer&);

    /**
     * @brief Operator =(Forbidden)
     */
    SocketServer& operator =(const SocketServer&);

};

/*---------------------------------------------------------------------------*/
// Namespace
}

/*---------------------------------------------------------------------------*/
 #endif // CXX_SOCKET_SERVER_H
 /*EOF*/
