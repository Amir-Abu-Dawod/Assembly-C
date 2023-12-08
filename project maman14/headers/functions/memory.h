/*
@function: int getIC();
@parameters: no parameters passed.

@description: the function return the current value of the IC counter.
*/
int getIC();
/*
@function: int getDC();
@parameters: no parameters passed.

@description: the function return the current value of the DC counter.
*/
int getDC();
/*
@function: int get_pass1IC();
@parameters: no parameters passed.

@description: the function return the current value of the pass1IC counter.
*/
int get_pass1IC();
/*
@function: int get_pass1DC();
@parameters: no parameters passed.

@description: the function return the current value of the pass1DC counter. 
*/
int get_pass1DC();
/*
@function: void increaseDC(int num);
@parameters: int num

	int num: 

@description: the function increases the current value of the DC counter by 1.
*/
void increaseDC(int num);
/*
@function: void increaseIC(int num);
@parameters: int num

	int num: 

@description: the function increases the current value of the IC counter by 1.
*/
void increaseIC(int num);
/*
@function: void reset_ICDC_counters();
@parameters: no parameters passed.

@description: the function resets the value of the counters IC and DC to their starting values.
*/
void reset_ICDC_counters();
/*
@function: void set_pass1counters();
@parameters: no parameters passed.

@description: the function sets the value of pass1IC and pass1DC counters to be equals to the last value of IC and DC counters accordingly.
*/
void set_pass1counters();
/*
@function: void allocateMemoryWord();
@parameters: no parameters passed.

@description: the function allocates a memory for the struct (BinaryWord) binWord which saves all the binary words of each line after converting.
*/
void allocateMemoryWord();
/*
@function: void addWord(int index, char *newWord);
@parameters: int index, char *newWord

	int index: holds the index of the binary word in which it should be saved, code operations are saved before any data instruction.
	char *newWord: holds the content of the new binary word that must be added to the struct binWord.

@description: the function adds a new binary word to the struct binWord which saves each binary word.
*/
void addWord(int index, char *newWord);
/*
@function: int add_externValue(char *label_name, int value);
@parameters: char *label_name, int value

	char *label_name: holds the name of the current label.
	int value: holds the compatible value of the current extern label which is being used in the current line.

@description: the function adds a new extern label value each time the compiler finds an extern label which is being used.
*/
int add_externValue(char *label_name, int value);
/*
@function: char *getBinWord(int index);
@parameters: int index

	int index: holds the index of the compatible passed binary word.

@description: the function return the binary word from the struct binWord according to the given index.
*/
char *getBinWord(int index);
/*
@function: int get_countExtLabels();
@parameters: no parameters passed.

@description: the function returns the value of the global counter of extern labels.
*/
int get_countExtLabels();
/*
@function: int getExtValues(int position);
@parameters: int position

	int position: holds the number of the position in which the extern label must be found.

@description: the function returns the value of the extern label which sets in the given position.
*/
int getExtValues(int position);
/*
@function: char *getExtName(int position);
@parameters: int position

	int position: holds the number of the position in which the extern label must be found.

@description: the function returns the name of the extern label which sets in the given position.
*/
char *getExtName(int position);
/*
@function: void destroy_extLabels();
@parameters: no parameters passed.

@description: the function destroys the struct ExternValues which saves all the extern labels and their values.
*/
void destroy_extLabels();
/*
@function: void destroy_binWords();
@parameters: no parameters passed.

@description: the function destroys the struct binWord which saves all the binary words.
*/
void destroy_binWords();

void printCodeWords();

