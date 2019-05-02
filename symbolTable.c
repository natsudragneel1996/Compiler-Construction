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
#include "typeExtractor.h"
//enter input parameters into symbol table
void loadInputPar(ast_node* ptr){
	int i = 0;
	while(1){
		sym.f[funct_index].input[i].type = ptr->children[0];
		sym.f[funct_index].input[i].v_name = ptr->children[1];
		i++;
		if(ptr->child_size > 2){
			ptr = ptr->children[2];
		}else{
			break;
		}	
	}
	sym.f[funct_index].input_num = i;
}
//enter output parameters into symbol table
void loadOutputPar(ast_node* ptr){
	int i = 0;
	while(1){
		sym.f[funct_index].output[i].type = ptr->children[0];
		sym.f[funct_index].output[i].v_name = ptr->children[1];
		i++;
		if(ptr->child_size > 2){
			ptr = ptr->children[2];
		}else{
			break;
		}	
	}
	sym.f[funct_index].output_num = i;
}
//enter record definitions into symbol table
void loadRecordData(ast_node* ptr){
	sym.r[sym.recd_num].rec_name = ptr->children[0];
	ptr = ptr->children[1];
	int i =0;
	int flag =0;
	while(1){
		flag = 0;
		for(i = 0;i < ptr->child_size; i++){
			if(ptr->children[i]->id== 118){
				sym.r[sym.recd_num].var[sym.r[sym.recd_num].var_num].type = ptr->children[i]->children[0];
				sym.r[sym.recd_num].var[sym.r[sym.recd_num].var_num].v_name = ptr->children[i]->children[1];
				sym.r[sym.recd_num].var_num = sym.r[sym.recd_num].var_num+1;
			}else{

				break;
			}
		}
		if(i==ptr->child_size){
			break;
		}else{
			ptr = ptr->children[i];
		}
	}
}
//get type definition non terminal
void loadTypedefs(ast_node* ptr){
	while(1){
		if(ptr->id == 112){
			loadRecordData(ptr->children[0]);
			sym.recd_num = sym.recd_num+1;
			ptr = ptr->children[1];
		}else if(ptr->id == 116){
			loadRecordData(ptr);
			sym.recd_num = sym.recd_num+1;
			break;
		}
	}
}
//loads declarations into symbol table
void loadDeclarations(ast_node* ptr){
	int i = 0;
	while(1){
		if(ptr->id == 113){
			ast_node* ptr2 = ptr->children[0];
			if(ptr2->child_size == 2){
				sym.f[funct_index].var[i].type = ptr2->children[0];
				sym.f[funct_index].var[i].v_name = ptr2->children[1];
				i++;
			}
			else if(ptr2->child_size == 3){
				sym.g[sym.global_num].type = ptr2->children[0];
				sym.g[sym.global_num].v_name = ptr2->children[1];
				sym.global_num = sym.global_num+1;
			}
			ptr = ptr->children[1];
		}
		if(ptr->id == 120){
			if(ptr->child_size == 2){
				sym.f[funct_index].var[i].type = ptr->children[0];
				sym.f[funct_index].var[i].v_name = ptr->children[1];
				i++;
			}
			else if(ptr->child_size == 3){
				sym.g[sym.global_num].type = ptr->children[0];
				sym.g[sym.global_num].v_name = ptr->children[1];
				sym.global_num = sym.global_num+1;
			}
			break;
		}	
	}
	sym.f[funct_index].var_num = i;
}
//load declarations for main functions
void loadMainDeclarations(ast_node* ptr){
	int i = 0;
	while(1){
		if(ptr->id == 113){
			ast_node* ptr2 = ptr->children[0];
			if(ptr2->child_size == 2){
				sym.m.var[i].type = ptr2->children[0];
				sym.m.var[i].v_name = ptr2->children[1];
				i++;
			}
			else if(ptr2->child_size == 3){
				sym.g[sym.global_num].type = ptr2->children[0];
				sym.g[sym.global_num].v_name = ptr2->children[1];
				sym.global_num = sym.global_num+1;
			}
			ptr = ptr->children[1];
		}
		if(ptr->id == 120){
			if(ptr->child_size == 2){
				sym.m.var[i].type = ptr->children[0];
				sym.m.var[i].v_name = ptr->children[1];
				i++;
			}
			else if(ptr->child_size == 3){
				sym.g[sym.global_num].type = ptr->children[0];
				sym.g[sym.global_num].v_name = ptr->children[1];
				sym.global_num = sym.global_num+1;
			}
			break;
		}	
	}
	sym.m.var_num = i;
	
}

