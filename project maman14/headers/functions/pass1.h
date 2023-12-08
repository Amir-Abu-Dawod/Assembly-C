/*
@function: void set_label_name(char *token, char *name); 
@parameters: char *token, char *name

	char *token: holds the name of the current label which has been detected as a label definition.
	char *name: another parameter that holds the name of the current label name but without the ending ":".

@description: the function return the current label name without the ending ":".
*/
void set_label_name(char *token, char *name);
/*
@function: void first_pass(FILE *target, char *fileName);
@parameters: FILE *target, char *fileName

	FILE *target: the new target file after parsing the macros.
	char *fileName: the name of the given file via command line.

@description: the function handles the first pass. it returns 1 if no errors has been detected.
*/
int first_pass(FILE *target, char *fileName);

