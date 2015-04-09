# Network-Daemon
Homework 7 for NAU CS480

###Overview

This assignment accomplishes the first of threee steps that lead to designing and implementing a network server. This is a team effort. A team may have up to three students, with a minimum of at least two.

###Task

- In this first exploratory step you are expected to write a POC program that demonstrates how a Unix deamon process works. Your program has to have the following parts:
- Deamon initialization code: It takes a number of steps to make a normal process (or rather the child of a process) a deamon. We talked about the steps in class, but I invite you to search the Internet to look at examples to understand every single step. Make sure that your deamon prints out its pid to be used later on when the deamon needs to be temrinated.
- Inifinite loop: a deamon is a long-lived process that normally runs in an infinite loop, executing the same task over and over again. In our case I ask you to do the same thing that I demonstrated in class, i.e. let the deamon sleep for a bit, then print out some message to the syslog deamon and sleep a bit again etc.
- Logging: I ask you to implement logging to syslog, whenever the deamon needs to output information that normally would be made to standard output and/or standard error.
- Termination: To terminate a deamon is tricky, as by definition the deamon is decoupled from everything - it is a deamon, after all. One option is to send it a signal. I ask you to prepare the deamon to accept signal SIGUSR1. In case your deamon catches that signal, it is supposed to terminate gracefully, i.e. it will log a last message to syslog, then close the syslog and finally exit. I want you to name the signal handler function deamon_exit()
- For structural purposes all deamon related code, i.e. all of the above except the main loop, needs to be contained in a function deamon_init(), in a file deamon.c, with associated deamon.h. 
