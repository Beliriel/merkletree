/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: beliriel
 *
 * Created on August 19, 2024, 2:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "merkletree.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    uint64_t array[] = { 0, 1, 2, 3, 5, 8, 9};
    struct MTree tree;
    tree.hash_size = 16;
    
    int rc = mtree_init(&tree, array, sizeof(uint64_t), 7);
    
    mtree_process_tree(&tree);
    mtree_print_tree(&tree);
    mtree_free(&tree);
    return (EXIT_SUCCESS);
}

