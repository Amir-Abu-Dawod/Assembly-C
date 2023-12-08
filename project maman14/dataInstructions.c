#include "dataHeaders.h"

int is_dataInstruction(char *token){

	if(!strcmp(token, DATA) || !strcmp(token, STRUCT) || !strcmp(token, STRING)){
		return 1;
	}
	else{
		return 0;
	}
}

int handleData(char *token, int valid, int line_num){ /*token send as .data*/

	int isNum, words=0;
	
	token = strtok(NULL, ", \n\t\v\f\r");
	while(token!=NULL){

		isNum = atoi(token);
		if(!isNum && *token !='0'){
			valid=0;
			fprintf(stderr, "\nError! expected number after .data in line %d\n",line_num);
		}
		else if(!isdigit(*(token+strlen(token)-1))){
			valid=0;
			fprintf(stderr, "\nError! expected number after .data in line %d\n",line_num); /*if a number was 4H*/
		}
		else if(strchr(token,'.')){
			valid=0;
			fprintf(stderr, "\nError! expected integer after .data in line %d\n",line_num); /*if a number was 4H*/
		}

		else{
			words++;
		}
		token = strtok(NULL, ", \n\t\v\f\r");
	}
	if(valid){
		increaseDC(words);
	}
	return valid;
}

int handleString(char *token, int valid, int line_num){

	int words=0;
	char *start, *end;

	token = strtok(NULL, ", \n\t\v\f\r");
	if(token==NULL){
		valid=0;
		fprintf(stderr, "\nError! missing a string in line %d\n",line_num);
		return valid;
	}

	start = strchr(token, '\"');
	if(!*start || !start){
		valid=0;
		fprintf(stderr, "\nError! quotes are missing in .string instruction line %d\n",line_num);
		return valid;
	}
	
	else{
		end = strrchr(token, '\"');
		if (start == end && (*start == '\"')){
			valid=0;
			fprintf(stderr, "\nError! second quote missing in line %d\n",line_num);
			return valid;
		}
		if(start == end && (*start != '\"')){
			valid=0;
			fprintf(stderr, "\nError! missing quotes in line %d\n",line_num);
			return valid;
		}
	}
	if(valid){
		words = strlen(start) - strlen(end); /*number of character +1 the ending 0*/
		increaseDC(words);
	}

	return valid;
}

int handleStruct(char *token, int valid, int line_num){

	int first_token=1, isNum, words=0;
	char *start, *end;

	token = strtok(NULL, ", \n\t\v\f\r");


	while(token!=NULL){

		if(first_token){
			isNum = atoi(token);
			if(!isNum && *token !='0'){
				valid=0;
				fprintf(stderr, "\nError! expected number after .string in line %d\n",line_num);
			}
			else if(!isdigit(*(token+strlen(token)-1))){
				valid=0;
				fprintf(stderr, "\nError! expected number after .string in line %d\n",line_num); /*if a number was 4H*/
			}
			else if(strchr(token,'.')){
				valid=0;
				fprintf(stderr, "\nError! expected integer after .string in line %d\n",line_num); /*if a number
 was 4H*/
			}
			else{
				words++;
			}
			first_token=0;
		}
		token = strtok(NULL, ", \n\t\v\f\r");

		if(token==NULL){
			valid=0;
			fprintf(stderr, "\nError! missing a string in line %d\n",line_num);
			return valid;
		}
		start = strchr(token, '\"');
		if(!*start || !start){
			valid=0;
			fprintf(stderr, "\nError! quotes are missing for a struct in line %d\n",line_num);
			return valid;
		}

		else{
			end = strrchr(token, '\"'); /*last appearence of " quotes*/
			if (start == end && (*start == '\"')){
				valid=0;
				fprintf(stderr, "\nError! second quote missing in line %d\n",line_num);
				return valid;
			}
			if(start == end && (*start != '\"')){
				valid=0;
				fprintf(stderr, "\nError! missing quotes in line %d\n",line_num);
				return valid;
			}
		}
		token = strtok(NULL, ", \n\t\v\f\r");
	}
	if(valid){
		words += (strlen(start) - strlen(end)); /*number of character +1 the ending 0*/
		increaseDC(words);
	}
	return valid;
}

int handleInstruction(char *line, char *token, int line_num){

	int valid=1;	
	char *dataName, temp_line[MAX_LINE] ={0};

	dataName = (char*)malloc(4);
	strcpy(dataName,token);
	
	strcpy(temp_line,line); /*handling with commas*/
	strcpy(temp_line,strstr(temp_line, dataName) + strlen(dataName));

	valid = commaSyntax(temp_line,line_num);

	if(!strcmp(token, STRING)){
		valid = handleString(token,valid,line_num);
	}
	else if(!strcmp(token, STRUCT)){
		valid = handleStruct(token,valid,line_num);
	}
	else{
		valid = handleData(token,valid,line_num);
	}
	
	free(dataName);
	return valid;
}
