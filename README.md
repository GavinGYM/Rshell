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

# Classes
 - Rshellbase
  ```cpp
  class Rshellbase{
   string input;
  public:
   Rshellbase (string s) : input (s){}
   ~Rshellbase (){
    delete input;
   }
   virtual Operate();
   bool Disintegrate(ExeArgu*,Connector*){
    /*
    The input string looks like this:
    
    $ executable [argumentList] [connector]

    This function is used to disintegrate the input string. It passes the "executable" and "[argumentList]" part 
    to the ExeArgu[](which is an array of objects), and passes the "[connector]" part to the Connector[]
    (which is also an array of objects).
    These two arrays will be paired using subscripts
    */
   }
  }
  ```
   - ExeArgu
   - Connector
     - And, Or, Semicolon
   - Command
# Prototypes/Research

# Development and Testing Roadmap
