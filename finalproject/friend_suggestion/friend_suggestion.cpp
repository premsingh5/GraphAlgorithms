#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include<iostream>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,less<pair<Len,int>>>> Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<vector<int>> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // by forward in visited_[0] and othewise backward search.
    vector<vector<bool>> visited_;

public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(2,vector<bool>(n,false)),
     workset_(2,vector<int>(0,0))   
    {workset_.reserve(2);}

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear() {
        for (int i = 0; i < workset_[0].size(); ++i) {
            int v = workset_[0][i];
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[0][v] = false;
        }
        for(int j=0;j<workset_[1].size();++j){
        	int v = workset_[1][j];
        	distance_[0][v] = distance_[1][v] = INFINITY;
        	visited_[1][v] = false;
		}
        workset_.clear();
    }

    // Processes visit of either forward or backward search 
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue& q, int side, int v, Len dist) {
    	if(!visited_[side][v]){
    		workset_[side].push_back(v);
			visited_[side][v] = true;
			}
    	if(distance_[side][v]>dist){
    		distance_[side][v] = dist;
    		pair<Len,int> p(dist,v);
    		q[side].push(p);
		}
    }
    int Reverse(int side){
    	if(side==0)return 1;
    	else return 0;
	}

    // Returns the distance from s to t in the graph.
    Len query(int s, int t) {
        clear();
        Queue q(2);
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
        int side=0;
        if(s==t)return 0;
        while( !q[0].empty() && !q[1].empty()){
        	pair<Len,int> P = q[side].top();
        	Len dist = P.first;
        	int v = P.second;
        	q[side].pop();
        	int source;
        	if(side==0)source = s;
        	if(side==1)source = t;
        	int reverse = Reverse(side);
        	if(visited_[reverse][v]){
        		cout<<"v:"<<v+1<<endl;
        		Len m = INFINITY;
        		cout<<m<<endl;
        		for(int i=0;i<workset_[0].size();i++){
        			int node = workset_[0][i];
        			Len k = distance_[0][node]+distance_[1][node];
        			cout<<node<<" "<<k<<" "<<distance_[0][node]<<" "<<distance_[1][node]<<endl;
        			if(k<m)m = k;
				}
				for(int i=0;i<workset_[1].size();++i){
					int node = workset_[1][i];
        			Len k = distance_[0][node]+distance_[1][node];
        			cout<<node<<" "<<k<<" "<<distance_[0][node]<<" "<<distance_[1][node]<<endl;
        			if(k<m)m = k;
				}
				clear();
				std::cout<<"m:"<<m<<endl;
				if(m<INFINITY)return m;
			}
        	else{
        		int nEdges = adj_[side][v].size();
        		for(int i=0;i<nEdges;i++){
        			Len d = dist + cost_[side][v][i];
        			int node = adj_[side][v][i];
        			visit(q,side,node,d);
				}
				side = Reverse(side);	
			}
			
		}
        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("dist is: %lld\n", bidij.query(u-1, v-1));
    }
}
