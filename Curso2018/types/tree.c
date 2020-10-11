/*
 * binary_tree.c
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */


#include "tree.h"

memory_heap memory_heap_binary_tree;
memory_heap memory_heap_tree;

binary_tree * binary_tree_empty(memory_heap * hp) {
	binary_tree tree = {Empty_Binary_Tree,null_type,NULL,NULL,NULL};
	return (binary_tree *) memory_heap_copy_and_mem(hp,&tree,sizeof(binary_tree));
}

binary_tree * binary_tree_leaf(void * label, type label_type, memory_heap * hp) {
	void * lb = memory_heap_copy_and_mem(hp,label,label_type.size);
	binary_tree tree = {Leaf_Binary_Tree,label_type,lb,NULL,NULL};
	return (binary_tree *) memory_heap_copy_and_mem(hp,&tree,sizeof(binary_tree));
}

binary_tree * binary_tree_new(void * label, type label_type, binary_tree * left,  binary_tree * right, memory_heap * hp){
	void * lb = memory_heap_copy_and_mem(hp,label,label_type.size);
	binary_tree tree = {Binary_Tree,label_type,lb,left,right};
	return (binary_tree *) memory_heap_copy_and_mem(hp,&tree,sizeof(binary_tree));
}

binary_tree * binary_tree_empty_m() {
	return binary_tree_empty(&memory_heap_binary_tree);
}

binary_tree * binary_tree_leaf_m(void * label, type type_label) {
	return binary_tree_leaf(label, type_label, &memory_heap_binary_tree);
}

binary_tree * binary_tree_new_m(void * label,type type_label, binary_tree * left, binary_tree * right) {
	return binary_tree_new(label,type_label,left,right,&memory_heap_binary_tree);
}

token label_parse(tokens * tks) {
		token t = next_token(tks);
		switch (t.type) {
		case Operator:
			if(strcmp(t.text_token,"+") == 0 || strcmp(t.text_token,"-") ==0) {
				char  op[20];
				strcpy(op,t.text_token);
				token_class tps[] = {Integer,Double};
				t = match_token_types(tps,2,tks);
				char  nb[20];
				strcpy(nb,t.text_token);
				strcpy(t.text_token,op);
				strcat(t.text_token,nb);
			} else {
				error_token(&t);
			}
			break;
		case Integer:
		case Double:
		case Identifier:
			break;
		default: error_token(&t);
		}
		return t;
}

binary_tree * binary_tree_parse_private(tokens * tks, memory_heap * hp) {
	binary_tree * r;
	token t = label_parse(tks);
	if (strcmp(t.text_token, "_") == 0) {
		r = binary_tree_empty(hp);
	} else {
		r = binary_tree_leaf(t.text_token, pchar_type, hp);
		token tn = see_next_token(tks);
		char * ln = tn.text_token;
		if (has_more_tokens(tks) && strcmp(ln, "(") == 0) {
			char tt1[][5] = { "(" };
			match_token_texts((char*) tt1, 5, 1, tks);
			binary_tree * left = binary_tree_parse_private(tks, hp);
			char tt2[][5] = { "," };
			match_token_texts((char*) tt2, 5, 1, tks);
			binary_tree * right = binary_tree_parse_private(tks, hp);
			char tt3[][5] = { ")" };
			match_token_texts((char*) tt3, 5, 1, tks);
			r = binary_tree_new(t.text_token, pchar_type, left, right, hp);
		}
	}
	return r;
}

binary_tree * binary_tree_parse(char * text, memory_heap * hp) {
	tokens tks = get_tokens(text);
	binary_tree * tree = binary_tree_parse_private(&tks, hp);
	if (has_more_tokens(&tks)) {
		token t = current_token(&tks);
		error_token(&t);
	}
	return tree;
}

binary_tree* binary_tree_parse_m(binary_tree * out, char * in) {
	return binary_tree_parse(in, &memory_heap_binary_tree);
}


binary_tree_class class_binary_tree(binary_tree * tree) {
	return tree->tree_type;
}

void * binary_tree_label(binary_tree * tree){
	check_argument(tree->tree_type != Empty_Binary_Tree,__FILE__,__LINE__,"el árbol es vacío");
	return tree->label;
}

binary_tree * binary_tree_left(binary_tree * tree){
	check_argument(tree->tree_type == Binary_Tree,__FILE__,__LINE__,"el árbol no es binario");
	return tree->left;
}

binary_tree * binary_tree_right(binary_tree * tree){
	check_argument(tree->tree_type == Binary_Tree,__FILE__,__LINE__,"el árbol no es binario");
	return tree->right;
}

