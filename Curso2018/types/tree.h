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

typedef enum{Empty_Binary_Tree, Leaf_Binary_Tree, Binary_Tree} binary_tree_type;
typedef enum{Empty_Tree, Leaf_Tree, Tree} tree_type;

typedef struct bt {
	binary_tree_type tree_type;
	type type_label;
	void * label;
	struct bt * left;
	struct bt * right;
}binary_tree;



typedef struct tr {
	tree_type tree_type;
	type type_label;
	void * label;
	int num_children;
	struct tr ** children;
}tree;


binary_tree * binary_tree_empty(memory_heap * hp);
binary_tree * binary_tree_leaf(void * label, type type_label, memory_heap * hp);
binary_tree * binary_tree_new(void * label,type type_label, binary_tree * left, binary_tree * right, memory_heap * hp);
binary_tree * binary_tree_parse(char * in, memory_heap * hp);
binary_tree_type type_binary_tree(binary_tree * tree);
void * binary_tree_label(binary_tree * tree);
binary_tree * binary_tree_left(binary_tree * tree);
binary_tree * binary_tree_right(binary_tree * tree);
list binary_tree_to_list(binary_tree * tree);
int binary_tree_size(binary_tree * tree);
void binary_tree_toconsole(binary_tree * tree);


tree * tree_empty(memory_heap * hp);
tree * tree_leaf(void * label, type type_label, memory_heap * hp);
tree * tree_new(void * label, type type_label, int num_children, tree ** children, memory_heap * hp);
tree * tree_parse(char * text, memory_heap * hp);
tree_type type_tree(tree * tree);
void * tree_label(tree * tree);
tree * tree_get_child(tree * tree, int i);
list tree_to_list(tree * tree);
int tree_size(tree * tree);
void tree_toconsole(tree * tree);

void test_binary_tree();
void test_tree();
void test_parse_binary_tree();
void test_parse_tree();

#endif /* TREE_H_ */
