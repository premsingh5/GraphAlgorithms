#include <iostream>
#include <vector>
#include <queue>
#include<limits>
#include "C:/Users/PREMSINGH/source/repos/priority_queue/Header.h"
#include<functional>
using namespace std;
const int inf = numeric_limits<int>::max();
template<class T>
class node{
	T key;
	int index;
	public:
		bool operator==(node<T> i) const {
        if ( i.key==this->key && i.index==this->index) {
            return true;
        } else {
            return false;
        }
    }
    	node(T a=0,int b=0):key(a),index(b){
		};
		const T getKey() const{
			return key;
		}
		const int getIndex() const{
		return index;
		}
		void changeKey(T c){
			key = c;
		}
};
template<class T>
class comparision{
	bool reverse;
	public:
		comparirion(){
			reverse = false;
		}
		comparirion(bool k){
			reverse = true;
		}
		bool operator()(node<T> &a,node<T> &b){
			if(reverse)return (a.getKey()> b.getKey());
			else return a.getKey()<b.getKey();
		}
};

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
	int n = adj.size();
	typedef node<int> Node;
	vector<int> dist(n,inf);
	dist[s]=0;
	vector<int>prev(n,-1);
	PriorityQueue<node<int>,vector<node<int>>,comparision<int>>pq;
	pq.insert(node<int>(0,s));
	while(!pq.empty()){
		node<int> k = pq.extractMaxPriority();
		int u = k.getIndex();
		int m = adj[u].size();
		for(int i=0;i<m;i++){
			int v = adj[u][i];
			if(dist[v] > dist[u]+cost[u][i]){
				dist[v] = dist[u]+cost[u][i];
				prev[v] = u;
				pq.insert(Node(dist[v],v));
			}
		}
		
	}
	int latest = t;
	vector<int>patht;
	patht.push_back(t);
	while(latest!=s){
		patht.push_back(prev[latest]);
		latest = prev[latest];
	}
	for(int i=patht.size()-1;i>=0;i--){
		cout<<patht[i]+1<<"->";
	}
	cout<<endl;
	return dist[t];
}
/*template<class T>
class Hash{
	public:
		size_t operator()(const node<T>& k)const {
		return hash<T>()(k.getKey());
	}
};*/
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
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, cost, s, t);
  /*node<long long int>N(1000,0);
  typedef node<long long int> mynode;
  
  mynode(100,1);
  Hash<long long int> h;
  //cout<<h(N);
  typedef unordered_map<node<long long int>,int,Hash<long long int>> mymap;
  mymap a;
  a.insert(make_pair<node<long long int>,int>(mynode(100,1),1));
  //cout<<(mypair(mynode(100,1)==mynode(100,1));
  a.insert(make_pair<node<long long int>,int>(mynode(101,2),2));
  a.insert(make_pair<node<long long int>,int>(mynode(101,3),3));
  for(auto& x: a) {
  	cout<<x.first.getKey()<<"	"<<x.second<<endl;
  }
  vector<int> v(10,1);
  vector<int>::iterator it;
  for(it = v.begin();it!=v.end();it++){
  	cout<<*it<<endl;
  }
  for(auto&x: v)cout<<x;*/
  
  return 0;
  
}
