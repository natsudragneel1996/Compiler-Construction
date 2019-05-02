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
#include "codeGeneratorDef.h"
#include "codeGenerator.h"

//prints .data section to file
void printData(FILE*fp){
	regNo =0;
	itrNo =0;
	jumpInd =0;
	elseCount =0;
	int i =0;
	fprintf(fp,"section .data\n");
	for(i = 0;i<25;i++){
		fprintf(fp,"r_%d dd 0\n",i);
	}
	fprintf(fp,"input : db %c%cd%c,0\n",34,37,34);
	fprintf(fp,"output: db %c%cd%c,10,0\n",34,37,34);
	fprintf(fp,"section .bss\n");
}

//prints asm code for logical AND for given addresses
void printLogicalAnd(int r1,int r2,FILE *fp){
	fprintf(fp,"mov eax,[r_%d]\n",r1);
	fprintf(fp,"mov ebx,[r_%d]\n",r2);
	fprintf(fp,"and eax,ebx\n");
	fprintf(fp,"mov [r_%d],eax\n",r1);
}

//prints asm code for logical OR for given addresses
void printLogicalOr(int r1,int r2,FILE *fp){
	fprintf(fp,"mov eax,[r_%d]\n",r1);
	fprintf(fp,"mov ebx,[r_%d]\n",r2);
	fprintf(fp,"or eax,ebx\n");
	fprintf(fp,"mov [r_%d],eax\n",r1);
}

//prints asm code for moving number into given addresses
void printReadNum(int r,char* s,FILE*fp){
	fprintf(fp,"mov eax,%s\n",s);
	fprintf(fp,"mov [r_%d],eax\n",r);
}

//prints asm code moving value in one given variable to other address 
void printReadVar(int r,char* s,int o,FILE*fp){
	fprintf(fp,"mov ecx,%s\n",s);
	fprintf(fp,"add ecx,%d\n",o);
	fprintf(fp,"mov eax,[ecx]\n");
	fprintf(fp,"mov [r_%d],eax\n",r);
}

//prints asm code moving value in one addresses to other given variable
void printWriteVar(char* var,char*s,int o,FILE*fp){
	fprintf(fp,"mov ebx,%s\n",var);
	fprintf(fp,"add ebx,%d\n",o);
	fprintf(fp,"mov eax,[%s]\n",s);
	fprintf(fp,"mov [ebx],eax\n");
}

//prints asm code for addition of variables in two addresses, r1 = r1 +r2
void printAdder(char* op1,char* op2,FILE*fp){
	fprintf(fp,"mov eax,[%s]\n",op1);
	fprintf(fp,"mov ebx,[%s]\n",op2);
	fprintf(fp,"add eax,ebx\n");	
	fprintf(fp,"mov [%s],eax\n",op1);
}

//prints asm code for subtraction of variables in two addresses, r1 = r1 -r2
void printSub(char* op1,char* op2,FILE*fp){
	fprintf(fp,"mov eax,[%s]\n",op1);
	fprintf(fp,"mov ebx,[%s]\n",op2);
	fprintf(fp,"sub eax,ebx\n");	
	fprintf(fp,"mov [%s],eax\n",op1);
}

//prints asm code for multiplication of variables in two addresses, r1 = r1 *r2
void printMul(char* op1,char* op2,FILE*fp){
	fprintf(fp,"mov eax,[%s]\n",op2);
	fprintf(fp,"mov ebx,[%s]\n",op1);
	fprintf(fp,"mov edx,0\n");
	fprintf(fp,"imul ebx\n");
	fprintf(fp,"mov [%s],eax\n",op1);
}

//prints asm code for division of variables in two addresses, r1 = r1 /r2
void printDiv(char* op1,char* op2,FILE*fp){
	fprintf(fp,"mov eax,[%s]\n",op1);
	fprintf(fp,"mov ebx,[%s]\n",op2);
	fprintf(fp,"mov edx,0\n");
	fprintf(fp,"idiv ebx\n");
	fprintf(fp,"mov [%s],eax\n",op1);
}

