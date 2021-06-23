#pragma once

#include "Scene.h"
#include "Plane.h"
#include "Text.h"

class EscenaInicial : public Scene 
{
    public:
    EscenaInicial();
    void Init() override;
    void Update(float dt) override;
    void Draw(float dt) override;
    
    static Font font;

    private:
    
    Plane img;
};