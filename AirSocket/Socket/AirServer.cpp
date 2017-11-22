//
//  AirBSDServer.cpp
//  Socket
//
//  Created by 彭浩 on 16/4/28.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#include "AirServer.h"
namespace AirCpp {
    Server::~Server() {
        if (_pListener) {
            delete _pListener;
        }
        if (m_pListenThread) {
            delete m_pListenThread;
        }
        for (const auto kvp : m_mapConnections) {
            delete kvp.second;
        }
    }
    
    void Server::startListen() {
        _pListener = new AirCpp::Listener(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_pListener->init(m_uiPort, m_uiBackLog) == 0 ) {
            printf("pListener->init \r\n");
            _pListener->startListen([&](Connection *pConnection) {
                m_pSessionManager->create(pConnection);
            });
            printf("pListener->startListen \r\n");
        } else {
            perror("listen port failed!");
            exit(0);
        }
    }
    
    Server::Server(unsigned short usPort, unsigned int uiBacklog):
    m_uiPort(usPort),
    m_uiBackLog(uiBacklog),
    _pListener(nullptr){
        m_pListenThread = new Thread();
        m_pListenThread->init();
    }
    
    Server *Server::Create(unsigned short usPort, unsigned int uiBacklog, SessionManager *pSessionManager) {
        Server *server = new Server(usPort, uiBacklog);
        server->m_pSessionManager = pSessionManager;
        return server;
    }
    
    void Server::run() {
        startListen();
    }
}
