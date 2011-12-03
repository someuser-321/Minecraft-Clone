#include <GL/glfw.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


#define WINDOW_X 800
#define WINDOW_Y 600


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


int window_x = WINDOW_X, window_y = WINDOW_Y;

char title[256] = "Heightmap test";

int chunk[8][8][8] = \
{
	{{1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,1}},
	{{1,2}, {2,2}, {3,2}, {4,2}, {5,2}, {6,2}, {7,2}, {8,2}},
	{{1,3}, {2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}, {8,3}},
	{{1,4}, {2,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4}, {8,4}},
	{{1,5}, {2,5}, {3,5}, {4,5}, {5,5}, {6,5}, {7,5}, {8,5}},
	{{1,6}, {2,6}, {3,6}, {4,6}, {5,6}, {6,6}, {7,6}, {8,6}},
	{{1,7}, {2,7}, {3,7}, {4,7}, {5,7}, {6,7}, {7,7}, {8,7}},
	{{1,8}, {2,8}, {3,8}, {4,8}, {5,8}, {6,8}, {7,8}, {8,8}},
};

float rcolor[8] = {1.0f, 0.875f, 0.75f, 0.625f, 0.5f, 0.375f, 0.25f, 0.125f};
float gcolor[8] = {1.0f, 0.875f, 0.75f, 0.625f, 0.5f, 0.375f, 0.25f, 0.125f};
float bcolor[8] = {1.0f, 0.875f, 0.75f, 0.625f, 0.5f, 0.375f, 0.25f, 0.125f};

int heightmap_x = 8;
int heightmap_z = 8;
					  
int quit = 0;
double tv0, tv1, tv2, tv3;
int frames, frames2 = 0;
double fps, fps2;

int i = 0;
int j = 0;

float roty = 0.0f;
float rotx = 0.0f;
float posx = 0.0f;
float posy = 0.0f;
float posz = 0.0f;


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


void rendersetup();
void setup();
void step();
void render();
void getinput();

void drawcube(int x, int y, int z);

void resize(int x, int y);

void getFPS();


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


