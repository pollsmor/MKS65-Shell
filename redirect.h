void redir_out(char ** args, int num_args);
//args: list of arguments created by strsep-ing space characters
//num_args: keep track of the number of arguments

//The arguments array should contain a command to run, and a file name.
//stdout is redirected to the file, so when the command is run, the contents are written to the file.

void redir_in(char ** args, int num_args);
//args: list of arguments created by strsep-ing space characters
//num_args: keep track of the number of arguments

//The arguments array should contain a command to run, and a file name.
//stdin is redirected to the file, so when the command is run, the command takes in the contents of the file.

void redir_in_out(char ** args, int num_args);
//args: list of arguments created by strsep-ing space characters
//num_args: keep track of the number of arguments

//The arguments array should contain a command to run, an input file name, and an output file name.
//stdin is redirected to the file, the command is run from the contents of the file, and the output is redirected to the output file.
