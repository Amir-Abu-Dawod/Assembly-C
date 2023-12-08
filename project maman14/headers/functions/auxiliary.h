/*
@function: int commaSyntax(char *line, int line_num);
@parameters: char *line, int line_num

	char *line: holds the content of the current line.
	int line_num: holds the number of the current line.

@description: the function returns 1 if the comma syntax of the current line is legal without any errors, other wise it returns zreo, it also shows a relevant errors: 
- in this line number: %d an illegal appearence of commas (when a comma is appears before any word in the beginning of the line).
- in this line number: %d a comma appeared before any operand (for example: mov , r1, r2).
-  an extra comma appeared between 2 operands in line (for example: mov r1, ,r2).
- a comma is missing between 2 operands in line (for example: mov r1 r2).
- a comma appeared after the last operand at line (for example: mov r1, r2 ,).
*/
int commaSyntax(char *line, int line_num);
/*
@function: int is_register_name(char *token);
@parameters: char *token

	char *token: holds the word which appears in the current line.

@description: the function return 1 if the current word token is actually a register (r0 to r7).
*/
int is_register_name(char *token);
/*
@function: char *base32values(int num);
@parameters: int num

	int num: holds an integer number to be converted to a number of base 32.

@description: the function converts the passed integer to a number in the form of base 32. 0 equals to "!", 1 equals to "@"... .
*/
char *base32values(int num);
/*
@function: int binToDecimal(int num);
@parameters: int num

	int num: holds an integer number to be converted to a number of integer decimal.

@description: the function converts the passed integer to a number in a base of decimal.
*/
int binToDecimal(int num);
/*
@function: char *binToBase32(char *binaryWord);
@parameters: char *binaryWord

	char *binaryWord: holds a binary number to be converted to base 32.

@description: the function converts the passed binary number to a base 32 number.
*/
char *binToBase32(char *binaryWord);
/*
@function: char *numToBin(int num, int isData, int isCode, int isOpcode, int isRegister);
@parameters: int num, int isData, int isCode, int isOpcode, int isRegister

	int num: hold the passed integer decimal number to be converted to binary base number.
	int isData: this parameter will be passed as 1 if the current linehas an appearance of a data instruction word.
	int isCode: this parameter will be passed as 1 if the current line has an appearance of a code operation word.
	int isOpcode: this parameter will be passed as 1 if the compiler have to translate the line into a binary first word in each line, meaning the firsrt binary word which consists of opcode + source operand + destination operad + ending :"00".
	int isRegister: this parameter will be passed as 1 if the current word to be converted is actually a register.

@description: the function converts the line into binary words.
*/
char *numToBin(int num, int isData, int isCode, int isOpcode, int isRegister);
/*
@function: char *decimalToBase32(int decimalNum);
@parameters: int decimalNum

	int decimalNum: holds the decimal number to be converted to base 32.

@description: the function converts decimal numbers into base 32 via the help of the function base32values.
*/
char *decimalToBase32(int decimalNum);
/*
@function: char *remove_leftSpaces(char *token);
@parameters: char *token

	char *token: holds the current word in the current line.

@description: the function removes the spaces from the start(starting from the left) to the first non space characters appearance.
*/
char *remove_leftSpaces(char *token);
/*
@function: void convertDataOperand(char *operand);
@parameters: char *operand

	char *operand: holds the content of the .data operands for example: .data 1, 4. operand will be the numbers that appear after ".data": (1, 4).

@description: the function converts each number of the data instruction into binary words according to their appearance order.
*/
void convertDataOperand(char *operand);
/*
@function: void convertStringOperand(char *operand);
@parameters: char *operand

	char *operand: holds the content of the .string operands for example: .string "abcdef". operand will be the string that appears after ".string": ("abcdef").

@description: the function converts each character of the string after .string into binary words according to their appearance order, it also adds a binary word as an ending consists of zero numbers which represents the ending of a string ("\0").
*/
void convertStringOperand(char *operand);
/*
@function: void convertStructOperand(char *operand);
@parameters: char *operand

	char *operand: holds the content of the .string operands for example: .string "abcdef". operand will be the string that appear after ".struct": (8, "abcdef").

@description: the function converts the number and the string that appear after ".struct" into binary words according to their appearance order. 
*/
void convertStructOperand(char *operand);
/*
@function: int checkIfLabelUsedIsFound(char *operand, int addrMethod, int line_num);
@parameters: char *operand

	char *operand: holds the current operand which appears in the current line.
	int addrMethod: holds the compatible addressing method to the current operand.
	int line_num: holds the number of the current line.

@description: the function returns 1 if the current label that is been used is already found in Labels linked list, otherwise it shows an error that the label is not found.
*/
int checkIfLabelUsedIsFound(char *operand, int addrMethod, int line_num);
/*
@function: void convertTwoRegisters(char *first, char *second);
@parameters: char *first, char *second

	char *first: holds the first (source) register.
	char *second: holds the second (destination) register.

@description: the function handles the case in which the compiler finds a code operation with two registers so it adds only one binary word for the two registers.
*/
void convertTwoRegisters(char *first, char *second);
/*
@function: int convertImmediateOperand(char *operand,int valid, int line_num);
@parameters: char *operand,int valid, int line_num

	char *operand: holds the current operand which appears in the current line.
	int valid: this parameter will be 1 if no error is being detected, otherwise it equals zero.
	int line_num: holds the number of the current line.

@description: the function handles the case in which the compiler finds a code operation with an immediate operand, if the number that appears after "#" is over 255 then an error will be printed cause it cannot be translated into base 32.
*/
int convertImmediateOperand(char *operand, int valid, int line_num);
/*
@function: int convertDirectOperand(char *operand);
@parameters: char *operand

	char *operand: holds the current operand which appears in the current line.

@description: the function handles the case in which the compiler finds a code operation with a direct operand (a label).
*/
int convertDirectOperand(char *operand);
/*
@function: void convertIndexOperand(char *operand,int valid);
@parameters: char *operand

	char *operand: holds the current operand which appears in the current line.

@description: the function handles the case in which the compiler finds a code operation with an index operand (a label with an index: S1.1).
*/
void convertIndexOperand(char *operand,int valid);
/*
@function: void convertRegisterOperand(char *operand,int valid,int position);
@parameters: char *operand,int valid,int position

	char *operand: holds the current operand which appears in the current line.
	int valid: this parameter will be 1 if no error is being detected, otherwise it equals zero.
	int position: holds the position of the register, first or second (source/destination).

@description: the function handles the case in which the compiler finds a code operation with a register operand.
*/
void convertRegisterOperand(char *operand, int valid,int position);
/*
@function: int convertFirstOperand(char *first, int line_num, int addrMethod, int valid);
@parameters: char *first, int line_num, int addrMethod, int valid

	char *first: holds the first opoerand which appears after the current operation code word in the same current line.
	int line_num: holds the number of the current line.
	int addrMethod: holds the addressing method number which represents the first operand.
	int valid: this parameter will be 1 if no error is being detected, otherwise it equals zero.

@description: the function handles the translating of the first operand after the appearance of a operation code word.
*/
int convertFirstOperand(char *first, int line_num, int addrMethod, int valid);
/*
@function: int convertSecondOperand(char *second,int line_num, int addrMethod, int valid);
@parameters: char *second, int line_num, int addrMethod, int valid

	char *second: holds the second opoerand which appears after the current operation code word in the same current line.
	int line_num: holds the number of the current line.
	int addrMethod: holds the addressing method number which represents the second operand.
	int valid: this parameter will be 1 if no error is being detected, otherwise it equals zero.

@description: the function handles the translating of the first operand after the appearance of a operation code word.
*/
int convertSecondOperand(char *second, int line_num, int addrMethod, int valid);
/*
@function: int convertLineToBinWord(char *operation, char *operands, int isFirst, int isCode, int isData, int line_num);
@parameters: char *operation, char *operands, int isFirst, int isCode, int isData, int line_num

	char *operation: holds the current operation, if no operation has been found in the current line then it will be NULL. 
	char *operands: the operands that appears after the last word whether it`s an operation code word or data instruction.
	int isFirst: if it equals to 1, then the compiler adds the first binary word which ends with "00", otherwise it adds binary words for each operand.
	int isCode: this parameter will be 1 if an operation code word has been detected in the current line.
	int isData: this parameter will be 1 if a data instruction word has been detected in the current line.
	int line_num: holds the number of the current line.

@description: the function handles the converting of each line into binary words, it calls the functions above according to the given line.
*/
int convertLineToBinWord(char *operation, char *operands, int isFirst, int isCode, int isData, int line_num);
/*
@function: void convertFirstCodeWord(int first, int second, char *operation);
@parameters: int first, int second, char *operation

	int first: holds the first operand after operation code word in the current line.
	int second: holds the second operand after operation code word in the current line.
	char *operation: holds the name of the operation code word.

@description: the function handles the convertion of the first binary word in each line that has an operation code word.
*/
void convertFirstCodeWord(int first, int second, char *operation); /*words with opcode*/

