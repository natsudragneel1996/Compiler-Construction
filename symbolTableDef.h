/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
typedef struct vars{
	ast_node* type;
	ast_node* v_name;
	int width;
	int offset;
}variables;

typedef struct mainTables{
	int var_num;
	ast_node* mainNode;
	variables var[10];
}mainTable;

typedef struct funcTables{
	char *fname;
	ast_node* funNode;
	int input_num;	
	variables input[10];
	int output_num;
	variables output[10];
	int var_num;
	variables var[10];
}funcTable;


typedef struct recdTables{
	ast_node* rec_name;
	int var_num;
	variables var[10];
}recdTable;


typedef struct symbolTables{
	mainTable m;
	funcTable* f;
	int recd_num;
	recdTable r[10];
	int global_num;
	variables g[10];
}symbolTable;

symbolTable* s;
symbolTable sym;
int funct_index;

