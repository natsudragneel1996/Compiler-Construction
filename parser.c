/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<malloc.h>
#include <string.h>
#include "lexerDef.h"
#include "lexer.h"
#include "parserDef.h"
#include "parser.h"


#define TK_WITH 0
#define TK_ASSIGNOP 1
#define TK_LT 2
#define TK_LE 3
#define TK_END 4
#define TK_ENDIF 5
#define TK_ENDWHILE 6
#define TK_ENDRECORD 7
#define TK_COMMENT 8
#define TK_PARAMETERS 9
#define TK_WHILE 10
#define TK_INT 11
#define TK_REAL 12
#define TK_TYPE 13
#define TK_MAIN 14
#define TK_GLOBAL 15
#define TK_PARAMETER 16
#define TK_LIST 17
#define TK_SQL 18
#define TK_SQR 19
#define TK_INPUT 20
#define TK_OUTPUT 21
#define TK_SEM 22
#define TK_COLON 23
#define TK_DOT 24
#define TK_OP 25
#define TK_CL 26
#define TK_IF 27
#define TK_THEN 28
#define TK_READ 29
#define TK_WRITE 30
#define TK_RETURN 31
#define TK_PLUS 32
#define TK_MINUS 33
#define TK_MUL 34
#define TK_DIV 35
#define TK_CALL 36
#define TK_RECORD 37
#define TK_ELSE 38
#define TK_AND 39
#define TK_OR 40
#define TK_NOT 41
#define TK_EQ  42
#define TK_GT 43
#define TK_GE 44
#define TK_NE 45
#define TK_COMMA 46
#define TK_FIELDID 47
#define TK_ID 48
#define TK_NUM 49
#define TK_RNUM 50
#define TK_FUNID 51
#define TK_RECORDID 52
#define TK_DOLLAR 53
#define TK_EPS -1

#define program 100
#define otherFunctions 101
#define mainFunction 102
#define stmts 103
#define function 104
#define input_par 105
#define output_par 106
#define parameter_list 107
#define dataType 108
#define remaining_list 109
#define primitiveDatatype 110
#define constructedDatatype 111
#define typeDefinitions 112
#define declarations 113
#define otherStmts 114
#define returnStmt 115
#define typeDefinition 116
#define fieldDefinitions 117
#define fieldDefinition 118
#define moreFields 119
#define declaration 120
#define global_or_not 121
#define stmt 122
#define assignmentStmt 123
#define iterativeStmt 124
#define conditionalStmt 125
#define ioStmt 126
#define funCallStmt 127
#define singleOrRecId 128
#define new_24 129
#define arithmeticExpression 130
#define outputParameters 131
#define inputParameters 132
#define idList 133
#define booleanExpression 134
#define elsePart 135
#define allVar 136
#define var 137
#define term 138
#define expPrime 139
#define lowPrecedenceOperators 140
#define factor 141
#define termPrime 142
#define highPrecedenceOperators 143
#define all 144
#define temp 145
#define logicalOp 146
#define relationalOp 147
#define optionalReturn 148
#define more_ids 149
#define numVar 150


//this function takes  file pointer and  id  checks whether it is terminal or non terminal and prints accordingly in the file.
/*int print(int id,FILE*fp){
	int len;
	if(id==-1){
		len = fprintf(fp,"eps ");
	}
	int c = id/100;

	if(c==0){
		
		len = print_terminal(id,fp);
	}
	if(c==1){
		len = fprintf(fp,"%s ",nonTerminalsArray[id%100].name);
	}
	return len;
}*/
int printConsole(int id){
	int len;
	if(id==-1){
		len = printf("eps ");
	}
	int c = id/100;

	if(c==0){
		
		len = print_terminalConsole(id);
	}
	if(c==1){
		len = printf("%s ",nonTerminalsArray[id%100].name);
	}
	return len;
}

//this function prints error msg when  ERROR_5 is  DETECTED and it also specifies where the error is such as line number and gives the expected token.
void printErrorMsg(int stackTop,int token_num,char*val,int line,int info){
	parsing_err=1;
	if(val==NULL){
		val = token_array[token_num].keyword;
	}
	if(info==1){
		
		printf("ERROR_5: The token %s ",token_array[token_num].tokenid); 
		printf("for lexeme %s does not match at line %d. ",val,line);
		printf("The expected token here is %s \n",token_array[stackTop].tokenid);
		
	}
	else{
		printf("ERROR_5: The token %s ",token_array[token_num].tokenid); 
		printf("for lexeme %s does not match at line %d. ",val,line);
		printf("The expected token here is  ");
		int i;
		for(i =0;i<=53;i++){
			if(nonTerminalsArray[stackTop%100].table[i]!=-1){
				printf("%s ",token_array[i].tokenid);
			}
		}
		printf("\n");
	}
}



