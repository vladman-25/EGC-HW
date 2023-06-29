#include "Duck.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* Duck::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* Duck::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length/2, length * 1.73/2, 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

    triangle->SetDrawMode(GL_TRIANGLES);
    triangle->InitFromData(vertices, indices);

    return triangle;
}
Mesh* Duck::CreateBody(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color1), //0
        VertexFormat(corner + glm::vec3(3, 2, 0), color1), //1
        VertexFormat(corner + glm::vec3(8, 1, 0), color1), //2
        VertexFormat(corner + glm::vec3(5, 4, 0), color1), //3
        VertexFormat(corner + glm::vec3(7, 5, 0), color1), //4
        VertexFormat(corner + glm::vec3(12, 8, 0), color1), //5
        VertexFormat(corner + glm::vec3(16, 4, 0), color1), //6
        VertexFormat(corner + glm::vec3(18, 8, 0), color1), //7
        VertexFormat(corner + glm::vec3(19, 6, 0), color1), //8

        VertexFormat(corner, color2), //9
        VertexFormat(corner + glm::vec3(14, 6, 0), color2), //10
        VertexFormat(corner + glm::vec3(8, 1, 0), color2), //11
        VertexFormat(corner + glm::vec3(16, 4, 0), color2), //12
        VertexFormat(corner + glm::vec3(19, 6, 0), color2), //13
    };

    Mesh* body = new Mesh(name);
    std::vector<unsigned int> indices = { 
        9,10,11,
        11,10,12,
        10,13,12,
        0, 1, 2,
        1, 3, 2,
        3, 4, 2,
        2, 4, 6,
        4, 5, 6,
        5, 7, 6,
        6, 7, 8,
    };

    body->SetDrawMode(GL_TRIANGLES);
    body->InitFromData(vertices, indices);

    return body;
}
Mesh* Duck::CreateHead(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(18, 8, 0), color), //0--7
        VertexFormat(corner + glm::vec3(19, 6, 0), color), //1--8
        VertexFormat(corner + glm::vec3(21, 6, 0), color), //2--9
        VertexFormat(corner + glm::vec3(20, 9, 0), color), //3--10
        VertexFormat(corner + glm::vec3(23, 7, 0), color), //4--11
        VertexFormat(corner + glm::vec3(22, 9, 0), color), //5--12
        VertexFormat(corner + glm::vec3(23, 8, 0), color), //6--13



    };

    Mesh* head = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,2,1,
        0,3,2,
        3,5,2,
        2,5,4,
        5,6,4,

    };

    head->SetDrawMode(GL_TRIANGLES);
    head->InitFromData(vertices, indices);

    return head;
}
Mesh* Duck::CreateBeak(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(23, 7, 0), color), //0--11
        VertexFormat(corner + glm::vec3(23, 8, 0), color), //1--13
        VertexFormat(corner + glm::vec3(25, 7, 0), color), //2--14



    };

    Mesh* beak = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2

    };

    beak->SetDrawMode(GL_TRIANGLES);
    beak->InitFromData(vertices, indices);

    return beak;
}
Mesh* Duck::CreateLWing(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(7, 5, 0), color1), //0
        VertexFormat(corner + glm::vec3(4, 12, 0), color1), //1
        VertexFormat(corner + glm::vec3(5, 16, 0), color1), //2
        VertexFormat(corner + glm::vec3(12, 8, 0), color1), //3

        VertexFormat(corner + glm::vec3(8, 5, 0), color2), //4
        VertexFormat(corner + glm::vec3(5, 16, 0), color2), //5
        VertexFormat(corner + glm::vec3(10, 6.5, 0), color2), //6


    };

    Mesh* lwing = new Mesh(name);
    std::vector<unsigned int> indices = {
        4,5,6,
        0,1,2,
        0,2,3,

    };

    lwing->SetDrawMode(GL_TRIANGLES);
    lwing->InitFromData(vertices, indices);

    return lwing;
}
Mesh* Duck::CreateRWing(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(12, 8, 0), color1), //0
        VertexFormat(corner + glm::vec3(15, 17, 0), color1), //1
        VertexFormat(corner + glm::vec3(16, 7, 0), color1), //2
        VertexFormat(corner + glm::vec3(17, 13, 0), color1), //3



    };

    Mesh* rwing = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        2,1,3,
    };

    rwing->SetDrawMode(GL_TRIANGLES);
    rwing->InitFromData(vertices, indices);

    return rwing;
}


