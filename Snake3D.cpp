// Snake3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "stdafx.h"
#include "glut.h"
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <io.h>
#include "ImageLoader.h"

// Valores para teclas
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Declaracion de Varibles a emplear
int longitudSnake = 0;
static float anguloCamara = 0;
int flag = 0;
// coordenas x y z
struct position
{
	float x;
	float y;
	float z;
};
typedef struct position position;
position cuerpoSnake[2000];
position p, p2, p3, p4, serpiente, velocidad, CoodEscenario;
position pxz, pxz1;
int ancho = 1300;
int alto = 1000;
int direction;
// valores para la comida
int lados = 10;
int anillo = 10;
double radioInterior = 0.3;
double radioExterior = 0.6;
//mensajes
char msgPuntuacion[100] = "Puntuacion:";
char msgGameOver[100] = "GAME OVER!  puntuacion:";
char msgModo3D[100] = "Para iniciar el juego pulse la tecla 'I'";
// Variables para movimiento flg y flg2 tendran 4 estados: 0,1,2 y 3
int flg = 0;
int flg2 = 0;
int flg3 = 0;
int flg4;
float f, g;
// vector que representa la direccion de la camara
float lx = 0.0f, lz = -1.0f;
// position XZ de la camara
float x = 0.0f, z = 5.0f;
int banderaNavegacion = 1;
int cc = 0;
char str[80];
char string[1000];
int cpt = 0;
int cambiarCamara = -1;
float longitud = 15.0f;// longitud del escenario
float X, Z, P;
int oprimido = 0;
int oprimido2 = 0;
int Xmax = 8;
float cx, cy, cz;
int r = 0;
float angulo;
GLuint _suelo;
GLuint _cielo;
GLuint _tabla;

// Metodo para la animacion del inicio del juego
void animacion()
{
	// rotacion de la escena antes de iniciar el juego
	float rayon = sqrt((CoodEscenario.x) * (CoodEscenario.x) + (CoodEscenario.z) * (CoodEscenario.z));
	if (r == 0)
	{
		CoodEscenario.x = rayon * sin(angulo);
		CoodEscenario.z = rayon * cos(angulo);
		angulo += 0.0002;//velocidad vualtas animacion
		if (angulo > 360)
			angulo = 0;
		//glutPostRedisplay();
	}
}

GLuint loadTexture(Image *image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE,
		image->pixels);
	return textureId;
}

void initRendering() {
	Image* suelo = loadBMP("suelo.bmp");
	Image* cielo = loadBMP("cielo.bmp");
	Image* tabla = loadBMP("tabla.bmp");
	_suelo = loadTexture(suelo);
	_cielo = loadTexture(cielo);
	_tabla = loadTexture(tabla);
	delete suelo;
	delete cielo;
	delete tabla;
}

void cargarTextura(GLuint _textura) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void dibujarCubo() {
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3f(1, -1, 1);
		glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, 1);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, 1);

		glTexCoord2f(1.0, 0.0); glVertex3f(-1, -1, -1);
		glTexCoord2f(1.0, 1.0); glVertex3f(-1, 1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3f(1, 1, -1);
		glTexCoord2f(0.0, 0.0); glVertex3f(1, -1, -1);

		glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, -1);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1, 1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3f(1, 1, 1);
		glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, -1);

		glTexCoord2f(1.0, 1.0); glVertex3f(-1, -1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3f(1, -1, -1);
		glTexCoord2f(0.0, 0.0); glVertex3f(1, -1, 1);
		glTexCoord2f(1.0, 0.0); glVertex3f(-1, -1, 1);

		glTexCoord2f(1.0, 0.0); glVertex3f(1, -1, -1);
		glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, -1);
		glTexCoord2f(0.0, 1.0); glVertex3f(1, 1, 1);
		glTexCoord2f(0.0, 0.0); glVertex3f(1, -1, 1);

		glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
		glTexCoord2f(1.0, 0.0); glVertex3f(-1, -1, 1);
		glTexCoord2f(1.0, 1.0); glVertex3f(-1, 1, 1);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, -1);
	glEnd();
}