int binary_tree_size(binary_tree * tree){
	int r;
	switch(tree->tree_type){
	case Empty_Binary_Tree: r = 0; break;
	case Leaf_Binary_Tree: r = 1; break;
	case Binary_Tree: r = 1 + binary_tree_size(binary_tree_left(tree))+ binary_tree_size(binary_tree_right(tree));
	}
	return r;
}

void binary_tree_toconsole(binary_tree * tree) {
	switch (tree->tree_type) {
	char mem[256];
	case Empty_Binary_Tree:
		printf("_");
		break;
	case Leaf_Binary_Tree:
		printf("%s",tree->type_label.tostring(binary_tree_label(tree), mem));
		break;
	case Binary_Tree:
		printf("%s",tree->type_label.tostring(binary_tree_label(tree), mem));
		printf("(");
		binary_tree_toconsole(binary_tree_left(tree));
		printf(",");
		binary_tree_toconsole(binary_tree_right(tree));
		printf(")");
	}
}

char* binary_tree_tostring_private(const binary_tree * tree, char * out) {
	char mem[256];
	switch (class_binary_tree(tree)) {
	case Empty_Binary_Tree:
		strcat(out, "_");
		break;
	case Leaf_Binary_Tree:
		strcat(out, tree->type_label.tostring(binary_tree_label(tree), mem));
		break;
	case Binary_Tree:
		strcat(out, tree->type_label.tostring(binary_tree_label(tree), mem));
		strcat(out, "(");
		binary_tree_tostring_private(binary_tree_left(tree), out);
		strcat(out, ",");
		binary_tree_tostring_private(binary_tree_right(tree), out);
		strcat(out, ")");
	}
	return out;
}

char* binary_tree_tostring(const binary_tree * tree, char * out) {
	out[0] = '\0';
	return binary_tree_tostring_private(tree,out);
}

bool binary_tree_equals(const binary_tree * e1, const binary_tree * e2) {
	bool res=false;
	switch (class_binary_tree(e1)) {
	case Empty_Binary_Tree:
		res = class_binary_tree(e2)==Empty_Binary_Tree;
		break;
	case Leaf_Binary_Tree:
		res = class_binary_tree(e2)==Leaf_Binary_Tree && e1->type_label.equals(e1->label,e2->label);
		break;
	case Binary_Tree:
		res = class_binary_tree(e2)==Binary_Tree && e1->type_label.equals(e1->label,e2->label) &&
		binary_tree_equals(binary_tree_left(e1), binary_tree_left(e2)) &&
		binary_tree_equals(binary_tree_right(e1), binary_tree_right(e2));
	}
	return res;
}


void binary_tree_to_list_private(const binary_tree * tree, list * ls) {
	switch (tree->tree_type) {
	case Empty_Binary_Tree: break;
	case Leaf_Binary_Tree: list_add_pointer(ls,binary_tree_label(tree)); break;
	case Binary_Tree:
		list_add_pointer(ls,binary_tree_label(tree));
		binary_tree_to_list_private(binary_tree_left(tree),ls);
		binary_tree_to_list_private(binary_tree_right(tree),ls);
	}
}

list binary_tree_to_list(const binary_tree * tree){
	list ls = list_empty(tree->type_label);
	binary_tree_to_list_private(tree,&ls);
	return ls;
}

binary_tree* binary_tree_map(binary_tree* tree_in, type tipo_out,void* fmap(void* out, const void* in), memory_heap* hp) {
	binary_tree * res = NULL;
	binary_tree * left = NULL;
	binary_tree * right = NULL;
	void *etq_in, *etq_out;
	char mem[tipo_out.size];
	switch (class_binary_tree(tree_in)) {
	case Empty_Binary_Tree:
		res = binary_tree_empty(hp);
		break;
	case Leaf_Binary_Tree:
		etq_in = binary_tree_label(tree_in);
		etq_out = fmap(mem, etq_in);
		res = binary_tree_leaf(etq_out, tipo_out, hp);
		break;
	case Binary_Tree:
		etq_in = binary_tree_label(tree_in);
		etq_out = fmap(mem, etq_in);
		left = binary_tree_map(binary_tree_left(tree_in), tipo_out, fmap, hp);
		right = binary_tree_map(binary_tree_right(tree_in), tipo_out, fmap,  hp);
		res = binary_tree_new(etq_out, tipo_out, left, right, hp);
	}
	return res;
}

binary_tree* binary_tree_map_m(binary_tree* t, type tipo_out, void* fmap(void* out, const void* in)) {
	return binary_tree_map(t,tipo_out,fmap,&memory_heap_binary_tree);
}

