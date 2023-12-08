/*
@function: int is_operation_name(char *token);
@parameters: char *token

	char *token: holds the current word which appears in the current line.

@description: the function returns 1 if the current token (the word that appears in the current line) is actually an operation name, otherwise it returns zero.
*/
int is_operation_name(char *token);
/*
@function: int get_operation_addressSrc(char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg);
@parameters: char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg

	char *name: holds the current operation name which appears in the current line.
	unsigned isImmediate: the parameter will be passed as 1 if the current addressing method of the source operand must be immediate according to the operation name.
	unsigned isDirect: the parameter will be passed as 1 if the current addressing method of the source operand must be direct according to the operation name.
	unsigned isIndex: the parameter will be passed as 1 if the current addressing method of the source operand must be index according to the operation name.
	unsigned isReg: the parameter will be passed as 1 if the current addressing method of the source operand must be register according to the operation name.

@description: the function returns 1 if the the current addressing method of the source operand is valid and compatible with the operation name that has detected right before it.
*/
int get_operation_addressSrc(char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg);
/*
@function: int get_operation_addressDes(char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg);
@parameters: char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg

	char *name: holds the current operation name which appears in the current line.
	unsigned isImmediate: the parameter will be passed as 1 if the current addressing method of the destination operand must be immediate according to the operation name.
	unsigned isDirect: the parameter will be passed as 1 if the current addressing method of the destination operand must be direct according to the operation name.
	unsigned isIndex: the parameter will be passed as 1 if the current addressing method of the destination operand must be index according to the operation name.
	unsigned isReg: the parameter will be passed as 1 if the current addressing method of the destination operand must be register according to the operation name.

@description: the function returns 1 if the the current addressing method of the destination operand is valid and compatible with the operation name that has detected right before it.
*/
int get_operation_addressDes(char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg);
/*
@function: int get_operation_orderNum(char *name);
@parameters: char *name

	char *name: holds the current operation name which appears in the current line.

@description: the function returns the order number of the current operation according to its name (via the struct operations).
*/
int get_operation_orderNum(char *name);
/*
@function: int num_of_operands(char *name);
@parameters: char *name

	char *name: holds the current operation name which appears in the current line.

@description: the function returns the number of the operands which the current operation can get according to its name (via the struct operations).
*/
int num_of_operands(char *name);
/*
@function: int handleOneOperand(char *token, int line_num, int valid, char *opName);
@parameters: char *token, int line_num, int valid, char *opName

	char *token: holds the current operand (destination operand in this function) which appears in the current line right after the operation name.
	int line_num: holds the number of the current line in the target file.
	int valid: this parameter will be 1 if no error is detected, otherwise it returns zero.
	char *opName: holds the name of the current operation.

@description: the function handles the cases of lines in which the compiler finds an operation word with only one operand, it shows a relevant errors:
- missing an operand in line (if the passed operand is NULL, no operands found).
- an extra operand appeared (operation takes more than one operand: prn #5, r1).
*/
int handleOneOperand(char *token, int line_num, int valid, char *opName); /*for an operation which takes only one operand*/
/*
@function: int handleTwoOperands(char *token, int line_num, int valid, char *opName);
@parameters: char *token, int line_num, int valid, char *opName

	char *token: holds the current operand which appears in the current line after the operation name.
	int line_num: holds the number of the current line in the target file.
	int valid: this parameter will be 1 if no error is detected, otherwise it returns zero.
	char *opName: holds the name of the current operation. 

@description: the function handles the cases of lines in which the compiler finds an operation word with two operands, it shows a relevant errors:
- missing an operand in line.
- an extra operand appeared (more than two operands have been detected).
*/
int handleTwoOperands(char *token, int line_num, int valid, char *opName);
/*
@function: int handleOperation(char *line, char *token, int line_num);
@parameters: char *line, char *token, int line_num

	char *line: holds the content of the current line in the target file.
	char *token: holds the current word in line (operation name or operands).
	int line_num: holds the number of the current line in the target file.

@description: the function handles the cases in which the compiler finds a new operation name, it calls the relevant function of these explained above, according to the current line.
*/
int handleOperation(char *line, char *token, int line_num);

