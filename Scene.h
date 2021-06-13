#pragma once

//tambien es una clase abstracta
class Scene
{
    public:
    virtual void Init() =0;
    virtual void Update(float dt) =0;
    virtual void Draw(float dt) =0;
};