type binary_tree_type = {binary_tree_equals, binary_tree_tostring, NULL, binary_tree_parse_m, sizeof(binary_tree)};


///////////////////////////////

tree * tree_empty(memory_heap * hp) {
	tree t = {Empty_Tree,null_type,NULL,0,NULL};
	return (tree *) memory_heap_copy_and_mem(hp,&t,sizeof(tree));
}

tree * tree_leaf(void * label, type label_type, memory_heap * hp) {
	void * lb = memory_heap_copy_and_mem(hp,label,label_type.size);
	tree t = {Leaf_Tree,label_type,lb,0,NULL};
	return (tree *) memory_heap_copy_and_mem(hp,&t,sizeof(tree));
}

tree * tree_new(void * label, type label_type, int num_children, tree ** children, memory_heap * hp){
	void * lb = memory_heap_copy_and_mem(hp,label,label_type.size);
	tree ** ch = memory_heap_copy_and_mem(hp,children,num_children*sizeof(tree *));
	tree t = {Tree,label_type,lb,num_children,ch};
	return (tree *) memory_heap_copy_and_mem(hp,&t,sizeof(tree));
}

tree * tree_empty_m() {
	return tree_empty(&memory_heap_tree);
}

tree * tree_leaf_m(void * label, type type_label) {
	return tree_leaf(label,type_label,&memory_heap_tree);
}

tree * tree_new_m(void * label, type type_label, int num_children, tree ** children) {
	return tree_new(label,type_label,num_children,children,&memory_heap_tree);
}

tree_class class_tree(tree * tree) {
	return tree->tree_type;
}

void * tree_label(tree * tree){
	check_argument(tree->tree_type != Empty_Tree,__FILE__,__LINE__,"el árbol es vacío");
	return tree->label;
}

int tree_child_number(tree * tree) {
	return tree->num_children;
}

tree * tree_get_child(tree * tree, int child){
	check_argument(tree->tree_type == Tree,__FILE__,__LINE__,"el árbol no es nario");
	check_argument(child < tree->num_children,__FILE__,__LINE__,"el árbol no tiene ese hijo");
	return tree->children[child];
}

tree * tree_parse_private(tokens * tks, memory_heap * hp) {
	tree * r;
	token t = label_parse(tks);
	if (strcmp(t.text_token, "_") == 0) {
		r = tree_empty(hp);
	} else {
		r = tree_leaf(t.text_token, pchar_type, hp);
		token tn = see_next_token(tks);
		char * ln = tn.text_token;
		if (has_more_tokens(tks) && strcmp(ln, "(") == 0) {
			char tt1[][5] = { "(" };
			match_token_texts((char*) tt1, 5, 1, tks);
			tree * children[10];
			tree * tt = tree_parse_private(tks, hp);
			int nh = 0;
			children[nh] = tt;
			nh++;
			char tt2[][5] = { "," };
			tn = see_next_token(tks);
			ln = tn.text_token;
			while(has_more_tokens(tks) && strcmp(ln, ",") == 0){
				match_token_texts((char*) tt2, 5, 1, tks);
				tt = tree_parse_private(tks, hp);
				children[nh] = tt;
				nh++;
				tn = see_next_token(tks);
				ln = tn.text_token;
			}
			char tt3[][5] = { ")" };
			match_token_texts((char*) tt3, 5, 1, tks);
			r = tree_new(t.text_token, pchar_type, nh, children, hp);
		}
	}
	return r;
}

tree * tree_parse(char * text, memory_heap * hp) {
	tokens tks = get_tokens(text);
	tree * tree = tree_parse_private(&tks, hp);
	if (has_more_tokens(&tks)) {
		token t = current_token(&tks);
		error_token(&t);
	}
	return tree;
}

tree* tree_parse_m(tree * out, char * in) {
	return tree_parse(in, &memory_heap_tree);
}

int tree_size(tree * tree){
	int r;
	switch(tree->tree_type){
	case Empty_Tree: r = 0; break;
	case Leaf_Tree: r = 1; break;
	case Tree:
		r = 0;
		for (int i=0; i < tree->num_children; i++){
			r = r + tree_size(tree_get_child(tree,i));
		}
		r = 1 + r;
		break;
	}
	return r;
}

list * tree_to_list_private(const tree * tree, list * ls) {
	switch (tree->tree_type) {
	case Empty_Tree: break;
	case Leaf_Tree: list_add_pointer(ls,binary_tree_label(tree)); break;
	case Tree:
		list_add_pointer(ls,tree_label(tree));
		for(int i=0; i < tree_child_number(tree); i++) {
			tree_to_list_private(tree_get_child(tree,i),ls);
		}
	}
	return ls;
}

