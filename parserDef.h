/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/


typedef struct nodes{
	int id;
	int parentId;
	char *value;
	int prodRule;
	int child_size;
	struct nodes* children[10];
	int line_no;
}node;

typedef struct prodRules{
	int id;
	int leftHand;
	int righthand[15];
}prodRule;

typedef struct nonTerminals{
	int id;
	char name[30];
	int first_count;
	int first[20];
	int follows_count;
	int follows[20];
	int table[54] ;
}nonTerminal;



int nonTerminalsArraySize;

nonTerminal* nonTerminalsArray;

int prodRulesArraySize;

prodRule* prodRulesArray;

node* Root;

int parsing_err;


int  parse_num;

