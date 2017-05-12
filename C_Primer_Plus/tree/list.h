#include <stdio.h>
#include <string.h>

typedef struct node{
	struct node* Lchild;
	int data;
	struct node* Rchild;
}Node;

typedef Node* BinaryTreeList;

void InitBinaryTree(BinaryTreeList 
Insert(Node* Root,int n);

void Delete(Node* temp);

Node Search(const Node* Root);
