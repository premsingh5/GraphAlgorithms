#include <iostream>
#include <vector>
using namespace std;

void explore(vector<vector<int> > &adj,bool visited[],int u){
	int n = adj[u].size();
	visited[u]=true;
	for(int i = 0;i<n;i++){
		int neibour = adj[u][i];
		if(!visited[neibour]){
			visited[neibour] = true;
			explore(adj,visited,neibour);
		}
	}
}
int reach(vector<vector<int> > &adj, int u, int v) {
	int num_vertices = adj.size();
	bool visited[num_vertices] = {false};
	explore(adj,visited,u);
	if(visited[v])return 1;
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  cin >> x >> y;
  cout << reach(adj, x - 1, y - 1);
}