//this function populates nonTerminalArray with all possible non terminals in the grammar and also populaates productionruleArray with given grammar rules.
void initiate_parser(){
	
	nonTerminalsArraySize =51;
	nonTerminalsArray = (nonTerminal *)malloc(sizeof(nonTerminal)*nonTerminalsArraySize);
	
	int i=0;
	for(i=0;i<nonTerminalsArraySize;i++){
		int j=0;
		for(j=0;j<54;j++){
			nonTerminalsArray[i].table[j] = -1;
		}
	}
	
	nonTerminalsArray[0].id = program;
	strcpy(nonTerminalsArray[0].name,"program");
	nonTerminalsArray[0].first_count =0;
	nonTerminalsArray[0].follows_count =1;
	nonTerminalsArray[0].follows[0] = TK_DOLLAR;

	nonTerminalsArray[1].id = otherFunctions;
	strcpy(nonTerminalsArray[1].name,"otherFunctions");
	nonTerminalsArray[1].first_count =0;
	nonTerminalsArray[1].follows_count =0;

	nonTerminalsArray[2].id = mainFunction;
	strcpy(nonTerminalsArray[2].name,"mainFunction");
	nonTerminalsArray[2].first_count =0;
	nonTerminalsArray[2].follows_count =0;

	nonTerminalsArray[3].id = stmts;
	strcpy(nonTerminalsArray[3].name,"stmts");
	nonTerminalsArray[3].first_count =0;
	nonTerminalsArray[3].follows_count =0;

	nonTerminalsArray[4].id = function;
	strcpy(nonTerminalsArray[4].name,"function");
	nonTerminalsArray[4].first_count =0;
	nonTerminalsArray[4].follows_count =0;

	nonTerminalsArray[5].id = input_par;
	strcpy(nonTerminalsArray[5].name,"input_par");
	nonTerminalsArray[5].first_count =0;
	nonTerminalsArray[5].follows_count =0;

	nonTerminalsArray[6].id = output_par;
	strcpy(nonTerminalsArray[6].name,"output_par");
	nonTerminalsArray[6].first_count =0;
	nonTerminalsArray[6].follows_count =0;

	nonTerminalsArray[7].id = parameter_list;
	strcpy(nonTerminalsArray[7].name,"parameter_list");
	nonTerminalsArray[7].first_count =0;
	nonTerminalsArray[7].follows_count =0;

	nonTerminalsArray[8].id = dataType;
	strcpy(nonTerminalsArray[8].name,"dataType");
	nonTerminalsArray[8].first_count =0;
	nonTerminalsArray[8].follows_count =0;

	nonTerminalsArray[9].id = remaining_list;
	strcpy(nonTerminalsArray[9].name,"remaining_list");
	nonTerminalsArray[9].first_count =0;
	nonTerminalsArray[9].follows_count =0;

    nonTerminalsArray[10].id = primitiveDatatype;
    strcpy(nonTerminalsArray[10].name,"primitiveDatatype");
	nonTerminalsArray[10].first_count =0;
	nonTerminalsArray[10].follows_count =0;

	nonTerminalsArray[11].id = constructedDatatype;
	strcpy(nonTerminalsArray[11].name,"constructedDatatype");
	nonTerminalsArray[11].first_count =0;
	nonTerminalsArray[11].follows_count =0;

	nonTerminalsArray[12].id = typeDefinitions;
	strcpy(nonTerminalsArray[12].name,"typeDefinitions");
	nonTerminalsArray[12].first_count =0;
	nonTerminalsArray[12].follows_count =0;

	nonTerminalsArray[13].id = declarations;
	strcpy(nonTerminalsArray[13].name,"declarations");
	nonTerminalsArray[13].first_count =0;
	nonTerminalsArray[13].follows_count =0;

	nonTerminalsArray[14].id = otherStmts;
	strcpy(nonTerminalsArray[14].name,"otherStmts");
	nonTerminalsArray[14].first_count =0;
	nonTerminalsArray[14].follows_count =0;

	nonTerminalsArray[15].id = returnStmt;
	nonTerminalsArray[15].first_count =0;
	strcpy(nonTerminalsArray[15].name,"returnStmt");
	nonTerminalsArray[15].follows_count =0;

	nonTerminalsArray[16].id = typeDefinition;
	strcpy(nonTerminalsArray[16].name,"typeDefinition");
	nonTerminalsArray[16].first_count =0;
	nonTerminalsArray[16].follows_count =0;

	nonTerminalsArray[17].id = fieldDefinitions;
	strcpy(nonTerminalsArray[17].name,"fieldDefinitions");
	nonTerminalsArray[17].first_count =0;
	nonTerminalsArray[17].follows_count =0;

	nonTerminalsArray[18].id = fieldDefinition;
	strcpy(nonTerminalsArray[18].name,"fieldDefinition");
	nonTerminalsArray[18].first_count =0;
	nonTerminalsArray[18].follows_count =0;

	nonTerminalsArray[19].id = moreFields;
	strcpy(nonTerminalsArray[19].name,"moreFields");
	nonTerminalsArray[19].first_count =0;
	nonTerminalsArray[19].follows_count =0;

	nonTerminalsArray[20].id = declaration;
	strcpy(nonTerminalsArray[20].name,"declaration");
	nonTerminalsArray[20].first_count =0;
	nonTerminalsArray[20].follows_count =0;

	nonTerminalsArray[21].id = global_or_not;
	strcpy(nonTerminalsArray[21].name,"global_or_not");
	nonTerminalsArray[21].first_count =0;
	nonTerminalsArray[21].follows_count =0;

	nonTerminalsArray[22].id = stmt;
	strcpy(nonTerminalsArray[22].name,"stmt");
	nonTerminalsArray[22].first_count =0;
	nonTerminalsArray[22].follows_count =0;

	nonTerminalsArray[23].id = assignmentStmt;
	strcpy(nonTerminalsArray[23].name,"assignmentStmt");
	nonTerminalsArray[23].first_count =0;
	nonTerminalsArray[23].follows_count =0;

	nonTerminalsArray[24].id = iterativeStmt;
	strcpy(nonTerminalsArray[24].name,"iterativeStmt");
	nonTerminalsArray[24].first_count =0;
	nonTerminalsArray[24].follows_count =0;

	nonTerminalsArray[25].id = conditionalStmt;
	strcpy(nonTerminalsArray[25].name,"conditionalStmt");
	nonTerminalsArray[25].first_count =0;
	nonTerminalsArray[25].follows_count =0;

	nonTerminalsArray[26].id = ioStmt;
	strcpy(nonTerminalsArray[26].name,"ioStmt");
	nonTerminalsArray[26].first_count =0;
	nonTerminalsArray[26].follows_count =0;

	nonTerminalsArray[27].id = funCallStmt;
	strcpy(nonTerminalsArray[27].name,"funCallStmt");
	nonTerminalsArray[27].first_count =0;
	nonTerminalsArray[27].follows_count =0;

	nonTerminalsArray[28].id = singleOrRecId;
	strcpy(nonTerminalsArray[28].name,"singleOrRecId");
	nonTerminalsArray[28].first_count =0;
	nonTerminalsArray[28].follows_count =0;

	nonTerminalsArray[29].id = new_24;
	strcpy(nonTerminalsArray[29].name,"new_24");
	nonTerminalsArray[29].first_count =0;
	nonTerminalsArray[29].follows_count =0;

	nonTerminalsArray[30].id = arithmeticExpression;
	strcpy(nonTerminalsArray[30].name,"arithmeticExpression");
	nonTerminalsArray[30].first_count =0;
	nonTerminalsArray[30].follows_count =0;

	nonTerminalsArray[31].id = outputParameters;
	strcpy(nonTerminalsArray[31].name,"outputParameters");
	nonTerminalsArray[31].first_count =0;
	nonTerminalsArray[31].follows_count =0;

	nonTerminalsArray[32].id = inputParameters;
	strcpy(nonTerminalsArray[32].name,"inputParameters");
	nonTerminalsArray[32].first_count =0;
	nonTerminalsArray[32].follows_count =0;

	nonTerminalsArray[33].id = idList;
	strcpy(nonTerminalsArray[33].name,"idList");
	nonTerminalsArray[33].first_count =0;
	nonTerminalsArray[33].follows_count =0;

	nonTerminalsArray[34].id = booleanExpression;
	strcpy(nonTerminalsArray[34].name,"booleanExpression");
	nonTerminalsArray[34].first_count =0;
	nonTerminalsArray[34].follows_count =0;

	nonTerminalsArray[35].id = elsePart;
	strcpy(nonTerminalsArray[35].name,"elsePart");
	nonTerminalsArray[35].first_count =0;
	nonTerminalsArray[35].follows_count =0;

	nonTerminalsArray[36].id = allVar;
	strcpy(nonTerminalsArray[36].name,"allVar");
	nonTerminalsArray[36].first_count =0;
	nonTerminalsArray[36].follows_count =0;

	nonTerminalsArray[37].id = var;
	strcpy(nonTerminalsArray[37].name,"var");
	nonTerminalsArray[37].first_count =0;
	nonTerminalsArray[37].follows_count =0;

	nonTerminalsArray[38].id = term;
	strcpy(nonTerminalsArray[38].name,"term");
	nonTerminalsArray[38].first_count =0;
	nonTerminalsArray[38].follows_count =0;

	nonTerminalsArray[39].id = expPrime;
	strcpy(nonTerminalsArray[39].name,"expPrime");
	nonTerminalsArray[39].first_count =0;
	nonTerminalsArray[39].follows_count =0;

	nonTerminalsArray[40].id = lowPrecedenceOperators;
	strcpy(nonTerminalsArray[40].name,"lowPrecedenceOperators");
	nonTerminalsArray[40].first_count =0;
	nonTerminalsArray[40].follows_count =0;

	nonTerminalsArray[41].id = factor;
	strcpy(nonTerminalsArray[41].name,"factor");
	nonTerminalsArray[41].first_count =0;
	nonTerminalsArray[41].follows_count =0;

	nonTerminalsArray[42].id = termPrime;
	strcpy(nonTerminalsArray[42].name,"termPrime");
	nonTerminalsArray[42].first_count =0;
	nonTerminalsArray[42].follows_count =0;

	nonTerminalsArray[43].id = highPrecedenceOperators;
	strcpy(nonTerminalsArray[43].name,"highPrecedenceOperators");
	nonTerminalsArray[43].first_count =0;
	nonTerminalsArray[43].follows_count =0;

	nonTerminalsArray[44].id = all;
	strcpy(nonTerminalsArray[44].name,"all");
	nonTerminalsArray[44].first_count =0;
	nonTerminalsArray[44].follows_count =0;

	nonTerminalsArray[45].id = temp;
	strcpy(nonTerminalsArray[45].name,"temp");
	nonTerminalsArray[45].first_count =0;
	nonTerminalsArray[45].follows_count =0;

	nonTerminalsArray[46].id = logicalOp;
	strcpy(nonTerminalsArray[46].name,"logicalOp");
	nonTerminalsArray[46].first_count =0;
	nonTerminalsArray[46].follows_count =0;

	nonTerminalsArray[47].id = relationalOp;
	strcpy(nonTerminalsArray[47].name,"relationalOp");
	nonTerminalsArray[47].first_count =0;
	nonTerminalsArray[47].follows_count =0;

	nonTerminalsArray[48].id = optionalReturn;
	strcpy(nonTerminalsArray[48].name,"optionalReturn");
	nonTerminalsArray[48].first_count =0;
	nonTerminalsArray[48].follows_count =0;

	nonTerminalsArray[49].id = more_ids;
	strcpy(nonTerminalsArray[49].name,"more_ids");
	nonTerminalsArray[49].first_count =0;
	nonTerminalsArray[49].follows_count =0;

	nonTerminalsArray[50].id = numVar;
	strcpy(nonTerminalsArray[50].name,"numVar");
	nonTerminalsArray[50].first_count =0;
	nonTerminalsArray[50].follows_count =0;
	
	
	prodRulesArraySize = 90;
	prodRulesArray = (prodRule *)malloc(sizeof(nonTerminal)*prodRulesArraySize);

	prodRulesArray[0].id = 200;
	prodRulesArray[0].leftHand = program ;
	prodRulesArray[0].righthand[0] =otherFunctions ;
	prodRulesArray[0].righthand[1] =mainFunction;
	prodRulesArray[0].righthand[2] =TK_EPS;

	prodRulesArray[1].id = 201;
	prodRulesArray[1].leftHand = mainFunction;
	prodRulesArray[1].righthand[0] =TK_MAIN;
	prodRulesArray[1].righthand[1] =stmts;
	prodRulesArray[1].righthand[2]=TK_END;
	prodRulesArray[1].righthand[3]=TK_EPS;


	prodRulesArray[2].id = 202;
	prodRulesArray[2].leftHand = otherFunctions ;
	prodRulesArray[2].righthand[0] =function;
	prodRulesArray[2].righthand[1] =otherFunctions;
	prodRulesArray[2].righthand[2] =TK_EPS ;

	prodRulesArray[3].id = 203;
	prodRulesArray[3].leftHand = otherFunctions ;
	prodRulesArray[3].righthand[0] =TK_EPS ;

	prodRulesArray[4].id = 204 ;
	prodRulesArray[4].leftHand = function ;
	prodRulesArray[4].righthand[0] =TK_FUNID ;
	prodRulesArray[4].righthand[1] =input_par;
	prodRulesArray[4].righthand[2] =output_par;
	prodRulesArray[4].righthand[3] =TK_SEM;
	prodRulesArray[4].righthand[4] =stmts;
	prodRulesArray[4].righthand[5] =TK_END;
	prodRulesArray[4].righthand[6] =TK_EPS;


	prodRulesArray[5].id = 205;
	prodRulesArray[5].leftHand = input_par;
	prodRulesArray[5].righthand[0] =TK_INPUT;
	prodRulesArray[5].righthand[1] =TK_PARAMETER;
	prodRulesArray[5].righthand[2] =TK_LIST;
	prodRulesArray[5].righthand[3] =TK_SQL;
	prodRulesArray[5].righthand[4] =parameter_list;
	prodRulesArray[5].righthand[5] =TK_SQR;
	prodRulesArray[5].righthand[6] =TK_EPS;

	prodRulesArray[6].id = 206;
	prodRulesArray[6].leftHand = output_par;
	prodRulesArray[6].righthand[0] =TK_OUTPUT ;
	prodRulesArray[6].righthand[1] =TK_PARAMETER;
	prodRulesArray[6].righthand[2] =TK_LIST;
	prodRulesArray[6].righthand[3] =TK_SQL ;
	prodRulesArray[6].righthand[4] =parameter_list ;
	prodRulesArray[6].righthand[5] =TK_SQR ;
	prodRulesArray[6].righthand[6] =TK_EPS ;

	prodRulesArray[7].id = 207;
	prodRulesArray[7].leftHand = output_par ;
	prodRulesArray[7].righthand[0] =TK_EPS ;

	prodRulesArray[8].id = 208;
	prodRulesArray[8].leftHand = parameter_list ;
	prodRulesArray[8].righthand[0] =dataType;
	prodRulesArray[8].righthand[1] =TK_ID;
	prodRulesArray[8].righthand[2] =remaining_list;
	prodRulesArray[8].righthand[3] =TK_EPS;

	prodRulesArray[9].id = 209;
	prodRulesArray[9].leftHand = dataType;
	prodRulesArray[9].righthand[0] =primitiveDatatype;
	prodRulesArray[9].righthand[1] =TK_EPS;

	prodRulesArray[10].id = 210;
	prodRulesArray[10].leftHand = dataType ;
	prodRulesArray[10].righthand[0] =constructedDatatype;
	prodRulesArray[10].righthand[1] =TK_EPS;

	prodRulesArray[11].id = 211;
	prodRulesArray[11].leftHand = primitiveDatatype ;
	prodRulesArray[11].righthand[0] =TK_INT;
	prodRulesArray[11].righthand[1] =TK_EPS;

	prodRulesArray[12].id = 212;
	prodRulesArray[12].leftHand = primitiveDatatype ;
	prodRulesArray[12].righthand[0] =TK_REAL;
	prodRulesArray[12].righthand[1] =TK_EPS;

	prodRulesArray[13].id = 213;
	prodRulesArray[13].leftHand = constructedDatatype ;
	prodRulesArray[13].righthand[0] =TK_RECORD;
	prodRulesArray[13].righthand[1] =TK_RECORDID;
	prodRulesArray[13].righthand[2] =TK_EPS;

	prodRulesArray[14].id = 214;
	prodRulesArray[14].leftHand = remaining_list ;
	prodRulesArray[14].righthand[0] =TK_COMMA;
	prodRulesArray[14].righthand[1] =parameter_list;
	prodRulesArray[14].righthand[2] =TK_EPS;

	prodRulesArray[15].id = 215;
	prodRulesArray[15].leftHand = remaining_list ;
	prodRulesArray[15].righthand[0] =TK_EPS;


	prodRulesArray[16].id = 216;
	prodRulesArray[16].leftHand = stmts ;
	prodRulesArray[16].righthand[0] =typeDefinitions;
	prodRulesArray[16].righthand[1] =declarations;
	prodRulesArray[16].righthand[2] =otherStmts;
	prodRulesArray[16].righthand[3] =returnStmt;
	prodRulesArray[16].righthand[4] =TK_EPS;
	
	prodRulesArray[17].id = 217;
	prodRulesArray[17].leftHand = typeDefinitions ;
	prodRulesArray[17].righthand[0] =typeDefinition;
	prodRulesArray[17].righthand[1] =typeDefinitions;
	prodRulesArray[17].righthand[2] =TK_EPS;

	prodRulesArray[18].id = 218;
	prodRulesArray[18].leftHand = typeDefinitions ;
	prodRulesArray[18].righthand[0] =TK_EPS;

	prodRulesArray[19].id = 219;
	prodRulesArray[19].leftHand = typeDefinition ;
	prodRulesArray[19].righthand[0] =TK_RECORD;
	prodRulesArray[19].righthand[1] =TK_RECORDID;
	prodRulesArray[19].righthand[2] =fieldDefinitions;
	prodRulesArray[19].righthand[3] =TK_ENDRECORD;
	prodRulesArray[19].righthand[4] =TK_SEM;
	prodRulesArray[19].righthand[5] =TK_EPS;

	prodRulesArray[20].id = 220;
	prodRulesArray[20].leftHand = fieldDefinitions ;
	prodRulesArray[20].righthand[0] =fieldDefinition;
	prodRulesArray[20].righthand[1] =fieldDefinition;
	prodRulesArray[20].righthand[2] =moreFields;
	prodRulesArray[20].righthand[3] =TK_EPS;

	prodRulesArray[21].id = 221;
	prodRulesArray[21].leftHand = fieldDefinition ;
	prodRulesArray[21].righthand[0] =TK_TYPE;
	prodRulesArray[21].righthand[1] =primitiveDatatype;
	prodRulesArray[21].righthand[2] =TK_COLON;
	prodRulesArray[21].righthand[3] =TK_FIELDID;
	prodRulesArray[21].righthand[4] =TK_SEM;
	prodRulesArray[21].righthand[5] =TK_EPS;

	prodRulesArray[22].id = 222;
	prodRulesArray[22].leftHand = moreFields ;
	prodRulesArray[22].righthand[0] =fieldDefinition;
	prodRulesArray[22].righthand[1] =moreFields;
	prodRulesArray[22].righthand[2] =TK_EPS;

	prodRulesArray[23].id = 223;
	prodRulesArray[23].leftHand = moreFields ;
	prodRulesArray[23].righthand[0] =TK_EPS;

	prodRulesArray[24].id = 224;
	prodRulesArray[24].leftHand = declarations ;
	prodRulesArray[24].righthand[0] =declaration;
	prodRulesArray[24].righthand[1] =declarations;
	prodRulesArray[24].righthand[2] =TK_EPS;

	prodRulesArray[25].id = 225;
	prodRulesArray[25].leftHand = declarations ;
	prodRulesArray[25].righthand[0] =TK_EPS;

	prodRulesArray[26].id = 226;
	prodRulesArray[26].leftHand = declaration ;
	prodRulesArray[26].righthand[0] =TK_TYPE;
	prodRulesArray[26].righthand[1] =dataType;
	prodRulesArray[26].righthand[2] =TK_COLON;
	prodRulesArray[26].righthand[3] =TK_ID;
	prodRulesArray[26].righthand[4] =global_or_not;
	prodRulesArray[26].righthand[5] =TK_SEM;
	prodRulesArray[26].righthand[6] =TK_EPS;

	prodRulesArray[27].id = 227;
	prodRulesArray[27].leftHand = global_or_not ;
	prodRulesArray[27].righthand[0] =TK_COLON;
	prodRulesArray[27].righthand[1] =TK_GLOBAL;
	prodRulesArray[27].righthand[2] =TK_EPS;

	prodRulesArray[28].id = 228;
	prodRulesArray[28].leftHand = global_or_not ;
	prodRulesArray[28].righthand[0] =TK_EPS;

	prodRulesArray[29].id = 229;
	prodRulesArray[29].leftHand = otherStmts ;
	prodRulesArray[29].righthand[0] =stmt;
	prodRulesArray[29].righthand[1] =otherStmts;
	prodRulesArray[29].righthand[2] =TK_EPS;

	prodRulesArray[30].id = 230;
	prodRulesArray[30].leftHand = otherStmts ;
	prodRulesArray[30].righthand[0] =TK_EPS;

	prodRulesArray[31].id = 231;
	prodRulesArray[31].leftHand = stmt ;
	prodRulesArray[31].righthand[0] =assignmentStmt;
	prodRulesArray[31].righthand[1] =TK_EPS;

	prodRulesArray[32].id = 232;
	prodRulesArray[32].leftHand = stmt ;
	prodRulesArray[32].righthand[0] =iterativeStmt;
	prodRulesArray[32].righthand[1] =TK_EPS;

	prodRulesArray[33].id = 233;
	prodRulesArray[33].leftHand = stmt ;
	prodRulesArray[33].righthand[0] =conditionalStmt;
	prodRulesArray[33].righthand[1] =TK_EPS;

	prodRulesArray[34].id = 234;
	prodRulesArray[34].leftHand = stmt ;
	prodRulesArray[34].righthand[0] =ioStmt;
	prodRulesArray[34].righthand[1] =TK_EPS;

	prodRulesArray[35].id = 235;
	prodRulesArray[35].leftHand = stmt ;
	prodRulesArray[35].righthand[0] =funCallStmt;
	prodRulesArray[35].righthand[1] =TK_EPS;

	prodRulesArray[36].id = 236;
	prodRulesArray[36].leftHand = assignmentStmt ;
	prodRulesArray[36].righthand[0] =singleOrRecId;
	prodRulesArray[36].righthand[1] =TK_ASSIGNOP;
	prodRulesArray[36].righthand[2] =arithmeticExpression;
	prodRulesArray[36].righthand[3] =TK_SEM;
	prodRulesArray[36].righthand[4] =TK_EPS;
	
	prodRulesArray[37].id = 237;
	prodRulesArray[37].leftHand = singleOrRecId ;
	prodRulesArray[37].righthand[0] =TK_ID;
	prodRulesArray[37].righthand[1] =new_24;
	prodRulesArray[37].righthand[2] =TK_EPS;

	prodRulesArray[38].id = 238;
	prodRulesArray[38].leftHand = new_24 ;
	prodRulesArray[38].righthand[0] =TK_DOT;
	prodRulesArray[38].righthand[1] =TK_FIELDID;
	prodRulesArray[38].righthand[2] =TK_EPS;

	prodRulesArray[39].id = 239;
	prodRulesArray[39].leftHand = new_24 ;
	prodRulesArray[39].righthand[0] =TK_EPS;

	prodRulesArray[40].id = 240;
	prodRulesArray[40].leftHand = funCallStmt ;
	prodRulesArray[40].righthand[0] =outputParameters;
	prodRulesArray[40].righthand[1] =TK_CALL;
	prodRulesArray[40].righthand[2] =TK_FUNID;
	prodRulesArray[40].righthand[3] =TK_WITH;
	prodRulesArray[40].righthand[4] =TK_PARAMETERS;
	prodRulesArray[40].righthand[5] =inputParameters;
	prodRulesArray[40].righthand[6] =TK_SEM;
	prodRulesArray[40].righthand[7] =TK_EPS;	

	prodRulesArray[41].id = 241;
	prodRulesArray[41].leftHand = outputParameters ;
	prodRulesArray[41].righthand[0] =TK_SQL;
	prodRulesArray[41].righthand[1] =idList;
	prodRulesArray[41].righthand[2] =TK_SQR;
	prodRulesArray[41].righthand[3] =TK_ASSIGNOP;
	prodRulesArray[41].righthand[4] =TK_EPS;

	prodRulesArray[42].id = 242;
	prodRulesArray[42].leftHand = outputParameters ;
	prodRulesArray[42].righthand[0] =TK_EPS;
	
	prodRulesArray[4].id = 243;
	prodRulesArray[43].leftHand = inputParameters ;
	prodRulesArray[43].righthand[0] =TK_SQL;
	prodRulesArray[43].righthand[1] =idList;
	prodRulesArray[43].righthand[2] =TK_SQR;
	prodRulesArray[43].righthand[3] =TK_EPS;

	prodRulesArray[44].id = 244;
	prodRulesArray[44].leftHand = iterativeStmt ;
	prodRulesArray[44].righthand[0] =TK_WHILE;
	prodRulesArray[44].righthand[1] =TK_OP;
	prodRulesArray[44].righthand[2] =booleanExpression;
	prodRulesArray[44].righthand[3] =TK_CL;
	prodRulesArray[44].righthand[4] =stmt;
	prodRulesArray[44].righthand[5] =otherStmts;
	prodRulesArray[44].righthand[6] =TK_ENDWHILE;
	prodRulesArray[44].righthand[7] =TK_EPS;

	prodRulesArray[45].id = 245;
	prodRulesArray[45].leftHand = conditionalStmt ;
	prodRulesArray[45].righthand[0] =TK_IF;
	prodRulesArray[45].righthand[1] =TK_OP;
	prodRulesArray[45].righthand[2] =booleanExpression;
	prodRulesArray[45].righthand[3] =TK_CL;
	prodRulesArray[45].righthand[4] =TK_THEN;
	prodRulesArray[45].righthand[5] =stmt;
	prodRulesArray[45].righthand[6] =otherStmts;
	prodRulesArray[45].righthand[7] =elsePart;
	prodRulesArray[45].righthand[8] =TK_EPS;
	
	prodRulesArray[46].id = 246;
	prodRulesArray[46].leftHand = elsePart ;
	prodRulesArray[46].righthand[0] =TK_ELSE;
	prodRulesArray[46].righthand[1] =stmt;
	prodRulesArray[46].righthand[2] =otherStmts;
	prodRulesArray[46].righthand[3] =TK_ENDIF;
	prodRulesArray[46].righthand[4] =TK_EPS;

	prodRulesArray[47].id = 247;
	prodRulesArray[47].leftHand = elsePart ;
	prodRulesArray[47].righthand[0] =TK_ENDIF;
	prodRulesArray[47].righthand[1] =TK_EPS;

	prodRulesArray[48].id = 248;
	prodRulesArray[48].leftHand = ioStmt ;
	prodRulesArray[48].righthand[0] =TK_READ;
	prodRulesArray[48].righthand[1] =TK_OP;
	prodRulesArray[48].righthand[2] =singleOrRecId;
	prodRulesArray[48].righthand[3] =TK_CL;
	prodRulesArray[48].righthand[4] =TK_SEM;
	prodRulesArray[48].righthand[5] =TK_EPS;

	prodRulesArray[49].id = 249;
	prodRulesArray[49].leftHand = ioStmt ;
	prodRulesArray[49].righthand[0] =TK_WRITE;
	prodRulesArray[49].righthand[1] =TK_OP;
	prodRulesArray[49].righthand[2] =allVar;
	prodRulesArray[49].righthand[3] =TK_CL;
	prodRulesArray[49].righthand[4] =TK_SEM;
	prodRulesArray[49].righthand[5] =TK_EPS;

	prodRulesArray[50].id = 250;
	prodRulesArray[50].leftHand = allVar ;
	prodRulesArray[50].righthand[0] =TK_ID;
	prodRulesArray[50].righthand[1] =temp;
	prodRulesArray[50].righthand[2] =TK_EPS;

	prodRulesArray[51].id = 251;
	prodRulesArray[51].leftHand = allVar ;
	prodRulesArray[51].righthand[0] =numVar;
	prodRulesArray[51].righthand[1] =TK_EPS;
	
	prodRulesArray[52].id = 252;
	prodRulesArray[52].leftHand = arithmeticExpression ;
	prodRulesArray[52].righthand[0] =term;
	prodRulesArray[52].righthand[1] =expPrime;
	prodRulesArray[52].righthand[2] =TK_EPS;

	prodRulesArray[53].id = 253;
	prodRulesArray[53].leftHand = expPrime ;
	prodRulesArray[53].righthand[0] =lowPrecedenceOperators;
	prodRulesArray[53].righthand[1] =term;
	prodRulesArray[53].righthand[2] =expPrime;
	prodRulesArray[53].righthand[3] =TK_EPS;

	prodRulesArray[54].id = 254;
	prodRulesArray[54].leftHand = expPrime ;
	prodRulesArray[54].righthand[0] =TK_EPS;

	prodRulesArray[55].id = 255;
	prodRulesArray[55].leftHand = term ;
	prodRulesArray[55].righthand[0] =factor;
	prodRulesArray[55].righthand[1] =termPrime;
	prodRulesArray[55].righthand[2] =TK_EPS;

	prodRulesArray[56].id = 256;
	prodRulesArray[56].leftHand = termPrime ;
	prodRulesArray[56].righthand[0] =highPrecedenceOperators;
	prodRulesArray[56].righthand[1] =factor;
	prodRulesArray[56].righthand[2] =termPrime;
	prodRulesArray[56].righthand[3] =TK_EPS;

	prodRulesArray[57].id = 257;
	prodRulesArray[57].leftHand = termPrime ;
	prodRulesArray[57].righthand[0] =TK_EPS;

	prodRulesArray[58].id = 258;
	prodRulesArray[58].leftHand = factor ;
	prodRulesArray[58].righthand[0] =TK_OP;
	prodRulesArray[58].righthand[1] =arithmeticExpression;
	prodRulesArray[58].righthand[2] =TK_CL;
	prodRulesArray[58].righthand[3] =TK_EPS;
	
	prodRulesArray[59].id = 259;
	prodRulesArray[59].leftHand = factor ;
	prodRulesArray[59].righthand[0] =all;
	prodRulesArray[59].righthand[1] =TK_EPS;
	
	prodRulesArray[60].id = 260;
	prodRulesArray[60].leftHand = highPrecedenceOperators ;
	prodRulesArray[60].righthand[0] =TK_MUL;
	prodRulesArray[60].righthand[1] =TK_EPS;	

	prodRulesArray[61].id = 261;
	prodRulesArray[61].leftHand = highPrecedenceOperators ;
	prodRulesArray[61].righthand[0] =TK_DIV;
	prodRulesArray[61].righthand[1] =TK_EPS;

	prodRulesArray[62].id = 262;
	prodRulesArray[62].leftHand = lowPrecedenceOperators ;
	prodRulesArray[62].righthand[0] =TK_PLUS;
	prodRulesArray[62].righthand[1] =TK_EPS;

	prodRulesArray[63].id = 263;
	prodRulesArray[63].leftHand = lowPrecedenceOperators ;
	prodRulesArray[63].righthand[0] =TK_MINUS;
	prodRulesArray[63].righthand[1] =TK_EPS;

	prodRulesArray[64].id = 264;
	prodRulesArray[64].leftHand = numVar ;
	prodRulesArray[64].righthand[0] =TK_NUM;
	prodRulesArray[64].righthand[1] =TK_EPS;

	prodRulesArray[65].id = 265;
	prodRulesArray[65].leftHand = all ;
	prodRulesArray[65].righthand[0] =TK_NUM;
	prodRulesArray[65].righthand[1] =TK_EPS;

	prodRulesArray[66].id = 266;
	prodRulesArray[66].leftHand = all ;
	prodRulesArray[66].righthand[0] =TK_RNUM;
	prodRulesArray[66].righthand[1] =TK_EPS;

	prodRulesArray[67].id = 267;
	prodRulesArray[67].leftHand = all ;
	prodRulesArray[67].righthand[0] =TK_ID;
	prodRulesArray[67].righthand[1] =temp;
	prodRulesArray[67].righthand[2] =TK_EPS;

	prodRulesArray[68].id = 268;
	prodRulesArray[68].leftHand = temp ;
	prodRulesArray[68].righthand[0] =TK_DOT;
	prodRulesArray[68].righthand[1] =TK_FIELDID;
	prodRulesArray[68].righthand[2] =TK_EPS;

	prodRulesArray[69].id = 269;
	prodRulesArray[69].leftHand = temp ;
	prodRulesArray[69].righthand[0] =TK_EPS;

	prodRulesArray[70].id = 270;
	prodRulesArray[70].leftHand = booleanExpression ;
	prodRulesArray[70].righthand[0] =TK_OP;
	prodRulesArray[70].righthand[1] =booleanExpression;
	prodRulesArray[70].righthand[2] =TK_CL;
	prodRulesArray[70].righthand[3] =logicalOp;
	prodRulesArray[70].righthand[4] =TK_OP;
	prodRulesArray[70].righthand[5] =booleanExpression;
	prodRulesArray[70].righthand[6] =TK_CL;
	prodRulesArray[70].righthand[7] =TK_EPS;

	prodRulesArray[71].id = 271;
	prodRulesArray[71].leftHand = booleanExpression ;
	prodRulesArray[71].righthand[0] =var;
	prodRulesArray[71].righthand[1] =relationalOp;
	prodRulesArray[71].righthand[2] =var;
	prodRulesArray[71].righthand[3] =TK_EPS;

	prodRulesArray[72].id = 272;
	prodRulesArray[72].leftHand = booleanExpression ;
	prodRulesArray[72].righthand[0] =TK_NOT;
	prodRulesArray[72].righthand[1] =TK_OP;
	prodRulesArray[72].righthand[2] =booleanExpression;
	prodRulesArray[72].righthand[3] =TK_CL;
	prodRulesArray[72].righthand[4] =TK_EPS;

	prodRulesArray[73].id = 273;
	prodRulesArray[73].leftHand = var ;
	prodRulesArray[73].righthand[0] =TK_ID;
	prodRulesArray[73].righthand[1] =TK_EPS;

	prodRulesArray[74].id = 274;
	prodRulesArray[74].leftHand = var ;
	prodRulesArray[74].righthand[0] =TK_NUM;
	prodRulesArray[74].righthand[1] =TK_EPS;
	
	prodRulesArray[75].id = 275;
	prodRulesArray[75].leftHand = var ;
	prodRulesArray[75].righthand[0] =TK_RNUM;
	prodRulesArray[75].righthand[1] =TK_EPS;
	
	prodRulesArray[76].id = 276;
	prodRulesArray[76].leftHand = logicalOp ;
	prodRulesArray[76].righthand[0] =TK_AND;
	prodRulesArray[76].righthand[1] =TK_EPS;

	prodRulesArray[77].id = 277;
	prodRulesArray[77].leftHand = logicalOp ;
	prodRulesArray[77].righthand[0] =TK_OR;
	prodRulesArray[77].righthand[1] =TK_EPS;

	prodRulesArray[78].id = 278;
	prodRulesArray[78].leftHand = relationalOp ;
	prodRulesArray[78].righthand[0] =TK_LT;
	prodRulesArray[78].righthand[1] =TK_EPS;

	prodRulesArray[79].id = 279;
	prodRulesArray[79].leftHand = relationalOp ;
	prodRulesArray[79].righthand[0] =TK_LE;
	prodRulesArray[79].righthand[1] =TK_EPS;

	prodRulesArray[80].id = 280;
	prodRulesArray[80].leftHand = relationalOp ;
	prodRulesArray[80].righthand[0] =TK_EQ;
	prodRulesArray[80].righthand[1] =TK_EPS;

	prodRulesArray[81].id = 281;
	prodRulesArray[81].leftHand = relationalOp ;
	prodRulesArray[81].righthand[0] =TK_GT;
	prodRulesArray[81].righthand[1] =TK_EPS;

	prodRulesArray[82].id = 282;
	prodRulesArray[82].leftHand = relationalOp ;
	prodRulesArray[82].righthand[0] =TK_GE;
	prodRulesArray[82].righthand[1] =TK_EPS;

	prodRulesArray[83].id = 283;
	prodRulesArray[83].leftHand = relationalOp ;
	prodRulesArray[83].righthand[0] =TK_NE;
	prodRulesArray[83].righthand[1] =TK_EPS;

	prodRulesArray[84].id = 284;
	prodRulesArray[84].leftHand = returnStmt ;
	prodRulesArray[84].righthand[0] =TK_RETURN;
	prodRulesArray[84].righthand[1] =optionalReturn;
	prodRulesArray[84].righthand[2] =TK_SEM;
	prodRulesArray[84].righthand[3] =TK_EPS;
	
	prodRulesArray[85].id = 285;
	prodRulesArray[85].leftHand = optionalReturn ;
	prodRulesArray[85].righthand[0] =TK_SQL;
	prodRulesArray[85].righthand[1] =idList;
	prodRulesArray[85].righthand[2] =TK_SQR;
	prodRulesArray[85].righthand[3] =TK_EPS;	
	
	prodRulesArray[86].id = 286;
	prodRulesArray[86].leftHand = optionalReturn ;
	prodRulesArray[86].righthand[0] =TK_EPS;	
	
	prodRulesArray[87].id = 287;
	prodRulesArray[87].leftHand = idList ;
	prodRulesArray[87].righthand[0] =TK_ID;
	prodRulesArray[87].righthand[1] =more_ids;
	prodRulesArray[87].righthand[2] =TK_EPS;	
	
	prodRulesArray[88].id = 278;
	prodRulesArray[88].leftHand = more_ids ;
	prodRulesArray[88].righthand[0] =TK_COMMA;
	prodRulesArray[88].righthand[1] =idList;
	prodRulesArray[88].righthand[2] =TK_EPS;	
	
	prodRulesArray[89].id = 289;
	prodRulesArray[89].leftHand = more_ids ;
	prodRulesArray[89].righthand[0] =TK_EPS;	
	
	prodRulesArray[90].id = 290;
	prodRulesArray[90].leftHand = numVar ;
	prodRulesArray[90].righthand[0] =TK_RNUM;
	prodRulesArray[90].righthand[1] =TK_EPS;

}
//this function computes  first set  for  for a particular non termianal.
void findFirsts(int nonTerminal){
	if(nonTerminalsArray[nonTerminal%100].first_count!=0){

		return;
	}
	
	int i=0;
	for(i=0;i<prodRulesArraySize;i++){  
		if(prodRulesArray[i].leftHand == nonTerminal){
			
			firstof_firsts(i+200,0);
		}
	}
}

