#include "interpret.h"
using namespace std; 
// Constant PI for providing angles in radians 
int main() {
	Windows window(Point(w, 0), w, h, "Interpreter");
	vector<Line> lines=interpreter1(split("TO tree size\nif size<5 [\nstop\n]\nforward size\ntree size/2\nback size\nright 35\nforward size\ntree size/2\nback size\nleft 70\nforward size\ntree size/2\nEND\ntree 300","\n"));
	for(int i=0;i<lines.size();i++){
	window.attach(lines[i]);
	}
	return Fl::run();
}
