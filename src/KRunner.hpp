//
//  KAsyncLoader.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 26/12/2015.
//
//

#ifndef KRunner_hpp
#define KRunner_hpp

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include <string>

class KRunner
{
public:
	KRunner();
	~KRunner();

	static void run(std::string ip, std::string port);
};

#endif