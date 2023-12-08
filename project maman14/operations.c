#include "dataHeaders.h"

static const struct Operations operations[OP_SIZE] = {

	{"mov", 0, {1,1,1,1}, {0,1,1,1}},
	{"cmp", 1, {1,1,1,1}, {1,1,1,1}},
	{"add", 2, {1,1,1,1}, {0,1,1,1}},
	{"sub", 3, {1,1,1,1}, {0,1,1,1}},
	{"not", 4, {0,0,0,0}, {0,1,1,1}},
	{"clr", 5, {0,0,0,0}, {0,1,1,1}},
	{"lea", 6, {0,1,1,0}, {0,1,1,1}},
	{"inc", 7, {0,0,0,0}, {0,1,1,1}},
	{"dec", 8, {0,0,0,0}, {0,1,1,1}},
	{"jmp", 9, {0,0,0,0}, {0,1,1,1}},
	{"bne", 10, {0,0,0,0}, {0,1,1,1}},
	{"get", 11, {0,0,0,0}, {0,1,1,1}},
	{"prn", 12, {0,0,0,0}, {1,1,1,1}},
	{"jsr", 13, {0,0,0,0}, {0,1,1,1}},
	{"rts", 14, {0,0,0,0}, {0,0,0,0}},
	{"hlt", 15, {0,0,0,0}, {0,0,0,0}},
};

int is_operation_name(char *token){

	int i=0;
	while(i<OP_SIZE){
		if(!strcmp(operations[i].op_name, token)){
			return 1;
		}
		i++;
	}
	return 0;
}

int get_operation_addressSrc(char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg){

	int i=0,temp;
	while(i<OP_SIZE){
		if(!strcmp(operations[i].op_name, name)){
			temp =i;
			i=OP_SIZE;
		}
		i++;
	}
	if(isImmediate){
		return operations[temp].src.immediate;
	}
	else if(isDirect){
		return operations[temp].src.direct;
	}
	else if(isIndex){
		return operations[temp].src.index;
	}
	else{
		return operations[temp].src.reg;
	}
}

int get_operation_addressDes(char *name, unsigned isImmediate, unsigned isDirect, unsigned isIndex, unsigned isReg){

	int i=0, temp;
	while(i<OP_SIZE){
		if(!strcmp(operations[i].op_name, name)){
			temp =i;
			i=OP_SIZE;
		}
		i++;
	}
	if(isImmediate){
		return operations[temp].des.immediate;
	}
	else if(isDirect){
		return operations[temp].des.direct;
	}
	else if(isIndex){
		return operations[temp].des.index;
	}
	else{
		return operations[temp].des.reg;
	}
}

int get_operation_orderNum(char *name){

	int i=0,temp;
	while(i<OP_SIZE){
		if(!strcmp(operations[i].op_name, name)){
			temp =i;
			i=OP_SIZE;
		}
		i++;
	}
	return operations[temp].op;
}

int num_of_operands(char *name){

	int order_number;
	order_number = get_operation_orderNum(name);

	if(order_number == 0 || order_number == 1 || order_number == 2 || order_number == 3 || order_number == 6){
		return 2; /*source & destination operands*/
	}
	else if(order_number == 14 || order_number == 15){
		return 0; /*none*/
	}
	else{
		return 1; /*only a destination operand*/
	}
}

int handleOneOperand(char *token, int line_num, int valid, char *opName){ /*for an operation which takes only one operand (destination)*/
	char *first_operand, *extra_operand;

	first_operand = strtok(NULL, ", \n\t\v\f\r");
	if(first_operand==NULL){
		fprintf(stderr, "\nError! missing an operand in line %d\n",line_num);
		valid=0;
	}
	else{
		extra_operand = strtok(NULL, ", \n\t\v\f\r");
		if(extra_operand != NULL){
			fprintf(stderr, "\nError! operation in line %d takes only one operand, an extra operand appeared\n",line_num);
			valid=0;
		}
		else{
			valid = handleAddrMethods(opName,first_operand,extra_operand,line_num,valid);
		}
	}
	return valid;
}

int handleTwoOperands(char *token, int line_num, int valid, char *opName){

	char *first_operand, *second_operand, *extra_operand;

	first_operand = strtok(NULL, ", \n\t\v\f\r");
	if(first_operand==NULL){
		fprintf(stderr, "\nError! missing an operand in line %d\n",line_num);
		valid=0;
	}
	else{
		second_operand = strtok(NULL, ", \n\t\v\f\r");
		if(second_operand==NULL){
			fprintf(stderr, "\nError! missing an operand in line %d\n",line_num);
			valid=0;
		}
		else{
			extra_operand = strtok(NULL, ", \n\t\v\f\r");
			if(extra_operand){ /*third operand found*/
				fprintf(stderr, "\nError! operation in line %d takes only two operands, an extra operand appeared\n",line_num);
				valid =0;
			}
			else{
				valid = handleAddrMethods(opName,first_operand,second_operand,line_num,valid);
			}
		}
	}

	return valid;
}

int handleOperation(char *line, char *token, int line_num){

	int operands_num, valid=1;
	char *opName, temp_line[MAX_LINE] = {0};

	opName = (char*)malloc(4);
	strcpy(opName,token);

	strcpy(temp_line,line);
	strcpy(temp_line,strstr(line, opName) + strlen(opName));

	valid=commaSyntax(temp_line,line_num);

	operands_num = num_of_operands(token);

	if(!operands_num){/*none*/
		token = strtok(NULL, " \n\t\v\f\r");
		if(token!=NULL){
			fprintf(stderr, "\nError! there must not be any operands after the current operation: %s at line %d\n", opName,line_num);
			valid=0;
		}
		else{
			increaseIC(1);
		}
	}
	else if(operands_num == 2){ /*two operands*/
		valid = handleTwoOperands(token,line_num,valid,opName);
	}
	else{ /*only des operand*/
		valid = handleOneOperand(token,line_num,valid,opName);
	}
	
	free(opName);
	return valid;
}


