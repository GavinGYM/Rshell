#include <sys/wait.h>
#include<sys/types.h>
#include<cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
	pid_t pid;
	pid=fork();
	
	if ( pid < 0){
		cout << "fork creates child process error!" << endl;
		exit(0);
	}
	else if ( pid == 0){
		cout << "fork creates child process successfully!" << endl;
		cout << "It's in child process!" << endl;
		sleep (4);
		
		char *argv[]={"-a",NULL};
		char* path = "ls";
		
		int a = execvp(path,argv);
		if( a == -1 ){
			cout << "execution fails!" << endl;
		}
		exit(0);
	}	
	else{
		waitpid(pid,NULL,0);
		cout << "child process releases successfully!" << endl;
		cout << "It's in parent process!" << endl;
	}
	exit(0);
}
