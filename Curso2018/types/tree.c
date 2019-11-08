/*
 * binary_tree.c
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */


#include "tree.h"


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

binary_tree_type type_binary_tree(binary_tree * tree) {
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



void tree_to_list_private(binary_tree * tree, list * ls);

list binary_tree_to_list(binary_tree * tree){
	list ls = list_empty(tree->type_label);
	tree_to_list_private(tree,&ls);
	return ls;
}

void tree_to_list_private(binary_tree * tree, list * ls) {
	switch (tree->tree_type) {
	case Empty_Binary_Tree: break;
	case Leaf_Binary_Tree: list_add_pointer(ls,binary_tree_label(tree)); break;
	case Binary_Tree:
		list_add_pointer(ls,binary_tree_label(tree));
		tree_to_list_private(binary_tree_left(tree),ls);
		tree_to_list_private(binary_tree_right(tree),ls);
	}
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

tree_type type_tree(tree * tree) {
	return tree->tree_type;
}

void * tree_label(tree * tree){
	check_argument(tree->tree_type != Empty_Tree,__FILE__,__LINE__,"el árbol es vacío");
	return tree->label;
}

tree * tree_get_child(tree * tree, int child){
	check_argument(tree->tree_type == Tree,__FILE__,__LINE__,"el árbol no es nario");
	return tree->children[child];
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

void test_tree() {

	printf("Tree test\n\n");
	memory_heap hp = memory_heap_create();
	char mem[500];
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
//	list ls = binary_tree_to_list(t4);
//	char *s = list_tostring(&ls, mem);
//	printf("ls = %s\n", s);
//	list_sort(&ls, int_naturalorder);
//	s = list_tostring(&ls, mem);
//	printf("ls = %s\n\n", s);
	tree_toconsole(t4);
	printf("\n\n");
	memory_heap_free(&hp);
}
