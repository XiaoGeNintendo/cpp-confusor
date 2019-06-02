#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <deque>
#include <bits/stdc++.h>
//#include "D:\C++\test_lib_projects\testlib.h"
using namespace std;
#define ll long long
#define pii pair<int,int>
#define qi ios::sync_with_stdio(0)

bool debug=true;

/*    *************************************
	  * Written in New Computer           *
	  * The following code belongs to     *
	  * XiaoGeNintendo of HellHoleStudios *
	  *************************************
*/
template<typename T1,typename T2>ostream& operator<<(ostream& os,pair<T1,T2> ptt){
	os<<ptt.first<<","<<ptt.second;
	return os;
}
template<typename T>ostream& operator<<(ostream& os,vector<T> vt){
	os<<"{";
	for(int i=0;i<vt.size();i++){
		os<<vt[i]<<" ";
	}
	os<<"}";
	return os;
}


int main(int argc,char* argv[]){
	
	cout<<"File passed to be SUOed:";
	string s;
	cin>>s;
	freopen(s.c_str(),"r",stdin);
	freopen(("suo_"+s).c_str(),"w",stdout);
	
	
	vector<string> vs;
	
	while(getline(cin,s)){
		vs.push_back(s);
		
	}
	
	for(string t:vs){
		while(t[0]==' ' || t[0]=='\t'){
			t.erase(t.begin());
		}
		
		
		int index=t.find("//");
		if(index!=-1){
			t=t.substr(0,index);
		}
		
		if(t[0]=='#'){
			cout<<t<<endl;
		}else{
			cout<<t;
		}
	}
	return 0;
}


