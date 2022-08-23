#include <windows.h>		
#include <glaux.h>	
#include <vector>
#include "unit.cpp"


using namespace std;


class Box
{

private:
	float x;
	float y;
	float z;
	float size;
	float height;

public:

	static int boxTexture;

	Box(float x, float y, float z ,float size, float height)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->size = size;
		this->height = height;
	}


	void allocate(vector<unit> &V)
	{
		unit temp( x , y , z , size , size , height );
		V.push_back(temp);
	}




	void Draw()
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		/*--------- BuildRound ---------*/
		// Draw The Cube Using quads

		/*---------  top ---------*/
		glBindTexture(GL_TEXTURE_2D, boxTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, y+height, z + size);   // Bottom Left Of The Quad (Top)
		glTexCoord2s(1.0, 0.0); glVertex3f(x + size, y+height, z + size);    // Bottom Right Of The Quad (Top)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, y+height, z);    // Top Right Of The Quad (Top)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, y+height, z);   // Top Left Of The Quad (Top)
		glEnd();

		/*---------  Bottom ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, y , z + size);    // Bottom Left Of The Quad (Bottom)
		glTexCoord2f(1.0, 0.0); glVertex3f(x + size, y, z + size);   // Bottom Right Of The Quad (Bottom)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, y, z);   // Top Right Of The Quad (Bottom)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, y, z);    // Top Left Of The Quad (Bottom)
		glEnd();

		/*--------- Front ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, y, z + size);    // Bottom Left Of The Quad (front)
		glTexCoord2f(1.0, 0.0); glVertex3f(x + size, y , z + size);    // Bottom Right Of The Quad (front)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, y+height, z + size);    // up Right Of The Quad (front)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, y+height, z + size);    // up Left Of The Quad (front)
		glEnd();

		/*--------- Back ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, y, z);    // Bottom Left Of The Quad (back)
		glTexCoord2f(1.0, 0.0); glVertex3f(x + size, y, z);    // Bottom Right Of The Quad (back)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, y+height, z);    // up Right Of The Quad (back)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, y+height, z);    // up Left Of The Quad (back)
		glEnd();

		/*---------  Right ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x + size, y, z);    //  Bottom Left Of The Quad (right)
		glTexCoord2f(1.0, 0.0);	glVertex3f(x + size, y, z + size);    // Bottom right Of The Quad (right)
		glTexCoord2f(1.0, 1.0);	glVertex3f(x + size, y+height, z + size);    // Top right Of The Quad (right)
		glTexCoord2f(0.0, 1.0); glVertex3f(x + size, y+height, z);    // Top Left Of The Quad (right)
		glEnd();

		/*---------  Left ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, y, z);    //  Bottom Left Of The Quad (left)
		glTexCoord2f(1.0, 0.0); glVertex3f(x, y, z + size);    // Bottom right Of The Quad (left)
		glTexCoord2f(1.0, 1.0); glVertex3f(x, y+height, z + size);    // Top right Of The Quad (left)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, y+height, z);    // Top Left Of The Quad (left)
		glEnd();

		// cube is done
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}


	~Box() {}
};
