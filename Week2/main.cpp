
#include <iostream>
#include "Point.h"

int main()
{
	Point p1;
	p1.setx(2.4);
	p1.sety(3.5);

    Point p2(10.0 - p1.getx(), 10.0 - p1.gety());     
    std::cout<<"p1 = "<<p1<<"\n";
    std::cout<<"p2 = "<<p2<<"\n";     std::cout<<"p ="<<p1+p2<<"\n";
    return 0; 
}
