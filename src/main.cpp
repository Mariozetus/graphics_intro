
#define GLAD_BIN // Compila con glad (activador OpenGL), poner unicamente en el main

#include "math_lib.h"
#include "event_manager.h"
#include "object_3d.h"
#include "render.h"

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