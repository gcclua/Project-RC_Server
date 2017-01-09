#include "Utils.h"
#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, const std::string& cs)
{
	out << cs.data();
	return out;
}

int Utils::Clamp(int val, int min, int max)
{
	if (val < min)
	{
		return min;
	}
	else if (val > max)
	{
		return max;
	}
	else
	{
		return val;
	}
}

void Utils::Log(const std::string &info)
{
	std::cout << std::string("[Info]") << info << std::endl;
}

bool Utils::Assert(bool p_flag, const std::string &info)
{
	if (!p_flag)
	{
		std::cout << std::string("[Assert fail]") << info << std::endl;

		return false;
	}
	else
	{
		return true;
	}
}

void Utils::Split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}


std::vector<std::string> Utils::Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	Utils::Split(s, delim, elems);
	return elems;
}

void Utils::LogError(const std::string &info)
{
	std::cout << std::string("[Error]") << info << std::endl;
}

Vector3::Vector3(float p_x, float p_y, float p_z)
{
	InitializeInstanceFields();
	x = p_x;
	y = p_y;
	z = p_z;
}

const float Vector3::getmagnitude() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::operator + (Vector3 p_vec2)
{
	return Vector3(this->x + p_vec2.x, this->y + p_vec2.y, this->z + p_vec2.z);
}

Vector3 Vector3::operator - (Vector3 p_vec2)
{
	return Vector3(this->x - p_vec2.x, this->y - p_vec2.y, this->z - p_vec2.z);
}

Vector3 Vector3::operator *(float kine)
{
	return Vector3(this->x * kine, this->y * kine, this->z * kine);
}

Vector3 Vector3::operator / (float kine)
{
	return Vector3(this->x / kine, this->y / kine, this->z / kine);
}

void Vector3::InitializeInstanceFields()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector2::Vector2(float p_x, float p_y)
{
	InitializeInstanceFields();
	x = p_x;
	y = p_y;
}

Vector2 Vector2::operator *(float kine)
{
	return Vector2(this->x * kine, this->y * kine);
}

void Vector2::InitializeInstanceFields()
{
	x = 0;
	y = 0;
}

Color::Color()
{

	InitializeInstanceFields();
}

Color::Color(float p_r, float p_g, float p_b, float p_a)
{
	InitializeInstanceFields();
	r = p_r;
	g = p_g;
	b = p_b;
	a = p_a;
}

void Color::InitializeInstanceFields()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}
