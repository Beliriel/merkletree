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

#include <stdint.h>

#ifndef MERKLETREE_H
#define MERKLETREE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define MTREE_FLAG_ROOT 2
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
        size_t num_levels;  //can never be 0 => 0 is error
        size_t hash_size;
        struct MTreeLevel *levels;
    };
    
    
    struct MTreeBuffer mtree_hash_data (void* data, size_t size);
    struct MTreeBuffer mtree_get_parent(void *data1, size_t size1, void *data2, size_t size2);
    struct MTreeNode mtree_load_data(void* data, size_t size);
    
    int mtree_init_level(struct MTree *tree, void *data_array, size_t size, size_t elements);
    int mtree_process_level(struct MTree *tree);
    struct MTreeBuffer mtree_get_root(struct MTree *tree);
    

#ifdef __cplusplus
}
#endif

#endif /* MERKLETREE_H */

