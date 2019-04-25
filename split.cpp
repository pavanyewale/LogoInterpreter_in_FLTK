#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
vector<string>  split(std::string s,std::string delimiter){
size_t pos = 0;
std::string token;
vector<string> v;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    v.push_back(token);
    //std::cout << token << std::endl;
    s.erase(0, pos + delimiter.length());
}
//std::cout << s<< std::endl;
    
v.push_back(s);
return v;
}
int main(){
    vector <string> v;
    v=split("hello    split this by space "," ");
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<endl;
    }
}
