/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_SOCKET_BASE_H
 #define CXX_SOCKET_BASE_H

/*---------------------------------------------------------------------------*/
// Include files

#include <list>

/*---------------------------------------------------------------------------*/
// Namespace
namespace sockettest
{

/*---------------------------------------------------------------------------*/
// Class define

/**
 * @class SocketReceiveMsgCallback
 * 
 * @brief Handle socket receive message callback class
 * 
 */
class SocketReceiveMsgCallback
{
public:
    /**
     * @brief On receive message
     * 
     * @param msg 
     * @param len 
     */
    virtual void onReceiveMsg(char* msg, int len) {}
};

/**
 * @class SocketBase
 * 
 * @brief Handle socket class
 * 
 */
class SocketBase
{
public:
    /**
     * @brief Construct a new Socket Server object
     */
    SocketBase()
    : m_cCbList()
    {
    }

    /**
     * @brief Destroy the Socket Server object
     */
    virtual ~SocketBase() {}

    /**
     * @brief init
     * 
     */
    virtual void init(const SocketReceiveMsgCallback& cb)
    {
        m_cCbList.push_back(cb);
    };

    /**
     * @brief init
     * 
     */
    virtual bool start() = 0;

    /**
     * @brief init
     * 
     */
    virtual bool stop() = 0;

    /**
     * @brief Send message
     * 
     * @param msg 
     * @param len 
     * @return true 
     * @return false 
     */
    virtual bool send(const char* msg, int len) = 0;

    /**
     * @brief On receive message
     * 
     * @param msg 
     * @param len 
     * @return true 
     * @return false 
     */
    virtual bool onReceive(const char* msg, int len) = 0;

protected:
    // Members
    std::list<SocketReceiveMsgCallback>     m_cCbList;

private:
    /**
     * @brief Copy constructor(Forbidden)
     */
    SocketBase(const SocketBase&);

    /**
     * @brief Operator =(Forbidden)
     */
    SocketBase& operator =(const SocketBase&);

};

/*---------------------------------------------------------------------------*/
// Namespace
}

/*---------------------------------------------------------------------------*/
#endif // CXX_SOCKET_BASE_H
/*EOF*/
