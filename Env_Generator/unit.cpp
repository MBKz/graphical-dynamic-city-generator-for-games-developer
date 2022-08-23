#pragma once


class unit
{
public:

	float x, y, z;
	float length, width, hight;
public:
	unit(float x , float y, float z , float width ,float length  , float hight)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->width = width;
		this->length = length;
		this->hight = hight;
	};
	~unit() {};


	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getZ()
	{
		return z;
	}
	float getLength()
	{
		return length;
	}
	float getWidth()
	{
		return width;
	}
	float getHight()
	{
		return hight;
	}
};