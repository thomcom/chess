
#include "texture.h"
#include "Mystack.h"
#include "defs.h"
#include "etSimpleObjParser.h"
#include "Vertices.h"
#include "Shapemove.h"
#include "Movement.h"
#include "etMouse.h"

void display();
void keyboardInterrupt(unsigned char, int, int);
void mouseInterrupt(int, int, int, int);
void motion(int, int);
void initWindow();
void initLightNames();
void initLight();
void initOrtho();
void initPieces();
void initTextures();
void addBoard();
void seedBoard();
void drawAll(GLenum);
void drawOne(shape_ptr p, GLenum mode);
int pickFunction(int, int, int, int);
int processHits(GLint, GLuint*);
void liftPiece(int passVal);
void movePiece(int passVal);
void dropPiece(int passVal);
int getJ(int position);

Movement mover;
Mystack objects;
int pickedObject = 0;
int positionFilled[64];
int objID = 0;
bool seeded = 0;
int seedStart = 0;
GLuint texture;
bool inMotion   = false;
int* moveVector;
int texArray[64];
int lightnames[8];

etSimpleObjParser pb("piecebase.obj");
etSimpleObjParser pawn("pawn.obj");
etSimpleObjParser rook("rook.obj");
etSimpleObjParser knight("knight.obj");
etSimpleObjParser bishop("bishop.obj");
etSimpleObjParser queen("queen.obj");
etSimpleObjParser king("king.obj");

int CAMERA_MODE = 0;
int OBJECT_MODE = 0;
int PIECE_MODE = 0;
string LIGHT_MODE = ZERO;
int COLOR_MODE = 0;

bool lighton[8] = {
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false
};

GLfloat lightp[8][4] = {
	{ 0, 1, 0, 0},
	{ 0,-1, 0, 0},
	{ 0, 0, 1, 0},
	{1, 3,-3, 16},
	{ 3, 5, -1, 12},
	{-1, 1, -2, 28},
	{ 1, 0, 1, 0},
	{-1, 0, 1, 0}
};
	
GLfloat lightc[][3][3] = {
	{{.61,.6,.6},{.7,.7,.7},{.1,.1,.1}},
	{{.5,.5,.5},{.3,.3,.5},{.1,.1,.1}},
	{{.5,.5,.5},{.3,.5,.3},{.1,.1,.1}},
	{{.5,.5,.5},{.3,.5,.5},{.1,.1,.1}},
	{{.5,.5,.5},{.5,.3,.3},{.1,.1,.1}},
	{{.5,.5,.5},{.5,.3,.5},{.1,.1,.1}},
	{{.5,.5,.5},{.5,.5,.3},{.1,.1,.1}},
	{{.5,.5,.5},{.5,.5,.5},{.1,.1,.1}},
};

etMouse mouse;

enum Mode
{
    CAMERA;
    OBJECT;
    PIECE;
    COLOR;
    LIGHT;
}

namespace engine
{
    Mode mode = CAMERA;
};

namespace scene
{
    etVector spin( 17.8f, 27.4f, 0.0f );
};

namespace camera
{
    /*******************
    * Constants
    *******************/
    float viewAngle = 46.0;
    float nearClip = 1.0;
    float farClip = 35.0;
    float aspect = 1024.0f/768.0f;
    float advanceIncrement = 0.707f;
    /*******************
    * Coordinates
    *******************/
    etVector camPosition( 0.0f, 0.0f, 15.0f );
    etVector lookAt( 0.63f, -2.2f, 0.0f );
    etVector vup( 0.0f, 1.0f, 0.0f );
    /*******************
    * Methods
    *******************/
    // returns the normalized view plane normal
    etVector vpn() { return (lookAt - camPosition).Normal(); }
};

using camera::camPosition;
using camera::lookAt;
using camera::vup;
	