//prints asm code for Io read
void printIORead(char* s,int offset,FILE*fp){
	fprintf(fp,"mov rsi,%s\n",s);
	fprintf(fp,"add rsi,%d\n",offset);
	fprintf(fp,"mov rdi,input\n");
	fprintf(fp,"mov rax,0\n");
	fprintf(fp,"call scanf\n");
}

//prints asm code for Io write
void printIOWrite(char* s,FILE*fp){
	fprintf(fp,"mov rsi,[%s]\n",s);
	fprintf(fp,"mov rdi,output\n");
	fprintf(fp,"mov rax,0\n");
	fprintf(fp,"call printf\n");
}

//prints asm code for logical not
void printLogicalNot(int r,FILE*fp){
	fprintf(fp,"mov eax,[r_%d]\n",r);
	fprintf(fp,"not eax\n");
	fprintf(fp,"mov [r_%d],eax\n",r);
}

//prints asm code for comparing values at two addresses
void printCompare(char* res1,char* res2,FILE*fp){
	fprintf(fp,"mov eax,[%s]\n",res1);
	fprintf(fp,"mov ebx,[%s]\n",res2);
	fprintf(fp,"cmp eax,ebx\n");
}

//prints asm code for comparing values at a address and a number
void printCompareToNum(int r,int n,FILE*fp){
	fprintf(fp,"mov eax,[r_%d]\n",r);
	fprintf(fp,"mov ebx,%d\n",n);
	fprintf(fp,"cmp eax,ebx\n");
}

//returns address assignned to the output for the operation
char* getRegister(ast_node* ptr,int offset,FILE*fp){
	if(ptr->id == 130){
		//arithmatic expression
		char* op1 = getRegister(ptr->children[0],offset,fp);
		char* op2 = getRegister(ptr->children[1],offset,fp);
		if(ptr->children[1]->children[0]->id == 32){
			//addition
			printAdder(op1,op2,fp);
		}else{
			//substraction
			printSub(op1,op2,fp);
		}
		return op1;
	}
	if(ptr->id == 138){
		//term
		char* op1 = getRegister(ptr->children[0],offset,fp);
		char* op2 = getRegister(ptr->children[1],offset,fp);
		if(ptr->children[1]->children[0]->id == 34){
			//multiplication
			printMul(op1,op2,fp);
		}else{
			//divide
			printDiv(op1,op2,fp);
		}
		return op1;
	}
	if(ptr->id == 139){
		//expPrime
		if(ptr->child_size == 2){
			char* term = getRegister(ptr->children[1],offset,fp);
			return term;
		}
		char* op1 = getRegister(ptr->children[1],offset,fp);
		char* op2 = getRegister(ptr->children[2],offset,fp);
		if(ptr->children[2]->children[0]->id == 32){
			//addition
			printAdder(op1,op2,fp);
		}else{
			//substraction
			printSub(op1,op2,fp);
		}
		return op1;
	}
	if(ptr->id == 142){
		//termPrime
		if(ptr->child_size == 2){
			char* term = getRegister(ptr->children[1],offset,fp);
			return term;
		}
		char* op1 = getRegister(ptr->children[1],offset,fp);
		char* op2 = getRegister(ptr->children[2],offset,fp);
		if(ptr->children[2]->children[0]->id == 32){
			//multiply 
			printMul(op1,op2,fp);
		}else{
			//divide
			printDiv(op1,op2,fp);
		}
		return op1;
	}
	if(ptr->id ==48){
		//TK_ID
		char* retValue = (char*)malloc(sizeof(char)*5);
		printReadVar(regNo,ptr->value,offset,fp);
		sprintf(retValue,"r_%d",regNo);
		regNo++;
		return retValue;
	}
	if(ptr->id ==49){
		//TK_NUM
		char* retValue = (char*)malloc(sizeof(char)*5);
		printReadNum(regNo,ptr->value,fp);
		sprintf(retValue,"r_%d",regNo);
		regNo++;
		return retValue;
	}
	if(ptr->id == 136||ptr->id == 128){
		//singleOrRecdId or allVar
		char* var = ptr->children[0]->value;
		int off =0;
		int i =0;
		int rec_no = getType(ptr->children[0],-1);
		for(i =0;i<sym.r[rec_no].var_num;i++){
			if(strcmp(ptr->children[0]->children[1]->value,sym.r[rec_no].var[i].v_name->value)==0)
				break;
			off = off +4;
		}
		printReadVar(regNo,var,off,fp);
		regNo = regNo+1;
		char* retValue = (char*)malloc(sizeof(char)*5);
		sprintf(retValue,"r_%d",regNo-1);
		return retValue;
	}
}


