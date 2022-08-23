#include <windows.h>
#include <gl/GL.h>
#include <gl/glu.h>			
#include <fstream>
#include <math.h>
#include "camera.h"
#include <stdlib.h>

#include <vector>
#include "unit.cpp"

using namespace std;

#define SQR(x) (x*x)

#define NULL_VECTOR Vector3dCreate(0.0f,0.0f,0.0f)

Vector3dStruct Vector3dCreate ( float x, float y, float z )
{
	Vector3dStruct tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

float LengthVector3d( Vector3dStruct * v)
{
	return (float)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

Vector3dStruct NormalizeVector3d( Vector3dStruct v)
{
	Vector3dStruct res;
	float L = LengthVector3d(&v);
	if (L == 0.0f) return NULL_VECTOR;
	res.x = v.x / L;
	res.y = v.y / L;
	res.z = v.z / L;
	return res;
}

Vector3dStruct operator+ (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res;
	res.x = v.x+u.x;
	res.y = v.y+u.y;
	res.z = v.z+u.z;
	return res;
}
Vector3dStruct operator- (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res;
	res.x = v.x-u.x;
	res.y = v.y-u.y;
	res.z = v.z-u.z;
	return res;
}


Vector3dStruct operator* (Vector3dStruct v, float r)
{
	Vector3dStruct res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}


Vector3dStruct CrossProduct (Vector3dStruct u, Vector3dStruct v)
{
	Vector3dStruct resVector;
	resVector.x = u.y*v.z - u.z*v.y;
	resVector.y = u.z*v.x - u.x*v.z;
	resVector.z = u.x*v.y - u.y*v.x;

	return resVector;

}
float operator* (Vector3dStruct v, Vector3dStruct u)
{
	return v.x*u.x+v.y*u.y+v.z*u.z;
}




/***************************************************************************************/


Camera::Camera()
{
	
	Position = Vector3dCreate (0.0, 10.0, 200.0);
	View = Vector3dCreate( 0.0, 0.0, -1.0);
	RightVector = Vector3dCreate (1.0, 0.0, 0.0);
	Up = Vector3dCreate (0.0, 1.0, 0.0);
	qddo = 0 ;

	RotatedX = RotatedY = RotatedZ = 0.0;
}

void Camera::Move (Vector3dStruct Direction)
{
	Position = Position + Direction;
}

void Camera::RotateX (float Angle)
{

	if (-90 < RotatedX && RotatedX < 90)
	{
		RotatedX += Angle;
		//View = NormalizeVector3d(View * cosf(Angle * PIdiv180) + Up * sinf(Angle * PIdiv180));
	}
	else
	{
		if (RotatedX > 90)
		{
			if (Angle < 0)
			{
				RotatedX += Angle;
				//View = NormalizeVector3d(View * cosf(Angle * PIdiv180) + Up * sinf(Angle * PIdiv180));
			}
		}
		if (RotatedX < -90)
		{
			if (Angle > 0)
			{
				RotatedX += Angle;
				//View = NormalizeVector3d(View * cosf(Angle * PIdiv180) + Up * sinf(Angle * PIdiv180));
			}
		}
	}
	//View = NormalizeVector3d(View * cosf(Angle * PIdiv180) + Up * sinf(Angle * PIdiv180));
	//Up = CrossProduct(View, RightVector)*-1;
}

void Camera::RotateY (float Angle)
{
	RotatedY += Angle;
	
	View = NormalizeVector3d(View*cosf(Angle*PIdiv180)- RightVector*sinf(Angle*PIdiv180));

	RightVector = CrossProduct(View, Up);
}


void Camera::RotateZ (float Angle)
{
	RotatedZ += Angle;

	RightVector = NormalizeVector3d(RightVector*cosf(Angle*PIdiv180)+ Up*sinf(Angle*PIdiv180));
	
	Up = CrossProduct(View, RightVector)*-1;
}

void Camera::Render( void )
{	
	Vector3dStruct ViewPoint = Position+View;
	glRotated(-RotatedX , 1 , 0 , 0);
	gluLookAt(	Position.x , Position.y , Position.z , ViewPoint.x , ViewPoint.y , ViewPoint.z , Up.x , Up.y , Up.z);
	
}

bool Camera::UnBlock(Vector3dStruct positionToCheck , vector<unit> &allunits)
{
	for (int i = 0; i < allunits.size(); i++)
	{
		{
			if ((positionToCheck.x - allunits[i].x >= -1) && (positionToCheck.x - (allunits[i].x + allunits[i].width) <= 1))
			{
				if (((positionToCheck.z) - (allunits[i].z) >= -1) && (positionToCheck.z - (allunits[i].z + allunits[i].length) <= 1))
				{
					if ( (positionToCheck.y - allunits[i].y >= -1) && (positionToCheck.y - (allunits[i].y + allunits[i].hight) <= 1))
					{
						return false;
					}
				}
			}
		}
	}
	
	
	return true;
}


void Camera::MoveForwardWitout(float Distance)
{
	Vector3dStruct temp = Position + (View * Distance);
		Position = temp;
}


void Camera::MoveForward(float Distance , vector<unit>& allunits)
{
	Vector3dStruct temp = Position + (View * Distance);
	if (UnBlock(temp , allunits))
	{
		Position = temp;
		this->MoveUpward(0.5 * sin(qddo) );
		qddo += PI/4;
	}
}


void Camera::MoveUpward(float Distance)
{
	Position = Position + (Up * Distance);
}

bool Camera::inRangeOfPosition(pair<float, float> positionToCheck)
{
	if (Position.x > positionToCheck.first && Position.x < positionToCheck.first+12)
	{
		if (Position.z > positionToCheck.second && Position.z < positionToCheck.second + 12)
		{
			return true;
		}
	}
	return false;
}


void Camera::MoveRight ( float Distance , vector<unit>& allunits)
{
	Vector3dStruct temp = Position + (RightVector * Distance);
	if (UnBlock(temp, allunits))
	{
		Position = temp;
	}
}


void Camera::MoveUpward( float Distance, vector<unit>& allunits , pair<float, float> position)
{

	Vector3dStruct temp = Position + (Up * Distance);
	if (UnBlock(temp, allunits) && inRangeOfPosition(position))
	{
		Position = temp;
	}
}

void Camera::SetRotateX( float Angle )
{
	View = Vector3dCreate( 0.0, 0.0, -1.0);
	RightVector = Vector3dCreate (1.0, 0.0, 0.0);
	Up = Vector3dCreate (0.0, 1.0, 0.0);
	RotatedX=Angle;
}
