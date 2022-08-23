#include <windows.h>		
#include <gl\gl.h>			
#include <gl\glu.h>			
#include <glaux.h>	
#include <math.h>
#include <texture.h>
#include "camera.h"
#include "unit.cpp"
#include "Street.cpp"
#include "Cupe.cpp"
#include "Box.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <Model_3DS.h>
#include <3DTexture.h>
#include "baseBuilding.cpp"
#include <set>
#include <queue>
#include "sound.h"



using namespace std;

#define PI 3.141592653589


vector<unit> allUnits;
Model_3DS tree;
Model_3DS plane;
Model_3DS lamp;
Model_3DS car1;
Model_3DS car2;
Model_3DS car3;

vector<Cupe> Cupes;
vector<Street> ourStreets;
vector <Box> ourBox;
vector<pair<float, float>> ourTrees, ourLight;
set<pair<float, float>> baseCircles;


HDC			hDC = NULL;	
HGLRC		hRC = NULL;
HWND		hWnd = NULL;
HINSTANCE	hInstance;

bool	keys[256];			
bool	active = TRUE;		
bool	fullscreen = TRUE;	

GLfloat LightPos[] = { 0.0f , 190.0f , 0.0f , 150.0f };
GLfloat LightAmp[] = { 1.0f , 1.0f , 1.0f , 1.0f };
GLfloat LightDiff[] = { 1.0f , 1.0f , 1.0f , 1.0f };
GLfloat LightSpec[] = { 1.0f , 1.0f , 1.0f , 1.0f };

GLfloat MatAmb[] = { 0.5f , 0.5f , 0.5f , 1.0f };
GLfloat MatDiff[] = { 0.6f , 0.6f , 0.6f , 1.0f };
GLfloat MatSpec[] = { 0.2f , 0.2f , 0.2f , 1.0f };
GLfloat Matshn[] = {128.0f};


struct mousePair
	{
		GLfloat X, Y;
	} MousePt;

