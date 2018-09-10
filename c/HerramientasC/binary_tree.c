/*
 * binary_tree.c
 *
 *  Created on: 18 ago. 2018
 *      Author: migueltoro
 */


#include "binary_tree.h"


memory_heap tree_memory = {0,0,NULL};

memory_heap * get_tree_memory(){
	if(tree_memory.elements == NULL) {
		tree_memory = memory_heap_create();
	}
	return &tree_memory;
}

void * get_mem_tree(int size){
	return memory_heap_tam_memory(get_tree_memory(),size);
}

void * get_int_tree(int a){
	return int_pointer_from_value(a,get_tree_memory());
}

void * get_long_tree(long a){
	return long_pointer_from_value(a,get_tree_memory());
}

void * get_value_tree(int size, void * value){
	return memory_heap_memory_for_value(get_tree_memory(),size, value);
}

void binary_tree_memory_clear(){
	memory_heap_free(&tree_memory);
}

type binary_tree_type = {1,NULL,sizeof(binary_tree),NULL,NULL,NULL,NULL,NULL,NULL,"binary_tree_type"};

binary_tree * tree_empty(type * label_type) {
	binary_tree tree = {label_type,Empty_Tree,NULL,NULL,NULL};
	return (binary_tree *) get_value_tree(sizeof(binary_tree),&tree);
}

binary_tree * tree_leaf(type * label_type, void * label) {
	binary_tree tree = {label_type,Leaf_Tree,label,NULL,NULL};
	return (binary_tree *) get_value_tree(sizeof(binary_tree),&tree);
}

binary_tree * tree_binary(void * label, binary_tree * left, binary_tree * right){
	binary_tree tree = {left->label_type,Binary_Tree,label,left,right};
	return (binary_tree *) get_value_tree(sizeof(binary_tree),&tree);
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

void tree_to_buffer(string_buffer * buffer, binary_tree * tree){
		char mem[Tam_String];
		switch(tree->tree_type){
		case Empty_Tree:
			string_buffer_add(buffer,"_"); break;
		case Leaf_Tree:
			string_buffer_add(buffer,tostring(tree->label_type,mem,get_label(tree)));
			break;
		case Binary_Tree:
			string_buffer_add(buffer,tostring(tree->label_type,mem,get_label(tree)));
			string_buffer_add(buffer,"(");
			tree_to_buffer(buffer,get_left(tree));
			string_buffer_add(buffer,",");
			tree_to_buffer(buffer,get_right(tree));
			string_buffer_add(buffer,")");
		}
}

list * tree_to_list_private(binary_tree * tree, list * ls);

list * tree_to_list(binary_tree * tree){
	list ls = list_empty(tree->label_type);
	return tree_to_list_private(tree,(list *)get_value_tree(sizeof(list),&ls));
}

list * tree_to_list_private(binary_tree * tree, list * ls) {
	switch (tree->tree_type) {
	case Empty_Tree: break;
	case Leaf_Tree: list_add(ls,get_label(tree)); break;
	case Binary_Tree:
		list_add(ls,get_label(tree));
		tree_to_list_private(get_left(tree),ls);
		tree_to_list_private(get_right(tree),ls);
	}
	return ls;
}



stream  * tree_stream(binary_tree * tree){
	return NULL;
}

void tree_memory_clear(){
	memory_heap_free(&tree_memory);
}


