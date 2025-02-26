#pragma once
#include <iostream>
#include "checkML.h"
using namespace std;

template <typename T = int>
class Vector2D {
private:
	T x;
	T y;
public:
	Vector2D(T _x = 0, T _y = 0) : x(_x), y(_y) {}
	T getX() const { return x; }
	T getY() const { return y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	// Suma de vectores
	Vector2D operator+(const Vector2D& other) const {
		int _x = x + other.getX();
		int _y = y + other.getY();
		return Vector2D(_x, _y);
	}
	// Suma
	void operator+= (const Vector2D& other) {
		x = x + other.getX();
		y = y + other.getY();
	}
	// Resta de vectores
	Vector2D operator-(const Vector2D& other) const {
		int _x = x - other.getX();
		int _y = y - other.getY();
		return Vector2D(_x, _y);
	}
	void operator-= (const Vector2D& other) {
		x = x - other.getX();
		y = y - other.getY();
	}
	// Producto escalar
	T operator*(const Vector2D& other) const {
		int prod = x * other.getX() + y * other.getY();
		return prod;
	}
	// Vector * escalar
	Vector2D operator*(const T esc) const {
		int _x = x * esc;
		int _y = y * esc;
		return Vector2D(_x, _y);
	}
	bool operator==(const Vector2D& otro) {
		return x == otro.getX() && otro.getY();
	}
	friend istream& operator>>(istream& in, Vector2D& v) {
		in >> v.x >> v.y;
		return in;
	}
};
// Alias Point2D para la clase
template<typename T = int> using Point2D = Vector2D<T>;