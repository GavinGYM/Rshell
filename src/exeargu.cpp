#include "rshellbase.hpp"
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

bool ExeArgu::Operate()
{ 	
	//io redirection part
	if (this->argu.find('>') != string::npos || this->argu.find('<') != string::npos || this->argu.find('|') != string::npos && this->argu.find("||") == string::npos) {
		vector<Connector*> connector;
		vector<ExeArgu*> exeargu;
		vector<Command*> command;

		string subinput;
		subinput = this->exe + ' ' + this->argu;
		while (subinput.find('|') != string::npos || subinput.find('>') != string::npos || subinput.find('<') != string::npos) {
			int pos = INT_MAX;
			char con;
			string cmd;
			if (subinput.find('<') != string::npos) {
				pos = subinput.find('<');
				con = '<';
			}
			if (subinput.find('>') != string::npos && (subinput.find('>') < pos)) {
				pos = subinput.find('>');
				con = '>';
			}
			if (subinput.find('|') != string::npos && (subinput.find('|') < pos)) {
				pos = subinput.find('|');
				con = '|';
			}

			if (con == '<') {
				cmd = subinput.substr(0, pos - 1);
				subinput = subinput.substr(pos + 2, subinput.size() - pos - 1);
			}
			else if (con == '>') {
				if (subinput.at(subinput.find('>') + 1) == '>') {
					con = '^'; // '^' stand for ">>"
					cmd = subinput.substr(0, pos - 1);
					subinput = subinput.substr(pos + 3, subinput.size() - pos - 1);
				}
				else {
					cmd = subinput.substr(0, pos - 1);
					subinput = subinput.substr(pos + 2, subinput.size() - pos - 1);
				}
			}
			else if (con == '|') {
				cmd = subinput.substr(0, pos - 1);
				subinput = subinput.substr(pos + 2, subinput.size() - pos - 1);
			}

			string argu;
			string exe;
			if (cmd.find(" ") != string::npos) {
				argu = cmd.substr(cmd.find(" ") + 1, cmd.size() - 1);
				if (argu.at(0) == '\"'&&argu.at(argu.size() - 1) == '\"') {
					argu = argu.substr(1, argu.size() - 2);
				}
				else if (argu.at(0) == '\"'&&argu.at(argu.size() - 2) == '\"'&&argu.at(argu.size() - 1) == ')') {
					argu = argu.substr(1, argu.size() - 3);
					argu.append(")");
				}
			}
			else {
				argu = "";
			}
			
			//This is for the case we have a comment
			if (argu.find("#") != string::npos) {
				argu = argu.substr(0, argu.find("#"));
			}
			exe = cmd.substr(0, cmd.find(" "));

			ExeArgu *newea = new ExeArgu(exe, argu);
			exeargu.push_back(newea);

			Connector *newcon;
			newcon = new Connector(con);
			connector.push_back(newcon);

			Command *newcom = new Command(newea, newcon);
			command.push_back(newcom);
		}
		//this is for the last command which don't have a connector following it
		string cmd;
		cmd = subinput;
		string argu;
		string exe;
		if (cmd.find(" ") != string::npos) {
			argu = cmd.substr(cmd.find(" ") + 1, cmd.size() - 1);
			if (argu.at(0) == '\"'&&argu.at(argu.size() - 1) == '\"') {
				argu = argu.substr(1, argu.size() - 2);
			}
			else if (argu.at(0) == '\"'&&argu.at(argu.size() - 2) == '\"'&&argu.at(argu.size() - 1) == ')') {
				argu = argu.substr(1, argu.size() - 3);
				argu.append(")");
			}
		}
		else {
			argu = "";
		}
		if (argu.find("#") != string::npos) {
			argu = argu.substr(0, argu.find("#"));
		}
		exe = cmd.substr(0, cmd.find(" "));

		ExeArgu *newea = new ExeArgu(exe, argu);
		exeargu.push_back(newea);
		Connector *newcon = new Connector('.');
		connector.push_back(newcon);

		Command *newcom = new Command(newea, newcon);
		command.push_back(newcom);
		
		//The integration has finished
		//Now start the 
		if(command.size() == 2){
			if(connector.at(0)->GetSign()=='<')
			{	
				pid_t pid,pr;
				pid = fork();

				if (pid < 0) {
					perror("fork creates child process error!");
					exit(0);
				}
				else if (pid == 0) {
					if(exeargu.at(0)->getArgu() == ""){
						char *argv[] = { const_cast<char*>(exeargu.at(0)->getExe().c_str()),NULL };
						char* path = const_cast<char*>(exeargu.at(0)->getExe().c_str());
						//------------------------------------------------------------------------------
						int savestdin = dup(0);
						int in=open(exeargu.at(1)->getExe().c_str(),O_RDONLY,0777); //0777表示文件所有者   该文件用户组     其他用户都有可读可写可执行权限
			        		dup2(in,0);
						//------------------------------------------------------------------------------
						int a = execvp(path, argv);
						dup2(savestdin,0);
						if (a == -1) {
							perror("execution fails!");
							exit(1);				
						}
						else {
							exit(0);
						}	
					}
					else{
						char *argv[] = { const_cast<char*>(exeargu.at(0)->getExe().c_str()), const_cast<char*>(exeargu.at(0)->getArgu().c_str()),NULL };
						char* path = const_cast<char*>(exeargu.at(0)->getExe().c_str());
						//------------------------------------------------------------------------------
						int savestdin = dup(0);
						int in=open(exeargu.at(1)->getExe().c_str(),O_RDONLY,0777); //0777表示文件所有者   该文件用户组     其他用户都有可读可写可执行权限
			        		dup2(in,0);
						//------------------------------------------------------------------------------
						int a = execvp(path, argv);
						dup2(savestdin,0);
						if (a == -1) {
							perror("execution fails!");
							exit(1);	
						}
						else {
							exit(0);
						}
					}
				}
				else {
					int status;
					pr = waitpid(pid, &status, 0);
					if(pr == pid){
						status = WEXITSTATUS(status);
						if(status == 1){
							return false;
						}
						else if(status == 0) {
							return true;
						}
					}
					else{
						cout << "someerror occured" << endl;
						return false;
					}
				}
			}

			else if(connector.at(0)->GetSign()=='>')
			{	
				pid_t pid,pr;
				pid = fork();

				if (pid < 0) {
					perror("fork creates child process error!");
					exit(0);
				}
				else if (pid == 0) {
					if(exeargu.at(0)->getArgu() == ""){
						char *argv[] = { const_cast<char*>(exeargu.at(0)->getExe().c_str()),NULL };
						char* path = const_cast<char*>(exeargu.at(0)->getExe().c_str());
						//------------------------------------------------------------------------------
						int savestdout = dup(1);
			    			int in=open(exeargu.at(1)->getExe().c_str(),O_CREAT|O_TRUNC|O_WRONLY,0777);
			    			dup2(in,1);
						//------------------------------------------------------------------------------
						int a = execvp(path, argv);
						dup2(savestdout,1);
						if (a == -1) {
							perror("execution fails!");
							exit(1);				
						}
						else {
							exit(0);
						}	
					}
					else{
						char *argv[] = { const_cast<char*>(exeargu.at(0)->getExe().c_str()), const_cast<char*>(exeargu.at(0)->getArgu().c_str()),NULL };
						char* path = const_cast<char*>(exeargu.at(0)->getExe().c_str());
						//------------------------------------------------------------------------------
						int savestdout = dup(1);
			    			int in=open(exeargu.at(1)->getExe().c_str(),O_CREAT|O_TRUNC|O_WRONLY,0777);
			    			dup2(in,1);
						//------------------------------------------------------------------------------
						int a = execvp(path, argv);
						dup2(savestdout,1);
						if (a == -1) {
							perror("execution fails!");
							exit(1);	
						}
						else {
							exit(0);
						}
					}
				}
				else {
					int status;
					pr = waitpid(pid, &status, 0);
					if(pr == pid){
						status = WEXITSTATUS(status);
						if(status == 1){
							return false;
						}
						else if(status == 0) {
							return true;
						}
					}
					else{
						cout << "someerror occured" << endl;
						return false;
					}
				}
			}

			else if(connector.at(0)->GetSign()=='^')
			{	
				pid_t pid,pr;
				pid = fork();

				if (pid < 0) {
					perror("fork creates child process error!");
					exit(0);
				}
				else if (pid == 0) {
					if(exeargu.at(0)->getArgu() == ""){
						char *argv[] = { const_cast<char*>(exeargu.at(0)->getExe().c_str()),NULL };
						char* path = const_cast<char*>(exeargu.at(0)->getExe().c_str());
						//------------------------------------------------------------------------------
						int savestdout = dup(1);
						int in=open(exeargu.at(1)->getExe().c_str(),O_WRONLY|O_APPEND);
			    			dup2(in,1);
						//------------------------------------------------------------------------------
						int a = execvp(path, argv);
						dup2(savestdout,1);
						if (a == -1) {
							perror("execution fails!");
							exit(1);				
						}
						else {
							exit(0);
						}	
					}
					else{
						char *argv[] = { const_cast<char*>(exeargu.at(0)->getExe().c_str()), const_cast<char*>(exeargu.at(0)->getArgu().c_str()),NULL };
						char* path = const_cast<char*>(exeargu.at(0)->getExe().c_str());
						//------------------------------------------------------------------------------
						int savestdout = dup(1);
						int in=open(exeargu.at(1)->getExe().c_str(),O_WRONLY|O_APPEND);
			    			dup2(in,1);
						//------------------------------------------------------------------------------
						int a = execvp(path, argv);
						dup2(savestdout,1);
						if (a == -1) {
							perror("execution fails!");
							exit(1);	
						}
						else {
							exit(0);
						}
					}
				}
				else {
					int status;
					pr = waitpid(pid, &status, 0);
					if(pr == pid){
						status = WEXITSTATUS(status);
						if(status == 1){
							return false;
						}
						else if(status == 0) {
							return true;
						}
					}
					else{
						cout << "someerror occured" << endl;
						return false;
					}
				}
			}
		}
		return true;
	}
	
	// This part is before assignment 3
	if(this->exe == "["){
		this->exe = "test";
		if(this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) == ' '){
			this->argu = this->argu.substr(0,this->argu.size() - 2);
		}
		else if( this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) != ' '){
			this->argu = this->argu.substr(0,this->argu.size() - 1);
		}
	}
	else if(this->exe.at(0) == '['){
		if(this->exe.at(this->exe.size()-1) == ']'){
			this->argu = this->exe.substr(1,this->exe.size() - 2);
			this->exe = "test";
		}
		else{
			this->argu.insert(0," ");
			this->argu.insert(0,this->exe.substr(1,this->exe.size()-1));
			this->exe = "test";
			if(this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) == ' '){
				this->argu = this->argu.substr(0,this->argu.size() - 2);
			}
			else if( this->argu.at(this->argu.size() - 1) == ']' && this->argu.at(this->argu.size() - 2) != ' '){
				this->argu = this->argu.substr(0,this->argu.size() - 1);
			}
		}
	}
	if(this->exe == "test"){
		string flag;
		if(this->argu.at(0)!='-'){
			flag = "-e";
		}
		else{
			flag = this->argu.substr(0,2);
			this->argu = this->argu.substr(3,this->argu.size()-3);
		}
		

		struct stat buf;
		if(flag=="-e")
		{
			int status = stat(const_cast<char*>(this->argu.c_str()),&buf);
			if(status==0)
			{
				cout<<"(True)"<<endl;
				return true;
			}
			else
			{
				cout<<"(False)"<<endl;
				return false;
			}  
		}
		else if(flag=="-f"){
			int status = stat(const_cast<char*>(this->argu.c_str()),&buf);
			if(status!=0) {
				cout<<"(False)"<<endl; 
				return false;
			}
			if(S_ISREG(buf.st_mode)) {
				cout<<"(True)"<<endl; 
				return true;
			}
			else {
				cout<<"(False)"<<endl; 
				return false;
			}	
		}
		else if(flag=="-d"){
			int status = stat(const_cast<char*>(this->argu.c_str()),&buf);
			if(status!=0) {
				cout<<"(False)"<<endl; 
				return false;
			}
			if(S_ISDIR(buf.st_mode)) {
				cout<<"(True)"<<endl;
				return true;
			}
			else {
				cout<<"(False)"<<endl; 
				return false;
			}
		}
		else {
			cout << "flag doesn't exist, please try again(-e, -f or -d)" << endl;
			return false;
		}
     	}
	else{
		pid_t pid,pr;
		pid = fork();

		if (pid < 0) {
			perror("fork creates child process error!");
			exit(0);
		}
		else if (pid == 0) {
			if(this->argu == ""){
				char *argv[] = { const_cast<char*>(this->exe.c_str()),NULL };
				char* path = const_cast<char*>(this->exe.c_str());
				int a = execvp(path, argv);
				if (a == -1) {
					perror("execution fails!");
					exit(1);				
				}
				else {
					exit(0);
				}	
			}
			else{
				char *argv[] = { const_cast<char*>(this->exe.c_str()), const_cast<char*>(this->argu.c_str()),NULL };
				char* path = const_cast<char*>(this->exe.c_str());
				int a = execvp(path, argv);
				if (a == -1) {
					perror("execution fails!");
					exit(1);	
				}
				else {
					exit(0);
				}
			}
		}
		else {
			int status;
			pr = waitpid(pid, &status, 0);
			if(pr == pid){
				status = WEXITSTATUS(status);
				if(status == 1){
					return false;
				}
				else if(status == 0) {
					return true;
				}
			}
			else{
				cout << "someerror occured" << endl;
				return false;
			}
		}
	}
}

string ExeArgu::getExe()
{
	return this->exe;
}

string ExeArgu::getArgu()
{
	return this->argu;
}

vector<int> ExeArgu::getLeftP()
{
	return this->leftP;
}

vector<int> ExeArgu::getRightP()
{
	return this->rightP;
}

void ExeArgu::setLeftP(int i)
{
	leftP.push_back(i);
}

void ExeArgu::setRightP(int i)
{
	rightP.push_back(i);
}

void ExeArgu::setExeL()
{
	if(exe.at(0) == '('){
		exe = exe.substr(1 , exe.size()-1);
	}
}

void ExeArgu::setExeR()
{
	if (exe.at(exe.size() - 1) == ')') {
		exe = exe.substr(0, exe.size() - 1);
	}
}

void ExeArgu::setArgu()
{
	if (argu.at(argu.size() - 1) == ')') {
		argu = argu.substr(0, argu.size() - 1);
	}
}
