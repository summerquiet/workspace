/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_SOCKET_UDP_RECEIVER_H
 #define CXX_SOCKET_UDP_RECEIVER_H

/*---------------------------------------------------------------------------*/
// Include files

#include "SocketBase.h"
#include <pthread.h>

/*---------------------------------------------------------------------------*/
// Class define

struct sockaddr_in;

/*---------------------------------------------------------------------------*/
// Namespace
namespace sockettest
{

/*---------------------------------------------------------------------------*/
// Class define

/**
 * @class SocketUdpReceiver
 * 
 * @brief Handle socket client class
 * 
 */
class SocketUdpReceiver : public SocketBase
{
public:
    /**
     * @brief Construct a new Socket Server object
     */
    SocketUdpReceiver();

    /**
     * @brief Destroy the Socket Server object
     */
    virtual ~SocketUdpReceiver();

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
    int                 m_iServerFd;

    pthread_t           m_th;

private:
    /**
     * @brief Copy constructor(Forbidden)
     */
    SocketUdpReceiver(const SocketUdpReceiver&);

    /**
     * @brief Operator =(Forbidden)
     */
    SocketUdpReceiver& operator =(const SocketUdpReceiver&);

};

/*---------------------------------------------------------------------------*/
// Namespace
}

/*---------------------------------------------------------------------------*/
#endif // CXX_SOCKET_UDP_RECEIVER_H
/*EOF*/
