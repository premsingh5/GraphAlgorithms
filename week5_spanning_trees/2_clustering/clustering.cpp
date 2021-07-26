#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include<random>
#include<time.h>
#include "C:/Users/PREMSINGH/source/repos/UnionFind/Header.h"

using std::vector;
using std::pair;

using namespace std;
template<class T>
T Random(int from_range,int to_range){
	random_device rand_dev;
	mt19937 generator(rand_dev());
	uniform_int_distribution<T>distr(from_range,to_range);
	return distr(generator);
	
}

struct node{
	int source;
	int dest;
	double weight;
	node(int s,int d,double w):source(s),dest(d),weight(w){
	}
	
};
class Sort{
	public:
		void swap(vector<node>&vec,int i,int j){
			node t = vec[i];
			vec[i] = vec[j];
			vec[j] = t;
		}
		int partition(vector<node>&vec,int low,int high){
			int i = low-1;
			int j=low;
			while(j<high){
				if(vec[j].weight<vec[high].weight){
					i++;
					swap(vec,i,j);
				}
				j++;
			}
			i++;
			swap(vec,i,high);
			return i;
		}
		void QuickSort(vector<node>&vec,int low,int high){
			if(low<high){
				int i = partition(vec,low,high);
				QuickSort(vec,low,i-1);
				QuickSort(vec,i+1,high);
			}
		}
};
double clustering(vector<int> x, vector<int> y, int k) {
  int n = x.size();
  vector<node>edge;
  for(int i=0;i<n;i++){
  	for(int j=0;j<n;j++){
  		if(i==j)continue;
  		double w = pow((pow((x[i]-x[j]),2)+pow((y[i]-y[j]),2)),0.5);
  		edge.push_back(node(i,j,w));
	  }
  }
  Sort mysort;
  int NumEdges = edge.size();
  mysort.QuickSort(edge,0,NumEdges-1);
  UnionFind uf(n);
  int NumClusters = n;
  for(auto i=0;i<NumEdges;i++){
  	int u = edge[i].source;
  	int v = edge[i].dest;
	if(!uf.find(u,v)){
	  	if(NumClusters>k){
	  		uf.Union(u,v);
	  		NumClusters-=1;
			}
	  	else if(NumClusters==k){
		  	return edge[i].weight;
		  }		
	}
	}
	return -1;
}

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
