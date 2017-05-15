#!/bin/sh
gcc cstl_rb_tree_aux.c cstl_rb_tree.c cstl_rb_tree_iterator.c cstl_rb_tree_private.c main.c -o rb -lcstl
