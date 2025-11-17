/**
 * Kstream.c
 * Author: Jodley Angrand(jsa6675)
 *
 * Private implementation of KStream ADT. 
 */

#include "KStream.h"
#include <stdlib.h>
#include <stdio.h>



/**
 * Struct KStream_s
 */
 struct KStream_s{
	 byte S[256];
	 unsigned i;
	 unsigned j;
};

// private helper functions 

/**
 * swap- swaps the value of tow bytes.
 * @param a - pointer to the first byte.
 * @param b - pointer to the second byte.
 */
static void swap( byte *a, byte *b){
	byte temp;
	temp = *a; 
	*a = *b; 
	*b = temp;
}

/**
 * next_byte - generates the next byte from the keystream.
 *
 * @param ks - the Kstream instance
 * @return the next random byte from the keystream. 
 */
static byte next_byte(KStream ks){
	ks->i = (ks->i +1) % 256;
	ks->j = (ks->j + ks->S[ks->i]) % 256;
	swap(&(ks->S[ks->i]),&(ks->S[ks->j]));
	unsigned int index = (ks->S[ks->i] + ks->S[ks->j]) % 256;
	return ks->S[index];
}


// public Function Implementations 

KStream ks_create(byte *key, size_t keylen){
	KStream ks = malloc(sizeof(struct KStream_s));
	if (ks == NULL){
		return NULL;
	}

	for (unsigned int i = 0; i < 256; i++){
		ks->S[i] = i;
	}

	unsigned int j = 0;

	for( int i = 0; i < 256; i++){
		j = (j + ks->S[i] + (unsigned int)key[i % keylen]) % 256;
		swap(&(ks->S[i]),&(ks->S[j]));	
	}	

	ks->i = 0;
	ks->j = 0;

	for ( int k = 0; k < 1024; k++){
		next_byte(ks);
	}

	return ks;
}

/*
 *ks_translate - translate data between input and output forms.
 */
void ks_translate(KStream ks, byte *in_bytes, byte *out_bytes, size_t num){
	for(size_t i = 0; i < num; i++){
		out_bytes[i] = in_bytes[i] ^ next_byte(ks);
	}
}

// ks_destroy - free the memory for the KStream instance
void ks_destroy(KStream ks){
	free(ks);
}
	