int main(void){

	if ( !glfwInit() ){
		exit(EXIT_FAILURE);
	}

	if ( !glfwOpenWindow(window_x, window_y, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) ){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	
	glfwSetWindowSizeCallback(&resize);
	glfwSetWindowTitle(title);
	
	
	rendersetup();
	setup();


	while (!quit){

		getFPS();
		step();
		getinput();
		render();
			
		quit = glfwGetKey(GLFW_KEY_ESC) || (!glfwGetWindowParam(GLFW_OPENED));
		
		sprintf(title, "Heightmap test - %.1f FPS - %.1f FPS", (float)fps, (float)fps2);
		glfwSetWindowTitle(title);

	}


	glfwTerminate();
	exit(EXIT_SUCCESS);

}


///////////////////////////////////////////////////////////


void rendersetup(){
	
	glfwSwapInterval(0);
	
	glViewport(0, 0, window_x, window_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(/*-1.0f*/-0.01f, /*1.0f*/0.01f, /*-1.0f*/-0.01f, /*1.0f*/0.01f, /*1.0f*/0.01f, 64.0f);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);

}


///////////////////////////////////////////////////////////


void setup(){
	
	tv0 = glfwGetTime();

}


///////////////////////////////////////////////////////////


void step(){

	frames++;
	frames2++;
	
}


///////////////////////////////////////////////////////////


void getinput(){
	
	if ( glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS ){
		roty -= 1.0f;
		printf("%f\n", roty);
	}
	if ( glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS ){
		roty += 1.0f;
		printf("%f\n", roty);
	}
	if ( glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS && rotx > -89.2f){
		rotx -= 1.0f;
		printf("%f\n", rotx);
	}
	if ( glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS && rotx < 89.2f){
		rotx += 1.0f;
		printf("%f\n", rotx);
	}
	
	if ( glfwGetKey('W') == GLFW_PRESS ){
		posx += sin(roty/57.2957795f)*-0.05f;
		posz -= cos(roty/57.2957795f)*-0.05f;
		posy -= sin(rotx/57.2957795f)*-0.05f;
		printf("W\n");
	}
	if ( glfwGetKey('A') == GLFW_PRESS ){
		posx += cos(roty/57.2957795f)*0.05f;
		posz += sin(roty/57.2957795f)*0.05f;
		printf("A\n");
	}
	if ( glfwGetKey('S')== GLFW_PRESS ){
		posx -= sin(roty/57.2957795f)*-0.05f;
		posz += cos(roty/57.2957795f)*-0.05f;
		posy += sin(rotx/57.2957795f)*-0.05f;
		printf("S\n");
	}
	if ( glfwGetKey('D') == GLFW_PRESS ){
		posx -= cos(roty/57.2957795f)*0.05f;
		posz -= sin(roty/57.2957795f)*0.05f;
		printf("D\n");
	}
	if ( glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS )
		posy -= 0.05f;
	if ( glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS )
		posy += 0.05f;

}


///////////////////////////////////////////////////////////


void render(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();

	glPushMatrix();

	glRotatef(rotx, 1.0f, 0.0f, 0.0f);
	glRotatef(roty, 0.0f, 1.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, -8.0f);

	glTranslatef(posx, posy, posz);


	glPointSize(1.0f);

		for ( i=0 ; i<heightmap_x ; i++ ){
			for ( j=0 ; j<heightmap_z ; j++ ){
				glColor3f(rcolor[heightmap[i][j][1]-1], gcolor[heightmap[i][j][1]-1], bcolor[heightmap[i][j][1]-1]);
				drawcube(i, j, heightmap[i][j][0]);
			}
		}

	glBegin(GL_LINES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	glPopMatrix();

	glfwSwapBuffers();

}


///////////////////////////////////////////////////////////


void getFPS(){
	
	if ( frames > 100 ){
		tv1 = glfwGetTime();
		fps = frames / (tv1 - tv0);
		frames = 0;
		tv0 = glfwGetTime();
	}
	
	if ( frames2 > 500 ){
		tv3 = glfwGetTime();
		fps2 = frames2 / (tv3 - tv2);
		frames2 = 0;
		tv2 = glfwGetTime();
	}



}


///////////////////////////////////////////////////////////


void resize(int x, int y){

	window_x = x;
	window_y = y;
	
	glViewport(0, 0, window_x, window_y);

	glfwSetWindowSize(window_x, window_y);

}


///////////////////////////////////////////////////////////


void drawcube(int x, int y, int z){
	
	glBegin(GL_QUADS);

		glVertex3f(x+0.5f, y+0.5f, z-0.5f);
		glVertex3f(x-0.5f, y+0.5f, z-0.5f);
		glVertex3f(x-0.5f, y+0.5f, z+0.5f);
		glVertex3f(x+0.5f, y+0.5f, z+0.5f);

		glVertex3f(x+0.5f, y-0.5f, z+0.5f);
		glVertex3f(x-0.5f, y-0.5f, z+0.5f);
		glVertex3f(x-0.5f, y-0.5f, z-0.5f);
		glVertex3f(x+0.5f, y-0.5f, z-0.5f);

		glVertex3f(x+0.5f, y+0.5f, z+0.5f);
		glVertex3f(x-0.5f, y+0.5f, z+0.5f);
		glVertex3f(x-0.5f, y-0.5f, z+0.5f);
		glVertex3f(x+0.5f, y-0.5f, z+0.5f);

		glVertex3f(x+0.5f, y-0.5f, z-0.5f);
		glVertex3f(x-0.5f, y-0.5f, z-0.5f);
		glVertex3f(x-0.5f, y+0.5f, z-0.5f);
		glVertex3f(x+0.5f, y+0.5f, z-0.5f);
		
  		glVertex3f(x-0.5f, y+0.5f, z+0.5f);
		glVertex3f(x-0.5f, y+0.5f, z-0.5f);
		glVertex3f(x-0.5f, y-0.5f, z-0.5f);
		glVertex3f(x-0.5f, y-0.5f, z+0.5f);

		glVertex3f(x+0.5f, y+0.5f, z-0.5f);
		glVertex3f(x+0.5f, y+0.5f, z+0.5f);
		glVertex3f(x+0.5f, y-0.5f, z+0.5f);
		glVertex3f(x+0.5f, y-0.5f, z-0.5f);
	
	glEnd();

}


///////////////////////////////////////////////////////////
