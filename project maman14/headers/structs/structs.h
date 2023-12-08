typedef struct Macros{
	int line_n; /*line number of the macro define*/
	char name[100];
	char *content;
	struct Macros *next;
}Macros;

typedef struct Labels{
	char name[30];
	int line_n; /*IC or DC*/	
	int val;
	int code;
	int data;
	int external;
	int entry;
	int defined;
	int externAddress;

	struct Labels *next;

}Labels;

struct valid_addressingMethods{

    unsigned int immediate;
    unsigned int direct;
    unsigned int index;
    unsigned int reg;

};

struct Operations{

	char op_name[4];
	unsigned int op; /*number of the operation*/
	struct valid_addressingMethods src;
	struct valid_addressingMethods des;
};

typedef struct{

	char *word;

}BinaryWord;

typedef struct ExternValues{

	char name[30];
	int val;

	struct ExternValues *next;

}ExternValues;

