
#include "YJTcpClient.h"
YJTcpClient::YJTcpClient()
{
	_socket = INVALID_SOCKET;
	_initSocketEvn();
	memset(_buffer, 0, BUFFER_SIZE);
}

YJTcpClient::~YJTcpClient()
{
	WSACleanup();
}

void YJTcpClient::_initSocketEvn()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA data;
	int ret = WSAStartup(ver, &data);
	if (0 != ret)
	{
		std::cout << LINE << "WSAStartup error:" << ret << std::endl;
	}
}

bool YJTcpClient::createSocket(const char* ip,unsigned short port)
{
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == _socket)
	{
		std::cout << LINE << "create socket error:" << GetLastError() << std::endl;
		return false;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	int ret = connect(_socket, (const sockaddr*)&addr, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		std::cout << LINE << "connect socket error:" << GetLastError() << std::endl;
		return false;
	}
	std::cout << LINE << "connect socket sucessful..."<< std::endl;
	return true;
}

void  YJTcpClient::sendMsg(const char* message)
{
	int ret = send(_socket, message, (int)strlen(message), 0);
	if (ret <= 0)
	{
		std::cout << LINE << "sendMsg error:" << GetLastError() << std::endl;
	}
}

bool YJTcpClient::onSelect()
{
	fd_set fdRead;

	FD_ZERO(&fdRead);

	FD_SET(_socket,&fdRead);

	timeval t = { 1,0 };
	select(0, &fdRead, nullptr, nullptr, &t);

	if (FD_ISSET(_socket,&fdRead))
	{
		int rcvLen = recv(_socket, _buffer, BUFFER_SIZE, 0);
		_buffer[rcvLen + 1] = 0;
		if (rcvLen <= 0)
		{
			std::cout << LINE << "serve  disconnected..." <<  std::endl;
			return false;
		}
		else
		{
			//std::cout << LINE << "rcv serve message.length = " << strlen(_buffer) << std::endl;
			//std::cout << _buffer << std::endl;
		}		
	}
	return true;

}

void YJTcpClient::release()
{
	if (INVALID_SOCKET == _socket) return;
	closesocket(_socket);
}