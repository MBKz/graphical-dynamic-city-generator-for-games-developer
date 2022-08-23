//***************************************************************************
//  Camera based on Vectors
//***************************************************************************

#include <glut.h>	

#include <vector>
#include "unit.cpp"

using namespace std;
#define PI 3.141592653589
#define PIdiv180 (PI/180.0)

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct Vector3dStruct  
{
	float x,y,z;
};
Vector3dStruct Vector3dCreate ( float x, float y, float z );
Vector3dStruct NormalizeVector3d( Vector3dStruct v);

class Camera
{
public:
	
	Vector3dStruct View;
	Vector3dStruct RightVector;	
	Vector3dStruct Up;
	Vector3dStruct Position;

	float RotatedX, RotatedY, RotatedZ;	

	float qddo;
	
public:
	Camera();	
	void Render ( void );	
							

	void Move ( Vector3dStruct Direction );
	void RotateX ( float Angle );
	void RotateY ( float Angle );
	void RotateZ ( float Angle );

	void MoveForward ( float Distance , vector<unit>& allunits);
	void MoveUpward(float Distance);
	bool inRangeOfPosition(pair<float, float> positionToCheck);
	void MoveUpward ( float Distance, vector<unit>& allunits , pair<float, float> position);
	void MoveRight ( float Distance , vector<unit>& allunits);
	bool UnBlock(Vector3dStruct positionToCheck, vector<unit>& allunits);

	void MoveForwardWitout(float Distance);

	void SetRotateX(float Angle);



};


