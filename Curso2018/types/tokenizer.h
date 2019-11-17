/*
 * tokenizer.h
 *
 *  Created on: 10 nov. 2019
 *      Author: migueltoro
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "types.h"
#include "list.h"

typedef enum {Integer,Double,Identifier,FunctionIdentifier,ReservedWord,Operator,Separator,Symbol,End}
	token_class;

#define max_len_token 20

typedef struct {
	char * text;
	char text_token[max_len_token];
	token_class type;
	int start_position;
	int end_position;
}token;

typedef struct {
	char * text;
	int current_position;
	int end_position;
}tokenizer;

typedef struct {
	list ls;
	int current_token;
	int n_tokens;
}tokens;

token token_of(char * text, char * text_token, token_class type, int start_position, int end_position);
char * token_tostring(token * t, char * mem);
char * token_text(token * t);
int token_length(token * t);
int token_position(token * t);
token_class token_cls(token * t);

extern type token_type;

tokenizer tokenizer_of(char * text);
token current_token(tokens * tk);
bool has_more_tokens(tokens * tk);
token next_token(tokens * tk);
token match_token_types(token_class * types, int ntypes, tokens * tk);
token match_token_texts(char * labels, int max_tam_label, int nlabels, tokens * tk);
token see_next_token(tokens * tk);
void error_token(token * t);

tokens get_tokens(char * text);

void test_token();
void test_tokenizer();

#endif /* TOKENIZER_H_ */
