#include "dataHeaders.h"

int commaSyntax(char *line, int line_num){

	int valid=1, counter=0, first_operand=1, operand=0;

	while ((*line == ',' || isspace(*line)) && *line != '\0')
	{
	        if (*line == ','){
	            counter++;
		}
	        line++;
	}

	if (!*line && counter > 0){
		fprintf(stderr, "\nError! in this line number: %d an illegal appearence of commas\n",line_num);
		valid=0;
		return valid;
	}

	else if (*line && strlen(line) && counter > 0){ /*first operand reached*/
		fprintf(stderr, "\nError! in this line number: %d a comma appeared before any operand\n",line_num);
		valid=0;
	}

	counter = 0;
	while(line && *line != '\0'){
		if(operand){
			if(counter>1){
				fprintf(stderr, "\nError! an extra comma appeared between 2 operands in line %d\n",line_num);
				valid=0;
				counter =1;
			}
			else if(counter<1 && !first_operand){
				fprintf(stderr, "\nError! a comma is missing between 2 operands in line %d\n",line_num);
				valid=0;
			}
			if(first_operand){
				first_operand=0;
			}

			while(*line!='\0' && !isspace(*line) && *line!=','){

				line++;
			}

			if((*line==',' || isspace(*line))){
				operand=0;
				counter=0;
				line--; /*1 step backward*/
			}
		}
		else{
			while(*line==',' || isspace(*line)){

				if(*line==','){
					counter++;
				}
				line++;
				if(*line=='\0'){
				}
			}
			if(*line && (isprint(*line) && !isspace(*line))){
				operand=1;
			}
		}
		if(*line!='\0'){
			line++;
		}

	}

	if(counter){
		fprintf(stderr, "\nError! a comma appeared after the last operand at line %d\n",line_num);
		valid=0;
	}
	return valid;
}

int is_register_name(char *token){

	char temp[2] = "r ";
	int i;

	for(i=0;i<8;i++){
		temp[1] = i + '0';
	
		if(!strcmp(token, temp)){
			return 1;
		}
	}
	return 0;
}

char *base32values(int num){
	char *temp;
	temp=(char*)malloc(sizeof(char));

	switch(num){
		case(0):
			strcat(temp,"!");
			break;
		case(1):
			strcat(temp,"@");
			break;
		case(2):
			strcat(temp,"#");
			break;
		case(3):
			strcat(temp,"$");
			break;
		case(4):
			strcat(temp,"%");
			break;
		case(5):
			strcat(temp,"^");
			break;
		case(6):
			strcat(temp,"&");
			break;
		case(7):
			strcat(temp,"*");
			break;
		case(8):
			strcat(temp,"<");
			break;
		case(9):
			strcat(temp,">");
			break;
		case(10):
			strcat(temp,"a");
			break;
		case(11):
			strcat(temp,"b");
			break;
		case(12):
			strcat(temp,"c");
			break;
		case(13):
			strcat(temp,"d");
			break;
		case(14):
			strcat(temp,"e");
			break;
		case(15):
			strcat(temp,"f");
			break;
		case(16):
			strcat(temp,"g");
			break;
		case(17):
			strcat(temp,"h");
			break;
		case(18):
			strcat(temp,"i");
			break;
		case(19):
			strcat(temp,"j");
			break;
		case(20):
			strcat(temp,"k");
			break;
		case(21):
			strcat(temp,"l");
			break;
		case(22):
			strcat(temp,"m");
			break;
		case(23):
			strcat(temp,"n");
			break;
		case(24):
			strcat(temp,"o");
			break;
		case(25):
			strcat(temp,"p");
			break;
		case(26):
			strcat(temp,"q");
			break;
		case(27):
			strcat(temp,"r");
			break;
		case(28):
			strcat(temp,"s");
			break;
		case(29):
			strcat(temp,"t");
			break;
		case(30):
			strcat(temp,"u");
			break;
		case(31):
			strcat(temp,"v");
			break;
	}
	return temp;
}

int binToDecimal(int num){
	int base=1, remain, decimal_num=0;

	while(num>0){
		remain = num%10;
		decimal_num = decimal_num +(base*remain);
		num=num/10;
		base*=2;
	}
	return decimal_num;
}

