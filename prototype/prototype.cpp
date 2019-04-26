#include <sys/wait.h>
#include<sys/types.h>
#include<cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
	pid_t pid;
	pid=fork();
	char *argv[]={"-a",NULL};
	char* path = "ls";
	waitpid(pid,NULL,0);
	if( pid == 0 ){
		execvp(path,argv);
		exit(0);
	}
	return 0;
}
