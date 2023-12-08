/*
@function: int is_dataInstruction(char *token);
@parameters: char *token

	char *token: holds the word that appears in the current line.

@description: the function returns 1 if token equals to ".struct", ".data" or ".string", otherwise it returns zero.
*/
int is_dataInstruction(char *token);
/*
@function: int handleData(char *token, int valid, int line_num);
@parameters: char *token, int valid, int line_num

	char *token: holds the word that appears in the current line.
	int valid: this parameter will be 1 if no error has been detected, otherwise valid will be zero.
	int line_num: holds the number of the current line of the target file.

@description: the function handles the validity of .data operands, it shows a relevant errors:
- expected number after .data in line (if a non digit appears right after .data for example: .data w, 1, 3).
- expected integer after .data in line.
*/
int handleData(char *token, int valid, int line_num); /*token send as .data*/
/*
@function: int handleString(char *token, int valid, int line_num);
@parameters: char *token, int valid, int line_num

	char *token: holds the word that appears in the current line.
	int valid: this parameter will be 1 if no error has been detected, otherwise valid will be zero.
	int line_num: holds the number of the current line of the target file.

@description: the function the function handles the validity of .string operands, it shows a relevant errors:
- missing a string in line (if nothing appears after .string).
- quotes are missing in .string instruction line (if a string appears after .string without the quotes '"': .string abcdef).
- second quote missing in line (for example: .srtring "abcdef).
- missing quotes in line.
*/
int handleString(char *token, int valid, int line_num);
/*
@function: int handleStruct(char *token, int valid, int line_num);
@parameters: char *token, int valid, int line_num

	char *token: holds the word that appears in the current line.
	int valid: this parameter will be 1 if no error has been detected, otherwise valid will be zero.
	int line_num: holds the number of the current line of the target file.

@description: the function the function handles the validity of .string operands, it shows a relevant errors:
- expected number after .string in line (non digit appears after .struct: .struct a, "abcdef").
- expected integer after .string in line (if a non integer appears right after .struct).
- missing a string in line (for example: .struct 2,).
- quotes are missing for a struct in line.
- second quote missing in line.
*/
int handleStruct(char *token, int valid, int line_num);
/*
@function: int handleInstruction(char *line, char *token, int line_num);
@parameters: char *token, int valid, int line_num

	char *token: holds the word that appears in the current line.
	int valid: this parameter will be 1 if no error has been detected, otherwise valid will be zero.
	int line_num: holds the number of the current line of the target file.

@description: the function handles the data instructions and it calls the functions above according to the token passed.
*/
int handleInstruction(char *line, char *token, int line_num);

