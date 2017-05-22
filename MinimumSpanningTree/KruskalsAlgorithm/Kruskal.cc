#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
 
using namespace std;
int leader[std::numeric_limits<int>::max()], nodes, edges;
pair <long, pair<int, int> > p[std::numeric_limits<int>::max()];
 
void initialize()
{
    for(int i = 0;i < MAX;++i)
        leader[i] = i;
}
 
// TODO
// 1) currently this is a very basic algorithm that simply finds the root without using
// better techniques such as union by rank and all. Make that change later.
// 2) also apply path compression while doing this find operation.
int find(int x)
{
    while(leader[x] != x)
    {
        x = leader[x];
    }
    return x;
}
 
// TODO
// 1) choosing random leader from the two groups does not give good performance because
// in the worst case it can go to THETA(n) for find and union operations.
// 2) update code below to make less dense tree the child of more dense tree. This will
// need us to keep "rank" system and "parent" of each node. 
void union(int x, int y)
{
    int p = find(x);
    int q = find(y);
    leader[p] = leader[q];
}
 
long long kruskal(pair<long, pair<int, int> > p[])
{
    int from, to;
    long long cost, minimum_cost = 0;
    for(int i = 0;i < edges;++i)
    {
        // Selecting edges one by one in increasing order from the beginning
        from = p[i].second.first;
        to = p[i].second.second;
        cost = p[i].first;
        // Check if the selected edge is creating a cycle or not
        if(find(from) != find(to))
        {
            minimumCost += cost;
            union(from, to);
        }    
    }
    return minimum_cost;
}
 
int main()
{
    int x, y;
    long weight, cost, minimumCost;
    initialize();
    cin >> nodes >> edges;
    for(int i = 0;i < edges;++i)
    {
        cin >> x >> y >> weight;
        p[i] = make_pair(weight, make_pair(x, y));
    }
    // Sort the edges in the ascending order
    sort(p, p + edges);
    minimumCost = kruskal(p);
    cout << minimumCost << endl;
    return 0;
}