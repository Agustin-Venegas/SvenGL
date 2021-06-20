#include <ft2build.h>
#include FT_FREETYPE_H

#include "Text.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Utils.h"

unsigned int Text::Shader = 0;
unsigned int Text::VAO = 0;
unsigned int Text::VBO = 0;

void Text::Init() 
{
    //Crear Shader
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    Utils::CompileShader(vs, Utils::ReadFile("TextVertex.shader"));

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    Utils::CompileShader(fs, Utils::ReadFile("TextFragment.shader"));

    Text::Shader = glCreateProgram();
    glAttachShader(Text::Shader, vs);
    glAttachShader(Text::Shader, fs);
    glLinkProgram(Text::Shader);
    Utils::CheckProgramCompile(Text::Shader);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glGenVertexArrays(1, &Text::VAO);
    glGenBuffers(1, &Text::VBO);
    glBindVertexArray(Text::VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Text::VBO);

    //son dos triangulos sin info
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    //solo un atributo
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
    //deseleccionar estos arrays y buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Font Text::LoadFont(const char * filename)
{   

    FT_Library ft;

    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: No se pudo iniciar FreeType" << std::endl;
    }

    FT_Face face;

    if (FT_New_Face(ft, filename, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: No se pudo cargar fuente " << filename << std::endl;  
    }

    //setear tamaño y desactivar restriccion de tamaño de bit
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font font;

    //Cargar set ASCII
    for (unsigned char c = 0; c < 128; c++)
    {
        //Activar un caracter en la Face
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Fallo al cargar glifo" << std::endl;
            continue;
        }
        
        //generar textura
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D, //tipo de textura
            0,
            GL_RED, //un solo "color"
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer //donde esta almacenada la info
        );
        
        //informacion de la textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        //guardar informacion de caracter
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        font.Characters.insert(std::pair<char, Character>(c, character));
    }

    //desactivar textura
    glBindTexture(GL_TEXTURE_2D, 0);   

    //borrar cara cargada
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return font;
}

Font Text::LoadFont(FT_Library ft_inst, const char * filename)
{   
    FT_Face face;

    if (FT_New_Face(ft_inst, filename, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: No se pudo cargar fuente " << filename << std::endl;  
    }

    //setear tamaño y desactivar restriccion de tamaño de bit
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font font;

    //Cargar set ASCII
    for (unsigned char c = 0; c < 128; c++)
    {
        //Activar un caracter en la Face
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Fallo al cargar glifo" << std::endl;
            continue;
        }
        
        //generar textura
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D, //tipo de textura
            0,
            GL_RED, //un solo "color"
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer //donde esta almacenada la info
        );
        
        //informacion de la textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        //guardar informacion de caracter
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        font.Characters.insert(std::pair<char, Character>(c, character));
    }

    //desactivar textura
    glBindTexture(GL_TEXTURE_2D, 0);   

    //borrar cara cargada
    FT_Done_Face(face);

    return font;
}

void Text::LoadFonts(std::vector<std::string> filenames) 
{
    FT_Library ft;

    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: No se pudo iniciar FreeType" << std::endl;
    }

    
    for (std::string f:filenames) 
    {
        const char * c = f.c_str();

        Text::LoadFont(c);

        //ESTA WEA LEAKEA MEMORIA
        delete c;
    }

    FT_Done_FreeType(ft);
}

Font::Font() 
{
    Characters = std::map<char, Character>();
}

//Obviamente segui un tutorial
void Font::RenderText(std::string text, float x, float y, float scale, glm::vec3 color) 
{
    //configuracion de openGL
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //cargar el shader
    glUseProgram(Text::Shader);

    glUniform3f(glGetUniformLocation(Text::Shader, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(Text::VAO);

    //Iterar todos los caracteres
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        
        //Se cambiara la sub-info del VBO, para cada letra
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };

        //Renderizar la textura de la letra en el rectangulo del VBO
        glBindTexture(GL_TEXTURE_2D, ch.Texture);

        ////actualizar la info
        glBindBuffer(GL_ARRAY_BUFFER, Text::VBO);
        //se usa SubData para editar el contenido de un VBO
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        //ahora si renderizar
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //Avanzar la posicion segun el ancho de la letra
        x += (ch.Advance >> 6) * scale; //2^6 = 64
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}