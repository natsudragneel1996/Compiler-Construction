/*
BATCH NUMBER ---------> 19
C.RAGHU VAMSI KRISHNA   2013A7PS031P
L.SATYA PAVAN           2013A7PS150P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexerDef.h"

#define TK_FIELDID 47
#define TK_ID 48
#define TK_NUM 49
#define TK_RNUM 50
#define TK_FUNID 51
#define TK_RECORDID 52
#define TK_DOLLAR 53
#define TK_EOL 54


// prints  tokenid of a particular terminal in  output file
/*int print_terminal(int id,FILE *fp){
	return fprintf(fp,"%s ",token_array[id].tokenid);
}*/
int print_terminalConsole(int id){
	return printf("%s ",token_array[id].tokenid);
}

//checks whether given character is in between 'b' to 'd'
int is_bd(char c){
    if(c>=98&&c<=100)
        return 1;
    else
        return 0;
}

//checks whether given character is not  in between 'b' to 'd'
int is_notbd(char c){
    if(islower((int)c))
    {
        if(c>=98&&c<=100)
            return 0;
        else
            return 1;
    }
    else
    {
        return 0;
    }
}


//checks whether given character is in between '2' to '7'
int is_27(char c){
    if(c>=50&&c<=55)
        return 1;
    else
        return 0;
}

