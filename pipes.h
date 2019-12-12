void my_pipe(char ** args, int num_args);
//args: list of arguments created by strsep-ing space characters
//num_args: keep track of the number of arguments

//Both commands are taken from the args array. The left command gets run and outputs the contents
//to a temporary file. The right command is run on the temporary file. After both commands are done
//running, the file is deleted.
