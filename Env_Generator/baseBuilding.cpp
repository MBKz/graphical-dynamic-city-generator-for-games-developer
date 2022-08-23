#include <windows.h>		
#include <glaux.h>	

#include <vector>
#include "unit.cpp"

using namespace std;
class baseBuilding
{
private:
	float x;
	float z;
	int floorNum;
	int roomNum;

	int sizeFloor;
	int sizeRoom;


public:
	int static houseTexture[3];
	int static roomTexture[5];

	baseBuilding(){}

	baseBuilding(float x, float z, int floorNum, int roomNum)
	{
		this->x = x;
		this->z = z;
		this->floorNum = floorNum;
		this->roomNum = roomNum;
		sizeFloor = 120;
		sizeRoom = 50;
	}
	~baseBuilding() {}

	void allocateFloors(vector<unit>& V, int numOfFloors)
	{
		int heightOfFloor = numOfFloors * 30;
		int RangeViewDown = 17;
		int RangeViewUp = 20;

		//north;
		unit north(x, heightOfFloor, z + sizeFloor, sizeFloor, 5, 30);
		V.push_back(north);

		//east
		unit east(x, heightOfFloor, z, 5, sizeFloor, 30);
		V.push_back(east);

		//west
		unit west(x + sizeFloor, heightOfFloor, z, 5, sizeFloor, 30);
		V.push_back(west);

		//south;
		unit south(x, heightOfFloor, z, sizeFloor, 5, 30);
		V.push_back(south);

		if (numOfFloors == floorNum)
		{
			unit up(x, heightOfFloor - RangeViewDown + 30, z, sizeFloor, sizeFloor, RangeViewUp);
			V.push_back(up);
		}
		else
		{
			unit upOne(x + 15, heightOfFloor - RangeViewDown + 30, z, sizeFloor - 15, sizeFloor, RangeViewUp);
			V.push_back(upOne);

			unit upTwo(x, heightOfFloor - RangeViewDown + 30, z + 15, 15, sizeFloor + 15, RangeViewUp);
			V.push_back(upTwo);
		}


	}

	void allocate(vector<unit>& V)
	{


		//round of the first floor

		//north;
		unit northright(x, 0, z + sizeFloor, (sizeFloor / 2.3), 5, 30);
		unit northMidlle(x + (sizeFloor / 2.3), 15, z + sizeFloor, 15.6, 5, 15);
		unit northLeft(x + (sizeFloor / 2.3) + 15, 0, z + sizeFloor, (sizeFloor / 2.3), 5, 30);

		V.push_back(northright);
		V.push_back(northMidlle);
		V.push_back(northLeft);

		//east
		unit east(x, 0, z, 5, sizeFloor, 30);
		V.push_back(east);

		//west
		unit west(x + sizeFloor, 0, z, 5, sizeFloor, 30);
		V.push_back(west);

		//south;
		unit southright(x, 0, z, (sizeFloor / 2.3), 5, 30);
		unit southMidlle(x + (sizeFloor / 2.3), 15, z, 15.6, 5, 15);
		unit southLeft(x + (sizeFloor / 2.3) + 15, 0, z, (sizeFloor / 2.3), 5, 30);

		V.push_back(southright);
		V.push_back(southMidlle);
		V.push_back(southLeft);

		//up
		unit upOne(x + 15, 13, z, sizeFloor - 15, sizeFloor, 20);
		V.push_back(upOne);

		unit upTwo(x, 13, z + 15, 15, sizeFloor - 15, 20);
		V.push_back(upTwo);




		//Down
		unit Down(x, 0, z, sizeFloor, sizeFloor, 7);
		V.push_back(Down);





		for (int i = 1; i <= floorNum; i++)
		{
			allocateFloors(V, i);
		}
	}

