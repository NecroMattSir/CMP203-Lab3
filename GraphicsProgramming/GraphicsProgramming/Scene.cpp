#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	// Initialise scene variables
	rot = 0;

	p1rot = 0;
	p2rot = 0;
	p3rot = 0;
	p2m1rot = 0;
	p2m1m1rot = 0;
	p3m1rot = 0;
	p3m2rot = 0;
}

void Scene::handleInput(float dt)
{
	// Handle user input
	if (input->isKeyDown('o'))
	{
		rot -= 15;
		input->setKeyUp('o');
	}

	if (input->isKeyDown('p'))
	{
		rot += 15;
		input->setKeyUp('p');
	}
}

void Scene::update(float dt)
{
	// update scene related variables.

	//a
	rot += 10 * dt;
	p1rot += 10 * dt;
	p2rot += 15 * dt;
	p3rot += 5 * dt;

	//quad
	roty += 10 * dt;
	rotx += 30 * dt;
	rotz += 5 * dt;

	//solarsystem
	p2m1rot -= 40 * dt;
	p2m1m1rot += 70 * dt;
	p3m1rot += 50 * dt;
	p3m2rot += 80 * dt;

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 1.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	
	// Render geometry/scene here -------------------------------------
	

	//light
	GLfloat AmbientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat DiffuseLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glEnable(GL_LIGHT0);


	GLfloat PointCoords2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat DiffuseLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT1, GL_POSITION, PointCoords2);
	glEnable(GL_LIGHT1);

	

	glBegin(GL_QUADS);
	for (float z = -10.0f; z < 10.f; z += 1.0f)
	{
		for (float x = -10.f; x < 10.f; x += 1.0f)
		{
			glVertex3f(x, 0, z);
			glVertex3f(x + 1.f, 0, z);
			glVertex3f(x + 1.f, 0, z + 1.f);
			glVertex3f(x, 0, z + 1.f);
		}
	}
	glEnd();

	//glPushMatrix();
	//glTranslatef(2, 1, -5);

	//glScalef(2, 0.5, 0);


	//glRotatef(rot, 0, 1, 0);


	////a (has a part in update)
	//glTranslatef(-2, 0, 0);
	//glRotatef(rot, 0, 0, -1);

	////b
	//glRotatef(rot, 0, 0, -1);
	//glTranslatef(1.5, 0, 0);
	//glRotatef(rot, 0, 0, 1);
	//glScalef(0.5, 0.5, 0);


	////triangle
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f);
	//glEnd();

	////trianglemidpoint
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.02f, 0.0f);
	//glVertex3f(-0.02f, -0.02f, 0.0f);
	//glVertex3f(0.02f, -0.02f, 0.0f);
	//glEnd();

	//quad
	glPushMatrix();
	glTranslatef(-3, 1, 0);
	glRotatef(roty, 50, 20, 5);
	DrawCube();
	glPopMatrix();

	//solarsystem

	{
		//sun
		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 1.0f, 0.0f);
		gluSphere(gluNewQuadric(), 0.25, 100, 100);
		glEnable(GL_LIGHTING);

		//p1
		glPushMatrix();
		glRotatef(p1rot, 0, 0, 1);
		glTranslatef(0.7, 0, 0);
		glColor3f(0.8f, 0.0f, 0.0f);
		gluSphere(gluNewQuadric(), 0.05, 100, 100);
		glPopMatrix();

		//p2
		glPushMatrix();
		{
			glRotatef(p2rot, 0, 0, 1);
			glTranslatef(1.4, 0, 0);
			glColor3f(0.0f, 0.5f, 0.0f);
			gluSphere(gluNewQuadric(), 0.05, 100, 100);
			//m1
			glPushMatrix();
			{
				glRotatef(p2m1rot, 0, 0, 1);
				glTranslatef(0.2, 0, 0);
				glColor3f(0.2f, 0.1f, 0.3f);
				gluSphere(gluNewQuadric(), 0.025, 100, 100);
				//m1m1
				glPushMatrix();
				{
					glRotatef(p2m1m1rot, 0, 0, 1);
					glTranslatef(0.1, 0, 0);
					glColor3f(0.2f, 0.6f, 0.3f);
					gluSphere(gluNewQuadric(), 0.015, 100, 100);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//p3
		glPushMatrix();
		{
			glRotatef(p3rot, 0, 0, 1);
			glTranslatef(2.1, 0, 0);
			glColor3f(0.0f, 0.5f, 0.8f);
			gluSphere(gluNewQuadric(), 0.05, 100, 100);
			//m1
			glPushMatrix();
			{
				glRotatef(p3m1rot, 0, 0, 1);
				glTranslatef(0.2, 0, 0);
				glColor3f(0.8f, 0.1f, 0.6f);
				gluSphere(gluNewQuadric(), 0.025, 100, 100);
			}
			glPopMatrix();
			//m2
			glPushMatrix();
			{
				glRotatef(p3m2rot, 1, 0, 0);
				glTranslatef(0, 0, 0.2);
				glColor3f(0.3f, 0.8f, 0.6f);
				gluSphere(gluNewQuadric(), 0.025, 100, 100);
			}
			glPopMatrix();
		}
		glPopMatrix();

	}


	

	////midpoint
	//glPopMatrix();
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.02f, 0.0f);
	//glVertex3f(-0.02f, -0.02f, 0.0f);
	//glVertex3f(0.02f, -0.02f, 0.0f);
	//glEnd();



	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}


void Scene::DrawCube()
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.5f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);


		glColor3f(0.5f, 0.0f, 0.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);


		glColor3f(0.5f, 0.0f, 0.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(0.5f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f,- 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.5f, 0.0f, 0.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glColor3f(0.5f, 0.0f, 0.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();
}