bool isClicked = false;
bool isRClicked = false;
bool isDragging = false;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height == 0)										
	{
		height = 1;										
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000000000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


//******declaretion of tecturesId******//

	int Street::verticalStreetTexture;
	int Street::horizontalStreetTexture;

	int Cupe::aroundBuildingTextureId;
	int Cupe::BuildingTextureId[6];
	int Cupe::skyBoxTexture1Id[6];
	int Cupe::skyBoxTexture2Id[6];
	int Cupe::BuildNight[6];

	int Box::boxTexture;

	GLTexture planeTexture1;
	GLTexture planeTexture2;

	int baseBuilding::houseTexture[3];
	int baseBuilding::roomTexture[5];

	int CircleTextureId;


//****************************************//

	const float r = 150, d = 2 * r, widthStreet = 60;
	int buildings = 50;
	int floorNumber = 10;
	int numberOfRooms = 4;
	float Xmax = 1000;
	Cupe skyBox;  // sky Box
	baseBuilding ourBuilding;

	/***************************************/

	int grassTexture;

	void LoadTexturId()
	{
		Cupe::skyBoxTexture2Id[0] = LoadTexture((char*)"images//world//up.bmp");
		Cupe::skyBoxTexture2Id[1] = LoadTexture((char*)"images//nature//down.bmp");
		Cupe::skyBoxTexture2Id[2] = LoadTexture((char*)"images//world//default.bmp");
		Cupe::skyBoxTexture2Id[3] = LoadTexture((char*)"images//world//default.bmp");
		Cupe::skyBoxTexture2Id[4] = LoadTexture((char*)"images//world//default.bmp");
		Cupe::skyBoxTexture2Id[5] = LoadTexture((char*)"images//world//default.bmp");

		Cupe::skyBoxTexture1Id[0] = LoadTexture((char*)"images//nature//up.bmp");
		Cupe::skyBoxTexture1Id[1] = LoadTexture((char*)"images//nature//down.bmp");
		Cupe::skyBoxTexture1Id[2] = LoadTexture((char*)"images//nature//north.bmp");
		Cupe::skyBoxTexture1Id[3] = LoadTexture((char*)"images//nature//south.bmp");
		Cupe::skyBoxTexture1Id[4] = LoadTexture((char*)"images//nature//right.bmp");
		Cupe::skyBoxTexture1Id[5] = LoadTexture((char*)"images//nature//left.bmp");

		//*****************************************************//
		baseBuilding::houseTexture[0] = LoadTexture((char*)"images//baseBuilding//upIN.bmp");
		baseBuilding::houseTexture[1] = LoadTexture((char*)"images//baseBuilding//roundIN.bmp");
		baseBuilding::houseTexture[2] = LoadTexture((char*)"images//baseBuilding//downIN.bmp");

		baseBuilding::roomTexture[0] = LoadTexture((char*)"images//baseBuilding//roomUP.bmp");
		baseBuilding::roomTexture[1] = baseBuilding::roomTexture[2] = baseBuilding::roomTexture[3] = LoadTexture((char*)"images//baseBuilding//roomBack.bmp");
		baseBuilding::roomTexture[4] = LoadTexture((char*)"images//baseBuilding//image.bmp");

		//*****************************************************//


		Cupe::aroundBuildingTextureId = LoadTexture((char*)"images//BuildRound.bmp");
		Cupe::BuildingTextureId[0] = Cupe::BuildingTextureId[1] = LoadTexture((char*)"images//downBuild.bmp");
		Cupe::BuildingTextureId[2] = Cupe::BuildingTextureId[3] = Cupe::BuildingTextureId[4] = Cupe::BuildingTextureId[5] = LoadTexture((char*)"images//build.bmp");

		Cupe::BuildNight[0] = Cupe::BuildNight[1] = LoadTexture((char*)"images//downBuild.bmp");
		Cupe::BuildNight[2] = Cupe::BuildNight[3] = Cupe::BuildNight[4] = Cupe::BuildNight[5] = LoadTexture((char*)"images//build2.bmp");

		

		Street::verticalStreetTexture = LoadTexture((char*)"images//vroad.bmp");
		Street::horizontalStreetTexture = LoadTexture((char*)"images//wroad.bmp");

		Box::boxTexture = LoadTexture((char*)"images//box.bmp");

		CircleTextureId = LoadTexture((char*)"images//myphoto.bmp");

		grassTexture = LoadTexture((char*)"images//grass.bmp");




	}

	/*
	int trying;
	bool isNumeric(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(str[i]))
				return false;
		}
		return true;
	}

	int str_to_int(const string& str) {
		stringstream ss(str);
		int num;
		ss >> num;
		return num;
	}
 
	void getinput()
	{
		fstream file;
		string line;
		file.open("input.txt", ios::in);
			getline(file, line);
			getline(file, line);
			buildings = str_to_int(line);
			getline(file, line);
			getline(file, line);
			floorNumber = str_to_int(line);
			getline(file, line);
			getline(file, line);
			numberOfRooms = str_to_int(line);
		file.close();
	}
	*/

	void generateEnv()
	{
		queue<pair<float, float>> Q;
		baseCircles.insert(make_pair(0, 0));
		buildings -= 4;
		Q.push(make_pair(0, 0));
		if (buildings <= 0)
			return;


		//make Circles
		while (!Q.empty() && buildings > 0)
		{
			float x = Q.front().first, y = Q.front().second;
			Q.pop();

			/// Right
			if (baseCircles.find(make_pair(x + (2 * r) + d, y)) == baseCircles.end() && buildings > 0)
			{
				baseCircles.insert(make_pair(x + (2 * r) + d, y));
				Q.push(make_pair(x + (2 * r) + d, y));
				buildings -= 4;
			}

			/// Left
			if (baseCircles.find(make_pair(x - 2 * r - d, y)) == baseCircles.end() && buildings > 0)
			{
				baseCircles.insert(make_pair(x - 2 * r - d, y));
				Q.push(make_pair(x - 2 * r - d, y));
				buildings -= 4;
			}

			/// Up
			if (baseCircles.find(make_pair(x, y + 2 * r + d)) == baseCircles.end() && buildings > 0)
			{
				baseCircles.insert(make_pair(x, y + 2 * r + d));
				Q.push(make_pair(x, y + 2 * r + d));
				buildings -= 4;
			}

			/// Down
			if (baseCircles.find(make_pair(x, y - 2 * r - d)) == baseCircles.end() && buildings > 0)
			{
				baseCircles.insert(make_pair(x, y - 2 * r - d));
				Q.push(make_pair(x, y - 2 * r - d));
				buildings -= 4;
			}
		}

		
		Xmax = max(Xmax, abs(baseCircles.begin()->first));
		for (auto i : baseCircles)
		{
				Xmax = max(Xmax, max(abs(i.first), abs(i.second)));
		}
	
		set<pair<float, float>> Temp(baseCircles);
		set<pair<float, float>> visited;

		for (auto cur : Temp)
		{
			float x = cur.first, y = cur.second;
			/// Right

			if (Temp.find(make_pair(x + 2 * r + d, y)) != Temp.end() && visited.find(make_pair(x + 2 * r + d, y)) == visited.end())
			{
				Street temp(x, y, x + 2 * r + d, y);
				ourStreets.push_back(temp);
			}
			/// Left
			if (Temp.find(make_pair(x - 2 * r - d, y)) != Temp.end() && visited.find(make_pair(x - 2 * r - d, y)) == visited.end())
			{
				Street temp(x, y, x - 2 * r - d, y);
				ourStreets.push_back(temp);
			}
			/// Up
			if (Temp.find(make_pair(x, y + 2 * r + d)) != Temp.end() && visited.find(make_pair(x, y + 2 * r + d)) == visited.end())
			{
				Street temp(x, y, x, y + 2 * r + d);
				ourStreets.push_back(temp);
			}
			/// Down
			if (Temp.find(make_pair(x, y - 2 * r - d)) != Temp.end() && visited.find(make_pair(x, y - 2 * r - d)) == visited.end())
			{
				Street temp(x, y, x, y - 2 * r - d);
				ourStreets.push_back(temp);
			}
			visited.insert(make_pair(cur.first, cur.second));
		}


		//buildings
		for (auto t : baseCircles)
		{
			float xx = t.first, yy = t.second;
			int dis = 270;
			float xs[4], ys[4];

			xs[0] = dis * cos(PI / 4) + xx - 50;
			ys[0] = dis * sin(PI / 4) + yy - 50;

			xs[1] = dis * cos(3 * PI / 4) + xx - 50;
			ys[1] = dis * sin(3 * PI / 4) + yy - 50;

			xs[2] = dis * cos(5 * PI / 4) + xx - 50;
			ys[2] = dis * sin(5 * PI / 4) + yy - 50;

			xs[3] = dis * cos(7 * PI / 4) + xx - 50;
			ys[3] = dis * sin(7 * PI / 4) + yy - 50;

			for (int i = 0; i < 4; i++)
			{
				Cupe Temp(xs[i], ys[i], 100, 150, 1);
				Cupes.push_back(Temp);
			}
		}

		// trees // lighting // boxes

		for(auto t : ourStreets)
		{
			float x1 = t.getx1(), y1 = t.getz1(), x2 = t.getx2(), y2 = t.getz2();
			int counter = 0;
			int signal;

			if(x1 == x2)
			{
				
				pair<float,float> tempTree , tempLight , tempBox;

				float q = (y1+y2)/2;
				counter = 1;
				signal = 1;

				// lights right of the street
				tempLight.first = x1 + (widthStreet / 2) + 5;
				tempLight.second = q;
				ourLight.push_back(tempLight);


				while(counter <= 3)
				{
					//trees right of the street
					tempTree.first = x1 - (widthStreet / 2) - 30;
					tempTree.second = q ;
					ourTrees.push_back(tempTree);

					// box left of the street
					Box temp1(x1 + (widthStreet / 2) + 30 , 10 , q , 10 , 10);
					Box temp2(x1 + (widthStreet / 2) + 30 , 0 , q-7 , 10 , 10);
					Box temp3(x1 + (widthStreet / 2) + 30 , 0 , q+7 , 10 , 10);
					ourBox.push_back(temp1);
					ourBox.push_back(temp2);
					ourBox.push_back(temp3);

					// step
					q+= (d/3)*signal*counter;
					counter++;
					signal = -signal;

				}
			}
			else
			{
				// tree & light & ( box ?? )
				pair<float,float> tempTree , tempLight , tempBox ;
				float q = (x1+x2)/2;
				counter = 1;
				signal = 1;

				// light up of the street
				tempLight.first = q;
				tempLight.second = y1 - (widthStreet / 2) -5;
				ourLight.push_back(tempLight);

				while(counter <= 3){
					// tree up of the street
					tempTree.first = q;
					tempTree.second = y1 + (widthStreet / 2) + 30 ;
					ourTrees.push_back(tempTree);

					

					// box down of the street
					tempBox.first = q;
					tempBox.second = y1 - (widthStreet / 2) - 30 ;

					Box temp1( q , 10 , y1 - (widthStreet / 2) - 30 , 10 , 10);
					Box temp2(q-7 , 0 , y1 - (widthStreet / 2) - 30 , 10 , 10);
					Box temp3(q+7 , 0 , y1 - (widthStreet / 2) - 30 , 10 , 10);
					ourBox.push_back(temp1);
					ourBox.push_back(temp2);
					ourBox.push_back(temp3);

					

					// step
					q+= (d/3)*signal*counter;
					counter++;
					signal = -signal;
				}
			}
		}

		Xmax+= 4*d;
		Cupe temp(-Xmax , -Xmax , 2*Xmax , floorNumber*30+1000, 0);  // sky Box
		skyBox = temp;
		LightPos[1] = floorNumber * 30 + 300;
		plane.pos.y = floorNumber * 30 + 100;

	}

	INIT initializer = INIT();
	Sound sound1, sound2, sound3;
	bool EnableSound = false;
	bool soundIsRunning = false;
	bool soundRuning = true;

int InitGL(GLvoid)
{
	initializer.InitOpenAL();
	sound1 = Sound((char*)"wave//Mr-robot.wav");
	sound2 = Sound((char*)"wave//GOT.wav");
	sound3 = Sound((char*)"wave//Footsteps.wav");
	
	//getinput();
	generateEnv();
	LoadTexturId();

	baseBuilding temp(-60, -60, floorNumber, numberOfRooms);
	ourBuilding = temp;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	plane.Load((char*)"images//plane//E 45 Aircraft_3ds.3ds");
	planeTexture1.LoadBMP((char*)"images//plane//dayTexture.bmp");
	planeTexture2.LoadBMP((char*)"images//plane//nightTexture.bmp");
	plane.Materials[0].tex.Load((char*)"images//plane//E-45_REF 1.bmp");
	plane.Materials[1].tex = planeTexture1;
	plane.pos.x = 400;
	plane.pos.y = 400;
	plane.pos.z = 0;
	plane.scale=15;

	ourBuilding.allocate(allUnits);
	skyBox.allocate(allUnits);

	for (auto i: ourBox)
	{
		i.allocate(allUnits);
	}

	for (auto i: Cupes)
	{
		i.allocate(allUnits);
	}



	tree.Load((char*)"images/tree/M_TREE5.3DS");
	GLTexture treeTexture1;
	GLTexture treeTexture2;
	treeTexture1.LoadBMP((char*)"images/tree/WC_Tree_Bark_Diffuse.bmp");
	treeTexture2.LoadBMP((char*)"images/tree/WC_Leafs.bmp");
	tree.Materials[0].tex = treeTexture1;
	tree.Materials[1].tex = treeTexture2;
	tree.scale = 1;
	tree.pos.x = 0;
	tree.pos.z = 0;

	lamp.Load((char*)"images/lamp/Lamppost.3DS");
	GLTexture lamptexture1;
	lamptexture1.LoadBMP((char*)"images/lamp/metaly1.bmp");
	GLTexture lamptexture2;
	lamptexture2.LoadBMP((char*)"images/lamp/metaly2.bmp");
	lamp.Materials[0].tex=lamptexture1;
	lamp.scale = 0.03;

	car1.Load((char*)"images/car/Mercedes AMG GT3 .3ds");
	car2.Load((char*)"images/car/Mercedes AMG GT3 .3ds");
	car3.Load((char*)"images/car/Mercedes AMG GT3 .3ds");

	GLTexture carTexture1;
	GLTexture carTexture2;
	GLTexture carTexture3;

	carTexture1.LoadBMP((char*)"images/car/diffuse.bmp");
	carTexture2.LoadBMP((char*)"images/car/01 - Default_Height.bmp");
	carTexture3.LoadBMP((char*)"images/car/21 - Default_Base_Color.bmp");

	car1.Materials[0].tex = car2.Materials[0].tex = car3.Materials[0].tex = carTexture1;
	car1.Materials[2].tex = car2.Materials[2].tex = car3.Materials[2].tex = carTexture2;
	car1.Materials[5].tex = car2.Materials[5].tex = car3.Materials[5].tex = carTexture3;

	car1.pos.x = 170;
	car1.pos.z = 0;
	car1.scale = 7;
	car1.rot.y = 90 ;

	car2.pos.x = 50;
	car2.pos.z = r - 30;
	car2.scale = 7;
	car2.rot.y = 35;

	car3.pos.x = -50;
	car3.pos.z = r - 30;
	car3.scale = 7;
    car3.rot.y = -35 ;

	return TRUE;										// Initialization Went OK
}

Camera MyCamera;
GLfloat lastX = 0;
GLfloat lastY = 0;
GLboolean spaceFlage1 = false;
GLboolean spaceFlage2 = false;
GLint spaceCounter = 0;

void Key(bool* keys, float speed)
{

	if (keys['Z'])
	{
		if(soundRuning){
			if (EnableSound)
			{
				sound1.Stop();
				EnableSound = false;
			}
			else
			{
				sound1.Play();
				EnableSound = true;
			}
		}
		else{
			if (EnableSound)
			{
				sound2.Stop();
				EnableSound = false;
			}
			else
			{
				sound2.Play();
				EnableSound = true;
			}
		}
	}


	if (!isDragging)
	{
		if (isRClicked || isClicked)
		{
			isDragging = true;
			lastX = MousePt.X;
			lastY = MousePt.Y;
		}
	}
	else
	{
		if (isRClicked || isClicked)
		{
			if (lastY > MousePt.Y)
			{
				MyCamera.RotateX(2 * speed);
			}
			if (lastY < MousePt.Y)
			{
				MyCamera.RotateX(-2 * speed);
			}
			if (lastX > MousePt.X)
			{
				MyCamera.RotateY(2 * speed);
			}
			if (lastX < MousePt.X)
			{
				MyCamera.RotateY(-2 * speed);
			}
		}
		else
		{
			isDragging = false;
		}
		lastX = MousePt.X;
		lastY = MousePt.Y;
	}


	if (keys[VK_UP])
		MyCamera.RotateX(2 * speed);
	if (keys[VK_DOWN])
		MyCamera.RotateX(-2 * speed);
	if (keys[VK_RIGHT])
		MyCamera.RotateY(-2 * speed);
	if (keys[VK_LEFT])
		MyCamera.RotateY(2 * speed);

	if (keys['W']) 
	{
		MyCamera.MoveForward(1 * speed , allUnits);
		if (!soundIsRunning)
		{
			sound3.Play();
			soundIsRunning = true;
		}
	}
	if (keys['S'])
	{
		MyCamera.MoveForward(-1 * speed , allUnits);
		if (!soundIsRunning)
		{
			sound3.Play();
			soundIsRunning = true;
		}
	}
	if ( keys['F'] )
	{
		MyCamera.MoveUpward(1 * speed, allUnits , make_pair(-60 , -60));
	}
	if (keys['G'])
	{
		MyCamera.MoveUpward(-1 * speed, allUnits , make_pair(-60, -60));
	}

		 
	if (keys['D'])
	{
		MyCamera.MoveRight(1 * speed, allUnits);
		if (!soundIsRunning)
		{
			sound3.Play();
			soundIsRunning = true;
		}
	}
	if (keys['A'])
	{
		MyCamera.MoveRight(-1 * speed, allUnits);
		if (!soundIsRunning)
		{
			sound3.Play();
			soundIsRunning = true;
		}
	}
	if (!keys['W'] && !keys['S'] && !keys['D'] && !keys['A'])
	{
		sound3.Stop();
		soundIsRunning = false;

	}
	if (keys['Y'] )
	{
		skyBox.switchDayToNight();
		plane.Materials[1].tex = planeTexture2;	
		sound1.Stop(); sound2.Stop();
		soundRuning = false;
		for (auto i: Cupes)
		{
			i.switchDayToNight();
		}

		glLightfv(GL_LIGHT2, GL_POSITION, LightPos);
		glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmp);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiff);
		glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpec);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHTING);
		
	}
	if (keys['U'] )
	{
		skyBox.switchNightToDay();
		plane.Materials[1].tex = planeTexture1;
		sound1.Stop(); sound2.Stop();
		soundRuning=true;
		for (auto i : Cupes)
		{
			i.switchNightToDay();
		}

		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHTING);

	}	

	if (keys[VK_SHIFT])
	{
		MyCamera.MoveForwardWitout(1 * speed);
	}
}