int main(int argc, char** argv)
{
	srand((unsigned) time(0));
	for(int i=0;i<64;i++) texArray[i] = rand() %3;
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
	
	initWindow();
	initLightNames();
	addBoard();
	initPieces();
	initTextures();

	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.1,0.1,0.1,1);
	glutMainLoop();
}

void initWindow()
{
	glutInitWindowSize(1000,950);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Chess");
	
	glutKeyboardFunc(keyboardInterrupt);
	glutMouseFunc(mouseInterrupt);
	glutMotionFunc(motion);
	glutDisplayFunc(display);
}

void addBoard()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			shape_ptr p = new shape;
			p->type = BOARDPIECE;
			if((i+j)%2==0)
			{
				p->ambimat[0] = 0.35;
				p->ambimat[1] = 0.35;
				p->ambimat[2] = 0.35;
				p->specmat[0] = 0.9;
				p->specmat[1] = 0.9;
				p->specmat[2] = 0.9;
				p->diffmat[0] = .7;
				p->diffmat[1] = .7;
				p->diffmat[2] = .7;
				p->shininess = 4;
				p->texID = 1;
			}
			else
			{
				p->ambimat[0] = 0.1;
				p->ambimat[1] = 0.1;
				p->ambimat[2] = 0.1;
				p->specmat[0] = 0.8;
				p->specmat[1] = 0.8;
				p->specmat[2] = 0.8;
				p->diffmat[0] = .7;
				p->diffmat[1] = .7;
				p->diffmat[2] = .7;
				p->shininess = 4;
				p->texID = 2;
			}
			p->position[0] = i-3.5;
			p->position[1] = 0.0;
			p->position[2] = j-3.5;
			p->rotation[0] = 0;
			p->rotation[1] = 0;
			p->rotation[2] = 0;
			p->scale[0] = 1;
			p->scale[1] = 0.2;
			p->scale[2] = 1;
			p->ID = objID;
			objID++;
			objects.push(p);
		}
	}
	shape_ptr p = new shape;
	p->type = BOARDBASE;
	p->ambimat[0] = .1;
	p->ambimat[1] = .15;
	p->ambimat[2] = .4;
	p->specmat[0] = .3;
	p->specmat[1] = .3;
	p->specmat[2] = .3;
	p->diffmat[0] = .2;
	p->diffmat[1] = .3;
	p->diffmat[2] = .8;
	p->shininess = 4;
	p->position[0] = 4.5;
	p->position[1] = 0;
	p->position[2] = 0;
	p->rotation[0] = 0;
	p->rotation[1] = 0;
	p->rotation[2] = 0;
	p->scale[0] = 1;
	p->scale[1] = 1;
	p->scale[2] = 1;

	p->ID = objID;
	objID++;
	objects.push(p);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	initLight();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(camera::viewAngle, camera::aspect, camera::nearClip, camera::farClip);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPosition.x,camPosition.y,camPosition.z,lookAt.x,lookAt.y,lookAt.z,vup.x,vup.y,vup.z);
    glTranslatef( mouse.MouseUpdate.Translation.x , mouse.MouseUpdate.Translation.y , mouse.MouseUpdate.Translation.z );	
    scene::spin = scene::spin + mouse.MouseUpdate.Rotation;
    mouse.ClearUpdate();
    scene::spin.etVectorSummary("Spin: ");    
	glRotatef(scene::spin.x,0,1,0);
	glRotatef(scene::spin.y,1,0,0);
	drawAll(GL_RENDER);
	initOrtho();
	glutSwapBuffers();
}

/*! initOrtho() draws all of the informative text on the bottom of the screen!
 */
