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
static void main_helper(KStream ks, FILE *in_file, FILE *out_file, int to_stdout){
	byte in_buffer[BUFFER_SIZE];
	byte out_buffer[BUFFER_SIZE];
	size_t bytes_read;

	while ((bytes_read = fread(in_buffer, 1, BUFFER_SIZE, in_file)) > 0){
		ks_translate(ks, in_buffer, out_buffer, bytes_read);
		if (to_stdout == 1){
			for (size_t i = 0; i < bytes_read; i++){
				if(isascii(out_buffer[i])){
					printf("%c", out_buffer[i]);
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

/**
 * main function - 
 * 		   this functions manages the setup, error checking, and cleanup of encrpyting
 * 		   and decrypting
 */
int main(int argc, char *argv[]){
	FILE *key_file  = NULL;
	FILE *in_file = NULL;
	FILE *out_file = NULL;
	KStream ks =  NULL;

	if (argc != 4){
		print_usage();
		return EXIT_FAILURE;
	}

	char *key_filename = argv[1];
	char *in_filename = argv[2];
	char *out = argv[3];

	key_file = fopen(key_filename, "rb");
	if (key_file == NULL){
		perror(key_filename);
		return EXIT_FAILURE;

	}

	byte key[KEY_SIZE];
	size_t key_read = fread(key, 1, KEY_SIZE, key_file);
	if(key_read != KEY_SIZE){
		fprintf(stderr, "Error: Key file '%s' is not '%d' bytes long.\n",
				key_filename, KEY_SIZE);
		fclose(key_file);
		return EXIT_FAILURE;
	}

	in_file = fopen(in_filename, "rb");
	if(in_file == NULL){
		perror(in_filename);
		fclose(key_file);
		return EXIT_FAILURE;
	}

	int to_stdout = 0;

	if(strcmp(out, "-") == 0){
		to_stdout = 1;
		out_file  = stdout;
	}else {
		out_file =  fopen(out, "wb");
		if(out_file == NULL){
			perror(out);
			fclose(key_file);
			fclose(in_file);
			return EXIT_FAILURE;
		}
	}

	ks = ks_create(key, KEY_SIZE);
	if (ks == NULL){
		fprintf(stderr, "Error: failed to create KStream instance.\n");
		fclose(key_file);
        	fclose(in_file);
        	if (!to_stdout) fclose(out_file);
        	return EXIT_FAILURE;
	}

	main_helper(ks, in_file, out_file, to_stdout);
	fclose(key_file);
	fclose(in_file);
	if (!to_stdout) fclose(out_file);
    	ks_destroy(ks);
	
	return EXIT_SUCCESS; 
}


