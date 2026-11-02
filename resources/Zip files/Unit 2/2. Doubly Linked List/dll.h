#ifndef DLL_H
#define DLL_H
struct node {
	
    int key_;
    struct node *prev_;
    struct node *next_;
};
typedef struct node node_t;

struct DLL {
	node_t *head_;
	node_t *tail_;
};
typedef struct DLL dll_t;
void init_dll(dll_t *ptr_dll);
void deinit_dll(dll_t *ptr_dll);
void insert_begin(dll_t *ptr_dll, int key);
void insert_end(dll_t* ptr_dll, int key);
void disp_forward(dll_t *ptr_dll);
void disp_backward(dll_t *ptr_dll);
void insert_after(dll_t *ptr_dll, int key1, int key2);
void delete_begin(dll_t *ptr_dll);
void delete_end(dll_t *ptr_dll);
void delete_value(dll_t *ptr_dll, int key);

#endif