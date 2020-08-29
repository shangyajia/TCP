#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>

#include <iostream>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#define LINE   "[file:"<< __FILE__ <<",line:"<<__LINE__<<"] "
#else
#define LINE   "[line:"<<__LINE__<<"] "
#endif // _DEBUG

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10240
#endif // !BUFFER_SIZE



class YJTcpServe
{
public:
	YJTcpServe();
	virtual ~YJTcpServe();
	void initSocket();
	bool bindSocket(unsigned short port, const char* ip = nullptr);
	void listenPort(int ncount = 5);
	void acceptConnet();
	void onSelect();
	void rcvMsg(SOCKET& cSocket);
	void sendMsg(SOCKET& cSocket,const char* message);
	void realse();
private:
	void _initSocketEnv();//初始化 socket 环境
private:
	SOCKET _socket;
	std::vector<SOCKET> _clientContainer;
	char _buffer[BUFFER_SIZE];
};

