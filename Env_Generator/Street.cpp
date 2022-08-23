#include <windows.h>		
#include <glaux.h>	
#include <queue>

using namespace std;

class  Street
{
private:
	float x1;
	float z1;
	float x2;
	float z2;
	float widthStreet;
	

public:
	static int verticalStreetTexture;
	static int horizontalStreetTexture;

	Street(float x1, float z1, float x2, float z2)
	{
		this->x1 = x1;
		this->z1 = z1;
		this->x2 = x2;
		this->z2 = z2;
		widthStreet = 60;
	}
	float getx1 (){return x1 ;}
	float getz1 (){return z1 ;}
	float getx2 (){return x2 ;}
	float getz2 (){return z2 ;}
	~Street(){}

	void Draw()
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		if (x1 == x2)
		{
			if (z1 < z2) swap(z1, z2);
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, verticalStreetTexture);
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x1 - widthStreet / 2, 0 , z2);

			glTexCoord2f(0.0, 10.0);
			glVertex3f(x1 - widthStreet / 2, 0 , z1);
			glTexCoord2f(1.0, 10.0);
			glVertex3f(x1 + widthStreet / 2, 0 , z1);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x1 + widthStreet / 2, 0, z2);
			glEnd();
			glPopMatrix();
		}
		else
		{
			if (x1 < x2) swap(x1, x2);
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, horizontalStreetTexture);
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x2, 0, z1 - widthStreet / 2);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x2, 0 , z1 + widthStreet / 2);
			glTexCoord2f(10.0, 1.0);
			glVertex3f(x1, 0 , z1 + widthStreet / 2 );
			glTexCoord2f(10.0, 0.0); 
			glVertex3f(x1, 0 , z1 - widthStreet / 2);
			glEnd();
			glPopMatrix();
		}
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
};




