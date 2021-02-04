#include <bits/stdc++.h>
using namespace std;

#define INFORMED 1

string board;
deque<string> open;
deque<string> closed;
map<string, int> visited;
map<string, int> heuristic;
map<string, string> back;
string reached;
int itr;
map<string, int> id;

int e_idx(string curr)
{
    for(int i=0; i<curr.size(); i++)
	if(curr[i] == 'E') return i;
    return -1;
}

int valid(string c)
{
    if(c.size() != 7) return 0;
    int f = 0;
    for(int i=0; i<c.size(); i++) 
    {
	if(c[i] != 'W') continue; // iterate through w cells
	for(int j=0; j<c.size(); j++)
	{
	    if(c[j] != 'B') continue; // iterate through b cells
	    if(j <= i) f = 1;
	}
	if(f == 1) break;
    }
    if(f == 1) return 0;
    return 1;
}

int calc_heuristic(string curr)
// sum over each Wi { number of B to the left of Wi }
{
    int ans = 0;
    for(int i=0; i<curr.size(); i++) 
    {
	if(curr[i] != 'W') continue; // iterate over W
	for(int j=0; j<curr.size(); j++)
	{
	    if(curr[j] != 'B') continue; // iterate over B
	    if(j < i) ans++;
	}
    }
    return ans;
}
bool comp(string a, string b)
{
    return (heuristic[a] < heuristic[b]);
}

void bfs()
{
    open.push_back(board); visited[board] = 0;
    while(open.size())
    {
	string curr = open[0];
	open.pop_front();
	closed.push_back(curr);

	int e = e_idx(curr);
	int t;
	string curr_backup = curr;

	for(int i=-3; i<=3; i++) // curr node er children add korte hobe open e
	{
	    if(i == 0)  continue;
	    t = e + i; // tile to hop
	    if(t < 0 || t >= 7) continue; // outside board

	    int cost = visited[curr] + abs(i)-1;
	    curr[e] = curr[t]; curr[t] = 'E'; // hop
	    if(visited.find(curr) == visited.end())
	    {
		open.push_back(curr);
		visited[curr] = cost;
		back[curr] = curr_backup;
	    }
	    curr[t] = curr[e]; curr[e] = 'E'; // undo hop
	}

	printf("board: %s cost: %d\n", curr.c_str(), visited[curr]);
	printf("OPEN: ");
	for(int i=0; i<open.size(); i++)
	{
	    printf("%s, ", open[i].c_str());
	}
	printf("\nvisited: %d", closed.size());
	printf("\n\n");

	if(valid(curr))
	{
	    reached = curr;
	    break; // reached   
	}
    }
}
void informed()
{
    open.push_back(board); visited[board] = 0;
    while(open.size())
    {
	string curr = open[0];
	open.pop_front();
	closed.push_back(curr);


	int e = e_idx(curr);
	int t;
	string curr_backup = curr;

	for(int i=-3; i<=3; i++) // curr node er children add korte hobe open e
	{
	    if(i == 0)  continue;
	    t = e + i; // tile to hop
	    if(t < 0 || t >= 7) continue; // outside board

	    int cost = visited[curr] + abs(i)-1;
	    curr[e] = curr[t]; curr[t] = 'E'; // hop
	    if(visited.find(curr) == visited.end())
	    {
		open.push_back(curr);
		visited[curr] = cost;
		heuristic[curr] = calc_heuristic(curr);
		back[curr] = curr_backup;
		id[curr] = itr;
	    }
	    curr[t] = curr[e]; curr[e] = 'E'; // undo hop
	}


	// reorder open
	sort(open.begin(), open.end(), comp);

	printf("%d. board: %s cost: %d  parent: %d[%s]\n", itr, curr.c_str(),
	       visited[curr], id[curr], back[curr].c_str()); itr++;
	printf("OPEN: ");
	for(int i=0; i<open.size(); i++)
	{
	    printf("%s, ", open[i].c_str());
	}
	printf("\nheuristic: %d visited: %d", calc_heuristic(curr), closed.size());
	printf("\n\n");

	if(valid(curr))
	{
	    reached = curr;
	    break; // reached
	}
    }
}

void show_board(string a)
{
    for(int i=0; i<a.size(); i++)
    {
	if(a[i] == 'E') printf(".");
	else printf("%c", a[i]);
    }
}

vector<string> path;
int main()
{
    printf("tree:\n\n");
    board = "BBBWWWE";
    itr = 0;
    if(INFORMED)
	informed();
    else
	bfs();
    printf("path:\n\n");

    string t = reached;
    while(1)
    {
	path.push_back(t);
	if(t == board) break;
	t = back[t];
    }
    for(int i=path.size()-1; i>=0; i--)
    {
	show_board(path[i]);
	printf(" cost: %d\n", visited[path[i]]);
    }
    return 0;
}