//this function computes  first terminal set  for lHS non terminal in a particular production rule.
void firstof_firsts(int prodNo, int index){
	
	int lhs = prodRulesArray[prodNo%200].leftHand;

	//if the index corresponds to 'e' or 'terminal'
	if(prodRulesArray[prodNo%200].righthand[index]<100){
		int obtTerminal = prodRulesArray[prodNo%200].righthand[index] ;
		int firstsIndex = 	nonTerminalsArray[lhs%100].first_count;
	
		int i=0;
		for(i=0;i<firstsIndex;i++){
			if(nonTerminalsArray[lhs%100].first[i]==obtTerminal){
				break;
			}
		}
		if(i==firstsIndex){
			nonTerminalsArray[lhs%100].first[firstsIndex] = obtTerminal;
			nonTerminalsArray[lhs%100].first_count = firstsIndex+1;
		}

		
		return;
	}


	//if lhs is non terminal
	int targetFirst = prodRulesArray[prodNo%200].righthand[index];
	if(nonTerminalsArray[targetFirst%100].first_count==0){
		findFirsts(targetFirst);
	}
	int count = nonTerminalsArray[targetFirst%100].first_count;
	int i;
	for(i=0;i<count;i++){
		if(nonTerminalsArray[targetFirst%100].first[i]==-1){
			firstof_firsts(prodNo,index+1);
			continue;
		}

		int obtTerminal = nonTerminalsArray[targetFirst%100].first[i];

		int firstsIndex = 	nonTerminalsArray[lhs%100].first_count;
		int i=0;
		for(i=0;i<firstsIndex;i++){
			if(nonTerminalsArray[lhs%100].first[i]==obtTerminal){
				break;
			}
		}
		if(i==firstsIndex){
			nonTerminalsArray[lhs%100].first[firstsIndex] = obtTerminal;
			nonTerminalsArray[lhs%100].first_count = firstsIndex+1;
		}

	}

}

