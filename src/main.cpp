#include "mathLib.h"
#include "Render.h"

using namespace mathLib;

int main(int argc, char** argv){
	Render render(11, 11);
	vec4float punto = { 3, 3, 0, 1 };

	render.PutPixel(punto.x, punto.y);
	render.Draw();
	
	punto = makeTranslate(-6, 0, 0) * punto;
	render.resetBuffer();
	render.PutPixel(punto.x, punto.y);
	render.Draw();

	punto = makeRotate(0, 0, 45) * punto;
	render.resetBuffer();
	render.PutPixel(punto.x, punto.y);
	render.Draw();
}