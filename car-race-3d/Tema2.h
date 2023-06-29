#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         Tema2();
        ~Tema2();

        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        void Init() override;

        Mesh *CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        //void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderScene(float deltaTimeSeconds);
        bool CheckCircuit(float posx, float posz, std::vector<glm::vec3> circuitMiddle);
        bool CheckCars(float posx, float posz);
    protected:
       
        int angle;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        ViewportArea miniViewportArea;
        testcamera::Camera* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        float left;
        float right;
        float bottom;
        float top;
        float fov;
        float unit;
        float speed;
        float acceleration;

        float dtu;
        float dti;

        std::vector<glm::vec3> treePos;
        std::vector<glm::vec3> carTraj;
        std::vector<glm::vec3> circuitMiddle;

        int checkpoint[50];
        int checkpoint_R[50];
        float enemyX[50], enemyZ[50], enemyStepOY[50];
        float enemyX_R[50], enemyZ_R[50], enemyStepOY_R[50];
        int nr_enemies;
        int nr_enemies_R;

        std::vector<glm::vec3> carTraj_R;

        float dt;
    };
}   // namespace m1