//this function computes  follow set of terminals for a particular non terminal
void findFollows(int nonTerminal){
	//finds the production rule
	if(nonTerminalsArray[nonTerminal%100].follows_count!=0){
		return;
	}
	int i=0;
	for(i=0;i<prodRulesArraySize;i++){  
		int j =0;
		while(prodRulesArray[i].righthand[j]!=-1){
			if(prodRulesArray[i].righthand[j]==nonTerminal){
				
				firstof_follows(nonTerminal,200+i,j+1);
				
			}
			j++;
		}
	}
}


//this function computes  follows of non terminal in a production rule.
void firstof_follows(int input_NT, int prodNo, int index){

	int lhs = prodRulesArray[prodNo%200].leftHand;
	//if the index corresponds to 'e'
	
	if(prodRulesArray[prodNo%200].righthand[index]==-1){
		if(nonTerminalsArray[lhs%100].follows_count==0){		
			findFollows(lhs);
		}
		
		int i = nonTerminalsArray[lhs%100].follows_count;
		int j;
		for(j=0;j<i;j++){
			int obtTerminal = nonTerminalsArray[lhs%100].follows[j];
			
			int followIndex = nonTerminalsArray[input_NT%100].follows_count;
			int m;
			for(m=0;m<followIndex;m++){
				if(obtTerminal==nonTerminalsArray[input_NT%100].follows[m]){
					break;
				}
			}
			if(m==followIndex){
				nonTerminalsArray[input_NT%100].follows[followIndex] = obtTerminal;
				nonTerminalsArray[input_NT%100].follows_count = followIndex+1;
			}

		}
		return;
	}

	//if lhs is terminal
	if(prodRulesArray[prodNo%200].righthand[index]<100){

		int obtTerminal = prodRulesArray[prodNo%200].righthand[index];
		int followIndex = nonTerminalsArray[input_NT%100].follows_count;
		int m;
		for(m=0;m<followIndex;m++){
			if(obtTerminal==nonTerminalsArray[input_NT%100].follows[m]){
				break;
			}
		}
		if(m==followIndex){
			nonTerminalsArray[input_NT%100].follows[followIndex] = obtTerminal;
			nonTerminalsArray[input_NT%100].follows_count = followIndex+1;
		}
		return;
	}

	//if lhs is non terminal
	int targetFirst = prodRulesArray[prodNo%200].righthand[index];
	int count = nonTerminalsArray[targetFirst%100].first_count;
	int i;
	for(i=0;i<count;i++){
		if(nonTerminalsArray[targetFirst%100].first[i]==-1){
			firstof_follows(input_NT,prodNo,index+1);
			continue;
		}
		int obtTerminal = nonTerminalsArray[targetFirst%100].first[i];
		int followIndex = nonTerminalsArray[input_NT%100].follows_count;
		int m;
		for(m=0;m<followIndex;m++){
			if(obtTerminal==nonTerminalsArray[input_NT%100].follows[m]){
				break;
			}
		}
		if(m==followIndex){
			nonTerminalsArray[input_NT%100].follows[followIndex] = obtTerminal;
			nonTerminalsArray[input_NT%100].follows_count = followIndex+1;
		}
	}
}

