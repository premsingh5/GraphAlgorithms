#include <iostream>
#include <vector>
using namespace std;
int count=0;
void explore(vector<vector<int>> &G,bool visited[],int u,bool &cycle,int previsit[],int postvisit[],int N){
	//cout<<endl;
	//cout<<u+1;
	//cout<<endl;
	visited[u]=true;
	previsit[u]=count;
	//for(int i=0;i<N;i++)cout<<previsit[i]<<" ";
	count+=1;
	int n=G[u].size();
	for(int i=0;i<n;i++){
		int neighbor = G[u][i];
		if(previsit[neighbor]<previsit[u] && postvisit[neighbor]==INT_MAX){
			cycle=true;
			break;
		}
		if(!visited[neighbor]){
			explore(G,visited,neighbor,cycle,previsit,postvisit,N);
		}
	}
	postvisit[u]=count;
	count+=1;
}
int acyclic(vector<vector<int>> &G,size_t N){
	bool visited[N]={false};
	int previsit[N];
	int postvisit[N];
	for(int i=0;i<N;i++){
		previsit[i]=INT_MAX;
		postvisit[i]=INT_MAX;
	}
	bool cycle=false;
	for(int i=0;i<N;i++){
		if(!visited[i]){
			explore(G,visited,i,cycle,previsit,postvisit,N);
		if(cycle==true)return 1;
		}
	}
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
  }
  cout << acyclic(adj,n);
}
