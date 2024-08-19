/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "utilities.h"

void print_buf(const char *title, const void *buf, size_t buf_len)
{
    size_t i = 0;
    const unsigned char* conv_buf = (unsigned char*)buf;
    fprintf(stdout, "%s\n", title);
    for(i = 0; i < buf_len; ++i)
    fprintf(stdout, "%02X%s", conv_buf[i],
             ( i + 1 ) % 16 == 0 ? "\n" : " " );
    

}