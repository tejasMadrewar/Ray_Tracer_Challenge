#ifndef TUPLE_H
#define TUPLE_H

class tuple
{
	// ordered elements
	// x y z w
	// if w = 0 tuple is point
	// if w = 1 tuple is vector
private:
public:
	float t[4];
	// contructor
	tuple(){
		t[0]=0; t[1]=0; t[2]=0; t[3]=0;
	}

	tuple(float x, float y, float z, float w){
		t[0]=x; t[1]=y; t[2]=z; t[3]=w;
	}
	~tuple(){}

	// get value
	float getX(){return t[0];}
	float getY(){return t[1];}
	float getZ(){return t[2];}
	float getW(){return t[3];}

	// set value
	void setX(float a){t[0] = a;}
	void setY(float a){t[1] = a;}
	void setZ(float a){t[2] = a;}
	void setW(float a){t[3] = a;}

	// point or vector check
	bool isPoint(){return (t[3] == 0);}
	bool isVector(){return (t[3] == 1);}

	// compare
	bool operator==(tuple a){
		if( t[0] == a.t[0] &&
		    t[1] == a.t[1] && 
		    t[2] == a.t[2] && 
		    t[3] == a.t[3])
			return true;
		else
			return false;
	}

	// addition
	tuple operator+(tuple a){
		return tuple( t[0] + a.t[0], 
		    t[1] + a.t[1],  
		    t[2] + a.t[2],  
		    t[3] + a.t[3]);
	}

	// subtraction
	tuple operator-(tuple a){
		return tuple( t[0] - a.t[0], 
		    t[1] - a.t[1],  
		    t[2] - a.t[2],  
		    t[3] - a.t[3]);
	}

};

#endif
