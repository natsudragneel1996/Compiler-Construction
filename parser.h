/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
//int print(int id,FILE*fp);
int printConsole(int id);
void firstof_firsts(int prodNo, int index);
void findFirsts(int nonTerminal);

void findFollows(int nonTerminal);
void firstof_follows(int input_NT,int prodNo, int index);

void initiate_parser();

void firstof(int prodNo, int index);

void parse(tokenInfo *input);

void createParseTable();

//void printParseTree(node *ptr,FILE *fp);
void printParseTreeConsole(node *ptr);

void printErrorMsg(int stackTop,int token_num,char*val,int line,int info);


