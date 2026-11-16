# Unit 1: List with Header Node

## Concept

Add a **dummy header node** at start:
- Empty list has header node (next = NULL)
- Eliminates special cases for empty list and insert at beginning
- Insertion code becomes simpler

```c
void init_list(mylist_t* ptr_list) {
    ptr_list->head_ = (node_t*)malloc(sizeof(node_t));
    ptr_list->head_->next_ = NULL;
}

void insert_list(mylist_t* ptr_list, int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->next_ = NULL;
    
    // Traverse from header
    node_t* prev = ptr_list->head_;
    node_t* pres = ptr_list->head_->next_;
    
    while (pres != NULL && pres->key_ < temp->key_) {
        prev = pres;
        pres = pres->next_;
    }
    
    // Same code for middle AND end!
    temp->next_ = pres;
    prev->next_ = temp;
}
```

---