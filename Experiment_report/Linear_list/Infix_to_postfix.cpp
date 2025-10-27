#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/*  Announcement For Exp-1(Postfix and Prefix Expression):
	1.All storage structure indices start from 1 (U neednot consider Head Node of Zero)
	2.the first Node isnot avalable but counted in Sum.
      if you wanna insert an head Node, you ought to start from Subscript-1
      (the head node has subscript-0 !!!!!!)
      replace the head node is considered illegal here
    3.Stack defined by chains always insert from head Node
    4.Pay great attention to Pop sequence and Operating Sequence
    5.When caculate the postfix expression, U must ensure the max result (no matter(in)/direct) are above 128   !!!!!!!
*/
/*  BugAssets:
    1.When release Node memory space , pay great attention that which you have freed.
	 The next one? or the next next to the next one?
	2.When you get "\n",there are still operators in the stack,
	 remember to clear them
	3.When encountering an operator with lower priority,
	first pop out the operator with higher priority.(pay attention to the relationship)


	!!!4.Note the short-circuit principle in the while condition: the check for
	   "not equal to left parenthesis" should be placed in the first position.
	!!!5.Note the order: the Pop operation should be placed in the last condition check;
	otherwise, it will affect the position of elements.
	!!!6.U must pay great attention to condition sequence after 'While'.
	Or you will get an "Array Out Of Bounds" and STUCK there helplessly!

	7.When encountering an operator with lower priority, don't forget to push it
	onto the stack after popping the necessary operators.
*/
/*  Sample:
          2*(9+6/3-5)+4
*/


typedef struct Node * ptr;
typedef char Elementtype;
struct Node {
	Elementtype data;
	ptr next;// (ptr)next is an pointer!
};
char infix[100];//infix expression
char postfix[100];//postfix expression
typedef ptr Position;//for pointer(foront rear)
typedef ptr List;//for definition
typedef enum {
	num,
	opr,
	end
} Type;
Position Findpre(List L,int i);
List Createlist();
int Length(List L);
List Insert(List L,int i,Elementtype X);
void Enumrate(List L);
Elementtype Delete(List L,int i);
void Push(List L,Elementtype X);
Elementtype Pop(List L);

//Experiment-1: Postfix and Infix Expression
void Intopost(char infix[],char postfix[],List L);
Type Getop(char a);
int Calc(int a,int b,char opr);
int Calcpostfix(char postfix[],List L);
void Append(char postfix[],char infix[]);
int Eigen(char a);


int main() {
	List L=Createlist();
	scanf("%s",infix);
	Intopost(infix,postfix,L);
	printf("%s\n",postfix);
	int result=Calcpostfix(postfix,L);
	printf("%d",result);
	return 0;
}
//Experiment-1: Postfix and Infix Expression
int Eigen(char a) { //Assign priority to operators
	if(a=='*')
		return 4;
	if(a=='/')
		return 3;
	if(a=='+')
		return 2;
	if(a=='-')
		return 1;
	if(a=='(')
		return 5;
}
void Append(char postfix[],char c) {
	int len=strlen(postfix);
	postfix[len]=c;
	postfix[len+1]='\0';
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
		printf("%c  ",p->data);
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
void Intopost(char infix[],char postfix[],List L) {
	//Operator in stack
	for(int i=0; i<strlen(infix); i++) {

		if(Getop(infix[i])==num) {
			Append(postfix,infix[i]);// Append single element
		} else if(Getop(infix[i])==opr) {

			if(L->next==NULL||infix[i]=='(')
				Push(L,infix[i]);

			else if(infix[i]==')') {
				char a;
				while((a=Pop(L))!='(') {
					Append(postfix,a);
				}
			} else if(Eigen(infix[i])>=Eigen(L->next->data)) { //compare top stack element
				Push(L,infix[i]);
			} else if(Eigen(infix[i])<Eigen(L->next->data)) {
				char a;
				while(L->next&&L->next->data!='('&&Eigen(a=Pop(L))>=Eigen(infix[i])) {
					//left parenthesis would never get pop for Priority
					Append(postfix,a);
				}
				Push(L,infix[i]);
			}
		}
	}
	while(L->next) {
		Append(postfix,Pop(L));
	}

}
Type Getop(char a) {
	int asc=a;
	if(a<=0x39&&a>=0x30)
		return num;
	else if(a=='+'||a=='-'||a=='*'||a=='/'||a=='('||a==')')
		return opr;
	else if(a=='\0')
		return end;
	else return (Type)-1;
}
int Calc(int a,int b,char opr) {
	if(opr=='+')
		return a+b;
	if(opr=='-')
		return a-b;
	if(opr=='*')
		return a*b;
	if(opr=='/')
		return a/b;
}
int Calcpostfix(char postfix[],List L) {
	for(int i=0; i<strlen(postfix); i++) {
		if(Getop(postfix[i])==num) {
			Push(L,postfix[i]);
		} else if(Getop(postfix[i])==opr) {
			int op1 = Pop(L) - '0';
			int op2 = Pop(L) - '0';
			Push(L,(Calc(op2,op1,postfix[i])+'0'));
		}
	}
	return L->next->data-'0';
	//although U get an Illegal Oprand during opration (like @ # &...),but U finally minus '0',which enable U got correct answer!!
	//Bravo!  Hoooooray！ Woohoo!
}


