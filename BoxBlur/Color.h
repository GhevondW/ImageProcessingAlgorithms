#ifndef _COLOR_H__
#define _COLOR_H__
 
class Color
{
public:
	Color();
	Color(int r,int g,int b);
	Color(const Color& other) = default;
	Color(Color&& other) = default;
	~Color();

public:
	int get_r()const;
	int get_g()const;
	int get_b()const;

	void set_r(int value);
	void set_g(int value);
	void set_b(int value);

private:
	int r_;
	int g_;
	int b_;
};

#endif // !_COLOR_H__
