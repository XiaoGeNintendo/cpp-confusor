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

std::vector<std::string> split(const std::string& s, char separator)
{
    std::vector<std::string> result;
    std::string item;
    for (size_t i = 0; i < s.length(); i++)
        if (s[i] == separator)
        {
        	if(item=="") continue; 
            result.push_back(item);
            item = "";
        }
        else
            item += s[i];
    result.push_back(item);
    return result;
}

string prog;
string path;
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

void read_prog(){
	freopen(path.c_str(),"r",stdin);
	string tmp;
	while(getline(cin,tmp)){
		prog+=tmp+"\n";
		
		cout<<"[read_prog] find code:"<<tmp<<endl;
	}
	
	cout<<"[read_prog] All program readed"<<endl;
}


void export_ans(){
	string out="confused_"+path;
	
	cout<<"[export_ans] Exporting to "<<out<<endl;
	
	freopen(out.c_str(),"w",stdout);
	cout<<prog<<endl<<"//Confused by XGN's Confuser"<<endl;
}

string ops="[]{};<>,()+-*/^|=%~&.";

bool isOp(char c){
	return ops.find(c)!=string::npos;
}

bool isdd(int pos){
	if(pos==prog.size()-1){
		return false;
	}
	
	if(prog[pos]=='<' && prog[pos+1]=='<'){
		return true;
	}
	if(prog[pos]=='>' && prog[pos+1]=='>'){
		return true;
	}
	
	return false;
}

void add_space(){
	cout<<"[add_space] Adding spaces"<<endl;
	for(int i=0;i<prog.size();i++){
		if(isOp(prog[i])){
			if(isdd(i)){
				continue;
			}
			
			cout<<"[add_space] Add spaces at "<<i<<endl;
			prog.insert(i+1," ");
			prog.insert(i," ");
			i++; 
		}
	}
	
	cout<<"[add_space] Added all spaces"<<endl;
}

void killSpace(string s,int del,string fa="del_space"){
	while(true){
		int pos=prog.find(s);
		if(pos==string::npos){
			break;
		}
		
		prog.erase(prog.begin()+pos+del);
		cout<<"[killSpace @ "<<fa<<"] Deleted spaces at"<<pos+del<<endl;
	}

	cout<<"[killSpace @ "<<fa<<"] Ended with"<<s<<endl;
}


void killspace(int l,int r){
	
	while(true){
		cout<<prog.substr(l,r-l+1)<<endl;
		
		int pos=-1;
		for(int i=l;i<=r;i++){
			if(prog[i]==' '){
				pos=i;
				break;
			}
		}
		
		if(pos==-1){
			break;
		}
		
		cout<<"[del_space]Killed space at "<<pos<<endl;
		prog.erase(prog.begin()+pos);
		r--;
	}
} 

void del_space(){
	cout<<"[del_space] Deleting spaces"<<endl;
//	
//	killSpace(" <",0);
//	killSpace("< ",1);
//	killSpace("> ",1);
//	killSpace(" >",0);
	
	bool found=true;
	
	int lasti=0;
	while(found){
		found=false;
			
		for(int i=lasti;i<prog.size();i++){
			if(prog[i]=='<'){
				for(int j=i;j<prog.size();j++){
					if(prog[j]=='>'){
						cout<<"[del_space] Handling with ["<<i-1<<","<<j<<"]"<<endl;
						
						killspace(i,j);
						lasti=i+1;
						
						found=true;
						break;
					}
				}
			}
			
			if(found) break;
		}
		
	}
	
	cout<<"[del_space] Killing spaces before '<>*&'"<<endl;
	killSpace(" >",0);
	killSpace(" <",0);
	killSpace(" *",0); 
	killSpace(" &",0);
}

