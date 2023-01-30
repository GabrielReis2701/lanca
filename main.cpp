#include "glut.h"
#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>
#include "tgaload.h"
/* Definições da câmera */
#define y_min 60
#define ro_min 120
#define MAX_NO_TEXTURES 6
#define CUBE_TEXTURE 0


GLUquadric* cylinder = gluNewQuadric();

GLUquadric* sphere = gluNewQuadric();

GLuint texture_id[MAX_NO_TEXTURES];


float eyex = 0, eyey = y_min, eyez = ro_min;
float angle = 0, anglex = 0,anglez = 0,angleMX=-60,angleMY= 0,angleMZ=0;
int aux=0;

void initTexture (void)
{
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	image_t temp_image0;
	tgaLoad  ( "ponta_lanca.tga", &temp_image0, TGA_FREE | TGA_LOW_QUALITY );
	
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	image_t temp_image1;
	tgaLoad  ( "lado_esq.tga", &temp_image1, TGA_FREE | TGA_LOW_QUALITY );
}
void make_tex(void){
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
		for (int x = 0; x < 255; x++) {
	    unsigned char *p = data[y][x];
	    p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
		}
	}
   
    glGenTextures (5, texture_id);
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
}
void drawPonta(){
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	glBegin(GL_POLYGON);
	    glTexCoord2f(0.0, 0.0);	glVertex3f(0,0,3); //Ponto A
		glTexCoord2f(1.0, 0.0);	glVertex3f(-1,0,0); //Ponto B
		glTexCoord2f(1.0, 1.0);	glVertex3f(0,0,-1); //Ponto C
		glTexCoord2f(0.0, 1.0);	glVertex3f(1,0,0); //Ponto D
		glEnd();
		glBegin(GL_POLYGON);
			//Parte de Baixo
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,3); //Ponto A
			glTexCoord2f(1.0, 0.0);glVertex3f(0,-1,0); //Ponto E
			glTexCoord2f(1.0, 1.0);glVertex3f(0,0,-1); //Ponto C
		 	glTexCoord2f(0.0, 1.0);glVertex3f(-1,0,0); //Ponto B
	    glEnd();
	    glBegin(GL_POLYGON);
			//Parte de Baixo
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,3); //Ponto A
			glTexCoord2f(1.0, 0.0);glVertex3f(-1,0,0); //Ponto B
			glTexCoord2f(1.0, 1.0);glVertex3f(0,0,-1); //Ponto C
			glTexCoord2f(0.0, 1.0);glVertex3f(0,1,0); //Ponto F
	    glEnd();
	    glBegin(GL_POLYGON);
			//Parte de Baixo
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,3); //Ponto A
			glTexCoord2f(1.0, 0.0);glVertex3f(0,1,0); //Ponto F
			glTexCoord2f(1.0, 1.0);glVertex3f(0,0,-1); //Ponto C
			glTexCoord2f(0.0, 1.0);glVertex3f(1,0,0); //Ponto D
	    glEnd();
	    glBegin(GL_POLYGON);
			//Parte de Baixo
			glTexCoord2f(0.0, 0.0);glVertex3f(0,0,3); //Ponto A
			glTexCoord2f(1.0, 0.0);glVertex3f(1,0,0); //Ponto D
			glTexCoord2f(1.0, 1.0);glVertex3f(0,0,-1); //Ponto C
			glTexCoord2f(0.0, 1.0);glVertex3f(0,-1,0); //Ponto E
	    glEnd();
	    
	    glDisable(GL_TEXTURE_2D); 
}
void drawCabo(){
	color(0.79,0.83,0.79);
	glEnable(GL_TEXTURE_2D);
	
//	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
//	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
	gluQuadricDrawStyle(cylinder, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    //color(0.4434,0.4434,0.4353);
    gluQuadricTexture(cylinder, GL_TRUE);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder,0.4,0.4,6,64,64);
	//gluDisk(sphere, 0.0, 1.5, 64, 1);
	
	glDisable(GL_TEXTURE_2D); 		
	//gluCylinder
	
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* Limpa o Buffer de Pixels */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Estabelece a cor da primitiva como preta */
    
    /* Define a posição do observador */
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
    glRotatef(angle, 0,1,0);
	glRotatef(anglex, 1,0,0);
	glRotatef(anglez, 0,0,1);
    glPushMatrix();
    glScalef(10,10,10);
		glPushMatrix();
	    drawPonta();
	    glPopMatrix();
	    glTranslatef(0,0,-1);
	    glPushMatrix();
			color(1,0,0);
	    	glRotatef(90,1,0,0);
	    	drawRings(0.4,0.1);
	    glPopMatrix();
	    glTranslatef(0,0,-11.6);
	    glScalef(1,1,2);
	    glPushMatrix();
	    	drawCabo();
	    glPopMatrix();
	glPopMatrix();
	//Executa os comandos OpenGL 
	glFlush();
}

