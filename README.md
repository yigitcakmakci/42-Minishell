*This project has been created as part of the 42 curriculum by burozdem, ycakmakc.*

# Minishell

## Description
Minishell is a project that involves building a simple, yet fully functional Unix shell from scratch. The main goal of this project is to dive deep into the core mechanisms of an operating system, particularly focusing on process creation, file descriptor manipulation, and signal handling. By recreating a subset of the famous GNU Bash, we gain a comprehensive understanding of how a shell parses user input, manages environment variables, executes commands, and safely handles memory and concurrent processes.

### Key Features
* **Prompt:** Displays a custom prompt and features a working history using the `readline` library.
* **Execution:** Executes commands using absolute paths, relative paths, or by searching the `$PATH` environment variable.
* **Built-ins:** Fully implements `echo` (with `-n`), `cd` (relative/absolute), `pwd`, `export`, `unset`, `env`, and `exit`.
* **Redirections:** Handles input (`<`), output (`>`), append (`>>`), and heredoc (`<<`) seamlessly.
* **Pipes (`|`):** Connects the output of one command to the input of the next, managing multiple child processes safely.
* **Expansions:** Expands environment variables (`$VAR`) and the exit status of the last command (`$?`).
* **Signals:** Properly handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` in interactive and blocking modes exactly like bash.

## Instructions

### Compilation
The project is written in C and must be compiled using the provided `Makefile`. It adheres strictly to the 42 Norm and compiles with `-Wall -Wextra -Werror` flags without any relinking.

To compile the project, run:
```bash
make
Execution
Once compiled, you can start the interactive shell by running the executable:

Bash
./minishell
Cleaning Up
To remove object files, run:

Bash
make clean
To remove both object files and the compiled executable, run:

Bash
make fclean
To recompile from scratch, run:

Bash
make re
```
## Resources
### Documentation & References:

GNU Bash Reference Manual - To understand the expected behavior of the shell.

GNU Readline Library - For handling the interactive prompt and history.

Unix Processes in C - Guide to fork(), waitpid(), and execve().

Pipes and Redirections - Understanding dup(), dup2(), and pipe().

### AI Usage Statement:
During the development of this project, Artificial Intelligence (AI) was utilized strictly as an educational assistant and debugging tool:

* **Debugging & Memory Management:** AI was used to analyze Valgrind reports to pinpoint the source of memory leaks (specifically tracking down Double Free errors and FD leaks during complex pipe/redirection chains).

* **Refactoring:** AI assisted in restructuring large functions to strictly comply with the 42 Norminette rules (e.g., splitting functions to meet the 25-line limit without breaking the logic).

* **Bash Edge Cases:** AI was used to clarify obscure Bash behaviors, such as how word splitting works after variable expansion and how specific heredoc quoting rules apply.