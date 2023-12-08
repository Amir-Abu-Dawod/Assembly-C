#include "dataHeaders.h"

int main(int argc, char *argv[])
{
	int i;
	if(argc <= 1){
		fprintf(stderr, "\nError! you did not pass any source file to the assembler!\n");
		exit(1);
	}
	
	for(i=1;i<argc;i++){
		printf("\nHANDLING FILE NUMBER %d\n",i);
		handleCurrentFile(argv[i]);
	}

	return 0;
}

void handleCurrentFile(char *arg){
	
	char *fullFileName, *src;
	FILE *source = NULL, *target = NULL;
	int validity=1;

	fullFileName=(char*)malloc(strlen(arg)*sizeof(char)); /*saves arg file name*/
	strcpy(fullFileName,arg);
	src=(char*)malloc((strlen(fullFileName)+3)*sizeof(char));
	strcpy(src,fullFileName);

	if((source = fopen(strcat(src,".as"), "r")) == NULL){
		fprintf(stderr, "\nFailed to open file: %s\n", fullFileName);
		return;
	}

	validity = macro_analysis(source,target,fullFileName);
	fclose(source);

	strcpy(src,fullFileName);
	target = fopen(strcat(src,".am"), "r");
	rewind(target);

	if(validity){
		if(!first_pass(target, fullFileName)){
			validity=0;
		}
	}
	else{
		fprintf(stderr, "\nPreprocessor run has ending up with errors! thus no files will be exported\n");
	}
	if(validity){
		if(!second_pass(target, fullFileName)){
			validity=0;
		}
	}
	if(validity){ /*exporting only if there were no errors found*/
		/* PRINTING THE MACHINE CODE WORDS*/
		printCodeWords();
		
		if(isExtFileNeeded()){
			if(isEntFileNeeded()){
				exportFiles(target,fullFileName,1,1);
			}
			else{
				exportFiles(target,fullFileName,0,1);
			}
		}
		else{
			if(isEntFileNeeded()){
				exportFiles(target,fullFileName,1,0);
			}
			else{
				exportFiles(target,fullFileName,0,0);
			}
		}
	}

	destroy_macros();
	destroy_labels();
	destroy_binWords();
	destroy_extLabels();
	printf("\n########\tend of checking the current file: (%s)\t########\n",fullFileName);

}