//enters data and declaration in function
void populatefunctTable(ast_node* ptr){
	sym.f[funct_index].fname = ptr->children[0]->value;
	sym.f[funct_index].funNode = ptr;
	int i =1;
	ast_node* ptr2;
	for(i=1;i<ptr->child_size;i++){
		ptr2 = ptr->children[i];
		if(ptr2->parentId == 105)
			loadInputPar(ptr2);
		else if(ptr2->parentId == 106)
			loadOutputPar(ptr2);
		else break;
	}
	if(i==ptr->child_size){
		return;
	}
	if(ptr2->id != 103){
		return;
	}
	i = 0;
	ast_node* ptr3;
	for(i=0;i<ptr2->child_size;i++){
		ptr3 = ptr2->children[i];
		if(ptr3->id == 112||ptr3->id == 116)
			loadTypedefs(ptr3);
		else if(ptr3->id == 113||ptr3->id == 120)
			loadDeclarations(ptr3);
		else break;
	}	
}
//enters declaration in main function
void populatemainTable(ast_node* ptr){
	ast_node* ptr2 = ptr->children[1];
	sym.m.mainNode = ptr;
	if(ptr2->id != 103){
		return;
	}
	ast_node* ptr3;
	int i;
	for(i=0;i<ptr2->child_size;i++){
		ptr3 = ptr2->children[i];
		if(ptr3->id == 112||ptr3->id == 116)
			loadTypedefs(ptr3);
		else if(ptr3->id == 113||ptr3->id == 120)
			loadMainDeclarations(ptr3);
		else break;
	}	
}
//enters data in symbol table
void populateSymTable(ast_node* ptr){
	int i =0;
	if(ptr->id == 100){
		for(i = 0;i < ptr->child_size; i++){
			populateSymTable(ptr->children[i]);
		}
	}
	if(ptr->id == 101){
		for(i = 0;i < ptr->child_size; i++){
			populateSymTable(ptr->children[i]);
		}		
	}
	if(ptr->id == 104){
		populatefunctTable(ptr);
		funct_index = funct_index+1;
	}
	if(ptr->id == 102){
		populatemainTable(ptr);
	}
} 

