/*
@function: int is_num(char *token);
@parameters: char *token

	char *token: holds the current word that appears in the current line of the target file.

@description: the function returns 1 if the token passed is a number of digits, it`s called by two functions: is_operand_index(char *token) and is_operand_immediate(char *token), if it`s called by the first one, the token will include the sign +/- if existed, if it`s called by the second one, the token will not include the mentioned sign, because if the current token is #-5 then it is legal to get negative numbers of the immediate addressing method, although, if token was S1.-2 then an error will be printed by this function is_num(char *token).
*/
int is_num(char *token);
/*
@function: int is_operand_index(char *token);
@parameters: char *token

	char *token: holds the current word that appears in the current line of the target file.

@description: the function returns 1 if the addressing method of the cuurent operand is index (third method).
*/
int is_operand_index(char *token);
/*
@function: int is_operand_immediate(char *token);
@parameters: char *token

	char *token: holds the current word that appears in the current line of the target file.

@description: the function returns 1 if the addressing method of the cuurent operand is immediate (first method).
*/
int is_operand_immediate(char *token);
/*
@function: int get_addressMethod_type(char *token);
@parameters: char *token

	char *token: holds the current word that appears in the current line of the target file.

@description: the function returns the number of the current addressing method type according to the passed argument(operand).
*/
int get_addressMethod_type(char *token);
/*
@function: int handleAddrMethods(char *opName, char *first, char *second, int line_num, int valid);
@parameters: char *token

	char *token: holds the current word that appears in the current line of the target file.

@description: the function handles the validity and correctness of the addressing methods of operands according to the current code word or data word, it also prints a relevant error for each error case.
*/
int handleAddrMethods(char *opName, char *first, char *second, int line_num, int valid);

