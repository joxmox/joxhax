/*
 * Shapes.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: sebis
 */

#ifndef SRC_LIB_SHAPES_HPP_
#define SRC_LIB_SHAPES_HPP_

#define PI 3.1415927

class Shape {
public:
	virtual double area() const = 0;
};

class Circle: public Shape {
	double radius;
public:
	Circle(double r): radius(r) {}
	double area() const override {return PI * radius * radius;}
};

class Triangle: public Shape {
	double base;
	double height;
public:
	Triangle(double b, double h): base(b), height(h) {}
	double area() const override {return base * height / 2;}
};

class Rectangle: public Shape {
	double width;
	double height;
public:
	Rectangle(double w, double h): width(w), height(h) {}
	double area() const override {return width * height;}
};

class Square: public Rectangle {
	double side;
	Square(double s): Rectangle(s, s), side(s) {}
};




#endif /* SRC_LIB_SHAPES_HPP_ */
