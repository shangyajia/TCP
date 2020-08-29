#include "YJTcpServe.h"
YJTcpServe::YJTcpServe()	
{	
	_socket = INVALID_SOCKET;
	memset(_buffer, 0, BUFFER_SIZE);
	_initSocketEnv();
}

YJTcpServe::~YJTcpServe()
{
	WSACleanup();
}

void YJTcpServe::_initSocketEnv()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA data;
	int ret = WSAStartup(ver, &data);
	if ( 0 != ret)
	{
		std::cout << LINE << "WSAStartup error:" << ret << std::endl;
	}
}

void YJTcpServe::initSocket()
{
	if (_socket != INVALID_SOCKET)
	{
		std::cout << LINE << "realse old socket:" << (int)_socket << std::endl;
		realse();
	}

	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == _socket)
	{
		std::cout << LINE << "initSocket error:" << GetLastError() << std::endl;
		return;
	}
	std::cout << LINE << "server socket <"<< (int)_socket <<"> create successful..." << std::endl;
}

bool  YJTcpServe::bindSocket( unsigned short port, const char* ip)
{
	if (_socket == INVALID_SOCKET)
	{
		std::cout << LINE << "socket is invalid.forget inintsocket ? auto invoke initSocket." << std::endl;
		initSocket();
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = ip == nullptr ? INADDR_ANY : inet_addr(ip);
	int ret = bind(_socket, (const sockaddr*)&addr, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		std::cout << LINE << "bindSocket error:" << GetLastError() << std::endl;
		return false;
	}
	return true;
}

void  YJTcpServe::listenPort(int ncount)
{
	int ret = listen(_socket, ncount);
	if (INVALID_SOCKET == ret)
	{
		std::cout << LINE << "listen error:" << GetLastError() << std::endl;
		return;
	}
	std::cout << LINE << "waitting for client connect..." << std::endl;
}

void YJTcpServe::acceptConnet()
{
	sockaddr_in addr;
	int len = sizeof(sockaddr_in);
	SOCKET cSocket = accept(_socket, (sockaddr*)&addr, &len);

	if (cSocket != INVALID_SOCKET)
	{
		_clientContainer.push_back(cSocket);

		std::cout << LINE << "new client <socket:"<< (int)cSocket <<"> connected..." << std::endl;		
	}
}
void  YJTcpServe::sendMsg(SOCKET& cSocket, const char* message)
{
	int ret = send(cSocket, message, (int)strlen(message), 0);
	if (ret <= 0)
	{
		std::cout << LINE << "sendMsg client <socket:" << (int)cSocket << "> error..." << std::endl;
	}
}
void YJTcpServe::onSelect()
{
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExcept;

	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExcept);

	FD_SET(_socket, &fdRead);

	for (size_t i = 0,length = _clientContainer.size() ; i < length; i++)
	{
		FD_SET(_clientContainer[i], &fdRead);
	}

	timeval t = { 1,0 };
	select((int)_socket + 1, &fdRead, &fdWrite, &fdExcept, &t);

	if (FD_ISSET(_socket,&fdRead))
	{
		FD_CLR(_socket, &fdRead);
		acceptConnet();
	}

	for (size_t i = 0,length = fdRead.fd_count; i < length; i++)
	{
		rcvMsg(fdRead.fd_array[i]);
	}
}

void YJTcpServe::rcvMsg(SOCKET& cSocket)
{
	int rcvlength = recv(cSocket, _buffer, BUFFER_SIZE, 0);
	_buffer[rcvlength + 1] = 0;
	if (rcvlength <= 0)
	{
		std::cout << LINE << "client <socket:" << (int)cSocket << "> disConnect..." << std::endl;
		auto it = find(_clientContainer.begin(), _clientContainer.end(), cSocket);
		_clientContainer.erase(it);
	}
	else
	{
		//std::cout << LINE << " rcv <socket:" << (int)cSocket << "> message,length:" << strlen(_buffer)  <<std::endl;
		//std::cout << _buffer << std::endl;

		char buffer[1024] = { 0 };
		strcpy_s(buffer, strlen("rcv your message:")+1, "rcv your message:");
		strcpy_s(buffer + strlen("rcv your message:"), strlen(_buffer)+1, _buffer);

		sendMsg(cSocket, buffer);
		
	}
}

void YJTcpServe::realse()
{
	if (_socket == INVALID_SOCKET) return;

	closesocket(_socket);
	_socket = INVALID_SOCKET;

	_clientContainer.clear();	
}