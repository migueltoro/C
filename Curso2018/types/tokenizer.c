/*
 * tokenizer.c
 *
 *  Created on: 10 nov. 2019
 *      Author: migueltoro
 */

#include "tokenizer.h"



bool is_alphabetic_char(char c){
	return ((c>='a' && c <='z') || (c>='A' && c<='Z'));
}

bool is_digit_char(char c){
	return c>='0' && c <='9';
}

bool is_space_char(char c){
	return strchr(" \t\n\b",c) != NULL;
}

bool is_separator_char(char c){
	return strchr("(){},;[]",c) != NULL;
}

bool is_operator_char(char c){
	return strchr("+-*%/=",c) != NULL;
}

bool is_symbol_char(char c){
	return strchr("$&@",c) != NULL;
}

char * skip_spaces(tokenizer * tk){
	int i = 0;
	char * s = tk->text+tk->current_position;
	while(is_space_char(s[i])){
			if(s[i] == '\0') break;
			i++;
	}
	tk->current_position += i;
	return s+i;
}

char * get_identifier(int * n, tokenizer * tk){
	int i = 0;
	char * r = skip_spaces(tk);
	while(is_alphabetic_char(r[i]) || is_digit_char(r[i]) || r[i] == '_'){
		i++;
	}
	*n = i;
	tk->current_position += i;
	return r;
}

char * get_integer(int * n, tokenizer * tk){
	char * s = tk->text+tk->current_position;
	s = skip_spaces(tk);
	int i = 0;
	char * r = s;
	while(is_digit_char(s[i])){
		i++;
	}
	*n=i;
	tk->current_position += i;
	return r;
}

token token_of(char * text,char * text_token, token_class type, int start_position, int end_position){
	token t = {text,"",type,start_position,end_position};
	copy(t.text_token,text_token,end_position-start_position);
	return t;
}

char * copy_n(char * out, char * in, int n){
	for(int i = 0; i<n; i++){
		*(out+i) = *(in +i);
	}
	out[n] = '\0';
	return out;
}

char * tipos[] = {"Integer","Double","Identifier","FunctionIdentifier","ReservedWord","Operator","Separator","Symbol","End"};

char * token_tostring(token * t,char * mem){
	sprintf(mem,"(%s;%s;%d;%d)",tipos[t->type],
			t->text_token,
			t->start_position,t->end_position);
	return mem;
}

char * token_text(token * t){
	return t->text_token;
}

int token_length(token * t){
	return t->end_position - t->start_position;
}

int token_position(token * t){
	return t->start_position;
}

token_class token_cls(token * t){
	return t->type;
}


type token_type = {NULL,token_tostring,NULL,NULL,sizeof(token)};

tokenizer tokenizer_of(char * text){
	int n = strlen(text);
	tokenizer t = {text,0,n};
	return t;
}

token current_token(tokens * tk){
	token t;
	t = *(token *) list_get(&tk->ls,tk->current_token-1);
	return t;
}

bool has_more_tokens(tokens * tk){
	return tk->current_token < tk->n_tokens;
}

token next_token(tokens * tk){
	token t;
	t = *(token *) list_get(&tk->ls,tk->current_token);
	tk->current_token +=1;
	return t;
}

token match_token_types(token_class * types, int ntypes, tokens * tk){
	token t = next_token(tk);
	bool r = false;
	int i =0;
	while(i<ntypes && !r){
		r = types[i] == t.type;
		i++;
	}
	if(!r) error_token(&t);
	return t;
}

token match_token_texts(char * labels, int max_tam_label, int nlabels, tokens * tk){
	token t = next_token(tk);
	char * label = t.text_token;
	bool r = false;
	int i =0;
	while(i<nlabels && !r){
		r = strcmp(labels+i*max_tam_label,label) == 0;
		i++;
	}
	if(!r) error_token(&t);
	return t;
}

token see_next_token(tokens * tk){
	token t;
	t = *(token *) list_get(&tk->ls,tk->current_token);
	return t;
}

void error_token(token * t){
	char mem[Tam_String];
	sprintf(mem,"Error en token %s \nPosición %d Sufijo %s en cadena == %s",
					tipos[t->type], t->start_position,t->text+t->start_position, t->text);
	check_argument(false,__FILE__,__LINE__,mem);
}

token next_tk(tokenizer * tk);

tokens get_tokens(char * text){
	list ls = list_empty(token_type);
	tokenizer tk = tokenizer_of(text);
	while(tk.current_position < tk.end_position){
		token t = next_tk(&tk);
		list_add(&ls,&t);
	}
	tokens tks = {ls,0,list_size(&ls)};
	return tks;
}

token next_tk(tokenizer * tk) {
	token t;
	int token_length = 1;
	skip_spaces(tk);
	char c = tk->text[tk->current_position];
	if (is_digit_char(c)) {
		char * st1 = get_integer(&token_length,tk);
		t = token_of(tk->text,st1,Integer,tk->current_position-token_length,tk->current_position);
		int old_len = token_length;
		c = tk->text[tk->current_position];
		if (c == '.') {
			tk->current_position +=1;
			get_integer(&token_length,tk);
			token_length += 1+old_len;
			t = token_of(tk->text,st1,Double,tk->current_position-token_length,tk->current_position);
		}
	} else if (is_alphabetic_char(c) || c == '_') {
		char * st = get_identifier(&token_length,tk);
		t = token_of(tk->text,st,Identifier,tk->current_position-token_length,tk->current_position);
	} else if (is_operator_char(c)) {
		t = token_of(tk->text,tk->text+tk->current_position, Operator,tk->current_position,tk->current_position+1);
		tk->current_position +=1;
	} else if (is_separator_char(c)) {
		t = token_of(tk->text,tk->text+tk->current_position,Separator,tk->current_position,tk->current_position+1);
		tk->current_position +=1;
	} else if (is_symbol_char(c)) {
		t = token_of(tk->text,tk->text+tk->current_position,Symbol,tk->current_position,tk->current_position+1);
		tk->current_position +=1;
	} else if(c == '\0'){
		t = token_of(tk->text,tk->text+tk->current_position,End,tk->current_position,tk->current_position+1);
		tk->current_position +=1;
	} else {
		char m[Tam_String];
		sprintf(m,"caracter %c no reconocido",c);
		check_argument(false,__FILE__,__LINE__,m);
	}
	skip_spaces(tk);
	return t;
}

void test_token() {
	char str[] = " finding digits where there could be digit 5236.45 is amazing finding 5236 ( ,      ";
//	char str[] = "  5236.45  ";
	char mem[Tam_String];
	tokenizer tk = tokenizer_of(str);
	token t;
	while(tk.current_position < tk.end_position) {
		t = next_tk(&tk);
		printf("%s\n",token_tostring(&t,mem));
	}
}



void test_tokenizer(){
	char str[] = "finding digits where there could be digit 5236.45 is amazing ) ;*";
	tokens tk = get_tokens(str);
	char mem[1000];
	char * r = list_tostring(&tk.ls,mem);
	printf("%s\n",r);
//
}


