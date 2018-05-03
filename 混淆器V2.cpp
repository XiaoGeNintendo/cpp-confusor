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

bool debug=true;
/*
   Write In New Computer
    By XiaoGeNintendo
	     gwq2017
	Type:
*/
string prog;
string path;

template<typename T> static std::string toString(const T& t)
{
    std::string s;
    std::stringstream ss;
    ss << t;
    ss >> s;
    return s;
}


void read_prog(){
	freopen(path.c_str(),"r",stdin);
	string tmp;
	while(getline(cin,tmp)){
		prog+=tmp+"\n";
		
		cout<<"[read_prog] find code:"<<tmp<<endl;
	}
	
	cout<<"[read_prog] All program readed"<<endl;
}


void del_comment(){
	cout<<"[del_comment]Deleting comments"<<endl;
	while(true){
		int pos=prog.find("//");
		if(pos==string::npos){
			break;
		}
		
		for(int j=pos;j<prog.size();j++){
			if(prog[j]=='\n'){
				cout<<"[del_comment] Deleted single-line comment at "<<pos<<" to "<<j<<endl;
				prog.erase(pos,j-pos);
				break;
			}
		}
		
		
	}
	
	cout<<"[del_comment] Single line comment finished finding!"<<endl;
	
	while(true){
		int pos=prog.find("/*");
		if(pos==string::npos){
			break;
		}
		for(int k=0;k<prog.size();k++){
			if(prog.substr(k,2)=="*/"){
				cout<<"[del_comment]Deleted comment from "<<pos<<" to "<<k<<endl;
				prog.erase(pos,k-pos+2);
				break;
			}
		}
	}
	
	cout<<"[del_comment] Long comment finished finding!"<<endl;
	
	
}

string splitor="[],.;<>?/\\\"'()*&^%$#@!~+-={} |`~\n\t:";

vector<string> splits(string s,string sep){
	//keep the sep
	
	vector<string> vs;
	string sy="";
	for(int i=0;i<s.size();i++){
		bool issep=false;
		for(int j=0;j<sep.size();j++){
			if(sep[j]==s[i]){
				//sep
				vs.push_back(sy);
				sy="";
				string tmp="";
				tmp+=sep[j];
				vs.push_back(tmp);
				issep=true;
				break;
			}
		}
		
		if(!issep){
			sy+=s[i];
		}
	}
	
	if(sy!=""){
		vs.push_back(sy);
	}
	return vs;
}

map<string,string> con;
void addConfuse(string s,string pre,int b){
	if(con.count(s)){
		return;
	}
	con[s]=pre+toString(b);
}
void addConfuse(string s,string pre){
	if(con.count(s)){
		return;
	}
	con[s]=pre;
}
template<typename T> ostream& operator<<(ostream& os,vector<T>& vt){
	for(int i=0;i<vt.size();i++){
		os<<vt[i]<<" ";
	}
	return os;
}
bool isVarName(string s){
	if(s.back()=='*' || s.back()=='&'){
		s.erase(s.end()-1);
	}
	
	if(!isalpha(s[0]) && s[0]!='_'){
		return false;
	}
	for(int i=0;i<s.size();i++){
		if(!isalpha(s[i]) && !isdigit(s[i]) && s[i]!='_'){
			return false;
		}
	}
	
	
	return true;
} 

vector<string> syss={
				"int",
				"long",
				"string",
				"vector",
				"main",
				"return",
				"true",
				"false",
				"short",
				"float",
				"double",
				"map",
				"pair",
				"include",
				"define",
				"set",
				"unordered_map",
				"queue",
				"deque",
				"bool",
				"register",
				"inline",
				"erase",
				"size",
				"using",
				"namespace",
				"std",
				"void",
				"char",
				"cout",
				"endl",
				"cin",
				"const",
				"size",
				"first",
				"second",
				"iostream",
				"algorithm",
				"define",
				"push_back",
				"pop",
				"push",
				"top",
				"count",
				"isaplha",
				"isdigit",
				"islower",
				"isupper",
				"operator",
				"template",
				"typename",
				"end",
				"begin",
				"ostream",
				"break",
				"for",
				"while",
				"do",
				"typedef",
				"srand",
				"rand",
				"time",
				"system",
				"tie",
				"sync_with_stdio",
				"ios",
				"multimap",
				"multiset",
				"clock",
				"getline",
				"scanf",
				"printf",
				"iterator",
				"priority_queue",
				"make_pair",
				"sort",
				"if",
				"else",
			  };


bool isSystem(string s){
	for(int i=0;i<syss.size();i++){
		if(s==syss[i]){
			return true;
		}
	}
	return false;
} 

string getConfuse(string s){
	if(con.count(s)){
		return con[s];
	}else{
		return s;
	}
}

string getRandomChars(int a,int b){
	srand(time(0));
	int sz=rand()%(b-a)+a;
	string s;
	for(int i=0;i<sz;i++){
		s+=rand()%('z'-'a')+'a';
	}
	return s;
}

//HXQ V2 
int main(int argc,char* argv[]){
	
	
	if(argc==1){
	
		cout<<"File path to be confused:";
		getline(cin,path);
	
	}else{
		path=argv[1];
	}
	
	cout<<"Start confusing..."<<endl;
	

	read_prog();
	
	del_comment();
	
	vector<string> vs=splits(prog,splitor);
	
	for(int i=0;i<vs.size();i++){
		if(vs[i]==""){
			vs.erase(vs.begin()+i);
			i--;
		}
	}
	cout<<"[afer_read]"<<vs<<endl;
	
	bool inIt=false;
	bool inKyu=false;
	
	for(int i=0;i<vs.size();i++){
		if(vs[i]=="\"" && vs[i-1]!="\\"){
			inIt=!inIt;
		}
		if(vs[i]=="#"){
			inKyu=true;
		}
		if(vs[i]=="\n"){
			inKyu=false;
		}
		
		
		
		if(inIt){
			continue;
		}
		if(isVarName(vs[i]) && !isSystem(vs[i])){
			if(inKyu){
				addConfuse(vs[i],vs[i]);
				cout<<"[new_confuse]De-Confused:"<<vs[i]<<endl;
				continue;
			}
		
			addConfuse(vs[i],"var",i);
			cout<<"[new_confuse]Confused:"<<vs[i]<<endl;
		}
	}
	
	
	cout<<"END"<<endl;
	inIt=false;
	inKyu=false;
	freopen(("confused_"+path).c_str(),"w",stdout);
	for(int i=0;i<vs.size();i++){
		if(vs[i]=="\"" && vs[i-1]!="\\"){
			inIt=!inIt;
		}
		if(vs[i]=="#"){
			inKyu=true;
		}
		if(vs[i]=="\n"){
			inKyu=false;
		}
		
		if(inIt || inKyu){
			cout<<vs[i];
			continue;
		}
		cout<<getConfuse(vs[i]);
	}
	return 0;
}

