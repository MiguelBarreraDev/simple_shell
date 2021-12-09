<h2 align="center">
    C - Simple Shell Project
</h2>
<h1 align ="center">
<img src="https://assets.website-files.com/6105315644a26f77912a1ada/610540e8b4cd6969794fe673_Holberton_School_logo-04-04.svg" height="40%" width="30%">
</h1>

<p align="center">
    <a href="https://github.com/MiguelBarreraDev/simple_shell/commits/main">
        <img src="https://img.shields.io/github/last-commit/MiguelBarreraDev/simple_shell.svg?style=flat-square&logo=github&logoColor=white" alt="GitHub last commit">
    </a>
    <a href="https://github.com/MiguelBarreraDev/simple_shell/issues">
    <img src="https://img.shields.io/github/issues-raw/MiguelBarreraDev/simple_shell.svg?style=flat-square&logo=github&logoColor=white"
         alt="GitHub issues">
    </a>
    <a href="https://github.com/MiguelBarreraDev/simple_shell/pulls">
    <img src="https://img.shields.io/github/issues-pr-raw/MiguelBarreraDev/simple_shell.svg?style=flat-square&logo=github&logoColor=white"
         alt="GitHub pull requests">
    </a>
</p>

<h4 align="center"> _printf() - lightweight version of printf, supporting basic and most used functionality </h4>

<p align="center">
    <a href="#Overview">Overview</a> •
    <a href="#Description">Description</a> •
    <a href="#Format">Format</a> •
</p>

# Overview
Simple_shell repository contains files of our version of Shell
which is a simple UNIX shell based on bash and Sh. Our command
line version of the interpreter is written in C language.

# Description
Simple Shell is a program that emulates a shell (bash) in an
interactive mode. This is a command language interpreter
that executes commands read from standard input.

# Files Contained on this repository

| File | Description |
|--|--|
| **AUTHORS** | Contains the authors of the Simple Shell program. |
| **README.md** | Contains an overview of Simple Shell. Important things that you should know before executes our Simple Shell program. |
| **functions_IO.c** | **built_in:** Checks cmd structure and prints their system calls. **my_getline:** Reads and store the input console. **_strtok:** Divides the buffer in tokens when it finds spaces. **flag_0:** Checks if there are errors on the first buffer. **flag_1:** Checks if there is more than 1 buffer. |
| **functions_main.c** |  **print_env:** Prints the enviroment. **shell_printenv:** Prints a single line of the enviroment. **shell_setenv:** Creates a value at the enviroment. **shell_unsetenv:** Deletes a value at the enviroment. |
| **function_libraries.c** | **shell_clear:** Clears the console. **change_directory:** Changes the directory. **change_path:** Changes the PATH. |
| **functions_help_01.c** | **_concat:** Concatenates the buffer with 'n' arguments. |
| **functions_help_02.c** | **my_getenv:** Searches a key string into the enviroment. **_dstrlen:** Calculates the size of the string of a double pointer. **_free:** Frees the double pointer. **_drealloc:** Reallocates memory depending on flags. |
| **functions_custom_01.c** | **_concat:** Concatenates the buffer with 'n' arguments. |
| **functions_custom_02.c** | **_concat:** Concatenates the buffer with 'n' arguments. |
| **shell.h** | Contains the structures used in our code. Also contains all libraries needed. |
| **shell.c** | **main:** Creates a simple shell. **exit_time:** Compares buffer with 'exit' ignoring spaces. **bypass:** Controls the routes of the structure of cmd. **signal_betty:** Prints \nCisfun$ after signal with betty style. |

# Compilation

Usage: **Shell**
Simple shell is started with the standard input connected to the terminal. To start, compile all .c located in this repository by using this command:
```js
gcc -Wall -Werror -Wextra -pedantic *.c -o Shell
```
# Example

Usage: Interactive mode
```js
user@ubuntu:~/simple_shell$ ./Shell
#Cisfun$~ cp /bin/ls my_ls
#Cisfun$~ ./my_ls
check-betty       hsh    parts_project  simple_shell_tester  tests_2  val
haru_checker_v03  my_ls  run            tests                text
#Cisfun$~ exit
user@ubuntu:~/simple_shell$
```
Usage: Non-interactive mode
```js
user@ubuntu:~/simple_shell$ echo "ls -la" | ./Shell
total 304
-rwxr--r-- 1 root root     29 Dec  8 18:55 check-betty
-rwxr-xr-x 1 root root   2862 Dec  8 23:24 haru_checker_v03
-rwxr-xr-x 1 root root 128568 Dec  9 01:32 hsh
-rwxr-xr-x 1 root root 142144 Dec  8 18:55 my_ls
-rwxr--r-- 1 root root    204 Dec  8 18:55 parts_project
-rwxr-xr-x 1 root root     83 Dec  8 18:55 run
drwxr-xr-x 6 root root   4096 Dec  8 18:55 simple_shell_tester
drwxr-xr-x 2 root root   4096 Dec  9 01:34 tests
drwxr-xr-x 2 root root   4096 Dec  9 01:33 tests_2
-rwxr--r-- 1 root root    374 Dec  8 18:55 text
-rwxr--r-- 1 root root     66 Dec  8 18:55 val
user@ubuntu:~/simple_shell$
```

# Command List

| Commands | Description |
|--|--|
| `ls` | ls (from list), allows you to list the contents of a directory or file. |
| `pwd` | Pwd (from print working directory) is a convenient command that prints our path or location when executed, so we avoid getting lost if we are working with multiple directories and folders. |
| `touch` | touch creates an empty file, if the file exists it updates the modification time. |
| `rm` | rm (from remove) is the command needed to delete a file or directory. |
| `mkdir` | mkdir (from make directory) creates a new directory taking into account the current location. |
| `cp` | cp (from copy) copies a source file or directory to a target fileor directory. |
| `rmdir` | rmdir (from ReMove DIRectory) This command is used to delete empty directories or subdirectories. |
| `cd` | cd (from change directory) you will need this command to access a path other than the one you are in. basically it is for navigating from directory to directory. |
| `exit` | exits the current shell. 0 status value indicates successful execution, another value represents unsuccessful execution. |
| `cat` | cat (from concatenate), is a wonderful utility that allows us to visualize the content of a text file in the standard output, without the need of an editor. |

# Authors and Github

* **Please, read the [AUTHORS](https://github.com/MiguelBarreraDev/simple_shell/blob/main/AUTHORS) file**
* **https://github.com/MiguelBarreraDev/simple_shell**

# Contact Information


##### Please feel free to contact us regarding any matter (specially about mistakes, recomendations and gramar errors)

<p align="center">
Miguel Barrera -
<a href="https://github.com/MiguelBarreraDev">
        <img src="https://img.shields.io/badge/Miguel-mainPage-blue">
</a>
</p>

<p align="center">
Cristhian Apaza - 
<a href="https://github.com/cristhian1107">
        <img src="https://img.shields.io/badge/Cristhian-mainPage-blue">
</a>
</p>
<div align="center">
    <img src="https://stormotion.io/blog/content/images/2018/12/developer.gif" width="400" height="200">
</div>
