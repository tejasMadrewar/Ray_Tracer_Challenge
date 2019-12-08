#include "tuple.h"
#include "vec.h"

#ifndef POINT_H
#define POINT_H
	

class point : public tuple
{
private:

public:
	point(): tuple(0,0,0,0){}
	point(float x, float y, float z): tuple(x,y,z,0){}
	~point(){}

	void setW(float a){}

	tuple c = tuple(4.3, -4.1, 3.1, 1.0);

	// point subtraction
	vec operator-(point a){
		return vec( t[0] - a.t[0], 
			    t[1] - a.t[1],  
			    t[2] - a.t[2]);
	}

	point operator-(vec a){
		return point( t[0] - a.t[0], 
			    t[1] - a.t[1],  
			    t[2] - a.t[2]);
	}
	
};

#endif
