#include "dataHeaders.h"

static int is_macro_found =0;
static Macros *head = NULL;
static char *macro_content;
static int validity =1;

int macro_analysis(FILE *src, FILE *target, char *fileName){
	
	char line[MAX_LINE], *token = NULL, *targetName;
	int line_num=1, check_macro=0, if_nested=0, copy=1, legal=1;
	
	targetName = (char*)malloc(strlen(fileName)*sizeof(char));
	macro_content=(char*)malloc(sizeof(char));

	while(fgets(line,MAX_LINE,src)!=NULL){/*sending row by row to check macros defining*/	
		macro_define_check(line,token,line_num,&check_macro,&if_nested,&legal);/*searching for macro define only*/
		line_num++;
	}

	line_num=1;
	if_nested=0;
	/*macro has found in the source file*/
	rewind(src);
	strcpy(targetName,fileName);
	target = fopen(strcat(targetName, ".am"), "w");

	while(fgets(line,MAX_LINE,src)!=NULL){ /*copying source file content to the target file after parsing macros*/
		if(!macro_analysis2(target,line_num,line, &copy, &if_nested)){
			legal=0;
		}
		line_num++;
	}
	
	free(targetName);
	free(macro_content);
	fclose(target);

	return legal;
}

void macro_define_check(char *line, char *token, int line_num, int *check_macro, int *if_nested, int *legal){
	
	char line_temp[MAX_LINE];

	strcpy(line_temp,line);
	token = strtok(line, " ,\n\t\v\f\r");

	if(token==NULL || !strcmp(token,";")){
		return;
	}
	if(!*check_macro){	 /*if macro define did not appear yet*/
		if(!strcmp(token, "macro")){
			token = (strtok(NULL, " ,\n\t\v\f\r"));/*taking the name of the macro*/
			if(check_macro_name(token) && (strtok(NULL, " \n\t\v\f\r")) == NULL){
		/*if the name is valid && nothing comes after the macro name in the same row => NOTHING IS WRONG*/

				if(!is_macro_found){
					strcpy(macro_content,"");
					*check_macro=1;
					create_firstMacro(token,line_num);
					is_macro_found=1;
					return;
				}
				else{
					create_newMacro(token,line_num);
					*check_macro=1;
					is_macro_found=1;
					return;
				}
			}
			else{
				fprintf(stderr, "\nError! the macro name (%s) in line %d is not valid\n",token,line_num);
				*legal =0;
			}
		}
	}
	else{

		if(!strcmp(token, "macro")){/*macro define has found*/
			fprintf(stderr, "\nError! nested macro definig, cannot make a double macro definition, line %d\n",line_num);
			*if_nested=1;
			*legal=0;
			return;
			/*continue till you find endmacro*/
		}

		if(*if_nested && (!strcmp(token, "endmacro"))){ /*end of the nisted macro definition*/
			*if_nested=0;
			return;
		}
		else if(*if_nested){
			return;
		}
		else if(!strcmp(token,"endmacro") && !*if_nested){	
			*check_macro=0; /*end of valid defining so we reset macro content and keep searching for another macro 						define*/
			save_macro_content();
			macro_content = realloc(macro_content, MAX_LINE);
			strcpy(macro_content, "");
			return;
		}
		else if(!*if_nested && *check_macro){ /*defining macro in a right way without any error*/
			macro_content = (char*)realloc(macro_content, (strlen(macro_content) + MAX_LINE));
			strcat(macro_content, line_temp);/*copying the content of the current macro*/
		}
	}	
}

int macro_analysis2(FILE *target, int line_num, char *line, int *copy, int *if_nested){

	int valid=1;
	Macros *temp = head;
	char *token, s[MAX_LINE];

	strcpy(s,line);
	token = strtok(line, " ,\n\t\v\f\r");
	
	if(token==NULL || !strcmp(token,";")){
		return valid;
	}

	if(strcmp(token, ENTRY) && strcmp(token, EXTERN) && strcmp(token, STRUCT) && strcmp(token, DATA) && (!is_operation_name(token)) && strcmp(token+strlen(token)-1, ":") && strcmp(token, "macro") && strcmp(token, "endmacro")){
		while(temp!=NULL){
			if(!strcmp(token, temp->name)){
				if(line_num < temp->line_n){
					fprintf(stderr, "\nError! macro cannot be used before its definition, line %d\n",line_num);
					valid=0;
				}
				else{
					fputs(temp->content, target);
					return valid;
				}	
			}
			else{
				if(temp->next == NULL){
					fprintf(stderr, "\nError! an attempt to call an undefined macro in a name of: %s, line %d. this word is invalid\n",token,line_num);
					valid=0;
				}
				temp = temp->next;
			}
		}
	}
	/*if copy==0 then we don`t copy any content to the target file, words like macro/endmacro will not be copied*/
	if((!strcmp(token, "macro")) && (!*if_nested)){
		*copy=0;
	}
	if(!strcmp(token, "macro") && !*copy){
		*if_nested=1;
	}
	if(!strcmp(token, "endmacro") && *if_nested){
		*if_nested=0;	
	}
	if(!strcmp(token, "endmacro") && !*if_nested){
		*copy=1;
		return valid;
	}
	if(*copy){	
		fputs(s, target); /*copying normal line content (not a macro content)*/
	}

	return valid;
}

void save_macro_content(){
	Macros *temp = head;

	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->content = malloc(strlen(macro_content));
	strcpy(temp->content, macro_content);
}

int check_macro_name(char *token){
	if(token[strlen(token)-1] ==':'){
		fprintf(stderr, "\nError! macro name ended with ':' similar to Label\n");
		return 0;
	}
	else if(!strcmp(token, DATA) || !strcmp(token, STRING) || !strcmp(token, EXTERN) || !strcmp(token, ENTRY) || !strcmp(token, STRUCT)){
		fprintf(stderr, "\nError! macro name is a prompt name (.data/.string/.entry/.extern)\n");
		return 0;
	}
	else if(is_operation_name(token)){
		fprintf(stderr, "\nError! macro name is an Instruction name\n");
		return 0;
	}
	else{
		return 1;
	}
}

void create_firstMacro(char *token, int line_num){
	head = (Macros*)malloc(sizeof(Macros));
	if(head==NULL){
		fprintf(stderr ,"\nError! macro allocation failed, out of memory\n");
		exit(1);
	}
	head->line_n = line_num;
	strcpy(head->name, token);
	head->next = NULL;
}

void create_newMacro(char *token, int line_num){
	Macros *temp=head;
	
	while(temp->next != NULL){
		temp=temp->next;
	}
	temp->next = (Macros*)malloc(sizeof(Macros));
	if(temp->next == NULL){
		fprintf(stderr, "\nError! macro allocation failed, out of memory\n");
		exit(1);
	}
	temp=temp->next;
	temp->line_n = line_num;
	strcpy(temp->name, token);
	temp->next = NULL;
}

int is_label_macro(char *label_name){

	Macros *temp = head;

	while(temp != NULL){
		
		if(!strcmp(label_name, temp->name)){
			fprintf(stderr, "\nError! label name (%s) is a defined macro name\n",label_name);
			return 1;
		}
		else{
			temp=temp->next;
		}
	}
	return 0;
}

void destroy_macros(){
	if(head==NULL){
		return;
	}

	while(head!=NULL){
		Macros *temp = head;
		head=head->next;
		free(temp);
	}
	is_macro_found=0;
	validity=1;
}
