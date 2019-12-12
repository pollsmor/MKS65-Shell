void strip_leading_spaces(char *str);
//str: an input string

//Take a string, and remove any leading spaces. Done so in-place, not by returning a new string.

char ** parse_args(char *line, int *num_args);
//line: passed from exec_args; whatever you typed in from the terminal
//num_args: passed from exec_args; gets incremented everytime strsep is run on space characters

//Uses strsep to separate your input into separate arguments. The last + 1 argument is set to NULL
//so exec_args has no chance of running anything extra (this happened on the school computers, not my own Ubuntu PC)

void exec_args(char * line, int *exited);
//line: whatever you typed in from the terminal
//exited: keeps track of if the while forever loop should exit

//Looks at the input and chooses the correct operation, whether it is to run a command
//normally, redirect in or out, or piping.

char ** semicolon_parse(char *line, int *num_commands);
//line: passed from semicolon_exec; whatever you typed in from the terminal
//num_commands: passed from semicolon_exc; gets incremented everytime strsep is run on semicolons

//Uses strsep to separate your input into separate arguments.

void semicolon_exec(char *line, int *exited);
//line: whatever you typed in from the terminal
//exited: keeps track of if the while forever loop should exit

//Takes the list of arg lists from semicolon_parse and runs everything (via for loop) in sequence.
