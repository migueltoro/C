/*
 * binary_tree.h
 *
 *  Created on: 18 ago. 2018
 *      Author: migueltoro
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "basic_types.h"
#include "string_buffer.h"
#include "memory_heap.h"
#include "list.h"

typedef enum{Empty_Tree, Leaf_Tree, Binary_Tree} tree_type;

typedef struct bt {
	type * label_type;
	tree_type tree_type;
	void * label;
	struct bt * left;
	struct bt * right;
}binary_tree;


binary_tree * tree_empty(type * label_type);
binary_tree * tree_leaf(type * label_type, void * label);
binary_tree * tree_binary(void * label, binary_tree * left, binary_tree * right);
tree_type get_type(binary_tree * tree);
void * get_label(binary_tree * tree);
binary_tree * get_left(binary_tree * tree);
binary_tree * get_right(binary_tree * tree);
list * tree_to_list(binary_tree * tree);
stream * tree_stream(binary_tree * tree);
int tree_size(binary_tree * tree);
void tree_to_buffer(string_buffer * buffer, binary_tree * tree);

void * get_mem_tree(int size);
void * get_int_tree(int value);
void * get_long_tree(long value);
void * get_value_tree(int size, void * value);
void binary_tree_memory_clear();

extern type binary_tree_type;

#endif /* BINARY_TREE_H_ */
