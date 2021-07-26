
#include <iostream>
#include <vector>
using namespace std;

void explore(vector<vector<int> > &adj,bool visited[],int u){
	int n = adj[u].size();
	visited[u]=true;
	for(int i = 0;i<n;i++){
		int neibour = adj[u][i];
		if(!visited[neibour]){
			explore(adj,visited,neibour);
		}
	}
}
int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  int n = adj.size();
  bool visited[n]  = {false};
  for(int i = 0;i<n;i++){
  	if(!visited[i]){
  		res+=1;
  		explore(adj,visited,i);
	  }
  }
  return res;
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
 cout << number_of_components(adj);
 return 0;
}
