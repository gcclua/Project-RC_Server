//----------------------------------------------
//	CreateTime  : 
//	Author      : Taylor Liang
//	Project     : 
//	Company     : 
//	Instruction : Utils and Converts of UnityEngine module
//	ChangeLog   : None
//----------------------------------------------

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <vector>


class Utils
{
public:
	static int Clamp(int val, int min, int max);

	static void Log(const std::string &info);

	static bool Assert(bool p_flag, const std::string &info);

	static void Split(const std::string &s, char delim, std::vector<std::string> &elems);

	static std::vector<std::string> Split(const std::string &s, char delim);

	static void LogError(const std::string &info);
};

class Vector3
{
public:
	Vector3(float p_x, float p_y, float p_z);

	float x;
	float y;
	float z;

	const float getmagnitude() const;

	Vector3 operator + (Vector3 p_vec2);

	Vector3 operator - (Vector3 p_vec2);

	Vector3 operator *(float kine);

	Vector3 operator / (float kine);

private:
	void InitializeInstanceFields();
};

class Vector2
{
public:
	Vector2(float p_x, float p_y);

	float x;
	float y;

	Vector2 operator *(float kine);

private:
	void InitializeInstanceFields();
};

class Color
{
public:
	Color();

	Color(float p_r, float p_g, float p_b, float p_a);

	float r;
	float g;
	float b;
	float a;

private:
	void InitializeInstanceFields();
};
