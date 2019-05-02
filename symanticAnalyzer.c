#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<malloc.h>
#include <string.h>
#include "astDef.h"
#include "symbolTableDef.h"
#include "typeExtractor.h"
#include "symanticAnalyzerDef.h"
//checks semantic(type) correcteness of assinment statements
void assignTester(ast_node* ptr,int fun_index){
	if(ptr->id == 123){
		int line = ptr->children[0]->line_no;
		if(line==-1)
			line = ptr->children[0]->children[0]->line_no;
		int result1 = getType(ptr->children[0],fun_index);
		int result2 = getType(ptr->children[1],fun_index);
		if(result1!=result2 && (result1!= -1) && (result2!= -1)){
			printf("Line:%d:Assignment type mismatch!!!!!!!\n",line);
			semantic_err=1;
		}
	/*	else
			printf("Line:%d:Symantically correct!!!!!!!\n",line);*/
			
	}
	int i =0;
	for(i = 0;i<ptr->child_size;i++){
		assignTester(ptr->children[i],fun_index);
	}
}
//checks if variable declared more than once
void checkMultipleDeclaration(){
	int i =0;
	//variables in main function
	for(i =0;i<sym.m.var_num;i++){
		char* name = sym.m.var[i].v_name->value;
		int j = i+1;
		for(j =i+1;j<sym.m.var_num;j++){
			char* name2 = sym.m.var[j].v_name->value;
			if(strcmp(name,name2)==0){
				printf("line:%d:variable %s already declared\n", sym.m.var[j].v_name->line_no,name);
				semantic_err=1;
			}
		}
	}
	int f_ind = 0;
	//variables in other functions
	for(f_ind = 0;f_ind < funct_index;f_ind++){
		for(i =0;i<sym.f[f_ind].var_num;i++){
			char* name = sym.f[f_ind].var[i].v_name->value;
			int j = i+1;
			for(j =i+1;j<sym.f[f_ind].var_num;j++){
				char* name2 = sym.f[f_ind].var[j].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:variable %s already declared\n", sym.f[f_ind].var[j].v_name->line_no,name);
					semantic_err=1;
				}
			}
			for(j =0;j<sym.f[f_ind].input_num;j++){
				char* name2 = sym.f[f_ind].input[j].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:variable %s already declared\n", sym.f[f_ind].input[j].v_name->line_no,name);
					semantic_err=1;
				}
			}
			for(j =0;j<sym.f[f_ind].output_num;j++){
				char* name2 = sym.f[f_ind].output[j].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:variable %s already declared\n", sym.f[f_ind].output[j].v_name->line_no,name);
					semantic_err=1;
				}
			}
		}
		for(i =0;i<sym.f[f_ind].input_num;i++){
			char* name = sym.f[f_ind].input[i].v_name->value;
			int j = i+1;
			for(j =i+1;j<sym.f[f_ind].input_num;j++){
				char* name2 = sym.f[f_ind].input[j].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:variable %s already declared\n", sym.f[f_ind].input[j].v_name->line_no,name);
					semantic_err=1;
				}
			}
			for(j =0;j<sym.f[f_ind].output_num;j++){
				char* name2 = sym.f[f_ind].output[j].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:variable %s already declared\n", sym.f[f_ind].output[j].v_name->line_no,name);
					semantic_err=1;
				}
			}
		}
		for(i =0;i<sym.f[f_ind].output_num;i++){
			char* name = sym.f[f_ind].output[i].v_name->value;
			int j = i+1;
			for(j =i+1;j<sym.f[f_ind].output_num;j++){
				char* name2 = sym.f[f_ind].output[j].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:variable %s already declared\n", sym.f[f_ind].output[j].v_name->line_no,name);
					semantic_err=1;
				}
			}
		}	
	}
	//global variables
	for(i =0;i<sym.global_num;i++){
		char* name = sym.g[i].v_name->value;
		int j = i+1;
		for(j =i+1;j<sym.global_num;j++){
			char* name2 = sym.g[j].v_name->value;
			if(strcmp(name,name2)==0){
				printf("line:%d:Variable %s being a global variable, cannot be declared more than once.\n", sym.g[j].v_name->line_no,name);
				semantic_err=1;
			}
		}
	}
	//record definations and field variables
	for(i =0;i<sym.recd_num;i++){
		char* name = sym.r[i].rec_name->value;
		int j = i+1;
		for(j =i+1;j<sym.recd_num;j++){
			char* name2 = sym.r[j].rec_name->value;
			if(strcmp(name,name2)==0){
				printf("line:%d:record type %s already defined\n", sym.r[j].rec_name->line_no,name);
				semantic_err=1;
			}
		}
		int k;
		for(k =0;k<sym.r[i].var_num;k++){
			name = sym.r[i].var[k].v_name->value;
			int l;
			for(l = k+1;l<sym.r[i].var_num;l++){
				char* name2 = sym.r[i].var[l].v_name->value;
				if(strcmp(name,name2)==0){
					printf("line:%d:field variable %s already declared\n", sym.r[i].var[l].v_name->line_no,name);
					semantic_err=1;
				}
			}
		}
	}
}
//checks variable is declared or weather in the scope for a function
void isDeclaredVariable(ast_node* ptr,int fun_index){
	int line = ptr->line_no;
	if(line==-1)
		line = ptr->children[0]->line_no;
	if(ptr->id == 48||ptr->id == 128||ptr->id == 144){
		int result = getType(ptr,fun_index);
		if(result == -1)
			if(ptr->id==48){
				printf("Line:%d:Variable %s not declared\n",line,ptr->value);
				semantic_err=1;
			}
			else{
				result = getType(ptr->children[0],fun_index);
				if(result == -1){
					printf("Line:%d:Variable %s not declared\n",line,ptr->children[0]->value);
					semantic_err=1;
				}
				else{
					printf("Line:%d:record %s of type %s do not have variable %s\n",line,ptr->children[0]->value,typeToString(getType(ptr->children[0],fun_index)),ptr->children[1]->value);
					semantic_err=1;
				}
			}
	/*	else
			printf("Line:%d:Symantically correct!!!!!!!\n",line);*/
	}
	int i =0;
	for(i = 0;i<ptr->child_size;i++){
		isDeclaredVariable(ptr->children[i],fun_index);
	}
}

