// Vyshnavee Reddlapalli and Lorna Xiao
// Lab 4: Memory Allocation

//References Used:
//Stackoverflow was utilized
//http://tharikasblogs.blogspot.com/p/how-to-write-your-own-malloc-and-free.html
//http://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
//https://stackoverflow.com/questions/10864593/implementation-of-realloc-in-c
//https://danluu.com/malloc-tutorial/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

struct block {
        size_t Size;
        void *ptr2;
        struct block *next;
        int Free;
};
struct block *root = NULL; //the top node
#define struct_sz sizeof(struct block)

//add new block to the linked list
void add_block(struct block *node) {
        struct block *prevnode;
        if(root == NULL) {
                root = node;
                root->next = NULL;
        }
        else {
                struct block *current = root;
                while(current) {
                        prevnode = current;
                        current = current->next;
                }
                prevnode->next = node;
                node->next = NULL;
        }
};
//round a number upto the nearest multiple of 8
int divis_eight(int n) {
        return ((n - 1)/8 + 1) *  8;
};

//find the block of memory given a size
void *find_free_block(size_t size) {
        struct block *current = root;
        struct block *find;
        int Find;
        int newsize;
        struct block *node;
        while(current) {
                if(current->Free) {
                        find = (void*) (long) divis_eight(struct_sz + size);
                        Find = find - current - struct_sz;
                        if((current->Size) >= (Find + size)) {
                                current->ptr2 = find;
                                current->Free = 0;
                                break;
                        }
                }
                current = current->next;
                if(current) {
                        newsize = current->Size - Find - struct_sz - size;
                        node = size + find;
                        node->Size = newsize;
                        node->Free = 1;
                        current->Size = size;
                        add_block(node);
                }
        }
        return find;
};
//if no free block, request memory using sbrk
struct block *request_mem(size_t size) {
        //find system page size when request new memory
        int pagesize = sysconf(_SC_PAGESIZE);
        struct block *request;
        size_t sz;
        struct block *Block;
        int size2;
        if((struct_sz + size) <= pagesize) {
                request = sbrk(pagesize);
                if(request == (void*) - 1) {
                        errno = ENOMEM;
                        return NULL;
                }
                request->Size = pagesize;
        }
        else {
                sz = (size/pagesize) + 1;
                request = sbrk(pagesize * sz);
                request->Size = pagesize * sz;
        }
        if(root == NULL) {
                root = request;
                root->next = NULL;
        }
        int newsz;
        newsz = Block - request - struct_sz;
        if((size + newsz) <= request->Size) {
                request->Free = 0;
                request->ptr2 = Block;
                request->next = NULL;
        }
        add_block(request);
        size2 = - newsz - struct_sz - size;
        struct block *node;
        if(struct_sz < size2) {
                node = Block + size;
                node->Size = size2;
                node->Free = 1;
                request->Size = size;
                add_block(node);
        }
        return Block;
};

//called to request a contiguous block of memory
void *malloc(size_t size) {
        void *block;
        if(size < 1) {
                return NULL;
        }
        if(root) {
                block = find_free_block(size);
                if (block == NULL) {
                        block = request_mem(size);
                        if(block == NULL) {
                                return NULL;
                        }
                }
        }
        else {
                block = request_mem(size);
                if(!block) {
                        return NULL;
                }
        }
};

//frees a block of memory previously allocated so it can be reused
void free(void *ptr) {
        struct block *current = root;
        if(ptr) {
                while(current) {
                        if(current->ptr2 == ptr) {
                                current->Free = 1;
                        }
                current = current->next;
                }
        }
};

//sets the allocated memory to zero
void *calloc(size_t num_of_elts, size_t elt_size) {
        size_t sz = num_of_elts * elt_size;
        void *c_ptr = malloc(sz);
        memset(c_ptr, 0, sz);
        return c_ptr;
};