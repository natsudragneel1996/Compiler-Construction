/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
int is_bd(char c);
int is_notbd(char c);
int is_27(char c);
void initiate_tokenArray();
int checkToken(token* input,token* output,char c,int position);
int* getTokens(char *str);
FILE* getStream(FILE *fp,char *str,int buffersize);
//int  print_terminal(int id,FILE* fp);
int  print_terminalConsole(int id);
void findTokens(FILE* fp,int line,tokenInfo* result,int index);


