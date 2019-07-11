/*
 * binary_tree.c
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */


#include "../types/binary_tree.h"
#include "../types/memory_heap.h"

memory_heap tree_memory;

binary_tree * tree_empty() {
	binary_tree tree = {Empty_Tree,NULL,NULL,NULL};
	return (binary_tree *) memory_heap_to_data(&tree_memory,&tree,sizeof(binary_tree));
}

binary_tree * tree_leaf(void * label) {
	binary_tree tree = {Leaf_Tree,label,NULL,NULL};
	return (binary_tree *) memory_heap_to_data(&tree_memory,&tree,sizeof(binary_tree));
}

binary_tree * tree_binary(void * label, binary_tree * left, binary_tree * right){
	binary_tree tree = {Binary_Tree,label,left,right};
	return (binary_tree *) memory_heap_to_data(&tree_memory,&tree,sizeof(binary_tree));
}

tree_type get_type(binary_tree * tree) {
	return tree->tree_type;
}

void * get_label(binary_tree * tree){
	assert(tree->tree_type != Empty_Tree && "el árbol es vacío");
	return tree->label;
}

binary_tree * get_left(binary_tree * tree){
	assert(tree->tree_type == Binary_Tree && "el árbol no es binario");
	return tree->left;
}

binary_tree * get_right(binary_tree * tree){
	assert(tree->tree_type == Binary_Tree && "el árbol no es binario");
	return tree->right;
}

int tree_size(binary_tree * tree){
	int r;
	switch(tree->tree_type){
	case Empty_Tree: r = 0; break;
	case Leaf_Tree: r = 1; break;
	case Binary_Tree: r = 1 + tree_size(get_left(tree))+ tree_size(get_right(tree));
	}
	return r;
}



void tree_to_list_private(binary_tree * tree, list * ls);

list tree_to_list(binary_tree * tree, type type_element){
	list ls = list_empty(type_element);
	tree_to_list_private(tree,&ls);
	return ls;
}

void tree_to_list_private(binary_tree * tree, list * ls) {
	switch (tree->tree_type) {
	case Empty_Tree: break;
	case Leaf_Tree: list_add_pointer(ls,get_label(tree)); break;
	case Binary_Tree:
		list_add_pointer(ls,get_label(tree));
		tree_to_list_private(get_left(tree),ls);
		tree_to_list_private(get_right(tree),ls);
	}
}

void tree_tostring(binary_tree * tree, char * tostring(const void * source, char * mem)) {
	switch (tree->tree_type) {
	char mem[256];
	case Empty_Tree:
		printf("_");
		break;
	case Leaf_Tree:
		printf("%s",tostring(get_label(tree), mem));
		break;
	case Binary_Tree:
		printf("%s",tostring(get_label(tree), mem));
		printf("(");
		tree_tostring(get_left(tree),tostring);
		printf(",");
		tree_tostring(get_right(tree),tostring);
		printf(")");
	}
}

void binary_tree_memory_free(){
	memory_heap_free(&tree_memory);
}

void binary_tree_memory_create(){
	tree_memory = memory_heap_create();
}

void test_tree(){
	printf("Binary Tree test\n\n");
	memory_heap hp = memory_heap_create();
	binary_tree_memory_create();
	char mem[500];

	int a = 84; void * pa = memory_heap_to_data(&hp,&a,sizeof(int));
	int b = 90; void * pb = memory_heap_to_data(&hp,&b,sizeof(int));
	int c = 56; void * pc = memory_heap_to_data(&hp,&c,sizeof(int));
	int d = 81; void * pd = memory_heap_to_data(&hp,&d,sizeof(int));
	int e = 55; void * pe = memory_heap_to_data(&hp,&e,sizeof(int));

	binary_tree * t0 = tree_empty();
	binary_tree * t1 = tree_leaf(pc);
	binary_tree * t2 = tree_binary(pa,t0,t1);
	binary_tree * t3 = tree_binary(pb,t2,tree_leaf(pe));
	binary_tree * t4 = tree_binary(pd,t3,t3);
	printf("size = %d\n\n", tree_size(t4));
	list ls = tree_to_list(t4,int_type);
	char * s = list_tostring(&ls, mem);
	printf("ls = %s\n", s);
	list_sort(&ls,int_naturalorder);
	s = list_tostring(&ls, mem);
	printf("ls = %s\n\n", s);
	tree_tostring(t4,int_tostring);
	printf("\n\n");
	memory_heap_free(&hp);
	binary_tree_memory_free();
}
