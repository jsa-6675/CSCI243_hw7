/**
 * Kstream.h 
 * Author: Jodley Angrand
 *
 * Public Interface for Kstream
 * This module provides a Keystream afor symmetric-key encryption/decryption
 */

#ifndef KSTREAM_H
#define KSTREAM_H

#include <stdlib.h> 

typedef struct Kstream_s * KStream

typedef unsigned char byte 


/**
 * ks_create- creates and initializes a new Kstream instance.
 *
 * design: the client is responsible for acquiring the key from the file 
 * and passing it to this function. 
 *
 * @param key - A pointer to an array of bytes used as the key
 * @param keylen - the number of bytes in the key array 
 *
 * @return A new KStream instance. 
 */
KStream ks_create(byte *key, size_t keylen);

/**
 * ks_translate- Translates data between plaintext input and ciphertext output. 
 *
 * design: The client is responsible for allocating both input and output buffers
 *
 * @param ks the Kstream instance to use for translation.
 * @param inBytes The input buffer containing data to translate. 
 * @param outBytes The output buffer to store the translated data.
 * @param num the number of bytes to translate. 
 */
void ks_translate(Kstream ks, byte *in_bytes, *out_bytes, size_t num);

/**
 * Frees all resources with a KStream instance. 
 *
 *@param ks The Kstram instance to destroy
 */
void ks_destroy(Kstream ks);

#endif 