Mesh* Duck::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(2, 0, 0), color), //0
        VertexFormat(corner + glm::vec3(0, 3, 0), color), //1
        VertexFormat(corner + glm::vec3(2, 3, 0), color), //2
        VertexFormat(corner + glm::vec3(1, 4, 0), color), //3
        VertexFormat(corner + glm::vec3(4, 3, 0), color), //4
        VertexFormat(corner + glm::vec3(3, 4, 0), color), //5



    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        1,3,2,
        0,2,4,
        2,5,4,
    };

    heart->SetDrawMode(GL_TRIANGLES);
    heart->InitFromData(vertices, indices);

    return heart;
}

Mesh* Duck::CreateBullet(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color), //0
        VertexFormat(corner + glm::vec3(0, 4, 0), color), //1
        VertexFormat(corner + glm::vec3(2, 4, 0), color), //2
        VertexFormat(corner + glm::vec3(2, 0, 0), color), //3
        VertexFormat(corner + glm::vec3(1, 5, 0), color), //4



    };

    Mesh* bullet = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        1,4,2,
        0,2,3,
    };

    bullet->SetDrawMode(GL_TRIANGLES);
    bullet->InitFromData(vertices, indices);

    return bullet;
}
Mesh* Duck::CreateCursor(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(3, 0, 0), color), //0
        VertexFormat(corner + glm::vec3(2, 3, 0), color), //1
        VertexFormat(corner + glm::vec3(4, 3, 0), color), //2
        VertexFormat(corner + glm::vec3(3, 6, 0), color), //3

        VertexFormat(corner + glm::vec3(0, 3, 0), color), //4
        VertexFormat(corner + glm::vec3(3, 4, 0), color), //5
        VertexFormat(corner + glm::vec3(3, 2, 0), color), //6
        VertexFormat(corner + glm::vec3(6, 3, 0), color), //7


    };

    Mesh* cursor = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        1,3,2,
        4, 5, 6,
        6,5,7,
    };

    cursor->SetDrawMode(GL_TRIANGLES);
    cursor->InitFromData(vertices, indices);

    return cursor;
}

Mesh* Duck::CreateGun(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color), //0
        VertexFormat(corner + glm::vec3(2, 3, 0), color), //1
        VertexFormat(corner + glm::vec3(4, 1, 0), color), //2

        VertexFormat(corner + glm::vec3(3, 2, 0), color), //3
        VertexFormat(corner + glm::vec3(5, 2, 0), color), //4
        VertexFormat(corner + glm::vec3(5, 4, 0), color), //5

        VertexFormat(corner + glm::vec3(15, 3, 0), color), //6
        VertexFormat(corner + glm::vec3(15, 4, 0), color), //7
        VertexFormat(corner + glm::vec3(2, 1, 0), color), //8

    };

    Mesh* gun = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        3,1,4,
        1,5,4,
        4,5,6,
        5,6,7,
        8,4,2,
    };

    gun->SetDrawMode(GL_TRIANGLES);
    gun->InitFromData(vertices, indices);

    return gun;
}
Mesh* Duck::CreateFrontGrass(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color1), //0
        VertexFormat(corner + glm::vec3(1, 4, 0), color1), //1
        VertexFormat(corner + glm::vec3(2, 0, 0), color1), //2

        VertexFormat(corner + glm::vec3(-1, 0, 0), color2), //3
        VertexFormat(corner + glm::vec3(0, 3, 0), color2), //4
        VertexFormat(corner + glm::vec3(2, 0, 0), color2), //5
    };

    Mesh* gun = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        3,4,5,
    };

    gun->SetDrawMode(GL_TRIANGLES);
    gun->InitFromData(vertices, indices);

    return gun;
}

Mesh* Duck::CreateBehindGrass(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(-1, 0, 0), color), //3
        VertexFormat(corner + glm::vec3(0, 4, 0), color), //4
        VertexFormat(corner + glm::vec3(2, 0, 0), color), //5

    };

    Mesh* gun = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
    };

    gun->SetDrawMode(GL_TRIANGLES);
    gun->InitFromData(vertices, indices);

    return gun;
}

Mesh* Duck::CreateSunRay(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(-1, 0, 0), color), //0
        VertexFormat(corner + glm::vec3(0, 3, 0), color), //1
        VertexFormat(corner + glm::vec3(1, 0, 0), color), //2



    };

    Mesh* bullet = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
    };

    bullet->SetDrawMode(GL_TRIANGLES);
    bullet->InitFromData(vertices, indices);

    return bullet;
}
Mesh* Duck::CreateMoonRay(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color), //0
        VertexFormat(corner + glm::vec3(-1, 3, 0), color), //1
        VertexFormat(corner + glm::vec3(1, 3, 0), color), //2



    };

    Mesh* bullet = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
    };

    bullet->SetDrawMode(GL_TRIANGLES);
    bullet->InitFromData(vertices, indices);

    return bullet;
}
