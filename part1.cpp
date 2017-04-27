//lab 10 part 1

#include <cstdlib>
#include <valarray>
#include <iostream>

using namespace std;


class BaseConic{
    private:
        double x;
        double y;

    public:
        BaseConic(double x0 = 0, double y0 = 0);
        virtual ~BaseConic();
        void Move(double nx, double ny){x = nx; y = ny;}
        virtual double Area() const = 0; // a pure virtual function
        virtual void Display() = 0;
};

BaseConic::~BaseConic(){
	//do nothing no memory allocated
}

BaseConic::BaseConic(double nx, double ny){
	x = nx;
	y = ny;
}

//****************** Ellipse class and functions ***********************//

class Ellipse : public BaseConic{
    private:
        double x;
        double y;
        double a; // semi-major axis
        double b; // semi-minor axis
        double angle; // orientation angle

    public:
        void Move(double nx, double ny){x = nx; y = ny;}
        Ellipse(double na,double nb,double nx,double ny,double nang);
        double Area() const
            {return 3.14159 * a * b;}
        void Rotate(double nang)
            {angle += nang;}
        void Resize(double na, double nb){a = na; b = nb;}
        void VertPos();
        void Display();
};

//constructor
Ellipse::Ellipse(double na, double nb, double nx, double ny, double nang){
	a = na;
	b = nb;
	x = nx;
	y = ny;
	angle = nang;
}

//vertices position
void Ellipse::VertPos(){
    double v1x, v1y, v2x, v2y, v3x, v3y, v4x, v4y;
    v1x = x + a;
    v1y = y;

    v2x = x - a;
    v2y = y;

    v3x = x;
    v3y = y + b;

    v4x = x;
    v4y = y - b;

    cout<<"Location of Vertices: "<<endl;
    cout<<"( "<<v1x<<", "<<v1y<<")"<<endl;
    cout<<"( "<<v2x<<", "<<v2y<<")"<<endl;

    cout<<"Location of Co-Vertices: "<<endl;
    cout<<"( "<<v3x<<", "<<v3y<<")"<<endl;
    cout<<"( "<<v4x<<", "<<v4y<<")"<<endl;
}

//display ellipse info
void Ellipse::Display(){
    cout<<"x = "<<x<<endl;
    cout<<"y = "<<y<<endl;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    cout<<"angle = "<<angle<<endl;
}



//******************** Circle class and functions ******************//

class Circle : BaseConic{
    private:
        double x;
        double y;
        double radius;

    public:
        Circle(double nx,double ny,double nr);
        void Move(double nx, double ny){x = nx; y = ny;}
        double Area() const
        {return 3.14159 * radius * radius;}
        void Resize(double nr){radius = nr;}
        void IsPt(double nx, double ny);
        void Display();
};

//constructor
Circle::Circle(double nx, double ny, double nr){
	x = nx;
	y = ny;
	radius = nr;
}

//display circle info
void Circle::Display(){
    cout<<"x = "<<x<<endl;
    cout<<"y = "<<y<<endl;
    cout<<"radius = "<<radius<<endl;
}

//calculates if point is inside circle
void Circle::IsPt(double nx, double ny){
    double d;
    d = sqrt((x-nx)*(x-nx) + (y-ny)*(y-ny));
    if (d == radius)
        cout<<"Point is on the circle"<<endl;
    else if (d > radius)
        cout<<"Point is outside the circle"<<endl;
    else if (d < radius)
        cout<<"Point is inside the circle"<<endl;
    else
        cout<<"Error calculating d"<<endl;
}


int main() {

	//testing ellipse functions
	Ellipse e1(1, 3, 5, 7, 9);
	cout<<"Area = "<<e1.Area()<<endl;
	e1.Resize(6,7);
	e1.Display();
	e1.VertPos();
	e1.Rotate(10);
	e1.Display();
	e1.VertPos();
	e1.Move(15,10);
	e1.Display();
	e1.VertPos();

	//testing circle functions
	Circle c1(4, 5, 3);
	cout<<"Area = "<<c1.Area()<<endl;
	c1.Display();
	c1.IsPt(1, 2);
	c1.Move(10, 5);
	c1.Display();
	c1.Resize(7);
	c1.Display();

	//testing pointer
	BaseConic* p1 = &e1;
	p1->Display();
	return 0;
}
