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
    
    unsigned int *p = malloc(sizeof(unsigned int));
    *p = 23;
    printf("%d\n", *p);
    free(p);
    return (EXIT_SUCCESS);
}

