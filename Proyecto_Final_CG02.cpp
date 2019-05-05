#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"
//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0;
float giroMonito = 0;
float movBrazoDer = 0.0;

#define MAX_FRAMES 9
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	float movBrazoDer;
	float movBrazoDerInc;

	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=5;			//introducir datos
bool play=false;
int playIndex=0;

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

////////////////////////////////// Montaña Rusa///////////////////
CTexture text7; // Tubo amarillo
CTexture text8; //Apoyo metálico
CTexture text9; //Bandera carreras
///////////////////////////////////////////////////////////////////

CTexture tree;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

////////////////////////////////// Montaña Rusa///////////////////
CFiguras fig8;  // Tubo Montaña Rusa
CFiguras fig9;  // Apoyo metálico
CFiguras fig10; //Bandera carreras
///////////////////////////////////////////////////////////////////

//Figuras de 3D Studio
CModel kit;
CModel llanta;
CModel casita;
CModel oldhouse;

//Animación del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float movKitY = 4.0;
float rotKit = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = false;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;
bool recorrido8 = false;



void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazoDer = KeyFrame[0].movBrazoDer;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	KeyFrame[playIndex].movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;

}

void ciudad ()
{

	
		glPushMatrix(); // Pavimento
			glTranslatef(-47,0.0,-19);
			glRotatef(90, 0, 1, 0);
			//glScalef(40,0.1,7);
			glScalef(200,0.1,250);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		///////////////////////////// Montaña Rusa /////////////////////////////////////

		glPushMatrix(); //////////////// Montaña Rusa tubo 1
		glTranslatef(20.0, 1.5, -20.0);
		glRotatef(90, 0, 1, 0);
		glScalef(7.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 1
		glTranslatef(19, 1.5, -33.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 2
		glTranslatef(19, 1.5, -30.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 3
		glTranslatef(19, 1.5, -27.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 4
		glTranslatef(19, 1.5, -24.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 5
		glTranslatef(19, 1.5, -21.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 6
		glTranslatef(19, 1.5, -18.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 7
		glTranslatef(19, 1.5, -15.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 8
		glTranslatef(19, 1.5, -12.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 9
		glTranslatef(19, 1.5, -9.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 10
		glTranslatef(19, 1.5, -6.0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2
		glTranslatef(18.0, 1.5, -20.0);
		glRotatef(90, 0, 1, 0);
		glScalef(7.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo vuelta 1
		glTranslatef(19.5, 1.5, -5.1);
		glRotatef(60, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo vuelta 2
		glTranslatef(18.1, 1.5, -3.7);
		glRotatef(30, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo vuelta 3
		glTranslatef(16.3, 1.5, -3.2);
		glRotatef(60, 1, 0, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo vuelta 4
		glTranslatef(14.6, 1.5, -3.8);
		glRotatef(330, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 vuelta 1
		glTranslatef(17.6, 1.5, -5.1);
		glRotatef(60, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); /////////////// Montaña Rusa tubo 2 vuelta 2
		glTranslatef(16.2, 1.5, -4.2);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 
		glTranslatef(17.8, 1.5, -4.3);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 3.5, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 
		glTranslatef(16.4, 1.5, -3.7);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 2.1, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2
		glTranslatef(18.5, 8.1, -10.7);
		glRotatef(70, 0, 1, 1);
		glScalef(6.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 3, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1
		glTranslatef(17.2, 8.1, -10.5);
		glRotatef(70, 0, 1, 1);
		glScalef(6.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 3, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 11
		glTranslatef(14.9, 2.5, -4.8);
		glRotatef(10, 1, 1, 1);
		glScalef(0.5, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 2.7, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 11.5
		glTranslatef(15.4, 3.5, -6.0);
		glRotatef(10, 1, 1, 1);
		glScalef(0.5, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 2.7, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 12
		glTranslatef(16.5, 5.5, -7.8);
		glRotatef(10, 1, 1, 1);
		glScalef(0.5, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 2.7, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 13
		glTranslatef(17.9, 8.5, -10.8);
		glRotatef(10, 1, 1, 1);
		glScalef(0.5, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 2.7, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 14
		glTranslatef(19.4, 11.5, -13.8);
		glRotatef(10, 1, 1, 1);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 2.7, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 vuelta parte 2 (1)
		glTranslatef(22.0, 14.5, -17.9);
		glRotatef(60, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 vuelta parte 2 (1)
		glTranslatef(21.0, 14.5, -17.9);
		glRotatef(60, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 vuelta parte 2 (2)
		glTranslatef(22.2, 14.5, -19.7);
		glRotatef(120, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 vuelta parte 2 (2)
		glTranslatef(20.9, 14.5, -20.3);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 vuelta parte 2 (2)
		glTranslatef(20.5, 14.5, -18.6);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 curva fondo
		glTranslatef(19.6, 1.5, -35.2);
		glRotatef(290, 0, 1, 0);
		glScalef(0.7, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 curva fondo 2
		glTranslatef(16.4, 1.5, -36.6);
		glRotatef(180, 0, 1, 0);
		glScalef(1.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 curva fondo 2
		glTranslatef(13.5, 1.5, -22.7);
		glRotatef(90, 0, 1, 0);
		glScalef(7.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 1 curva fondo
		glTranslatef(16.2, 1.5, -35.3);
		glRotatef(90, 0, 1, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 2 curva fondo
		glTranslatef(17.2, 1.5, -35.3);
		glRotatef(90, 0, 1, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 3 curva fondo
		glTranslatef(14.8, 1.5, -35.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.66, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 3 perpendicular lado 2
		glTranslatef(14.8, 1.5, -33.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 4 perpendicular lado 2
		glTranslatef(14.8, 1.5, -31.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 5 perpendicular lado 2
		glTranslatef(14.8, 1.5, -28.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 6 perpendicular lado 2
		glTranslatef(14.8, 1.5, -25.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 7 perpendicular lado 2
		glTranslatef(14.8, 1.5, -23.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 8 perpendicular lado 2
		glTranslatef(14.8, 1.5, -21.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 9 perpendicular lado 2
		glTranslatef(14.8, 1.5, -18.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 10 perpendicular lado 2
		glTranslatef(14.8, 1.5, -15.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 11 perpendicular lado 2
		glTranslatef(14.8, 1.5, -13.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 12 perpendicular lado 2
		glTranslatef(14.8, 1.5, -11.3);
		glRotatef(90, 1, 0, 0);
		glScalef(0.64, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa línea perpendicular 13 perpendicular lado 2
		glTranslatef(14.8, 1.5, -9.3);
		glRotatef(10, 0, 1, 0);
		glScalef(0.625, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 curva fondo 2
		glTranslatef(17.0, 1.5, -34.0);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 curva fondo 2
		glTranslatef(16.0, 1.5, -21.9);
		glRotatef(90, 0, 1, 0);
		glScalef(6.07, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 curva 3
		glTranslatef(13.2, 1.5, -7.8);
		glRotatef(70, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular curva 3
		glTranslatef(15.6, 1.5, -8.7);
		glRotatef(70, 0, 1, 0);
		glScalef(0.6, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 curva 3
		glTranslatef(12.0, 1.5, -6.9);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 inclinación 2
		glTranslatef(15.1, 9.1, -14.7);
		glRotatef(70, 0, 1, 1);
		glScalef(5.8, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 perpendicular curva 3
		glTranslatef(14.6, 1.5, -6.6);
		glRotatef(60, 0, 1, 0);
		glScalef(0.6, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 3 perpendicular curva 3
		glTranslatef(12.0, 1.5, -5.5);
		glRotatef(180, 1, 0, 0);
		glScalef(1.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 4 perpendicular curva 3
		glTranslatef(11.0, 1.5, -5.5);
		glRotatef(180, 0, 1, 0);
		glScalef(1.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 5 perpendicular curva 3
		glTranslatef(9.0, 1.5, -6.1);
		glRotatef(90, 0, 1, 0);
		glScalef(0.3, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 inclinación 2
		glTranslatef(13.1, 9.5, -14.6);
		glRotatef(70, 0, 1, 1);
		glScalef(6.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 1 curva 3
		glTranslatef(13.0, 1.5, -6.2);
		glRotatef(90, 0, 1, 0);
		glScalef(0.36, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 2 curva 3
		glTranslatef(12.0, 1.5, -6.2);
		glRotatef(90, 0, 1, 0);
		glScalef(0.36, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 2 curva 3
		glTranslatef(11.0, 1.5, -6.2);
		glRotatef(90, 0, 1, 0);
		glScalef(0.36, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 1 inclinación 2
		glTranslatef(10.6, 2.5, -7.8);
		glRotatef(40, 0, 1, 1);
		glScalef(0.9, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 2 inclinación 2
		glTranslatef(11.8, 5.0, -10.3);
		glRotatef(37, 0, 1, 1);
		glScalef(0.9, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 3 inclinación 2
		glTranslatef(12.8, 7.0, -12.3);
		glRotatef(37, 0, 1, 1);
		glScalef(0.9, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 4 inclinación 2
		glTranslatef(14.0, 9.0, -14.3);
		glRotatef(37, 0, 1, 1);
		glScalef(0.9, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 5 inclinación 2
		glTranslatef(14.9, 11.0, -16.3);
		glRotatef(37, 0, 1, 1);
		glScalef(0.9, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 6 inclinación 2
		glTranslatef(16.0, 13.0, -18.7);
		glRotatef(37, 0, 1, 1);
		glScalef(0.9, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 1 vuelta inclinación 2
		glTranslatef(17.5, 14.5, -18.7);
		glRotatef(180, 0, 1, 0);
		glScalef(1.0, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo 2 vuelta inclinación 2
		glTranslatef(17.5, 14.5, -20.3);
		glRotatef(180, 0, 1, 0);
		glScalef(1.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 1 vuelta inclinación 2
		glTranslatef(17.5, 14.4, -19.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 2 vuelta inclinación 2
		glTranslatef(18.5, 14.4, -19.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 3 vuelta inclinación 2
		glTranslatef(19.5, 14.4, -19.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 4 vuelta inclinación 2
		glTranslatef(20.5, 14.4, -19.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Montaña Rusa tubo perpendicular 4 vuelta inclinación 2
		glTranslatef(21.5, 14.4, -19.5);
		glRotatef(90, 0, 1, 0);
		glScalef(0.5, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig8.prisma(1, 4, 1, text7.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(20.0, 1.0, -31.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(20.0, 1.0, -27.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(20.0, 1.0, -23.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(20.0, 1.0, -19.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(20.0, 1.0, -15.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(20.0, 1.0, -11.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(20.0, 1.0, -7.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		//////////////////////////////////////// Segundo Tubo ///////////////////



		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -31.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -27.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -23.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -19.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -15.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -11.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(18.0, 1.0, -7.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		/////////////////////////////// Tercer tubo //////////////////////////

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(16.0, 1.0, -31.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(16.0, 1.0, -27.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(16.0, 1.0, -23.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(16.0, 1.0, -19.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(16.0, 1.0, -15.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(16.0, 1.0, -11.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(15.1, 1.0, -7.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		/////////////////////////////// Cuarto tubo ///////////////////////////////

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(13.5, 1.0, -31.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(13.5, 1.0, -27.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(13.5, 1.0, -23.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(13.5, 1.0, -19.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(13.5, 1.0, -15.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(13.5, 1.0, -11.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(12.5, 1.0, -7.0);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(12.5, 1.0, -5.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		/////////////////////////// Apoyo para las cuestas //////////////////////////////

		glPushMatrix(); //////////////// Apoyo 1
		glTranslatef(17.0, 1.0, -3.2);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 2
		glTranslatef(17.0, 1.0, -4.2);
		glRotatef(90, 0, 0, 1);
		glScalef(0.2, 0.2, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 3
		glTranslatef(17.0, 1.0, -21.2);
		glRotatef(90, 0, 0, 1);
		glScalef(0.1, 0.5, 32.0);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();


		/////////////////////////// Apoyo horizontal ///////////////////////////////

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(17.0, 0.5, -31.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(16.8, 0.5, -27.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);		
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(17.0, 0.5, -23.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(17.0, 0.5, -19.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(17.0, 0.5, -15.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(17.0, 0.5, -11.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Apoyo 4
		glTranslatef(17.0, 0.5, -7.8);
		glRotatef(90, 0, 0, 1);
		glScalef(0.050, 7.0, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo elevaciones
		glTranslatef(17.0, 3.0, -7.9);
		glRotatef(90, 1, 0, 0);
		glScalef(0.1, 0.1, 4.3);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo 2 elevaciones
		glTranslatef(17.0, 5.0, -13.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.1, 0.1, 11.3);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo 3 elevaciones
		glTranslatef(14.0, 5.0, -13.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.1, 6.1, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo 3 perpendicular 1 elevaciones
		glTranslatef(12.5, 6.7, -13.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.8, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo 3 perpendicular 2 elevaciones
		glTranslatef(14.5, 6.5, -13.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.7, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();



		glPushMatrix(); ////////////////Apoyo 4 elevaciones
		glTranslatef(14.0, 5.0, -19.0);
		glRotatef(90, 0, 0, 1);
		glScalef(0.1, 6.1, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo 4 perpendicular 1 elevaciones
		glTranslatef(15.4, 9.4, -19.0);
		glRotatef(90, 0, 0, 1);
		glScalef(2.2, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); ////////////////Apoyo 4 perpendicular 2 elevaciones
		glTranslatef(17.0, 9.3, -19.0);
		glRotatef(90, 0, 0, 1);
		glScalef(2.2, 0.1, 0.1);
		glDisable(GL_LIGHTING);
		fig9.prisma(1, 4, 1, text8.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		///////////////////////// Bandera de carreras//////////////////

		glPushMatrix(); //////////////// Bandera 1
		glTranslatef(17.0, 11.3, -20.6);
		glRotatef(90, 0, 0, 1);
		glScalef(0.8, 0.1, 3.3);
		glDisable(GL_LIGHTING);
		fig10.prisma(1, 4, 1, text9.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //////////////// Bandera 1
		glTranslatef(15.5, 8.3, -20.6);
		glRotatef(90, 0, 0, 1);
		glScalef(0.8, 0.1, 3.3);
		glDisable(GL_LIGHTING);
		fig10.prisma(1, 4, 1, text9.GLindex);
		glEnable(GL_LIGHTING);
		glPopMatrix();

		/////////////////////////////////// Fin montaña Rusa /////////////////////////////////
}


void arbol_alpha()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable( GL_ALPHA_TEST );
		glAlphaFunc( GL_GREATER, 0.1 );
		glBindTexture(GL_TEXTURE_2D, tree.GLindex);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
				
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();
		glDisable( GL_ALPHA_TEST );
		glEnable(GL_LIGHTING);
				
	glPopMatrix();
}

void arbol_blend()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);     // Turn Blending On
		//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, tree.GLindex);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();	
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();	
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();				
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
		glEnd();		
	glPopMatrix();
	glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);
}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0 ,2.0 ,1 ,text2.GLindex);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, 0);
			glPushMatrix();//Cabeza
				glTranslatef(0, 1.0, 0);
				fig7.esfera(0.75, 15, 15, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
			glTranslatef(1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(movBrazoDer, 0.0, 0.0, 1.0);
				glRotatef(-45, 0, 1, 0); 
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
			glTranslatef(-1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45, 0, 1, 0); 
				glRotatef(25, 0, 0, 1);
				glRotatef(25, 1, 0, 0); 
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glColor3f(0, 0, 1);
			glTranslatef(0, -1.5, 0);
			fig7.prisma(1, 2, 1, 0);

			glPushMatrix(); //Pie Derecho -->
				glTranslatef(0.75, -0.5, 0);
				glRotatef(-15, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


			glPushMatrix(); //Pie Izquierdo -->
				glTranslatef(-0.75, -0.5, 0);
				glRotatef(-5, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodIzq, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}

////////////////////////////////////////////////////////////

			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	//glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
    //glColor4f(1.0f, 1.0f, 1.0f, 0.5); 
    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text4.LoadBMP("pavimento_1.bmp");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	///////////////////////////////////////////////Montaña Rusa///////
	text7.LoadBMP("montana_rusa/tubo_amarillo.bmp");		/////////
	text7.BuildGLTexture();                                 /////////
	text7.ReleaseImage();									////////
															///////
	text8.LoadBMP("montana_rusa/apoyo.bmp");               ////////
	text8.BuildGLTexture();								////////////
	text8.ReleaseImage();								////////////
															///////
	text9.LoadBMP("montana_rusa/bandera_carrera.bmp");		//////
	text9.BuildGLTexture();								//////////
	text9.ReleaseImage();								//////////
	//////////////////////////////////////////////////////////////


	tree.LoadTGA("Tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	kit._3dsLoad("kitt.3ds");	
	//kit.VertexNormals();
	
	llanta._3dsLoad("k_rueda.3ds");

	casita._3dsLoad("Dollshouse.3ds");

	oldhouse._3dsLoad("oldhouse/oldhouse.3ds");
	oldhouse.LoadTextureImages();
	oldhouse.GLIniTextures();
	oldhouse.ReleaseTextureImages();
	
	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();
	//montana_rusa_display_list = createDL();
	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
		KeyFrame[i].giroBrazo =0;
		KeyFrame[i].giroBrazoInc = 0;

	}*/

	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].giroMonito = 0;
	KeyFrame[0].movBrazoDer = 0;

	KeyFrame[1].posX = 20;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -3.5;
	KeyFrame[1].rotRodIzq = 60;
	KeyFrame[1].giroMonito = -90.0;
	KeyFrame[1].movBrazoDer = 40;

	KeyFrame[2].posX = 20;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = 4.0;
	KeyFrame[2].rotRodIzq = -20.0;
	KeyFrame[2].giroMonito = 0;
	KeyFrame[2].movBrazoDer = 0;

	KeyFrame[3].posX = 20;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = 4.0;
	KeyFrame[3].rotRodIzq = 40.0;
	KeyFrame[3].giroMonito = 45;
	KeyFrame[3].movBrazoDer = 90;

	KeyFrame[4].posX = 20;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = 4.0;
	KeyFrame[4].rotRodIzq = -40.0;
	KeyFrame[4].giroMonito = -45;
	KeyFrame[4].movBrazoDer = -90;
	//NEW//////////////////NEW//////////////////NEW//////////////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	
	glPushMatrix();

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					//glScalef(0.5, 0.5, 0.5);
					//monito();
					glCallList(ciudad_display_list);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);
					monito();
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();


			glPushMatrix(); //Casa M0delo 3ds
				glTranslatef(-12.0,0.0,-9.0);
				glScalef(0.3,0.3,0.3);
				casita.GLrender(NULL,_SHADED, 1);
			glPopMatrix();

			glPushMatrix(); //Casa M0delo 3ds
				glTranslatef(-32.0,0.0,-9.0);
				glScalef(0.7,0.7,0.7);
				oldhouse.GLrender(NULL,_SHADED, 1);
			glPopMatrix();


			

			glPushMatrix();
				glRotatef(90, 0, 1, 0);
				glScalef(0.3, 0.3, 0.3);
				


				glTranslatef(movKitX, movKitY, movKitZ);
				glRotatef(rotKit, 0, 1, 0);

				kit.GLrender(NULL,_SHADED,1.0); //Dibujamos la carroceria
				//llanta.GLrender(NULL,_SHADED,1.0);

				//Colocar aquí las llantas
				glPushMatrix(); //llanta frontal der
					glTranslatef(-6,-1,7.5);
					glRotatef(-rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

				glPushMatrix(); //llanta frontal izq
					glTranslatef(6,-1,7.5);	
					glRotatef(180,0,1,0);
					glRotatef(rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();
				
				glPushMatrix(); //llanta trasera der
					glTranslatef(-6,-1,-9.5);	
					glRotatef(-rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

				glPushMatrix(); //llanta trasera izq
					glTranslatef(6,-1,-9.5);	
					glRotatef(180,0,1,0);
					glRotatef(rotTires,1,0,0);
					llanta.GLrender(NULL,_SHADED,1.0);
				glPopMatrix();

			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-30, 0, 10);
				arbol_alpha();
			glPopMatrix();

			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); 

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto Final Feria");
			//pintaTexto(-11,10.5,-14,(void *)font,"Listas de Dibujo");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.01;
	fig3.text_der-= 0.01;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del coche
	if(g_fanimacion)
	{
		if(g_avanza)
		{
			movKitZ +=1.0;
			rotTires -= 20;
			if(movKitZ>130)
				g_avanza = false;
		}
		else
		{
			movKitZ -=1.0;
			rotTires += 20;
			if(movKitZ<0)
				g_avanza = true;
		}
	}

	if(circuito)
	{
		if(recorrido1)
		{
			movKitZ = movKitZ+7;

			if(movKitZ>155)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if(recorrido2)
		{
			rotKit = 90;
			movKitX = movKitX + 7;

			if(movKitX > 125)
			{
				recorrido2 = false;
				recorrido3 = true;
				
			}
		}


		if(recorrido3)
		{
			rotKit = 180; // La rotación necesaria para simular el giro del carro en la dirección correcta
			movKitZ = movKitZ - 7; // La velocidad que toma sobre el eje Z
			//movKitX = movKitX - 7; // La velocidad que toma sobre el eje X
	

			if(movKitZ < -155)
			{
				recorrido3 = false; // Se desactiva el recorrido actual (3)
				recorrido4 = true; // Se activa el recorrido siguiente (5)
			}
		}


		if(recorrido4)
		{
			rotKit = 360;
			movKitX = movKitX - 7;
			movKitY = movKitY + 5;
			
			if(movKitX<0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}

	
		if(recorrido5)
		{
			rotKit = 0;
			movKitZ = movKitZ + 7;
			if(movKitZ>0)
			{
				recorrido5 = false;
				recorrido6 = true;
			}
		}

		if (recorrido6) {
			rotKit = 0.0;
			movKitX = -45.0;
			movKitZ += 7;
			movKitY += 0.33;
			if (movKitZ >= -120.0) {
				recorrido6 = false;
				recorrido7 = true;
			}
		}

		if (recorrido7) {
			rotKit = 0.0;
			movKitX = 0.0;
			movKitZ += 7.0;

			if (movKitZ >= 120.0) {
				recorrido7 = false;
				recorrido8 = true;
			}
		}

		if (recorrido8) {
			rotKit = 0.0;
			movKitX = 47.0;
			movKitZ += 7.0;
			movKitY -= 0.3;
			if (movKitZ >= 150) {

				movKitY = 0.0;
				recorrido8 = false;
				recorrido2 = true;
			}
		}




	}


	//Movimiento del monito
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			giroMonito += KeyFrame[playIndex].giroMonitoInc;
			movBrazoDer += KeyFrame[playIndex].movBrazoDerInc;

			i_curr_steps++;
		}

	}

	/*frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}*/

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'O':		//  
		case 'o':
				g_fanimacion^= true; //Activamos/desactivamos la animacíon
				circuito = false;
			break;

		case 'i':		//  
		case 'I':
				circuito^= true; //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;

		case 'k':		//
		case 'K':
			if (FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':
		case 'L':
			if (play == false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play = false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			//printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			//printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			//printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			//printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			//printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			//printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			//printf("%f \n", giroMonito);
			break;

		case 'P':						
			giroMonito--;
			//printf("%f \n", giroMonito);
			break;
	

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex >1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}

int main ( int argc, char** argv )   // Main Function
{
	int submenu;

  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu(menuKeyFrame);
  glutAddMenuEntry("Guardar KeyFrame", 0);
  glutAddMenuEntry("Reproducir Animacion", 1);
  glutCreateMenu(menu);
  glutAddSubMenu("Animacion Monito", submenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop        ( );          // 

  return 0;
}
