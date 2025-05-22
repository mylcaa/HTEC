#include <vector>
#include <iostream>
#include <memory>

class Point
{
private:
	int x{};
	int y{};

public:
	Point(int x, int y)
		: x{ x }, y{ y }
	{}

	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "Point(" << p.x << ", " << p.y << ')';
	}
};

class Shape{
    public:

    virtual std::ostream& print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& shape){
        return shape.print(out);
    }
    virtual ~Shape() = default;
};

class Triangle: public Shape{
    protected:
        Point a;
        Point b;
        Point c;
    public:
        Triangle(Point aa, Point bb, Point cc): 
        a{aa},
        b{bb},
        c{cc}
        {}

        std::ostream& print(std::ostream& out) const override{
            out << "Triangle(" << a << ", " << b << ", " << c << ")";
            return out;
        }

        friend std::ostream& operator<<(std::ostream& out, const Triangle& triangle){
            return triangle.print(out);
        }

};

class Circle: public Shape{
    protected:
        Point o;
        int radius;
    public:
        Circle(Point oo, int r):
        o{oo},
        radius{r}
        {}

        int getRadius() const {return radius;}

        std::ostream& print(std::ostream& out) const override{
            out << "Circle(" << o << ", radius " << radius;
            return out;
        }

        friend std::ostream& operator<<(std::ostream& out, const Circle& circle){
            return circle.print(out);
        }
};

int getLargestRadius(std::vector<std::unique_ptr<Shape>>& v){
    int max_radius = 0;

    for(int i = 0; i < v.size(); ++i){
        Circle* ptr = dynamic_cast<Circle*>(v[i].get());
        if(ptr != nullptr){
            max_radius = (ptr->getRadius() > max_radius ? ptr->getRadius() : max_radius); 
        }
    }

    return max_radius;
}

int main()
{
	std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Circle>(Point{ 1, 2 }, 7));
    v.push_back(std::make_unique<Triangle>(Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }));
    v.push_back(std::make_unique<Circle>(Point{ 7, 8 }, 3));

	// print each shape in vector v on its own line here
    for(int i = 0; i < v.size(); ++i){
        std::cout << *v[i] << '\n';
    }

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	return 0;
}