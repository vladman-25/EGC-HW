#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
     public:
         Tema3();
        ~Tema3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D *texture1 = NULL, Texture2D *texture2 = NULL, int Earth = 0, const glm::vec3& color = glm::vec3(1));
        Texture2D *CreateRandomTexture(unsigned int width, unsigned int height);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        std::unordered_map<std::string, Texture2D *> mapTextures;
        std::vector<glm::vec2> textureCoords;

        std::vector<glm::vec2> treeCords;

        std::vector<glm::vec2> presentCords;

        std::vector<glm::vec2> poleCords;

        std::vector<glm::vec2> stoneCords;

        glm::vec3 playerPos;

        int spotlight[200];

        float text_x;
        float text_y;
        float unit;
        float time,time_y;
        float mX, mY, resy, resx;
        float angle;
        int score;

        bool run;

        glm::vec3 lightPosition[200];
        glm::vec3 lightColor[200];
        int nr_lights;
        glm::vec3 lightDirection;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
    };
}   // namespace m1
