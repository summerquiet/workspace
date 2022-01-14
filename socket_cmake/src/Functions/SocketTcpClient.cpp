/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include "SocketTcpClient.h"
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

static const int SOCKET_SERVER_PORT = 12001;
static const long BUFFER_SIZE = 1024;

static bool g_bQuit = false;

/*---------------------------------------------------------------------------*/
//
SocketTcpClient::SocketTcpClient()
: m_eStatus(E_CLIENT_STATUS_NONE)
, m_iServerFd(-1)
, m_th(0)
{

}

/*---------------------------------------------------------------------------*/

SocketTcpClient::~SocketTcpClient()
{

}

/*---------------------------------------------------------------------------*/
// Init
void SocketTcpClient::init(const SocketReceiveMsgCallback& cb)
{
    SocketBase::init(cb);
}

/*---------------------------------------------------------------------------*/
// Start
bool SocketTcpClient::start()
{
    m_eStatus = E_CLIENT_STATUS_NONE;

    int ret = pthread_create(&m_th, NULL, run, this);
    if (ret != 0) {
        printf("%s:%d start thread error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

/*---------------------------------------------------------------------------*/
// Stop
bool SocketTcpClient::stop()
{
    g_bQuit = true;
    int* thread_ret = NULL;
    pthread_join(m_th, (void**)&thread_ret);

    m_eStatus = E_CLIENT_STATUS_NONE;
    return true;
}

/*---------------------------------------------------------------------------*/
// Send message
bool SocketTcpClient::send(const char* msg, int len)
{
    // Check status
    if (m_eStatus != E_CLIENT_STATUS_CONNECTED) {
        printf("%s:%d status:%d error\n", __PRETTY_FUNCTION__, __LINE__, m_eStatus);
        return false;
    }

    // Send data
    int ret = ::send(m_iServerFd, msg, len, 0);
    if (ret == -1) {
        printf("%s:%d send message error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    printf("%s:%d send message:%s\n", __PRETTY_FUNCTION__, __LINE__, msg);
    return true;
}

/*---------------------------------------------------------------------------*/
// On receive message
bool SocketTcpClient::onReceive(const char* msg, int len)
{
    if (m_eStatus != E_CLIENT_STATUS_CONNECTED) {
        printf("%s:%d status:%d error\n", __PRETTY_FUNCTION__, __LINE__, m_eStatus);
        return false;
    }

    printf("%s:%d receive message %s\n", __PRETTY_FUNCTION__, __LINE__, msg);

    // TODO:

    return true;
}

/*---------------------------------------------------------------------------*/
// Run
void* SocketTcpClient::run(void* arg)
{
    SocketTcpClient* pThis = (SocketTcpClient*)arg;
    pThis->connectSocket();

    return NULL;
}

/*---------------------------------------------------------------------------*/
// Start socket server
bool SocketTcpClient::connectSocket()
{
    printf("%s:%d\n", __PRETTY_FUNCTION__, __LINE__);
    m_eStatus = E_CLIENT_STATUS_CONNECTING;

    // Local address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SOCKET_SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bzero(&server_addr.sin_zero, 8);

    // Create socket
    m_iServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_iServerFd == -1) {
        printf("%s:%d create socket error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    // Connect
    if (connect(m_iServerFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        printf("%s:%d cannot connect to server\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    fd_set client_fd_set;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;

    while (1) {
        if (g_bQuit) {
            break;
        }

        FD_ZERO(&client_fd_set);
        FD_SET(STDIN_FILENO, &client_fd_set);
        FD_SET(m_iServerFd, &client_fd_set);
        int ret = select(m_iServerFd + 1, &client_fd_set, NULL, NULL, &tv);
        if (ret < 0 ) {
            printf("%s:%d select error\n", __PRETTY_FUNCTION__, __LINE__);
            continue;
        }
        else if (ret == 0) {
            printf("%s:%d select time out\n", __PRETTY_FUNCTION__, __LINE__);
            continue;
        }
        else {
            m_eStatus = E_CLIENT_STATUS_CONNECTED;

            if (FD_ISSET(m_iServerFd, &client_fd_set)) {
                // Receive
                char recv_msg[BUFFER_SIZE] = { 0 };
                long byte_num = recv(m_iServerFd, recv_msg, BUFFER_SIZE, 0);
                if (byte_num > 0) {
                    if (byte_num > BUFFER_SIZE) {
                        printf("%s:%d BUFFER_SIZE not enough for receive\n", __PRETTY_FUNCTION__, __LINE__);
                        byte_num = BUFFER_SIZE;
                    }

                    if (!onReceive(recv_msg, byte_num)) {
                        printf("%s:%d onReceive error\n", __PRETTY_FUNCTION__, __LINE__);
                    }
                }
                else if (byte_num < 0) {
                    printf("%s:%d receive message error\n", __PRETTY_FUNCTION__, __LINE__);
                }
                else {
                    printf("%s:%d socket server down\n", __PRETTY_FUNCTION__, __LINE__);
                    break;
                }
            }
        }
    }

    printf("%s:%d socket client exit\n", __PRETTY_FUNCTION__, __LINE__);
    return true;
}

/*---------------------------------------------------------------------------*/
}

/*---------------------------------------------------------------------------*/
/*EOF*/