list tree_to_list(const tree * tree){
	list ls = list_empty(tree->type_label);
	tree_to_list_private(tree,&ls);
	return ls;
}

void tree_toconsole(tree * tree) {
	switch (tree->tree_type) {
	char mem[256];
	case Empty_Tree:
		printf("_");
		break;
	case Leaf_Tree:
		printf("%s",tree->type_label.tostring(tree_label(tree), mem));
		break;
	case Tree:
		printf("%s",tree->type_label.tostring(tree_label(tree), mem));
		printf("(");
		tree_toconsole(tree_get_child(tree,0));
		for(int i = 1; i<tree->num_children;i++){
			printf(",");
			tree_toconsole(tree_get_child(tree,i));
		}
		printf(")");
	}
}



char* tree_tostring_private(const tree * tree, char * out) {
	char mem[256];
	switch (class_tree(tree)) {
	case Empty_Tree:
		strcat(out, "_");
		break;
	case Leaf_Tree:
		strcat(out,tree->type_label.tostring(tree_label(tree), mem));
		break;
	case Tree:
		strcat(out,tree->type_label.tostring(tree_label(tree), mem));
		strcat(out, "(");
		tree_tostring_private(tree_get_child(tree, 0), out);
		for (int i = 1; i < tree_child_number(tree); i++) {
			strcat(out, ",");
			tree_tostring_private(tree_get_child(tree, i), out);
		}
		strcat(out, ")");
	}
	return out;
}

char* tree_tostring(const tree * tree, char * out) {
	out[0] = '\0';
	return tree_tostring_private(tree,out);
}

bool tree_equals(const tree * e1, const tree * e2) {
	bool res=false;
	switch (class_tree(e1)) {
	case Empty_Tree:
		res = class_tree(e2)==Empty_Tree;
		break;
	case Leaf_Tree:
		res = class_tree(e2)==Leaf_Tree && e1->type_label.equals(e1->label,e2->label);
		break;
	case Tree:
		res = class_tree(e2)==Tree && e1->type_label.equals(e1->label,e2->label);
		int i=0, n = e1->num_children;
		while(res && i<n && n==e2->num_children) {
			res = tree_equals(tree_get_child(e1, i), tree_get_child(e2, i));
		}
	}
	return res;
}

tree* tree_map(tree* tree_in, type tipo_out, void* fmap(void* out, const void* in),memory_heap* hp) {
	tree *res = NULL;
	void * etq_in;
	void * etq_out;
	char mem[tipo_out.size];
	switch (class_tree(tree_in)) {
	case Empty_Tree:
		res = tree_empty(hp);
		break;
	case Leaf_Tree:
		etq_in = tree_label(tree_in);
		etq_out = fmap(mem, etq_in);
		res = tree_leaf(etq_out, tipo_out, hp);
		break;
	case Tree:
		etq_in = tree_label(tree_in);
		etq_out = fmap(mem, etq_in);
		tree* children[tree_in->num_children];
		for (int i = 0; i < tree_in->num_children; i++) {
			children[i] = tree_map(tree_get_child(tree_in, i), tipo_out, fmap, hp);
		}
		res = tree_new(etq_out, tipo_out, tree_in->num_children,children, hp);
	}
	return res;

}

tree* tree_map_m(tree* tree_in, type tipo_out, void* fmap(void* out, const void* in)) {
	return tree_map(tree_in,tipo_out,fmap,&memory_heap_tree);
}

type tree_type = {tree_equals,tree_tostring,NULL,tree_parse_m,sizeof(tree)};

void test_binary_tree(){
	printf("Binary Tree test\n\n");
	memory_heap hp =  memory_heap_create();
	char mem[500];
	int a = 84;
	int b = 90;
	int c = 56;
	int d = 81;
	int e = 55;

	binary_tree * t0 = binary_tree_empty(&hp);
	binary_tree * t1 = binary_tree_leaf(&c,int_type,&hp);
	binary_tree * t2 = binary_tree_new(&a,int_type,t0,t1,&hp);
	binary_tree * tl = binary_tree_leaf(&e,int_type,&hp);
	binary_tree * t3 = binary_tree_new(&b,int_type,t2,tl,&hp);
	binary_tree * t4 = binary_tree_new(&d,int_type,t3,t3,&hp);
	printf("size = %d\n\n", binary_tree_size(t4));
	list ls = binary_tree_to_list(t4);
	char * s = list_tostring(&ls, mem);
	printf("ls = %s\n", s);
	list_sort(&ls,int_naturalorder);
	s = list_tostring(&ls, mem);
	printf("ls = %s\n\n", s);
	binary_tree_toconsole(t4);
	printf("\n\n");
	memory_heap_free(&hp);
}

