/**
 * mcrypt.c
 * Author: Jodley A(jsa6675)
 *
 * This program encrypts or decrypes a file using a provided key.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "KStream.h"

#define KEY_SIZE 8
#define BUFFER_SIZE 4096

typedef unsigned char byte;

/**
 * Prints the usage message to stderr.
 */
static void print_usage(void){
	fprintf(stderr, "usage: mcrypt key-file in-file [ out file | -]\n");
}

/**
 * main helper function 
 *
 * reads from in_file, translates the KStream, and write to out_file)
 * @param ks the initializes KStream instance
 * @param in_file the open input file stream.
 * @param out_file the open output file. 
 * @param prints to stdout if 1 prints to stdout 0 if otherwise.
 */
static void main_helper(KStream ks, File *in_file, File *out_file, int to_stdout){
	byte in_buffer[BUFFER_SIZE];
	byte out_buffer[BUFFER_SIZE];
	size_t bytes_read;

	while ((bytes_read = fread(in_buffer, 1, BUFFER_SIZE, in_file)) > 0){
		ks_translate(ks, in_buffer, out_bufer, bytes_read);
		if (to_stdout == 1){
			for (size i = 0; i < bytes_read; i++){
				if(isascii(out_buffer[i])){
					printf("%c" outbuffer[i]);
				} else {
					printf("%02x", out_buffer[i]);
				}
			}
		}
		else{
			fwrite(out_buffer, 1, bytes_read, out_file);
		}
		
	}

}


