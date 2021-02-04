#include <bits/stdc++.h>
using namespace std;

#define int long long

#undef int
int main()
#define int long long
{
   
    int tt = 1000;
    while(tt--)
    {
	int w[8];
	for(int i=1; i<=7; i++) w[i] = rand()%10-5;
	int a = 0, b = 0, d, e, ans, flag=0;

	a=0; b=0; ans = a^b;
	d = w[1]*a + w[2]*b + w[6]*1; if(d < 0) d = 0;
	e = w[5]*1 + w[3]*a + w[4]*b + w[7]*d; if(e <= 0) e = 0; else e = 1;
	if(e != ans) flag = 1;

	a=0; b=1; ans = a^b;
	d = w[1]*a + w[2]*b + w[6]*1; if(d < 0) d = 0;
	e = w[5]*1 + w[3]*a + w[4]*b + w[7]*d; if(e <= 0) e = 0; else e = 1;
	if(e != ans) flag = 1;

	a=1; b=0; ans = a^b;
	d = w[1]*a + w[2]*b + w[6]*1; if(d < 0) d = 0;
	e = w[5]*1 + w[3]*a + w[4]*b + w[7]*d; if(e <= 0) e = 0; else e = 1;
	if(e != ans) flag = 1;

	a=1; b=1; ans = a^b;
	d = w[1]*a + w[2]*b + w[6]*1; if(d < 0) d = 0;
	e = w[5]*1 + w[3]*a + w[4]*b + w[7]*d; if(e <= 0) e = 0; else e = 1;
	if(e != ans) flag = 1;

	if(!flag)
	{
	    printf("xor ache\n");
	    for(int i=1; i<=7; i++) printf("w[%lld]=%lld ", i, w[i]); printf("\n");
	}
    }
    printf("\n\n");
    return 0;
}

