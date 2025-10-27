#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//Experiment-2: Dequeue Operetion
/*	Announcement:
	1.We define the first Node as CONST empty
	2.In order to prevent the rear exceed front, we must break when ISFULL!
*/
#define MAXSIZE 10
typedef struct Qnode *ptr;
typedef ptr Deque ;
typedef int Position;

struct Qnode {
	int data[MAXSIZE];
	Position front,rear;
};
Deque Createdeque();
bool Isempty(Deque);
bool Push_deque(Deque,int);
int Pop_deque(Deque);
bool Inject_deque(Deque,int);
int Eject_deque(Deque);
void Enumerate(Deque);
int main() {
	//Following are test code:
	Deque D=Createdeque();
	for(int i=1;i<=3;i++){
		Enumerate(D);
		if(!Push_deque(D,i))
		break;
	}
	for(int i=10;i<=17;i++){
		Enumerate(D);
		if(!Inject_deque(D,i))
		break;
	}
	
	printf("---------------\n");
	Eject_deque(D);
	Pop_deque(D);
	Enumerate(D);
	return 0;
}

//Experiment-2: Dequeue Operetion
void Enumerate(Deque D){
	for(int i=0;i<MAXSIZE;i++)
	printf("%d ",D->data[i]);
	printf("\n");
}
Deque Createdeque() {
	Deque D=(Deque)malloc(sizeof(Qnode));
	D->front=0;
	D->rear=0;
	memset(D->data,0,sizeof(D->data));
	return D;
}
bool Isempty(Deque D) {
	return (D->front==D->rear);
}
bool Isfull(Deque D) {
	return ((D->rear+1)%MAXSIZE==D->front);
}
bool Push_deque(Deque D,int X) { //front-in
	if(Isfull(D)) {
		printf("QUEUE IS ALREADY FULL\n");
		return false;
	} else {
		D->data[D->front]=X;
		D->front=(D->front-1+MAXSIZE)%MAXSIZE;
		return true;
	}
	//PS:here is little different from Powerpoint.we assert the first node is NULL
}
int Pop_deque(Deque D) { //front-out
	if(Isempty(D)) {
		printf("QUEUE IS EMPTY\n");
		return false;
	} else {
		D->front=(D->front+1)%MAXSIZE;
		D->data[D->front]=0x00;
	}
}
bool Inject_deque(Deque D,int X) { //rear-in
	if(Isfull(D)) {
		printf("QUEUE IS ALREADY FULL\n");
		return false;
	} else {
		D->rear=(D->rear+1)%MAXSIZE;
		D->data[D->rear]=X;
		return true;
	}
}
int Eject_deque(Deque D) { //rear-out
	if(Isempty(D)) {
		printf("QUEUE IS EMPTY\n");
		return false;
	} else {
		D->data[D->rear]=0x00;
		D->rear=(D->rear+MAXSIZE-1)%MAXSIZE;
		return true;
	}
}