//checks weather variable is declared
void checkVariableDeclared(){
	isDeclaredVariable(sym.m.mainNode,-1);
	int i =0;
	for(i =0;i< funct_index;i++)
		isDeclaredVariable(sym.f[i].funNode,i);		
}

//checks single declaration of global variable
void checkUniqueGlobalVariables(){
	int i =0;
	for(i =0;i<sym.global_num;i++){
		char* name1 = sym.g[i].v_name->value;
		int j =0;
		for(j =0;j<sym.m.var_num;j++){
			char* name2 = sym.m.var[j].v_name->value;
			if(strcmp(name1,name2)==0){
				printf("line:%d:Variable %s being a global variable, cannot be declared more than once.\n",sym.m.var[j].v_name->line_no,name1);
				semantic_err=1;
			}
		}
		int f_ind = 0;
		for(f_ind =0;f_ind<funct_index;f_ind++){
			int j =0;
			for(j =0;j<sym.f[f_ind].var_num;j++){
				char* name2 = sym.f[f_ind].var[j].v_name->value;
				if(strcmp(name1,name2)==0){
					printf("line:%d:Variable %s being a global variable, cannot be declared more than once.\n",sym.f[f_ind].var[j].v_name->line_no,name1);
					semantic_err=1;
				}
			}
			for(j =0;j<sym.f[f_ind].input_num;j++){
				char* name2 = sym.f[f_ind].input[j].v_name->value;
				if(strcmp(name1,name2)==0){
					printf("line:%d:Variable %s being a global variable, cannot be declared more than once.\n",sym.f[f_ind].input[j].v_name->line_no,name1);
					semantic_err=1;
				}
			}
			for(j =0;j<sym.f[f_ind].output_num;j++){
				char* name2 = sym.f[f_ind].output[j].v_name->value;
				if(strcmp(name1,name2)==0){
					printf("line:%d:Variable %s being a global variable, cannot be declared more than once.\n",sym.f[f_ind].output[j].v_name->line_no,name1);
					semantic_err=1;
				}
			}
		}
	}
}