void initOrtho()
{
	string s = "";
	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glOrtho(-1,1,-1,1,-1,1);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		// draw objects before text
		glColor3f(1,1,1);
			glRasterPos3f(-.95,-.83,0);
			s = "Camera Mode: ";
			for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			if( CAMERA_MODE==NONE )
			{
				s = "Shift for red pieces, no shift for green pieces. Zoom with <,>";
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			}
			else if( CAMERA_MODE==ROTATE_MODE )
			{
				s = "Rotate";
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			}
			else if( CAMERA_MODE==TRANSLATE_MODE )
			{
				s = "Translate";
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			}
		glRasterPos3f(-.95,-.90,0);
			s = "Cursor Mode: ";
			for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			if( OBJECT_MODE==NONE )
			{
				s = "Translate (Switch to piece mode with z-n).";
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			}
			else if( OBJECT_MODE==GREENPIECE )
			{
				if( PIECE_MODE==PAWN )
				{
					s = "Green Pawn (z)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==ROOK )
				{
					s = "Green Rook (x)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==KNIGHT )
				{
					s = "Green Knight (c)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==BISHOP )
				{
					s = "Green Bishop (v)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==QUEEN )
				{
					s = "Green Queen (b)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==KING )
				{
					s = "Green King (n)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
			}
			else if( OBJECT_MODE==REDPIECE )
			{
				if( PIECE_MODE==PAWN )
				{
					s = "Red Pawn (Z)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==ROOK )
				{
					s = "Red Rook (X)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==KNIGHT )
				{
					s = "Red Knight (X)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==BISHOP )
				{
					s = "Red Bishop (V)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==QUEEN )
				{
					s = "Red Queen (B)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
				if( PIECE_MODE==KING )
				{
					s = "Red King (N)";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				}
			}
			glRasterPos3f(-.95,-.97,0);
				s = "Light Mode: ";
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				s = LIGHT_MODE;
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
				if( COLOR_MODE==SPECULAR ) s = " SPEC";
				else if( COLOR_MODE==DIFFUSE ) s = " DIFF";
				else if( COLOR_MODE==AMBIENT ) s = " AMBIENT";
				else s = " (-ASD- Select Mode)";
				s = s + " (select a and toggle a light with 0-7, u,i,o to change color/intensity).";
				for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			if(inMotion)
			{
				glRasterPos3f(0,-.7,0);
					s = "Piece Moving - Please Wait";
					for(unsigned int i=0;i<s.length();i++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
			}
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void initLightNames()
{
	lightnames[0] = GL_LIGHT0;
	lightnames[1] = GL_LIGHT1;
	lightnames[2] = GL_LIGHT2;
	lightnames[3] = GL_LIGHT3;
	lightnames[4] = GL_LIGHT4;
	lightnames[5] = GL_LIGHT5;
	lightnames[6] = GL_LIGHT6;
	lightnames[7] = GL_LIGHT7;
}

void initLight()
{	
	for(int i=0;i<8;i++)
	{
		if( lighton[i]==true )
		{
			glEnable(lightnames[i]);
			glLightfv(lightnames[i], GL_POSITION, lightp[i]);
			glLightfv(lightnames[i], GL_SPECULAR, lightc[i][0]);
			glLightfv(lightnames[i], GL_DIFFUSE, lightc[i][1]);
			glLightfv(lightnames[i], GL_AMBIENT, lightc[i][2]);
		}
		else glDisable(lightnames[i]);
	}
}

void initPieces()
{
	pb.BuildMesh();
	pawn.BuildMesh();
	rook.BuildMesh();
	knight.BuildMesh();
	bishop.BuildMesh();
	queen.BuildMesh();
	king.BuildMesh();
}

void initTextures()
{
	LoadBitmap("./marbwhite.bmp");
	LoadBitmap("./marbblack.bmp");
}

void drawAll(GLenum mode)
{
	shape_ptr p = objects.getTop();
	for(int i=0;i<objects.length();i++)
	{
		drawOne(p,mode);
		p=p->next;
	}
}

void drawOne(shape_ptr drawShape, GLenum mode)
{
	glPushMatrix();
	int id = drawShape->type;

	GLfloat transX = drawShape->position[0];
	GLfloat transY = drawShape->position[1];
	GLfloat transZ = drawShape->position[2];
	
	GLfloat rotatX = drawShape->rotation[0];
	GLfloat rotatY = drawShape->rotation[1];
	GLfloat rotatZ = drawShape->rotation[2];

	GLfloat scaleX = drawShape->scale[0];
	GLfloat scaleY = drawShape->scale[1];
	GLfloat scaleZ = drawShape->scale[2];

	GLfloat* spec = &drawShape->specmat[0];
	GLfloat* diff = &drawShape->diffmat[0];
	GLfloat* ambi = &drawShape->ambimat[0];
	GLfloat shiny = drawShape->shininess;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
	glMaterialf(GL_FRONT, GL_SHININESS, shiny);

	glTranslatef(transX,transY,transZ);
	glScalef(scaleX,scaleY,scaleZ);
	glRotatef(rotatX,1,0,0);
	glRotatef(rotatY,0,1,0);
	glRotatef(rotatZ,0,0,1);

	if(mode==GL_SELECT) glLoadName(drawShape->ID);

	if(id==BOARDPIECE)
	{
		glEnable(GL_TEXTURE_2D);
		if( drawShape->texID==1 ) glBindTexture( GL_TEXTURE_2D, 1);
		else if( drawShape->texID==2 ) glBindTexture( GL_TEXTURE_2D, 2);
		fieldSquare(texArray[drawShape->ID]);
		glDisable(GL_TEXTURE_2D);
		glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	}
	if(id==BOARDBASE)
	{
		boardBase();
	}
	if(id==PAWN)
	{
		drawPiece(pb);
		drawPiece(pawn);
	}
	if(id==BISHOP)
	{
		drawPiece(pb);
		drawPiece(bishop);
	}
	if(id==KING)
	{
		drawPiece(pb);
		drawPiece(king);
	}
	if(id==QUEEN)
	{
		drawPiece(pb);
		drawPiece(queen);
	}
	if(id==ROOK)
	{
		drawPiece(pb);
		drawPiece(rook);
	}
	if(id==KNIGHT)
	{
		drawPiece(pb);
		drawPiece(knight);
	}
	glPopMatrix();
}

void keyboardInterrupt(unsigned char keyPressed, int x, int y)
{
//	if( keyPressed=='A' || keyPressed=='a' ) COLOR_MODE = AMBIENT;
//	if( keyPressed=='D' || keyPressed=='d' ) COLOR_MODE = DIFFUSE;
//	if( keyPressed=='S' || keyPressed=='s' ) COLOR_MODE = SPECULAR;
	if( keyPressed=='q' || keyPressed=='Q' ) exit(0);
    if( keyPressed=='W' || keyPressed=='w' )
    {
        etVector increment = camera::vpn() * camera::advanceIncrement;

        lookAt      = lookAt + increment;
        camPosition = camPosition + increment;
    }
	if( keyPressed=='A' || keyPressed=='a' )
	{
        etVector left = (camera::vpn() | vup) * -camera::advanceIncrement;
        
        lookAt      = lookAt + left;
        camPosition = camPosition + left;
	}
	if( keyPressed=='D' || keyPressed=='d' )
	{
	    etVector right = (camera::vpn() | vup) * camera::advanceIncrement;
        
        lookAt      = lookAt + right;
        camPosition = camPosition + right;
	}
	if( keyPressed=='S' || keyPressed=='s' )
	{
        etVector increment = camera::vpn() * camera::advanceIncrement;
        
        lookAt      = lookAt - increment;
        camPosition = camPosition - increment;
	}
	if( keyPressed==' ' ) seedBoard();
	if( keyPressed=='z' )
	{
		if( PIECE_MODE==PAWN && OBJECT_MODE==REDPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else 
		{
			OBJECT_MODE = REDPIECE;
			PIECE_MODE = PAWN;
		}
	}
	if( keyPressed=='Z' )
	{
		if( PIECE_MODE==PAWN && OBJECT_MODE==GREENPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = GREENPIECE;
			PIECE_MODE = PAWN;
		}
	}
	if( keyPressed=='x' )
	{
		if( PIECE_MODE==ROOK && OBJECT_MODE==REDPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = REDPIECE;
			PIECE_MODE = ROOK;
		}
	}
	if( keyPressed=='X' )
	{
		if( PIECE_MODE==ROOK && OBJECT_MODE==GREENPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = GREENPIECE;
			PIECE_MODE = ROOK;
		}
	}
	if( keyPressed=='c' )
	{
		if( PIECE_MODE==KNIGHT && OBJECT_MODE==REDPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = REDPIECE;
			PIECE_MODE = KNIGHT;
		}
	}
	if( keyPressed=='C' )
	{
		if( PIECE_MODE==KNIGHT && OBJECT_MODE==GREENPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = GREENPIECE;
			PIECE_MODE = KNIGHT;
		}
	}
	if( keyPressed=='v' )
	{
		if( PIECE_MODE==BISHOP && OBJECT_MODE==REDPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = REDPIECE;
			PIECE_MODE = BISHOP;
		}
	}
	if( keyPressed=='V' )
	{
		if( PIECE_MODE==BISHOP && OBJECT_MODE==GREENPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = GREENPIECE;
			PIECE_MODE = BISHOP;
		}
	}
	if( keyPressed=='n' )
	{
		if( PIECE_MODE==KING && OBJECT_MODE==REDPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = REDPIECE;
			PIECE_MODE = KING;
		}
	}
	if( keyPressed=='N' )
	{
		if( PIECE_MODE==KING && OBJECT_MODE==GREENPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = GREENPIECE;
			PIECE_MODE = KING;
		}
	}
	if( keyPressed=='b' )
	{
		if( PIECE_MODE==QUEEN && OBJECT_MODE==REDPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = REDPIECE;
			PIECE_MODE = QUEEN;
		}
	}
	if( keyPressed=='B' )
	{
		if( PIECE_MODE==QUEEN && OBJECT_MODE==GREENPIECE )
		{
			OBJECT_MODE = 0;
			PIECE_MODE = 0;
		}
		else
		{
			OBJECT_MODE = GREENPIECE;
			PIECE_MODE = QUEEN;
		}
	}
	switch(keyPressed)
	{
		case '1': lighton[1]=!lighton[1];
					LIGHT_MODE = ONE;
				  break;
		case '2': lighton[2]=!lighton[2];
					LIGHT_MODE = TWO;
				  break;
		case '3': lighton[3]=!lighton[3];
					LIGHT_MODE = THREE;
				  break;
		case '4': lighton[4]=!lighton[4];
					LIGHT_MODE = FOUR;
				  break;
		case '5': lighton[5]=!lighton[5];
					LIGHT_MODE = FIVE;
				  break;
		case '6': lighton[6]=!lighton[6];
					LIGHT_MODE = SIX;
				  break;
		case '7': lighton[7]=!lighton[7];
					LIGHT_MODE = SEVEN;
				  break;
		case '0': lighton[0]=!lighton[0];
					LIGHT_MODE = ZERO;
				  break;
	}
	if( (keyPressed=='u' || keyPressed=='U' || keyPressed=='i' ||
		keyPressed=='I' || keyPressed=='o' || keyPressed=='O' ||
		keyPressed=='p' || keyPressed=='P') && COLOR_MODE!=NONE )
	{
		int whichLight = 0;
		if( LIGHT_MODE==ONE ) whichLight = 1;
		else if( LIGHT_MODE==TWO ) whichLight = 2;
		else if( LIGHT_MODE==THREE ) whichLight = 3;
		else if( LIGHT_MODE==FOUR ) whichLight = 4;
		else if( LIGHT_MODE==FIVE ) whichLight = 5;
		else if( LIGHT_MODE==SIX ) whichLight = 6;
		else if( LIGHT_MODE==SEVEN ) whichLight = 7;
		
		switch(keyPressed)
		{
		case 'u':
			lightc[whichLight][COLOR_MODE-30][0] = lightc[whichLight][COLOR_MODE-30][0] + 0.05;
			if(lightc[whichLight][COLOR_MODE-30][0]>1) lightc[whichLight][COLOR_MODE-30][0] = 1;
			break;
		case 'U':
			lightc[whichLight][COLOR_MODE-30][0] = lightc[whichLight][COLOR_MODE-30][0] - 0.05;
			if(lightc[whichLight][COLOR_MODE-30][0]<0) lightc[whichLight][COLOR_MODE-30][0] = 0;
			break;
		case 'i':
			lightc[whichLight][COLOR_MODE-30][1] = lightc[whichLight][COLOR_MODE-30][1] + 0.05;
			if(lightc[whichLight][COLOR_MODE-30][1]>1) lightc[whichLight][COLOR_MODE-30][2] = 1;
			break;
		case 'I':
			lightc[whichLight][COLOR_MODE-30][1] = lightc[whichLight][COLOR_MODE-30][1] - 0.05;
			if(lightc[whichLight][COLOR_MODE-30][1]<0) lightc[whichLight][COLOR_MODE-30][1] = 0;
			break;			
		case 'o':
			lightc[whichLight][COLOR_MODE-30][2] = lightc[whichLight][COLOR_MODE-30][2] + 0.05;
			if(lightc[whichLight][COLOR_MODE-30][2]>1) lightc[whichLight][COLOR_MODE-30][2] = 1;
			break;
		case 'O':
			lightc[whichLight][COLOR_MODE-30][2] = lightc[whichLight][COLOR_MODE-30][2] - 0.05;
			if(lightc[whichLight][COLOR_MODE-30][2]<0) lightc[whichLight][COLOR_MODE-30][2] = 0;		
			break;
		}
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutPostRedisplay();
}

void mouseInterrupt(int button, int state, int x, int y)
{
	if( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN )
	{
//		cout << "Started X: " << x << " Y: " << y << endl;
		CAMERA_MODE = ROTATE_MODE;
        mouse.Down( RIGHT );
        mouse.SetPosition(x, y);
	}
	if( button==GLUT_RIGHT_BUTTON && state==GLUT_UP )
	{
//		cout << "Ended X: " << x << " Y: " << y << endl;
		CAMERA_MODE = 0;
        mouse.Up( RIGHT );
	}
	if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
	{
		shape_ptr obj = NULL;
		int pickedType = 0;
		pickedObject = pickFunction(button, state, x, y);
		if( pickedObject!=999)
		{
			obj = objects.find(pickedObject);
			pickedType = obj->type;
		}
		
		if( pickedType!=BOARDPIECE && pickedType!=BOARDBASE && pickedObject!=999 ) // objectID != 0-64
		{
			mover.setObj(obj);
			mover.setStart();
			mover.on(true);
		}
		if( pickedType==BOARDPIECE )
		{
			if(mover.on())
			{
				if( positionFilled[pickedObject]==0 )
				{
					mover.setFinish( pickedObject );
					moveVector = mover.getDifference();
					cout << "x: " << moveVector[0] << " y: " << moveVector[1] << endl;
					inMotion = true;
					mover.on(false);
					glutTimerFunc(10,movePiece,(int)(30*sqrt(moveVector[0]*moveVector[0]+moveVector[1]*moveVector[1])));
					mover.piece->location=pickedObject;
				}
			}
			else if( OBJECT_MODE==REDPIECE )
			{
					positionFilled[pickedObject] = objID;
					switch(	PIECE_MODE )
					{
					case PAWN:
						addRed(objects, pickedObject, objID, PAWN);
						break;
					case ROOK:
						addRed(objects, pickedObject, objID, ROOK);
						break;
					case KNIGHT:
						addRed(objects, pickedObject, objID, KNIGHT);
						break;
					case BISHOP:
						addRed(objects, pickedObject, objID, BISHOP);
						break;
					case KING:
						addRed(objects, pickedObject, objID, KING);
						break;
					case QUEEN:
						addRed(objects, pickedObject, objID, QUEEN);
						break;
					}
			
			}
			else if( OBJECT_MODE==GREENPIECE )
			{
					positionFilled[pickedObject] = objID;
					switch( PIECE_MODE )
					{
					case PAWN:
						addGreen(objects, pickedObject, objID, PAWN);
						break;
					case ROOK:
						addGreen(objects, pickedObject, objID, ROOK);
						break;
					case KNIGHT:
						addGreen(objects, pickedObject, objID, KNIGHT);
						break;
					case BISHOP:
						addGreen(objects, pickedObject, objID, BISHOP);
						break;
					case KING:
						addGreen(objects, pickedObject, objID, KING);
						break;
					case QUEEN:
						addGreen(objects, pickedObject, objID, QUEEN);
						break;
					}
				
			}
			else
			{
				CAMERA_MODE = TRANSLATE_MODE;
                mouse.Down( LEFT );
                mouse.SetPosition(x, y);
			}
				
			glutPostRedisplay();
		}
		else if( pickedType==PAWN || pickedType==ROOK || pickedType==KNIGHT
			  || pickedType==BISHOP || pickedType==QUEEN || pickedType==KING )
		{
			if( OBJECT_MODE==REDPIECE )
			{	
				addRed(objects, pickedObject, objID, pickedType);
				for(int i=0;i<64;i++) if(positionFilled[i]==pickedObject) positionFilled[i]=0;
				mover.on(false);
			}
			else if( OBJECT_MODE==GREENPIECE )
			{	
				addGreen(objects, pickedObject, objID, pickedType);
				for(int i=0;i<64;i++) if(positionFilled[i]==pickedObject) positionFilled[i]=0;
				mover.on(false);
			}
			else 
			{
				CAMERA_MODE = TRANSLATE_MODE;
				mouse.Down( LEFT );
                mouse.SetPosition(x, y);
			}
			glutPostRedisplay();
		}
		else if( pickedType!=0 )
		{
			CAMERA_MODE = TRANSLATE_MODE;
			mouse.Down( LEFT );
            mouse.SetPosition(x, y);
		}
	}
	if( button==GLUT_LEFT_BUTTON && state==GLUT_UP )
	{
		if( CAMERA_MODE==TRANSLATE_MODE ) CAMERA_MODE = NONE;
        mouse.Up( LEFT );
	}
	glutPostRedisplay();
}

void liftPiece(int passVal)
{
	mover.piece->position[1] += 2.0f/33.0f;
	glutPostRedisplay();
	passVal--;
	if(passVal>0) glutTimerFunc(10,liftPiece,passVal);
}

void movePiece(int passVal)
{
	float increment = 30*sqrt(moveVector[0]*moveVector[0]+moveVector[1]*moveVector[1]);
	if (passVal >= increment*(2.0f/3.0f))
		mover.piece->position[1] += 2.0f / (increment / 3.0f);
	else if (passVal < increment/3.0f)
		mover.piece->position[1] -= 2.0f / (increment / 3.0f);
	else
	{
		mover.piece->position[0] -= (float)moveVector[0] / (increment / 3.0f);
		mover.piece->position[2] -= (float)moveVector[1] / (increment / 3.0f);
	}
	glutPostRedisplay();
	passVal--;
	if(passVal>0) glutTimerFunc(10,movePiece,passVal);
	else
	{
		mover.piece->position[1] = 0.2f;
		mover.piece->position[0] = -3.5+mover.piece->location/8;
		mover.piece->position[2] = -3.5+mover.piece->location%8;
		inMotion = false;
	}
}

void dropPiece(int passVal)
{
	mover.piece->position[1] -= 2.0f/33.0f;
	glutPostRedisplay();
	passVal--;
	if(passVal>0) glutTimerFunc(10,dropPiece,passVal);
}

void seedBoard()
{
	if(!seeded)
	{
		seedStart = objID;
		for(int i=8;i<16;i++) addGreen(objects, i, objID, PAWN);
		addGreen(objects, 0, objID, ROOK);
		addGreen(objects, 7, objID, ROOK);
		addGreen(objects, 1, objID, KNIGHT);
		addGreen(objects, 6, objID, KNIGHT);
		addGreen(objects, 2, objID, BISHOP);
		addGreen(objects, 5, objID, BISHOP);
		addGreen(objects, 4, objID, QUEEN);
		addGreen(objects, 3, objID, KING);
		for(int i=48;i<56;i++) addRed(objects, i, objID, PAWN);
		addRed(objects, 63, objID, ROOK);
		addRed(objects, 56, objID, ROOK);
		addRed(objects, 57, objID, KNIGHT);
		addRed(objects, 62, objID, KNIGHT);
		addRed(objects, 61, objID, BISHOP);
		addRed(objects, 58, objID, BISHOP);
		addRed(objects, 60, objID, QUEEN);
		addRed(objects, 59, objID, KING);
		seeded = true;
	}
	else
	{
		for(int i=0;i<32;i++)
		objects.erase(seedStart+i);
		seeded = false;
	}
}

void motion(int x, int y)
{
    mouse.SetPosition(x, y);
	if(mouse.IsActive() && mouse.HasMoved())
	{
        mouse.Update();
        glutPostRedisplay();
	}
}

int pickFunction(int button, int state, int x, int y)
{
	GLuint selectBuf[MAX_NAME_BUFFER];
	GLint hits;
	GLint viewport[4];
	int hitObject = 0;
	printf ("win:x%d y%d\n",x,y);
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(MAX_NAME_BUFFER,selectBuf);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] -y),1.0,1.0,viewport);
	gluPerspective(camera::viewAngle, camera::aspect, camera::nearClip, camera::farClip);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(camPosition.x,camPosition.y,camPosition.z,lookAt.x,lookAt.y,lookAt.z,vup.x,vup.y,vup.z);
    glTranslatef( mouse.MouseUpdate.Translation.x , mouse.MouseUpdate.Translation.y , mouse.MouseUpdate.Translation.z );
    scene::spin = scene::spin + mouse.MouseUpdate.Rotation;
	glRotatef(scene::spin.x,0,1,0);
	glRotatef(scene::spin.y,1,0,0);
	glRenderMode(GL_SELECT);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glInitNames();
	glPushName(0);
	drawAll(GL_SELECT);

	hits = glRenderMode(GL_RENDER);
	hitObject = processHits (hits, selectBuf);
	
	cout << "hitObject: " << hitObject << endl;
	
	glPopMatrix();
	if(!inMotion) return hitObject;
	else return 999;
}

int processHits(GLint signedHits, GLuint buffer[])
{
	unsigned int i, j, hits;
	GLuint names, *ptr, minZ, *ptrNames, numberOfNames;
	ptrNames = 0;
	numberOfNames = 0;
	hits = signedHits;
	
	printf("hits = %d\n", hits);
	ptr = (GLuint *) buffer;
	minZ = 0xffffffff;
	
	for(i=0;i<hits;i++)
	{
		names = *ptr;
		ptr++;
		if (*ptr < minZ) 
		{
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr+2;
		}

		ptr+=names+2;
	}
	printf("The closest object is ");
	ptr = ptrNames;
	int what = 0;
	for(j=0;j<numberOfNames;j++,ptr++)
	{
		what = *ptr;
		printf ("%d\n", what);
	}
	if(numberOfNames>0) return what;
	else return 999;	
}
// processHits taken in part from http://www.lighthouse3d.com/opengl/picking
// /index.php?openglway3
// Adapted from the Red Book, this code found in a tutorial explaining
// the datatype for the minimum and maximum depth of picked objects.
