#include <bits/stdc++.h>
using namespace std;

int n, m;
char maze[100][100];
int visited[100][100];
deque<pair<int, int>> open;
deque<pair<int, int>> closed;
int h[100][100]; // heruristic
int targety, targetx;
int starty, startx;
pair<int, int> back[100][100];
vector<pair<int, int>> path;

#define INFORMED 1

int inside(int i, int j)
{
    if(i < 0) return 0;
    if(j < 0) return 0;
    if(i >= n) return 0;
    if(j >= m) return 0;
    return 1;
}
void bfs()
{
    int y = 0, x = 1;
    open.push_back({y, x}); visited[y][x] = 1;
    while(open.size())
    {
	y = open[0].first;
	x = open[0].second;
	open.pop_front();
	closed.push_back({y, x});

	int tx, ty;

	tx = x+1, ty = y;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{ open.push_back({ty, tx}); visited[ty][tx] = 1;
	    back[ty][tx] = {y, x}; }
	tx = x-1, ty = y;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{ open.push_back({ty, tx}); visited[ty][tx] = 1;
	    back[ty][tx] = {y, x}; }
	tx = x, ty = y+1;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{ open.push_back({ty, tx}); visited[ty][tx] = 1;
	    back[ty][tx] = {y, x}; }
	tx = x, ty = y-1;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{ open.push_back({ty, tx}); visited[ty][tx] = 1;
	    back[ty][tx] = {y, x}; }

	// display maze
	for(int i=0; i<n; i++)
	{
	    for(int j=0; j<m; j++)
	    {
		if(i == y && j == x)
		    printf("P");
		else
		    printf("%c", maze[i][j]);
	    }
	    printf("\n");
	}
	printf("Open: ");
	for(int i=0; i<open.size(); i++)
	    printf("(%d, %d), ", open[i].first, open[i].second);
	printf("\n");
	printf("Closed: ");
	for(int i=0; i<closed.size(); i++)
	    printf("(%d, %d), ", closed[i].first, closed[i].second);
	printf("\nvisited: %d\n", closed.size());
	printf("\n\n");


	if(y == targety && x == targetx)
	{
	    printf("\n\nREACHED\n\n");
	    break; // reached exit
	}
    }
}

int manhatt(int ay, int ax, int by, int bx)
{
    int ans = abs(by - ay) + abs(bx - ax);
    return ans;
}

bool comp(pair<int, int> a, pair<int, int> b)
{
    return (h[a.first][a.second] < h[b.first][b.second]);
}

void informed()
{
    int y = 0, x = 1;
    open.push_back({y, x}); visited[y][x] = 1;
    while(open.size())
    {
	y = open[0].first;
	x = open[0].second;
	open.pop_front();
	closed.push_back({y, x});

	int tx, ty;

	tx = x+1, ty = y;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{
	    open.push_back({ty, tx}); visited[ty][tx] = 1;
	    h[ty][tx] = manhatt(ty, tx, starty, startx) + manhatt(ty, tx, targety, targetx);
	    back[ty][tx] = {y, x};
	}
	tx = x-1, ty = y;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{
	    open.push_back({ty, tx}); visited[ty][tx] = 1;
	    h[ty][tx] = manhatt(ty, tx, starty, startx) + manhatt(ty, tx, targety, targetx);
	    back[ty][tx] = {y, x};
	}
	tx = x, ty = y+1;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{
	    open.push_back({ty, tx}); visited[ty][tx] = 1;
	    h[ty][tx] = manhatt(ty, tx, starty, startx) + manhatt(ty, tx, targety, targetx);
	    back[ty][tx] = {y, x};
	}
	tx = x, ty = y-1;
	if(inside(ty, tx) && maze[ty][tx] != '#' && !visited[ty][tx])
	{
	    open.push_back({ty, tx}); visited[ty][tx] = 1;
	    h[ty][tx] = manhatt(ty, tx, starty, startx) + manhatt(ty, tx, targety, targetx);
	    back[ty][tx] = {y, x};
	}


	// reorder open
	sort(open.begin(), open.end(), comp);

	// display maze
	for(int i=0; i<n; i++)
	{
	    for(int j=0; j<m; j++)
	    {
		if(i == y && j == x)
		    printf("P");
		else
		    printf("%c", maze[i][j]);
	    }
	    printf("\n");
	}
	printf("Open: ");
	for(int i=0; i<open.size(); i++)
	    printf("(%d, %d)[%d], ", open[i].first, open[i].second, h[open[i].first][open[i].second]);
	printf("\n");
	printf("Closed: ");
	for(int i=0; i<closed.size(); i++)
	    printf("(%d, %d), ", closed[i].first, closed[i].second);
	printf("\nvisited: %d\n", closed.size());
	printf("\n\n");

	if(y == targety && x == targetx) 
	{
	    printf("\n\ntargety: %d targetx: %d\n", targety, targetx);
	    printf("y: %d x: %d\n", y, x);
	    printf("REACHED\n\n");
	    break; // reached exit
	}
    }

}

void reset()
{
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    visited[i][j] = 0;
	    h[i][j] = 100000;
	}
    }
    open.clear();
    closed.clear();
}

void display(int r, int c)
{
    for(int i=0; i<n; i++)
    {
	for(int j=0; j<m; j++)
	{
	    if(i == r && j == c)
		printf("P");
	    else printf("%c", maze[i][j]);
	}
	printf("\n");
    }
    printf("\n\n");
}

int main()
{
    cin >> n >> m;
    for(int i=0; i<n; i++)
	for(int j=0; j<m; j++)
	    cin >> maze[i][j];
    reset();
    startx = 1; starty = 0;
    targetx = m-1; targety = 1;

    printf("tree:\n\n");
    if(INFORMED) informed();
    else bfs();

    printf("path:\n\n");
    int curr_y = targety, curr_x = targetx;
    while(1)
    {
	path.push_back({curr_y, curr_x});
	if(curr_y == starty && curr_x == startx) break;
	int next_y = back[curr_y][curr_x].first;
	int next_x = back[curr_y][curr_x].second;
	curr_y = next_y; curr_x = next_x;
    }
   for(int i=path.size()-1; i>=0; i--)
   {
	display(path[i].first, path[i].second);
   }
   printf("cost: %d\n\n", path.size());

    return 0;
}