void TimerFunc(int value) {
	angle += 1; 
    glutPostRedisplay();
    glutTimerFunc( 33, TimerFunc, 1);
}

void reshape(int width, int height) {
	glViewport(0,0,width,height); // Reset The Current Viewport
	
	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix
	
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(float)640/(float)480,0.1f,1000.0f);
	// Always keeps the same aspect as a 640 wide and 480 high window
	
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity(); // Reset The Modelview Matrix
}

void key(unsigned char key, int x, int y) {
	switch(key) {
		case 27:
			exit(0);
			break;
		case 'y': /* e key rotates at elbow */
	 	 aux = (int) (angle + 5);
		 angle = aux % 360;
		 glutPostRedisplay();
		 break;
		case 'Y': /* e key rotates at elbow */
	 	 aux = (int) (angle - 5);
		 angle = aux % 360;
		 glutPostRedisplay();
		 break;
		 
		case 'x': /* e key rotates at elbow */
	 	 aux = (int) (anglex + 5);
		 anglex = aux % 360;
		 glutPostRedisplay();
		 break;
		case 'X': /* e key rotates at elbow */
	 	 aux = (int) (anglex - 5);
		 anglex = aux % 360;
		 glutPostRedisplay();
		 break;
		 
		case 'z': /* e key rotates at elbow */
	 	 aux = (int) (anglez + 5);
		 anglez = aux % 360;
		 glutPostRedisplay();
		 break;
		case 'Z': /* e key rotates at elbow */
	 	 aux = (int) (anglez - 5);
		 anglez = aux % 360;
		 glutPostRedisplay();
		 break;
			
	}
}

void init() {
	glClearColor(1,1,1,0);
	glClearDepth(1.0); // Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS); // The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	make_tex();
    initTexture ();
    //glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH); // Enables Smooth Color Shading
}

/*
Funcao principal do programa.
*/
int main(int argc, char** argv)
{
	//Inicia a Telinha
	glutInit(&argc,argv);
	
    /*
    Estabelece o modo de exibicao a ser utilizado pela janela a ser
    neste caso utiliza-se de um buffer duplo, ou seja, a apresentacao
    execucao
    Define o modo de cores como RGBA
    */
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    
    /*
    Determina o tamanho em pixels da
    janela a ser criada
    */
    glutInitWindowSize (450, 450);
    
    /*
    Estabelece a posicao inicial para criacao da
    janela
    */
    glutInitWindowPosition (100, 100);
    
    /*
    Cria uma janela com base nos parametros especificados
    nas funcoes glutInitWindowSize e glutInitWindowPosition
    com o nome de titulo especificado em seu argumento
    */
    glutCreateWindow ("Projeto Base");
    
    /*
    Especifica os parametros inicias para as variaveis
    de estado do OpenGL
    */
    init ();
    //TimerFunc(angle);
    // Associa a funcao display como uma funcao de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    
    /*
    Inicia a execucao do programa OpenGL.
    O programa ira executar num loop infinito devendo
    o desenvolvedor especificar as condicoes de saida do mesmo
    atraves de interrupcoes no proprio programa ou atraves
    de comandos de mouse ou teclado como funcoes de callback
    */
    glutMainLoop();
    return 0;
}
