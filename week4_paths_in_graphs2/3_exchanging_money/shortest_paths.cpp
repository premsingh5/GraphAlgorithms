#include <iostream>
#include <limits>
#include <vector>
#include <list>
#include <queue>
#include<utility>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

void explore(vector<vector<int>> &adj,vector<bool>&isexplored,int node){
	int m = adj[node].size();
	isexplored[node] = true;
	//cout<<"node:"<<node<<endl;
	for(int i=0;i<m;i++){
		if(!isexplored[adj[node][i]]){
			explore(adj,isexplored,adj[node][i]);
		}
	}
}
pair<int,int> RelaxAll(vector<vector<int>> &adj,vector<vector<int>> &cost,vector<long long int> &dist,vector<int>& prev,vector<int>& reachable,int s,int iteration){
	int n = adj.size();
	vector<bool>isRelaxed(n,false);
	queue<int,list<int>> Q;
	pair<int,int>p = make_pair(-1,-1);
	dist[s] = 0;
	reachable[s] = 1;
	Q.push(s);
	while(!Q.empty()){
		int e = Q.front();
		Q.pop();
		isRelaxed[e]=true;
		int m = adj[e].size();
		for(int i=0;i<m;i++){
			if(iteration==0){
			reachable[adj[e][i]]=1;
			}
			if(dist[adj[e][i]]>dist[e]+cost[e][i]){
				p = make_pair(e,adj[e][i]);
				dist[adj[e][i]] = dist[e]+cost[e][i];
				prev[adj[e][i]] = e;
			}
			if(!isRelaxed[adj[e][i]]){
			Q.push(adj[e][i]);
			}
		}	
	}
	return p;
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<long long int> &dist,vector<int> &reachable,vector<int>&prev,int s,pair<int,int>&relaxed) {
	int n = adj.size();
	for(int i=0;i<n;i++){
		relaxed = RelaxAll(adj,cost,dist,prev,reachable,s,i);
	}
	if(relaxed.first!=-1)return 1;
    return 0;
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
	pair<int,int>relaxed = make_pair(-1,-1);
	int n = adj.size();
	vector<int>prev(n,-1);
	int t = negative_cycle(adj,cost,distance,reachable,prev,s,relaxed);
	if(t){
		int x,y=relaxed.second;
		for(int i=0;i<n;i++){
			x = prev[y];
			y = x;
		}
		vector<bool>reachableX(n,false);
		explore(adj,reachableX,x);
		for(int i=0;i<n;i++){
			if(reachableX[i])shortest[i] = 0;
		}
		
	}
	

}


int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
