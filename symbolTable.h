/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
void loadInputPar(ast_node* ptr);
void loadOutputPar(ast_node* ptr);
void loadRecordData(ast_node* ptr);
void loadTypedefs(ast_node* ptr);
void loadDeclarations(ast_node* ptr);
void loadMainDeclarations(ast_node* ptr);
void populatefunctTable(ast_node* ptr);
void populatemainTable(ast_node* ptr);
void populateSymTable(ast_node* ptr);
int getNoOfFunctions(ast_node* ptr);
void printSymTable();
void generateFunoffset(int fun);
void generateOffset();
