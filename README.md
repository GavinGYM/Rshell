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
###Rshellbase

###ExeArgu

###Connector

####And, Or, Semicolon

###Command


# Prototypes/Research

# Development and Testing Roadmap
