/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */




#include "merkletree.h"
#include "utilities.h"


struct MTreeBuffer mtree_hash_data(void* data, size_t size, size_t hash_size)
{
    struct MTreeBuffer res = {0};
    unsigned char tmp_flag = MTREE_FLAG_LEAF;
    unsigned char tmp_level = 0;
    res.dsize = hash_size;
    res.dptr = malloc(res.dsize);
    blake2b_state state;
    blake2b_init(&state, res.dsize);
    blake2b_update(&state, (uint8_t*) (&tmp_flag), 1);
    blake2b_update(&state, (uint8_t*) (&tmp_level), 1);
    blake2b_update(&state, (uint8_t*) data, size);
    blake2b_final(&state, (uint8_t*) res.dptr, res.dsize);
    return res;
}

int mtree_get_node_hash(struct MTreeNode *node, size_t hash_size, size_t level)
{
    struct MTreeBuffer res = {0};
    int rc = 0;
    unsigned char tmp_flag = MTREE_FLAG_NODE;
    unsigned char tmp_level = (unsigned char) level;
    res.dsize = hash_size;
    res.dptr = malloc(res.dsize);
    blake2b_state state;
    rc += blake2b_init(&state, res.dsize);
    rc += blake2b_update(&state, (uint8_t*) (&tmp_flag), 1);
    rc += blake2b_update(&state, (uint8_t*) (&tmp_level), 1);
    rc += blake2b_update(&state, (uint8_t*) node->child_left->hash.dptr, hash_size);
    rc += blake2b_update(&state, (uint8_t*) node->child_right->hash.dptr, hash_size);
    rc += blake2b_final(&state, (uint8_t*) res.dptr, res.dsize);
    node->hash = res;
    return rc;
}

int mtree_init(struct MTree *tree, void *data_array, size_t size, size_t elements)
{
    unsigned char *index_p;
    struct MTreeBuffer tmp_buf;
    
    if (tree == NULL) {
        return -1;
    }
    
    tree->num_levels = calculate_log2_height(elements) + 1;
    tree->levels = malloc(tree->num_levels * sizeof(struct MTreeLevel));
    tree->levels[0].level_num = 0;
    tree->levels[0].num_elements = elements;
    tree->levels[0].elements = malloc(tree->levels[0].num_elements * sizeof(struct MTreeNode));
    index_p = data_array;
    
    for (int i = 0; i < elements; i++) {
        struct MTreeNode *node = &(tree->levels[0].elements[i]);
        node->hash = mtree_hash_data(index_p, size, tree->hash_size);
        node->child_left = NULL;
        node->child_right = NULL;
        node->parent = NULL;
        index_p += size;
    }
    
    return 0;
}

void mtree_make_parent(struct MTreeNode *parent, struct MTreeNode *child_left, struct MTreeNode *child_right)
{
    parent->child_left = child_left;
    parent->child_right = child_right;
    child_left->parent = parent;
    child_right->parent = parent;
    parent->parent = NULL;
}

int mtree_process_level(struct MTree *tree, size_t lvl)
{
    if(lvl >= tree->num_levels-1) return -1;
    struct MTreeLevel *nlvl = &(tree->levels[lvl + 1]); //new level
    struct MTreeLevel *plvl = &(tree->levels[lvl]); //previous level
    nlvl->level_num = plvl->level_num + 1;
    size_t n = plvl->num_elements;
    size_t size_nxt_lvl = (n / 2) + (n % 2);
    nlvl->num_elements = size_nxt_lvl;
    nlvl->elements = malloc(size_nxt_lvl * sizeof(struct MTreeNode));
    
    for (int i = 0; i < n/2; i++) {
        struct MTreeNode *node = &(nlvl->elements[i]);
        mtree_make_parent(node, &(plvl->elements[i*2]), &(plvl->elements[i*2 + 1]));
        if (mtree_get_node_hash(node, tree->hash_size, nlvl->level_num)) {
            printf("Error hashing node Level: %d, Node %d\n", nlvl->level_num, i);
            return -1;
        }
    }
    
    if (size_nxt_lvl > 1 && (n % 2 != 0)) {
        struct MTreeNode *node = &(nlvl->elements[nlvl->num_elements-1]);
        size_t ipl = plvl->num_elements - 1; //Index of Previous level of the Last element
        mtree_make_parent(node, &(plvl->elements[ipl]), &(plvl->elements[ipl]));
        if (mtree_get_node_hash(node, tree->hash_size, nlvl->level_num)) {
            printf("Error hashing node Level: %d, Node %d\n", nlvl->level_num, nlvl->num_elements-1);
            return -1;
        }
    }
    return 0; 
}

int mtree_process_tree(struct MTree* tree)
{
    size_t proc_level = 0;
    while(!mtree_process_level(tree, proc_level)) {
        proc_level++;
    }
    
    if (tree->levels[tree->num_levels - 1].elements[0].parent != NULL) {
        printf("Root not correct\n");
        return -1;
    }
    
    return 0;
}

void mtree_print_level(struct MTreeLevel level)
{
    for (int i = 0; i < level.num_elements; i++) {
        printf("%d", i + 1);
        print_buf(". element: ", level.elements[i].hash.dptr, level.elements[i].hash.dsize);
    }
    printf("\n");
}

void mtree_print_tree(struct MTree* tree)
{
    for (int i = 0; i < tree->num_levels; i++) {
        mtree_print_level(tree->levels[i]);
    }
}

void mtree_free_node(struct MTreeNode* node)
{
    free(node->hash.dptr);
    node->hash.dptr = NULL;
    node->parent = NULL;
    node->child_left = NULL;
    node->child_right = NULL;
}

void mtree_free_level(struct MTreeLevel* level)
{
    for (int i = 0; i < level->num_elements; i++) {
        mtree_free_node(&(level->elements[i]));
    }
    free(level->elements);
    level->elements = NULL;
}

void mtree_free(struct MTree* tree)
{
    for (int i = 0; i < tree->num_levels; i++) {
        mtree_free_level(&(tree->levels[i]));
    }
    free(tree->levels);
    tree->levels = NULL;
    tree->num_levels = 0;
    tree->hash_size = 0;
}