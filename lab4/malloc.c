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

struct node {
	//contains the size of this node
        size_t Size;

	//the pointer
        void *ptr2;

	//the next node 
        struct node *next;

	//amount of free space
        int Free;
};
struct node *root = NULL; //the root node at the top
#define struct_sz sizeof(struct node)

//add new node to the linked list
//input is a new node
void add_node(struct node *newnode) {
        //previous node
	struct node *prevnode;
	//if the current root is null
        if(root == NULL) {
		//set the current root to the new node
                root = newnode;
		//set the node after to be free/null
                root->next = NULL;
        }
        else {
		//otherwise, set the current node to be the root
                struct node *current = root;
                while(current) {
                        prevnode = current;
                        current = current->next;
                }
                prevnode->next = node;
                node->next = NULL;
        }
};
//round a number upto the nearest multiple of 8
//nodes have an 8 byte boundary
int divis_eight(int n) {
        return ((n - 1)/8 + 1) *  8;
};

//find the node of memory given a size
void *find_free_node(size_t size) {
        struct node *current = root;
        struct node *find;
        int Find;
        int newsize;
        struct node *node;
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
                        add_node(node);
                }
        }
        return find;
};
//if no free nodes, request memory using sbrk
struct node *request_mem(size_t size) {
        //find system page size when request new memory
        int pagesize = sysconf(_SC_PAGESIZE);
        struct node *request;
        size_t sz;
        struct node *Node;
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
	//move pointer
        if(root == NULL) {
                root = request;
                root->next = NULL;
        }

        int newsz;
        newsz = Node - request - struct_sz;
        if((size + newsz) <= request->Size) {
                request->Free = 0;
                request->ptr2 = Node;
                request->next = NULL;
        }
        add_node(request);
        size2 = - newsz - struct_sz - size;
        struct node *node;
        if(struct_sz < size2) {
                node = Node + size;
                node->Size = size2;
                node->Free = 1;
                request->Size = size;
                add_Node(node);
        }
        return Node;
};

//called to request a contiguous node of memory
void *malloc(size_t size) {
        void *node;
        if(size < 1) {
                return NULL;
        }
        if(root) {
                node = find_free_node(size);
                if (node == NULL) {
                        node = request_mem(size);
                        if(node == NULL) {
                                return NULL;
                        }
                }
        }
        else {
                node = request_mem(size);
                if(!node) {
                        return NULL;
                }
        }
};

//frees a node of memory previously allocated so it can be reused
void free(void *ptr) {
        struct node *current = root;
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
