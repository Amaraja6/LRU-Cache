#include "hashmap.h"
static Bucket *newBucket()
{
    Bucket *bucket = (Bucket *)malloc(sizeof(Bucket));
    bucket->Key = (char *)malloc(50 * sizeof(char));
    bucket->Value = (Node *)malloc(sizeof(Node));
    return bucket;
}

static void destroyBucket(Bucket *bucket)
{
    if (bucket)
    {
        if (bucket->Key)
        {
            free(bucket->Key);
        }
        if (bucket->Value)
        {
            destroyNode(bucket->Value);
        }
    }
    return;
}

static int hash(const char *key)
{
    char c;
    unsigned long hash = 5381;
    while (c = *(key++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

static bool isPrime(size_t num)
{
    if (num == 0 || num == 1)
        return false;
    else if (num == 2)
        return true;
    else if (num % 2 == 0)
        return false;
    else
    {
        for (int i = 2; i <= sqrt(num); i += 2)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }
}
static bool isOverLoad(int entries, int size, double lambda)
{
    return ((double)entries / (double)size) >= lambda;
}

static size_t findClosestPrime(size_t size)
{
    int raising_steps = 0;
    int falling_steps = 0;
    size_t i = size;
    size_t j = size;
    while (!isPrime(++i))
    {
        raising_steps++;
    }
    while (!isPrime(--j))
    {
        falling_steps++;
    }
    return (raising_steps < falling_steps) ? i : j;
}

HashMap *newHashMap(size_t size)
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (map)
    {
        map->Size = size;
        map->Entries = 0;
        map->BucketList = (Bucket **)malloc(map->Size * sizeof(Bucket *));

        if (map->BucketList)
        {
            for (int i = 0; i < size; i++)
            {
                map->BucketList[i] = NULL;
            }
        }
        else
        {
            printf("\nNo memory for creating Bucketlist for the new Hashmap!");
        }
    }
    else
    {
        printf("\nNo memory for creating new Hashmap!");
    }
    return map;
}

void *destroyMap(HashMap *map)
{
    if (map)
    {
        if (map->BucketList)
        {
            for (int i = 0; i < map->Size; i++)
            {
                destroyBucket(map->BucketList[i]);
            }
            free(map->BucketList);
        }
        free(map);
    }
    return NULL;
}

void printMap(HashMap *map)
{
    for (int i = 0; i < map->Size; i++)
    {
        if (map->BucketList[i])
        {
            printf("\nKey:%s Value:%p", map->BucketList[i]->Key, map->BucketList[i]->Value);
        }
    }
    printf("\nEntries : %d\nSize : %d", map->Entries, map->Size);
}

HashMap *insert(HashMap *map, const char *key, const Node *value)
{
    if (isOverLoad(map->Entries, map->Size, LOADFACTOR))
    {
        printf("\nMap is Overloaded.. Rehasing");
        map = reHash(map);
    }
    int bucketindex = hash(key) % map->Size;
    if (map->BucketList[(bucketindex % map->Size)] != NULL)
    {
        int bucketiterations = 0;
        while (map->BucketList[(bucketindex % map->Size)] != NULL && bucketiterations < map->Size)
        {
            if (strcmp(map->BucketList[(bucketindex % map->Size)]->Key, key) == 0)
            {
                destroyBucket(map->BucketList[(bucketindex % map->Size)]);
                map->BucketList[(bucketindex % map->Size)] = NULL;
                map->Entries--;
                break;
            }
            bucketindex++;
            bucketiterations++;
        }
    }
    map->BucketList[(bucketindex % map->Size)] = newBucket();
    strcpy(map->BucketList[(bucketindex % map->Size)]->Key, key);
    map->BucketList[(bucketindex % map->Size)]->Value = value;
    map->Entries++;
    // printf("\nPointer at bucket index %d is %p", bucketindex % map->Size, (void *)map->BucketList[bucketindex % map->Size]);
    return map;
}

static HashMap *reHash(HashMap *map)
{
    size_t prime_size = findClosestPrime(map->Size * 2);
    HashMap *remap = newHashMap(prime_size);
    if (remap)
    {
        for (int i = 0; i < map->Size; i++)
        {
            if (map->BucketList[i] != NULL)
            {
                remap = insert(remap, map->BucketList[i]->Key, map->BucketList[i]->Value);
            }
        }
        return remap;
    }
    return map;
}

Node *obtain(HashMap *map, const char *key)
{
    int bucketindex = hash((char *)key) % map->Size;

    int bucketiterations = 0;
    while (map->BucketList[(bucketindex % map->Size)] != NULL && bucketiterations < map->Size)
    {
        if (strcmp(map->BucketList[(bucketindex % map->Size)]->Key, key) == 0)
        {
            return map->BucketList[(bucketindex % map->Size)]->Value;
        }
        bucketindex++;
        bucketiterations++;
    }
    return NULL;
}
