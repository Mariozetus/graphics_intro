
#define GLAD_BIN // Compila con glad (activador OpenGL), poner unicamente en el main

#include "mathLib.h"
#include "eventManager.h"
#include "Object3D.h"
#include "Render.h"

using namespace std;
using namespace mathLib;


int main(int argc, char** argv)
{	
	// Inicializar GLFW
	auto render = new Render(); // Crear ventana
	/**/
	auto object = new Object3D();

	render->setupObject(object);
	render->objectList.push_back(object);
	render->mainLoop();
	return 0;
}