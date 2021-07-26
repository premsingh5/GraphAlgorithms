#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include<iostream>
#include<cmath>

using namespace std;
typedef long long Len;
const Len INF = LLONG_MAX;
typedef vector<vector<vector<int>>> Adj;

// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,less<pair<Len,int>>>> Queue;



class AStar {
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<vector<int>> workset_;
    vector<vector<bool>> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;

public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
        : n_(n), adj_(adj), cost_(cost), distance_(1, vector<Len>(n_, INF)), visited_(n), xy_(xy)
    { workset_.reserve(1); }

    // See the description of this method in the starter for friend_suggestion
   void clear() {
        for (int i = 0; i < workset_[0].size(); ++i) {
            int v = workset_[0][i];
            distance_[0][v] = INF;
            visited_[0][v] = false;
        }
        workset_.clear();
    }
    Len potential(pair<Len,Len> u,pair<Len,Len> v,pair<Len,Len> t){
    	Len x = v.first;
    	Len y = v.second;
    	Len piv = sqrt((pow((v.first-t.first),2)+pow((v.second-t.second),2)));
    	Len piu = sqrt((pow((u.first-t.first),2)+pow((u.second-t.second),2)));
    	
    	return piu-piv;
    	
	}

    // See the description of this method in the starter for friend_suggestion
    // pair<Len,Len> represents distance,key of a node in the graph
   void visit(Queue& q,int v, Len dist) {
    	if(!visited_[0][v]){
    		workset_[0].push_back(v);
			visited_[0][v] = true;
			}
    	if(distance_[0][v]>dist){
    		distance_[0][v] = dist;
    		pair<Len,int> p(dist,v);
    		q[0].push(p);
		}
    }


    // Returns the distance from s to t in the graph.
    Len query(int s, int t) {
        clear();
        Queue q(1);
        visit(q, s, 0);
        int side=0;
        if(s==t)return 0;
        while( !q[0].empty()){
        	pair<Len,int> P = q[0].top();
        	Len dist = P.first;
        	int u = P.second;
        	q[0].pop();
        	int nEdges = adj_[side][u].size();
        	for(int i=0;i<nEdges;i++){
        		Len v = adj_[side][u][i];
        		Len d = dist + cost_[side][u][i]-potential(xy_[u],xy_[v],xy_[t]);
        		int node = adj_[side][v][i];
        		visit(q,node,d);
			}
			}
		if(distance_[0][t]>=INF)return -1;
        else return distance_[0][t]+potential(xy_[s],xy_[t],xy_[t]);
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(1, vector<vector<int>>(n));
    Adj cost(1, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
