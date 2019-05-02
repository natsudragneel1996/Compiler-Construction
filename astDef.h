/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
typedef struct ast_nodes{
	int id;
	int parentId;
	char *value;
	int child_size;
	struct ast_nodes* children[5];
	int line_no;
}ast_node;

int ast_num;