// this function populates the token_array(array of token data structure)with keywords and standard patterns.
void initiate_tokenArray(){
	token_arraySize = 55;

	token_array = (token *)malloc(sizeof(token)*token_arraySize);

	token_array[0].keylen = 4;
	
	strcpy(token_array[0].keyword,"with");
	strcpy(token_array[0].tokenid,"TK_WITH");
	strcpy(token_array[0].postkey,"");
	token_array[0].postlen = 0;
	token_array[0].id =0;

	token_array[1].keylen = 4;
	strcpy(token_array[1].keyword,"<---");
	strcpy(token_array[1].tokenid,"TK_ASSIGNOP");
	strcpy(token_array[1].postkey,"");
	token_array[1].postlen = 0;
	token_array[1].id =1;

	token_array[2].keylen = 1;
	strcpy(token_array[2].keyword,"<");
	strcpy(token_array[2].tokenid,"TK_LT");
	strcpy(token_array[2].postkey,"=-");
	token_array[2].postlen = 2;
	token_array[2].id =2;
	
	token_array[3].keylen = 2;
	strcpy(token_array[3].keyword,"<=");
	strcpy(token_array[3].tokenid,"TK_LE");
	strcpy(token_array[3].postkey,"");
	token_array[3].postlen = 0;
	token_array[3].id =3;

	token_array[4].keylen = 3;
	strcpy(token_array[4].keyword,"end");
	strcpy(token_array[4].tokenid,"TK_END");
	strcpy(token_array[4].postkey,"wir");
	token_array[4].postlen = 3;
	token_array[4].id =4;

	token_array[5].keylen = 5;
	strcpy(token_array[5].keyword,"endif");
	strcpy(token_array[5].tokenid,"TK_ENDIF");
	strcpy(token_array[5].postkey,"");
	token_array[5].postlen = 0;
	token_array[5].id =5;
	
	token_array[6].keylen = 8;
	strcpy(token_array[6].keyword,"endwhile");
	strcpy(token_array[6].tokenid,"TK_ENDWHILE");
	strcpy(token_array[6].postkey,"");
	token_array[6].postlen = 0;
	token_array[6].id =6;
	
	token_array[7].keylen = 9;
	strcpy(token_array[7].keyword,"endrecord");
	strcpy(token_array[7].tokenid,"TK_ENDRECORD");
	strcpy(token_array[7].postkey,"");
	token_array[7].postlen = 0;
	token_array[7].id =7;
	

	token_array[8].keylen = 1;
	strcpy(token_array[8].keyword,"%");
	strcpy(token_array[8].tokenid,"TK_COMMENT");
	strcpy(token_array[8].postkey,"");
	token_array[8].postlen = 0;
	token_array[8].id =8;
	

	token_array[9].keylen = 10;
	strcpy(token_array[9].keyword,"parameters");
	strcpy(token_array[9].tokenid,"TK_PARAMETERS");
	strcpy(token_array[9].postkey,"");
	token_array[9].postlen = 0;
	token_array[9].id =9;
	
	token_array[10].keylen = 5;
	strcpy(token_array[10].keyword,"while");
	strcpy(token_array[10].tokenid,"TK_WHILE");
	strcpy(token_array[10].postkey,"");
	token_array[10].postlen = 0;
	token_array[10].id =10;
	
	token_array[11].keylen = 3;
	strcpy(token_array[11].keyword,"int");
	strcpy(token_array[11].tokenid,"TK_INT");
	strcpy(token_array[11].postkey,"");
	token_array[11].postlen = 0;
	token_array[11].id =11;

	token_array[12].keylen = 4;
	strcpy(token_array[12].keyword,"real");
	strcpy(token_array[12].tokenid,"TK_REAL");
	strcpy(token_array[12].postkey,"");
	token_array[12].postlen = 0;
	token_array[12].id =12;

	token_array[13].keylen = 4;
	strcpy(token_array[13].keyword,"type");
	strcpy(token_array[13].tokenid,"TK_TYPE");
	strcpy(token_array[13].postkey,"");
	token_array[13].postlen = 0;
	token_array[13].id =13;

	token_array[14].keylen = 5;
	strcpy(token_array[14].keyword,"_main");
	strcpy(token_array[14].tokenid,"TK_MAIN");
	strcpy(token_array[14].postkey,"");
	token_array[14].postlen = 0;
	token_array[14].id =14;


	token_array[15].keylen = 6;
	strcpy(token_array[15].keyword,"global");
	strcpy(token_array[15].tokenid,"TK_GLOBAL");
	strcpy(token_array[15].postkey,"");
	token_array[15].postlen = 0;
	token_array[15].id =15;

	token_array[16].keylen = 9;
	strcpy(token_array[16].keyword,"parameter");
	strcpy(token_array[16].tokenid,"TK_PARAMETER");
	strcpy(token_array[16].postkey,"s");
	token_array[16].postlen = 1;
	token_array[16].id =16;

	token_array[17].keylen = 4;
	strcpy(token_array[17].keyword,"list");
	strcpy(token_array[17].tokenid,"TK_LIST");
	strcpy(token_array[17].postkey,"");
	token_array[17].postlen = 0;
	token_array[17].id =17;

	token_array[18].keylen = 1;
	strcpy(token_array[18].keyword,"[");
	strcpy(token_array[18].tokenid,"TK_SQL");
	strcpy(token_array[18].postkey,"");
	token_array[18].postlen = 0;
	token_array[18].id =18;

	token_array[19].keylen = 1;
	strcpy(token_array[19].keyword,"]");
	strcpy(token_array[19].tokenid,"TK_SQR");
	strcpy(token_array[19].postkey,"");
	token_array[19].postlen = 0;
	token_array[19].id =19;

	token_array[20].keylen = 5;
	strcpy(token_array[20].keyword,"input");
	strcpy(token_array[20].tokenid,"TK_INPUT");
	strcpy(token_array[20].postkey,"");
	token_array[20].postlen = 0;
	token_array[20].id =20;

	token_array[21].keylen = 6;
	strcpy(token_array[21].keyword,"output");
	strcpy(token_array[21].tokenid,"TK_OUTPUT");
	strcpy(token_array[21].postkey,"");
	token_array[21].postlen = 0;
	token_array[21].id =21;

    token_array[22].keylen = 1;
	strcpy(token_array[22].keyword,";");
	strcpy(token_array[22].tokenid,"TK_SEM");
	strcpy(token_array[22].postkey,"");
	token_array[22].postlen = 0;
	token_array[22].id =22;


	token_array[23].keylen = 1;
	strcpy(token_array[23].keyword,":");
	strcpy(token_array[23].tokenid,"TK_COLON");
	strcpy(token_array[23].postkey,"");
	token_array[23].postlen = 0;
	token_array[23].id =23;

	token_array[24].keylen = 1;
	strcpy(token_array[24].keyword,".");
	strcpy(token_array[24].tokenid,"TK_DOT");
	strcpy(token_array[24].postkey,"");
	token_array[24].postlen = 0;
	token_array[24].id =24;

	token_array[25].keylen = 1;
	strcpy(token_array[25].keyword,"(");
	strcpy(token_array[25].tokenid,"TK_OP");
	strcpy(token_array[25].postkey,"");
	token_array[25].postlen = 0;
	token_array[25].id =25;


	token_array[26].keylen = 1;
	strcpy(token_array[26].keyword,")");
	strcpy(token_array[26].tokenid,"TK_CL");
	strcpy(token_array[26].postkey,"");
	token_array[26].postlen = 0;
	token_array[26].id =26;

    token_array[27].keylen = 2;
	strcpy(token_array[27].keyword,"if");
	strcpy(token_array[27].tokenid,"TK_IF");
	strcpy(token_array[27].postkey,"");
	token_array[27].postlen = 0;
	token_array[27].id =27;

    token_array[28].keylen = 4;
	strcpy(token_array[28].keyword,"then");
	strcpy(token_array[28].tokenid,"TK_THEN");
	strcpy(token_array[28].postkey,"");
	token_array[28].postlen = 0;
	token_array[28].id =28;

	token_array[29].keylen = 4;
	strcpy(token_array[29].keyword,"read");
	strcpy(token_array[29].tokenid,"TK_READ");
	strcpy(token_array[29].postkey,"");
	token_array[29].postlen = 0;
	token_array[29].id =29;

    token_array[30].keylen = 5;
	strcpy(token_array[30].keyword,"write");
	strcpy(token_array[30].tokenid,"TK_WRITE");
	strcpy(token_array[30].postkey,"");
	token_array[30].postlen = 0;
	token_array[30].id =30;

    token_array[31].keylen = 6;
	strcpy(token_array[31].keyword,"return");
	strcpy(token_array[31].tokenid,"TK_RETURN");
	strcpy(token_array[31].postkey,"");
	token_array[31].postlen = 0;
	token_array[31].id =31;

    token_array[32].keylen = 1;
	strcpy(token_array[32].keyword,"+");
	strcpy(token_array[32].tokenid,"TK_PLUS");
	strcpy(token_array[32].postkey,"");
	token_array[32].postlen = 0;
	token_array[32].id =32;


	token_array[33].keylen = 1;
	strcpy(token_array[33].keyword,"-");
	strcpy(token_array[33].tokenid,"TK_MINUS");
	strcpy(token_array[33].postkey,"");
	token_array[33].postlen = 0;
	token_array[33].id =33;

	token_array[34].keylen = 1;
	strcpy(token_array[34].keyword,"*");
	strcpy(token_array[34].tokenid,"TK_MUL");
	strcpy(token_array[34].postkey,"");
	token_array[34].postlen = 0;
	token_array[34].id =34;

	token_array[35].keylen = 1;
	strcpy(token_array[35].keyword,"/");
	strcpy(token_array[35].tokenid,"TK_DIV");
	strcpy(token_array[35].postkey,"");
	token_array[35].postlen = 0;
	token_array[35].id =35;

	token_array[36].keylen = 4;
	strcpy(token_array[36].keyword,"call");
	strcpy(token_array[36].tokenid,"TK_CALL");
	strcpy(token_array[36].postkey,"");
	token_array[36].postlen = 0;
	token_array[36].id =36;

	token_array[37].keylen = 6;
	strcpy(token_array[37].keyword,"record");
	strcpy(token_array[37].tokenid,"TK_RECORD");
	strcpy(token_array[37].postkey,"");
	token_array[37].postlen = 0;
	token_array[37].id =37;

	token_array[38].keylen = 4;
	strcpy(token_array[38].keyword,"else");
	strcpy(token_array[38].tokenid,"TK_ELSE");
	strcpy(token_array[38].postkey,"");
	token_array[38].postlen = 0;
	token_array[38].id =38;

	token_array[39].keylen = 3;
	strcpy(token_array[39].keyword,"&&&");
	strcpy(token_array[39].tokenid,"TK_AND");
	strcpy(token_array[39].postkey,"");
	token_array[39].postlen = 0;
	token_array[39].id =39;

	token_array[40].keylen = 3;
	strcpy(token_array[40].keyword,"@@@");
	strcpy(token_array[40].tokenid,"TK_OR");
	strcpy(token_array[40].postkey,"");
	token_array[40].postlen = 0;
	token_array[40].id =40;

	token_array[41].keylen = 1;
	strcpy(token_array[41].keyword,"~");
	strcpy(token_array[41].tokenid,"TK_NOT");
	strcpy(token_array[41].postkey,"");
	token_array[41].postlen = 0;
	token_array[41].id =41;

	token_array[42].keylen = 2;
	strcpy(token_array[42].keyword,"==");
	strcpy(token_array[42].tokenid,"TK_EQ");
	strcpy(token_array[42].postkey,"");
	token_array[42].postlen = 0;
	token_array[42].id =42;

	token_array[43].keylen = 1;
	strcpy(token_array[43].keyword,">");
	strcpy(token_array[43].tokenid,"TK_GT");
	strcpy(token_array[43].postkey,"=");
	token_array[43].postlen = 1;
	token_array[43].id =43;

	token_array[44].keylen = 2;
	strcpy(token_array[44].keyword,">=");
	strcpy(token_array[44].tokenid,"TK_GE");
	strcpy(token_array[44].postkey,"");
	token_array[44].postlen = 0;
	token_array[44].id =44;

    token_array[45].keylen = 1;
	strcpy(token_array[45].keyword,"!=");
	strcpy(token_array[45].tokenid,"TK_NE");
	strcpy(token_array[45].postkey,"");
	token_array[45].postlen = 0;
	token_array[45].id =45;

	token_array[46].keylen = 1;
	strcpy(token_array[46].keyword,",");
	strcpy(token_array[46].tokenid,"TK_COMMA");
	strcpy(token_array[46].postkey,"");
	token_array[46].postlen = 0;
	token_array[46].id =46;

	array_size = 47;
	
	strcpy(token_array[47].tokenid,"TK_FIELDID");
	token_array[47].id =47;
	
	strcpy(token_array[48].tokenid,"TK_ID");
	token_array[48].id =48;
	
	strcpy(token_array[49].tokenid,"TK_NUM");
	token_array[49].id =49;
	
	strcpy(token_array[50].tokenid,"TK_RNUM");
	token_array[50].id =50;
	
	strcpy(token_array[51].tokenid,"TK_FUNID");
	token_array[51].id =51;
	
	strcpy(token_array[52].tokenid,"TK_RECORDID");
	token_array[52].id =52;
	
	strcpy(token_array[53].tokenid,"$");
	token_array[53].id =53;
	
	strcpy(token_array[54].tokenid,"EOL");
	token_array[54].id =54;
}

