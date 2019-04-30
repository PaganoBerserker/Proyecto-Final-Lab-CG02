/*
Erick Paniagua Trejo
Grupo 2
Visual Studio 2017
Práctica 11 de Casa "Piedra, papel o tijeras y like"
*/
#include "texture.h"
#include "figuras.h"
#include "Camera.h"

//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5; // Posición para que se  pueda mover
float giroMonito = 0; //Idem

float transZ = -5.0f;
float transX = 0.0f;
float angleX = 0.0f;
float angleY = 0.0f;
int screenW = 0.0;
int screenH = 0.0;
float angHombro = 0.0f;
float angcodo = 0.0f;
float angmu = 0.0f;
float angpul = 0.0f;
float angind = 0.0f;
float angmed = 0.0f;
float anganu = 0.0f;
float angme = 0.0f;

void prisma(void)

{
	GLfloat vertice[8][3] = {

	{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
	{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
	{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
	{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
	{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
	{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
	{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
	{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
	};

	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();

}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	glLoadIdentity();

	glTranslatef(transX, 0.0f, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Poner Código Aquí.

	//hombro
	glPushMatrix();
	glRotatef(angHombro, 0, 0, 1);
	glScalef(0.3f, 0.5f, 0.5f);
	glColor3f(1, 1, 1);
	prisma();
	glScalef(3, 2, 1);

	//bicep

	glTranslatef(0.65f, 0.0f, 0.0f);
	glScalef(1, 0.5, 1);
	glColor3f(1, 0, 0);
	prisma();

	//codo

	glScalef(1, 2, 1);
	glTranslatef(0.6f, 0.0, 0.0);
	glRotatef(angcodo, 0, 0, 1);
	glScalef(0.2f, 0.5f, 1.0f);
	glColor3f(0, 1, 0);
	prisma();

	//antebrazo

	glScalef(5, 2, 0.5);
	glTranslatef(0.5f, 0.0f, 0.0f);
	glScalef(0.8f, 0.5f, 1.0f);
	glColor3f(0, 0, 1);
	prisma();

	//muñeca

	glScalef(1.25, 2, 1);
	glTranslatef(0.45, 0, 0);
	glRotatef(angmu, 0, 1, 0);
	glScalef(0.1, 0.5, 1);
	glColor3f(1, 1, 0);
	prisma();

	glScalef(10, 2, 1);

	//palma
	glTranslatef(0.35, 0, 0);
	glScalef(0.6, 0.5, 1);
	glColor3f(0, 1, 1);
	prisma();

	//glScalef(1.66, 2, 1);

	glTranslatef(0, 2, -1);
	glScalef(0.3, 0.7, 1);
	//pulgar
	
	glTranslatef(-0.2, 0.285, 0);
	glScalef(0.2, 0.07, 1);
	glColor3f(0.5, 0.3, 0);
	prisma();
	
	//glScalef(5, 14.28, 1);

	//falanje pulgar
	glRotatef(angpul, 1, 0, 0);
	glTranslatef(0, 0.035, 0);
	glTranslatef(0.0, 0.035, 0);
	glScalef(10, 50, 1);
	glColor3f(0.2, 0.3, 0.1);

	prisma();
	glPopMatrix();
	glScalef(5, 14.29, 1);

	// índice
	glRotatef(angind, 0, 1, 0);
	glTranslatef(0.60, -0.13, 0);
	glScalef(0.2, 0.05, 1);
	glColor3f(1, 0, 1);
	prisma();

	glScalef(2, 20, 1);

	//falanje índice 
	glRotatef(angind, 0, 1, 0);
	glTranslatef(0.50, 0, 0);
	glScalef(0.5, 0.05, 1);
	glColor3f(0, 0, 1);
	prisma();

	glScalef(2, 20, 1);

	// falanje índice 2

	glTranslatef(0.50, 0, 0);
	glScalef(0.5, 0.05, 1);
	glColor3f(1, 1, 0);
	prisma();

	glScalef(2, 20, 1);

	// medio

	glTranslatef(-1.0, -0.20, 0);
	glScalef(0.5, 0.05, 1);
	glColor3f(1, 0, 1);
	prisma();

	glScalef(2, 20, 1);

	//falanje medio 1

	glTranslatef(0.50, 0, 0);
	glScalef(0.5, 0.05, 1);
	glColor3f(0, 0, 1);
	prisma();

	glScalef(2, 20, 1);

	//falanje medio 2
	glRotatef(angmed, 0, 1, 0);
	glTranslatef(0.60, 0, 0);
	glScalef(0.7, 0.05, 1);
	glColor3f(1, 1, 0);
	prisma();

	glScalef(1.48, 20, 1);

	//anular

	glTranslatef(-1.05, -0.13, 0),
	glScalef(0.5, 0.05, 1);
	glColor3f(1, 0, 1);
	prisma();

	glScalef(1.48, 20, 1);

	//falanje anular 1
	glRotatef(anganu, 0, 1, 0);
	glTranslatef(0.58, 0, 0);
	glScalef(0.5, 0.05, 1);
	glColor3f(0, 0, 1);
	prisma();

	glScalef(2, 20, 1);

	//falanje anular 2

	glTranslatef(0.60, 0, 0);
	glRotatef(anganu, 0, 1, 0); //////////////// 1 -> 0
	glScalef(0.71, 0.05, 1);
	glColor3f(1, 1, 0);
	prisma();

	glScalef(1.5, 20, 1);

	//meñique

	glTranslatef(-1.15, -0.12, 0);
	glScalef(-0.55, 0.05, 1);
	glColor3f(1, 0, 1);
	prisma();

	glScalef(1.9, 20, 1);

	// falanje meñique 1
	glRotatef(angme, 0, 1, 0);
	glTranslatef(-0.45, 0, 0);
	glScalef(0.4, 0.05, 1);
	glColor3f(0, 0, 1);
	prisma();

	glScalef(2.5, 20, 1);

	//falanje meñique 2
	glRotatef(angme, 0, 1, 0);
	glTranslatef(-0.40, 0, 0);
	glScalef(0.4, 0.05, 1);
	glColor3f(1, 1, 0);
	prisma();

	glutSwapBuffers();

	// Swap The Buffers

}

////////////////////////////////////////////////////////////////////////////////////////////////

float rotRodDer = 0;
float rotCabeza = 0;
float rotCuello = 0;
float rotBrazoIzq = 0;
float rotBrazoDer = 0;
float rotBrazoIzq2 = 0;
float rotBrazoDer2 = 0;

#define MAX_FRAMES 500 //Número máximo de keyframes ////////////// Poner N Keyframes
int i_max_steps = 10; //Número de pasos (tiempo) ///////// Más velocidad en la animación
int i_curr_steps = 0; //Frame actual (inicializar en 0)

int contador = 0;
int tam = 0;
FILE *archivo; //////////Apuntador a un archivo

typedef struct _frame
{
	//Variables para GUARDAR Key Frames				//Mismo nombre
	float angHombro;
	float angcodo;
	float angmu;
	float angpul;
	float angind;
	float angmed;
	float anganu;
	float angme;

	float angHombroInc;
	float angcodoInc;
	float angmuInc;
	float angpulInc;
	float angindInc;
	float angmedInc;
	float anganuInc;
	float angmeInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;	//introducir datos	
bool play = false; //Ejecutar animación
int playIndex = 0;

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

void saveFrame(void) // Se manda a llamar cuando se oprime K
{

	printf("frameindex %d\n", FrameIndex);
	KeyFrame[FrameIndex].angHombro = angHombro; 
	KeyFrame[FrameIndex].anganu = anganu; 
	KeyFrame[FrameIndex].angind = angind; 
	KeyFrame[FrameIndex].angme = angme; 
	KeyFrame[FrameIndex].angmu = angmu; 
	KeyFrame[FrameIndex].angpul = angpul; 
	KeyFrame[FrameIndex].angmed = angmed; 

	fprintf(archivo, "%.1f", anganu);
	fprintf(archivo, "%.1f", angmed);
	fprintf(archivo, "%.1f", angme);
	fprintf(archivo, "%.1f", angmu);
	fprintf(archivo, "%.1f", angpul);
	fprintf(archivo, "%.1f", angind);

	fprintf(archivo,"\n");

	printf("Anular: %.1f", KeyFrame[playIndex].anganu);
	printf("Medio: %.1f", KeyFrame[playIndex].angmed);
	printf("Menique: %.1f", KeyFrame[playIndex].angme);
	printf("Muñeca: %.1f", KeyFrame[playIndex].angmu);
	printf("Pulgar: %.1f", KeyFrame[playIndex].angpul);
	printf("Indice: %.1f", KeyFrame[playIndex].angind);

	FrameIndex++;
}

void resetElements(void) //Las variables se regresan a la posición actual
{
	anganu = KeyFrame[0].anganu; 
	angpul = KeyFrame[0].angpul; 
	angmu = KeyFrame[0].angmu; 
	angind = KeyFrame[0].angind; 
	angme = KeyFrame[0].angme; 
	angmed = KeyFrame[0].angmed; 
}

void interpolation(void) // Se calcula el incremento Keyframe siguiente - Keyframe actual / keyframes (tiempo)
{
	
	KeyFrame[playIndex].anganuInc = (KeyFrame[playIndex + 1].anganu - KeyFrame[playIndex].anganu) / i_max_steps; ////// Rodilla Derecha
	KeyFrame[playIndex].angmedInc = (KeyFrame[playIndex + 1].angmed - KeyFrame[playIndex].angmed) / i_max_steps; ////// Cabeza
	KeyFrame[playIndex].angmeInc = (KeyFrame[playIndex + 1].angme - KeyFrame[playIndex].angme) / i_max_steps; ////// Cuello
	KeyFrame[playIndex].angmuInc = (KeyFrame[playIndex + 1].angmu - KeyFrame[playIndex].angmu) / i_max_steps; ////// Brazo Izquierdo
	KeyFrame[playIndex].angpulInc = (KeyFrame[playIndex + 1].angpul - KeyFrame[playIndex].angpul) / i_max_steps; ////// Brazo Derecho
	KeyFrame[playIndex].angindInc = (KeyFrame[playIndex + 1].angind - KeyFrame[playIndex].angind) / i_max_steps; ////// Brazo Izquierdo 2
	
}

void salvarFrame_2(void) {

	int contador = -1;
	float arr[] = {
		
-6.5, -6.5, -6.5,0.0, -6.5, -6.5,
-7.0, - 7.0, -7.0,0.0, -7.0, -7.0,
-7.5, -7.5, -7.5,0.0, -7.5, -7.5,
-8.0, -8.0, -8.0,0.0, -8.0, - 8.0,
-8.5, -8.5, -8.5,0.0, -8.5, -8.5,
-9.0, -9.0, -9.0,0.0, -9.0, -9.0,
-9.5, -9.5, -9.5,0.0, -9.5, -9.5,
-10.0, -10.0, -10.0,0.0, -10.0, -10.0,
-10.5, -10.5, -10.5,0.0, -10.5, -10.5,
-11.0, -11.0, -11.0,0.0, -11.0, -11.0,
-11.5, -11.5, -11.5,0.0, -11.5, -11.5,
-12.0, -12.0, -12.0,0.0, -12.0, -12.0,
-12.5, -12.5, -12.5,0.0, -12.5, -12.5,
-13.0, -13.0, -13.0,0.0, -13.0, -13.0,
-13.5, -13.5, -13.5,0.0, -13.5, -13.5,
-14.0, -14.0, -14.0,0.0, -14.0, -14.0,
-14.5, -14.5, -14.5,0.0, -14.5, -14.5,
-15.0, -15.0, -15.0,0.0, -15.0, -15.0,
-15.5, -15.5, -15.5,0.0, -15.5, -15.5,
-16.0, -16.0, -16.0,0.0, -16.0, -16.0,
-16.5, -16.5, -16.5,0.0, -16.5, -16.5,
-17.0, -17.0, -17.0,0.0, -17.0, -17.0,
-17.5, -17.5, -17.5,0.0, -17.5, -17.5,
-18.0, -18.0, -18.0,0.0, -18.0, -18.0,
-19.0, -19.0, -19.0,0.0, -19.0, -19.0,
-19.5, -19.5, -19.5,0.0, -19.5, -19.5,
-19.0, -19.0, -19.0,0.0, -19.0, -19.0,
-18.5, -18.5, -18.5,0.0, -18.5, -18.5,
-18.0, -18.0, -18.0,0.0, -18.0, -18.0,
-17.5, -17.5, -17.5,0.0, -17.5, -17.5,
-17.0, -17.0, -17.0,0.0, -17.0, -17.0,
-16.5, -16.5, -16.5,0.0, -16.5, -16.5,
-16.0, -16.0, -16.0,0.0, -16.0, -16.0,
-15.5, -15.5, -15.5,0.0, -15.5, -15.5,
-15.0, -15.0, -15.0,0.0, -15.0, -15.0,
-14.5, -14.5, -14.5,0.0, -14.5, -14.5,
-14.0, -14.0, -14.0,0.0, -14.0, -14.0,
-13.5, -13.5, -13.5,0.0, -13.5, -13.5,
-13.0, -13.0, -13.0,0.0, -13.0, -13.0,
-12.5, -12.5, -12.5,0.0, -12.5, -12.5,
-12.0, -12.0, -12.0,0.0, -12.0, -12.0,
-11.5, -11.5, -11.5,0.0, -11.5, -11.5,
-11.0, -11.0, -11.0,0.0, -11.0, -11.0,
-10.5, -10.5, -10.5,0.0, -10.5, -10.5,
-10.0, -10.0, -10.0,0.0, -10.0, -10.0,
-9.5, -9.5, -9.5,0.0, -9.5, -9.5,
-9.0, -9.0, -9.0,0.0, -9.0, -9.0,
-8.5, -8.5, -8.5,0.0, -8.5, -8.5,
-7.5, -7.5, -7.5,0.0, -7.5, -7.5,
-7.5, -7.5, -7.5,0.0, -7.5, -7.5,
-7.0, -7.0, -7.0,0.0, -7.0, -7.0,
-6.5, -6.5, -6.5,0.0, -6.5, -6.5,
-6.0, -6.0, -6.0,0.0, -6.0, -6.0,
-5.5, -5.5, -5.5,0.0, -5.5, -5.5,
-5.0, -5.0, -5.0,0.0, -5.0, -5.0,
-4.5, -4.5, -4.5,0.0, -4.5, -4.5,
-4.0, -4.0, -4.0,0.0, -4.0, -4.0,
-3.5, -3.5, -3.5,0.0, -3.5, -3.5,
-3.0, -3.0, -3.0,0.0, -3.0, -3.0,
-2.5, -2.5, -2.5,0.0, -2.5, -2.5,
-2.0, -2.0, -2.0,0.0, -2.0, -2.0,
-1.5, -1.5, -1.5,0.0, -1.5, -1.5,
-1.0, -1.0, -1.0,0.0, -1.0, -1.0,
-0.5, -0.5, -0.5,0.0, -0.5, -0.5,
0.0, 0.0, 0.0, 0.0, -0.5, 0.0,
0.0, 0.0, 0.0, 0.0, -1.0, 0.0,
0.0, 0.0, 0.0, 0.0, -1.5, 0.0,
0.0, 0.0, 0.0, 0.0, -2.0, 0.0,
0.0, 0.0, 0.0, 0.0, -2.5, 0.0,
0.0, 0.0, 0.0, 0.0, -3.0, 0.0,
0.0, 0.0, 0.0, 0.0, -3.5, 0.0,
0.0, 0.0, 0.0, 0.0, -4.0, 0.0,
0.0, 0.0, 0.0, 0.0, -4.5, 0.0,
0.0, 0.0, 0.0, 0.0, -5.0, 0.0,
0.0, 0.0, 0.0, 0.0, -6.0, 0.0,
0.0, 0.0, 0.0, 0.0, -6.5, 0.0,
0.0, 0.0, 0.0, 0.0, -7.0, 0.0,
0.0, 0.0, 0.0, 0.0, -7.5, 0.0,
0.0, 0.0, 0.0, 0.0, -8.0, 0.0,
0.0, 0.0, 0.0, 0.0, -8.5, 0.0,
0.0, 0.0, 0.0, 0.0, -9.0, 0.0,
0.0, 0.0, 0.0, 0.0, -9.5, 0.0,
0.0, 0.0, 0.0, 0.0, -10.0,0.0,
0.0, 0.0, 0.0, 0.0, -11.0,0.0,
0.0, 0.0, 0.0, 0.0, -10.5,0.0,
0.0, 0.0, 0.0, 0.0, -10.0,0.0,
0.0, 0.0, 0.0, 0.0, -9.5, 0.0,
0.0, 0.0, 0.0, 0.0, -9.0, 0.0,
0.0, 0.0, 0.0, 0.0, -8.5, 0.0,
0.0, 0.0, 0.0, 0.0, -8.0, 0.0,
0.0, 0.0, 0.0, 0.0, -7.5, 0.0,
0.0, 0.0, 0.0, 0.0, -7.0, 0.0,
0.0, 0.0, 0.0, 0.0, -6.0, 0.0,
0.0, 0.0, 0.0, 0.0, -5.5, 0.0,
0.0, 0.0, 0.0, 0.0, -5.0, 0.0,
0.0, 0.0, 0.0, 0.0, -4.5, 0.0,
0.0, 0.0, 0.0, 0.0, -4.0, 0.0,
0.0, 0.0, 0.0, 0.0, -3.5, 0.0,
0.0, 0.0, 0.0, 0.0, -3.0, 0.0,
0.0, 0.0, 0.0, 0.0, -2.5, 0.0,
0.0, 0.0, 0.0, 0.0, -2.0, 0.0,
0.0, 0.0, 0.0, 0.0, -1.5, 0.0,
0.0, 0.0, 0.0, 0.0, -1.0, 0.0,
0.0, 0.0, 0.0, 0.0, -0.5, 0.0

	};
	for (int i = 0; i < 90; i++) {
		contador++;
		KeyFrame[playIndex].anganu = arr[contador];

		contador++;
		KeyFrame[playIndex].angmed = arr[contador];

		contador++;
		KeyFrame[playIndex].angme = arr[contador];

		contador++;
		KeyFrame[playIndex].angmu = arr[contador];

		contador++;
		KeyFrame[playIndex].angind = arr[contador];

		contador++;
		KeyFrame[playIndex].angpul = arr[contador];
		FrameIndex++;
	}

}

void InitGL(GLvoid)     // Inicializamos parametros
{

	//objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].anganu = 0;
		KeyFrame[i].angmed = 0;
		KeyFrame[i].angme  = 0;
		KeyFrame[i].angmu  = 0;
		KeyFrame[i].angpul = 0;
		KeyFrame[i].angind = 0;
	}

	archivo = fopen("archivo.txt", "w");
	salvarFrame_2();
}

void pintaTexto(float x, float y, float z, void *font, char *string)
{
	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void animacion()
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
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
			anganu += KeyFrame[playIndex].anganuInc; ////// Rodilla Derecha
			angmed += KeyFrame[playIndex].angmedInc; ////// Cabeza
			angme  += KeyFrame[playIndex].angmeInc; ////// Cuello
			angmu  += KeyFrame[playIndex].angmuInc; ////// Brazo Izquierdo
			angpul += KeyFrame[playIndex].angpulInc; ////// Brazo Derecho
			angind += KeyFrame[playIndex].angindInc; ////// Brazo Izquierdo 2

			i_curr_steps++;
		}

	}

	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':
	case 'W':
		transZ += 0.2f;
		break;

	case 's':
	case 'S':
		transZ -= 0.2f;
		break;

	case 'a':
	case 'A':
		transX += 0.2f;
		break;

	case 'd':
	case 'D':
		transX -= 0.2f;
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex > 1))
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
		printf("%f \n", posZ);
		break;

	case 'g':
	case 'G':
		posX--;
		printf("%f \n", posX);
		break;

	case 'h':
	case 'H':
		posZ--;
		printf("%f \n", posZ);
		break;

	case 'j':
	case 'J':
		posX++;
		printf("%f \n", posX);
		break;

	case 'v':
			angme -= 0.5f;
			anganu -= 0.5;
			angmed -= 0.5;
			angind -= 0.5;
			angpul -= 0.5;
		printf("ang menique: %f", angme);
		printf("ang anu %f", anganu);
		printf("ang med %f", angmed);
		printf("ang ind %f", angind);
		printf("ang pul %f", angpul);
		break;

	case 'b':
		angme += 0.5f;
		anganu += 0.5;
		angmed += 0.5;
		angind += 0.5;
		angpul += 0.5;
		printf("ang menique: %f", angme);
		printf("ang anu %f", anganu);
		printf("ang med %f", angmed);
		printf("ang ind %f", angind);
		printf("ang pul %f", angpul);
		break;

	case 'n':
		angpul -= 0.5;
		printf("ang menique: %f", angme);
		printf("ang anu %f", anganu);
		printf("ang med %f", angmed);
		printf("ang ind %f", angind);
		printf("ang pul %f", angpul);
		break;

	case 'm':
		angpul += 0.5;
		printf("ang menique: %f", angme);
		printf("ang anu %f", anganu);
		printf("ang med %f", angmed);
		printf("ang ind %f", angind);
		printf("ang pul %f", angpul);
		break;


	case 27:        // Cuando Esc es presionado...
		fclose(archivo);
		exit(0);   // Salimos del programa
		break;

	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)

{
	switch (a_keys) {

	case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		angleX += 2.0f;
		break;

	case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
		angleX -= 2.0f;
		break;

	case GLUT_KEY_LEFT:
		angleY += 2.0f;
		break;

	case GLUT_KEY_RIGHT:
		angleY -= 2.0f;
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
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
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

int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 11"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();          // 
	return 0;
}