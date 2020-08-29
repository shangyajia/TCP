#include "YJTcpClient.h"

#include <thread>

int main()
{
	//YJTcpClient client;
	//client.createSocket("127.0.0.1", 3689);
	//client.sendMsg("HelloWorld...");

	
	const int length = 63;
	YJTcpClient* pc[length];

	for (size_t i = 0; i < length; i++)
	{
		pc[i] = new YJTcpClient;
		pc[i]->createSocket("127.0.0.1", 3689);
	}

	char msg[] = "JIbX7gj5CYRtE7FfVqVsvAUbhNVpeYf9NM7fpPKLykxcvROjzmzZUzjrVxYubMo7gbU77KJHAzlqxGhgHCPnk9qT3ihrdXx4gNj18OaOwwWouzbChrvHIjkA6M4kKJBfQ77b6HdJw1avf2xgAUalWEtgAFyJAIwtbmpIaL67yxqa6wNBLmnBhxj6at8BaQgH2uJiImMfnzyp4GJCN0MJwPOfBDgp63qlda33YCufPuyI4wiD0f2xOvpmw2d3QAiPXiNBXqqTmkDSc6K9PGgWZAmHEVDm9vHFAj4YXDU5CbvveAYQuL5AX2dyypWEOUQhmhfG47HDllKgO4sL7nOI6iOc6ljzvmNGoKvZlE02s7uZHIGTkPYf5jr7IXRB27UKH4eIRxavTOFGrFShigcHVLQierG1iHj7IcMt7VSPrF8wbJ8eyKwLyuRJL4IVRzw9FckWR5T8mWjUQWh2rwyq7KZUjxMZL8oMtaOzF1sKbioQU7z5h7xKO1xvSl7nLywYzjjPPPsxcEoxSOuNME4kK43nCabdJRbbxyAobMyH59h9Q0cjHtrVabC4I3yCUU8DfJyFRV5KPpMFHGXqH7R7cU9QQXDnNc2KL9zn7G99uUZ6w7Iv4Xkvu0u9YJGoXh0Dn4I6MlYyMuyXC9lNwJQT3niYm1OOtg2DE1czjphEifXrD1sWrx41xJekdwlPfi06wHW2nj1mXaqvaUe7VA9xBsqUm1wIyjMTjz5JhYZdlMRd5qbHHuyZMnojPLsIoBJph6Uqb399UNreMH05SbdFLsYppqA4F5FpwHYOfzLCdFuBI5YFEwmXG747xgKhh6N0dESCVDpZJninkR4cMLjahiHRqCA43ESKuX2bwnp9VIHwBAisVL9O5hB0v1TbtWRUXUuRfdn0ZnVwc8zxlAtGsBZycDAnbm8q39UrKI02v3qM1BUoA6iyF4syrrUZZ1hsrfD6aA7b3bvgZyVchcUoIiWVfC0NbeF0UWy1NRFM";

	bool bRun = true;
	while (bRun)
	{
		for (size_t i = 0; i < length; i++)
		{			
			pc[i]->onSelect();
			pc[i]->sendMsg(msg);
		}
	}
	
	return 0;
}