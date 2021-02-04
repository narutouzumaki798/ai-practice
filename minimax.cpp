#include <bits/stdc++.h>
using namespace std;

#define INF 100000

vector<int> tree[100];
int value[100];
int n;
int first;
int height;

int generate(int s, int h)
{
    if(h == height-1)
    {
	value[s] = -8 + rand()%19;
	return value[s];
    }

    int children;
    if(rand()%3 > 0) children = 2; // 2/3 chance children = 2
    else children = 3;
    children = 2;

    if((h%2)^first) value[s] = -INF; else value[s] = INF;
    for(int i=0; i<children; i++)
    {
	// printf("child asche : %d\n", n);
	tree[s].push_back(n++);
	if((h%2)^first) value[s] = max(value[s], generate(n-1, h+1));
	else value[s] = min(value[s], generate(n-1, h+1));
    }
    return value[s];
}

void show()
{
    vector<int> q; q.push_back(0);
    vector<int> p;
    int h = 0;
    while(q.size())
    {
	if((h%2)^first) printf("max: ");
	else printf("min: "); h++;
	for(int i=0; i<q.size(); i++)
	{
	    int v = q[i];
	    printf("[");
	    for(int j=0; j<tree[v].size(); j++)
	    {
		printf("%2d ", value[tree[v][j]]);
		p.push_back(tree[v][j]);
	    }
	    printf("]  ");
	}
	printf("\n");
	q.clear();
	for(int i=0; i<p.size(); i++) q.push_back(p[i]);
	p.clear();
	if(h == height) break;
    }
}

void precomp()
{
    for(int i=0; i<100; i++) tree[i].clear();
    tree[0].push_back(1);
    n = 2;
    first = 0;
    height = 5;
}

int main()
{
    srand(time(0));
    precomp();
    generate(1, 0);
    for(int i=0; i<5; i++)
    {
	printf("adj %d: ", i);
	for(int j=0; j<tree[i].size(); j++) printf("%d ", tree[i][j]);
	printf("\n");
    }

    printf("\n\n");
    // if(first == 0) printf("min");
    // else printf("max"); printf("\n");
    show();
    return 0;
}