//check input parametes validity for function call satement
void checkInputParCompatability(ast_node* ptr,int f_ind,int called_func_id){
	int i =0;
	while(ptr->id == 133){
		int type = getType(ptr->children[0],f_ind);
		if(i>= sym.f[called_func_id].input_num){
			printf("line:%d:The number of input parametrs at function call %s is incorrect.\n",ptr->children[0]->line_no,sym.f[called_func_id].fname);
			semantic_err=1;
			return;
		}else{
			int type2 = getType(sym.f[called_func_id].input[i].type,called_func_id);
			if(type != type2){
				printf("line:%d: The type %s of variable %s given does not match with the type %s of the formal input parameter %s\n",getLine_start(ptr),typeToString(type),ptr->children[0]->value,typeToString(type2),sym.f[called_func_id].input[i].v_name->value);
				semantic_err=1;
			}
		}
		i++;
		ptr = ptr->children[1];
	}
	int type = getType(ptr,f_ind);
	if(i >= sym.f[called_func_id].input_num){
		printf("line:%d:The number of input parametrs at function call %s is incorrect.\n",ptr->line_no,sym.f[called_func_id].fname);
		semantic_err=1;
		return;
	}else{
		int type2 = getType(sym.f[called_func_id].input[i].type,f_ind);
		if(type != type2){
			printf("line:%d:The type %s of variable %s given does not match with the type %s of the formal input parameter %s\n",getLine_start(ptr),typeToString(type),ptr->value,typeToString(type2),sym.f[called_func_id].input[i].v_name->value);
			semantic_err=1;
		}
	}
	i++;
	if(i!=sym.f[called_func_id].input_num){
		printf("line:%d:The number of input parametrs at function call %s is incorrect.\n",ptr->line_no,sym.f[called_func_id].fname);
		semantic_err=1;
	}
}
//check output parametes validity for function call satement
void checkOutputParCompatability(ast_node* ptr,int f_ind,int called_func_id){
	int i =0;
	while(ptr->id == 133){
		int type = getType(ptr->children[0],f_ind);
		if(i>= sym.f[called_func_id].output_num){
			printf("line:%d:The number of output parametrs at function call %s is incorrect.\n",ptr->children[0]->line_no,sym.f[called_func_id].fname);
			semantic_err=1;
			return;
		}else{
			int type2 = getType(sym.f[called_func_id].output[i].type,called_func_id);
			if(type != type2){
				printf("line:%d:The type %s of variable %s returned does not match with the type %s of the formal output parameter %s\n",getLine_start(ptr),typeToString(type),ptr->children[0]->value,typeToString(type2),sym.f[called_func_id].output[i].v_name->value);
				semantic_err=1;
			}
		}
		i++;
		ptr = ptr->children[1];
	}
	int type = getType(ptr,f_ind);
	if(i>= sym.f[called_func_id].output_num){
		printf("line:%d:The number of output parametrs at function call %s is incorrect.\n",ptr->line_no,sym.f[called_func_id].fname);
		semantic_err=1;
		return;
	}else{
		int type2 = getType(sym.f[called_func_id].output[i].type,f_ind);
		if(type != type2){
			printf("line:%d:The type %s of variable %s returned does not match with the type %s of the formal output parameter %s\n",getLine_start(ptr),typeToString(type),ptr->value,typeToString(type2),sym.f[called_func_id].output[i].v_name->value);
			semantic_err=1;
		}
	}
	i++;
	if(i!=sym.f[called_func_id].output_num)
		printf("line:%d:The number of output parametrs at function call %s is incorrect.\n",ptr->line_no,sym.f[called_func_id].fname);
		semantic_err=1;
}
//verifies semantic correctness of function call statement in a given function
void checkCallStmt(ast_node* ptr,int f_ind){
	int l = 0;
	for(l = 0;l<ptr->child_size;l++){
		if(ptr->children[l]->id == 51){
			int called_func_id,i;
			for(i = 0;i<funct_index;i++){
				if(strcmp(ptr->children[l]->value,sym.f[i].fname)==0){
					called_func_id = i;
					if(ptr->children[l]->line_no<sym.f[i].funNode->children[0]->line_no){
						printf("line:%d:function %s undefined\n",ptr->children[l]->line_no,ptr->children[l]->value);
						semantic_err=1;
						return;
					}
					break;
				}
			}
			if(i == funct_index){
				printf("line:%d:function %s undefined\n",ptr->children[l]->line_no,ptr->children[l]->value);
				semantic_err=1;
				return;
			}
			if(f_ind == called_func_id){
				printf("line:%d:cannot call a function recursively\n",ptr->children[l]->line_no);
				semantic_err=1;
				return;
			}
			if(ptr->id!=127){
				if(sym.f[called_func_id].input_num!=0){
					printf("line:%d:The number of input parametrs at function call %s is incorrect.\n",ptr->children[l]->line_no,ptr->children[l]->value);
					semantic_err=1;
				}
				if(sym.f[called_func_id].output_num!=0){
					printf("line:%d:The number of output parametrs at function call %s is incorrect.\n",ptr->children[l]->line_no,ptr->children[l]->value);
					semantic_err=1;
				}
				return;
			}else{
				if((l-1)>=0){
					checkOutputParCompatability(ptr->children[l-1],f_ind,called_func_id);
				}else{
					if(sym.f[called_func_id].input_num!=0){
						printf("line:%d:The number of input parametrs at function call %s is incorrect.\n",ptr->children[l]->line_no,ptr->children[l]->value);
						semantic_err=1;
					}
				}
				if((l+1)<ptr->child_size){
					checkInputParCompatability(ptr->children[l+1],f_ind,called_func_id);
				}else{
					if(sym.f[called_func_id].output_num!=0){
						printf("line:%d:The number of output parametrs at function call %s is incorrect.\n",ptr->children[l]->line_no,ptr->children[l]->value);
						semantic_err=1;
					}
				}
			}		
		}else{
			checkCallStmt(ptr->children[l],f_ind);	
		}			
	}
}

