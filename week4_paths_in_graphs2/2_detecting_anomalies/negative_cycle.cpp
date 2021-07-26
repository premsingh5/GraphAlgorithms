#include <iostream>
#include <vector>
#include<limits>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<list>
#include<utility>
//#include<string>
using namespace std;
const int inf = numeric_limits<int>::max();

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

int NumberOfComponents(vector<vector<int>> &adj,vector<int> &componentsNode){
	int n = adj.size();
	int NumOfComponents = 0;
	vector<bool> isexplored(n,false);
	for(int i =0;i<n;i++){
		if(isexplored[i]==false){
			componentsNode.push_back(i);
			NumOfComponents+=1;
			explore(adj,isexplored,i);
		}
	}
	return NumOfComponents;
}

pair<int,int> RelaxAll(vector<vector<int>> &adj,vector<vector<int>> &cost,vector<int> &dist,int s){
	int n = adj.size();
	pair<int,int> relaxedE = make_pair(-1,-1);
	vector<bool>isRelaxed(n,false);
	bool firstRL = false;
	queue<int,list<int>> Q;
	dist[s] = 0;
	Q.push(s);
	while(!Q.empty()){
		int e = Q.front();
		Q.pop();
		isRelaxed[e]=true;
		int m = adj[e].size();
		for(int i=0;i<m;i++){
			if(dist[adj[e][i]]>dist[e]+cost[e][i]){
				//if(!firstRL){
				relaxedE = make_pair(e,adj[e][i]);
				//firstRL = true;	
				//}
				dist[adj[e][i]] = dist[e]+cost[e][i];
			}
			if(!isRelaxed[adj[e][i]]){
			Q.push(adj[e][i]);	
			}
		}	
	}
	return relaxedE;
	
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
	int n = adj.size();
	vector<int>dist(n,inf);
	//vector<int>prev(n,-1);
	vector<int>ComponentsNode;
	int Num = NumberOfComponents(adj,ComponentsNode);
	for(int k=0;k<Num;k++){
		vector<int>distCopy(dist);
		pair<int,int>relaxed;
		for(int i=0;i<n;i++){
		relaxed = RelaxAll(adj,cost,dist,ComponentsNode[k]);
		}
		if(relaxed.first!=-1)return 1;
	}
    return 0;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  cout<<negative_cycle(adj,cost);
}
