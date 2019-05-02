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
#include "parserDef.h"
#include "lexerDef.h"
#include "lexer.h"
#include "parser.h"

//returns 1 if token is needed in ast or 0 otherwise
int is_impToken(int id){
	int impTokens[28] = {2,3,6,11,12,14,15,29,30,31,32,33,34,35,38,39,40,41,42,43,44,45,47,48,49,50,51,52};
	int len = 28;
	int i = 0;
	if(id>=100){
		//non terminals will be considered important for now
		return 1;
	}
	for(i=0;i<len;i++){
		if(id==impTokens[i]){
			return 1;
		}
	}
	return 0;
}


//creates new ast_node and copies info from node
ast_node* copyInfo(node* n){
	ast_node* a_node = (ast_node*)malloc(sizeof(ast_node));
	a_node->id = n->id;
	a_node->parentId = n->parentId;
	a_node->value = n->value;
	a_node->line_no = n->line_no;
	
	return a_node;
}

//creates ast from parse tree
ast_node* ast_produce(node* ptr){
	ast_node* ast_ptr = copyInfo(ptr);
	int i =0;
	int j =0;
	ast_ptr->child_size = 0;
	for(i=0;i<=ptr->child_size;i++){
		int c_id = ptr->children[i]->id;
		if(is_impToken(c_id)){
			ast_ptr->children[j] = ast_produce(ptr->children[i]);
			
			ast_ptr->child_size = ast_ptr->child_size +1;
			j++;
		}
	}
	return ast_ptr;
}

//removes unnecessary non terminals
void ast_redefine(ast_node* ptr){
	int i =0;
	for(i = 0;i<ptr->child_size;i++){
		ast_redefine(ptr->children[i]);
	}
	for(i = (ptr->child_size -1);i>=0;i--){
		if(ptr->children[i]->child_size == 0 && (ptr->children[i]->id >=100)){
			ptr->child_size--;
			
			int j = i;
			for(j = i;j<ptr->child_size;j++){
				ptr->children[j] = ptr->children[j+1];
			}
		}
		if(ptr->children[i]->child_size == 1){
			ptr->children[i] = ptr->children[i]->children[0];
		}
		
	}
	
}

//prints ast
void PrintAst(ast_node *ptr){
	printf("\n");
	int print_len;
	//print lexeme current node
	if(ptr->id>=100){
		print_len = printf("---- ");
	}else{
		if(ptr->value != NULL){
			print_len = printf("%s ",ptr->value);
		}else{
			print_len = printf("%s ",token_array[ptr->id].keyword);
		}
	}
	
	while(print_len<=35){
		printf(" ");
		print_len++;
	}
	//print line no
	print_len = print_len + printf("%d ",ptr->line_no);
	
	while(print_len<=40){
		printf(" ");
		print_len++;
	}
	
	//print token name
	
	print_len = print_len + printConsole(ptr->id);
	
	while(print_len<=60){
		printf(" ");
		print_len++;
	}
	
	//print value if num
	
	if(ptr->id == 49||ptr->id == 50){
		print_len+=printf("%s ",ptr->value);
	} else{
		print_len+=printf("---- ");
	}
	
		while(print_len<=75){
		printf(" ");
		print_len++;
	}
	
	//print parent
	if(ptr->parentId==666){
		print_len+=printf("root ");
	}else{
		print_len+=printConsole(ptr->parentId);
	}
	
	while(print_len<=95){
		printf(" ");
		print_len++;
	}
	
	//print is leaf node
	if(ptr->id>=100){
		print_len+=printf("no ");
	}else{
		print_len+=printf("yes ");
	}
	while(print_len<=100){
		printf(" ");
		print_len++;
	}
	
	//node symbol
	print_len+=printConsole(ptr->id);
	
	
	//write remaining print statements
	int len = (ptr->child_size);
	int i;
	for(i=0;i<len;i++){
		PrintAst(ptr->children[i]);
	}
}

//calculates number of nodes in ast
void  astnodes(ast_node *ptr){
	ast_num=ast_num+1;
	int len=(ptr->child_size);
	int i;
	for(i=0;i<len;i++){
		astnodes(ptr->children[i]);
	}



}
