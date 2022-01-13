/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include "SocketUdpMulticast.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*---------------------------------------------------------------------------*/
// Namespace
namespace sockettest
{

/*---------------------------------------------------------------------------*/
// Value define

static const char* UDP_MULTICAST_IP = "224.0.0.1";    // 224.0.0.1-239.255.255.254 组播地址范围
static const int UDP_MULTICAST_PORT = 12001;

static bool g_bQuit = false;

/*---------------------------------------------------------------------------*/
//
SocketUdpMulticast::SocketUdpMulticast()
: m_iServerFd(-1)
, m_pMulticastAddr(nullptr)
, m_th(0)
{
    m_pMulticastAddr = new struct sockaddr_in();
    memset(m_pMulticastAddr, 0, sizeof(sockaddr_in));
}

/*---------------------------------------------------------------------------*/

SocketUdpMulticast::~SocketUdpMulticast()
{
    m_iServerFd = -1;
    delete m_pMulticastAddr;
    m_pMulticastAddr = nullptr;
}

/*---------------------------------------------------------------------------*/
// Init
void SocketUdpMulticast::init(const SocketReceiveMsgCallback& cb)
{
    SocketBase::init(cb);
}

/*---------------------------------------------------------------------------*/
// Start
bool SocketUdpMulticast::start()
{
    int ret = pthread_create(&m_th, NULL, run, this);
    if (ret != 0) {
        printf("%s:%d start thread error\n", __func__, __LINE__);
        return false;
    }

    return true;
}

/*---------------------------------------------------------------------------*/
// Stop
bool SocketUdpMulticast::stop()
{
    g_bQuit = true;
    int* thread_ret = NULL;
    pthread_join(m_th, (void**)&thread_ret);

    return true;
}

/*---------------------------------------------------------------------------*/
// Send message
bool SocketUdpMulticast::send(const char* msg, int len)
{
    // Check status
    if (m_iServerFd == -1) {
        printf("%s:%d m_iServerFd error\n", __func__, __LINE__);
        return false;
    }

    // Send data
    int ret = ::sendto(m_iServerFd, msg, len, 0, (sockaddr*)m_pMulticastAddr, sizeof(struct sockaddr_in));
    if (ret == -1) {
        printf("%s:%d send message error\n", __func__, __LINE__);
        return false;
    }

    printf("%s:%d send message:%s to %s:%d\n", __func__, __LINE__, msg, inet_ntoa(m_pMulticastAddr->sin_addr), ntohs(m_pMulticastAddr->sin_port));
    return true;
}

/*---------------------------------------------------------------------------*/
// On receive message
bool SocketUdpMulticast::onReceive(const char* msg, int len)
{
    if (m_iServerFd == -1) {
        printf("%s:%d m_iServerFd error\n", __func__, __LINE__);
        return false;
    }

    printf("%s:%d receive message %s\n", __func__, __LINE__, msg);

    // TODO:

    return true;
}

/*---------------------------------------------------------------------------*/
// Run
void* SocketUdpMulticast::run(void* arg)
{
    SocketUdpMulticast* pThis = (SocketUdpMulticast*)arg;
    pThis->connectSocket();

    return NULL;
}

/*---------------------------------------------------------------------------*/
// Start socket server
bool SocketUdpMulticast::connectSocket()
{
    printf("%s:%d\n", __func__, __LINE__);

    // Create socket
    m_iServerFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (m_iServerFd == -1) {
        printf("%s:%d create socket error\n", __func__, __LINE__);
        return false;
    }

    int opval = 1;
    setsockopt(m_iServerFd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opval, sizeof(int));

    m_pMulticastAddr->sin_family = AF_INET;
    m_pMulticastAddr->sin_addr.s_addr = inet_addr(UDP_MULTICAST_IP);
    m_pMulticastAddr->sin_port = htons(UDP_MULTICAST_PORT);

    // Multicast no need to bind port, it will alloc a rundom port
#if 0
    sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(UDP_MULTICAST_PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    bind(m_iServerFd, (sockaddr*)&local_addr, sizeof(sockaddr_in));
#endif

    while (1) {
        if (g_bQuit) {
            break;
        }

        sockaddr_in from_addr;
        int fromlen = sizeof(from_addr);
        char buffer[1024] = {0};
        int len = 1024; 
        int ret = ::recvfrom(m_iServerFd, buffer, len, 0, (sockaddr*)&from_addr, (socklen_t*)&fromlen);
        if (ret > 0) {
            printf("%s:%d receive message form %s:%d\n", __func__, __LINE__, inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port));
            printf("%s:%d receive message:%s\n", __func__, __LINE__, buffer);
        }
    }

    close(m_iServerFd);
    m_iServerFd = -1;

    printf("%s:%d socket client exit\n", __func__, __LINE__);
    return true;
}

/*---------------------------------------------------------------------------*/
}

/*---------------------------------------------------------------------------*/
/*EOF*/
