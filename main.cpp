#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std; //the

int main()
{    



//variables de ventana
glfwWindowHint(GLFW_SAMPLES, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //panes
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window;
window = glfwCreateWindow( 1024, 768, "La Ventana", NULL, NULL);
if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    glfwTerminate();
    return -1;
}

glfwMakeContextCurrent(window);

glewExperimental = true; // Needed for core profile
if( !glfwInit() )
{
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
}


glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    //Borrar la ventana con el color
    glClear( GL_COLOR_BUFFER_BIT );

    // Aqui va todo lo que se dibuja

    // Cambiar buffers (imagen de antes/imagen de ahora)
    glfwSwapBuffers(window);
    glfwPollEvents();

} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
       glfwWindowShouldClose(window) == 0 );

    
    cout << "Hello World!" << endl;
    return 0;
}