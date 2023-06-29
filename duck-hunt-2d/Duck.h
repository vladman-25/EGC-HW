#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Duck
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateBody(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color1, glm::vec3 color2, bool fill = false);
    Mesh* CreateHead(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateBeak(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateLWing(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color1, glm::vec3 color2, bool fill = false);
    Mesh* CreateRWing(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color1, glm::vec3 color2, bool fill = false);
    Mesh* CreateHeart(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateBullet(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCursor(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateGun(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateFrontGrass(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color1, glm::vec3 color2, bool fill = false);
    Mesh* CreateBehindGrass(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateSunRay(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateMoonRay(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
}

