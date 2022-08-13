#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "models/node.h"
#ifndef HASHMAP_H
#define HASHMAP_H
#define LOADFACTOR 0.7
typedef struct Bucket Bucket;
struct Bucket
{
    char *Key;
    Node *Value;
};
static Bucket *newBucket();
static void destroyBucket(Bucket *bucket);
/*
    Hashing function to hash the passed key 
    to get the index of the bucket list
   
    Hash algorithm used is djb2 by Dan Bernstein.
    this algorithm (k=33) was first reported by dan bernstein many 
    years ago in comp.lang.c. another version of this algorithm 
    (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; 
    the magic of number 33 (why it works better than many other 
    constants, prime or not) has never been adequately explained.
*/
static int hash(const char *key);
static bool isPrime(size_t num);
static bool isOverLoad(int entries, int size, double lambda);
static size_t findClosestPrime(size_t size);

typedef struct HashMap HashMap;
struct HashMap
{
    Bucket **BucketList;
    size_t Size;
    int Entries;
};

/*
    Constructor function for creating hashmap instance
    Takes in initial size of the hashmap
    and allocates memory for the instance  
*/
HashMap *newHashMap(size_t size);
void *destroyMap(HashMap *map);
HashMap *insert(HashMap *map, const char *key, const Node *value);
Node *obtain(HashMap *map, const char *key);
static HashMap *reHash(HashMap *map);
void printMap(HashMap *map);

#endif