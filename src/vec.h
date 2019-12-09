#include "tuple.h"

#ifndef VEC_H
#define VEC_H


class vec : public tuple
{
public:
	vec(): tuple(0,0,0,1){}
	vec(float x, float y, float z): tuple(x,y,z,1){}
	~vec(){}

	void setW(float a){}

	// vector subtraction
	vec operator-(vec a){
		return vec( t[0] - a.t[0], 
			    t[1] - a.t[1],  
			    t[2] - a.t[2]);
	}

	// negating operator
	vec operator-(){
		return vec(-t[0], 
			   -t[1],  
			   -t[2]);
	}
	
	

private:

};

#endif