//generates asm code for assignment statement with integer type
void printAssignmentStament(ast_node* ptr,FILE*fp){
	int reg_base = regNo;
	char* s = getRegister(ptr->children[1],0,fp);
	char* var ;
	int offset =0;
	if(ptr->children[0]->line_no == -1){
		//when left hand side is id.field_id
		var = ptr->children[0]->children[0]->value;
		int rec_no = getType(ptr->children[0]->children[0], -1);
		int i =0;
		for(i =0;i<sym.r[rec_no].var_num;i++){
			if(strcmp(ptr->children[0]->children[1]->value,sym.r[rec_no].var[i].v_name->value)==0)
				break;
			offset = offset +4;
		}
		printWriteVar(var,s,offset,fp);
		regNo = regNo+1;
	}else{
		//when lhs is just id
		var = ptr->children[0]->value;
		printWriteVar(var,s,0,fp);
	}
	regNo = reg_base;
}


//generates asm code for assignment statement with record type
void printRecdAssignmentStament(ast_node* ptr,FILE*fp){
	int recdType = getType(ptr->children[0],-1);
	int offset =0;
	int i =0; 
	for(i =0;i<sym.r[recdType].var_num;i++){
		int reg_base = regNo;
		char* res = getRegister(ptr->children[1],offset,fp);
		printWriteVar(ptr->children[0]->value,res,offset,fp);
		regNo = reg_base;
		offset = offset+4;
	}
}

//handles asm code generation for boolean statements and returns the address in which result is stored
int printBooleanExpression(ast_node* ptr,FILE*fp){
	if(ptr->children[0]->id == 134){
		int r1 = printBooleanExpression(ptr->children[0],fp);
		int r2 = printBooleanExpression(ptr->children[2],fp);
		if(ptr->children[1]->id == 39){
			//TK_AND
			printLogicalAnd(r1,r2,fp);
		}
		else{
			//TK_OR
			printLogicalOr(r1,r2,fp);
		}
		return r1;
	}
	if(ptr->children[0]->id == 41){
		int r = printBooleanExpression(ptr->children[1],fp);
		//TK_NOT
		printLogicalNot(regNo,fp);
		return r;
	}
	if(ptr->children[0]->id == 48||ptr->children[0]->id == 49){
		//handling relational operations
		int r = regNo;
		printReadNum(regNo,"0",fp);	
		printLogicalNot(regNo,fp);
		regNo++;
		char* res1 = getRegister(ptr->children[0],0,fp);
		char* res2 = getRegister(ptr->children[2],0,fp);
		printCompare(res1,res2,fp);
		if(ptr->children[1]->id == 42){
			fprintf(fp,"je jump%d\n",jumpInd);
		}
		if(ptr->children[1]->id == 43){
			fprintf(fp,"jg jump%d\n",jumpInd);
		}
		if(ptr->children[1]->id == 44){
			fprintf(fp,"jge jump%d\n",jumpInd);
		}
		if(ptr->children[1]->id == 45){
			fprintf(fp,"jne jump%d\n",jumpInd);
		}
		if(ptr->children[1]->id == 2){
			fprintf(fp,"jl jump%d\n",jumpInd);
		}
		if(ptr->children[1]->id == 3){
			fprintf(fp,"jle jump%d\n",jumpInd);
		}
		printReadNum(r,"0",fp);
		fprintf(fp,"jump%d:\n",jumpInd);
		jumpInd++;
		return (r);
	}
}

