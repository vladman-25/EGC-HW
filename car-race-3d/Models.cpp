#include "Models.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* Models::CreateCar(const char* name,float u, glm::vec3 color)
{
    //////////////////////////
    std::vector<VertexFormat> vertices = CreateCarVertices(u, color);
    std::vector<unsigned int> indices = CreateCarIndices();
    //////////////////////////
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


    glBindVertexArray(0);
    CheckOpenGLError();

    Mesh* obj = new Mesh(name);

    obj->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    obj->vertices = vertices;
    obj->indices = indices;


    return obj;
}

Mesh* Models::CreateCircuit(const char* name, float u, glm::vec3 color)
{
    //////////////////////////
    std::vector<VertexFormat> vertices = CreateCircuitVertices(u, color);
    std::vector<unsigned int> indices =
    {
    };
    for (int i = 0; i < vertices.size() - 2; i += 2) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 3);

        indices.push_back(i);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    indices.push_back(vertices.size() - 2);
    indices.push_back(vertices.size() - 1);
    indices.push_back(1);

    indices.push_back(vertices.size() - 2);
    indices.push_back(1);
    indices.push_back(0);
    //////////////////////////
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


    glBindVertexArray(0);
    CheckOpenGLError();

    Mesh* obj = new Mesh(name);

    obj->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    obj->vertices = vertices;
    obj->indices = indices;


    return obj;
}
Mesh* Models::CreateStrips(const char* name, float u, glm::vec3 color)
{
    //////////////////////////
    std::vector<glm::vec3> verticesAux
    {
        glm::vec3(-7.36 * u, 0,  -4.99 * u),//a
        glm::vec3(-8.19 * u, 0,  -2.99 * u),
        glm::vec3(-9.27 * u, 0,  -0.39 * u),
        glm::vec3(-9.99 * u, 0,  1.67 * u),
        glm::vec3(-10.47 * u, 0,  3.6 * u),
        glm::vec3(-9.81 * u, 0,  7.26 * u),
        glm::vec3(-7.67 * u, 0,  8.48 * u),
        glm::vec3(-5.23 * u, 0,  9.02 * u),
        glm::vec3(-1.78 * u, 0,  9.02 * u),
        glm::vec3(1.4 * u, 0,  8.87 * u),
        glm::vec3(3.99 * u, 0,  8.69 * u),//l
        glm::vec3(5.24 * u, 0,  7.09 * u),
        glm::vec3(4.35 * u, 0,  5.33 * u),
        glm::vec3(2.15 * u, 0,  4.82 * u),
        glm::vec3(-0.08 * u, 0,  5.94 * u),
        glm::vec3(-2.32 * u, 0,  4.97 * u),
        glm::vec3(-4.52 * u, 0,  4.65 * u),//r
        glm::vec3(-5.65 * u, 0,  3.72 * u),//s
        glm::vec3(-6 * u, 0,  2 * u),
        glm::vec3(-5.23 * u, 0,  0.42 * u),
        glm::vec3(-4.07 * u, 0,  -0.74 * u),
        glm::vec3(-1.72 * u, 0,  -0.35 * u),
        glm::vec3(-0 * u, 0,  0.9 * u),//z
        glm::vec3(2.27 * u, 0,  1.49 * u),
        glm::vec3(4.65 * u, 0,  1.43 * u),
        glm::vec3(6.49 * u, 0,  0.12 * u),
        glm::vec3(6.67 * u, 0,  -2.05 * u),
        glm::vec3(5.39 * u, 0,  -4.52 * u),
        glm::vec3(2 * u, 0,  -6 * u),
        glm::vec3(-0.41 * u, 0,  -6.54 * u),
        glm::vec3(-3.33 * u, 0,  -6.87 * u),
        glm::vec3(-5.23 * u, 0,  -6.48 * u),
    };
    std::vector<VertexFormat> vertices{};

    std::vector<glm::vec3> verticesAux2{};

    for (int i = 0; i < verticesAux.size() - 1; i++) {
        //verticesAux2.push_back(verticesAux[i]);
        glm::vec3 P1 = verticesAux[i];
        glm::vec3 P2 = verticesAux[i + 1];
        glm::vec3 D = P2 - P1;
        //verticesAux2.push_back(verticesAux[i] + D * 0.05f);
        for (int j = 1; j < 10; j++) {
            float x = j;
            verticesAux2.push_back(verticesAux[i] + D * (x / 10.0f));
        }
    }
    //verticesAux2.push_back(verticesAux[verticesAux.size() - 1]);
    glm::vec3 Pp1 = verticesAux[verticesAux.size() - 1];
    glm::vec3 Pp2 = verticesAux[0];
    glm::vec3 Dp = Pp2 - Pp1;
    //verticesAux2.push_back(verticesAux[verticesAux.size() - 1] + Dp * 0.05f);
    for (int j = 1; j < 10; j++) {
        float x = j;
        verticesAux2.push_back(verticesAux[verticesAux.size() - 1] + Dp * (x / 10.0f));
    }
    std::vector<unsigned int> indices = {};
    for (int i = 0; i < verticesAux2.size() - 1; i++) {
        vertices.push_back(VertexFormat(verticesAux2[i], color, glm::vec3(0.2, 0.8, 0.6)));
        indices.push_back(i);
    }
    //////////////////////////
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


    glBindVertexArray(0);
    CheckOpenGLError();

    glLineWidth(2);

    Mesh* obj = new Mesh(name);

    obj->SetDrawMode(GL_LINES);
    obj->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    obj->vertices = vertices;
    obj->indices = indices;


    return obj;
}