//this function is used in populating the parse table with first set and follow set.
void firstof(int prodNo, int index){

	int lhs = prodRulesArray[prodNo%200].leftHand;
	
	//if the index corresponds to 'e'
	if(prodRulesArray[prodNo%200].righthand[index]==-1){		
		int i = nonTerminalsArray[lhs%100].follows_count;
		int j;
		for(j=0;j<i;j++){
			int obtTerminal = nonTerminalsArray[lhs%100].follows[j];
			nonTerminalsArray[lhs%100].table[obtTerminal] = prodNo;
		}
		return;
	}
	
	//if lhs is terminal
	if(prodRulesArray[prodNo%200].righthand[index]<100){		
		
		int obtTerminal = prodRulesArray[prodNo%200].righthand[index];
		nonTerminalsArray[lhs%100].table[obtTerminal] = prodNo;
		return;
	}
	
	//if lhs is non terminal
	int targetFirst = prodRulesArray[prodNo%200].righthand[index];
	int count = nonTerminalsArray[targetFirst%100].first_count;
	int i;
	for(i=0;i<count;i++){
		if(nonTerminalsArray[targetFirst%100].first[i]==-1){
			firstof(prodNo,index+1);
		}
		int obtTerminal = nonTerminalsArray[targetFirst%100].first[i];
		nonTerminalsArray[lhs%100].table[obtTerminal] = prodNo;
	}
}
// this function  parses the  input array of tokens
void parse(tokenInfo *input){
	int index =0;
	node *ptr = (node *)malloc(sizeof(node));
	ptr->id = TK_DOLLAR;
	ptr->child_size = -1;
	ptr->value = NULL;
	
	
	Root = (node *)malloc(sizeof(node));
	Root->id = program;	
	Root->child_size = -1;
	Root->parentId = 666;
	Root->value = NULL;
	
	node* stack[100];
	stack[0] = ptr;
	stack[1] = Root;
	int stackPointer = 1;
	

	
	while(1){
		
		if(stack[stackPointer]->id==input[index].t.id){
			if(stackPointer==0){
				if(MODE==2){
					printf("PARSING COMPLETED SUCCESSFULLY\n");
				}
				/*if(MODE==4){
					printf("PARSE TABLE PRINTED SUCCESSFULLY IN THE OUTPUT FILE\n");
				}*/
				
				return;
			}
			stack[stackPointer]->line_no = input[index].line_no;
			stack[stackPointer]->value = input[index].val;
			stackPointer--;
			index++;

		}
		else{
			if(stack[stackPointer]->id<100){
				printErrorMsg(stack[stackPointer]->id,input[index].t.id,input[index].val,input[index].line_no,1);
				return;
			}
			
			int nonTer = stack[stackPointer]->id;
			node *nt_ptr = stack[stackPointer];
			int ter = input[index].t.id;
			int prod = nonTerminalsArray[nonTer%100].table[ter];
			nt_ptr->prodRule = prod;
			if(prod==-1){
				input[index];
				printErrorMsg(stack[stackPointer]->id,input[index].t.id,input[index].val,input[index].line_no,2);
				return;
			}
			
			int pos = 0;
			for(pos = 0;pos<15;pos++){
				if(prodRulesArray[prod%200].righthand[pos]==-1){
					break;
				}
				node *p = (node *)malloc(sizeof(node));
				p->id = prodRulesArray[prod%200].righthand[pos];
				p->value = NULL;
				p->line_no = -1;
				p->parentId = nonTer;
				p->child_size = -1;
				nt_ptr->children[pos]=p;
				nt_ptr->child_size = pos;
				parse_num =parse_num+1;

			}
			pos--;
			stackPointer--;
			while(pos>=0){
				stackPointer++;
				stack[stackPointer] = nt_ptr->children[pos];				
				pos--;
			}
		}
		
	}
}

