#include "Point.h"


Point::Point(double x,double y):x(x),y(y){std::cout<<"Here!";};
//Point::Point(){x = 0.0,y =0.0; std::cout<<"Here!";}
double Point::getx() const{return x;}
double Point::gety() const{return y;}
void Point::setx(double x_){x = static_cast<double>(x_);}
void Point::sety(double y_){y = static_cast<double>(y_);}

Point operator+( Point& p1, Point& p2)
{
	double x = p1.getx() + p2.getx();
	double y = p1.gety() + p1.gety();
	Point p(x,y);
	return p;
}

Point operator-(Point& p1, Point& p2)
{
	double x = p1.getx() - p2.getx();
	double y = p1.gety() - p1.gety();
	Point p(x,y);
	return p;
}

std::ostream& operator<<(std::ostream& out,const Point& p)
{
	out<<'('<<p.getx()<<','<<p.gety()<<')';
	return out;
}