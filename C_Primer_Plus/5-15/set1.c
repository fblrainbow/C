#include <stdio.h>
#include <cstl/cset.h>

int main(int argc,char* argv[])
{
	set_t* pset_coll = create_set(int);
	set_iterator_t it_pos;
	if(pset_coll == NULL)
		return -1;

	set_init(pset_coll);
	set_insert(pset_coll,3);
	set_insert(pset_coll,1);
	set_insert(pset_coll,6);
	set_insert(pset_coll,4);
	set_insert(pset_coll,1);
	set_insert(pset_coll,2);
	set_insert(pset_coll,5);

	for(it_pos = set_begin(pset_coll);!iterator_equal(it_pos,set_end(pset_coll));it_pos = iterator_next(it_pos))
		printf("%d",*(int*)iterator_get_pointer(it_pos));
	printf("\n");

	set_destroy(pset_coll);

	return 0;
}	
