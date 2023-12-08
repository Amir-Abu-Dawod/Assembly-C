/*
@function: void second_pass(FILE *target, char *fileName);
@parameters: FILE *target, char *fileName

	FILE *target: the new target file after the parsing of the macros.
	char *fileName: the name of the given file via command line without the ending ".as".

@description: the function handles the second pass. it returns 1 if no errors has been detected.
*/
int second_pass(FILE *target, char *fileName);

