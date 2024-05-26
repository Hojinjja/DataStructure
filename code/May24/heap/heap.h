typedef struct {
	char * arr ;
	int capacity ;
	int size ;
	size_t usize ;

	int (* cmp)(void *e1, void *e2) ;

} heap_t ;

heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) ;

void
heap_free (heap_t * heap) ;

int
heap_size (heap_t * heap) ;

int
heap_top (heap_t * heap, void * buf) ;

int
heap_pop (heap_t * heap, void * buf) ;

int
heap_push (heap_t * heap, void * buf) ;

// slist.h와 동일하게 생김 -> heap은 개념 자체가 priority queue와 같음. 
// push와 pop만 차이남