char *binToBase32(char *binaryWord){

	char *result, *temp;
	int i, num, counter=0;

	result = (char*)malloc(2*sizeof(char));
	temp = (char*)malloc(5*sizeof(char));

	strcpy(result,"");
	strcpy(temp,"");

	for(i=0;i<11;i++){
		if(!(counter%5) && counter){
			num = binToDecimal(atoi(temp));
			strcat(result, base32values(num));
			strcpy(temp,"");
		}
		if(binaryWord[i]=='1'){
			strcat(temp,"1");
		}
		else{
			strcat(temp,"0");
		}
		counter++;
	}
	free(temp);
	return result;
}

char *numToBin(int num, int isData, int isCode, int isOpcode, int isRegister){
	char *bin, *temp, *result;
	int i, negative=0;

	if(isData){
		bin = (char*)malloc(11*sizeof(char));
	}
	else if(isRegister){
		bin = (char*)malloc(4*sizeof(char));
	}
	else if(isCode){
		bin = (char*)malloc(8*sizeof(char));
	}
	strcpy(bin,"");

	if(num<0){
		num = abs(num);
		negative=1;
	}

	while(num>0){ /*bin will be the binary number but it must be reversed*/
		if(num%2){
			strcat(bin,"1");
		}
		else{
			strcat(bin,"0");
		}
      		num = num/2;
   	}	

	if(isData){
		i=10-strlen(bin);
		while(i>0){
			strcat(bin,"0");
			i--;
		}
	}

	else if(isOpcode || isRegister){
		i=4-strlen(bin);
		while(i>0){
			strcat(bin,"0");
			i--;
		}
	}

	else if(isCode && !isRegister){
		i=8-strlen(bin);
		while(i>0){
			strcat(bin,"0");
			i--;
		}
	}

	if(negative){
	   	temp = (char *)malloc(strlen(bin)*sizeof(char));
		for(i=0;i<strlen(bin);i++){
			if(bin[i]=='1'){
				strcat(temp,"0");
			}
			else{
				strcat(temp,"1");
			}
		}
		strcpy(bin,temp);

		strcpy(temp,"");/*empty the content*/
		if(bin[0]=='1'){
			i=0;

			while(i<strlen(bin) && bin[i]!='0'){
				strcat(temp,"0");
				i++;
			}
			strcat(temp,"1");
			i++;

			while(i<strlen(bin)){
				if(bin[i]=='1'){
					strcat(temp, "1");
				}
				else{
					strcat(temp, "0");
				}
				i++;
			}
		}
		else{
			i=1;
			strcat(temp, "1");
			while(i<strlen(bin)){
				if(bin[i]=='1'){
					strcat(temp, "1");
				}
				else{
					strcat(temp, "0");
				}
				i++;
			}
		}
		strcpy(bin,temp);
		free(temp);
	}

	result = (char*)malloc(11*strlen(bin));

	for(i=strlen(bin)-1;i>=0;i--){/*reverse the order of numbers*/
		if(bin[i]=='1'){
			strcat(result,"1");
		}
		else{
			strcat(result,"0");
		}
	}
	free(bin);
	return result;
}


char *decimalToBase32(int decimalNum){

	int start, end;
	char *base32, temp;

   	base32 = (char *)malloc(sizeof(char));
	strcpy(base32,"");
   	while(decimalNum>0){
		strcat(base32, base32values(decimalNum%32));
      		decimalNum = decimalNum/32;
   	}

	end = strlen(base32)-1;
	for(start=0;start<end;start++){ /*reversing*/
		temp = base32[start];
		base32[start]=base32[end];
		base32[end] = temp;
		end--;
	}
	return base32;
}

char *remove_leftSpaces(char *token){
	while(isspace(*token) && *token != '\0'){
		token++;
	}
	return token;
}

void convertDataOperand(char *operand){

	operand = strtok(operand, ",");

	while(operand!=NULL){
		addWord(getDC() + get_pass1IC(),numToBin(atoi(operand),1,0,0,0));
		increaseDC(1);
		operand = strtok(NULL, ",");
	}
}

void convertStringOperand(char *operand){

	operand++;
	while(*operand!='\"'){
		addWord(getDC()+get_pass1IC(),numToBin((int)operand[0],1,0,0,0));
		increaseDC(1);
		operand++;
	}

	addWord(getDC()+get_pass1IC(), "0000000000");
	increaseDC(1);
}

