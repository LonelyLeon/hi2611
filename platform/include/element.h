 #ifndef __ELEMENT_H
 #define __ELEMENT_H
 
#ifdef __cplusplus
extern "C" {
#endif

#define HEAD(l)  ((l)->l_head)
#define TAIL(l)  ((l)->l_tail)
#define PREV(n)  ((n)->e_prev)
#define NEXT(n)  ((n)->e_next)

typedef struct element_s {
  struct element_s* e_next;
  struct element_s* e_prev;
} element_t;

typedef struct list_s {
  struct element_s* l_head;
  struct element_s* l_tail;
} list_t;

void init_list(list_t *);

void add_head(list_t *, element_t *);
void add_tail(list_t *, element_t *);
void insert_element(element_t *,element_t *);

element_t *rem_head(list_t *);
element_t *rem_tail(list_t *);
element_t *rem_element(element_t *);

int is_empty(list_t *);

#define LIST_CONTENT(_s, _t, _e)     (_s*)((unsigned char*)_e - (unsigned char*)(&((_s*)0)->_t))

#ifdef __cplusplus
}
#endif
#endif
