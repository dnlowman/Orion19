#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
	protected:
		float _x;
		float _y;
		
	public:
		Vector();
		~Vector();
		void SetX(float x) { _x = x; }
		void SetY(float y) { _y = y; }
		float GetX() const { return _x; }
		float GetY() const { return _y; }
		float ReturnDistanceBetween(Vector* vec);
		
}

#endif