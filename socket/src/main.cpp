/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include <stdio.h>
#include <unistd.h>

#include "SocketServer.h"
#include "SocketClient.h"

static const char s_help_message[] = "\
input: [cammend][option]\n\
    server: start a socket server\n\
    client: start a socket client";

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
        || (strcmp(argv[1], "server") != 0
        && strcmp(argv[1], "client") != 0)) {
        printf("%s\n", s_help_message);
        return -1;
    }

    sockettest::SocketBase* pSocket = nullptr;
    if (strcmp(argv[1], "server") == 0) {
        pSocket = new sockettest::SocketServer();
    }
    else if (strcmp(argv[1], "client") == 0) {
        pSocket = new sockettest::SocketClient();
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
