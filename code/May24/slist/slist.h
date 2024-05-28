typedef struct {
	char * arr ;
	int capacity ;
	int size ;
	size_t usize ;

	int (* cmp)(void *e1, void *e2) ; //cmp=compare /function pointer 

} slist_t ; //sorted list , priority queue (element가 크기 순서로 저장, 작은 ->큰 )

slist_t *
slist_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) ;

void
slist_free (slist_t * heap) ;

int
slist_size (slist_t * heap) ;

int
slist_top (slist_t * heap, void * buf) ;

int
slist_pop (slist_t * heap, void * buf) ;

int
slist_push (slist_t * heap, void * buf) ;
