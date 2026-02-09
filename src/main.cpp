#define GLAD_BIN // Compila con glad (activador OpenGL), poner unicamente en el main

#include "mathLib.h"
#include "eventManager.h"
#include "Object3D.h"

using namespace std;
using namespace mathLib;

void drawObject(Object3D& obj);
void updateObject(Object3D& obj, double deltaTime);

int main(int argc, char** argv)
{	

	// inicializamos glfw0
	if(glfwInit() != GLFW_TRUE){ // si no es true, es que hay errores
		cout << "ERROR Starting GLFW" << endl;
		return 1;
	} 

#ifdef __APPLE__
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	int width = 640;
	int height = 480;
	GLFWwindow* window = glfwCreateWindow(width, height, "Intro PRGR", nullptr, nullptr);

	glfwMakeContextCurrent(window); // Creamos el contexto (contenedor) en base a nuestra ventana

	gladLoadGL(glfwGetProcAddress); // Usarla despues de iniciar GLFW

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Añadimos la propriedad de que no se pueda reescalar la ventana

	EventManager::initEventManager(window);

	bool exit = false;

	double lastTime = 0;
	double newTime = glfwGetTime();
	double deltaTime = newTime - lastTime;

	Object3D triangle;
	
	// Rendering loop
	while(!exit){
		
		// Calcular tiempo de render
		newTime = glfwGetTime();
		deltaTime = newTime - lastTime;
		lastTime = newTime;

		// Si pulsa ESC o pulsa el boton de cerrar (evento)
		if(EventManager::keymap[GLFW_KEY_ESCAPE] || glfwWindowShouldClose(window))
			exit = true;
		

		updateObject(triangle, deltaTime);

		// Limpiar
		glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer
		
		// Dibujar
		drawObject(triangle);

		// Intercambiar buffers
		glfwSwapBuffers(window); // (presenta lo dibujado)

		// Poll de eventos
		EventManager::updateEvents(); 
	}	

	glfwTerminate(); // Ultima linea de OpenGL
	
	vec4float v1 = { 1, 2, 3, 4 };
	vec4float v2 = { 5, 6, 7, 8 };

	auto vres = v1 + v2;

	// Es lo mismo, depende el contexto querremos usarlo de 1 manera u otra (e.g. bucles)
	cout << vres.x << " " << vres.y << " " << vres.z << " " << vres.w << endl;
	cout << vres.v[0] << " " << vres.v[1] << " " << vres.v[2] << " " << vres.v[3] << endl;
	cout << "Hola" << endl;

	
	return 0;
}

void drawObject(Object3D& obj){

	// Setear posiciones
	glBegin(GL_TRIANGLES); // Los agrupa de 3 en 3
	{
		// Tipo de malla 3D (triangulos)
		for(auto v: obj.vertexList){
			auto model = obj.computeModelMatrix(); // el modelo sirve para transformar (posicion, rotacion, escala)
			v.position = model * v.position;
			// Asignar posiciones
			glVertex3f(v.position.x, v.position.y, v.position.z);
		}
	}
	glEnd(); // Dibujar
}

void updateObject(Object3D& obj, double deltaTime){
	obj.moveObject(deltaTime);
}