map<string,string> con;
bool isVarName(string s){
	if(s=="long long"){
		return true;
	}
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


bool isHead(const vector<string>& vs){
		//[inline] <type> <func_name> ( [const] <type> <arg> , [const] <type> <arg>  )
	if(vs.size()<4){
		cout<<"[isHead] short"<<endl;
		return false;
	}
	if(vs[0]=="inline"){
		cout<<"[isHead] inline"<<endl;
		return true;
	}
	
	//Not inline
	if(!isVarName(vs[0]) || !isVarName(vs[1])){
		cout<<"[isHead] bad Var name"<<endl;
		return false;
	}
	
	if(vs[2]!="("){
		cout<<"[isHead] false"<<endl;
		return false;
	}
	
	cout<<"[isHead] true"<<endl; 
	return true;
}

string toString(int num){
	bool negative=false;
	if(num<0) negative=true;
	num=abs(num);
	string s;
	while(num!=0){
		s+=num%10+'0';
		num/=10;
    }
    reverse(s.begin(),s.end());
    if(negative) s='-'+s;
    return s;
}
	

void addConfuse(string s,string type,int pos){
	if(con.count(s)){
		cout<<"[addConfuse] Confuse has been added"<<endl;
	}else{
		//type_pos_CLOCK()
		string cons=type+"_"+toString(pos)+"_"+toString(clock());
		con[s]=cons;
		cout<<"[addConfuse] Confuse added: "<<s<<"->"<<cons<<endl;
	}
} 

void confuseHead(const vector<string>& vs){
	//[inline] <type> <func_name> ( [const] <type> <arg> , [const] <type> <arg>  )
	
	if(vs[0]=="inline"){
		if(vs[2]=="main"){
			return;
		}
		addConfuse(vs[2],"func",1);
	}else{
		if(vs[1]=="main"){
			return;
		}
		addConfuse(vs[1],"func",1);
	}
	
	int p=4;
	if(vs[0]=="inline"){
		p++;
	}
	while(true){
		
		if(p>=vs.size()){
			break;
		}
		
		if(vs[p-1]=="const"){
			p++;
		}
		
		cout<<"[confuseHead] Find parameter : "<<vs[p]<<endl;
		addConfuse(vs[p],"par",p);
		
		p++;
		if(vs[p]=="["){
			p++;
		}
		if(vs[p]=="]"){
			p++;
		}
		p+=2;
	}
	
	cout<<"[confuseHead] Parse ok"<<endl;
	
}

ostream& operator<<(ostream& os,vector<string> vs){
	os<<"{";
	for(int i=0;i<vs.size();i++){
		os<<"\""<<vs[i]<<"\"("<<int(vs[i][0])<<")   ";
		
	}
	os<<"}";
	return os;
}



bool isDeclare(const vector<string>& vs){
	//<type> <varible> [array declare] [ = <something> ] <;>
	if(vs.size()<3){
		cout<<"[isDeclare] short"<<endl;
		return false;
	}
	
	if(vs[0]=="using"){
		cout<<"[isDeclare] using"<<endl;
		return false;
	}
	
	if(isVarName(vs[0]) && isVarName(vs[1])){
		//ok. keep going
	}else{
		cout<<"[isDeclare] bad var name"<<endl;
		return false;
	}
	
	if(vs.size()==3){  // { } ;
	
		if(vs[2]!=";"){
			cout<<"[isDeclare] ;"<<endl;
			return false;
		}else{
			cout<<"[isDeclare] ok"<<endl;
			return true;
		}
	}else{
		//array define?
		
		bool array=false,equal=false,vars=false;
		for(int i=0;i<vs.size();i++){
			if(vs[i]=="["){
				array=true;
			}
			if(vs[i][0]=='='){
				equal=true;
			}
			if(vs[i]==","){
				vars=true;
			}
		}
		
		if(!array && !equal){
			
			if(vars){
				for(int i=0;i<vs.size();i++){
					if(vs[i]=="," && isVarName(vs[i+1])==false){
						cout<<"[isDeclare]BAD VAR-ON-1-LINE NAME"<<endl;
						return false;
					}
				}
				
				return true;
			}
			
			cout<<"[isDeclare] not array nor equal nor vars"<<endl;
			return false;
		}else{
			cout<<"[isDeclare] ok"<<endl;
			return true;
		}
	}
	
	
}


void confuseDeclare(const vector<string>& vs){
	//<type> <varible> [array declare] [ = <something> ] <;>
	
	cout<<"[confuseDeclare]"<<vs[1]<<endl;
	addConfuse(vs[1],"var",1);
	
	for(int i=0;i<vs.size();i++){
		if(vs[i]==","){
			cout<<"[confuseDeclare] varsOn1Line:"<<vs[i+1]<<endl;
			addConfuse(vs[i+1],"vars_on_1_line",i+1);
		}
	}
}

void trimForVs(vector<string>& vs){
	for(int i=0;i<vs.size();i++){
		if(vs[i]==""){
			vs.erase(vs.begin()+i);
			i--;
		}
	}
}


void longLongChecker(vector<string>& vs){
	
	cout<<"[longLongChecker] LLC ing"<<endl;
	 
	if(vs.size()<2){
		return;
	} 
	for(int i=0;i<vs.size()-1;i++){
		if(vs[i]=="long" && vs[i+1]=="long"){
			vs[i]="long long";
			vs.erase(i+1+vs.begin());
		}
	}
}

void find_function_head(){
	cout<<"[find_function_head] Looking for function heads"<<endl;
	cout<<"Compare template: [inline] <type> <func_name> ( <type1> <arg1> , ...)"<<endl;
	
	stringstream ss(prog);
	
	
	
	string tmp;
	while(getline(ss,tmp)){
		vector<string> vs=split(tmp,' ');
		cout<<"[find_function_head] Checking line:"<<tmp<<endl;
		
		trimForVs(vs);
		
		longLongChecker(vs);
		
		
		cout<<"After parsing:"<<vs<<endl;
		 
		if(isHead(vs)){
			confuseHead(vs);
			continue;
		}
		
		if(isDeclare(vs)){
			confuseDeclare(vs);
		} 
	}
} 

void trim(){
	cout<<"[trim] Deleting tabs and useless things"<<endl;
	while(true){
		int pos=prog.find("\t");
		if(pos==string::npos){
			break;
		}
		
		prog.erase(prog.begin()+pos);
	}
}

//void quotoShown(vector<string>& vs){
//	
//	bool q=false;
//	for(int i=0;i<vs.size();i++){
//		int pos=vs[i].find("\"");
//		if(pos==string::npos){
//			cout<<"[quotoShown] Not found quotes"<<endl;
//			continue;
//		}
//		q=true;
//		string pre=vs[i].substr(0,pos-1);
//		string suf=vs[i].substr(pos);
//		cout<<"[quotoShown] Fount quotes! pre="<<pre<<" and suf="<<suf<<endl;
//		vs.insert(i,pre);
//		vs[i]=suf;
//		
//	}
//} 

string VarOnly(string s){
	string ns;
	for(int i=0;i<s.size();i++){
		if(isdigit(s[i]) || isalpha(s[i]) || s[i]=='_'){
			ns+=s[i];
		}
	}
	
	return ns;
}

void makeDDSep(vector<string>& vs){
	for(int i=0;i<vs.size();i++){
		if(vs[i].substr(0,2)=="<<"){
			continue;
		}
		int pos=vs[i].find("<<");
		if(pos==string::npos){
			continue;
		}
		
		string pre=vs[i].substr(0,pos);
		string suf=vs[i].substr(pos);
		cout<<"[makeDDSep] pre="<<pre<<" suf="<<suf<<endl;
		
		vs[i]=pre;
		vs.insert(vs.begin()+i+1,suf);
	}
	
	for(int i=0;i<vs.size();i++){
		if(vs[i].substr(0,2)==">>"){
			continue;
		}
		int pos=vs[i].find(">>");
		if(pos==string::npos){
			continue;
		}
		
		string pre=vs[i].substr(0,pos);
		string suf=vs[i].substr(pos);
		cout<<"[makeDDSep] pre="<<pre<<" suf="<<suf<<endl;
		
		vs[i]=pre;
		vs.insert(vs.begin()+i+1,suf);
	}
	
}

void confuseMain(){
	cout<<"[confuseMain] Confuse Main starts!"<<endl;
	
	stringstream ss(prog);
	
	prog="";
	
	string tmp;
	while(getline(ss,tmp)){
		vector<string> vs=split(tmp,' ');
		
		trimForVs(vs);
		
		//quotoShown(vs);
		
		makeDDSep(vs);
		
		for(int i=0;i<vs.size();i++){
			if(con.count(vs[i])){
				cout<<"[confuseMain] Found confusing for "<<vs[i]<<" changed to "<<con[vs[i]]<<endl;
				
				vs[i]=con[vs[i]];
			}
		}
		
		for(int i=0;i<vs.size();i++){
			prog+=vs[i]+" ";
		}
		prog+="\n";
	}
	
	cout<<"[confuseMain] confusedAll! Time cost:"<<clock()<<"ms"<<endl;
	
}



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

	add_space();
	
	del_space();
	
	
	trim();
	
	find_function_head();
	
	confuseMain();
	
	export_ans();
	
	return 0;
}

