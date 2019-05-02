/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<malloc.h>
#include <string.h>
#include "astDef.h"
#include "symbolTableDef.h"

//returns starting line for all childrens a given node
int getLine_start(ast_node* ptr){
	if(ptr->line_no != -1){
		return ptr->line_no;
	}else{
		return getLine_start(ptr->children[0]); 
	}
}

//returns ending line for all childrens a given node
int getLine_end(ast_node* ptr){
	if(ptr->line_no != -1){
		return ptr->line_no;
	}else{
		return getLine_start(ptr->children[(ptr->child_size)-1]); 
	}
}

//returns type for all terminals and non terminals belong to arithmetic expression with refence to symbol table
int getType(ast_node* ptr,int fun_index){
	//TK_INT or TK_NUM
	if(ptr->id == 11||ptr->id == 49){
		return 11;
	}
	//TK_REAL or TK_RNUM
	if(ptr->id == 12||ptr->id == 50){
		return 12;
	}
	//TK_ID and belongs to other function
	if(ptr->id == 48 && fun_index>=0){
		int i =0;
		for(i =0;i<sym.global_num;i++){
			if(strcmp(sym.g[i].v_name->value,ptr->value)==0){
				return getType(sym.g[i].type,fun_index);
			}
		}
		for(i =0;i<sym.f[fun_index].input_num;i++){
			if(strcmp(sym.f[fun_index].input[i].v_name->value,ptr->value)==0){
				return getType(sym.f[fun_index].input[i].type,fun_index);

			}
		}
		for(i =0;i<sym.f[fun_index].output_num;i++){
			if(strcmp(sym.f[fun_index].output[i].v_name->value,ptr->value)==0){
				return getType(sym.f[fun_index].output[i].type,fun_index);
			}
		}
		for(i =0;i<sym.f[fun_index].var_num;i++){
			if(strcmp(sym.f[fun_index].var[i].v_name->value,ptr->value)==0){
				return getType(sym.f[fun_index].var[i].type,fun_index);
			}
		}
		for(i =0;i<sym.recd_num;i++){
			if(strcmp(sym.r[i].rec_name->value,ptr->value)==0){
				return i;
			}
		}
		//printf("variable not declared\n");
		return -1;
	}
	//TK_ID and belongs to main
	if(ptr->id == 48 && fun_index<0){
		int i =0;
		for(i =0;i<sym.global_num;i++){
			if(strcmp(sym.g[i].v_name->value,ptr->value)==0){
				return getType(sym.g[i].type,fun_index);
			}
		}
		for(i =0;i<sym.m.var_num;i++){
			if(strcmp(sym.m.var[i].v_name->value,ptr->value)==0){
				return getType(sym.m.var[i].type,fun_index);
			}
		}
		
		//printf("variable not declared\n");
		return -1;
	}
	//TK_RECORDID
	if(ptr->id == 52){
		int i =0;
		for(i =0;i<sym.recd_num;i++){
			if(strcmp(sym.r[i].rec_name->value,ptr->value)==0){
				return i;
			}
		}
	}
	//allVar or singleOrRecordid
	if(ptr->id == 128||ptr->id == 144){
		int recd_type = getType(ptr->children[0],fun_index);
		int i =0;
		for(i = 0;i<sym.r[recd_type].var_num;i++){
			if(strcmp(sym.r[recd_type].var[i].v_name->value,ptr->children[1]->value)==0){
				return getType(sym.r[recd_type].var[i].type,fun_index);
			}
		}
		//printf("field variable not declared\n");
		return -1;
	}
	//arthemetic expression
	if(ptr->id == 130){
		int result1 = getType(ptr->children[0],fun_index);
		int result2 = getType(ptr->children[1],fun_index);
		if(result1==result2)
			return result1;
		else
			printf("line:%d:low precedence operation between the types is not allowed\n",getLine_start(ptr));
			return -1;
	}
	//expPrime
	if(ptr->id == 139){
		if(ptr->child_size>2){
			int result1 = getType(ptr->children[1],fun_index);
			int result2 = getType(ptr->children[2],fun_index);
			if(result1==result2){
				return result1;
			}
			else{
				printf("line:%d:low precedence operator between the types is not allowed\n",getLine_start(ptr));
				return -1;
			}
		}else{
			return getType(ptr->children[1],fun_index);
		}
	}
	//factor
	if(ptr->id == 138){
		int result1 = getType(ptr->children[0],fun_index);

		int result2 = getType(ptr->children[1],fun_index);
		if(result1 < 10){
			int i =0;
			for(i =0;i<sym.r[result1].var_num;i++){
				if(result2!=sym.r[result1].var[i].type->id){
					printf("line:%d:high precedence operator between the types is not allowed\n",getLine_start(ptr));
					return -1;
				}
			}
			return result1;
		}
		if(result1 == result2 && result1>10){
			return result1;
		}else{
			printf("line:%d:high precedence operator between the types is not allowed\n",getLine_start(ptr));
		}
		return -1;
	}
	//termPrime
	if(ptr->id == 142){
		if(ptr->child_size>2){
			int result1 = getType(ptr->children[1],fun_index);
			int result2 = getType(ptr->children[2],fun_index);
			if(result1==result2 && result1>10){
				return result1;
			}
			else{
				printf("line:%d:high precedence operator between the types is not allowed\n",getLine_start(ptr));
				return -1;
			}
		}else{
			return getType(ptr->children[1],fun_index);
		}
	}
	return -1;		
}



//returns type in a string
char* typeToString(int t){
	if(t == 11){
		char* s = "int";
		return s;
	}else if(t == 12){
		char*s = "real";
		return s;
	}else if(t == -1){
		char*s = "(undeclared)";
		return s;
	}else{
		char *s = malloc(sizeof(char)*40);
		s[0] = '\0';
		int i =0;
		strcat(s,typeToString(getType(sym.r[t].var[0].type,-1)));
		for(i = 1;i<sym.r[t].var_num;i++){
			strcat(s," x ");
			strcat(s,typeToString(getType(sym.r[t].var[i].type,-1)));
		}
		return s;
	}
}


