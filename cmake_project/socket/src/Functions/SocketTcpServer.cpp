/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include "SocketTcpServer.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>

#include <stdio.h>
#include <unistd.h>

/*---------------------------------------------------------------------------*/
// Namespace
namespace sockettest
{

/*---------------------------------------------------------------------------*/
// Value define

static const int SOCKET_SERVER_PORT = 12001;
static const int BACKLOG = 5;
static const int CONNECT_CURRENT_MAX = 8;
static const long BUFFER_SIZE = 1024;

static bool g_bQuit = false;

/*---------------------------------------------------------------------------*/
//
SocketTcpServer::SocketTcpServer()
: m_eStatus(E_SERVER_STATUS_NONE)
, m_iServerFd(-1)
, m_th(0)
{
    memset(m_iClientFdList, 0, sizeof(m_iClientFdList));
}

/*---------------------------------------------------------------------------*/

SocketTcpServer::~SocketTcpServer()
{

}

/*---------------------------------------------------------------------------*/
// Init
void SocketTcpServer::init(const SocketReceiveMsgCallback& cb)
{
    SocketBase::init(cb);
}

/*---------------------------------------------------------------------------*/
// Start
bool SocketTcpServer::start()
{
    m_eStatus = E_SERVER_STATUS_NONE;

    int ret = pthread_create(&m_th, NULL, run, this);
    if (ret != 0) {
        printf("%s:%d start thread error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    return true;
}

/*---------------------------------------------------------------------------*/
// Stop
bool SocketTcpServer::stop()
{
    g_bQuit = true;
    int* thread_ret = NULL;
    pthread_join(m_th, (void**)&thread_ret);

    m_eStatus = E_SERVER_STATUS_NONE;
    return true;
}

/*---------------------------------------------------------------------------*/
// Send message
bool SocketTcpServer::send(const char* msg, int len)
{
    // Check status
    if (m_eStatus != E_SERVER_STATUS_READY) {
        printf("%s:%d status:%d error\n", __PRETTY_FUNCTION__, __LINE__, m_eStatus);
        return false;
    }

    // Send data
    for (int i = 0; i < CONNECT_CURRENT_MAX; i++) {
        if (m_iClientFdList[i] != 0) {
            int ret = ::send(m_iClientFdList[i], msg, len, 0);
            if (ret == -1) {
                printf("%s:%d send message to client(%d) error\n", __PRETTY_FUNCTION__, __LINE__, i);
            }
        }
    }

    printf("%s:%d send message:%s\n", __PRETTY_FUNCTION__, __LINE__, msg);
    return true;
}

/*---------------------------------------------------------------------------*/
// On receive message
bool SocketTcpServer::onReceive(const char* msg, int len)
{
    // Check status
    if (m_eStatus != E_SERVER_STATUS_READY) {
        printf("%s:%d status:%d error\n", __PRETTY_FUNCTION__, __LINE__, m_eStatus);
        return false;
    }

    printf("%s:%d receive message %s\n", __PRETTY_FUNCTION__, __LINE__, msg);

    // TODO:

    return true;
}

/*---------------------------------------------------------------------------*/
// Run
void* SocketTcpServer::run(void* arg)
{
    SocketTcpServer* pThis = (SocketTcpServer*)arg;
    pThis->startServer();

    return NULL;
}

/*---------------------------------------------------------------------------*/
// Start socket server
bool SocketTcpServer::startServer()
{
    printf("%s:%d\n", __PRETTY_FUNCTION__, __LINE__);
    m_eStatus = E_SERVER_STATUS_STARTING;

    // Local address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SOCKET_SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    bzero(&(server_addr.sin_zero), 8);

    // Create socket
    m_iServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_iServerFd == -1) {
        printf("%s:%d create socket error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    // Bind socket
    int bind_ret = bind(m_iServerFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_ret == -1) {
        printf("%s:%d bind socket error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    // Listen
    if (listen(m_iServerFd, BACKLOG) == -1) {
        printf("%s:%d listen error\n", __PRETTY_FUNCTION__, __LINE__);
        return false;
    }

    // FD set
    fd_set server_fd_set;
    int max_fd = -1;

    // Set timeout
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;

    while (1) {
        if (g_bQuit) {
            break;
        }

        FD_ZERO(&server_fd_set);
        FD_SET(STDIN_FILENO, &server_fd_set);
        if (max_fd < STDIN_FILENO) {
            max_fd = STDIN_FILENO;
        }

        // Server socket
        FD_SET(m_iServerFd, &server_fd_set);
        if (max_fd < m_iServerFd) {
            max_fd = m_iServerFd;
        }

        // Client connect
        for (int i = 0; i < CONNECT_CURRENT_MAX; i++) {
            if (m_iClientFdList[i] != 0) {
                FD_SET(m_iClientFdList[i], &server_fd_set);
                if (max_fd < m_iClientFdList[i]) {
                    max_fd = m_iClientFdList[i];
                }
            }
        }

        // Select
        int ret = select(max_fd + 1, &server_fd_set, NULL, NULL, &tv);
        if (ret < 0 ) {
            printf("%s:%d select error\n", __PRETTY_FUNCTION__, __LINE__);
            continue;
        }
        else if (ret == 0) {
            printf("%s:%d select time out\n", __PRETTY_FUNCTION__, __LINE__);
            continue;
        }
        else {
            m_eStatus = E_SERVER_STATUS_READY;

            if (FD_ISSET(m_iServerFd, &server_fd_set)) {
                // Client connecting
                struct sockaddr_in client_address;
                socklen_t address_len;
                int client_socket_fd = accept(m_iServerFd, (struct sockaddr *)&client_address, &address_len);
                printf("%s:%d new connection client_socket_fd = %d\n", __PRETTY_FUNCTION__, __LINE__, client_socket_fd);
                if (client_socket_fd > 0) {
                    int insert_index = -1;
                    for (int i = 0; i < CONNECT_CURRENT_MAX; i++) {
                        if (m_iClientFdList[i] == 0) {
                            insert_index = i;
                            m_iClientFdList[insert_index] = client_socket_fd;
                            break;
                        }
                    }

                    if (insert_index != -1) {
                        printf("%s:%d new client(%d) connected successful %s:%d\n",
                            __PRETTY_FUNCTION__, __LINE__,
                            insert_index,
                            inet_ntoa(client_address.sin_addr),
                            ntohs(client_address.sin_port));
                    }
                }
                else {
                    char error_msg[] = "Server connection max, cannot jion!\n";
                    ::send(client_socket_fd, error_msg, strlen(error_msg), 0);
                    printf("%s:%d connection max, new client cannot join in %s:%d\n",
                        __PRETTY_FUNCTION__, __LINE__,
                        inet_ntoa(client_address.sin_addr),
                        ntohs(client_address.sin_port));
                }
            }
        }

        for (int i = 0; i < CONNECT_CURRENT_MAX; i++) {
            if (m_iClientFdList[i] == 0) {
                continue;
            }

            if (FD_ISSET(m_iClientFdList[i], &server_fd_set)) {
                // Receive message from a cilent
                char recv_msg[BUFFER_SIZE] = { 0 };
                long byte_num = recv(m_iClientFdList[i], recv_msg, BUFFER_SIZE, 0);
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
                    printf("%s:%d client %d receive message error\n", __PRETTY_FUNCTION__, __LINE__, i);
                }
                else {
                    FD_CLR(m_iClientFdList[i], &server_fd_set);
                    m_iClientFdList[i] = 0;
                    printf("%s:%d client %d exit\n", __PRETTY_FUNCTION__, __LINE__, i);
                }
            }
        }
    }

    printf("%s:%d socket server exit\n", __PRETTY_FUNCTION__, __LINE__);
    return true;
}

/*---------------------------------------------------------------------------*/
}

/*---------------------------------------------------------------------------*/
/*EOF*/
