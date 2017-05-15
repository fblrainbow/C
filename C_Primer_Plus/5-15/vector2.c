#include <stdio.h>
#include <string.h>
#include <cstl/cvector.h>

int main(int argc,char* argv[])
{
	vector_t* pvec_coll = create_vector(char);

	if(pvec_coll == NULL)
	{
		return -1;
	}

	vector_init(pvec_coll);
	vector_resize_elem(pvec_coll,30,'\0');

	strcpy((char*)vector_at(pvec_coll,0),"Hello World!");

	printf("%s\n",(char*)vector_front(pvec_coll));

	vector_destroy(pvec_coll);

	return 0;
}