//this function populates the parse table with the use of automated firsts and follows

void createParseTable(){
    
	int i;
	
	//for populating firsts
	for(i=0;i<nonTerminalsArraySize;i++){
		findFirsts(i+100);
	}
	//for populating follows
	for(i=0;i<nonTerminalsArraySize;i++){
		findFollows(i+100);
	}
	
	//for populating parse table
	for(i=0;i<prodRulesArraySize;i++){
		firstof(200+i,0);
	}
	
}

//this function prints the  parse tree generated in the output file.

/*void printParseTree(node *ptr,FILE*fp){
	fprintf(fp,"\n");
	int print_len;
	//print lexeme current node
	if(ptr->id>=100){
		print_len = fprintf(fp,"---- ");
	}else{
		if(ptr->value != NULL){
			print_len = fprintf(fp,"%s ",ptr->value);
		}else{
			print_len = fprintf(fp,"%s ",token_array[ptr->id].keyword);
		}
	}
	
	while(print_len<=35){
		fprintf(fp," ");
		print_len++;
	}
	//print line no
	print_len = print_len + fprintf(fp,"%d ",ptr->line_no);
	
	while(print_len<=40){
		fprintf(fp," ");
		print_len++;
	}
	
	//print token name
	
	print_len = print_len + print(ptr->id,fp);
	
	while(print_len<=60){
		fprintf(fp," ");
		print_len++;
	}
	
	//print value if num
	
	if(ptr->id == 49||ptr->id == 50){
		print_len+=fprintf(fp,"%s ",ptr->value);
	} else{
		print_len+=fprintf(fp,"---- ");
	}
	
		while(print_len<=75){
		fprintf(fp," ");
		print_len++;
	}
	
	//print parent
	if(ptr->parentId==666){
		print_len+=fprintf(fp,"root ");
	}else{
		print_len+=print(ptr->parentId,fp);
	}
	
	while(print_len<=95){
		fprintf(fp," ");
		print_len++;
	}
	
	//print is leaf node
	if(ptr->id>=100){
		print_len+=fprintf(fp,"no ");
	}else{
		print_len+=fprintf(fp,"yes ");
	}
	while(print_len<=100){
		fprintf(fp," ");
		print_len++;
	}
	
	//node symbol
	print_len+=print(ptr->id,fp);
	
	
	//write remaining print statements
	int len = (ptr->child_size)+1;
	int i;
	for(i=0;i<len;i++){
		printParseTree(ptr->children[i],fp);
	}
}
*/

void printParseTreeConsole(node *ptr){
	
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
	int len = (ptr->child_size)+1;
	int i;
	for(i=0;i<len;i++){
		printParseTreeConsole(ptr->children[i]);
	}
}




