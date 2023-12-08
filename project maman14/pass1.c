#include "dataHeaders.h"

static int validity = 1;

void set_label_name(char *token, char *name){ /*returning a name of the label without the ending ":" */

	strcpy(name, token);
	name[strlen(name)-1] = '\0';
}

int first_pass(FILE *target, char *fileName){

	char line[MAX_LINE], *token, temp_line[MAX_LINE], label_name[MAX_LINE], *targetName;
	int line_num =1;

	targetName = (char*)malloc(strlen(fileName)*sizeof(char));
	strcpy(targetName,fileName);
	target = fopen(strcat(targetName,".am"), "r");

	if(target==NULL){
		fprintf(stderr, "\nError! failed to open file target in pass1\n");
	}

	while(fgets(line,MAX_LINE,target) != NULL){

		strcpy(temp_line,line);/*save the content of the current line*/
		token = strtok(line, " \n\t\v\f\r"); /*first word in current line*/
			
		if(*token!=';' && token!=NULL){/*avoid remarks line or space empty line*/
			
			if(!strcmp(token + strlen(token) -1, ":")){/*found a form of defining a label*/

				set_label_name(token, label_name);
				if(!handleLabel(temp_line,token,label_name,line_num)){
					validity=0;
				}	
			}

			else if(is_dataInstruction(token)){
				if(!handleInstruction(temp_line,token,line_num)){
					validity=0;
				}
			}

			else if(is_operation_name(token)){
				if(!handleOperation(temp_line,token,line_num)){
					validity=0;
				}
			}
			else if(!strcmp(token, EXTERN)){
				if(!handle_externalEntry(token,line_num,1,0)){
					validity=0;
				}
			}
			else if(!strcmp(token, ENTRY)){
				if(!handle_externalEntry(token,line_num,0,1)){
					validity=0;
				}
			}
			else{
				fprintf(stderr, "\nError! first word %s at line %d is invalid\n",token,line_num);
			}
		}
		line_num++;
	}
	rewind(target);

	if(!validity){
		fprintf(stderr, "\nFirst run ended up with errors, thus no files will be exported!\n");
		validity=1;
		return 0;
	}
	else{
		return 1;
	}
}

