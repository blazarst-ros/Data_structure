#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/*	Announcemen For Experiment-3:
	1.Given the linked list to be reversed and the head and tail pointers of its segments; Then do the partial reverse
	2.Do not forgrt to use Temp to record position when reversing
	3.'front' points to the one before first node (NULL Node)
	4.Getpoint will get the next node after the sequence
*/
typedef struct Node * ptr;
typedef int Elementtype;
struct Node {
	Elementtype data;
	ptr next;// (ptr)next is an pointer!
};
typedef ptr Position;//for pointer(foront rear)
typedef ptr List;//for definition

Position Findpre(List L,int i);
List Createlist();
int Length(List L);
List Insert(List L,int i,Elementtype X);
void Enumrate(List L);
Elementtype Delete(List L,int i);
void Push(List L,Elementtype X);
Elementtype Pop(List L);
Position Segreverse(List L,Position head,int k);
Position Getpoint(Position front,List L,int k);

int main() {
	int k,n;
	List L=Createlist();
	scanf("%d",&k);
	for(int i=1; i<=15; i++)
		Push(L,i);
	Enumrate(L);
	printf("\n");
	n=Length(L)/k;

	Position p=L;
	while(n--) {
		p=Segreverse(L,p,k);
	}
//	Segreverse(L,p,Length(L)-n*k-1);
	Enumrate(L);
//    int a=Getpoint(L,L,3)->data;
//    printf("%d",a);
	return 0;
}
Position Getpoint(Position front,List L,int k) {
	Position p=front;
	while(k--&&p->next) {
		p=p->next;
	}
	  return p->next;
}
Position Segreverse(List L,Position front,int k) {
	int kcnt=k;
	Position newhead,oldhead,temp;
	Position recordrear;
	oldhead=front->next;
	newhead=Getpoint(front,L,k);

	while(kcnt>0) {

		temp=oldhead->next;
		oldhead->next=newhead;
		newhead=oldhead;
		oldhead=temp;
		if(kcnt==k)
			recordrear=newhead;
		kcnt--;
	}
	front->next=newhead;
	return recordrear;
	//what returns is what next 'front'
}
Position Findpre(List L,int i) { //this function will return element pointer before i
	int cnt=0;
	Position pre=L;
	while(!pre->next&&cnt<i-1) {
		pre=pre->next;
		cnt++;
	}
	return pre;
	//cnt and pre finally stopped before the target

}
List Createlist() {
	List L=(ptr)malloc(sizeof(struct Node));
	L->data='0'; //set the Head Node as NLL
	L->next=NULL;
	return L;
}
int Length(List L) {
	Position p=L;
	int cnt=0;
	while(p) {
		p=p->next;
		cnt++;
	}
	return cnt-1;//cnt is the number of member(but head node)
}
List Insert(List L,int i,Elementtype X) { // insert before element i (1~n)
	Position temp,pre;
	temp=(ptr)malloc(sizeof(struct Node));
	temp->data=X;
	pre=Findpre(L,i);
	temp->next=pre->next;
	pre->next=temp;
	return L;
}
void Enumrate(List L) {
	Position p=L->next;
	while(p) {
		printf("%d  ",p->data);
		p=p->next;
	}
	printf("\n");
	return;
}
Elementtype Delete(List L,int i) { //delete the member sequened i
	Position pre=Findpre(L,i);
	if(pre->next) {
		Position temp=pre->next;
		Elementtype q=temp->data;
		pre->next=temp->next;
		free(temp);
		return q;
	} else
		return -100000;
}
void Push(List L,Elementtype X) {
	Insert(L,1,X);
}
Elementtype Pop(List L) {
	if(L->next!=NULL) {
		return Delete(L,1);
	}
	return -10000;
}