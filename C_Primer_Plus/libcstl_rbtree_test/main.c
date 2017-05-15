#include <stdio.h>
#include <cstl/cset.h>
#include "cstl_rb_tree.h"
#include "cstl_rb_tree_private.h"
#include "cstl_rb_tree_aux.h"
#include "cstl_rb_tree_iterator.h"

void when_creat_rbtree_fail(void)
{
	printf("Launch rbtree root is fail!\n");
}


int main(int argc,char* argv[])
{
	_rb_tree_t* root = NULL;
	char* s_typename = "int";

	root = _create_rb_tree(s_typename);
	if(NULL == root)
	{
		atexit(when_creat_rbtree_fail);
		return -1;
	}

	_rb_tree_init(root,NULL);

	int insert_value = -1;
	printf("Please input a value:");
	while(!scanf("%d",&insert_value))
	{
		while(getchar() != '\n')
			continue;
		printf("Please input again a int type value:");
	}

	_rb_tree_iterator_t _rb_tree_insert_unique(root,insert_value);	
	iterator_t it_begin = 40, it_end = 80;
	_rb_tree_insert_unique_range(root,it_begin,it_end);


	printf("Success!\n");
	return 0;
}






