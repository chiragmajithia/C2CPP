#include <iostream>
class Point
{
	public:
		double getx() const;
		double gety() const;
		void setx(double x_);
		void sety(double y_);
		Point(double,double);
		//Point();
	private:
		double x,y;
};



Point operator+(Point& p1, Point& p2);
Point operator-(Point& p1, Point& p2);
std::ostream& operator<<(std::ostream& out,const Point& p);
