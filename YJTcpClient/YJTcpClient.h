#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>

#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#define LINE   "[file:"<< __FILE__ <<",line:"<<__LINE__<<"] "
#else
#define LINE   "[line:"<<__LINE__<<"] "
#endif // _DEBUG

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10240
#endif // !BUFFER_SIZE

class YJTcpClient
{
public:
	YJTcpClient();
	virtual ~YJTcpClient();
	bool createSocket(const char* ip, unsigned short port);
	bool onSelect();
	void sendMsg(const char* message);
	void release();
	
private:
	void _initSocketEvn();
private:
	SOCKET _socket;
	char _buffer[BUFFER_SIZE];
	char _bufferHandle[BUFFER_SIZE * 10];
};

