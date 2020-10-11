/*
 * binary_tree.h
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */

#ifndef TREE_H_
#define TREE_H_


#include "../types/list.h"
#include "../types/types.h"
#include "../types/tokenizer.h"
#include "../types/memory_heap.h"

typedef enum{Empty_Binary_Tree, Leaf_Binary_Tree, Binary_Tree} binary_tree_class;
typedef enum{Empty_Tree, Leaf_Tree, Tree} tree_class;

typedef struct bt {
	binary_tree_class tree_type;
	type type_label;
	void * label;
	struct bt * left;
	struct bt * right;
}binary_tree;



typedef struct tr {
	tree_class tree_type;
	type type_label;
	void * label;
	int num_children;
	struct tr ** children;
}tree;

extern memory_heap memory_heap_tree;
extern memory_heap memory_heap_binary_tree;

binary_tree * binary_tree_empty(memory_heap * hp);
binary_tree * binary_tree_leaf(void * label, type type_label, memory_heap * hp);
binary_tree * binary_tree_new(void * label,type type_label, binary_tree * left, binary_tree * right, memory_heap * hp);

binary_tree * binary_tree_empty_m();
binary_tree * binary_tree_leaf_m(void * label, type type_label);
binary_tree * binary_tree_new_m(void * label,type type_label, binary_tree * left, binary_tree * right);

binary_tree_class class_binary_tree(binary_tree * tree);
void * binary_tree_label(binary_tree * tree);
binary_tree * binary_tree_left(binary_tree * tree);
binary_tree * binary_tree_right(binary_tree * tree);
list binary_tree_to_list(const binary_tree * tree);
int binary_tree_size(binary_tree * tree);
void binary_tree_toconsole(binary_tree * tree);

binary_tree * binary_tree_parse(char * text, memory_heap * hp);
binary_tree* binary_tree_parse_m(binary_tree * out, char * in);
char* binary_tree_tostring(const binary_tree * e, char * out);
bool binary_tree_equals(const binary_tree * e1, const binary_tree * e2);
int binary_tree_naturalorder(const binary_tree * e1,const binary_tree * e2);

binary_tree* binary_tree_map(binary_tree* tree_in, type tipo_out, void* fmap(void* out, const void* in), memory_heap* hp);
binary_tree* binary_tree_map_m(binary_tree* tree_in, type tipo_out, void* fmap(void* out, const void* in));

extern type binary_tree_type;


tree * tree_empty(memory_heap * hp);
tree * tree_leaf(void * label, type type_label, memory_heap * hp);
tree * tree_new(void * label, type type_label, int num_children, tree ** children, memory_heap * hp);

tree * tree_empty_m();
tree * tree_leaf_m(void * label, type type_label);
tree * tree_new_m(void * label, type type_label, int num_children, tree ** children);

tree_class class_tree(tree * tree);
void * tree_label(tree * tree);
tree * tree_get_child(tree * tree, int i);
int tree_child_number(tree * tree);
list tree_to_list(const tree * tree);
int tree_size(tree * tree);
void tree_toconsole(tree * tree);

tree * tree_parse(char * text, memory_heap * hp);
tree* tree_parse_m(tree * out, char * in);
char* tree_tostring(const tree * e, char * out);
bool tree_equals(const tree * e1, const tree * e2);
int tree_naturalorder(const tree * e1,const tree * e2);

tree* tree_map(tree* t, type tipo_out, void* fmap(void* out, const void* in), memory_heap* hp);
tree* tree_map_m(tree* t, type tipo_out, void* fmap(void* out, const void* in));

extern type tree_type;

void test_binary_tree();
void test_tree();
void test_parse_binary_tree();
void test_parse_tree();
void new_trees();

#endif /* TREE_H_ */
