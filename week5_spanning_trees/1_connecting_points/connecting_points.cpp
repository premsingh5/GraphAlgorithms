#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
#include "C:\Users\PREMSINGH\source\repos\UnionFind\Header.h"
using namespace std;
struct node{
	int source,dest;
	double weight;
	node(int s,int d,double w){
		source = s;
		dest = d;
		weight = w;
	}
};

class Sort{
	public:
		void swap(vector<node>&vec,int i,int j){
			node temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
		}
		int partition(vector<node>&vec,int low,int high){
			int i= low-1;
			int j=low;
			while(j<high){
			
				double l = vec[j].weight;
				double c = vec[high].weight;
			    if(l <=c){
				i++;
				swap(vec,i,j);
				}
				j++;
			}
			i+=1;
			swap(vec,i,high);
			return i;
		}
		void QuickSort(vector<node> &vec,int low,int high){
			if(low<high){
			int i = partition(vec,low,high);
			QuickSort(vec,low,i-1);
			QuickSort(vec,i+1,high);
			}
		}
};
double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  size_t n = x.size();
  UnionFind uf(n);
  vector<node>edges;
  for(int i=0;i<n;i++){
  	for(int j=0;j<n;j++){
  		if(i==j)continue;
  		double w = pow((pow((x[i]-x[j]),2)+pow((y[i]-y[j]),2)),0.5);
  		edges.push_back(node(i,j,w));
	  }
  }
  Sort mysort;
  long long int s = edges.size();
  mysort.QuickSort(edges,0,edges.size()-1);
  for(long long int i=0;i<s;i++){
  	int u=edges[i].source;
	int v=edges[i].dest;
	double w = edges[i].weight;
  	if(!uf.find(u,v)){
  		result+=w;
  		uf.Union(u,v);
	  }
  }
  cout<<result;
  return result;
} 

int main() {
  size_t n;
  ifstream source;
  ofstream destination("C:/Users/PREMSINGH/IOC++/connecting_pointsOP.txt");
  source.open("C:/Users/PREMSINGH/IOC++/connecting_pointsIP.txt");
  source >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    	source >> x[i] >> y[i];
  }
   destination<< std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
