#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#define MAXSIZE 100
using namespace std;
char Tree[MAXSIZE];
char Pre[MAXSIZE];
int pointer=0;
int n;
int Levelwidth[10];
void fill(char Tree[],int pos);
int check(int i);
int pow1(int a,int b);
int main() {
	for(int i=0; i<=MAXSIZE; i++)
		Tree[i]='0';
	scanf("%s",Pre);
	n=strlen(Pre);
	fill(Tree,1);
//	for(int i=1; i<MAXSIZE; i++)
//		printf("%c",Tree[i]);//transferred success
	printf("\n");
	int i=1,m=-100000;
	while(1) {
		int temp=check(i);
		m=m>temp?m:temp;
		i++;
		if(temp==0)
			break;
	}
	printf("Max Width %d",m);
	return 0;
}
//pos points to where to be filled (Tree array)
void fill(char Tree[],int pos) {
	if(pointer>=n||pos>=MAXSIZE)
		return ;
	Tree[pos]=Pre[pointer];
	pointer++;
	if(Tree[pos]=='0')
		return;//without subtree
	fill(Tree,2*pos);
	fill(Tree,2*pos+1);
}
int check(int i) {
	int cnt=0;
	for(int a=pow1(2,i-1); a<=pow1(2,i)-1; a++)
		if(Tree[a]!='0')
			cnt++;
	return cnt;
}
int pow1(int a,int b){
	int p=1;
	for(int i=1;i<=b;i++)
		p*=a;
	return p;
}