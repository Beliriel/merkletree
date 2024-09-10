/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   merkletree.h
 * Author: beliriel
 *
 * Created on August 19, 2024, 2:40 PM
 */

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <blake2.h>

#ifndef MERKLETREE_H
#define MERKLETREE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define MTREE_FLAG_NODE 1
#define MTREE_FLAG_LEAF 0

    struct MTreeBuffer {
        unsigned char *dptr;
        size_t dsize;
    };

    struct MTreeNode {
        struct MTreeBuffer hash;
        struct MTreeNode *parent;
        struct MTreeNode *child_left;
        struct MTreeNode *child_right;
    };
    
    struct MTreeLevel {
        size_t num_elements;
        struct MTreeNode *elements;
        unsigned char flag;
        unsigned char level_num;
    };
    
    struct MTree {
        size_t num_levels;  //can never be 0 => 0 is error, includes leaves
        size_t hash_size;   //byte size of hashfunction result
        struct MTreeLevel *levels;
    };
    
    
    struct MTreeBuffer mtree_hash_data(void* data, size_t size, size_t hash_size); //for leaves
    
    void mtree_make_parent(struct MTreeNode *parent, struct MTreeNode *child_left, struct MTreeNode *child_right);
    int mtree_get_node_hash(struct MTreeNode *node, size_t hash_size, size_t level);
    
    struct MTreeNode mtree_load_data(void* data, size_t size);
    
    /**
     * 
     * @param tree pointer to tree structure
     * @param data_array pointer to data array
     * @param size size of a single element of the data array
     * @param elements amount of data elements the data array contains
     * @return 
     */
    int mtree_init(struct MTree *tree, void *data_array, size_t size, size_t elements);
    int mtree_process_level(struct MTree *tree, size_t lvl);
    int mtree_process_tree(struct MTree *tree);
    struct MTreeBuffer mtree_get_root(struct MTree *tree);
    
    void mtree_print_level(struct MTreeLevel level);
    void mtree_print_tree(struct MTree *tree);
    
    void mtree_free_node(struct MTreeNode *node);
    void mtree_free_level(struct MTreeLevel *level);
    void mtree_free(struct MTree *tree);
    
    

#ifdef __cplusplus
}
#endif

#endif /* MERKLETREE_H */