//verifies semantic correctness of function call statement
void checkCallCompatibility(){
	int f_ind = 0;
	if(sym.m.mainNode->child_size>1)
		checkCallStmt(sym.m.mainNode->children[1],-1);
	for(f_ind =0;f_ind<funct_index;f_ind++){
		int i;
		for(i =1;i<sym.f[f_ind].funNode->child_size;i++){
			checkCallStmt(sym.f[f_ind].funNode->children[i],f_ind);
		}
	}
}

//checks function overloading
void checkFunctionOverloding(){
	int i;
	for(i =0;i<funct_index;i++){
		char* name1 = sym.f[i].fname;
		if(strcmp(name1,"_main")==0){
			printf("line:%d:only one main function is allowed\n",getLine_start(sym.f[i].funNode));
			semantic_err=1;
		}
		int j =i+1;
		for(j =i+1; j<funct_index;j++){
			if(strcmp(name1,sym.f[j].fname)==0){
				printf("line:%d:function %s overloading is not allowed\n",getLine_start(sym.f[i].funNode),name1);
				semantic_err=1;
			}
		}
	}
}
//checks if the variable is changing in the scope
int isExist(ast_node* ptr,ast_node* scope){
	if(scope->id == ptr->id){
		if(strcmp(scope->value,ptr->value)==0){
			return 1;
		}
		else{
			return 0;
		}
	}else{
		int i;
		int res = 0;
		for(i = 0;i<scope->child_size;i++){
			res = isExist(ptr,scope->children[i]);
			if(res>0){
				return res;
			}
		}
		return res;
	}
}
//checks weather variable is changing in the scope
int isAssigned(ast_node* ptr,ast_node* scope){
	if(scope->id == 123){
		return isExist(ptr,scope->children[0]);
	}else if(scope->id == 127){
		if(scope->children[0]->id != 51)
			return isExist(ptr,scope->children[0]);
		else return 0;
	}else if(scope->id == 126){
		if(scope->children[0]->id == 29)
			return isExist(ptr,scope->children[1]);
		else return 0;	
	}else{
		int i;
		int res = 0;
		for(i = 0;i<scope->child_size;i++){
			res = isAssigned(ptr,scope->children[i]);
			if(res>0){
				return res;
			}
		}
		return res;
	}
}
//checks weather variables in return assigned
void isReturnAssigned(ast_node* ptr,int f_ind){
	while(ptr->id == 133){
		if(isAssigned(ptr->children[0],sym.f[f_ind].funNode)==0){
			printf("%s value not assigned in function %s,so cannot return\n",ptr->children[0]->value,sym.f[f_ind].fname);
			semantic_err=1;
		}
		ptr = ptr->children[1];
	}
	if(isAssigned(ptr,sym.f[f_ind].funNode)==0){
		printf("%s value not assigned in function %s,so cannot return\n",ptr->value,sym.f[f_ind].fname);
		semantic_err=1;
	}
}

