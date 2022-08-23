#include <windows.h>		
#include <glaux.h>	

#include <vector>
#include "unit.cpp"


using namespace std;

class Cupe
{
private:
	int x;
	int z;
	int size;
	int height;

	//0 for skyBox else for building
	int type;

	bool day ;
	

public:
	int static aroundBuildingTextureId;
	int static BuildingTextureId[6];
	int static BuildNight[6];
	int static skyBoxTexture1Id[6];
	int static skyBoxTexture2Id[6];

	Cupe(){}


	Cupe(int x, int z, int size, int height, int type)
	{
		this->x = x;
		this->z = z;
		this->size = size;
		this->height = height;
		this->type = type;
		day = true;
	}
	~Cupe(){}


	void allocate(vector<unit>& V)
	{
		
		if (type == 0)
		{
			unit north( x , 0 , (z+size) , (size) , 10 , height );
			V.push_back(north);

			unit south( x , 0 , z-10 , size , 10 ,  height );
			V.push_back(south);

			unit east( (x+size) , 0 , z , 10 , (size) , height);
			V.push_back(east);

			unit west( (x-10) , 0, z, 10, (size), height);
			V.push_back(west);

			unit up( x ,  0+height , z , size , size , 10);
			V.push_back(up);

			unit down( x , -5, z , size , size , 5);
			V.push_back(down);

		}
		else
		{
			unit temp(x-5, 0, z-5, size+10, size+10, height);
			V.push_back(temp);
		}
	}

	void switchDayToNight()
	{
		day = false;
	}

	void switchNightToDay()
	{
		day = true;
	}

	void choose_TextureToBind(int index)
	{
		if (type == 0)
		{
			if (day)
			{
				glBindTexture(GL_TEXTURE_2D, skyBoxTexture1Id[index]);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, skyBoxTexture2Id[index]);
			}	
		}
		else
		{
			if (day)
			{
				glBindTexture(GL_TEXTURE_2D, BuildingTextureId[index]);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, BuildNight[index]);

			}
		}	
	}


	void Draw()
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		/*--------- BuildRound ---------*/
		// Draw The Cube Using quads

		/*---------  up ---------*/
		choose_TextureToBind(0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, height, z + size);   // Bottom Left Of The Quad (Top)
		glTexCoord2s(1.0, 0.0); glVertex3f(x + size, height, z + size);    // Bottom Right Of The Quad (Top)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, height, z);    // Top Right Of The Quad (Top)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z);   // Top Left Of The Quad (Top)
		glEnd();

		/*--------- Bottom ---------*/
		if (type != 0) 
		{
			glBindTexture(GL_TEXTURE_2D, aroundBuildingTextureId);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x - 10, 0.01, z + size + 10);    // Bottom Left Of The Quad (Bottom)
			glTexCoord2f(1.0, 0.0); glVertex3f(x + size + 10, 0.01, z + size + 10);   // Bottom Right Of The Quad (Bottom)
			glTexCoord2f(1.0, 1.0); glVertex3f(x + size + 10, 0.01, z - 10);   // Top Right Of The Quad (Bottom)
			glTexCoord2f(0.0, 1.0); glVertex3f(x - 10, 0.01, z - 10);    // Top Left Of The Quad (Bottom)
			glEnd();

			/*--------- Bottom ---------*/
			choose_TextureToBind(1);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, 0.02, z + size);    // Bottom Left Of The Quad (Bottom)
			glTexCoord2f(10.0, 0.0); glVertex3f(x + size, 0.02, z + size);   // Bottom Right Of The Quad (Bottom)
			glTexCoord2f(10.0, 10.0); glVertex3f(x + size, 0.02, z);   // Top Right Of The Quad (Bottom)
			glTexCoord2f(0.0, 10.0); glVertex3f(x, 0.02, z);    // Top Left Of The Quad (Bottom)
			glEnd();
		}
		if (type == 0) {

			/*--------- Bottom ---------*/
			choose_TextureToBind(1);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z + size);    // Bottom Left Of The Quad (Bottom)
			glTexCoord2f(size/50 , 0.0); glVertex3f(x + size, 0, z + size);   // Bottom Right Of The Quad (Bottom)
			glTexCoord2f(size / 50, size / 50); glVertex3f(x + size, 0, z);   // Top Right Of The Quad (Bottom)
			glTexCoord2f(0.0, size / 50); glVertex3f(x, 0, z);    // Top Left Of The Quad (Bottom)
			glEnd();
		}


		/*--------- Front ---------*/
		choose_TextureToBind(2);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z + size);    // Bottom Left Of The Quad (front)
		glTexCoord2f(1.0, 0.0); glVertex3f(x + size, 0, z + size);    // Bottom Right Of The Quad (front)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, height, z + size);    // up Right Of The Quad (front)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z + size);    // up Left Of The Quad (front)
		glEnd();

		/*--------- Back ---------*/
		choose_TextureToBind(3);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);    // Bottom Left Of The Quad (back)
		glTexCoord2f(1.0, 0.0); glVertex3f(x + size, 0, z);    // Bottom Right Of The Quad (back)
		glTexCoord2f(1.0, 1.0); glVertex3f(x + size, height, z);    // up Right Of The Quad (back)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z);    // up Left Of The Quad (back)
		glEnd();

		/*---------  Right ---------*/
		choose_TextureToBind(4);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x + size, 0, z);    //  Bottom Left Of The Quad (right)
		glTexCoord2f(1.0, 0.0);	glVertex3f(x + size, 0, z + size);    // Bottom right Of The Quad (right)
		glTexCoord2f(1.0, 1.0);	glVertex3f(x + size, height, z + size);    // Top right Of The Quad (right)
		glTexCoord2f(0.0, 1.0); glVertex3f(x + size, height, z);    // Top Left Of The Quad (right)
		glEnd();

		/*---------  Left ---------*/
		choose_TextureToBind(5);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);    //  Bottom Left Of The Quad (left)
		glTexCoord2f(1.0, 0.0); glVertex3f(x, 0, z + size);    // Bottom right Of The Quad (left)
		glTexCoord2f(1.0, 1.0); glVertex3f(x, height, z + size);    // Top right Of The Quad (left)
		glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z);    // Top Left Of The Quad (left)
		glEnd();

		// cube is done
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

};
