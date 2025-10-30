/* 
	1.  the core idea: different subtree use different in_sequence and post_sequence
 U only need to adjust pointer to point appropriate position!
	2.  one neednot to know where to end ,only to know where to 
    start and the number(get by root_node) is enough!
*/
#include<cstdio>
#include<cstdlib>
#define MAXSIZE 1000
using namespace std;
int post[MAXSIZE];
int in[MAXSIZE];
int n;
typedef  struct tnode* Position;
typedef Position Tree;
struct tnode{
	int data;
	Position left;
	Position right;	
};
Tree Create(int* in ,int* post,int num);
void Pretraversal(Tree T);
bool BST(int* in ,int num);
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&in[i]);
	for(int i=0;i<n;i++)
		scanf("%d",&post[i]);
	
	Tree T=Create(in,post,n);
	Pretraversal(T);
	printf("\nWhether or not ? %d",BST(in,n));	
	return 0;
}
Tree Create(int *in,int *post,int num){
//num is the number of trees in subtree 
	if(num==0)
		return NULL;
	Tree T=(Tree)malloc(sizeof(struct tnode));
	T->data=post[num-1];
	T->left=NULL;
	T->right=NULL;//no load when creating
	int p=-1;
	while(in[++p]!=post[num-1]);
	T->left=Create(in,post,p);
	T->right=Create(in+p+1,post+p,num-p-1);
	return T;
	
}
void Pretraversal(Tree T){
	if(!T)
	return;
	else{
		printf("%d ",T->data);
		Pretraversal(T->left);
		Pretraversal(T->right);
	}
}
bool BST(int *in,int num){
	int i=1;
	while(in[i]<=in[++i]&&i<=num);
	return (num==i);
}
