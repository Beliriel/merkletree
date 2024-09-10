/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utilities.h
 * Author: beliriel
 *
 * Created on August 19, 2024, 2:41 PM
 */

#include <stdio.h>

#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

void print_buf(const char *title, const void *buf, size_t buf_len);

/**
 * calculates the height of the tree based on the amount of elements
 * excluding the base layer (leaves). Only the node-height is calculated.
 * If the base layer should be included add one to the result.
 * @param x amount of leaves
 * @return amount of levels of nodes
 */
size_t calculate_log2_height(size_t x);


#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */

