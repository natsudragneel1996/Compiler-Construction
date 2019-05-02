/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
void assignTester(ast_node* ptr,int fun_index);
void checkMultipleDeclaration();
void isDeclaredVariable(ast_node* ptr,int fun_index);
void checkVariableDeclared();
void checkUniqueGlobalVariables();
void checkInputParCompatability(ast_node* ptr,int f_ind,int called_func_id);
void checkOutputParCompatability(ast_node* ptr,int f_ind,int called_func_id);
void checkCallStmt(ast_node* ptr,int f_ind);
void checkCallCompatibility();
void checkFunctionOverloding();
int isExist(ast_node* ptr,ast_node* scope);
int isAssigned(ast_node* ptr,ast_node* scope);
void isReturnAssigned(ast_node* ptr,int f_ind);
void getReturnStmt(ast_node* ptr,int f_ind);
void checkReturnStmnt();
int isWhileUpdating(ast_node* cond,ast_node* ptr);
void getIterativeStmt(ast_node* ptr,int f_ind);
void checkWhilestmnt();
int isBooleanExp(ast_node* ptr,int f_ind);
void getBooleanStmt(ast_node* ptr,int f_ind);
void checkBooleanStmt();
void checkAssignCompatibility();
void symanticAnalysis(ast_node* ptr);
