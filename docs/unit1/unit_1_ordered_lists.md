# Unit 1: Ordered Lists

## Insertion Cases

Four boundary conditions:
1. **Empty list**
2. **Insert at beginning**
3. **Insert in middle**
4. **Insert at end**

```c
void insert_list(mylist_t* ptr_list, int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->next_ = NULL;
    
    if (ptr_list->head == NULL) {  // Empty
        ptr_list->head = temp;
    } else {
        node_t* prev = NULL;
        node_t* pres = ptr_list->head;
        while (pres != NULL && pres->key_ < temp->key_) {
            prev = pres;
            pres = pres->next_;
        }
        if (prev == NULL) {  // Beginning
            temp->next_ = pres;
            ptr_list->head = temp;
        } else {  // Middle or end (same code!)
            temp->next_ = pres;
            prev->next_ = temp;
        }
    }
}
```

---