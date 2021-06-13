#pragma once

//clase abstracta para cosas dibujables
class Drawable 
{
    protected:
    unsigned int Shader;
    unsigned int VAO;

    virtual void Init() =0;//metodo puro virtual
    virtual void Update(float dt) =0;
    virtual void Draw() =0;
};