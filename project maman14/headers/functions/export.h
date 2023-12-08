/*
@function: void exportFiles(FILE *target, char *fileName, int isEnt, int isExt);
@parameters: FILE *target, char *fileName, int isEnt, int isExt

	FILE *target: the new target file after the parsing of the macros.
	char *fileName: the name of the given file via command line without the ending ".as".
	int isEnt: this parameter is passed as 1 if a new file with the ending ".ent" must be created, otherwise it equals zero.
	int isExt: this parameter is passed as 1 if a new file with the ending ".ext" must be created, otherwise it equals zero.

@description: the function handles the exportation of the files (ob, ext and ent files).
*/
void exportFiles(FILE *target, char *fileName, int isEnt, int isExt);
/*
@function: void obExport(FILE *obFile, char *fileName);
@parameters: FILE *obFile, char *fileName

	FILE *obFile: a new file with the ending ".ob".
	char *fileName: the name of the given file via command line without the ending ".as".

@description: the function handles the exporting of the .ob file.
*/
void obExport(FILE *obFile, char *fileName);
/*
@function: void entExport(FILE *entFile, char *fileName);
@parameters: FILE *entFile, char *fileName

	FILE *entFile: a new file with the ending ".ent".
	char *fileName: the name of the given file via command line without the ending ".as".

@description: the function handles the exportation of the .ent file.
*/
void entExport(FILE *entFile, char *fileName);
/*
@function: void extExport(FILE *extFile, char *fileName);
@parameters: FILE *extFile, char *fileName

	FILE *extFile: a new file with the ending ".ext".
	char *fileName: the name of the given file via command line without the ending ".as".

@description: the function handles the exportation of the .ext file.
*/
void extExport(FILE *extFile, char *fileName);

