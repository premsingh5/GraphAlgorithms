#include <iostream>
#include <vector>
#include <queue>
#include<list>
using namespace std;

int distance(vector<vector<int> > &adj, int s, int t) {
	vector<int> dist(adj.size(),INT_MAX);
	queue<int,list<int>> Q;
	Q.push(s);
	dist[s]=0;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int i=0;i<adj[u].size();i++){
			if(dist[adj[u][i]] == INT_MAX)Q.push(adj[u][i]);
			if(dist[adj[u][i]] > dist[u]+1) dist[adj[u][i]] =  dist[u]+1;
		}
	}
	return dist[t];
                                                                                                                                                                                                                                                             
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