// Metodo para la funcion de las teclas para rotacion del escenario
void teclasOprimidas(unsigned char teclaPresionada, int x, int y)
{
	switch (teclaPresionada)
	{
		// En caso de que sea la tecla Q saldremos
	case 'q':
		exit(0);
		break;
		// En caso de que la tecla oprimida sea la D
	case 'd':
		// Si direction es diferente de LEFT vamos hacia la RIGHT
		if (direction != LEFT && flg == 0)
		{
			direction = RIGHT;
			flg = 1;
			flg2 = 3;
		}
		// Si no, si direction es diferente de UP vamos hacia DOWN
		else if (direction != UP && flg == 1)
		{
			direction = DOWN;
			flg = 2;
			flg2 = 2;
		}
		// Si no, si direction es diferente de RIGHT vamos hacia la LEFT
		else if (direction != RIGHT && flg == 2)
		{
			direction = LEFT;
			flg = 3;
			flg2 = 1;
		}
		// Si no, si direction es diferente de DOWN vamos hacia UP
		else if (direction != DOWN && flg == 3)
		{
			direction = UP;
			flg = 0;
			flg2 = 0;
		}
		// Si la navegacion es igual a 1
		if (banderaNavegacion == 1)
		{
			direction = 0;
		}
		break;
		// En caso de que la tecla oprimida sea la A
	case 'a':
		// Si direction es diferente de RIGHT vamos hacia la LEFT
		if (direction != RIGHT && flg2 == 0)
		{
			flg2 = 1;
			flg = 3;
			direction = LEFT;
		}
		// Si no, si direction es diferente de UP vamos hacia DOWN
		else if (direction != UP && flg2 == 1)
		{
			flg2 = 2;
			flg = 2;
			direction = DOWN;
		}
		// Si no, si direction es diferente de LEFT vamos hacia la RIGHT
		else if (direction != LEFT && flg2 == 2)
		{
			flg2 = 3;
			flg = 1;
			direction = RIGHT;
		}
		// Si no, si direction es diferente de DOWN vamos hacia UP
		else if (direction != DOWN && flg2 == 3)
		{
			flg2 = 0;
			flg = 0;
			direction = UP;
		}
		// Si la navegacion es igual a 1
		if (banderaNavegacion == 1)
		{
			direction = 0;
		}
		break;
		// En caso de que la tecla oprimida sea la I iniciaremos el juego en modo 3D
	case 'i':
		cambiarCamara = 1;
		oprimido = 1;
		oprimido2 = 1;
		if (flg4 == -1)
		{
			direction = UP;
			flg4 = 1;
		}
		glutPostRedisplay();
		break;
	}
}