Mesh* Models::CreateTree(const char* name, float u, glm::vec3 color)
{
    //////////////////////////
    std::vector<VertexFormat> vertices = CreateTreeVertices(u);
    std::vector<unsigned int> indices = CreateTreeIndices();
    //////////////////////////
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


    glBindVertexArray(0);
    CheckOpenGLError();

    Mesh* obj = new Mesh(name);

    obj->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    obj->vertices = vertices;
    obj->indices = indices;


    return obj;
}

Mesh* Models::CreateGround(const char* name, float u, glm::vec3 color)
{
    //////////////////////////
    std::vector<VertexFormat> vertices = CreateGroundVertices(color);
    std::vector<unsigned int> indices = CreateGroundIndices();
    //////////////////////////
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


    glBindVertexArray(0);
    CheckOpenGLError();

    Mesh* obj = new Mesh(name);

    obj->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    obj->vertices = vertices;
    obj->indices = indices;


    return obj;
}


std::vector<VertexFormat> Models::CreateCarVertices(float u,
glm::vec3 color)
{

    std::vector<VertexFormat> vertices
    {
        //hood
        VertexFormat(glm::vec3(0, 0,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(3 * u,  -u / 2,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(u, u / 2,  2 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(3 * u,  u / 2,  2 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(11 * u,  0,  3 * u), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(10 * u,  -u,  6 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  0,  0),color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(0, 0,  -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(3 * u,  -u / 2,  -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(u, u / 2,  -2 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(3 * u,  u / 2,  -2 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(11 * u,  0,  -3 * u), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(10 * u,  -u,  -6 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)),
        //fender1
        VertexFormat(glm::vec3(0, -4 * u,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //13 - 0
        VertexFormat(glm::vec3(4 * u,  -4 * u,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //14 - 1 
        VertexFormat(glm::vec3(8 * u,  -4 * u,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //15 -  
        VertexFormat(glm::vec3(10 * u,  -4 * u,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //16 - 5
        VertexFormat(glm::vec3(4 * u,  -3 * u,  6 * u), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)), //17
        VertexFormat(glm::vec3(8 * u,  -3 * u,  6 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //18
        VertexFormat(glm::vec3(5 * u,  -2 * u,  6 * u), color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)), //19
        VertexFormat(glm::vec3(7 * u,  -2 * u,  6 * u), color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)), //20 
        //fender2
        VertexFormat(glm::vec3(0, -4 * u,  -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //21
        VertexFormat(glm::vec3(4 * u,  -4 * u,  -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //22
        VertexFormat(glm::vec3(8 * u,  -4 * u,  -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //23 
        VertexFormat(glm::vec3(10 * u,  -4 * u,  -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //24
        VertexFormat(glm::vec3(4 * u,  -3 * u,  -6 * u), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)), //25
        VertexFormat(glm::vec3(8 * u,  -3 * u,  -6 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //26
        VertexFormat(glm::vec3(5 * u,  -2 * u,  -6 * u), color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)), //27
        VertexFormat(glm::vec3(7 * u,  -2 * u,  -6 * u), color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)), //28 
        //grill
        VertexFormat(glm::vec3(10 * u,  -4 * u,  5 * u), color + glm::vec3(0, 0.1 * 1, 0), glm::vec3(0.2, 0.8, 0.6)),//29
        VertexFormat(glm::vec3(10 * u,  -1 * u,  5 * u), color + glm::vec3(0, 0.1 * 2, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -u,  0), color + glm::vec3(0, 0.1 * 3, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -3 * u,  0), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -4 * u,  0), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(10 * u,  -3 * u,  5 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(10 * u,  -3 * u,  5 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(10 * u,  -1 * u,  5 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -3 * u,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -u,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(10 * u,  -4 * u,  -5 * u), color + glm::vec3(0, 0.1 * 1, 0), glm::vec3(0.2, 0.8, 0.6)),//39
        VertexFormat(glm::vec3(10 * u,  -1 * u,  -5 * u), color + glm::vec3(0, 0.1 * 2, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -u,  0), color + glm::vec3(0, 0.1 * 3, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -3 * u,  0), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -4 * u,  0), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(10 * u,  -3 * u,  -5 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(10 * u,  -3 * u,  -5 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(10 * u,  -1 * u,  -5 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -3 * u,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(12 * u,  -u,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),

        //winshield
        VertexFormat(glm::vec3(u / 4, 0,  6 * u - u / 2), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)), //49
        VertexFormat(glm::vec3(-4 * u, 3 * u,  5 * u - u / 2), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)), //50
        VertexFormat(glm::vec3(-4 * u,  3 * u,  4 * u), color + glm::vec3(0, 0.2 * 3, 0), glm::vec3(0.2, 0.8, 0.6)), //51

        VertexFormat(glm::vec3(u / 4, 0,  6 * u - u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-4 * u,  3 * u,  4 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(u, u / 2,  2 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-4 * u, 3 * u,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(u / 4, 0,  -6 * u + u / 2), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)), //56
        VertexFormat(glm::vec3(-4 * u, 3 * u,  -5 * u + u / 2), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-4 * u,  3 * u,  -4 * u), color + glm::vec3(0, 0.2 * 3, 0), glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(u / 4, 0,  -6 * u + u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-4 * u,  3 * u,  -4 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(u, u / 2,  -2 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-4 * u, 3 * u,  0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),

        //top
        VertexFormat(glm::vec3(-12 * u, 3 * u,  5 * u - u / 2), color + glm::vec3(0, 0.2 * 3, 0), glm::vec3(0.2, 0.8, 0.6)), //63
        VertexFormat(glm::vec3(-12 * u, 3 * u,  -5 * u + u / 2), color + glm::vec3(0, 0.2 * 3, 0), glm::vec3(0.2, 0.8, 0.6)), //64
        VertexFormat(glm::vec3(-8 * u, 3 * u + u / 2,  0), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)), //65

        //side1
        VertexFormat(glm::vec3(0, 0,  6 * u), color + glm::vec3(0, 0.1 * 4, 0) , glm::vec3(0.2, 0.8, 0.6)), //66
        VertexFormat(glm::vec3(0, -4 * u,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),  //67
        VertexFormat(glm::vec3(-12 * u, -4 * u,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //68
        VertexFormat(glm::vec3(-17 * u,  0,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //69
        VertexFormat(glm::vec3(-4 * u, 3 * u,  5 * u - u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //70
        VertexFormat(glm::vec3(-4 * u - u / 2, 3 * u,  5 * u - u / 2),color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //71
        VertexFormat(glm::vec3(-u / 2, 0,  6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //72
        VertexFormat(glm::vec3(-12 * u, 3 * u,  5 * u - u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //73
        VertexFormat(glm::vec3(-12 * u + u / 2, 3 * u,  5 * u - u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //74
        VertexFormat(glm::vec3(-17 * u + u / 2,  0,  6 * u), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)), //75
        VertexFormat(glm::vec3(-8 * u, 3 * u, 5 * u - u / 2), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //76
        VertexFormat(glm::vec3(-8 * u - u / 2, 3 * u, 5 * u - u / 2), color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)), //77
        VertexFormat(glm::vec3(-8 * u, 0, 6 * u), color + glm::vec3(0, 0.1 * 8, 0), glm::vec3(0.2, 0.8, 0.6)), //78
        VertexFormat(glm::vec3(-8 * u - u / 2, 0, 6 * u), color + glm::vec3(0, 0.1 * 9, 0), glm::vec3(0.2, 0.8, 0.6)), //79

        VertexFormat(glm::vec3(-8 * u, 3 * u, 5 * u - u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //80
        VertexFormat(glm::vec3(-8 * u, 0, 6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //81
        VertexFormat(glm::vec3(-u / 2, 0, 6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //82
        VertexFormat(glm::vec3(-4 * u - u / 2, 3 * u, 5 * u - u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //83

        VertexFormat(glm::vec3(-8 * u - u / 2, 3 * u, 5 * u - u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //84
        VertexFormat(glm::vec3(-8 * u - u / 2, 0, 6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //85
        VertexFormat(glm::vec3(-12 * u + u / 2, 3 * u, 5 * u - u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //86
        VertexFormat(glm::vec3(-17 * u + u / 2, 0, 6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //87

        //side2
            VertexFormat(glm::vec3(0, 0, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //88
            VertexFormat(glm::vec3(0, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-12 * u, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-17 * u, 0, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-4 * u, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-4 * u - u / 2, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-u / 2, 0, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-12 * u, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-12 * u + u / 2, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-17 * u + u / 2, 0, -6 * u), color + glm::vec3(0, 0.1 * 5, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-8 * u, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-8 * u - u / 2, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 7, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-8 * u, 0, -6 * u), color + glm::vec3(0, 0.1 * 8, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-8 * u - u / 2, 0, -6 * u), color + glm::vec3(0, 0.1 * 9, 0), glm::vec3(0.2, 0.8, 0.6)),

            VertexFormat(glm::vec3(-8 * u, 3 * u, -5 * u + u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-8 * u, 0, -6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-u / 2, 0, -6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-4 * u - u / 2, 3 * u, -5 * u + u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),

            VertexFormat(glm::vec3(-8 * u - u / 2, 3 * u, -5 * u + u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-8 * u - u / 2, 0, -6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-12 * u + u / 2, 3 * u, -5 * u + u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-17 * u + u / 2, 0, -6 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //109
            //backwindshield

                VertexFormat(glm::vec3(-12 * u, 3 * u, 5 * u - u / 2), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //110
                VertexFormat(glm::vec3(-12 * u, 3 * u, 4 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //111
                VertexFormat(glm::vec3(-17 * u, 0, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //112
                VertexFormat(glm::vec3(-17 * u, 0, 5 * u + u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //113

                VertexFormat(glm::vec3(-12 * u, 3 * u, 4 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //114
                VertexFormat(glm::vec3(-17 * u, 0, 5 * u + u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //115
                VertexFormat(glm::vec3(-18 * u, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //116
                //
                VertexFormat(glm::vec3(-12 * u, 3 * u, -5 * u + u / 2), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //117
                VertexFormat(glm::vec3(-12 * u, 3 * u, -4 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-17 * u, 0, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-17 * u, 0, -5 * u - u / 2), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),

                VertexFormat(glm::vec3(-12 * u, 3 * u, -4 * u), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-17 * u, 0, -5 * u - u / 2), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),
                VertexFormat(glm::vec3(-18 * u, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //123

                //bhood
                VertexFormat(glm::vec3(-18 * u, 0, 0), color + glm::vec3(0, 0.2 * 1, 0), glm::vec3(0.2, 0.8, 0.6)), //124
                VertexFormat(glm::vec3(-17 * u + u / 2, 0, 6 * u), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)), //125
                VertexFormat(glm::vec3(-22 * u, -u / 2, 6 * u), color + glm::vec3(0, 0.2 * 3, 0), glm::vec3(0.2, 0.8, 0.6)), //126
                VertexFormat(glm::vec3(-23 * u, -u / 2, 4 * u), color + glm::vec3(0, 0.2 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //127

                    VertexFormat(glm::vec3(-18 * u, 0, 0), color + glm::vec3(0, 0.2 * 1, 0), glm::vec3(0.2, 0.8, 0.6)), //128
                    VertexFormat(glm::vec3(-17 * u + u / 2, 0, -6 * u), color + glm::vec3(0, 0.2 * 2, 0), glm::vec3(0.2, 0.8, 0.6)), //129
                    VertexFormat(glm::vec3(-22 * u, -u / 2, -6 * u), color + glm::vec3(0, 0.2 * 3, 0), glm::vec3(0.2, 0.8, 0.6)), //130
                    VertexFormat(glm::vec3(-23 * u, -u / 2, -4 * u), color + glm::vec3(0, 0.2 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //131
                    //bsideskirt1

                    VertexFormat(glm::vec3(-22 * u, -u / 2, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //132
                    VertexFormat(glm::vec3(-22 * u, -4 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                    VertexFormat(glm::vec3(-19 * u, -4 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),//134
                    VertexFormat(glm::vec3(-15 * u, -4 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                    VertexFormat(glm::vec3(-15 * u, -3 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //136
                    VertexFormat(glm::vec3(-12 * u, -4 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                    VertexFormat(glm::vec3(-19 * u, -3 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //138
                    VertexFormat(glm::vec3(-18 * u, -2 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //139
                    VertexFormat(glm::vec3(-17 * u, 0, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                    VertexFormat(glm::vec3(-16 * u, -2 * u, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //141
                    //BS2
                        VertexFormat(glm::vec3(-22 * u, -u / 2, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //142
                        VertexFormat(glm::vec3(-22 * u, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-19 * u, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),//134
                        VertexFormat(glm::vec3(-15 * u, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-15 * u, -3 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //136
                        VertexFormat(glm::vec3(-12 * u, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-19 * u, -3 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //138
                        VertexFormat(glm::vec3(-18 * u, -2 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //139
                        VertexFormat(glm::vec3(-17 * u, 0, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)),
                        VertexFormat(glm::vec3(-16 * u, -2 * u, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //151
                        //bgrill
                         VertexFormat(glm::vec3(-22 * u, -u / 2, 6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //152
                         VertexFormat(glm::vec3(-23 * u, -u / 2, 4 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //153
                         VertexFormat(glm::vec3(-22 * u, -u / 2, -6 * u), color + glm::vec3(0, 0.1 * 4, 0), glm::vec3(0.2, 0.8, 0.6)), //154
                         VertexFormat(glm::vec3(-23 * u, -u / 2, -4 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //155

                            VertexFormat(glm::vec3(-22 * u, -4 * u, 6 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //156
                            VertexFormat(glm::vec3(-23 * u, -4 * u, 4 * u), color + glm::vec3(0, 0.1 * 8, 0), glm::vec3(0.2, 0.8, 0.6)), //157
                            VertexFormat(glm::vec3(-22 * u, -4 * u, -6 * u), color + glm::vec3(0, 0.1 * 6, 0), glm::vec3(0.2, 0.8, 0.6)), //158
                            VertexFormat(glm::vec3(-23 * u, -4 * u, -4 * u), color + glm::vec3(0, 0.1 * 8, 0), glm::vec3(0.2, 0.8, 0.6)), //159
    };
    return vertices;
}
std::vector<unsigned int> Models::CreateCarIndices() {
    std::vector<unsigned int> indices =
    {
        //hoood
        0, 1, 2,
        2, 1, 3,
        3, 1, 4,
        1, 5, 4,
        3, 4, 6,

        7, 8, 9,
        9, 8, 10,
        10, 8, 11,
        8, 12, 11,
        10, 11, 6,

        3, 6, 10,
        2, 3, 9,
        9, 3, 10,
        //fender
        0,13,14,
        0,14,17,
        0,17,19,
        0,1,19,
        1,19,5,
        19,20,5,
        5,15,16,
        5,18,15,
        5,20,18,

        //fender2
        7,21,22,
        7,22,25,
        7,25,27,
        7,8,27,
        8,27,12,
        27,28,12,
        12,23,24,
        12,26,23,
        12,28,26,

        //grill
        5,16,29,
        5,29,30,
        5,30,4,

        30,4,6,
        30,6,31,

        29,32,33,
        29,32,34,

        35,36,37,
        36,37,38,

        12,24,39,
        12,39,40,
        12,40,11,

        40,11,6,
        40,6,41,

        39,42,43,
        39,42,44,

        45,46,47,
        46,47,48,

        //windhshield
        0, 49, 50,
        49, 50, 51,
        52,53,54,
        53,54,55,

        7,56,57,
        56,57,58,
        59,60,61,
        60,61,62,

        54,61,62,
        //top
        50,57, 65,
        63,64,65,
        50,63,65,
        57,64,65,
        //side1
        66,67,68,
        66,69,68,
        66,71,70,
        72,66,71,
        73,74,69,
        69,74,75,
        76,77,78,
        78,79,77,
        80,81,82,
        83,80,82,
        84,85,86,
        87,86,85,
        //side2
        88,89,90,
        88,91,90,
        88,93,92,

        94,88,93,
        95,96,91,
        91,96,97,

        98,99,100,
        100,101,99,
        102,103,104,

        105,102,104,
        106,107,108,
        109,108,107,
        //bshield

    110,111,112,
    111,112,113,
    114,115,116,

    117, 118, 119,
    118, 119, 120,
    121, 122, 123,
    114,121,116,

    //bhoood
    124,125,126,
    124,126,127,

        128, 129, 130,
        128, 130, 131,
    124,127,131,
    //bs1
    132,133,134,
        135,136,137,
        138,132,134,
        138,139,132,
        139,132,140,
        139,140,141,
        140,141,137,
        136,137,141,
        //bs2
            142, 143, 144,
            145, 146, 147,
            148, 142, 144,
            148, 149, 142,
            149, 142, 150,
            149, 150, 151,
            150, 151, 147,
            146, 147, 151,
            //bg
            152,156,157,
            152,157,153,
            153,157,159,
            153,159,155,
            155,159,158,
            154,155,158,
    };
    return indices;
}

std::vector<VertexFormat> Models::CreateCircuitVertices(float u,
    glm::vec3 color)
{   
    std::vector<glm::vec3> verticesAux
    {
        glm::vec3(-7.36 * u, 0,  -4.99 * u),//a
        glm::vec3(-8.19 * u, 0,  -2.99 * u),
        glm::vec3(-9.27 * u, 0,  -0.39 * u),
        glm::vec3(-9.99 * u, 0,  1.67 * u),
        glm::vec3(-10.47 * u, 0,  3.6 * u),
        glm::vec3(-9.81 * u, 0,  7.26 * u),
        glm::vec3(-7.67 * u, 0,  8.48 * u),
        glm::vec3(-5.23 * u, 0,  9.02 * u),
        glm::vec3(-1.78 * u, 0,  9.02 * u),
        glm::vec3(1.4 * u, 0,  8.87 * u),
        glm::vec3(3.99 * u, 0,  8.69 * u),//l
        glm::vec3(5.24 * u, 0,  7.09 * u),
        glm::vec3(4.35 * u, 0,  5.33 * u),
        glm::vec3(2.15 * u, 0,  4.82 * u),
        glm::vec3(-0.08 * u, 0,  5.94 * u),
        glm::vec3(-2.32 * u, 0,  4.97 * u),
        glm::vec3(-4.52 * u, 0,  4.65 * u),//r
        glm::vec3(-5.65 * u, 0,  3.72 * u),//s
        glm::vec3(-6 * u, 0,  2 * u),
        glm::vec3(-5.23 * u, 0,  0.42 * u),
        glm::vec3(-4.07 * u, 0,  -0.74 * u),
        glm::vec3(-1.72 * u, 0,  -0.35 * u),
        glm::vec3(-0 * u, 0,  0.9 * u),//z
        glm::vec3(2.27 * u, 0,  1.49 * u),
        glm::vec3(4.65 * u, 0,  1.43 * u),
        glm::vec3(6.49 * u, 0,  0.12 * u),
        glm::vec3(6.67 * u, 0,  -2.05 * u),
        glm::vec3(5.39 * u, 0,  -4.52 * u),
        glm::vec3(2* u, 0,  -6 * u),
        glm::vec3(-0.41 * u, 0,  -6.54* u),
        glm::vec3(-3.33 * u, 0,  -6.87 * u),
        glm::vec3(-5.23 * u, 0,  -6.48 * u),
    };
    std::vector<VertexFormat> vertices {};

    std::vector<glm::vec3> verticesAux2 {};

    for (int i = 0; i < verticesAux.size() - 1; i++) {
        //verticesAux2.push_back(verticesAux[i]);
        glm::vec3 P1 = verticesAux[i];
        glm::vec3 P2 = verticesAux[i + 1];
        glm::vec3 D = P2 - P1;
        //verticesAux2.push_back(verticesAux[i] + D * 0.05f);
        for (int j = 1; j < 10; j++) {
            float x = j;
            verticesAux2.push_back(verticesAux[i] + D * (x / 10.0f));
        }
    }
    //verticesAux2.push_back(verticesAux[verticesAux.size() - 1]);
    glm::vec3 Pp1 = verticesAux[verticesAux.size() - 1];
    glm::vec3 Pp2 = verticesAux[0];
    glm::vec3 Dp = Pp2 - Pp1;
    //verticesAux2.push_back(verticesAux[verticesAux.size() - 1] + Dp * 0.05f);
    for (int j = 1; j < 10; j++) {
        float x = j;
        verticesAux2.push_back(verticesAux[verticesAux.size() - 1] + Dp * (x / 10.0f));
    }



    for (int i = 0; i < verticesAux2.size()-1; i++) {
        glm::vec3 P1 = verticesAux2[i];
        glm::vec3 P2 = verticesAux2[i+1];
        glm::vec3 D = P2 - P1;
        float d = glm::distance(glm::vec3(0), D);
        glm::vec3 P = glm::cross(D, glm::vec3(0,1,0));
        glm::vec3 R = P1 + 3.0f * P/d;
        glm::vec3 A = P1 - 3.0f * P/d;
        
            vertices.push_back(VertexFormat(R, color, glm::vec3(0.2, 0.8, 0.6)));
            vertices.push_back(VertexFormat(A, color, glm::vec3(0.2, 0.8, 0.6)));
        
    }
    glm::vec3 P1 = verticesAux2[verticesAux2.size() - 1];
    glm::vec3 P2 = verticesAux2[0];
    glm::vec3 D = P2 - P1;
    float d = glm::distance(glm::vec3(0), D);
    glm::vec3 P = glm::cross(D, glm::vec3(0, 1, 0));
    glm::vec3 R = P1 + 3.0f * P/d;
    glm::vec3 A = P1 - 3.0f * P/d;
    vertices.push_back(VertexFormat(R, color, glm::vec3(0.2, 0.8, 0.6)));
    vertices.push_back(VertexFormat(A, color, glm::vec3(0.2, 0.8, 0.6)));


    return vertices;
}
std::vector<unsigned int> Models::CreateCircuitIndices(std::vector<VertexFormat> vertices) {
    std::vector<unsigned int> indices =
    {
    };
    for (int i = 0; i < vertices.size() - 2; i+=2) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 3);

        indices.push_back(i);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    indices.push_back(vertices.size() - 2);
    indices.push_back(vertices.size() - 1);
    indices.push_back(1);

    indices.push_back(vertices.size() - 2);
    indices.push_back(1);
    indices.push_back(0);


    return indices;
}

std::vector<VertexFormat> Models::CreateTreeVertices(float u)
{
    glm::vec3 color = glm::vec3(0.239, 0.168, 0.121);
    glm::vec3 color2 = glm::vec3(0.03, 0.26, 0.129);
    std::vector<VertexFormat> vertices
    {
        //hood
        VertexFormat(glm::vec3(-1 * u, 0,  -1 * u), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-1 * u, 0,  1 * u), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(1 * u, 0,  -1 * u), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(1 * u, 0,  1 * u), color, glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(-1 * u, 2 * u,  -1 * u), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-1 * u, 2 * u,  1 * u), color , glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(1 * u, 2 * u,  -1 * u), color, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(1 * u, 2 * u,  1 * u), color, glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(-3 * u, 2 * u,  -3 * u), color2, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-3 * u, 2 * u,  3 * u), color2, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(3 * u, 2 * u,  -3 * u), color2, glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(3 * u, 2 * u,  3 * u), color2, glm::vec3(0.2, 0.8, 0.6)),

        VertexFormat(glm::vec3(0 * u, 16 * u,  0 * u), color2, glm::vec3(0.2, 0.8, 0.6)),
    };
    return vertices;

}
std::vector<unsigned int> Models::CreateTreeIndices() {
    std::vector<unsigned int> indices =
    {
        0,1,2,
        1,2,3,

        0,4,2,
        4,2,6,
        6,2,3,
        6,3,7,
        3,7,5,
        3,5,1,
        1,4,5,
        1,4,0,

        4,5,6,
        5,6,7,

        8,9,10,
        9,10,11,

        8,10,12,
        10,11,12,
        11,9,12,
        9,8,12,
    };
    return indices;
}

std::vector<glm::vec3> Models::CreateTreePos(float u)
{
    std::vector<glm::vec3> verticesAux
    {

        glm::vec3(-7.36 * u, 0,  -4.99 * u),//a
        glm::vec3(-8.19 * u, 0,  -2.99 * u),
        glm::vec3(-9.27 * u, 0,  -0.39 * u),
        glm::vec3(-9.99 * u, 0,  1.67 * u),
        glm::vec3(-10.47 * u, 0,  3.6 * u),
        glm::vec3(-9.81 * u, 0,  7.26 * u),
        //glm::vec3(-10.44 * u, 0,  5.39 * u),//f
        //glm::vec3(-9.81 * u, 0,  7.26 * u),//g
        glm::vec3(-7.67 * u, 0,  8.48 * u),
        glm::vec3(-5.23 * u, 0,  9.02 * u),
        glm::vec3(-1.78 * u, 0,  9.02 * u),
        glm::vec3(1.4 * u, 0,  8.87 * u),
        glm::vec3(3.99 * u, 0,  8.69 * u),//l
        glm::vec3(5.24 * u, 0,  7.09 * u),
        glm::vec3(4.35 * u, 0,  5.33 * u),
        glm::vec3(2.15 * u, 0,  4.82 * u),
        glm::vec3(-0.08 * u, 0,  5.94 * u),
        glm::vec3(-2.32 * u, 0,  4.97 * u),
        glm::vec3(-4.52 * u, 0,  4.65 * u),//r
        glm::vec3(-5.65 * u, 0,  3.72 * u),//s
        glm::vec3(-6 * u, 0,  2 * u),
        glm::vec3(-5.23 * u, 0,  0.42 * u),
        glm::vec3(-4.07 * u, 0,  -0.74 * u),
        glm::vec3(-1.72 * u, 0,  -0.35 * u),
        glm::vec3(-0 * u, 0,  0.9 * u),//z
        glm::vec3(2.27 * u, 0,  1.49 * u),
        glm::vec3(4.65 * u, 0,  1.43 * u),
        glm::vec3(6.49 * u, 0,  0.12 * u),
        glm::vec3(6.67 * u, 0,  -2.05 * u),
        glm::vec3(5.39 * u, 0,  -4.52 * u),
        glm::vec3(2 * u, 0,  -6 * u),
        glm::vec3(-0.41 * u, 0,  -6.54 * u),
        glm::vec3(-3.33 * u, 0,  -6.87 * u),
        glm::vec3(-5.23 * u, 0,  -6.48 * u),

        //
    };
    std::vector<glm::vec3> vertices{};
    for (int i = 0; i < verticesAux.size() - 1; i++) {
        glm::vec3 P1 = verticesAux[i];
        glm::vec3 P2 = verticesAux[i + 1];
        glm::vec3 D = P2 - P1;
        glm::vec3 P = glm::cross(D, glm::vec3(0, 1, 0));
        float d = glm::distance(glm::vec3(0), D);
        glm::vec3 R = P1 + 6.0f * P / d;
        glm::vec3 A = P1 - 6.0f * P / d;
        vertices.push_back(R);
        vertices.push_back(A);
    }

    return vertices;
}

std::vector<glm::vec3> Models::CreateCarTraj(float u)
{
    std::vector<glm::vec3> verticesAux
    {

        glm::vec3(-7.36 * u, 0,  -4.99 * u),//a
        glm::vec3(-8.19 * u, 0,  -2.99 * u),
        glm::vec3(-9.27 * u, 0,  -0.39 * u),
        glm::vec3(-9.99 * u, 0,  1.67 * u),
        glm::vec3(-10.47 * u, 0,  3.6 * u),
        glm::vec3(-9.81 * u, 0,  7.26 * u),
        //glm::vec3(-10.44 * u, 0,  5.39 * u),//f
        //glm::vec3(-9.81 * u, 0,  7.26 * u),//g
        glm::vec3(-7.67 * u, 0,  8.48 * u),
        glm::vec3(-5.23 * u, 0,  9.02 * u),
        glm::vec3(-1.78 * u, 0,  9.02 * u),
        glm::vec3(1.4 * u, 0,  8.87 * u),
        glm::vec3(3.99 * u, 0,  8.69 * u),//l
        glm::vec3(5.24 * u, 0,  7.09 * u),
        glm::vec3(4.35 * u, 0,  5.33 * u),
        glm::vec3(2.15 * u, 0,  4.82 * u),
        glm::vec3(-0.08 * u, 0,  5.94 * u),
        glm::vec3(-2.32 * u, 0,  4.97 * u),
        glm::vec3(-4.52 * u, 0,  4.65 * u),//r
        glm::vec3(-5.65 * u, 0,  3.72 * u),//s
        glm::vec3(-6 * u, 0,  2 * u),
        glm::vec3(-5.23 * u, 0,  0.42 * u),
        glm::vec3(-4.07 * u, 0,  -0.74 * u),
        glm::vec3(-1.72 * u, 0,  -0.35 * u),
        glm::vec3(-0 * u, 0,  0.9 * u),//z
        glm::vec3(2.27 * u, 0,  1.49 * u),
        glm::vec3(4.65 * u, 0,  1.43 * u),
        glm::vec3(6.49 * u, 0,  0.12 * u),
        glm::vec3(6.67 * u, 0,  -2.05 * u),
        glm::vec3(5.39 * u, 0,  -4.52 * u),
        glm::vec3(2 * u, 0,  -6 * u),
        glm::vec3(-0.41 * u, 0,  -6.54 * u),
        glm::vec3(-3.33 * u, 0,  -6.87 * u),
        glm::vec3(-5.23 * u, 0,  -6.48 * u),

    };
    std::vector<glm::vec3> vertices{};
    for (int i = 0; i < verticesAux.size() - 1; i++) {
        glm::vec3 P1 = verticesAux[i];
        glm::vec3 P2 = verticesAux[i + 1];
        glm::vec3 D = P2 - P1;
        glm::vec3 P = glm::cross(D, glm::vec3(0, 1, 0));
        float d = glm::distance(glm::vec3(0), D);
        glm::vec3 R = P1 + 1.0f * P/d;
        vertices.push_back(R);
    }

    return vertices;
}
std::vector<glm::vec3> Models::CreateCarTraj_R(float u)
{
    std::vector<glm::vec3> verticesAux
    {
        glm::vec3(-7.36 * u, 0,  -4.99 * u),//a
        glm::vec3(-8.19 * u, 0,  -2.99 * u),
        glm::vec3(-9.27 * u, 0,  -0.39 * u),
        glm::vec3(-9.99 * u, 0,  1.67 * u),
        glm::vec3(-10.47 * u, 0,  3.6 * u),
        glm::vec3(-9.81 * u, 0,  7.26 * u),
        //glm::vec3(-10.44 * u, 0,  5.39 * u),//f
        //glm::vec3(-9.81 * u, 0,  7.26 * u),//g
        glm::vec3(-7.67 * u, 0,  8.48 * u),
        glm::vec3(-5.23 * u, 0,  9.02 * u),
        glm::vec3(-1.78 * u, 0,  9.02 * u),
        glm::vec3(1.4 * u, 0,  8.87 * u),
        glm::vec3(3.99 * u, 0,  8.69 * u),//l
        glm::vec3(5.24 * u, 0,  7.09 * u),
        glm::vec3(4.35 * u, 0,  5.33 * u),
        glm::vec3(2.15 * u, 0,  4.82 * u),
        glm::vec3(-0.08 * u, 0,  5.94 * u),
        glm::vec3(-2.32 * u, 0,  4.97 * u),
        glm::vec3(-4.52 * u, 0,  4.65 * u),//r
        glm::vec3(-5.65 * u, 0,  3.72 * u),//s
        glm::vec3(-6 * u, 0,  2 * u),
        glm::vec3(-5.23 * u, 0,  0.42 * u),
        glm::vec3(-4.07 * u, 0,  -0.74 * u),
        glm::vec3(-1.72 * u, 0,  -0.35 * u),
        glm::vec3(-0 * u, 0,  0.9 * u),//z
        glm::vec3(2.27 * u, 0,  1.49 * u),
        glm::vec3(4.65 * u, 0,  1.43 * u),
        glm::vec3(6.49 * u, 0,  0.12 * u),
        glm::vec3(6.67 * u, 0,  -2.05 * u),
        glm::vec3(5.39 * u, 0,  -4.52 * u),
        glm::vec3(2 * u, 0,  -6 * u),
        glm::vec3(-0.41 * u, 0,  -6.54 * u),
        glm::vec3(-3.33 * u, 0,  -6.87 * u),
        glm::vec3(-5.23 * u, 0,  -6.48 * u),
    };
    std::vector<glm::vec3> vertices{};
    for (int i = 0; i < verticesAux.size() - 1; i++) {
        glm::vec3 P1 = verticesAux[i];
        glm::vec3 P2 = verticesAux[i + 1];
        glm::vec3 D = P2 - P1;
        glm::vec3 P = glm::cross(D, glm::vec3(0, 1, 0));
        float d = glm::distance(glm::vec3(0), D);
        glm::vec3 R = P1 - 1.0f * P / d;
        vertices.push_back(R);
    }

    return vertices;
}

std::vector<glm::vec3> Models::CreateCircuitMiddle(float u)
{
    std::vector<glm::vec3> verticesAux
    {
        glm::vec3(-7.36 * u, 0,  -4.99 * u),//a
        glm::vec3(-8.19 * u, 0,  -2.99 * u),
        glm::vec3(-9.27 * u, 0,  -0.39 * u),
        glm::vec3(-9.99 * u, 0,  1.67 * u),
        glm::vec3(-10.47 * u, 0,  3.6 * u),
        glm::vec3(-9.81 * u, 0,  7.26 * u),
        //glm::vec3(-10.44 * u, 0,  5.39 * u),//f
        //glm::vec3(-9.81 * u, 0,  7.26 * u),//g
        glm::vec3(-7.67 * u, 0,  8.48 * u),
        glm::vec3(-5.23 * u, 0,  9.02 * u),
        glm::vec3(-1.78 * u, 0,  9.02 * u),
        glm::vec3(1.4 * u, 0,  8.87 * u),
        glm::vec3(3.99 * u, 0,  8.69 * u),//l
        glm::vec3(5.24 * u, 0,  7.09 * u),
        glm::vec3(4.35 * u, 0,  5.33 * u),
        glm::vec3(2.15 * u, 0,  4.82 * u),
        glm::vec3(-0.08 * u, 0,  5.94 * u),
        glm::vec3(-2.32 * u, 0,  4.97 * u),
        glm::vec3(-4.52 * u, 0,  4.65 * u),//r
        glm::vec3(-5.65 * u, 0,  3.72 * u),//s
        glm::vec3(-6 * u, 0,  2 * u),
        glm::vec3(-5.23 * u, 0,  0.42 * u),
        glm::vec3(-4.07 * u, 0,  -0.74 * u),
        glm::vec3(-1.72 * u, 0,  -0.35 * u),
        glm::vec3(-0 * u, 0,  0.9 * u),//z
        glm::vec3(2.27 * u, 0,  1.49 * u),
        glm::vec3(4.65 * u, 0,  1.43 * u),
        glm::vec3(6.49 * u, 0,  0.12 * u),
        glm::vec3(6.67 * u, 0,  -2.05 * u),
        glm::vec3(5.39 * u, 0,  -4.52 * u),
        glm::vec3(2 * u, 0,  -6 * u),
        glm::vec3(-0.41 * u, 0,  -6.54 * u),
        glm::vec3(-3.33 * u, 0,  -6.87 * u),
        glm::vec3(-5.23 * u, 0,  -6.48 * u),
    };

    std::vector<glm::vec3> verticesAux2{};

    for (int i = 0; i < verticesAux.size(); i++) {
        verticesAux2.push_back(verticesAux[i]);
        //glm::vec3 P1 = verticesAux[i];
        //glm::vec3 P2 = verticesAux[i + 1];
        //glm::vec3 D = P2 - P1;
        ////verticesAux2.push_back(verticesAux[i] + D * 0.05f);
        //for (int j = 1; j < 10; j++) {
        //    float x = j;
        //    verticesAux2.push_back(verticesAux[i] + D * (x / 10.0f));
        //}
    }
    /*glm::vec3 P1 = verticesAux2[verticesAux2.size() - 1];
    glm::vec3 P2 = verticesAux2[0];
    glm::vec3 D = P2 - P1;
    for (int j = 1; j < 10; j++) {
        float x = j;
        verticesAux2.push_back(P1 + D * (x / 10.0f));
    }*/
    return verticesAux;
}

std::vector<VertexFormat> Models::CreateGroundVertices(glm::vec3 color)
{
    std::vector<VertexFormat> vertices;
    {
    };
    int k = 1;
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            vertices.push_back(VertexFormat(glm::vec3(-100, 0, -100) + glm::vec3(i * k,0, j * k), color, glm::vec3(0.2, 0.8, 0.6)));
            vertices.push_back(VertexFormat(glm::vec3(-100, 0, -100) + glm::vec3(i * k + k, 0, j * k), color, glm::vec3(0.2, 0.8, 0.6)));
            vertices.push_back(VertexFormat(glm::vec3(-100, 0, -100) + glm::vec3(i * k, 0, j * k + k), color, glm::vec3(0.2, 0.8, 0.6)));
            vertices.push_back(VertexFormat(glm::vec3(-100, 0, -100) + glm::vec3(i * k  + k, 0, j * k + k), color, glm::vec3(0.2, 0.8, 0.6)));
        }
    }
    return vertices;
}

std::vector<unsigned int> Models::CreateGroundIndices()
{
    std::vector<unsigned int> indices;
    {
    };

    for (int i = 0; i < 200*4*200; i+=4) {
            indices.push_back(i);
            indices.push_back(i+1);
            indices.push_back(i+2);

            indices.push_back(i + 3);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
    }

    return indices;
}