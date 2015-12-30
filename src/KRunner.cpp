#include "KRunner.hpp"
#include "ofMain.h"

KRunner::KRunner()
{
}


KRunner::~KRunner()
{
}

void KRunner::run(std::string ip, std::string port)
{
	ofLogNotice("KRunner", "starting kag for server: " + ip + ":" + port);
#ifdef _WIN32
	ofLogNotice("KRunner", "OS = Windows :(");

	std::string path = "C:\\Program Files (x86)\\Steam\\Steam.exe";
	std::wstring wpath(path.begin(), path.end());

	std::string args = "-applaunch 219830 -join " + ip + ":" + port;
	std::wstring wargs(args.begin(), args.end());

	ofLogNotice("KRunner", path + " " + args);

	ShellExecute(NULL, L"open", wpath.c_str(),
		wargs.c_str(), NULL, SW_NORMAL);

#elif __APPLE__
#elif __linux__
#endif
}
