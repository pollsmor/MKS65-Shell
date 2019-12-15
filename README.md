# MKS65-Shell
Shell project for Systems

**Features implemented**
- Reads commands from the user via stdin
  - ``` exit ``` is hardcoded
  - ``` cd ``` is hardcoded; has error checking
- Commands can be separated via semicolons
  - Leading and trailing spaces are removed. That means something like <pre>```          ls -al                    ;           echo B```</pre> works.
    - Note: this only works with an entire command, not individual tokens. <pre>ls         -al</pre> would not work.
    - Note 2: this doesn't work for redirection and piping either due to the parsing method. There must be only one space to the left and right of a <, >, or |.

- Basic input and output redirection (only <, >, and < >)
- Piping (done via dup and dup2 and not popen() - as far as I know this hasn't caused issues with other parts of the shell)
  - [BUG] Due to using an intermediary file for the piping feature, something like ``` ls | wc ``` will show "tempfile.txt" in the 4th column. This doesn't happen in Bash - it only shows 3 columns.

**Features attempted but couldn't implement**
- The use of status macros (not sure how I can implement them into my program)

**Other bugs**
- When feeding in a test commands file via ./myshell < {file}, at the end it prints the current working directory the same amount of times as commands in the file. It doesn't happen when I don't print the cwd in main.c, but I think how it currently works is the better of two evils.
- When exiting from programs that continuously read from stdin (like tr) with Ctrl+C, you go right to Bash, not this shell.

**Function headers**
- parse.h
  - ``` void strip_leading_spaces(char *str); ```
  - ``` void strip_trailing_spaces(char *str); ```
  - ``` char ** parse_args(char *line, int *num_args); ```
  - ``` void exec_args(char * line, int *exited); ```
  - ``` char ** semicolon_parse(char *line, int *num_commands); ```
  - ``` void semicolon_exec(char *line, int *exited); ```
- redirect.h
  - ``` void redir_out(char ** args, int num_args); ```
  - ``` void redir_in(char ** args, int num_args); ```
  - ``` void redir_in_out(char ** args, int num_args); ```
- pipes.h
  - ``` void my_pipe(char ** args, int num_args); ```
