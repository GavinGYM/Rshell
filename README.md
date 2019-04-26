# CS 100 Programming Project
Spring 2019

Yiming Guo, SID:X670427, gavin-gym@foxmail.com

Yulin Liang, SID:X671565, yulin66728@gmail.com
# Introduction
This is a command shell called rshell in C++ which is made by Yulin Liang and Yiming Guo, and it is capable of performing the following steps:

1.	Print a command prompt (e.g. `$`)
2.	Read in a line of command(s) (and connector(s)) from standard input
>The connector is an optional way you can run multiple commands at once. If a command is followed by ;, then the next command is always >executed; if a command is followed by &&, then the next command is executed only if the first one succeeds; if a command is followed by >||, then the next command is executed only if the first one fails. 
3.	Execute the appropriate commands using fork, execvp, and waitpid

We designed this program by using composite pattern.

# Diagram
![Image of Rshell UML](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/blob/master/images/Rshell_UML.png?raw=true)
# Classes
 ### Rshellbase
  ```cpp
  class Rshellbase{
   string input;
  public:
   Rshellbase (string s) : input (s){}
   ~Rshellbase (){
    delete input;
   }
   virtual Operate();
   bool Disintegrate(ExeArgu exeargu[], Connector connector[], Command command[]){
    string subinput;
    subinput = this.string;
    int i=0;
    while(there is still a "&&", "||" or ";" in subinput){
     string cmd;
     cmd = subinput.substr(everything before a "&&", "||" or ";");
     exeargu[i]->exe = cmd.substr(the executable part of the cmd);
     exeargu[i]->argu = cmd.substr(the [argumentList] part of the cmd);
     if(the [connector] is "&&"){
      connector[i] = new And();
     }
     else if(the [connector] is "||"){
      connector[i] = new Or();
     }
     else if(the [connector] is ";"){
      connector[i] = new Semicolon();
     }
     command[i]->exeArgu = exeargu[i];
     command[i]->connector = connector[i];
     i++;
    }
    //this is for the last command which don't have a connector following it
    string cmd;
    cmd = subinput.substr(everything before a "&&", "||" or ";");
    exeargu[i]->exe = cmd.substr(the executable part of the cmd);
    exeargu[i]->argu = cmd.substr(the [argumentList] part of the cmd);
    command[i]->exeArgu = exeargu[i];
    /*
    The input string looks like this:
    
    $ executable [argumentList] [connector]

    This function is used to disintegrate the input string. 
    It passes the "executable" and "[argumentList]" part 
    to the ExeArgu[](which is an array of objects), 
    and passes the "[connector]" part to the Connector[]
    (which is also an array of objects).
    These two arrays will be paired by using their subscripts.
    */
    
   }
  }
  ```
   #### ExeArgu
   ```cpp
  class ExeArgu : public Rshellbase{
   string exe;
   string argu;
  public:
   ExeArgu (string e, string a) : exe (e), argu (a){}
   ~Rshellbase (){
    delete exe;
    delete argu;
   }
   bool Operate(){
    if(Execute the command by passing the string exe and string argu){
     return true;
    }
    else{
     return false;
    }
   }
  }
  ```
   #### Connector
   ```cpp
  class Connector : public Rshellbase{
  public:
   Connector () {}
   ~Connector (){
   }
   virtual Operate(){}
  }
  ```
   ##### And, Or, Semicolon
   ```cpp
   class And(Or,Semicolon) : public Connector{
   public:
    bool Operate(bool result){
     // This part of the code is different for these three classes
     // The "And" class
     if(result){
      return true;
     }
     else{
      return false;
     }
     // The "Or" class
     if(result){
      return false;
     }
     else{
      return true;
     }
     // The "Semicolon" class
     return true;
    }
   }
   ```
   #### Command
   ```cpp
  class Command : public Rshellbase{
   Rshellbase exeArgu;
   Rshellbase connector;
  public:
   Command (Rshellbase e, Rshellbase c) : exeArgu (e), connector (c){}
   ~Command (){
    delete exeArgu;
    delete connector;
   }
   bool Operate(){
    return connector.Operate(exeArgu.Operate());
   }
  }
  ```
# Prototypes/Research

# Development and Testing Roadmap
1. - [ ] [Build Rshellbase class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/3)
2. - [ ] [Unit test of Rshellbase class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/4)
3. - [ ] [Bulid ExeArgu class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/5)
4. - [ ] [Unit test of ExeArgu class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/6)
5. - [ ] [Build Connector class and "And, Or, Semicolon" subclass](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/7)
6. - [ ] [Unit test of Connector and it's subclass](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/8)
7. - [ ] [Bulid Command class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/9)
8. - [ ] [Unit test of Command class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/10)
9. - [ ] [Integration test of Rshellbase class, ExeArgu class, Connector class and Command class](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/11)
10. - [ ] [Build main.cpp](https://github.com/cs100/spring-2019-assignment-yiming_and_yulin/issues/12)
