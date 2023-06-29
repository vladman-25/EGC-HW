#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Models
{

    std::vector<VertexFormat> CreateCarVertices(float u, glm::vec3 color);
    std::vector<unsigned int> CreateCarIndices();

    std::vector<VertexFormat> CreateCircuitVertices(float u, glm::vec3 color);
    std::vector<unsigned int> CreateCircuitIndices(std::vector<VertexFormat> vertices);

    std::vector<VertexFormat> CreateTreeVertices(float u);
    std::vector<unsigned int> CreateTreeIndices();

    std::vector<glm::vec3> CreateTreePos(float u);
    std::vector<glm::vec3> CreateCarTraj(float u);
    std::vector<glm::vec3> CreateCarTraj_R(float u);
    std::vector<glm::vec3> CreateCircuitMiddle(float u);

    std::vector<VertexFormat> CreateGroundVertices(glm::vec3 color);
    std::vector<unsigned int> CreateGroundIndices();

    Mesh* CreateCar(const char* name, float u, glm::vec3 color);
    Mesh* CreateCircuit(const char* name, float u, glm::vec3 color);
    Mesh* CreateTree(const char* name, float u, glm::vec3 color);
    Mesh* CreateGround(const char* name, float u, glm::vec3 color);
    Mesh* CreateStrips(const char* name, float u, glm::vec3 color);
}

