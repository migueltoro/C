/*
 * binary_tree.c
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */


#include "../types/binary_tree.h"


binary_tree * tree_empty(memory_heap * hp) {
	binary_tree tree = {Empty_Tree,0,NULL,NULL,NULL};
	return (binary_tree *) memory_heap_copy_and_mem(hp,&tree,sizeof(binary_tree));
}

binary_tree * tree_leaf(void * label, int size_label, memory_heap * hp) {
	void * lb = memory_heap_copy_and_mem(hp,label,size_label);
	binary_tree tree = {Leaf_Tree,size_label,lb,NULL,NULL};
	return (binary_tree *) memory_heap_copy_and_mem(hp,&tree,sizeof(binary_tree));
}

binary_tree * tree_binary(void * label, int size_label, binary_tree * left,  binary_tree * right, memory_heap * hp){
	void * lb = memory_heap_copy_and_mem(hp,label,size_label);
	binary_tree tree = {Binary_Tree,size_label,lb,left,right};
	return (binary_tree *) memory_heap_copy_and_mem(hp,&tree,sizeof(binary_tree));
}

tree_type binary_tree_type(binary_tree * tree) {
	return tree->tree_type;
}

void * binary_tree_label(binary_tree * tree){
	check_argument(tree->tree_type != Empty_Tree,__FILE__,__LINE__,"el árbol es vacío");
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
	case Empty_Tree: r = 0; break;
	case Leaf_Tree: r = 1; break;
	case Binary_Tree: r = 1 + binary_tree_size(binary_tree_left(tree))+ binary_tree_size(binary_tree_right(tree));
	}
	return r;
}



void tree_to_list_private(binary_tree * tree, list * ls);

list binary_tree_to_list(binary_tree * tree, type type_element){
	list ls = list_empty(type_element);
	tree_to_list_private(tree,&ls);
	return ls;
}

void tree_to_list_private(binary_tree * tree, list * ls) {
	switch (tree->tree_type) {
	case Empty_Tree: break;
	case Leaf_Tree: list_add_pointer(ls,binary_tree_label(tree)); break;
	case Binary_Tree:
		list_add_pointer(ls,binary_tree_label(tree));
		tree_to_list_private(binary_tree_left(tree),ls);
		tree_to_list_private(binary_tree_right(tree),ls);
	}
}

void binary_tree_toconsole(binary_tree * tree, char * tostring(const void * source, char * mem)) {
	switch (tree->tree_type) {
	char mem[256];
	case Empty_Tree:
		printf("_");
		break;
	case Leaf_Tree:
		printf("%s",tostring(binary_tree_label(tree), mem));
		break;
	case Binary_Tree:
		printf("%s",tostring(binary_tree_label(tree), mem));
		printf("(");
		binary_tree_toconsole(binary_tree_left(tree),tostring);
		printf(",");
		binary_tree_toconsole(binary_tree_right(tree),tostring);
		printf(")");
	}
}


void test_tree(){
	printf("Binary Tree test\n\n");
	memory_heap hp =  memory_heap_create();
	char mem[500];
	int a = 84;
	int b = 90;
	int c = 56;
	int d = 81;
	int e = 55;

	binary_tree * t0 = tree_empty(&hp);
	binary_tree * t1 = tree_leaf(&c,sizeof(int),&hp);
	binary_tree * t2 = tree_binary(&a,sizeof(int),t0,t1,&hp);
	binary_tree * tl = tree_leaf(&e,sizeof(int),&hp);
	binary_tree * t3 = tree_binary(&b,sizeof(int),t2,tl,&hp);
	binary_tree * t4 = tree_binary(&d,sizeof(int),t3,t3,&hp);
	printf("size = %d\n\n", binary_tree_size(t4));
	list ls = binary_tree_to_list(t4,int_type);
	char * s = list_tostring(&ls, mem);
	printf("ls = %s\n", s);
	list_sort(&ls,int_naturalorder);
	s = list_tostring(&ls, mem);
	printf("ls = %s\n\n", s);
	binary_tree_toconsole(t4,int_tostring);
	printf("\n\n");

}