int * square(int * out, int * in){
	* out = (*in)*(*in);
	return out;
}

void test_binary_tree_2(){
	printf("Binary Tree test 2\n\n");
	memory_heap_binary_tree =  memory_heap_create();
	char mem[1500];
	int a = 84;
	int b = 90;
	int c = 56;
	int d = 81;
	int e = 55;

	binary_tree * t0 = binary_tree_empty_m();
	binary_tree * t1 = binary_tree_leaf_m(&c,int_type);
	binary_tree * t2 = binary_tree_new_m(&a,int_type,t0,t1);
	binary_tree * tl = binary_tree_leaf_m(&e,int_type);
	binary_tree * t3 = binary_tree_new_m(&b,int_type,t2,tl);
	binary_tree * t4 = binary_tree_new_m(&d,int_type,t3,t3);
	printf("size = %d\n\n", binary_tree_size(t4));
	list ls = binary_tree_to_list(t4);
	char * s = list_tostring(&ls, mem);
	printf("ls = %s\n", s);
	list_sort(&ls,int_naturalorder);
	s = list_tostring(&ls, mem);
	printf("ls = %s\n\n", s);
	binary_tree_toconsole(t4);
	binary_tree_tostring(t4,mem);
	printf("\n\ntree t4 = %s\n", mem);
	binary_tree * t5 = binary_tree_map_m(t4,int_type,square);
	binary_tree_tostring(t5,mem);
	printf("\n\ntree t5 = %s\n\n", mem);
	memory_heap_clear(&memory_heap_binary_tree);
}

void test_tree() {
	printf("Tree test\n\n");
	memory_heap hp = memory_heap_create();
	int a = 84;
	int b = 90;
	int c = 56;
	int d = 81;
	int e = 55;

	tree *t0 = tree_empty(&hp);
	tree *t1 = tree_leaf(&c, int_type, &hp);
	tree * ch1[] = {t0, t1};
	tree *t2 = tree_new(&a, int_type, 2, ch1, &hp);
	tree *tl = tree_leaf(&e, int_type, &hp);
	tree * ch2[] = {t2, tl};
	tree *t3 = tree_new(&b, int_type, 2, ch2, &hp);
	tree * ch3[] = {t3, t3};
	tree *t4 = tree_new(&d, int_type, 2, ch3, &hp);
	printf("size = %d\n\n", tree_size(t4));
	tree_toconsole(t4);
	printf("\n\n");
	memory_heap_free(&hp);
}



void test_tree_2() {
	printf("Tree test\n\n");
	memory_heap_tree = memory_heap_create();
	char mem[1500];
	int a = 84;
	int b = 90;
	int c = 56;
	int d = 81;
	int e = 55;

	tree *t0 = tree_empty_m();
	tree *t1 = tree_leaf_m(&c, int_type);
	tree * ch1[] = {t0, t1};
	tree *t2 = tree_new_m(&a, int_type, 2, ch1);
	tree *tl = tree_leaf_m(&e, int_type);
	tree * ch2[] = {t2, tl};
	tree *t3 = tree_new_m(&b, int_type, 2, ch2);
	tree * ch3[] = {t3, t3};
	tree *t4 = tree_new_m(&d, int_type, 2, ch3);
	printf("size = %d\n\n", tree_size(t4));
	tree_toconsole(t4);
	tree_tostring(t4,mem);
	printf("\n\ntree t4 = %s\n", mem);
	tree * t5 = tree_map_m(t4,int_type,square);
	tree_tostring(t5,mem);
	printf("\n\ntree t5 = %s\n\n", mem);
	memory_heap_free(&memory_heap_tree);
}

void test_parse_binary_tree(){
	memory_heap hp = memory_heap_create();
	binary_tree * tree = binary_tree_parse("-24.7(-34.5,-51(_,57))", &hp);
	binary_tree_toconsole(tree);
	binary_tree * tree2 = binary_tree_parse("0(_,-1)", &hp);
	binary_tree_toconsole(tree2);
	binary_tree * tree3 = binary_tree_parse("12(-34,56(-78,_))", &hp);
	binary_tree_toconsole(tree3);

}

void test_parse_tree(){
	memory_heap hp = memory_heap_create();
	tree * tree = tree_parse("-24.7(34.5,-51(33,56(57)),-51(33,57),-51(33,57))", &hp);
	tree_toconsole(tree);

}
