/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include <stdio.h>
#include <unistd.h>

#include "SocketTcpServer.h"
#include "SocketTcpClient.h"
#include "SocketUdpMulticast.h"
#include "SocketUdpReceiver.h"

static const char s_help_message[] = "\
input: [cammend][option]\n\
    tcpserver: start a tcp server \n\
    tcpclient: start a tcp client \n\
    udpmulticast: start a UDP multicast \n\
    udpreceiver: start a UDP receiver \n\
    ";

/*---------------------------------------------------------------------------*/
// Callback
class ReceiveMsgCallback : public sockettest::SocketReceiveMsgCallback
{
public:
    void onReceiveMsg(char* msg, int len)
    {
        printf("main receive msg:%s, len:%d\n", msg, len);
    }
};

/*---------------------------------------------------------------------------*/
// Main
int main(int argc, char** argv)
{
    bool bOutputMessage = false;
    if (argc != 2
        || (strcmp(argv[1], "tcpserver") != 0
        && strcmp(argv[1], "tcpclient") != 0
        && strcmp(argv[1], "udpmulticast") != 0
        && strcmp(argv[1], "udpreceiver") != 0)) {
        printf("%s\n", s_help_message);
        return -1;
    }

    sockettest::SocketBase* pSocket = nullptr;
    if (strcmp(argv[1], "tcpserver") == 0) {
        pSocket = new sockettest::SocketTcpServer();
    }
    else if (strcmp(argv[1], "tcpclient") == 0) {
        pSocket = new sockettest::SocketTcpClient();
    }
    else if (strcmp(argv[1], "udpmulticast") == 0) {
        pSocket = new sockettest::SocketUdpMulticast();
    }
    else if (strcmp(argv[1], "udpreceiver") == 0) {
        pSocket = new sockettest::SocketUdpReceiver();
    }
    else {
        return -1;
    }

    // Init socket
    ReceiveMsgCallback cb;
    pSocket->init(cb);

    // Start socket
    pSocket->start();

    char input[1024] = { 0 };

    // Wait
    while (1) {
        scanf("%s", input);

        if (strcmp(input, "q") == 0) {
            break;
        }

        pSocket->send(input, strlen(input));
    }

    // Quit
    if (pSocket != nullptr) {
        pSocket->stop();
        delete pSocket;
    }

    // Return
    return 0;

    // Thank you
}

/*---------------------------------------------------------------------------*/
 /*EOF*/