void circle()
{
	float angle, radian, x, y;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, CircleTextureId);

	glBegin(GL_POLYGON);
	for (angle = 0.0; angle < 360.0; angle += 2.0)
	{

		radian = angle * (PI / 180.0f);
		//glColor3f(0.501f, 0.501f , 0.501f );

		x = (float)cos(radian);
		y = (float)sin(radian);

		glTexCoord2f( x * 0.5 + 0.5, y * 0.5 + 0.5);
		glVertex3f(x*r, 0, y*r);
	
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f , 1.0f );
}

void quad(float x, float z) {
	int size = 30;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(x, 0, z + size);    // Bottom Left Of The Quad (Bottom)
	glTexCoord2f(1.0, 0.0); glVertex3f(x + size, 0, z + size);   // Bottom Right Of The Quad (Bottom)
	glTexCoord2f(1.0, 1.0); glVertex3f(x + size, 0, z);   // Top Right Of The Quad (Bottom)
	glTexCoord2f(0.0, 1.0); glVertex3f(x, 0, z);    // Top Left Of The Quad (Bottom)
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawEnvironment()
{
	glPushMatrix();

	glTranslated(0,-1.0,0);
	skyBox.Draw();
	glPopMatrix();
	// circles
	for (auto i : baseCircles) {
		glPushMatrix();
		glTranslatef(i.first, 0 , i.second);
		circle();
		glPopMatrix();
	}
	// trees
	for (auto i : ourTrees) {
		glPushMatrix();
		quad(i.first - 15, i.second - 15);
		tree.pos.x = i.first;
		tree.pos.z = i.second;
		tree.Draw();
		glPopMatrix();
	}
	// light
	for(auto j : ourLight){
	glPushMatrix();
	lamp.pos.x = j.first;
	lamp.pos.z = j.second;
	lamp.Draw();
	glPopMatrix();
	}
	// box
	for(auto j : ourBox){
	glPushMatrix();
	j.Draw();
	glPopMatrix();
	}
	// buildings
	for (auto i : Cupes)
	{
		i.Draw();
	}
	//streets
	for (auto i : ourStreets)
	{
	   glPushMatrix();
	   glTranslated(0,-0.5,0);
		i.Draw();
	  glPopMatrix();
	}
	// base building
	ourBuilding.Draw();
}

float Q=0;
float carWalk1 = 170;
bool car1flag = false;
void DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Key(keys, 2);
	MyCamera.Render();

	glPushMatrix();
	glRotated(Q , 0 , 1 , 0);
	Q += 0.5;
	plane.Draw();
	glPopMatrix();

	car2.Draw();
	car3.Draw();
	
	glPushMatrix();
	car1.pos.x = carWalk1;
	car1.Draw();
	if (carWalk1 < 2*d && !car1flag)
	{
		carWalk1+=5;
	}
	else
	{
		carWalk1 -= 5;

	}
	if (carWalk1 >= 2 * d)
	{
		car1flag = true;
		car1.rot.y = -90;
	}
	if (carWalk1 <= 170)
	{
		car1flag = false;
		car1.rot.y = 90;
	}
	glPopMatrix();

	DrawEnvironment();

	glFlush();	
	SwapBuffers(hDC);  
}


GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			
	WNDCLASS	wc;						
	DWORD		dwExStyle;				
	DWORD		dwStyle;				
	RECT		WindowRect;				
	WindowRect.left = (long)0;			
	WindowRect.right = (long)width;		
	WindowRect.top = (long)0;				
	WindowRect.bottom = (long)height;		

	fullscreen = fullscreenflag;			

	hInstance = GetModuleHandle(NULL);				
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc = (WNDPROC)WndProc;					
	wc.cbClsExtra = 0;									
	wc.cbWndExtra = 0;									
	wc.hInstance = hInstance;							
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground = NULL;									
	wc.lpszMenuName = NULL;									
	wc.lpszClassName = "OpenGL";								

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}
void CheckMouse(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		MousePt.X = (GLfloat)LOWORD(lParam);
		MousePt.Y = (GLfloat)HIWORD(lParam);
		isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
		isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
		break;
	case WM_LBUTTONUP:
		isClicked = false;
		break;
	case WM_RBUTTONUP:
		isRClicked = false;
		break;
	case WM_LBUTTONDOWN:
		isClicked = true;
		break;
	case WM_RBUTTONDOWN:
		isRClicked = true;
		break;
	}
}
LRESULT CALLBACK WndProc(HWND	hWnd,UINT	uMsg,WPARAM	wParam,LPARAM	lParam)			
{
	CheckMouse(uMsg, wParam, lParam);

	static PAINTSTRUCT ps;

	switch (uMsg)									
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = false;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow((char* )"Madhat NeHe Template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 20, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	cout << "Enter the number of buildings  ( 6 -> 50):\t";
	while(true){
	cin >> buildings;
	if (buildings > 5 && buildings <= 50) break;
	cout<<"wronge input"<<endl;
	}
	cout << "Enter the number of floors in the base building ( 1 -> 10):\t";
	while(true){
	cin >> floorNumber;
	if (floorNumber > 0 && floorNumber <= 10) break;
	cout<<"wronge input"<<endl;
	}
	cout << "Enter the number of rooms in each floor in the base building ( 0 -> 4): \t";
	while(true){
	cin >> numberOfRooms;
	if (numberOfRooms >= 0 && numberOfRooms <= 4) break;
	cout<<"wronge input"<<endl;
	}
	return WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}