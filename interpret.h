#include<fstream>
#include<sstream>
#include "GUI.h"
#include<vector>
#include <iostream> 
#include<math.h> 
struct Symbol{
    string sname;
    int value;
    Symbol(string sn,int val):sname(sn),value(val){}
};
struct Current{
    Point p;
    int angle;
    Current(Point pp,int angl) :p(pp),angle(angl){}
};
void print(vector<string> s){
    for(int i=0;i<s.size();i++){
        cout<<s[i]<<endl;
    }
}
struct Function{
    string fname;
    vector<string> body;
    vector<Symbol> syms;
    Function(string fn):fname(fn){}

};

/***  this is old code**/
#define PI 3.1415926535897932384626 
vector<Line> lines;

// Function used to display X and Y coordinates of a point 
void displayPoint(Point P) 
{ 
    cout << "(" << P.x << ", " << P.y << ")"; 
} 
#define SIN(x) sin(x * 3.141592653589/180) 
#define COS(x) cos(x * 3.141592653589/180)   
 
//Function for Rotation of P about Q by angle theta 
Point rotate(Point P, Point Q, double angle) 
{ 

 int x_shifted = P.x -Q.x; 
        int y_shifted = P.y - Q.y; 
  
        // Calculating the rotated point co-ordinates 
        // and shifting it back
		int x1,y1; 
        x1 = Q.x + (x_shifted*COS(angle)  
                          - y_shifted*SIN(angle)); 
        y1 = Q.y + (x_shifted*SIN(angle)  
                          + y_shifted*COS(angle)); 
        cout << "(" << x1 << ", " << y1<< ") "; 
		return Point(x1,y1);
} 

Point forword(int distance,Point current,int currentAngle){
    cout<<"forword"<<endl;
	Point q(current.x,current.y-distance);
	Point j= rotate(q,current,currentAngle);
	lines.push_back(Line(current,j,2,FL_WHITE));
	cout<<"line at:";
	displayPoint(current);
	displayPoint(j);
	cout<<endl;
	current=j;
	return current;
}
Point backword(int distance,Point current,int currentAngle){
	cout<<"backword"<<endl;
    return forword(distance*-1,current,currentAngle);
}
int rotate(int angle,int currentAngle){
    cout<<"rotate"<<endl;
	currentAngle+=angle;
    currentAngle=currentAngle%360;
	cout<<"currentAngle"<<currentAngle<<endl;
    return currentAngle;
}

/**** end of old code*******/

vector <Function> functions;

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

Current repeat(int n,char *s,vector<Symbol> syms,Current c);

Current interpreter(vector<Symbol> syms,vector<string> s,Current c);

Current repeat(int n,vector<string>s,vector<Symbol> syms,Current c){
    cout<<"repeat"<<endl;
    for(int i=0;i<n;i++){
        c=interpreter(syms,s,c);
    }
    return c;
}

bool isNumber(string s) 
{ 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
  
    return true; 
} 
int getValue(string exp,vector<Symbol> syms){
    cout<<"getValue:"<<exp<<endl;
    for(int i=0;i<syms.size();i++){
        if(syms[i].sname==exp){
            cout<<"done"<<syms[i].value<<endl;
            return syms[i].value;
        }
    }
    cout<<"invalid expression:"<<exp<<endl;
    exit(0);
}

