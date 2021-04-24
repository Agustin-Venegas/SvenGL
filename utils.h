#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Utils
{
    static bool CheckShaderCompile(GLuint shader);
    static bool CheckProgramCompile(GLuint program);
    static string ReadFile(string filename);
};