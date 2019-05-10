#include "rshellbase.hpp"
#include <sys/wait.h>
#include<sys/types.h>
#include<cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

bool ExeArgu::Operate()
{
	pid_t pid;
	pid = fork();

	if (pid < 0) {
		perror("fork creates child process error!");
		exit(0);
	}
	else if (pid == 0) {
		cout << "fork creates child process successfully!" << endl;
		cout << "It's in child process!" << endl;
		sleep(4);

		char *argv[] = { this->argu.c_str(),NULL };
		char* path = this->exe.c_str();

		int a = execvp(path, argv);
		if (a == -1) {
			perror("execution fails!");
			return false;
		}
		else {
			return true;
		}
		exit(0);
	}
	else {
		waitpid(pid, NULL, 0);
		cout << "child process releases successfully!" << endl;
		cout << "It's in parent process!" << endl;
	}
	exit(0);
}

string ExeArgu::getExe()
{
	return this->exe;
}

string ExeArgu::getArgu()
{
	return this->argu;
}