//get no of functions other than main
int getNoOfFunctions(ast_node* ptr){
	if(ptr->id == 100){
		if(ptr->child_size > 1)
			return (getNoOfFunctions(ptr->children[0]));
	}
	if(ptr->id == 101){
		return (1+getNoOfFunctions(ptr->children[1]));
	}
	if(ptr->id == 104){
		return 1;
	}
	return 0;
}
//prints symbol table
void printSymTable(){
	printf("Lexemes        ");
	printf("Type                          ");
	printf("Scope          ");
	printf("Offset         ");
	printf("\n");
	int i =0;
	for(i =0;i<sym.global_num;i++){
		int len = printf("%s",sym.g[i].v_name->value);
		int j ;
		for(j = len;j<15;j++){
			printf(" ");
		}
		len = printf("%s",typeToString(getType(sym.g[i].type,-1)));
		for(j = len;j<30;j++){
			printf(" ");
		}
		len = printf("global");
		for(j = len;j<15;j++){
			printf(" ");
		}
		len = printf("-");
		for(j = len;j<15;j++){
			printf(" ");
		}
		printf("\n");
	}
	for(i =0;i<sym.m.var_num;i++){
		int len = printf("%s",sym.m.var[i].v_name->value);
		int j ;
		for(j = len;j<15;j++){
			printf(" ");
		}
		len = printf("%s",typeToString(getType(sym.m.var[i].type,-1)));
		for(j = len;j<30;j++){
			printf(" ");
		}
		len = printf("_main");
		for(j = len;j<15;j++){
			printf(" ");
		}
		len = printf("%d",sym.m.var[i].offset);
		for(j = len;j<15;j++){
			printf(" ");
		}
		printf("\n");
	}
	int f_ind =0;
	for(f_ind =0;f_ind<funct_index;f_ind++){
		for(i =0;i<sym.f[f_ind].input_num;i++){
			int len = printf("%s",sym.f[f_ind].input[i].v_name->value);
			int j ;
			for(j = len;j<15;j++){
				printf(" ");
			}
			len = printf("%s",typeToString(getType(sym.f[f_ind].input[i].type,f_ind)));
			for(j = len;j<30;j++){
				printf(" ");
			}
			len = printf("%s",sym.f[f_ind].fname);
			for(j = len;j<15;j++){
				printf(" ");
			}
			len = printf("%d",sym.f[f_ind].input[i].offset);
			for(j = len;j<15;j++){
				printf(" ");
			}
			printf("\n");
		}
		for(i =0;i<sym.f[f_ind].output_num;i++){
			int len = printf("%s",sym.f[f_ind].output[i].v_name->value);
			int j ;
			for(j = len;j<15;j++){
				printf(" ");
			}
			len = printf("%s",typeToString(getType(sym.f[f_ind].output[i].type,f_ind)));
			for(j = len;j<30;j++){
				printf(" ");
			}
			len = printf("%s",sym.f[f_ind].fname);
			for(j = len;j<15;j++){
				printf(" ");
			}
			len = printf("%d",sym.f[f_ind].output[i].offset);
			for(j = len;j<15;j++){
				printf(" ");
			}
			printf("\n");
		}
		for(i =0;i<sym.f[f_ind].var_num;i++){
			int len = printf("%s",sym.f[f_ind].var[i].v_name->value);
			int j ;
			for(j = len;j<15;j++){
				printf(" ");
			}
			len = printf("%s",typeToString(getType(sym.f[f_ind].var[i].type,f_ind)));
			for(j = len;j<30;j++){
				printf(" ");
			}
			len = printf("%s",sym.f[f_ind].fname);
			for(j = len;j<15;j++){
				printf(" ");
			}
			len = printf("%d",sym.f[f_ind].var[i].offset);
			for(j = len;j<15;j++){
				printf(" ");
			}
			printf("\n");
		}	
	}
}
//calculate offset values in a function
void generateFunoffset(int fun){
	int foffset=0;
	int i,j,type;
	for(i=0;i<sym.f[fun].input_num;i++){
		type=getType(sym.f[fun].input[i].type,fun);
		if(type==11){
			sym.f[fun].input[i].offset=foffset;
			sym.f[fun].input[i].width = 2;
			foffset=foffset+2;
		}else if(type==12){
			sym.f[fun].input[i].offset=foffset;
			sym.f[fun].input[i].width = 4;
			foffset=foffset+4;
		}else{
			sym.f[fun].input[i].offset=foffset;
			sym.f[fun].input[i].width = 0;
			for(j=0;j<sym.r[type].var_num;j++){
				if(getType(sym.r[type].var[j].type,-1)==11){
					sym.f[fun].input[i].width = sym.f[fun].input[i].width + 2;
					foffset=foffset+2;
				}else{
					sym.f[fun].input[i].width = sym.f[fun].input[i].width + 4;
					foffset=foffset+4;
				}
			}
		}
	}
	for(i=0;i<sym.f[fun].output_num;i++){
		type=getType(sym.f[fun].output[i].type,fun);
		if(type==11){
			sym.f[fun].output[i].offset=foffset;
			sym.f[fun].output[i].width = 2;
			foffset=foffset+2;
		}
		else if(type==12){
			sym.f[fun].output[i].offset=foffset;
			sym.f[fun].output[i].width = 4;
			foffset=foffset+4;
		}else{
			sym.f[fun].output[i].offset=foffset;
			sym.f[fun].output[i].width = 0;
			for(j=0;j<sym.r[type].var_num;j++){
				if(getType(sym.r[type].var[j].type,-1)==11){
					sym.f[fun].output[i].width = sym.f[fun].output[i].width + 2;
					foffset=foffset+2;
				}else{
					sym.f[fun].output[i].width = sym.f[fun].output[i].width + 4;
					foffset=foffset+4;
				}
			}
		}

	}

	for(i=0;i<sym.f[fun].var_num;i++){
		type=getType(sym.f[fun].var[i].type,fun);
		if(type==11){
			sym.f[fun].var[i].offset=foffset;
			sym.f[fun].var[i].width = 2;
			foffset=foffset+2;
		}else if(type==12){
			sym.f[fun].var[i].offset=foffset;
			sym.f[fun].var[i].width = 4;
			foffset=foffset+4;
		}else{
			sym.f[fun].var[i].offset=foffset;
			sym.f[fun].var[i].width = 0;
			for(j=0;j<sym.r[type].var_num;j++){
				if(getType(sym.r[type].var[j].type,-1)==11){
					sym.f[fun].var[i].width = sym.f[fun].var[i].width + 2;
					foffset=foffset+2;
				}else{
					sym.f[fun].var[i].width = sym.f[fun].var[i].width + 4;
					foffset=foffset+4;
				}
			}
		}
	}
}



//calculates offset for main function variables
void generateOffset(){
	int i,j,type,moffset=0;
	for(i=0;i<sym.global_num;i++){
		sym.g[i].offset=-1;
		int width = 0;
		int t = getType(sym.g[i].type,-1);
		if(t == 11){
			sym.g[i].width = 2;				
		}else if(t == 12){
			sym.g[i].width = 4;				
		}
		else{
			int k;
			for(k =0;k<sym.r[t].var_num;k++){
				if(getType(sym.r[t].var[k].type,-1)==11)
					width = width +2;
				else
					width = width+4;
			}
			sym.g[i].width = width;
		}
	}
	for(i=0;i<sym.m.var_num;i++){
		type =  getType(sym.m.var[i].type,-1);
		if (type==11){
			sym.m.var[i].offset=moffset;
			sym.m.var[i].width = 2;
			moffset=moffset+2;
		}else if(type==12){
			sym.m.var[i].offset=moffset;
			sym.m.var[i].width = 4;
			moffset=moffset+4;
		}else{
			sym.m.var[i].offset=moffset;
			for(j=0;j<sym.r[type].var_num;j++){
				if(getType(sym.r[type].var[j].type,-1)==11){
					sym.m.var[i].width = sym.m.var[i].width + 2;
					moffset=moffset+2;
				}else{
					sym.m.var[i].width = sym.m.var[i].width + 4;
					moffset=moffset+4;
				}
			}
		}
	}
	for(i=0;i<funct_index;i++){
		generateFunoffset(i);
	}
}

