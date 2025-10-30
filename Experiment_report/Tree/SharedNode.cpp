#include<cstdio>
#include<cstdlib>
using namespace std;
int main(){
	unsigned int a,b;
	scanf("%u %u",&a,&b);
	unsigned int c=a&b;
	while((c&1)==0)
		c =c>>1;
	printf("%u ",c);
	return 0;
}