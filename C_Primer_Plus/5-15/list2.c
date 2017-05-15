#include <stdio.h>
#include <cstl/clist.h>
int main(int argc,char* argv[])
{
	list_t* plist_coll = create_list(char);
	list_iterator_t it_pos;
	char c = '\0';

	if(plist_coll == NULL)
	{
		return -1;
	}

	list_init(plist_coll);

	for(c = 'a';c <= 'z';++c)
	{
		list_push_back(plist_coll,c);
	}
	for(it_pos = list_begin(plist_coll);!iterator_equal(it_pos,list_end(plist_coll));it_pos = iterator_next(it_pos))
	{
		printf("%c",*(char*)iterator_get_pointer(it_pos));
	}
	printf("\n");

	list_destroy(plist_coll);

	return 0;
}
