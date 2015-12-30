#ifndef K_RUNNER_H
#define	K_RUNNER_H

#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

class KRunner
{
public:
	KRunner();
	~KRunner();

	static void run(std::string ip, std::string port);
};


#endif // !K_RUNNER_H
