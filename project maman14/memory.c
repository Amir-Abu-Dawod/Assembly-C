#include "dataHeaders.h"

static ExternValues *head=NULL;
static BinaryWord *binWord=NULL;
static int countExtLabels =0;
static int IC = MEMORY_START;
static int DC = 0;
static int pass1_IC;
static int pass1_DC;

int getIC(){

	return IC;
}

int getDC(){

	return DC;
}

int get_pass1IC(){

	return pass1_IC;
}

int get_pass1DC(){

	return pass1_DC;
}

void increaseDC(int num){

	DC += num;
}

void increaseIC(int num){

	IC += num;
}

void reset_ICDC_counters(){
	IC =0;
	DC =0;
}

void set_pass1counters(){
	pass1_IC = getIC() - MEMORY_START;
	pass1_DC = getDC();
}

void allocateMemoryWord(){

	int i, size = get_pass1IC() + get_pass1DC();

	binWord = (BinaryWord*)malloc(size*sizeof(BinaryWord));
	for(i=0;i<size;i++){
		binWord[i].word = (char*)malloc(MAX_BIN_WORD*sizeof(char)); /*10 digits plus one ending character \0*/
	}
}

void addWord(int index, char *newWord){

	strcpy(binWord[index].word,newWord);
}

void printCodeWords(){

    	int wordIndex = 0;

	printf("\nMACHINE CODE words:\n");

    	while (wordIndex < pass1_IC + pass1_DC) {
        	printf("Word %d: %s\n", wordIndex + 1, binWord[wordIndex].word);
        	wordIndex++;
    	}
}

void print_binImg(){

	int i, size = get_pass1IC() + get_pass1DC();

	printf("\nbinary machine words:\n");
	for(i=0;i<size;i++){
		printf("\n%s\n",binWord[i].word);
	}
}


int add_externValue(char *label_name, int value){ /*saves every memory used as extern to export .ext files*/

	ExternValues *temp = head;
	if(head==NULL){
		head = (ExternValues*)malloc(sizeof(ExternValues));
		if(head==NULL){
			fprintf(stderr ,"\nError! extern label value allocation failed, out of memory\n");
			return 0;
		}

		strcpy(head->name,label_name);
		head->val = value + MEMORY_START;
		head->next=NULL;
		countExtLabels++;
	}
	else{
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next = (ExternValues*)malloc(sizeof(ExternValues));
		temp=temp->next;
		strcpy(temp->name,label_name);
		temp->val = value + MEMORY_START;
		temp->next=NULL;
		countExtLabels++;
	}
	return 1;
}

char *getBinWord(int index){
	return binWord[index].word;
}

int get_countExtLabels(){
	return countExtLabels;
}

int getExtValues(int position){
	ExternValues *temp = head;
	int counter=0;

	while(counter!=position){
		temp=temp->next;
		counter++;
	}
	return temp->val;
}

char *getExtName(int position){
	ExternValues *temp = head;
	int counter=0;

	while(counter!=position){
		temp=temp->next;
		counter++;
	}
	return temp->name;
}

void destroy_extLabels(){
	if(head==NULL){
		return;
	}

	while(head!=NULL){
		ExternValues *temp = head;
		head=head->next;
		free(temp);
	}
	countExtLabels =0;
	IC = MEMORY_START;
	DC = 0;
}

void destroy_binWords(){
	int i, size = get_pass1IC() + get_pass1DC();

	if(binWord==NULL){
		return;
	}
	i=0;
	while(i<size){
		free(binWord[i].word);
		i++;
	}
	free(binWord);
}
