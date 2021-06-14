#pragma once

//Ya no es una clase abstracta :c
class Scene
{
    public:
    virtual void Init();
    virtual void Update(float dt);
    virtual void Draw(float dt);
};