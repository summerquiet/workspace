# 使用CM的编译环境

## build

使用Navi编写的CM修改的一个快捷使用cmake的工具
编译工程前，需要在build/目录下面执行

``` TXT
#build/ cmake .
#build/ make
```

## out

编译过程中生成的中间文件和最后的可执行文件在这个目录下

## src

用于放置代码和编译文件

### /Functions

#### TCP

SocketTcpServer & SocketTcpClient  
这是2使用TCP连接的多客户端实例代码

#### UDP

SocketUdpMulticast & SocketUdpReceiver  
这是2个使用UDP广播方法进行收发数据的实例代码

### main.cpp

是main入口

### main.cm

是本工程的工程文件
