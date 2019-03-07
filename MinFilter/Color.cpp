#include "Color.h"

Color::Color()
	:r_(0),
	g_(0),
	b_(0)
{

}

Color::Color(int r,int g,int b) 
	:r_(r),
	g_(g),
	b_(b)
{
}

Color::~Color() {
	
}

int Color::get_r()const {
	return r_;
}
int Color::get_g()const {
	return g_;
}
int Color::get_b()const {
	return b_;
}

void Color::set_r(int value) {
	if (value >= 0 && value <= 255) {
		r_ = value;
	}
}
void Color::set_g(int value) {
	if (value >= 0 && value <= 255) {
		g_ = value;
	}
}
void Color::set_b(int value) {
	if (value >= 0 && value <= 255) {
		b_ = value;
	}
}