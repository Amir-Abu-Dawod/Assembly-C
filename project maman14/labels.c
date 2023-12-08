#include "dataHeaders.h"

static Labels *head=NULL;
static int countEntryLabels=0;
static int countExtLabels=0;

int isDefined(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->defined;
		}
		temp=temp->next;
	}
	return 0;
}

int getValue(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->val;
		}
		temp=temp->next;
	}
	return 0;
}
int getCode(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->code;
		}
		temp=temp->next;
	}
	return 0;
}

int getData(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->data;
		}
		temp=temp->next;
	}
	return 0;
}
int getEntry(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->entry;
		}
		temp=temp->next;
	}
	return 0;
}

int getExtern(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->external;
		}
		temp=temp->next;
	}
	return 0;
}

int getLineNum(char *label_name){

	Labels *temp = head;

	if(temp==NULL){
		return 0;
	}

	while(temp!=NULL){
		if(!strcmp(label_name, temp->name)){
			return temp->line_n;
		}
		temp=temp->next;
	}
	return 0;
}

int is_label_found(char *label_name){
	Labels *temp =head;
	
	if(temp == NULL){
		return 0;
	}
	while(temp != NULL){
	
		if(!strcmp(label_name, temp->name)){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
	
}

int isLabel(char *label_name){ /*if token is a label format (ending with ':', below 31 size) and starts with an alpha*/
	
	int i;	
	
	if(strlen(label_name)<31 && isalpha(label_name[0])){

		for(i=1;i<strlen(label_name);i++){
			if(!isalnum(label_name[i])){
				return 0;
			}
		}
	}
	return 1;
}


int is_label_name_entry_extern(char *label_name){

	if(!strcmp(label_name, ENTRY)){
		fprintf(stderr, "\nError! label name is the same as %s\n", ENTRY);
		return 1;
	}
	else if(!strcmp(label_name, EXTERN)){
		fprintf(stderr, "\nError! label name is the same as %s\n", EXTERN);
		return 1;
	}
	else{
		return 0;
	}
}

int is_label_name_register(char *label_name){

	int result;

	result = is_register_name(label_name);
	if(result){
		fprintf(stderr, "\nError! label name is a register\n");
		return 1;
	}
	else{
		return 0;
	}
}

int is_label_name_dataInstruction(char *label_name){ /*if label name equals to .data or .*/
	
	return is_dataInstruction(label_name);
}

int is_label_name_op(char *label_name){ /*if label name is the same as one of the 16 operations*/

	return is_operation_name(label_name);
}

int is_label_name_macro(char *label_name){

	return is_label_macro(label_name);
}

int addSymbol(char *label_name, unsigned value, unsigned isCode, unsigned isData, unsigned isEntry, unsigned isExternal, int line_num, int def){

	Labels *temp = head;
	int found;

	found = is_label_found(label_name);

	if(head==NULL){/*first label define*/
		head = (Labels*)malloc(sizeof(Labels));
		if(head==NULL){
			fprintf(stderr ,"\nError! label allocation failed, out of memory\n");
			return 0;
		}
		strcpy(head->name, label_name);
		head->line_n = line_num;
		head->val = value;
		head->code = isCode ? 1 : 0;
		head->data = isData ? 1 : 0;
		head->external = isExternal ? 1 : 0;
		head->entry = isEntry ? 1 : 0;
		head->defined = def;
		head->next = NULL;

		free(temp);

		if(isEntry){
			countEntryLabels++;
		}
		else if(isExternal){
			countExtLabels++;
		}
	}
	else{
		int is_defined, entry_val, extern_val;
		found = is_label_found(label_name);
		is_defined = isDefined(label_name);
		if(found){
			if(is_defined){
				fprintf(stderr, "\nError! in line %d trying to define an already defined label\n",line_num);
				return 0;
			}
			else if(getExtern(label_name)){
				fprintf(stderr, "\nError! in line %d trying to define a label after a previous extern declared on the same label\n",line_num);
				return 0;
			}
			while(strcmp(temp->name, label_name)){
				temp=temp->next; /*till label is found*/
			}
			entry_val = getEntry(label_name);
			extern_val = getExtern(label_name);

			if(def==1 && !is_defined){
				is_defined=1;
			}
			temp->defined = is_defined;
			temp->line_n = line_num;
			temp->val = value;
			temp->code = isCode ? 1 : 0;
			temp->data = isData ? 1 : 0;
			temp->external = extern_val ? 1 : 0;
			temp->entry = entry_val ? 1 : 0;

			if(entry_val){
				countEntryLabels++;
			}
			else if(extern_val){
				countExtLabels++;
			}
		}

		else{
			while(temp->next != NULL){
				temp=temp->next;
			}
			temp->next = (Labels*)malloc(sizeof(Labels));
			if(temp->next == NULL){
				fprintf(stderr, "\nError! label allocation failed, out of memory\n");
				return 0;
			}
			temp = temp->next;
			strcpy(temp->name, label_name);

			temp->line_n = line_num;
			temp->val = value;
			temp->code = isCode ? 1 : 0;
			temp->data = isData ? 1 : 0;
			temp->external = isExternal ? 1 : 0;
			temp->entry = isEntry ? 1 : 0;
			temp->defined = def;
			temp->next = NULL;

			if(isEntry){
				countEntryLabels++;
			}
			else if(isExternal){
				countExtLabels++;
			}
		}
	}
	return 1;
	
}

int is_label_name_valid(char *name){

	return (!is_label_name_entry_extern(name) && !is_label_name_register(name) && !is_label_name_dataInstruction(name) && !is_label_name_op(name) && !is_label_name_macro(name));
}

int isDataType(char *token){

	return is_dataInstruction(token);
}

int isCodeType(char *token){

	return is_operation_name(token);
}

int handleLabel(char *line, char *token, char *label_name, int line_num){/*label define*/

	int valid, symbol_result;
		
	if(isLabel(label_name) && is_label_name_valid(label_name)){

		token = strtok(NULL, " \n\t\v\f\r");/*token now must be either an instruction or an operation name*/

		if(isCodeType(token)){ /*token is a Code operation*/
			int label_IC = getIC();

			if(!handleOperation(line,token,line_num)){
				valid=0;
			}
			symbol_result = addSymbol(label_name,label_IC,1,0,0,0,line_num,1);
			if(!symbol_result){
				valid=0;
			}	
		}

		else if(isDataType(token)){/*if label comes before .data or .struct or .string word*/
			int label_DC = getDC();
			if(!handleInstruction(line,token,line_num)){
				valid=0;
			}
			symbol_result = addSymbol(label_name,label_DC,0,1,0,0,line_num,1);
			if(!symbol_result){
				valid=0;
			}
		}

		else{
			if(token!=NULL){ /*still not the end of line*/
				fprintf(stderr, "\nError! an illegal word came after the label define at line %d\n",line_num);
			}
			else{/*end of line*/
				fprintf(stderr, "\nError! nothing comes after the label define at line %d\n",line_num);
			}
		}
	}
	else{
		valid=0;
	}
	return valid;
}

int handle_externalEntry(char *token, int line_num, int isEx, int isEn){

	char *label_name, *extra;

	label_name = strtok(NULL, " \n\t\v\f\r");
	if(label_name==NULL){
		fprintf(stderr, "\nError! missin a label name in line %d\n",line_num);
		return 0;
	}
	extra = strtok(NULL, " \n\t\v\f\r");
	if(extra){
		fprintf(stderr, "\nError! extra arguments after label name in line %d\n",line_num);
		return 0;
	}

	if(is_label_name_valid(label_name) && isLabel(label_name)){

		if(is_label_found(label_name)){
			int label_entry_value, label_extern_value, isCode, isData, value, defined;

			label_entry_value = getEntry(label_name);
			label_extern_value = getExtern(label_name);
			isCode = getCode(label_name);
			isData = getData(label_name);
			value = getValue(label_name);
			defined = isDefined(label_name);
			line_num = getLineNum(label_name);

			if(isEn && label_entry_value){
				fprintf(stderr,"\nError! trying to declare a label as entry again, label name: %s\n",label_name);
				return 0;
			}
			else if(isEx && label_entry_value){
				fprintf(stderr,"\nError! an extern declaration after a previous entry declared on the same label: %s\n",label_name);
				return 0;
			}
			else if(isEn && label_extern_value){
				fprintf(stderr,"\nError! an entry declaration after a previous extern declared on the same label: %s\n",label_name);
				return 0;
			}
			else if(isEx && label_extern_value){
				fprintf(stderr,"\nError! trying to declare a label as extern again, label name: %s\n",label_name);
				return 0;
			}
			else if(isEx && defined){
				fprintf(stderr,"\nError! extern declaration on a label which has been already defined in the current file, label name: %s\n",label_name);
				return 0;
			}

			else{
				return addSymbol(label_name,value,isCode,isData,isEn,isEx,line_num,defined);
			}
		}
		else{
			addSymbol(label_name,0,0,0,isEn,isEx,0,0);
		}
	}
	else{
		fprintf(stderr, "\nError! illegal label name in line %d\n",line_num);
	}

	return 1;
}

int check_entryLabels(){ /*checks if the .entry assigned labels is defined in the current file*/

	Labels *temp = head;
	int valid=1;

	while(temp!=NULL){
		if(temp->entry && !temp->defined){
			fprintf(stderr, "\nError! label name: %s is declared as .entry but hasn't been defined in this file\n",temp->name);
			valid=0;
		}
		temp=temp->next;
	}
	return valid;
}

void adjust_dataLabels_value(){ /*it sets the data labels to be afer the code labels in memory*/

	Labels *temp =head;
	int last_IC = get_pass1IC() + MEMORY_START;
	while(temp!=NULL){
		if(temp->data){
			temp->val += last_IC;
		}
		temp=temp->next;
	}
}

int isExtFileNeeded(){
	return countExtLabels ? 1 : 0;
}

int isEntFileNeeded(){
	return countEntryLabels ? 1 : 0;
}

void writeEntryLabels(FILE *ent){

	int cnt=0;
	Labels *temp=head;

	while(temp!=NULL && cnt < countEntryLabels){
		if(temp->entry){
			fprintf(ent, "%s\t%s\n", temp->name, decimalToBase32(temp->val));
			cnt++;
		}
		temp=temp->next;
	}
}

void writeExtLabels(FILE *ext){

	int cnt=0;
	while(cnt < get_countExtLabels()){
		fprintf(ext, "%s\t%s\n", getExtName(cnt),decimalToBase32(getExtValues(cnt)));
		cnt++;
	}
}

void destroy_labels(){
	if(head==NULL){
		return;
	}

	while(head!=NULL){
		Labels *temp = head;
		head=head->next;
		free(temp);
	}
	countEntryLabels=0;
	countExtLabels=0;
	destroy_extLabels();
}
