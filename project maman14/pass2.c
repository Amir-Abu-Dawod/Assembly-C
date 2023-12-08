#include "dataHeaders.h"

static int validity =1;

int second_pass(FILE *target, char *fileName){

	char line[MAX_LINE], *token, temp_line[MAX_LINE], label_name[MAX_LINE], *targetName;
	int line_num =1;
	char *operation, *operands;

	targetName = (char*)malloc(strlen(fileName)*sizeof(char));
	strcpy(targetName,fileName);
	if(!check_entryLabels()){
		validity=0;
	}

	set_pass1counters();
	reset_ICDC_counters();/*reset counters IC,DC,pass1IC and pass1DC*/
	adjust_dataLabels_value();
	allocateMemoryWord();

	target = fopen(strcat(targetName,".am"), "r");
	if(target==NULL){
		fprintf(stderr, "\nError! failed to open file target in pass1\n");
	}

	operation = (char*)malloc(7*sizeof(char));
	operands = (char*)malloc(MAX_LINE*sizeof(char));

	while(fgets(line,MAX_LINE,target) != NULL){
		strcpy(temp_line,line); /*save the content of the current line*/
		token = strtok(line, " \n\t\v\f\r");
		if(*token!=';' && token!=NULL && strcmp(token, EXTERN) && strcmp(token, ENTRY)){ /*skip .entry and .extern*/
			if(!strcmp(token + strlen(token) -1, ":")){/*found a form of defining a label*/

				set_label_name(token, label_name);
				token = strtok(NULL, " \n\t\v\f\r");
				strcpy(operation,token);
				operands = strstr(temp_line, operation) + strlen(operation);
				operands = remove_leftSpaces(operands);

				if(is_operation_name(operation)){ /*first we print the code labels*/
					if(!convertLineToBinWord(operation,operands,1,1,0,line_num)){
						validity=0;
					}
				}
				else{
					if(!convertLineToBinWord(operation,operands,1,0,1,line_num)){
							validity=0;
					}
				}
				
			}

			else{
				strcpy(operation,token);
				operands = strstr(temp_line, operation) + strlen(operation);
				operands = remove_leftSpaces(operands);

				if(is_operation_name(operation)){
					if(!convertLineToBinWord(operation,operands,1,1,0,line_num)){
							validity=0;
					}
				}

				else if(is_dataInstruction(operation)){
					if(!convertLineToBinWord(operation,operands,1,0,1,line_num)){
							validity=0;
					}
				}
			}
		}
		line_num++;
	}

	reset_ICDC_counters();
	rewind(target);

	if(!validity){
		printf("\nSECOND PASS has ended up with errors thus no output files will be exported\n");
		validity=1;
		return 0;
	}
	else{
		return 1;
	}
}
