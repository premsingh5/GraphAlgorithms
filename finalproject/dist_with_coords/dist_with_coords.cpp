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
// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type


// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,less<pair<Len,int>>>> Queue;



class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
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
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n_, INF)), visited_(n), xy_(xy)
    { workset_.reserve(n); }

    // See the description of this method in the starter for friend_suggestion
   void clear() {
        for (int i = 0; i < workset_[0].size(); ++i) {
            int v = workset_[0][i];
            distance_[0][v] = distance_[1][v] = INF;
            visited_[0][v] = false;
        }
        for(int j=0;j<workset_[1].size();++j){
        	int v = workset_[1][j];
        	distance_[0][v] = distance_[1][v] = INF;
        	visited_[1][v] = false;
		}
        workset_.clear();
    }
    Len potential(pair<Len,Len> u,pair<Len,Len> v,pair<Len,Len> s,pair<Len,Len> t){
    	Len x = v.first;
    	Len y = v.second;
    	Len piv = sqrt((pow((v.first-t.first),2)+pow((v.second-t.second),2)));
    	Len piu = sqrt((pow((u.first-t.first),2)+pow((u.second-t.second),2)));
    	Len pivr = sqrt((pow((v.first-s.first),2)+pow((v.second-s.second),2)));
    	Len piur = sqrt((pow((u.first-s.first),2)+pow((u.second-s.second),2)));
    	Len pfu  = (piu-piur)/2;
    	Len pfv  = (piv-pivr)/2;
    	return pfv-pfu;
    	
	}

    // See the description of this method in the starter for friend_suggestion
    // pair<Len,Len> represents distance,key of a node in the graph
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

    // Returns the distance from s to t in the graph
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
        	int u = P.second;
        	q[side].pop();
        	int source;
        	if(side==0)source = s;
        	if(side==1)source = t;
        	int reverse = Reverse(side);
        	if(visited_[reverse][u]){
        		Len m = INF;
        		cout<<m<<endl;
        		for(int i=0;i<workset_[0].size();i++){
        			int node = workset_[0][i];
        			Len k = distance_[0][node]+distance_[1][node];
        			if(k<m)m = k;
				}
				for(int i=0;i<workset_[1].size();++i){
					int node = workset_[1][i];
        			Len k = distance_[0][node]+distance_[1][node];
        			if(k<m)m = k;
				}
				clear();
				if(m<INF)return m;
			}
        	else{
        		int nEdges = adj_[side][u].size();
        		for(int i=0;i<nEdges;i++){
        			Len v = adj_[side][u][i];
        			Len d = dist + cost_[side][u][i]+potential(xy_[u],xy_[v],xy_[s],xy_[t]);
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
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
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

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