int solve (string exp,vector<Symbol> syms){
   cout<<"solve:"<<exp<<endl;
   vector<string> v;
   v=split(exp,"*");
   if(v.size()==2){
       return solve(v[0],syms)*solve(v[1],syms);
   }

   v=split(exp,"/");
   if(v.size()==2){
       return solve(v[0],syms)/solve(v[1],syms);
   }

   v=split(exp,"+");
   if(v.size()==2){
       return solve(v[0],syms)+solve(v[1],syms);
   }

   v=split(exp,"-");
   if(v.size()==2){
       return solve(v[0],syms)-solve(v[1],syms);
   }
   v=split(exp,"-");
   if(v.size()==2){
       return solve(v[0],syms)-solve(v[1],syms);
   }
   v=split(exp,"<");
   if(v.size()==2){
       if(solve(v[0],syms)<solve(v[1],syms)){
           return 1;
       }
       return 0;
   }
   v=split(exp,">");
   if(v.size()==2){
       if(solve(v[0],syms)>solve(v[1],syms)){
           return 1;
       }
       return 0;
   }
   v=split(exp,"==");
   if(v.size()==2){
       if(solve(v[0],syms)==solve(v[1],syms)){
           return 1;
       }
       return 0;
   }
   v=split(exp,"<=");
   if(v.size()==2){
       if(solve(v[0],syms)<=solve(v[1],syms)){
           return 1;
       }
       return 0;
   }
   v=split(exp,">=");
   if(v.size()==2){
       if(solve(v[0],syms)>=solve(v[1],syms)){
           return 1;
       }
       return 0;
   }
   v=split(exp,"!=");
   if(v.size()==2){
       if(solve(v[0],syms)!=solve(v[1],syms)){
           return 1;
       }
       return 0;
   }
    if(!isNumber(exp)){
        return getValue(exp,syms);
    }
    int number=0;
    stringstream geek(exp); 
    geek>>number;
    return number;
}
void runFunction(vector<string> line,vector<Symbol> syms,Current c){
    cout<<"runFunction"<<endl;
    print(line);
    vector<Symbol> s;
    for(int i=0;i<functions.size();i++){
        if(functions[i].fname==line[0]){
            for(int k=0;k<functions[i].syms.size();k++){
                s.push_back(Symbol(functions[i].syms[k].sname,solve(line[k+1],syms)));
            }
            interpreter(s,functions[i].body,c);
            break;
        }
    }
}
void remove(vector<string> s,string deli){
    auto p=s.begin();
        int i=0;
        while(p!=s.end()){
            if(s[i]==deli){
                s.erase(p);
            }
            i++;
            p++;
        }
}

Current interpreter(vector<Symbol> syms,vector<string> lines,Current c){
    cout<<"interpreter"<<endl;
    for(int i=0;i<lines.size();i++){
        if(lines[i]=="]"){
            continue;
        }
        vector<string> s=split(lines[i]," ");
        //remove(s,"");
        vector<string> k;
        if(s[0]=="TO"){
            functions.push_back(Function(s[1]));
            for(int k=2;k<s.size();k++){
                functions[functions.size()-1].syms.push_back(Symbol(s[k],0));
            }
            for(i=i+1;i<lines.size();i++){
                if(lines[i]=="END"){
                    cout<<"end"<<endl;
                   // print(functions[functions.size()-1].body);
                    break;
                }
                functions[functions.size()-1].body.push_back(lines[i]);
            }
        }

        if(s[0]=="if"){
            cout<<"if"<<endl;
            if(!solve(s[1],syms)){
                /*for(i=i+1;i<lines.size();i++){
                    if(lines[i]=="]"){
                        lines.erase(lines.begin()+i);
                        i--;
                        cout<<"found......................"<<endl;
                        break;
                    }
                    lines.insert(lines.begin(),lines[i]);
                    
                }
                interpreter(syms,k);            }else{*/
                while(lines[i]!="]"){
                    i++;
                }
            }
            continue;
        }
        if(s[0]=="stop"){
            return c;
        }
        if(s[0]=="repeat"){
            cout<<"repeat"<<endl;
                k.clear();
                for(i=i+1;i<lines.size();i++){
                   
                    if(lines[i]=="]"){
                        break;
                    }
                     k.push_back(lines[i]);
                
                }
                c=repeat(solve(s[1],syms),k,syms,c);
            
            continue;
        }
        if(s[0]=="forward"){
            cout<<"forward";
            c.p=forword(solve(s[1],syms),c.p,c.angle);
            continue;
        }
        if(s[0]=="back"){
            c.p=backword(solve(s[1],syms),c.p,c.angle);
            continue;
        }
        if(s[0]=="left"){
            cout<<"left"<<endl;
            c.angle-=solve(s[1],syms);
            c.angle%=360;
            //rotate(-1*solve(s[1],syms),currentAngle);
            continue;
        }
        if(s[0]=="right"){
            c.angle+=solve(s[1],syms);
            c.angle%=360;
            //rotate(solve(s[1],syms),currentAngle);
            continue;
        }
        if(s[0]=="stop"){
            break;
        }
        runFunction(s,syms,c);
    }
    return c;
}


vector<string> readfile(string filename){
    ifstream infile;
    infile.open(filename);
    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string s;
    vector<string> v;
    while (infile >> s) {
        v.push_back(s);
    }
    
    infile.close();
    
}


vector<Line> interpreter1(vector<string> line){
   Point current(w/2,h-h/4);
   int angle=0;
    vector<Symbol> syms;
    cout<<"interpreter1";
    Current c(current,angle);
   // print(line);
    interpreter(syms,line,c);
    return lines;
}