	void elevator(float x, float z, int floorNum)
	{
		float  height = floorNum * 30;
		int size = 15;
		glPushMatrix();
		glColor3f(0, 1, 1);
		/*---------  up ---------*/

		glBegin(GL_QUADS);
		glVertex3f(x, height, z + size);   // Bottom Left Of The Quad (Top)
		glVertex3f(x + size, height, z + size);    // Bottom Right Of The Quad (Top)
		glVertex3f(x + size, height, z);    // Top Right Of The Quad (Top)
		glVertex3f(x, height, z);   // Top Left Of The Quad (Top)
		glEnd();

		/*--------- Bottom ---------*/

		glBegin(GL_QUADS);
		glVertex3f(x, 0.05, z + size);    // Bottom Left Of The Quad (Bottom)
		glVertex3f(x + size, 0.05, z + size);   // Bottom Right Of The Quad (Bottom)
		glVertex3f(x + size, 0.05, z);   // Top Right Of The Quad (Bottom)
		glVertex3f(x, 0.05, z);    // Top Left Of The Quad (Bottom)
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1, 1, 1, 0.5);
		choose_TextureToBind(1, 0);
		/*--------- Back ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);    // Bottom Left Of The Quad (back)
		glTexCoord2f(1.0, 0.0); glVertex3f(x + size, 0, z);    // Bottom Right Of The Quad (back)
		glTexCoord2f(1.0, 2 * floorNum); glVertex3f(x + size, height, z);    // up Right Of The Quad (back)
		glTexCoord2f(0.0, 2 * floorNum); glVertex3f(x, height, z);    // up Left Of The Quad (back)
		glEnd();

		/*---------  Left ---------*/
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z);    //  Bottom Left Of The Quad (left)
		glTexCoord2f(1.0, 0.0); glVertex3f(x, 0, z + size);    // Bottom right Of The Quad (left)
		glTexCoord2f(1.0, 2 * floorNum); glVertex3f(x, height, z + size);    // Top right Of The Quad (left)
		glTexCoord2f(0.0, 2 * floorNum); glVertex3f(x, height, z);    // Top Left Of The Quad (left)
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
		glColor4f(1, 1, 1, 255);
	}

	void choose_TextureToBind(int index, int type)
	{
		if (type == 0)
		{
			glBindTexture(GL_TEXTURE_2D, houseTexture[index]);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, roomTexture[index]);
		}
	}


	void RoomFloor(float x, float z, float floor, int type)
	{
		glPushMatrix();
		float ground = (floor - 1) * 30, height = floor * 30;
		int size, elevatorSize = 15; // elev is 1/8 of floor
		if (type == 0) size = 120;
		else size = 50;

		glEnable(GL_TEXTURE_2D);
		ground = ground + 0.05;

		if (type == 0) {
			// floor 
			height = height - 0.05;
			/*---------  up floor ---------*/
			choose_TextureToBind(0, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x + elevatorSize, height, z + 15);   // Bottom Left Of The Quad (Top)
			glTexCoord2s(3.0, 0.0); glVertex3f(x + size, height, z + elevatorSize);    // Bottom Right Of The Quad (Top)
			glTexCoord2f(3.0, 1.0); glVertex3f(x + size, height, z);    // Top Right Of The Quad (Top)
			glTexCoord2f(0.0, 1.0); glVertex3f(x + elevatorSize, height, z);   // Top Left Of The Quad (Top)
			glEnd();

			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, height, z + size);   // Bottom Left Of The Quad (Top)
			glTexCoord2s(3.0, 0.0); glVertex3f(x + size, height, z + size);    // Bottom Right Of The Quad (Top)
			glTexCoord2f(3.0, 3.0); glVertex3f(x + size, height, z + elevatorSize);    // Top Right Of The Quad (Top)
			glTexCoord2f(0.0, 3.0); glVertex3f(x, height, z + elevatorSize);   // Top Left Of The Quad (Top)
			glEnd();


			/*--------- Bottom floor ---------*/
			choose_TextureToBind(2, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x + elevatorSize, ground, z + elevatorSize);   // Bottom Left Of The Quad (Top)
			glTexCoord2s(3.0, 0.0); glVertex3f(x + size, ground, z + elevatorSize);    // Bottom Right Of The Quad (Top)
			glTexCoord2f(3.0, 1.0); glVertex3f(x + size, ground, z);    // Top Right Of The Quad (Top)
			glTexCoord2f(0.0, 1.0); glVertex3f(x + elevatorSize, ground, z);   // Top Left Of The Quad (Top)
			glEnd();

			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z + size);   // Bottom Left Of The Quad (Top)
			glTexCoord2s(3.0, 0.0); glVertex3f(x + size, ground, z + size);    // Bottom Right Of The Quad (Top)
			glTexCoord2f(3.0, 3.0); glVertex3f(x + size, ground, z + elevatorSize);    // Top Right Of The Quad (Top)
			glTexCoord2f(0.0, 3.0); glVertex3f(x, ground, z + elevatorSize);   // Top Left Of The Quad (Top)
			glEnd();

			if (floor == 1) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(1, 1, 1, 0.5);
				/*--------- Front floor ---------*/
				choose_TextureToBind(1, type);
				glBegin(GL_QUADS); //right
				glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z + size);    // Bottom Left Of The Quad (front)
				glTexCoord2f(2.0, 0.0); glVertex3f(x + (size / 2.3), ground, z + size);    // Bottom Right Of The Quad (front)
				glTexCoord2f(2.0, 2.0); glVertex3f(x + (size / 2.3), height, z + size);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 2.0); glVertex3f(x, height, z + size);    // up Left Of The Quad (front)
				glEnd();

				glBegin(GL_QUADS); //left
				glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 1.8), ground, z + size);    // Bottom Left Of The Quad (front)
				glTexCoord2f(2.0, 0.0); glVertex3f(x + size, ground, z + size);    // Bottom Right Of The Quad (front)
				glTexCoord2f(2.0, 2.0); glVertex3f(x + size, height, z + size);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 2.0); glVertex3f(x + (size / 1.8), height, z + size);    // up Left Of The Quad (front)
				glEnd();

				glBegin(GL_QUADS); //up midlle
				glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 2.3), (ground + 15), z + size);    // Bottom Left Of The Quad (front)
				glTexCoord2f(1.0, 0.0); glVertex3f(x + (size / 1.8), (ground + 15), z + size);    // Bottom Right Of The Quad (front)
				glTexCoord2f(1.0, 1.0); glVertex3f(x + (size / 1.8), height, z + size);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 1.0); glVertex3f(x + (size / 2.3), height, z + size);    // up Left Of The Quad (front)
				glEnd();

				/*--------- Back floor ---------*/
				choose_TextureToBind(1, type);
				glBegin(GL_QUADS); //right
				glTexCoord2f(0.0, 0.0); glVertex3f(x + elevatorSize, ground, z);    // Bottom Left Of The Quad (front)
				glTexCoord2f(2.0, 0.0); glVertex3f(x + (size / 2.3), ground, z);    // Bottom Right Of The Quad (front)
				glTexCoord2f(2.0, 2.0); glVertex3f(x + (size / 2.3), height, z);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 2.0); glVertex3f(x + elevatorSize, height, z);    // up Left Of The Quad (front)
				glEnd();

				glBegin(GL_QUADS); //left
				glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 1.8), ground, z);    // Bottom Left Of The Quad (front)
				glTexCoord2f(2.0, 0.0); glVertex3f(x + size, ground, z);    // Bottom Right Of The Quad (front)
				glTexCoord2f(2.0, 2.0); glVertex3f(x + size, height, z);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 2.0); glVertex3f(x + (size / 1.8), height, z);    // up Left Of The Quad (front)
				glEnd();

				glBegin(GL_QUADS); //up midlle
				glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 2.3), (ground + 15), z);    // Bottom Left Of The Quad (front)
				glTexCoord2f(1.0, 0.0); glVertex3f(x + (size / 1.8), (ground + 15), z);    // Bottom Right Of The Quad (front)
				glTexCoord2f(1.0, 1.0); glVertex3f(x + (size / 1.8), height, z);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 1.0); glVertex3f(x + (size / 2.3), height, z);    // up Left Of The Quad (front)
				glEnd();
				glDisable(GL_BLEND);

			}
			else {
				/*--------- Front floor ---------*/
				choose_TextureToBind(1, type);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z + size);    // Bottom Left Of The Quad (front)
				glTexCoord2f(5.0, 0.0); glVertex3f(x + size, ground, z + size);    // Bottom Right Of The Quad (front)
				glTexCoord2f(5.0, 2.0); glVertex3f(x + size, height, z + size);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 2.0); glVertex3f(x, height, z + size);    // up Left Of The Quad (front)
				glEnd();

				/*--------- Back floor ---------*/
				choose_TextureToBind(1, type);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(x + elevatorSize, ground, z);    // Bottom Left Of The Quad (front)
				glTexCoord2f(5.0, 0.0); glVertex3f(x + size, ground, z);    // Bottom Right Of The Quad (front)
				glTexCoord2f(5.0, 2.0); glVertex3f(x + size, height, z);    // up Right Of The Quad (front)
				glTexCoord2f(0.0, 2.0); glVertex3f(x + elevatorSize, height, z);    // up Left Of The Quad (front)
				glEnd();

			}

			/*---------  Right floor ---------*/
			choose_TextureToBind(1, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x + size, ground, z);    //  Bottom Left Of The Quad (right)
			glTexCoord2f(5.0, 0.0);	glVertex3f(x + size, ground, z + size);    // Bottom right Of The Quad (right)
			glTexCoord2f(5.0, 2.0);	glVertex3f(x + size, height, z + size);    // Top right Of The Quad (right)
			glTexCoord2f(0.0, 2.0); glVertex3f(x + size, height, z);    // Top Left Of The Quad (right)
			glEnd();
			/*---------  Left floor ---------*/
			choose_TextureToBind(1, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z + elevatorSize);    //  Bottom Left Of The Quad (left)
			glTexCoord2f(5.0, 0.0); glVertex3f(x, ground, z + size);    // Bottom right Of The Quad (left)
			glTexCoord2f(5.0, 2.0); glVertex3f(x, height, z + size);    // Top right Of The Quad (left)
			glTexCoord2f(0.0, 2.0); glVertex3f(x, height, z + elevatorSize);    // Top Left Of The Quad (left)
			glEnd();
		}
		else {
			// room 
			height = height - 0.1;
			size = size - 0.05;
			/*---------  up room ---------*/
			choose_TextureToBind(0, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, height, z + size);   // Bottom Left Of The Quad (Top)
			glTexCoord2s(1.0, 0.0); glVertex3f(x + size, height, z + size);    // Bottom Right Of The Quad (Top)
			glTexCoord2f(1.0, 1.0); glVertex3f(x + size, height, z);    // Top Right Of The Quad (Top)
			glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z);   // Top Left Of The Quad (Top)
			glEnd();


			/*--------- Front room---------*/
			choose_TextureToBind(1, type);
			glBegin(GL_QUADS); //right
			glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z + size);    // Bottom Left Of The Quad (front)
			glTexCoord2f(2.0, 0.0); glVertex3f(x + (size / 2.4), ground, z + size);    // Bottom Right Of The Quad (front)
			glTexCoord2f(2.0, 2.0); glVertex3f(x + (size / 2.4), height, z + size);    // up Right Of The Quad (front)
			glTexCoord2f(0.0, 2.0); glVertex3f(x, height, z + size);    // up Left Of The Quad (front)
			glEnd();

			glBegin(GL_QUADS); //left
			glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 1.6), ground, z + size);    // Bottom Left Of The Quad (front)
			glTexCoord2f(2.0, 0.0); glVertex3f(x + size, ground, z + size);    // Bottom Right Of The Quad (front)
			glTexCoord2f(2.0, 2.0); glVertex3f(x + size, height, z + size);    // up Right Of The Quad (front)
			glTexCoord2f(0.0, 2.0); glVertex3f(x + (size / 1.6), height, z + size);    // up Left Of The Quad (front)
			glEnd();

			glBegin(GL_QUADS); //up midlle
			glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 2.4), (ground + 15), z + size);    // Bottom Left Of The Quad (front)
			glTexCoord2f(1.0, 0.0); glVertex3f(x + (size / 1.6), (ground + 15), z + size);    // Bottom Right Of The Quad (front)
			glTexCoord2f(1.0, 1.0); glVertex3f(x + (size / 1.6), height, z + size);    // up Right Of The Quad (front)
			glTexCoord2f(0.0, 1.0); glVertex3f(x + (size / 2.4), height, z + size);    // up Left Of The Quad (front)
			glEnd();


			/*--------- Back room ---------*/
			choose_TextureToBind(3, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z);    // Bottom Left Of The Quad (back)
			glTexCoord2f(1.0, 0.0); glVertex3f(x + size, ground, z);    // Bottom Right Of The Quad (back)
			glTexCoord2f(1.0, 1.0); glVertex3f(x + size, height, z);    // up Right Of The Quad (back)
			glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z);    // up Left Of The Quad (back)
			glEnd();

			choose_TextureToBind(4, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x + (size / 3), ground + 10, z + 0.5);    //  Bottom Left Of The Quad (right)
			glTexCoord2f(1.0, 0.0);	glVertex3f(x + 2 * (size / 3), ground + 10, z + 0.5);    // Bottom right Of The Quad (right)
			glTexCoord2f(1.0, 1.0);	glVertex3f(x + 2 * (size / 3), height - 10, z + 0.5);    // Top right Of The Quad (right)
			glTexCoord2f(0.0, 1.0); glVertex3f(x + (size / 3), height - 10, z + 0.5);    // Top Left Of The Quad (right)
			glEnd();

			/*---------  Right room ---------*/
			choose_TextureToBind(2, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x + size, ground, z);    //  Bottom Left Of The Quad (right)
			glTexCoord2f(1.0, 0.0);	glVertex3f(x + size, ground, z + size);    // Bottom right Of The Quad (right)
			glTexCoord2f(1.0, 1.0);	glVertex3f(x + size, height, z + size);    // Top right Of The Quad (right)
			glTexCoord2f(0.0, 1.0); glVertex3f(x + size, height, z);    // Top Left Of The Quad (right)
			glEnd();

			/*---------  Left room ---------*/
			choose_TextureToBind(2, type);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(x, ground, z);    //  Bottom Left Of The Quad (left)
			glTexCoord2f(1.0, 0.0); glVertex3f(x, ground, z + size);    // Bottom right Of The Quad (left)
			glTexCoord2f(1.0, 1.0); glVertex3f(x, height, z + size);    // Top right Of The Quad (left)
			glTexCoord2f(0.0, 1.0); glVertex3f(x, height, z);    // Top Left Of The Quad (left)
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}



	void Draw()
	{
		glPushMatrix();
		for (int floor = 1; floor <= floorNum; floor++) {
			if (roomNum > 0) {
				glPushMatrix();
				glRotated(-90, 0, 1, 0);
				RoomFloor(x + 70, z + 1, floor, 1);                     // first room ( bottom right )
				if (roomNum > 1)  RoomFloor(x + 17, z + 1, floor, 1);   // second room ( top right )
				glPopMatrix();
				if (roomNum > 2) {
					glPushMatrix();
					glRotated(90, 0, 1, 0);
					RoomFloor(x + 2, z + 1, floor, 1);                   // third room ( bottom left )
					if (roomNum > 3) RoomFloor(x + 55, z + 1, floor, 1); // fourth room ( top left )
					glPopMatrix();
				}
			}
			RoomFloor(x, z, floor, 0);
		}
		elevator(x, z, floorNum);
		glPopMatrix();
	}







};
