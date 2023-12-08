/*
@function: int isDefined(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the label name is already defined (has been mentioned before as a definition with the ending ":", otherwise if the label name is not found or has been mentioned as extern/entry it returns zero.
*/
int isDefined(char *label_name);
/*
@function: int getValue(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns the value of the current label according to its name, it return the number of the memory value which starts from 100 (as a default). 
*/
int getValue(char *label_name);
/*
@function: int getCode(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the current label is defined as a code label, meaning that the label has been defined right before an operation appearance. For example: MAIN: mov S1.1, W. MAIN is a code label, STR: .string "abcdef". STR is a data label.
*/
int getCode(char *label_name);
/*
@function: int getData(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function executes a similar role of the previous function (getCode), but it returns 1 if the current label is a data label.
*/
int getData(char *label_name);
/*
@function: int getEntry(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the current label has been mentioned before as .entry, otherwise it returns zero.
*/
int getEntry(char *label_name);
/*
@function: int getExtern(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the current label has been mentioned before as .extern, otherwise it returns zero.
*/
int getExtern(char *label_name);
/*
@function: int getLineNum(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns the line number in which the current label has been defined with the ending ":"
*/
int getLineNum(char *label_name);
/*
@function: int is_label_found(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the current label name is already found in the Labels linked list as entry/extern or a defined one.
*/
int is_label_found(char *label_name);
/*
@function: int isLabel(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if all the current label`s conditions is met together, these conditions are:
- label name length is no more than 30
- label name starts with alphabet
- each letter if the label name (except the first one) are alpha numeric characters.

	if one or more of these 3 conditions is not met, it returns zero.
*/
int isLabel(char *label_name);
/*
@function: int is_label_name_entry_extern(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the label name is ".extern"/".entry", otherwise it returns zero. for example: it returns 1 for this line: .extern: mov S1.1, W. This is an error, label name isn`t valid. 
*/
int is_label_name_entry_extern(char *label_name);
/*
@function: int is_label_name_register(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the label name is a known register (r0 to r7), otherwise it returns zero. for example: it returns 1 for this line: r2: mov S1.1, W. This is an error, label name isn`t valid.
*/
int is_label_name_register(char *label_name);
/*
@function: int is_label_name_dataInstruction(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description:  the function returns 1 if the label name is .data/.string or .struct (these are defined names), otherwise it returns zero. for example: it returns 1 for this line: .data: mov S1.1, W. This is an error, label name isn`t valid.
*/
int is_label_name_dataInstruction(char *label_name); /*if label name equals to .data or .*/
/*
@function: int is_label_name_op(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description:  the function returns 1 if the label name is an operation name (these are defined names), otherwise it returns zero. for example: it returns 1 for this line: clr: mov S1.1, W. This is an error, label name isn`t valid.
*/
int is_label_name_op(char *label_name); /*if label name is the same as one of the 16 operations*/
/*
@function: int is_label_name_macro(char *label_name);
@parameters: char *label_name

	char *label_name: holds the name of the current label (token in line).

@description: the function returns 1 if the label name is a macro name (these are defined names), otherwise it returns zero. for example: it returns 1 for this line: m1: mov S1.1, W. This is an error, label name isn`t valid.
*/
int is_label_name_macro(char *label_name);
/*
@function: int addSymbol(char *label_name, unsigned value, unsigned isCode, unsigned isData, unsigned isEntry, unsigned isExternal, int line_num, int defined);
@parameters: char *label_name, unsigned value, unsigned isCode, unsigned isData, unsigned isEntry, unsigned isExternal, int line_num, int defined

	char *label_name: holds the name of the current label (token in line).
	unsigned value: holds the value of the memory number to which the current label it belongs.
	unsigned isCode: holds 1 if the current label is a code label, zero if not.
	unsigned isData: holds 1 if the current label is a data label, zero if not.
	unsigned isEntry: holds 1 if the current label is a .entry label, zero if not.
	unsigned isExternal: holds 1 if the current label is a .extern label, zero if not.
	int line_num: holds the line number in which the current label is being defined.
	int defined: 1 if the current label is already defined or zero if not.

@description: the function is made to add new sembols to the Labels linked list, if it`s already found in the list, it shows an error if the label has been declared as .extern while it also defined in the source file, it shows another error if the use trying to define the same label name again.
*/
int addSymbol(char *label_name, unsigned value, unsigned isCode, unsigned isData, unsigned isEntry, unsigned isExternal, int line_num, int defined);
/*
@function: int is_label_name_valid(char *name);
@parameters: char *name

	char name: holds the name of the current label (token in line).

@description: the function returns 1 if all these functions returns zero: is_label_name_entry_extern() && is_label_name_register() && is_label_name_dataInstruction() && is_label_name_op() && is_label_name_macro().
*/
int is_label_name_valid(char *name);
/*
@function: int isDataType(char *token);
@parameters: char *token

	char *token: holds the first token that appears after the definition of the current label, for example: STR: .string "abcdef". token here is ".string".

@description: the function returns 1 if token is a data word (.data/.string/.struct).
*/
int isDataType(char *token);
/*
@function: int isCodeType(char *token);
@parameters: char *token

	char *token: holds the first token that appears after the definition of the current label, for example: LENGTH: mov S1.1, W. token here is "mov".

@description: the function returns 1 if token is a code (operation) word (mov,clr,bne..).
*/
int isCodeType(char *token);
/*
@function: int handleLabel(char *line, char *token, char *label_name, int line_num);label define
@parameters: char *line, char *token, char *label_name, int line_num

	char *line: holds the content of the current line of the target file.
	char *token: hold the current appearance of tokens (words) in the current line.
	char *label_name: holds the name of the current label (token in line).
	int line_num: holds the line number in which the current label is being defined.

@description: the function is called in pass1.c each time when a label definition is detected, it checks the word that appears after the ending ":", whether it`s a code word or data word. the function also shows an error if an illegal word appears after the label definition or if nothing is found, for example: S1: .extern, or: S1:
*/
int handleLabel(char *line, char *token, char *label_name, int line_num);
/*
@function: int handle_externalEntry(char *token, int line_num, int isEx, int isEn);
@parameters: char *token, int line_num, int isEx, int isEn

	char *token: holds the current word that appears in the current line.
	int line_num: holds the line number in which the current label is being defined.
	int isEx: this parameter will passed (from pass1.c file) as 1 if the current label is mentioned as .extern.
	int isEn: this parameter will passed (from pass1.c file) as 1 if the current label is mentioned as .entry.

@description: the function handles the labels that have been mentioned as .exter/.entry, if check the validity of the current label and shows a relevant errors, these errors are:
- missin a label name in line (nothing appears after the mention of .extern or .entry).
- extra arguments after label name in line (for example: .entry LOOP mov).
- trying to declare a label as entry again (declaring a label as .entry multiple times).
- an extern declaration after a previous entry declared on the same label (when a label is mentioned as .entry in a specific line and after that it appears as .extern later in the current file).
- an entry declaration after a previous extern declared on the same label (when a label is mentioned as .extern in a specific line and after that it appears as .entry later in the current file).
- trying to declare a label as extern again (declaring a label as .extern multiple times).
- extern declaration on a label which defined in the current file (if a label is already defined in the current file and after that it`s declared as .extern).
- illegal label name in line.
*/
int handle_externalEntry(char *token, int line_num, int isEx, int isEn);
/*
@function: int check_entryLabels();
@parameters: no parameters is passed.

@description: the function is called by pass2.c file, it checks if there are labels which have been assigned as .entry before in the current file, if yes, it shows an error if the entry labels is not defined, for example: .entry S1, if there is not line that defines S1 (S1: ...) then an error will be printed.
*/
int check_entryLabels();
/*
@function: void adjust_dataLabels_value();
@parameters: no parameters is passed.

@description: the function adjusts the memory value of the data type labels after the pass1 is done, it is called by pass2.c file. it adjust the DC to be DC plus 100 (starting memory)
*/
void adjust_dataLabels_value();
/*
@function: int isExtFileNeeded();
@parameters: no parameters is passed.

@description: the function search in Labels linked list if there are .extern labels found, if so then it returns 1 meaning that a file with ending .ext must be created, otherwise it returns zero.
*/
int isExtFileNeeded();
/*
@function: int isEntFileNeeded();
@parameters: no parameters is passed.

@description: the function search in Labels linked list if there are .entry labels found, if so then it returns 1 meaning that a file with ending .ent must be created, otherwise it returns zero.
*/
int isEntFileNeeded();
/*
@function: void writeEntryLabels(FILE *ent);
@parameters: FILE *ent

	FILE *ent: a new file to be created after file passed by command line with the ending ".ent".

@description: 
*/
void writeEntryLabels(FILE *ent);
/*
@function: void writeExtLabels(FILE *ext);
@parameters: FILE *ext

	FILE *ext: a new file to be created after file passed by command line with the ending ".ext".

@description: 
*/
void writeExtLabels(FILE *ext);
/*
@function: void destroy_labels();
@parameters: no parameters is passed.

@description: the function destroys the Labels linked list and reset the global parameters.
*/
void destroy_labels();


