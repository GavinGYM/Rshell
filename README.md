# CS 100 Programming Project
Spring 2019

Yiming Guo, SID:X670427, NetID: yguo111, gavin-gym@foxmail.com

Yulin Liang, SID:X671565, NetID: ylian089, yulin66728@gmail.com
# Introduction
This is a command shell called rshell in C++ which is made by Yulin Liang and Yiming Guo, and it is capable of performing the following steps:

1.	Print a command prompt (e.g. `$`)
2.	Read in a line of command(s) (and connector(s)) from standard input
>The connector is an optional way you can run multiple commands at once. If a command is followed by ;, then the next command is always >executed; if a command is followed by &&, then the next command is executed only if the first one succeeds; if a command is followed by >||, then the next command is executed only if the first one fails. 
3.	Execute the appropriate commands using fork, execvp, and waitpid

We designed this program by using composite pattern.

Here's a brief overview of how the inputs are ingested, transformed into classes and structures, and processed.

After we get the input from user, we paseed it to an Rshellbase object. This Rshellbase object will use the Disintegrate function to disintegrate the string, and we will create a ExeArgu object with the executable and argumentlist part of the string, and create a Connector object with the connector part of the string. After this, we will create a Command object which contains the previously created ExeArgu object and Connector object. 

Then the Command object will call the ExeArgu object to execute the command, and pass the result (succeed or not) to the connector object. Depends on the type of the connector object, it will return a value to judge whether to execute the next ExeArgu object or not.

# Diagram
![Image of Rshell UML](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/blob/master/images/2019-05-10%20(2).png?raw=true)
# Classes
 ### Rshellbase
  ```cpp
class Rshellbase {
private:
	string input;
public:
	Rshellbase(string s) : input(s) {}
	Rshellbase() {};
	~Rshellbase() {
		delete &this->input;
	}

	void Operate() {};

	bool Disintegrate(vector<ExeArgu*> &exeargu, vector<Connector*> &connector,vector<Command*> &command);
};
  ```
   #### ExeArgu
   ```cpp
 class ExeArgu : public Rshellbase {
private:
	string exe;
	string argu;
public:
	ExeArgu(string e, string a) : exe(e), argu(a) {}
	~ExeArgu() {
		delete &this->exe;
		delete &this->argu;
	}
	bool Operate();
	string getExe();
	string getArgu();
};
  ```
   #### Connector
   ```cpp
  class Connector : public Rshellbase {
private:
	char sign;
public:
	Connector() {}
	Connector(char c) : sign(c) {}
	~Connector() {
	}
	bool Operate(bool result);
	char GetSign();
};
  ```
   #### Command
   ```cpp
  class Command : public Rshellbase {
private:
	ExeArgu *exeArgu;
	Connector *connector;
public:
	Command(ExeArgu *e, Connector *c) : exeArgu(e), connector(c) {}
	~Command() {
		delete &this->exeArgu;
		delete &this->connector;
	}
	bool Operate();
};
  ```
# Prototypes/Research
#### Functions
1. fork() creates a new child process which has everything from the parent process except the memory space. And the child process and the parent process may not have a sequential order, it may be executed at the same time or the child starts first. If fork() creates successfully, it will return the PID of the newly created child process in the parent process. If PID is -1, it means fork() fails the creating child process; if PID is 0, it means it successfully create the child process.
2. waitpid() suspends execution of the current process until a signal arrives or the child process terminates. The first parameter of waitpid() is the PID of the waiting child process.
3. execvp() looks for the file name that matches the first parameter file in the directory indicated by the PATH environment variable, finds it, executes it, and passes the second argument to the file to be executed. It doesn’t return any value if it’s successful, but it will return -1 if it fails.

First, we will use the fork() to create a child process, and use the waitpid() to suspends the parent process to see what’s going on in the child process.  Then, we will disintegrate the string types of commands that we input into string arrays of execution, arguments and connectors. Then we will give execvp() these parameters to execute all of the commands.  
#### Seperators
1. ; Commands separated by semicolon are executed sequentially, and subsequent commands are executed even if the intermediate command is not used in the right way, but it will print associated error.
2. && If the first commands fails, then the following command won’t be executed.
3. || If the first commands successes, then the following command won’t be executed.
# Development and Testing Roadmap
1. - [x] [Build Rshellbase class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/3)
2. - [ ] [Unit test of Rshellbase class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/4)
3. - [ ] [Bulid ExeArgu class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/5)
4. - [ ] [Unit test of ExeArgu class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/6)
5. - [ ] [Build Connector class and "And, Or, Semicolon" subclass](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/7)
6. - [ ] [Unit test of Connector and it's subclass](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/8)
7. - [ ] [Bulid Command class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/9)
8. - [ ] [Unit test of Command class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/10)
9. - [ ] [Integration test of Rshellbase class, ExeArgu class, Connector class and Command class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/11)
10. - [ ] [Build main.cpp](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/12)
