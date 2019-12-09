void strip_leading_spaces(char *str);

char ** parse_args(char *line, int *num_args);

void exec_args(char * line, int *exited, int *status);

char ** semicolon_parse(char *line, int *num_commands);

void semicolon_exec(char *line, int *exited, int *status);
