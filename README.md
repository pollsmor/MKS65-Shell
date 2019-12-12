# MKS65-Shell
Shell project for Systems (tentative due date of 2019-12-13)

**Features implemented**
- Reads commands from the user via stdin
  - ``` exit ``` is hardcoded
  - ``` cd ``` is hardcoded: has error checking
- Commands can be separated via semicolon 
  - [BUG] At the moment, there cannot be any space to the left or right of a semicolon, will try to fix
- Very basic input and output redirection (only < and >)
- Piping (done via dup and dup2 and not popen() - as far as I know this hasn't caused issues with other parts of the shell)
  - [BUG] Due to using an intermediary file for the piping feature, something like ``` ls | wc ``` will show "tempfile.txt" in the 4th column. This doesn't happen in Bash - it only shows 3 columns.

**Features attempted but couldn't implement**
- Cannot string together input and output redirection due to method of parsing

**Other bugs**
- When exiting from programs that continuously read from stdin (like tr) with Ctrl+C, you go right to Bash, not this shell.

**Function headers**
- parse.h
  - ``` void strip_leading_spaces(char *str); ```
  - ``` char ** parse_args(char *line, int *num_args); ``` 
  - ``` void exec_args(char * line, int *exited); ``` 
  - ``` char ** semicolon_parse(char *line, int *num_commands); ``` 
  - ``` void semicolon_exec(char *line, int *exited); ``` 
- redirect.h
  - ``` void redir_out(char ** args, int num_args); ``` 
  - ``` void redir_in(char ** args, int num_args); ``` 
- pipes.h
  - ``` void my_pipe(char ** args, int num_args); ``` 
  