//this function checks given character with all tokens in input array at given position and those  that matched are given in output array 
int checkToken(token* input,token* output,char c,int position){
	
	int i;
	int j=0;
	
	for(i=0;i<array_size;i++){

		if(position==input[i].keylen){
			
			int k = input[i].postlen;
			int l;
			for(l=0;l<k;l++){
				if(c==input[i].postkey[l]){
					break;
				}
			}
			if(l==k){
				output[j] = input[i];
				return j;
			}
			else{
				
				continue;
			}
		}
		
		if(c == input[i].keyword[position]){
			
			output[j] = input[i];
			j++ ;
		}
	}
	array_size=j;
	
	return -1;
}


//this  function prints the error msg ERROR_3 if there is unknown symbol detected.
void error_msg3(int start_index,int endIndex,char*str,int line){
	int len = endIndex - start_index +1;
	char *eArr = (char *)malloc(sizeof(char)*len+1);
	int x =0;
	
	for(x=0;x<len;x++){
		eArr[x] = str[start_index];
		start_index++;
	}
	eArr[x]='\0';
				
	printf("ERROR_3:Unknown pattern <%s> at line %d \n",eArr,line);
	lexical_err=1;


  }


//this function takes the input as string and divide it  into tokens  returns a tokenInfo array .
tokenInfo* getTokens(char *str,int line){
	
	int output_len =0;
	tokenInfo* outputArray = (tokenInfo*)malloc(sizeof(tokenInfo)*100);
	int index=0;
	int id_len=0;
	token* intmdt_array = malloc(sizeof(token)*47);
	startOver:while(1){
		int check_len = output_len;
		int start_index=index;
		
		if(str[index]=='\0'){
			
			//if(MODE ==1){
				//printf("\n");
			//}
			break;
		}
		
		/*if(MODE == 1){
			printf("%c",str[index]);
			index++;
			continue;
		}*/
		
	
	    if(str[index]==' '||str[index]=='	'){
            	index++;
            	continue;
        }
        array_size=47;
		int result;
		id_len =0;
		
		result = checkToken(token_array,intmdt_array,str[index],id_len);
		
		if(result>=0){
			
			outputArray[output_len].line_no = line;
			outputArray[output_len].t = token_array[intmdt_array[result].id];
			outputArray[output_len].val = NULL;
			output_len++;
			goto startOver;
		}

		

		if(str[index]=='#'){
			index++;
			id_len++;

			result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
			if(result>=0){
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[intmdt_array[result].id];
				outputArray[output_len].val = NULL;
				output_len++;
				goto startOver;
			}


			if(islower((int)str[index])){
				index++;
				id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				if(result>=0){
					
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}

				while(islower((int)str[index])){
					index++;
					id_len++;

					result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
					if(result>=0){
						
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[intmdt_array[result].id];
						outputArray[output_len].val = NULL;
						output_len++;
						goto startOver;
					}
				}


				
				int endIndex = index-1;
				int len = endIndex - start_index +1;
				char *recArr = (char *)malloc(sizeof(char)*len+1);
				int x =0;
				
				if(len>20){
				printf("ERROR_1 : Recordid ID at line %d  is longer than the prescribed length of 20 characters\n",line);
				lexical_err = 1;
				outputArray[output_len].err_status = 1;
				}
				for(x=0;x<len;x++){
					recArr[x] = str[start_index];
					start_index++;
				}
				recArr[x]='\0';
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[TK_RECORDID];
				outputArray[output_len].val = recArr;
				output_len++;
				
			}

			if(output_len==check_len)
			{error_msg3(start_index,index-1,str,line);}
			continue;
		}

		if(str[index]=='_'){
			index++;
			id_len++;
			
			result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
		
			if(result>=0){
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[intmdt_array[result].id];
				outputArray[output_len].val = NULL;
				output_len++;
				
				goto startOver;
			}

			if(isalpha((int)str[index])){
				index++;
				id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				
				if(result>=0){
					
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}

				while(isalpha((int)str[index])){
					index++;
					id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				
				if(result>=0){
					
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}

				}

				while(isdigit((int)str[index])){
					index++;
					id_len++;

					result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
					
					if(result>=0){
						
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[intmdt_array[result].id];
						outputArray[output_len].val = NULL;
						output_len++;
						goto startOver;
					}
				}

				
				
				int endIndex = index-1;
				
				int len = endIndex - start_index +1;
				
				char *funArr = (char *)malloc(sizeof(char)*len+1);
                                
				if(len>30){
				printf("ERROR_1 : Function Id at line %d is longer than the prescribed length of 30 characters\n",line);
				lexical_err = 1;
				outputArray[output_len].err_status = 1;
				}
				int x =0;
				
				for(x=0;x<len;x++){
					funArr[x] = str[start_index];
					start_index++;
				}
				
				funArr[x]='\0';
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[TK_FUNID];
				outputArray[output_len].val = funArr;
				output_len++;
				

			}
		
			if(output_len==check_len)
			{error_msg3(start_index,index-1,str,line);}

			continue;
		}

		if(isdigit((int)str[index])){
			index++;
			id_len++;

			result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
			if(result>=0){
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[intmdt_array[result].id];
				outputArray[output_len].val = NULL;
				output_len++;
				goto startOver;
			}

			while(isdigit((int)str[index])){
				index++;
				id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				if(result>=0){
					
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}
			}

			if(str[index]=='.'){
				index++;
				id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				if(result>=0){
					
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}

				if(isdigit((int)str[index])){
					index++;
					id_len++;

					result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
					if(result>=0){
						
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[intmdt_array[result].id];
						outputArray[output_len].val = NULL;
						output_len++;
						goto startOver;
					}

					if(isdigit((int)str[index])){
						index++;
						id_len++;

						result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
						if(result>=0){
							
							outputArray[output_len].line_no = line;
							outputArray[output_len].t = token_array[intmdt_array[result].id];
							outputArray[output_len].val = NULL;
							output_len++;
							goto startOver;
						}

					

						int endIndex = index-1;
						int len = endIndex - start_index +1;
						char *numArr = (char *)malloc(sizeof(char)*len+1);
						int x =0;
						
						for(x=0;x<len;x++){
							numArr[x] = str[start_index];
							start_index++;
						}
						numArr[x]='\0';
						
						
						
												
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[TK_RNUM];
						outputArray[output_len].val = numArr;
						output_len++;
						
					}
					

				}
				
			}
			else{
				
				int endIndex = index-1;
				int len = endIndex - start_index +1;
				char *numArr = (char *)malloc(sizeof(char)*len+1);
				int x =0;
				
				for(x=0;x<len;x++){
					numArr[x] = str[start_index];
					start_index++;
				}
				numArr[x]='\0';
				

				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[TK_NUM];
				outputArray[output_len].val = numArr;
				output_len++;
			}
		if(output_len==check_len)
			{error_msg3(start_index,index-1,str,line);}
           continue;
		}

		if(is_bd(str[index])){
			index++;
			id_len++;

			result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
			if(result>=0){
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[intmdt_array[result].id];
				outputArray[output_len].val = NULL;
				output_len++;
				goto startOver;
			}

			if(is_27(str[index])){
				index++;
				id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				if(result>=0){
				 
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}

				while(is_bd(str[index])){
					index++;
					id_len++;

					result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
					if(result>=0){
						
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[intmdt_array[result].id];
						outputArray[output_len].val = NULL;
						output_len++;
						goto startOver;
					}

				}

				while(is_27(str[index])){
					index++;
					id_len++;

					result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
					if(result>=0){
						
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[intmdt_array[result].id];
						outputArray[output_len].val = NULL;
						output_len++;
						goto startOver;
					}

				}
				
				int endIndex = index-1;
				int len = endIndex - start_index +1;
				char *idArr = (char *)malloc(sizeof(char)*len+1);
				int x =0;
				
				if(len>20){
				printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",line);
				lexical_err=1;
				outputArray[output_len].err_status = 1;
				}
				for(x=0;x<len;x++){
					idArr[x] = str[start_index];
					start_index++;
				}
				idArr[x]='\0';
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[TK_ID];
				outputArray[output_len].val = idArr;
				output_len++;
				
			}
			else{

				while(islower((int)str[index])){
					index++;
					id_len++;

					result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
					if(result>=0){
						
						outputArray[output_len].line_no = line;
						outputArray[output_len].t = token_array[intmdt_array[result].id];
						outputArray[output_len].val = NULL;
						output_len++;
						goto startOver;
					}
				}
				
				int endIndex = index-1;
				int len = endIndex - start_index +1;
				char *fldArr = (char *)malloc(sizeof(char)*len+1);
				int x =0;
				
				if(len>20){
				printf("ERROR_1 : Field Id at line %d is longer than the prescribed length of 20 characters\n",line);
				lexical_err=1;
				outputArray[output_len].err_status = 1;
				}
				for(x=0;x<len;x++){
					fldArr[x] = str[start_index];
					start_index++;
				}
				fldArr[x]='\0';
				

				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[TK_FIELDID];
				outputArray[output_len].val = fldArr;
				output_len++;
				

			}
		if(output_len==check_len)
			{error_msg3(start_index,index-1,str,line);}

               continue;
		}

		if(is_notbd((int)str[index])){
			index++;
			id_len++;
			result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
			if(result>=0){
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[intmdt_array[result].id];
				outputArray[output_len].val = NULL;
				output_len++;
				goto startOver;
			}

			while(islower((int)str[index])){
				index++;
				id_len++;

				result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
				if(result>=0){
					
					outputArray[output_len].line_no = line;
					outputArray[output_len].t = token_array[intmdt_array[result].id];
					outputArray[output_len].val = NULL;
					output_len++;
					goto startOver;
				}
			}

			
			
			int endIndex = index-1;
			int len = endIndex - start_index +1;
			char *fldArr = (char *)malloc(sizeof(char)*len+1);
			int x =0;
			
			if(len>20){
				printf("ERROR_1 :Field Id at line %d is longer than the prescribed length of 20 characters\n",line);
				lexical_err = 1;
				outputArray[output_len].err_status = 1;
				}
			for(x=0;x<len;x++){
				fldArr[x] = str[start_index];
				start_index++;
			}
			fldArr[x]='\0';
			
			
			outputArray[output_len].line_no = line;
			outputArray[output_len].t = token_array[TK_FIELDID];
			outputArray[output_len].val = fldArr;
			output_len++;
			
				
			continue;

		}

		while(array_size>0){
			index++;

			
			id_len++;

			result = checkToken(intmdt_array,intmdt_array,str[index],id_len);
			if(result>=0){
				
				outputArray[output_len].line_no = line;
				outputArray[output_len].t = token_array[intmdt_array[result].id];
				outputArray[output_len].val = NULL;
				output_len++;
				goto startOver;
			}
		}
		if(start_index==index){
		printf("ERROR_2: Unknown Symbol   %c at line  %d \n",str[index],line);
		lexical_err=1;
		index++;
		}else{
			if(output_len==check_len)
			{error_msg3(start_index,index-1,str,line);}
		}
		

		
		
	}
	if(status ==0){
		outputArray[output_len].line_no = line;
		outputArray[output_len].t = token_array[TK_EOL];
		outputArray[output_len].val = NULL;
	}else{
		outputArray[output_len].line_no = line;
		outputArray[output_len].t = token_array[TK_DOLLAR];
		outputArray[output_len].val = NULL;
	}
	
	return outputArray;
}



//this function takes file pointer as input and takes a line from the file and stores it in a character array.
FILE* getStream(FILE *fp,char *str,int buffersize){
	char c;
	int i=0;
	c = fgetc(fp);
	while(1){
		if(c==EOF){
			status =1;
			break;
		}
		if(c!='\n'){
			if(c=='%'||c=='\r'){
				str[i] = '\0';
			}else{
				str[i] = c;
			}			
			i++;
			c= fgetc(fp);
		}
		else{
			break;
		}
	}
	
	str[i] = '\0';
	return fp;
}


//this function gets tokenInfo for all the lines and store them in a result array
void findTokens(FILE* fp,int line,tokenInfo* result,int index){
	char* str = (char *)malloc(sizeof(char)*300);
	FILE *f = getStream(fp,str,300);
	tokenInfo* ptr = getTokens(str,line);
	int i =0;
	while(1){
		if(ptr[i].t.id == TK_EOL){
			
			findTokens(fp,line+1,result,index);
			return;
		}
		if(ptr[i].t.id == TK_DOLLAR){
			
			result[index] = ptr[i];
			return;
		}
	
		
		result[index] = ptr[i];
		index++;
		
		
		i++;
	}
}