//handles code generation for iterative statement
void printIterativeStament(ast_node* ptr,FILE*fp){
	int loopNo = itrNo;
	itrNo++;
	fprintf(fp,"beginLoop%d:\n",loopNo);
	int regBase = regNo;
	int result = printBooleanExpression(ptr->children[0],fp);
	printCompareToNum(result,0,fp);
	fprintf(fp,"je endLoop%d\n",loopNo);
	regNo = regBase;
	int i =0;
	for(i =1;i<ptr->child_size;i++){
		printICG(ptr->children[i],fp);	
	}
	fprintf(fp,"jmp beginLoop%d\n",loopNo);
	fprintf(fp,"endLoop%d:\n",loopNo);
}

//handles code generation for conditional statement
void printConditionalStament(ast_node* ptr,FILE*fp){
	int regBase = regNo;
	int else_no = elseCount;
	int result = printBooleanExpression(ptr->children[0],fp);
	printCompareToNum(result,0,fp);
	fprintf(fp,"je else%d\n",else_no);
	int i =0;
	for(i =1;i<ptr->child_size;i++){
		if(ptr->children[i]->id == 135){
			//else part
			fprintf(fp,"jmp end_else%d\n",else_no);
			fprintf(fp,"else%d:\n",else_no);
			printICG(ptr->children[i],fp);
			fprintf(fp,"end_else%d:\n",else_no);
			break;
		}
		printICG(ptr->children[i],fp);
	}
}

//handles code generation for IO staements
void printIOStament(ast_node* ptr,FILE*fp){
	if(ptr->children[0]->id == 30){
		//TK_WRITE
		int t = getType(ptr->children[1],-1);
		if(t>10){
			//type integer
			char* res = getRegister(ptr->children[1],0,fp);
			printIOWrite(res,fp);
		}else{
			//type record
			int offset=0;
			int i = 0;
			for(i =0;i<sym.r[t].var_num;i++){
				char* res = getRegister(ptr->children[1],offset,fp);
				printIOWrite(res,fp);
				offset = offset+4;
			}
		}
			
	}else{
		//TK_READ
		if(ptr->children[1]->line_no != -1)
			printIORead(ptr->children[1]->value,0,fp);
		else{
			//read to a fieldid of record variable
			int i =0;
			int offset =0;
			int recNo = getType(ptr->children[1]->children[0],-1);
			for(i =0;i<sym.r[recNo].var_num;i++){
				if(strcmp(ptr->children[1]->children[1]->value,sym.r[recNo].var[i].v_name->value)==0){
					break;
				}
				offset = offset+4;
			}
			printIORead(ptr->children[1]->children[0]->value,offset,fp);
		}
	}
}
 
//generates ICG
void printICG(ast_node* ptr,FILE*fp){
	if(ptr->id == 123){
		fprintf(fp,"	;printAssignmentStament\n");
		int t = getType(ptr->children[0],-1);
		if(t>10){
			printAssignmentStament(ptr,fp);
		}else{
			printRecdAssignmentStament(ptr,fp);
		}
		
	}else if(ptr->id == 124){
		fprintf(fp,"	;printIterativeStament\n");
		printIterativeStament(ptr,fp);		
	}else if(ptr->id == 125){
		fprintf(fp,"	;printConditionalStament\n");
		printConditionalStament(ptr,fp);
	}else if(ptr->id == 126){
		fprintf(fp,"	;printIOStament\n");
		printIOStament(ptr,fp);
	}else{
		int i =0;
		for(i =0;i<ptr->child_size;i++){
			printICG(ptr->children[i],fp);
		}
	}
}

//prints asm code for declared variables from symbol table
void printvar(FILE*fp){
	int i =0;
	for(i = 0;i<sym.global_num;i++){
		fprintf(fp,"%s resb %d\n",sym.g[i].v_name->value,sym.g[i].width*2);
	}
	for(i = 0;i<sym.m.var_num;i++){
		fprintf(fp,"%s resb %d\n",sym.m.var[i].v_name->value,sym.m.var[i].width*2);
	}
	
	fprintf(fp,"section .text\n");
	fprintf(fp,"global main\n");
	fprintf(fp,"extern printf,scanf\n");
	fprintf(fp,"main:\n");
}