// Metodo para imprimir texto
void imprimir(int x, int y, int z, char *string)
{
	//posicion
	glRasterPos2f(x, y);
	//recuperamos el tama�o de la cadena
	int len = (int)strlen(string);
	//mostrar por caracteres
	for (int i = 0; i < len; i++)
	{
		//tipo de letra helvetica numero 18
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

//Metodo para reiniciar valores del juego
void reiniciarJuego()
{
	// reinicia cuerpo de la serpiente
	p.x = 1.0;
	p.y = 1.0;
	p.z = 1.0;
	p2.x = 2.0;
	p2.y = 2.0;
	p2.z = 2.0;
	// reinicia la comida de la serpiente
	p3.x = 2.0;
	p3.y = 1.0;
	p3.z = 2;
	p4.x = 3.0;
	p4.y = 2.0;
	p4.z = 3;
	int i = 0;
	longitudSnake = 0; //reiniciamos la longitud de la serpiente
	direction = 0; //reiniciamos la direccion 
	//reiniciamos las variables de la direccion
	flg = 0;
	flg2 = 0;
	flg3 = 0;
	flg4 = -1;
	oprimido = 0;
	//reiniciamos la velocidad
	velocidad.x = 0;
	velocidad.y = 0;
	velocidad.z = 1;
	serpiente.x = 1 / 2;
	serpiente.y = 1 / 2;
	serpiente.z = 1 / 2;
	cpt = 0;
}

// Metodo donde pintamos a la serpiente
void dibujarSnake()
{
	int i = 0;
	// dibujamos la cabeza de la serpiente al inicio
	glPushMatrix();
	glTranslatef(serpiente.x, 0.5, serpiente.z);
	glScalef(0.6, 0.6, 0.6);
	cargarTextura(_cielo);//textura serpiente
	dibujarCubo();// dibujar cubo de la cabeza tama�o 2
	glutSolidCube(2);
	glPopMatrix();

	for (i = 0; i < longitudSnake; i++)
	// cuerpo de la serpiente
	{
		glPushMatrix();
		glTranslatef(cuerpoSnake[i].x, 0.5, cuerpoSnake[i].z);
		glScalef(0.6, 0.6, 0.6);
		cargarTextura(_cielo);//textura serpiente
		dibujarCubo();// dibujar cubo de la cabeza tama�o 2
		glPopMatrix();
	}
}

// movimiento del cuerpo de la serpiente
void actualizarSnake(float AnteriorSnakeX, float AnteriorSnakeY, float AnteriorSnakeZ)
{	//coordenadas temporales cuerpo
	float temporalX = 0;
	float temporalY = 0;
	float temporalZ = 0;
	//coordenadas actuales cuerpo
	float ActualX = AnteriorSnakeX;
	float ActualY = AnteriorSnakeY;
	float ActualZ = AnteriorSnakeZ;

	for (int i = 0; i < longitudSnake; i++)
	{
		temporalX = cuerpoSnake[i].x;
		temporalY = cuerpoSnake[i].y;
		temporalZ = cuerpoSnake[i].z;

		cuerpoSnake[i].x = ActualX;
		cuerpoSnake[i].y = ActualY;
		cuerpoSnake[i].z = ActualZ;

		ActualX = temporalX;
		ActualY = temporalY;
		ActualZ = temporalZ;
	}
}

// Metodo para mover la serpiente de position
void moveSnakePos()
{
	// Verifica si la serpiente ha llegado a los bordes del escenario
	if (direction == RIGHT)
	{
		cc = 1;
		p.x += .01; // dificultad 1
		p2.x += .01;
		if (cpt >= 8)
		{ // dificultad 2
			p.x += .01;
			p2.x += .01;
		}
		if (cpt >= 15)
		{ // dificultad 3
			p.x += .01;
			p2.x += .01;
		}
		velocidad.x = 1;
		velocidad.y = 0;
		velocidad.z = 0;
		glutPostRedisplay();
	}
	else if (direction == LEFT)
	{
		cc = 1;
		p.x -= .01;
		p2.x -= .01;
		if (cpt >= 8)
		{
			p.x -= .01;
			p2.x -= .01;
		}
		if (cpt >= 15)
		{
			p.x -= .01;
			p2.x -= .01;
		}
		velocidad.x =-1;
		velocidad.y = 0;
		velocidad.z = 0;
		glutPostRedisplay();
	}
	else if (direction == UP)
	{
		cc = 0;
		p.z -= .02;
		p2.z -= .01;
		if (cpt >= 8)
		{
			p.z -= .01;
			p2.z -= .01;
		}
		if (cpt >= 15)
		{
			p.z -= .01;
			p2.z -= .01;
		}
		velocidad.x = 0;
		velocidad.y = 0;
		velocidad.z = -1;
		glutPostRedisplay();
	}
	else if (direction == DOWN)
	{
		cc = 0;
		p.z += .01;//velocidad de la serpiente aumenta en z
		p2.z += .01;
		if (cpt >= 8)
		{
			p.z += .01;
			p2.z += .01;
		}
		if (cpt >= 15)
		{
			p.z += .02;
			p2.z += .01;
		}
		velocidad.x = 0;
		velocidad.y = 0;
		velocidad.z = 1;
		glutPostRedisplay();
	}
}

void Escenario(float longitud)
{
	glPushMatrix();
	cargarTextura(_suelo);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  glVertex3f(longitud, 0, (longitud));
		glTexCoord2f(3.0f, 0.0f); glVertex3f(-longitud, 0, (longitud));
		glTexCoord2f(3.0f, 3.0f);  glVertex3f(-longitud, 0, -1 * (longitud));
		glTexCoord2f(0.0f, 3.0f);  glVertex3f(longitud, 0, -1 * (longitud));
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_tabla);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);  glVertex3f(longitud, -longitud, longitud);
		glTexCoord2f(3.0f, 0.0f);  glVertex3f(-longitud, -longitud, longitud);
		glTexCoord2f(3.0f, 3.0f);  glVertex3f(-longitud, 0, longitud);
		glTexCoord2f(0.0f, 3.0f);  glVertex3f(longitud, 0, longitud);

		glTexCoord2f(0.0f, 0.0f);  glVertex3f(-longitud, -longitud, -longitud);
		glTexCoord2f(3.0f, 0.0f);  glVertex3f(-longitud, -longitud, longitud);
		glTexCoord2f(3.0f, 3.0f);  glVertex3f(-longitud, 0, longitud);
		glTexCoord2f(0.0f, 3.0f);  glVertex3f(-longitud, 0, -longitud);

		glTexCoord2f(0.0f, 0.0f);  glVertex3f(longitud, -longitud, longitud);
		glTexCoord2f(3.0f, 0.0f);  glVertex3f(longitud, -longitud, -longitud);
		glTexCoord2f(3.0f, 3.0f);  glVertex3f(longitud, 0, -longitud);
		glTexCoord2f(0.0f, 3.0f);  glVertex3f(longitud, 0, longitud);

		glTexCoord2f(0.0f, 0.0f);  glVertex3f(-longitud, -longitud, -longitud);
		glTexCoord2f(3.0f, 0.0f);  glVertex3f(longitud, -longitud, -longitud);
		glTexCoord2f(3.0f, 3.0f);  glVertex3f(longitud, 0, -longitud);
		glTexCoord2f(0.0f, 3.0f);  glVertex3f(-longitud, 0, -longitud);
	glEnd();
	glPopMatrix();

	// colisiones de la serpiente
		//fabs para valor absoluto
	if ((fabs(serpiente.x - p3.x) <= 0.50 && fabs(serpiente.z - p3.z) <= 0.50) || (fabs(serpiente.x - p4.x) < 0.01 && fabs(serpiente.z - p4.z) < 0.01))
	{
		cpt++; //contador de puntaje
		if (cpt >= 5)
		{
			longitudSnake += 5;
		}
		else if (cpt >= 15)
		{
			longitudSnake += 2;
		}
		else
		{
			longitudSnake += 10;
		}
		//coordenadas random de la comida
		p3.x = (float)(rand() % (Xmax - (-1 * Xmax)) + (-1 * Xmax));
		p3.z = (float)(rand() % (Xmax - (-1 * Xmax)) + (-1 * Xmax));
		p4.x = p3.x + 1; // optimizar un poco las pruebas de choque
		p4.z = p3.z + 1;
	}
	// choque de la serpiente con el borde del area de juego
	else if (p.x <= -(longitud - 1) || p.z >= longitud || p2.x >= longitud || p2.z <= -(longitud - 1))
	{
		sprintf(str, "%d", cpt);
		strncpy(string, msgGameOver, 100);
		strcat(string, str);
		glPushMatrix();
		glColor3f(0, 0, 2.5);
		glTranslated(cx, cy + 4, cz);
		imprimir(0, 0, 0, string);
		glPopMatrix();
		reiniciarJuego();
	}
	else if (cpt >= 7)
	{ // choque de la serpiente con el cuerpo
		for (int i = 150; i <= longitudSnake; i++)
		{
			if (fabs(p.x - cuerpoSnake[i].x) <= 0.25 && fabs(p.z - cuerpoSnake[i].z) <= 0.25)
			{
				sprintf(str, "%d", cpt);
				strncpy(string, msgGameOver, 100);
				strcat(string, str);
				glPushMatrix();
				glColor3f(0, 0, 2.5);
				glTranslated(cx, cy + 3, cz);
				imprimir(0, 0, 0, string);
				glPopMatrix();
				reiniciarJuego();
			}
		}
	}
}

