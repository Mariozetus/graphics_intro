#include "render.h"
#include "event_manager.h"
#include "math_lib.h"

Render::Render()
{
    // inicializamos glfw0
	if(glfwInit() != GLFW_TRUE){ // si no es true, es que hay errores
		cout << "ERROR Starting GLFW" << endl;
		return;
	} 

#ifdef __APPLE__
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	int width = 640;
	int height = 480;

	this->window = glfwCreateWindow(width, height, "Intro PRGR", nullptr, nullptr);

	glfwMakeContextCurrent(window); // Creamos el contexto (contenedor) en base a nuestra ventana

	gladLoadGL(glfwGetProcAddress); // Usarla despues de iniciar GLFW

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Añadimos la propriedad de que no se pueda reescalar la ventana

	EventManager::initEventManager(window);

    this->exit = false;
}

void Render::setupObject(Object3D *obj)
{
    // Generar buffers
    bufferObject_t bufferObject  = { 0xFFFFFFFF, 0xFFFFFFFF, -0xFFFFFFFF };  // -1 en unsigned (se expresa asi) es infinito
    glGenVertexArrays(1, &bufferObject.bufferId); // Generar lista de buffers
    glGenBuffers(1, &bufferObject.vertexBufferId); // Genera un buffer de vertices
    glGenBuffers(1, &bufferObject.indexBufferId); // Genera un buffer de ids de vertices


    // Copiar datos
    glBindVertexArray(bufferObject.bufferId); // Activar lista de buffers
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject.vertexBufferId); // Activar buffer de vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW); // Copias los datos al buffer activo

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject.indexBufferId); // Activar buffer de indices de vertices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * obj->indexList.size(), obj->indexList.data(), GL_STATIC_DRAW);


    // Guardar identificadores
    bufferObjectList[obj->objectId] = bufferObject;

}

void Render::updateObjects(double timeStep)
{
    camera->moveObject(timeStep);

    for(auto& object : objectList){
        object->moveObject(timeStep);
    }
}

void Render::drawObjects()
{
    for(auto& object : objectList){
        
        // Settear buffers
        auto bufferObject = bufferObjectList[object->objectId]; // Recuperar lista buffers

        glBindVertexArray(bufferObject.bufferId); // Activar lista de buffers
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject.vertexBufferId); // Activar buffer de vertices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject.indexBufferId); // Activar buffer de indices de vertices
        
        // Settear matriz modelo
        Matrix4x4f model = object->computeModelMatrix();
        glPushMatrix(); // Crear una matriz en GPU
        glLoadIdentity(); // Cargar matriz identidad
        
        // Matriz modelo vista controlador
        auto mvp = mathLib::transpose(
            camera->computeProjectionMatrix(-0.001f, 1000.0f, 3.1416f/4.0f, 4.0f/3.0f)
            * camera->computeViewMatrix()
            * model
        );

        glMultMatrixf((float*) &mvp); // Traspuesta

        // Describir datos
        glEnableClientState(GL_VERTEX_ARRAY); // Vamos a uar array de posiciones
        // Describimos array de posiciones
        glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, position));

        // Dibujar
        glDrawElements(GL_TRIANGLES, object->indexList.size(), GL_UNSIGNED_INT, nullptr);


        glPopMatrix(); // Saca la matriz
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void Render::mainLoop()
{
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
		

		updateObjects(deltaTime);

		// Limpiar
		glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer
		
		// Dibujar
		drawObjects();

		// Intercambiar buffers
		glfwSwapBuffers(window); // (presenta lo dibujado)

		// Poll de eventos
		EventManager::updateEvents(); 
	}

	glfwTerminate(); // Ultima linea de OpenGL
}