void convertStructOperand(char *operand){

	char *temp;

	temp = (char*)malloc(strlen(operand)*sizeof(char));
	strcpy(temp,operand);
	operand = strtok(operand,",");
	convertDataOperand(operand);

	operand = strtok(temp,",");
	operand = strtok(NULL,",");
	operand = remove_leftSpaces(operand);
	convertStringOperand(operand);
}

void convertTwoRegisters(char *first, char *second){

	char *num1, *num2, *result;

	num1 = (char*)malloc(2*sizeof(char));
	num2 = (char*)malloc(2*sizeof(char));
	result = (char*)malloc(11*sizeof(char));
	strcpy(result,"");

	num1 = strtok(first, "r");
	num2 = strtok(second, "r");

	strcat(result, numToBin(atoi(num1),0,1,1,1));
	strcat(result, numToBin(atoi(num2),0,1,1,1));
	strcat(result, "00");

	addWord(getIC(), result);
	increaseIC(1);
}

int convertImmediateOperand(char *operand, int valid, int line_num){ /*#*/

	char *result;
	result = (char*)malloc(11*sizeof(char));
	strcpy(result,"");

	operand = strtok(operand,"#+");
	if(atoi(operand)>255){
		fprintf(stderr, "\nError! in line %d operand is a number over 255\n",line_num);
		valid=0;
	}
	else{
		strcat(result, numToBin(atoi(operand),0,1,0,0));
		strcat(result,"00");
		addWord(getIC(), result);
		increaseIC(1);
	}
	return valid;
}

int convertDirectOperand(char *operand){/*label*/

	int valid=1;
	char *result;
	result = (char*)malloc(11*sizeof(char));
	strcpy(result,"");

	if(getExtern(operand)){
		if(!add_externValue(operand,getIC())){
			valid=0;
		}
		else{
			addWord(getIC(),"0000000001");
			increaseIC(1);
		}
	}
	else{
		strcat(result, numToBin(getValue(operand),0,1,0,0));
		strcat(result, "10");/*normal or entry label*/
		addWord(getIC(),result);
		increaseIC(1);

	}
	return valid;
}

void convertIndexOperand(char *operand,int valid){

	char *result;
	result = (char*)malloc(11*sizeof(char));
	strcpy(result,"");

	operand = strtok(operand, ".");
	convertDirectOperand(operand);

	operand = strtok(NULL, ".");
	strcat(result,numToBin(atoi(operand),0,1,0,0));
	strcat(result, "00");
	
	addWord(getIC(),result);
	increaseIC(1);
}

void convertRegisterOperand(char *operand, int valid, int position){

	char *result;
	result = (char*)malloc(11*sizeof(char));
	strcpy(result,"");

	if(position==2){
		strcat(result, "0000");
		operand = strtok(operand,"r");
		numToBin(atoi(operand),0,1,0,1);
		strcat(result, numToBin(atoi(operand),0,1,0,1));
		strcat(result, "00");
	}
	else{

	operand = strtok(operand,"r");
	strcat(result,numToBin(atoi(operand),0,1,0,1));
	strcat(result, "000000");

	}
	addWord(getIC(),result);
	increaseIC(1);
}

int checkIfLabelUsedIsFound(char *operand, int addrMethod, int line_num){

	char *temp;

	temp =(char*)malloc(MAX_LINE*sizeof(char));
	strcpy(temp,operand);

	if(addrMethod==1){/*direct-label operand*/
		if(!is_label_found(temp)){
			printf("\nError! in line %d an attempt to use a none defined label (%s) has been detected\n",line_num,temp);
			free(temp);
			return 0;
		}
	}
	else if(addrMethod==2){
		temp = strtok(temp, ".");
		if(!is_label_found(temp)){
			printf("\nError! in line %d an attempt to use a none defined label (%s) has been detected\n",line_num,temp);
			free(temp);
			return 0;
		}
	}
	free(temp);
	return 1;
}

