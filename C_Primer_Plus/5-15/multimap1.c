#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cutility.h>

int main(int argc,char* argv[])
{
	multimap_t* pmmap_coll = create_multimap(int,char*);
	multimap_iterator_t it_pos;
	pair_t* ppair_elem = create_pair(int,char*);
	if(pmmap_coll == NULL || ppair_elem ==NULL)
		return -1;

	multimap_init(pmmap_coll);
	pair_init(ppair_elem);

	pair_make(ppair_elem,5,"tagged");
	multimap_insert(pmmap_coll,ppair_elem);

	pair_make(ppair_elem,2,"a");
	multimap_insert(pmmap_coll,ppair_elem);

	pair_make(ppair_elem,1,"this");
	multimap_insert(pmmap_coll,ppair_elem);

	pair_make(ppair_elem,4,"of");
	multimap_insert(pmmap_coll,ppair_elem);

	pair_make(ppair_elem,6,"strings");
	multimap_insert(pmmap_coll,ppair_elem);

	pair_make(ppair_elem,1,"is");
	multimap_insert(pmmap_coll,ppair_elem);

	pair_make(ppair_elem,3,"multimap");
	multimap_insert(pmmap_coll,ppair_elem);

	for(it_pos = multimap_begin(pmmap_coll);!iterator_equal(it_pos,multimap_end(pmmap_coll));it_pos = iterator_next(it_pos))
		printf("%s ",(char*)pair_second(iterator_get_pointer(it_pos)));
	printf("\n");

	multimap_destroy(pmmap_coll);
	pair_destroy(ppair_elem);

	return 0;
}
