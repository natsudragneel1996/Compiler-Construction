/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
void printData(FILE*fp);
void printLogicalAnd(int r1,int r2,FILE *fp);
void printLogicalOr(int r1,int r2,FILE *fp);
void printReadNum(int r,char* s,FILE*fp);
void printReadVar(int r,char* s,int o,FILE*fp);
void printWriteVar(char* var,char*s,int o,FILE*fp);
void printAdder(char* op1,char* op2,FILE*fp);
void printSub(char* op1,char* op2,FILE*fp);
void printMul(char* op1,char* op2,FILE*fp);
void printDiv(char* op1,char* op2,FILE*fp);
void printIORead(char* s,int offset,FILE*fp);
void printIOWrite(char* s,FILE*fp);
void printLogicalNot(int r,FILE*fp);
void printCompare(char* res1,char* res2,FILE*fp);
void printCompareToNum(int r,int n,FILE*fp);
char* getRegister(ast_node* ptr,int offset,FILE*fp);
void printAssignmentStament(ast_node* ptr,FILE*fp);
void printRecdAssignmentStament(ast_node* ptr,FILE*fp);
int printBooleanExpression(ast_node* ptr,FILE*fp);
void printIterativeStament(ast_node* ptr,FILE*fp);
void printConditionalStament(ast_node* ptr,FILE*fp);
void printIOStament(ast_node* ptr,FILE*fp);
void printICG(ast_node* ptr,FILE*fp);
void printvar(FILE*fp);
