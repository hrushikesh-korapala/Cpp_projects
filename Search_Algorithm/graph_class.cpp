#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <list>
#include <queue>
#include <map>

using namespace std;

class Graph
{
private:
    void _init_();
    void dfs(int a);

public:
    map<int, list<int>> adj;
    map<int, bool> visited;

    void add_edge(int a, int b);
    void BFS(int a);
    void DFS(int a);
    void show_graph();
    void BFS_path(int a);
};
void Graph::add_edge(int a, int b)
{
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void Graph::BFS(int s)
{
    _init_();
    visited[s] = true;
    cout << s << ' ';
    queue<int> ans;
    ans.push(s);
    while (!ans.empty())
    {
        s = ans.front();
        ans.pop();
        for (int a : adj[s])
        {
            if (visited[a] == false)
            {
                ans.push(a);
                cout << a << ' ';
                visited[a] = true;
            }
        }
    }
    cout<<endl;
}

void Graph::DFS(int a)
{
    _init_();
    if (visited[a] == true)
    {
        return;
    }
    cout << a << ' ';
    visited[a] = true;
    for (int b : adj[a])
    {
        
        if (visited[b] == false)
        {
            dfs(b);
        }
    }
    cout<<endl;
}

void Graph::dfs(int a)
{
    if (visited[a] == true)
    {
        return;
    }
    cout << a << ' ';
    visited[a] = true;
    for (int b : adj[a])
    {
        
        if (visited[b] == false)
        {
            dfs(b);
        }
    }
    
}

void Graph::show_graph()
{
    for (pair<int, list<int>> a : adj)
    {
        cout << a.first << " : ";
        for (int b : a.second)
        {
            cout << b << ' ';
        }
        cout << endl;
    }
}

void Graph::_init_()
{
    for (map<int, bool>::iterator it = visited.begin(); it != visited.end(); it++)
    {
        it->second = false;
    }
}

void Graph::BFS_path(int a)
{
    _init_();
    int dis=0,s;
    map<int,int> ans;
    queue<int> data;
    data.push(a);
    ans[a]=dis;
    visited[a]=true;
    while(!data.empty())
    {
        s=data.front();
        data.pop();
        dis++;
        for(int b:adj[s])
        {
            if (visited[b]==false)
            {
                data.push(b);
                ans[b]=dis;
                visited[b]=true;
            }
            
        }
    }
}

int main()
{
    Graph g;
    int n, temp1, temp2;
    cin >> n;
    while (n--)
    {
        cin >> temp1 >> temp2;
        g.add_edge(temp1 - 1, temp2 - 1);
    }
    
    return 0;
}