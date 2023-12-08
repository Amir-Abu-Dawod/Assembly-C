#include "dataHeaders.h"

void exportFiles(FILE *target, char *fileName, int isEnt, int isExt){

	FILE *ob=NULL, *ent=NULL, *ext=NULL;
	
	obExport(ob,fileName);

	if(isEnt){
		extExport(ent,fileName);
	}
	if(isExt){
		entExport(ext,fileName);
	}
}

void obExport(FILE *obFile, char *fileName){

	char *name, *line;
	int i;

	line = (char*)malloc(7*sizeof(char));
	strcpy(line,"");
	name = (char*)malloc(strlen(fileName)*sizeof(char));
	strcpy(name,fileName);
	strcat(name,".ob");

	obFile = fopen(name, "w");
	for(i=0;i<(get_pass1IC()+get_pass1DC());i++){

		strcat(line,decimalToBase32(100+i));
		strcat(line,"\t");
		strcat(line,binToBase32(getBinWord(i)));
		fputs(line, obFile);
		fprintf(obFile,"\n");
		strcpy(line,"");
	}
	free(line);
}

void entExport(FILE *entFile, char *fileName){
	char *name;

	name = (char*)malloc(strlen(fileName)*sizeof(char));
	strcpy(name,fileName);
	strcat(name,".ent");

	entFile = fopen(name, "w");
	writeEntryLabels(entFile);
}

void extExport(FILE *extFile, char *fileName){

	char *name;

	name = (char*)malloc(strlen(fileName)*sizeof(char));
	strcpy(name,fileName);
	strcat(name,".ext");

	extFile = fopen(name, "w");
	writeExtLabels(extFile);
}
