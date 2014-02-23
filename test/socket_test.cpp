#include "test.h"
#include "zsocket.h"
#include "zthread.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#if PLATFORM == WINDOWS
    #include <winsock2.h>
#elif PLATFORM == LINUX
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

void sendGrams(ZSocket *sock){
    zu64 count = 0;
    //ZAddress addr(127,0,0,1, 8998);
    ZAddress addr(192,168,1,38, 8998);

    while(true){
        ZString str = "hello world out there! ";
        str << ZString::ItoS(count);
        ZBinary data((unsigned char *)str.cc(), str.size());
        data.data().push(0);
        LOG(data.size() << " " << (char *)data.raw());
        sock->send(addr, data);
        ++count;
        usleep(500000);
    }
}

void *clientThread(void *zarg){
    LOG("Sending...");
    sendGrams((ZSocket*)((ZThreadArg*)zarg)->arg);
    return NULL;
}

int socket_test(){
    LOG("=== Socket Test...");
    if(!ZSocket::InitializeSockets()){
        LOG("Init Error");
        return 1;
    }
    ZSocket sock;
    if(!sock.open(8998)){
        ELOG("Socket Open Fail");
        return 2;
    }

    sendGrams(&sock);

    sock.close();
    ZSocket::ShutdownSockets();
    return 0;
}

void receivedGram(ZAddress addr, ZBinary data){
    LOG("packet " << addr.a() << "." << addr.b() << "." << addr.c() << "." << addr.d() << ":" << addr.port() << " (" << data.size() << "): " << (char *)data.raw());
}

int socketserver_test(){
    LOG("=== Socket Server Test...");
    if(!ZSocket::InitializeSockets()){
        LOG("Init Error");
        return 1;
    }
    ZSocket sock;
    if(!sock.open(8998)){
        ELOG("Socket Open Fail");
        return 2;
    }

    LOG("Listening...");
    sock.listen(receivedGram);

    sock.close();
    ZSocket::ShutdownSockets();
    return 0;
}
