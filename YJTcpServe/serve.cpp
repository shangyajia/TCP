
#include <iostream>
#include "YJTcpServe.h"

int main()
{
	YJTcpServe serve;
	serve.initSocket();
	serve.bindSocket(3689);
	serve.listenPort();
	while (true)
	{
		serve.onSelect();

	}
	return 0;
}