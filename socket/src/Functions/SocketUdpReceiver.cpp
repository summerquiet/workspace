/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include "SocketUdpReceiver.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*---------------------------------------------------------------------------*/
// Type define

struct IP_MREQ
{
    struct in_addr imr_multiaddr; //多播组的IP地址
    struct in_addr imr_interface; //加入的客服端主机IP地址
};

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
SocketUdpReceiver::SocketUdpReceiver()
: m_iServerFd(-1)
, m_th(0)
{

}

/*---------------------------------------------------------------------------*/

SocketUdpReceiver::~SocketUdpReceiver()
{

}

/*---------------------------------------------------------------------------*/
// Init
void SocketUdpReceiver::init(const SocketReceiveMsgCallback& cb)
{
    SocketBase::init(cb);
}

/*---------------------------------------------------------------------------*/
// Start
bool SocketUdpReceiver::start()
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
bool SocketUdpReceiver::stop()
{
    g_bQuit = true;
    int* thread_ret = NULL;
    pthread_join(m_th, (void**)&thread_ret);

    return true;
}

/*---------------------------------------------------------------------------*/
// Send message
bool SocketUdpReceiver::send(const char* msg, int len)
{
    // Check status
    if (m_iServerFd == -1) {
        printf("%s:%d m_iServerFd error\n", __func__, __LINE__);
        return false;
    }

    // TODO:

    printf("%s:%d send message:%s\n", __func__, __LINE__, msg);
    return true;
}

/*---------------------------------------------------------------------------*/
// On receive message
bool SocketUdpReceiver::onReceive(const char* msg, int len)
{
    if (m_iServerFd == -1) {
        printf("%s:%d m_iServerFd error\n", __func__, __LINE__);
        return false;
    }

    // TODO:

    printf("%s:%d receive message %s\n", __func__, __LINE__, msg);
    return true;
}

/*---------------------------------------------------------------------------*/
// Run
void* SocketUdpReceiver::run(void* arg)
{
    SocketUdpReceiver* pThis = (SocketUdpReceiver*)arg;
    pThis->connectSocket();

    return NULL;
}

/*---------------------------------------------------------------------------*/
// Start socket server
bool SocketUdpReceiver::connectSocket()
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

    // Receiver must bind port to multicast port
    sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(UDP_MULTICAST_PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(m_iServerFd, (sockaddr*)&local_addr, sizeof(sockaddr_in));;
    if (ret != 0) {
        printf("%s:%d bind to port:%d error\n", __func__, __LINE__, UDP_MULTICAST_PORT);
        return false;
    }

    // Add into multicast
    IP_MREQ mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(UDP_MULTICAST_IP);
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(m_iServerFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));

    int loop = 1;
    setsockopt(m_iServerFd, IPPROTO_IP, IP_MULTICAST_LOOP, (const char*)&loop, sizeof(loop));

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

            char temp[1024] = { 0 };
            sprintf(temp, "response msg, %s", buffer);
            ret = ::sendto(m_iServerFd, temp, 1024, 0, (sockaddr*)&from_addr, fromlen);
        }
    }

    // Remove from multicast
    setsockopt(m_iServerFd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const char*)&mreq, sizeof(mreq));

    // close sokcet
    close(m_iServerFd);
    m_iServerFd = -1;

    printf("%s:%d socket client exit\n", __func__, __LINE__);
    return true;
}

/*---------------------------------------------------------------------------*/
}

/*---------------------------------------------------------------------------*/
/*EOF*/
