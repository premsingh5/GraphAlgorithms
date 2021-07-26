#include <iostream>
#include <vector>
#include <queue>
#include<list>
#include<stdlib.h>
#include<time.h>
using namespace std;
enum colors {WHITE,RED,BLACK
};
bool bipartite(vector<vector<int> > &adj) {
	srand(time(NULL));
	int s = rand()% adj.size();
	cout<<s<<"	"<<adj.size()<<endl;
	vector<int> dist(adj.size(),INT_MAX);
	vector<colors> color(adj.size(),WHITE);
	queue<int,list<int>> Q;
	Q.push(s);
	dist[s]=0;
	color[s]=RED;
	bool isbipartite=true;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int i=0;i<adj[u].size();i++){
			if(dist[adj[u][i]] == INT_MAX){
			Q.push(adj[u][i]);
			if(color[u]==RED)color[adj[u][i]]=BLACK;
			else color[adj[u][i]]=RED;	
			}
			else{
				if(color[u]==color[adj[u][i]])isbipartite = false;
			}
			if(dist[adj[u][i]] > dist[u]+1) dist[adj[u][i]] =  dist[u]+1;
		}
	}
	for(int i=0;i<adj.size();i++)cout<<color[i]<<"	";
	cout<<endl;
	return isbipartite;
                                                                                                                                                                                                                                                             
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
  cout << bipartite(adj);
}
