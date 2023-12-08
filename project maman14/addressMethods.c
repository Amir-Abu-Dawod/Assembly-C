#include "dataHeaders.h"

int is_num(char *token){

	int i,len;

	len = strlen(token);
	for(i=0;i<len;i++){
		if(!isdigit(*token)){
			if(*token=='-'){
				fprintf(stderr, "\nError! trying to reach to negative index of label\n");
			}
			return 0;
		}
		token++;
	}
	return 1;
}

int is_operand_index(char *token){

	char temp[MAX_LABEL], *temp2; /*temp1 used for label name, temp2 used for index number*/
	int i;

	strcpy(temp,token);
	
	for(i=0;i<strlen(temp);i++){
		if(temp[i]=='.'){
			temp[i]='\0';
			i=strlen(temp);
		}
	}

	temp2 = (char*)malloc(sizeof(char));
	strcpy(temp2,token);
	
	temp2 = strchr(token,'.');
	if(temp2==NULL){
		return 0;
	}
	else{
		temp2++;
		return (is_num(temp2) && isLabel(temp));
	}
}

int is_operand_immediate(char *token){

	char c;
	c=*token; /*first character in token*/
	if(c=='#'){
		token++;
		if(*token=='-' || *token=='+'){
			token++;
			return is_num(token);
		}
		else{
			return is_num(token);
		}
	}
	return 0;
}

int get_addressMethod_type(char *token){

	if(is_operand_immediate(token)){ /*immediate*/
		return 0;
	}	

	else if(is_register_name(token)){ /*register*/
		return 3;
	}

	else if(is_operand_index(token)){ /*index*/
		return 2;
	}
	
	else if(isLabel(token)){ /*direct*/
		return 1;
	}

	else{
		return -1;
	}
}

int handleAddrMethods(char *opName, char *first, char *second, int line_num, int valid){
	/*if second is null it means the current operation takes only one operand*/

	int operand1, operand2, words=1;

	operand1 =get_addressMethod_type(first);
	if(second){
		operand2 =get_addressMethod_type(second);
	}
	if(second==NULL){ /*only one operand*/
		/*errors in this block are meant to show a not compatible operands along with the current operation addressing method*/
		switch(operand1){
			case(0):
				if(!get_operation_addressDes(opName,1,0,0,0)){
					fprintf(stderr, "\nError! operation: |%s| toke an immediate source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
					increaseIC(words);
					return valid;
				}
				break;

			case(1):
				if(!get_operation_addressDes(opName,0,1,0,0)){
					fprintf(stderr, "\nError! operation: |%s| toke a direct source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
					increaseIC(words);
					return valid;
				}
				break;

			case(2):
				if(!get_operation_addressDes(opName,0,0,1,0)){
					fprintf(stderr, "\nError! operation: |%s| toke an index source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words+=2;
					increaseIC(words);
					return valid;
				}
				break;

			case(3):
				if(!get_operation_addressDes(opName,0,0,0,1)){
					fprintf(stderr, "\nError! operation: |%s| toke a register source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;;
					increaseIC(words);
					return valid;
				}
				break;

			case(-1):/*Error operand doesn't belong to any of the 4 addressing methods*/
				fprintf(stderr, "\nError! unknown type of the first operand, invalid in line %d\n",line_num);
				return 0;
				break;

			default:
				break;
		}
	}
	else{
				/*Handling operations with two operands*/

		switch(operand1){
			case(0):
				if(!get_operation_addressSrc(opName,1,0,0,0)){
					fprintf(stderr, "\nError! operation: |%s| toke an immediate source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
				}
				break;

			case(1):
				if(!get_operation_addressSrc(opName,0,1,0,0)){
					fprintf(stderr, "\nError! operation: |%s| toke a direct source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
				}
				break;

			case(2):
				if(!get_operation_addressSrc(opName,0,0,1,0)){
					fprintf(stderr, "\nError! operation: |%s| toke an index source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words+=2;
				}
				break;

			case(3):
				if(!get_operation_addressSrc(opName,0,0,0,1)){
					fprintf(stderr, "\nError! operation: |%s| toke a register source type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
				}
				break;

			case(-1):/*Error operand doesn't belong to any of the 4 addressing methods*/
				fprintf(stderr, "\nError! unknown type of the first operand, invalid in line %d\n",line_num);
				return 0;
				break;

			default:
				break;
		}
		switch(operand2){
			case(0):
				if(!get_operation_addressDes(opName,1,0,0,0)){
					fprintf(stderr, "\nError! operation: |%s| toke an immediate destination type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
					increaseIC(words);
					return valid;
				}
				break;

			case(1):
				if(!get_operation_addressDes(opName,0,1,0,0)){
					fprintf(stderr, "\nError! operation: |%s| toke a direct destination type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words++;
					increaseIC(words);
					return valid;
				}
				break;

			case(2):
				if(!get_operation_addressDes(opName,0,0,1,0)){
					fprintf(stderr, "\nError! operation: |%s| toke an index destination type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{
					words+=2;
					increaseIC(words);
					return valid;
				}
				break;

			case(3):
				if(!get_operation_addressDes(opName,0,0,0,1)){
					fprintf(stderr, "\nError! operation: |%s| toke a register destination type operand in line %d\n",opName,line_num);
					return 0;
				}
				else{ /*words won't be increased because the two registers source & destination will be in one binary word*/
					if(operand1!=3){
						words++;
					}
					increaseIC(words);
					return valid;
				}
				break;

			case(-1):/*Error operand doesn't belong to any of the 4 addressing methods*/
				fprintf(stderr, "\nError! unknown type of the first operand, invalid in line %d\n",line_num);
				return 0;
				break;

			default:
				break;
		}
	}
	return valid;
}