int convertFirstOperand(char *first, int line_num, int addrMethod, int valid){ /*dealing with operation Instructions*/

	if(!checkIfLabelUsedIsFound(first,addrMethod,line_num)){
		valid=0;
		return valid;
	}

	if(addrMethod==0){
		if(!convertImmediateOperand(first,valid,line_num)){
			valid=0;
		}
	}
	else if(addrMethod==1){
		if(!convertDirectOperand(first)){
			valid=0;
		}
	}
	else if(addrMethod==2){
		convertIndexOperand(first,valid);
	}
	else{/*3*/
		convertRegisterOperand(first,valid,1);
	}

	return valid;
}

int convertSecondOperand(char *second, int line_num, int addrMethod, int valid){ /*dealing with operation Instructions*/

	if(!checkIfLabelUsedIsFound(second,addrMethod,line_num)){
		valid=0;
		return valid;
	}

	if(addrMethod==0){
		if(!convertImmediateOperand(second,valid,line_num)){
			valid=0;
		}
	}
	else if(addrMethod==1){
		if(!convertDirectOperand(second)){
			valid=0;
		}
	}
	else if(addrMethod==2){
		convertIndexOperand(second,valid);
	}
	else{/*3*/
		convertRegisterOperand(second,valid,2);
	}

	return valid;
}

int convertLineToBinWord(char *operation, char *operands, int isFirst, int isCode, int isData, int line_num){

	char *first, *second;
	int arr[2]={-1,-1},valid=1;

	if(isCode){
		first = strtok(operands, ", \n\t\v\f\r");
		second = strtok(NULL, ", \n\t\v\f\r");
		if(first && second){
			arr[0] = get_addressMethod_type(first);
			arr[1] = get_addressMethod_type(second);/*destination*/
		}
		else if(first){ 
			arr[1] = get_addressMethod_type(first);/*destination*/
		}/*-1 means operand is NULL or a dataInstruction operand*/
	}

	if(isFirst && isCode){
		convertFirstCodeWord(arr[0],arr[1],operation);
		increaseIC(1);

		if(arr[0]!=-1){ /*there are two operands*/

			if(arr[0]==3 && arr[1]==3){
				convertTwoRegisters(first,second);
			}
			else{
				if(!convertFirstOperand(first,line_num,arr[0],valid)){
					valid=0;
				}
				if(!convertSecondOperand(second,line_num,arr[1],valid)){
					valid=0;
				}
			}
		}

		else if(arr[1]!=-1){/*one operand exists as destination*/
			if(!convertFirstOperand(first,line_num,arr[1],valid)){
				valid=0;
			}
		}
		/*if else no need to translate anymore words cause no operands exist*/
	}

	if(isData){
		if(!strcmp(operation,DATA)){
			convertDataOperand(operands);
		}
		else if(!strcmp(operation,STRING)){
			convertStringOperand(operands);
		}
		else{
			convertStructOperand(operands);
		}
	}
	
	return valid;
}

void convertFirstCodeWord(int first, int second, char *operation){ /*words with opcode*/

	int opcode;
	char *word;

	word = (char*)malloc(11*sizeof(char)); /*try to free*/
	strcpy(word,"");

	opcode = get_operation_orderNum(operation);
	strcat(word, numToBin(opcode,0,1,1,0));
	if(first==-1 && second==-1){ /*the operation has no given operands, for example rts or hlt*/
		strcat(word, "000000");
		addWord(getIC(), word);
	}

	else if(first==-1){
		strcat(word, "00"); /*zero value to destination operand*/
		switch(second){
			case(0):
				strcat(word,"00");
				break;
			case(1):
				strcat(word,"01");
				break;
			case(2):
				strcat(word,"10");
				break;

			case(3):
				strcat(word,"11");
				break;
		}
		strcat(word,"00");
		addWord(getIC(), word);
	}

	else{
		switch(first){
			case(0):
				strcat(word,"00");
				break;
			case(1):
				strcat(word,"01");
				break;
			case(2):
				strcat(word,"10");
				break;

			case(3):
				strcat(word,"11");
				break;
		}
		switch(second){
			case(0):
				strcat(word,"00");
				break;
			case(1):
				strcat(word,"01");
				break;
			case(2):
				strcat(word,"10");
				break;

			case(3):
				strcat(word,"11");
				break;
		}
		strcat(word,"00");
		addWord(getIC(), word);
	}
}