//finds return stmt in a function checks semantic correctness of return statement
void getReturnStmt(ast_node* ptr,int f_ind){
	if(ptr->id == 115){
		checkOutputParCompatability(ptr->children[1],f_ind,f_ind);
		isReturnAssigned(ptr->children[1],f_ind);
		
	}
	else if(ptr->id == 31){
		if(sym.f[f_ind].output_num!=0){
			printf("line:%d:parameters are expected in return statement\n",ptr->line_no);
			semantic_err=1;
		}
	}else{
		int i;
		for(i = 0;i<ptr->child_size;i++){
			getReturnStmt(ptr->children[i],f_ind);
		}
	}	
}
//checks semantic correctness of return statement
void checkReturnStmnt(){
	int i =0;
	for(i =0;i<funct_index;i++){
		getReturnStmt(sym.f[i].funNode,i);
	}
}
//given node of iterative stmt it verifies updating of loop variables
int isWhileUpdating(ast_node* cond,ast_node* ptr){
	if(cond->id == 48){
		int i =0;
		for(i =1;i<(ptr->child_size);i++){
			if(isAssigned(cond,ptr->children[i])==1){
				return 1;
			}
		}
		return 0;
	}else{
		int i =0;
		for(i =0;i<cond->child_size;i++){
			if(isWhileUpdating(cond->children[i],ptr)==1){
				return 1;
			}
		}
		return 0;
	}
}
//get while statement in a function and checks its correctness
void getIterativeStmt(ast_node* ptr,int f_ind){
	if(ptr->id == 124){
		int i =0;
		ast_node* cond = ptr->children[0];
		if(isWhileUpdating(cond,ptr)==0){
			printf("line:%d-%d:None of the variables participating in the iterations of the while loop gets updated.\n",getLine_start(ptr),getLine_end(ptr));
			semantic_err=1;
		}
	}else{
		int i;
		for(i = 0;i<ptr->child_size;i++){
			getIterativeStmt(ptr->children[i],f_ind);
		}
	}	
}
//checks semantic correctness of while statement
void checkWhilestmnt(){
	getIterativeStmt(sym.m.mainNode,-1);
	int i =0;
	for(i =0;i<funct_index;i++){
		getIterativeStmt(sym.f[i].funNode,i);
	}
}
//checks semantics of boolean expression
int isBooleanExp(ast_node* ptr,int f_ind){
	if(ptr->children[0]->id == 134){
		//logical operation
		int res1 = isBooleanExp(ptr->children[0],f_ind);
		int res2 = isBooleanExp(ptr->children[2],f_ind);
		if(res1==1 && res2==1){
			return 1;
		}else{
			return 0;
		}
	}else if(ptr->children[0]->id == 41){
		//not case
		return isBooleanExp(ptr->children[1],f_ind);
	}else{
		//relational operation
		int type1 = getType(ptr->children[0],f_ind);
		int type2 = getType(ptr->children[2],f_ind);
		if(type1 == type2){
			if(type1>10){
				return 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}
}
//finds boolean statement in a function and verifies
void getBooleanStmt(ast_node* ptr,int f_ind){
	if(ptr->id == 134){
		if(isBooleanExp(ptr,f_ind)==0){
			printf("line:%d:do not satisfy semantics of boolean expression\n",getLine_start(ptr));
			semantic_err=1;
		}
	}else{
		int i;
		for(i = 0;i<ptr->child_size;i++){
			getBooleanStmt(ptr->children[i],f_ind);
		}
	}	
}
//checks semantics of boolean expression
void checkBooleanStmt(){
	getBooleanStmt(sym.m.mainNode,-1);
	int i =0;
	for(i =0;i<funct_index;i++){
		getBooleanStmt(sym.f[i].funNode,i);
	}
}
//checks semantics of assignment statement
void checkAssignCompatibility(){
	assignTester(sym.m.mainNode,-1);
	int i =0;
	for(i =0;i< funct_index;i++)
		assignTester(sym.f[i].funNode,i);	
}

//checks all semantics
void symanticAnalysis(ast_node* ptr){
	
	checkMultipleDeclaration();
	checkVariableDeclared();
	checkUniqueGlobalVariables();
	checkAssignCompatibility();
	checkCallCompatibility();
	checkFunctionOverloding();
	checkReturnStmnt();
	checkWhilestmnt();
	checkBooleanStmt();
}


