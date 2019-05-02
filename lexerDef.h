/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
typedef struct tokens{
    char  keyword[20];
    int  id;
    char  tokenid[20];
    int  keylen;
    char postkey[10];
    int postlen;
}token;

typedef struct containers{
	token t;
	char *val;
	int line_no;
	int err_status;
}tokenInfo;


token* token_array;

int token_arraySize;

int array_size;

int status;

int MODE;

int lexical_err;