void mostrar()
{
	//proyeccion y perspectiva del escenario
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, (float)ancho / (float)alto, 1, 100);
	//posicion serpiente
	serpiente.x = (p2.x + p.x) / 2;
	serpiente.y = (p2.y + p.y) / 2;
	serpiente.z = (p2.z + p.z) / 2;
	if (cambiarCamara == 1)
	{ 	// 3D
		cx = serpiente.x;
		cy = serpiente.y;
		cz = serpiente.z;
	}
	if (banderaNavegacion == 1)
	{
		// Restablecer transformaciones
		// Definimos una transformaci�n de visualizaci�n.
		gluLookAt(x, 1.3f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

	}
	else if (banderaNavegacion == 0)
	{
		// Definimos una transformaci�n de visualizaci�n.
		gluLookAt(CoodEscenario.x, CoodEscenario.y, CoodEscenario.z, cx, cy, cz, 0, 1, 0);
	}

	glPushMatrix();
	Escenario(longitud);
	actualizarSnake(serpiente.x, serpiente.y, serpiente.z);
	moveSnakePos();
	glPopMatrix();
	glPushMatrix();
	glPopMatrix();
	dibujarSnake();//funcion para dibujar la serpiente
	glPushMatrix();

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.54f, 0.0f, 0.464706f);
	glTranslated(p3.x, 0.5, p3.z);
	glScalef(0.6, 0.6, 0.6);
	anguloCamara += 0.01;//velocidad aumenta
	glutSolidTorus(radioInterior, radioExterior, lados, anillo);//dibujamos la comida en forma de anillo
	glPopMatrix();

	if (oprimido == 1)
	{
		// imprimimos el mensaje de puntuacion
		glPushMatrix();
		glColor3f(1, 1, 1);
		sprintf(str, "%d", cpt);
		strncpy(string, msgPuntuacion, 100);
		strcat(string, str);
		//mensaje fijo
		if (cambiarCamara == 1)
		{
			glTranslated(0.0, 10.0, -9.0);
			imprimir(0, 3, 0, string);
		}
		glPopMatrix();
	}
	if (oprimido2 == 0 && banderaNavegacion == 0)
	{
		//imprimimos mensaje de iniciar juego 
		strncpy(string, msgModo3D, 100);
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(0.0, 7.5, 0.0);
		imprimir(-5, 2, 0, string);
		glPopMatrix();
	}
	glPushMatrix();
	glPopMatrix();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);//iniciamos glut
	glutInitWindowSize(ancho, alto);//iniciamos nuestra ventana
	//posicion inicial de la serpiente
	serpiente.x = 1 / 2;
	serpiente.y = 1 / 2;
	serpiente.z = 1 / 2;
	//velocidad de la serpiente
	velocidad.x = 0;
	velocidad.y = 0;
	velocidad.z = -1;
	flg4 = -1;
	//Posicion de la ventana
	glutInitWindowPosition(0,0);
	//modo de visualizaci�n inicial: valor predeterminado RGBA, GLUT_SINGLE: ventana almacenada en b�fer y GLUT_DEPTH: ventana con b�fer de profundidad.
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	//titulo de la ventana
	glutCreateWindow("Proyecto Final Graficacion Snake 3D");
	glutSetCursor(GLUT_CURSOR_NONE);
	initRendering();
	//visualizaci�n para la ventana actual
	glEnable(GL_DEPTH_TEST);
	//posicion inicial del escenario
	CoodEscenario.x = -15.0;
	CoodEscenario.y = 15.0;
	CoodEscenario.z = 30.0;
	//visualizar el escenario al inicio
	banderaNavegacion = 0;
	glutDisplayFunc(mostrar);
	//funcionalidad de teclas
	glutKeyboardFunc(teclasOprimidas);
	//Animacion inicial del escenario
	glutIdleFunc(animacion);
	glutMainLoop();
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
