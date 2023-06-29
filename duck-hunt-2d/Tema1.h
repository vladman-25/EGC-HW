#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        float temptime;
        float sense;
        float start;
        float posx;
        float posy;
        float angle;
        float resx;
        float resy;
        float v;
        float vsense;
        float hsense;
        float turning;
        float ducksize;
        float duckL, duckH;
        float vx, vy;
        float angle90;
        float duckState;
        float totalTime;
        float xc;
        float multiplier;
        float mX, mY;
        glm::mat3 moves;
        float centerX, centerY;
        float nrLives;
        float bullets;
        float score;
        float totalTimeSun;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
