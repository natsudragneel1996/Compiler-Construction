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
#include "lexerDef.h"
#include "lexer.h"
#include "parserDef.h"
#include "parser.h"
#include "astDef.h"
#include "ast.h"
#include "symbolTableDef.h"
#include "symbolTable.h"
#include "typeExtractor.h"
#include "symanticAnalyzerDef.h"              
#include "symanticAnalyzer.h"
#include "codeGeneratorDef.h"
#include "codeGenerator.h"


//to calculate compression ratio
float compression(int a1,int a2){
	float factor;
	factor=(a1-a2)/(float)a1;
	factor=factor*100;
	return factor;


}

int main(int argc,char* argv[]){
	
	initiate_tokenArray();
	
	initiate_parser();

	createParseTable();
	
	MODE = 0;

	int size_node,size_astnode;

	char *input_file,*parseTree_file;

	input_file=(char*)malloc(100*sizeof(char));

	parseTree_file=(char*)malloc(100*sizeof(char));
	

	if(argc!=3){
		printf("insufficient number of command line arguments\n");
		return 0;
	}

	printf(" LEVEL 4: AST/Symbol Table/Type Checking/Semantic Analysis/Code Generator\n");

	
	sscanf(argv[1],"%s",input_file);
	sscanf(argv[2],"%s",parseTree_file);
	

	size_node=sizeof(node);
	size_astnode=sizeof(ast_node);
	
	
	
	
	
	while(1){
		tokenInfo* ptr = (tokenInfo *)malloc(sizeof(tokenInfo)*2000);
		printf("\nENTER THE  MODE NUMBER(1-7) and ENTER 0 TO EXIT\n");
		scanf("%d",&MODE);
		parse_num=1;
		ast_num=0;
		
		if(MODE==1||MODE==2||MODE==3||MODE==4||MODE==5||MODE==6||MODE==7){
			
				FILE *fp = fopen(input_file,"r");
				if(fp==NULL){
					printf("please ensure the given file path is correct\n");
				}
	
				status = 0;
				lexical_err = 0;
				parsing_err = 0;
				semantic_err= 0;
				
				findTokens(fp,1,ptr,0);
				
				//if(MODE==1){
					//continue;
				//}
				
				
				if(MODE==1){
					int i =0;
					while(1){
						int print_len = 0;
						if(ptr[i].t.id==53){
							break;
						}
						if(ptr[i].err_status==1){
							i++;
							continue;
						}
						print_len = printf("%s",ptr[i].t.tokenid);
						while(print_len<=20){
							printf(" ");
							print_len++;
						}
						
						if(ptr[i].val==NULL){
							print_len += printf("%s",ptr[i].t.keyword);
						}
						else{
							print_len += printf("%s",ptr[i].val);
						}
						while(print_len<=55){
							printf(" ");
							print_len++;
						}
 						printf("%d\n",ptr[i].line_no);
						i++;
					}
					if(lexical_err==1){
						printf("!!!LEXICAL ERRORS DETECTED AND PRINTED AT THE TOP!!!\n");
					}
					continue;
				}
	
				parse(ptr);
				
				
				if(MODE == 2){
					if(parsing_err==1||lexical_err==1){
						printf("PARSE TREE COULDN'T BE PRINTED. RESOLVE ABOVE ERRORS\n");
					continue;
					}
					//FILE* fp2=fopen(parseTree_file,"w");
					printParseTreeConsole(Root);
					continue;
					
				}
				ast_node* ast_root;
				if(parsing_err!=1&&lexical_err!=1){
				funct_index =0;
		
				 ast_root = ast_produce(Root);

				ast_redefine(ast_root);
				}
				//fclose(fp2);
				if(MODE==3){
					if(parsing_err==1||lexical_err==1){
				 		printf("ABSTRACT SYNTAX TREE COULDN'T BE PRINTED. RESOLVE ABOVE ERRORS \n");
					continue;
					}
					PrintAst(ast_root);
					//printParseTreeConsole(ast_root);
					continue;					
				}
				if(MODE==4){
					if(parsing_err==1||lexical_err==1){
				 		printf("RESOLVE ABOVE ERRORS \n");
					continue;
					}
					int parse_mem,ast_mem;
					parse_mem=size_node*parse_num;
					printf("parse tree Number of nodes = %d Allocated Memory=%d Bytes\n",parse_num,parse_mem);
					astnodes(ast_root);
					ast_mem=size_astnode*ast_num;
					printf("AST        Number of nodes = %d Allocated Memory=%d Bytes\n",ast_num,ast_mem);
					float comper= compression(parse_mem,ast_mem);
					printf("compression percentage=%f\n",comper);
				continue;
				}
				if(parsing_err!=1&&lexical_err!=1){
					s = (symbolTable*)malloc(sizeof(symbolTable));
					sym = *s;
					int no_funct = getNoOfFunctions(ast_root);
					sym.f = (funcTable*)malloc(sizeof(funcTable)*no_funct);
					populateSymTable(ast_root);
					generateOffset();
				}
				if(MODE==5){
					if(parsing_err==1||lexical_err==1){
				 		printf("SYMBOL TABLE COULDN'T BE PRINTED. RESOLVE ABOVE ERRORS \n");
					continue;
					}
					printSymTable();
					continue;
				}
				
				if(MODE==6){
					if(parsing_err==1||lexical_err==1){
				 		printf("SOURCE CODE IS SYNTACTICALLY INCORRECT. RESOLVE ABOVE ERRORS \n");
					continue;
					}
					symanticAnalysis(ast_root);
					if(semantic_err==0){
						printf("code compiles successfully....");
					}	
				
				continue;
				}
				if(MODE==7){
					if(parsing_err==1||lexical_err==1){
				 		printf("SOURCE CODE IS SYNTACTICALLY INCORRECT. RESOLVE ABOVE ERRORS \n");
					continue;
					}
					symanticAnalysis(ast_root);
					if(semantic_err==0){
					FILE* fp2=fopen(parseTree_file,"w");
					printData(fp2);
					printvar(fp2);
					printICG(sym.m.mainNode,fp2);
					fprintf(fp2,"ret\n");
					fclose(fp2);
					printf("ASM CODE IS GENERATED\n");
					}
					continue;
				}
				fclose(fp);
		}
		else{
			break;
		}
	}	
}

