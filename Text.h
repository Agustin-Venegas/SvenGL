#pragma once

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <vector>

//toda la información de una letra de FreeType
class Character 
{
    public:
    Character();
    Character(unsigned int t, glm::ivec2 s, glm::ivec2 b, unsigned int a);
    unsigned int Texture;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};


class Font 
{
    public:
    Font();
    std::map<char, Character> Characters;

    //texto 2D sobre la pantalla
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};


//clase para cargar fuentes
class Text 
{
    public:
    static unsigned int Shader, VAO, VBO; //Se usan con un shader pa escribir texto 2d en la pantalla
    static void Init(); //Inicializar Shader, VAO Y VBO
    static Font LoadFont(const char * filename);
    static Font LoadFont(FT_Library ft_inst, const char * filename);
    static void LoadFonts(std::vector<std::string> filenames);
    static void Dispose(); //eliminar al final del programa
};
