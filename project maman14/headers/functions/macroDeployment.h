/*
macroDeployment: in this file macros are created (if detected and defined in the source .as file), macros will be in the form of linked list that will replace macro names in the original file if any error happens, a relevant error will be printed.
*/

/*
@function: void macro_analysis(FILE *fp, FILE *target, char *fileName)
@parameters: FILE *src, FILE *target, char *fileName.
	FILE *src: is a pointer to the given source file (.as).
	FILE *target: is a pointer to the new target file (.am) that will be generated after parsing macros content.
	char *fileName: the file name the has been passed by the user without any extra ending(.as or .am).
@description: this function has to while`s, first while sends each line to other function and checks if there is a macro define and endmacro, the second while runs on the original .as file and does fputs to the .am file copying the same line from .as to .am file not including macro define and endmacro, it also replaces macro names by their relevant content.
*/
int macro_analysis(FILE *src, FILE *target, char *fileName);
/*
@function: void macro_define_check(char *line, char *token, int line_num, int *check_macro, int *if_nested, int *legal);
@parameters: char *line, char *token, int line_num, int *check_macro, int *if_nested, int *legal.

	char *line: used to save the current line content from .as original file via fputs method.
	char *token: used to save the current str token in the current line above.
	int line_num: used as a counter of the lines, it indicated to the number of the current line.
	int *check_macro: if this parameter equals to 1 it means a macro define has been detected, it turns off to zero when an 		"endmacro" is detected.
	int *if_nested: if a nested macro define detected, it equals 1, zero if not.
	int *legal: if macros are defined without errors, legal will be 1, zero if not.

@description: this function handles the correctness and propriety of macros content and defines it check whether the definition is nested or not, also if the macro name is valid, if no error has been found, a macro in a linked list will be created one by one. it returns 1 if no errors has been detected.
*/
void macro_define_check(char *line, char *token, int line_num, int *check_macro, int *if_nested, int *legal);
/*
@function: void macro_analysis2(FILE *target, int line_num, char *line, int *copy, int *if_nested);
@parameters: FILE *target, int line_num, char *line, int *copy, int *if_nested.

	FILE *target: is a pointer to the new target file (.am) that will be generated after parsing macros content.
	int line_num: used as a counter of the lines, it indicated to the number of the current line.
	char *line: used to save the current line content from .as original file via fputs method.
	int *copy: indicates to whether to copy line from .as file to target .am, if line is macro define or endmacro then copy 	will be zero, 1 otherwise.
	int *if_nested: if a nested macro define detected, it equals 1, zero if not.

@description: this function prints the lines of the original file to the target one not including macro blocks, replacing the macro name call to its content.
*/
int macro_analysis2(FILE *target, int line_num, char *line, int *copy, int *if_nested);
/*
@function: void save_macro_content(void);
@parameters: no parameters passed.

@description: the functiong saves the content of a current macro dynamically via the global parameter "macro_content". 
*/
void save_macro_content(void);
/*
@function: int check_macro_name(char *token);
@parameters: char *token.

	char *token: used to save the current str token in the current line above.

@description: the function checks whether the name of the current macro ends with ":" or if it equals to ".string", ".data", ".struct", ".entry", ".extern", or an operation name,these are all invalid names.
*/
int check_macro_name(char *token);
/*
@function: void create_firstMacro(char *token, int line_num);
@parameters: char *token, int line_num.

	char *token: used to save the current str token in the current line above.
	int line_num: used as a counter of the lines, it indicated to the number of the current line.

@description: the function creates the first macro which will be head of the Macros linked list. 
*/
void create_firstMacro(char *token, int line_num);
/*
@function: void create_newMacro(char *token, int line_num);
@parameters: char *token, int line_num.

	char *token: used to save the current str token in the current line above.
	int line_num: used as a counter of the lines, it indicated to the number of the current line.

@description: the function creates the next current macro which will be the next of the last macro in the linked list. 
*/
void create_newMacro(char *token, int line_num);
/*
@function: int is_label_macro(char *label_name);
@parameters: char *label_name.

	char *label_name: the current label name passed from pass1.c function.

@description: the function checks if the name of the current label is similar to one of the already defined macro names, if yes then an error will be printed.
*/
int is_label_macro(char *label_name);
/*
@function: void destroy_macros();
@parameters: no parameters passed

@description: the function frees all the macros from the Macros linked list.
*/
void destroy_macros();

