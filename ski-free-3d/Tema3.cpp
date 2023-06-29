#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "crate.jpg").c_str(), GL_REPEAT);
        mapTextures["crate"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "gift.jpg").c_str(), GL_REPEAT);
        mapTextures["gift"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snow2.jpg").c_str(), GL_REPEAT);
        mapTextures["snow"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "brad.png").c_str(), GL_REPEAT);
        mapTextures["brad"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "metal.jpg").c_str(), GL_REPEAT);
        mapTextures["metal"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "stone2.jpg").c_str(), GL_REPEAT);
        mapTextures["stone"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "ski.jpg").c_str(), GL_REPEAT);
        mapTextures["ski"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "skier.jpg").c_str(), GL_REPEAT);
        mapTextures["skier"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "wood.jpeg").c_str(), GL_REPEAT);
        mapTextures["wood"] = texture;
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("cone");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cone.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }


    // Create a simple quad
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(1.f,   1.f, 0.0f),    // top right
            glm::vec3(1.f,  -1.f, 0.0f),    // bottom right
            glm::vec3(-1.f, -1.f, 0.0f),    // bottom left
            glm::vec3(-1.f,  1.f, 0.0f),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };
        unit = 4.0f;
        text_x = 0.0f;
        text_y = 0.0f;
        textureCoords = 
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(text_x, text_y),
            glm::vec2(text_x, unit + text_y),
            glm::vec2(unit + text_x, unit + text_y),
            glm::vec2(unit + text_x, text_y),
        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    treeCords = {};
    for (int i = 0; i < 5; i++) {
        int x = rand() % 30 - 15;
        int y = rand() % 24 - 3;
        treeCords.push_back({ x, y });
    }
    presentCords = {};
    for (int i = 0; i < 5; i++) {
        int x = rand() % 30 - 15;
        int y = rand() % 24 - 3;
        presentCords.push_back({ x, y });
    }
    poleCords = {};
    for (int i = 0; i < 3; i++) {
        int x = rand() % 30 - 15;
        int y = rand() % 24 - 3;
        poleCords.push_back({ x, y });
    }
    stoneCords = {};
    for (int i = 0; i < 3; i++) {
        int x = rand() % 30 - 15;
        int y = rand() % 24 - 3;
        stoneCords.push_back({ x, y });
    }

    time = 0;
    time_y = 0;
    mX = 0;
    mY = 0;
    glm::ivec2 resolution = window->GetResolution();
    resx = resolution.x;
    resy = resolution.y;
    angle = 0;
    nr_lights = 0;
    score = 0;
    {   
        lightPosition[0] = glm::vec3(0, -6, 0);
        lightColor[0] = glm::vec3(1, 0, 0);
        nr_lights++;

        {
            lightPosition[0] = glm::vec3(lightPosition[0].x,  8, lightPosition[0].y);
            float x = lightPosition[0].x;
            float y = lightPosition[0].y;
            float z = lightPosition[0].z;
            float xp = x;
            float yp = y * cos(RADIANS(-50.0f)) - z * sin(RADIANS(-50.0f));
            float zp = y * sin(RADIANS(-50.0f)) + z * cos(RADIANS(-50.0f));
            lightPosition[0] = glm::vec3(xp, yp, zp);
        }
        playerPos = glm::vec3(lightPosition[0].x, lightPosition[0].y + 7, lightPosition[0].z);

        // /* Debug coords*/
        lightPosition[0] = glm::vec3(0.0f, 1, -10.0f);
        for (int i = 0; i < treeCords.size(); i++) {
            lightPosition[nr_lights] = glm::vec3(treeCords[i].x, .5f, treeCords[i].y);
            lightColor[nr_lights] = glm::vec3(0, 1, 0);
            spotlight[nr_lights] = 0;
            nr_lights++;
            
        }
        for (int i = 0; i < presentCords.size(); i++) {
            lightPosition[nr_lights] = glm::vec3(presentCords[i].x, .5f, presentCords[i].y);
            lightColor[nr_lights] = glm::vec3(0, 0, 1);
            spotlight[nr_lights] = 0;
            nr_lights++;
        }
        for (int i = 0; i < poleCords.size(); i++) {
            lightPosition[nr_lights] = glm::vec3(poleCords[i].x - 1.0f, 4.0f, poleCords[i].y);
            lightColor[nr_lights] = glm::vec3(1, 1, 1);
            spotlight[nr_lights] = 1;
            nr_lights++;
            lightPosition[nr_lights] = glm::vec3(poleCords[i].x - 1.0f, 4.0f, poleCords[i].y);
            lightColor[nr_lights] = glm::vec3(1, 1, 1);
            spotlight[nr_lights] = 1;
            nr_lights++;
        }
        //cout << nr_lights;
       
        lightDirection = glm::vec3(0, -1, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }

    run = true;
}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema3::Update(float deltaTimeSeconds)
{
    // TODO(student): Choose an object and add a second texture to it.
    // For example, for the sphere, you can have the "earth" texture
    // and the "random" texture, and you will use the `mix` function
    // in the fragment shader to mix these two textures.
    //
    // However, you may have the unpleasant surprise that the "random"
    // texture now appears onto all objects in the scene, even though
    // you are only passing the second texture for a single object!
    // Why does this happen? How can you solve it?
    if (run) {
        angle = atan(((resy + 250) / 2 - mY) / (resx / 2 - mX));
        time += deltaTimeSeconds * (1 - cos(angle));
        if (mX > resx / 2) {
            time_y += deltaTimeSeconds * -cos(angle);
        }
        else if (mX < resx / 2) {
            time_y += deltaTimeSeconds * cos(angle);
        }
    }

    for (int i = 0; i < treeCords.size(); i++) {
        if (run) {
            treeCords[i].y += deltaTimeSeconds * (1 - cos(angle)) * 5;
            if (mX > resx / 2) {
                treeCords[i].x -= cos(angle) * 0.2;
            }
            else if (mX < resx / 2) {
                treeCords[i].x += cos(angle) * 0.2;
            }
            if (treeCords[i].y >= 21) {
                int x = rand() % 30 - 15;
                int y = -1.5;
                treeCords[i] = { x, y };
            }
            if (treeCords[i].x > 15) {
                int x = -15;
                int y = treeCords[i].y;
                treeCords[i] = { x, y };
            }
            if (treeCords[i].x < -15) {
                int x = 15;
                int y = treeCords[i].y;
                treeCords[i] = { x, y };
            }

            if ((playerPos.x < treeCords[i].x + 0.75f) &&
                (playerPos.x + 0.75f > treeCords[i].x) &&
                (playerPos.y < treeCords[i].y + 0.75f) &&
                (playerPos.y + 0.75f > treeCords[i].y)) {

                cout << endl << "Scorul tau este:" << score << endl;
                run = false;
            }
        }

        lightPosition[i + 1] = glm::vec3(treeCords[i].x, treeCords[i].y + 0.75f, -5.2f);
        float x = lightPosition[i + 1].x;
        float y = lightPosition[i + 1].y;
        float z = lightPosition[i + 1].z;
        float xp = x;
        float yp = y * cos(RADIANS(-50.0f)) - z * sin(RADIANS(-50.0f));
        float zp = y * sin(RADIANS(-50.0f)) + z * cos(RADIANS(-50.0f));
        lightPosition[i + 1] = glm::vec3(xp, yp, zp);

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(treeCords[i].x, treeCords[i].y + 1.0f, -4.5f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(50), glm::vec3(1, 0, 0));
        RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, mapTextures["brad"], mapTextures["brad"], 0);
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(treeCords[i].x, treeCords[i].y + 1.5f, -3.8f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(50), glm::vec3(1, 0, 0));
        RenderSimpleMesh(meshes["cone"], shaders["LabShader"], modelMatrix, mapTextures["brad"], mapTextures["brad"], 0);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(treeCords[i].x, treeCords[i].y + 0.0f, -5.8f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(50), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 4.0f, 0.4f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["wood"], mapTextures["wood"], 0);
    }

    for (int i = 0; i < presentCords.size(); i++) {
        if (run) {
            presentCords[i].y += deltaTimeSeconds * (1 - cos(angle)) * 5;
            if (mX > resx / 2) {
                presentCords[i].x -= cos(angle) * 0.2;
            }
            else if (mX < resx / 2) {
                presentCords[i].x += cos(angle) * 0.2;
            }
            if (presentCords[i].y >= 21) {
                int x = rand() % 30 - 15;
                int y = -1.5;
                presentCords[i] = { x, y };
            }
            if (presentCords[i].x > 15) {
                int x = -15;
                int y = presentCords[i].y;
                presentCords[i] = { x, y };
            }
            if (presentCords[i].x < -15) {
                int x = 15;
                int y = presentCords[i].y;
                presentCords[i] = { x, y };
            }

            if ((playerPos.x < presentCords[i].x + 0.75f) &&
                (playerPos.x + 0.75f > presentCords[i].x) &&
                (playerPos.y < presentCords[i].y + 0.75f) &&
                (playerPos.y + 0.75f > presentCords[i].y)) {

                score++;
                /*cout << score << endl;*/
                int x = rand() % 30 - 15;
                int y = -1.5;
                presentCords[i] = { x, y };
            }
        }


        int iter = treeCords.size() + i + 1;
        lightPosition[iter] = glm::vec3(presentCords[i].x, presentCords[i].y + 1, -5.6f);
        float x = lightPosition[iter].x;
        float y = lightPosition[iter].y;
        float z = lightPosition[iter].z;
        float xp = x;
        float yp = y * cos(RADIANS(-50.0f)) - z * sin(RADIANS(-50.0f));
        float zp = y * sin(RADIANS(-50.0f)) + z * cos(RADIANS(-50.0f));
        lightPosition[iter] = glm::vec3(xp, yp, zp);
        //cout << treeCords.size() + i + 1 << endl;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(presentCords[i].x, presentCords[i].y + 1.0f, -5.5f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["gift"], mapTextures["gift"]);

    }

    {
        for (int i = 0; i < poleCords.size(); i++) {
            if (run) {
                poleCords[i].y += deltaTimeSeconds * (1 - cos(angle)) * 5;
                if (mX > resx / 2) {
                    poleCords[i].x -= cos(angle) * 0.2;
                }
                else if (mX < resx / 2) {
                    poleCords[i].x += cos(angle) * 0.2;
                }
                if (poleCords[i].y >= 21) {
                    int x = rand() % 30 - 15;
                    int y = -1.5;
                    poleCords[i] = { x, y };
                }
                if (poleCords[i].x > 15) {
                    int x = -15;
                    int y = poleCords[i].y;
                    poleCords[i] = { x, y };
                }
                if (poleCords[i].x < -15) {
                    int x = 15;
                    int y = poleCords[i].y;
                    poleCords[i] = { x, y };
                }

                if ((playerPos.x < poleCords[i].x + 0.3f) &&
                    (playerPos.x + 0.3f > poleCords[i].x) &&
                    (playerPos.y < poleCords[i].y + 0.3f) &&
                    (playerPos.y + 0.3f > poleCords[i].y)) {

                    cout << endl << "Scorul tau este:" << score << endl;
                    run = false;
                }
            }



            int iter = treeCords.size() + presentCords.size() + i*2 + 1;
            lightPosition[iter] = glm::vec3(poleCords[i].x + 1.0f, poleCords[i].y, -5.4f);
            float x = lightPosition[iter].x;
            float y = lightPosition[iter].y;
            float z = lightPosition[iter].z;
            float xp = x;
            float yp = y * cos(RADIANS(-50.0f)) - z * sin(RADIANS(-50.0f));
            float zp = y * sin(RADIANS(-50.0f)) + z * cos(RADIANS(-50.0f));
            lightPosition[iter] = glm::vec3(xp, yp + 4, zp);

            lightPosition[iter+1] = glm::vec3(poleCords[i].x - 1.0f, poleCords[i].y, -5.4f);
            x = lightPosition[iter + 1].x;
            y = lightPosition[iter + 1].y;
            z = lightPosition[iter + 1].z;
            xp = x;
            yp = y * cos(RADIANS(-50.0f)) - z * sin(RADIANS(-50.0f));
            zp = y * sin(RADIANS(-50.0f)) + z * cos(RADIANS(-50.0f));
            lightPosition[iter + 1] = glm::vec3(xp, yp + 4, zp);


            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(poleCords[i].x + 0.0f, poleCords[i].y + 0.5f, -4.5f));

            modelMatrix = glm::rotate(modelMatrix, RADIANS(50), glm::vec3(1, 0, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 4.0f, 0.2f));
            RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["metal"], mapTextures["metal"], 0);

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(poleCords[i].x + 0.0f, poleCords[i].y + 0.5f, -1.5f));

            modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.0f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(3.0f, 0.2f, 0.2f));
            RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["metal"], mapTextures["metal"], 0);
        }
    }

    {   
        for (int i = 0; i < stoneCords.size(); i++) {

            if (run) {
                stoneCords[i].y += deltaTimeSeconds * (1 - cos(angle)) * 5;
                if (mX > resx / 2) {
                    stoneCords[i].x -= cos(angle) * 0.2;
                }
                else if (mX < resx / 2) {
                    stoneCords[i].x += cos(angle) * 0.2;
                }
                if (stoneCords[i].y >= 21) {
                    int x = rand() % 30 - 15;
                    int y = -1.5;
                    stoneCords[i] = { x, y };
                }
                if (stoneCords[i].x > 15) {
                    int x = -15;
                    int y = stoneCords[i].y;
                    stoneCords[i] = { x, y };
                }
                if (stoneCords[i].x < -15) {
                    int x = 15;
                    int y = stoneCords[i].y;
                    stoneCords[i] = { x, y };
                }

                if ((playerPos.x < stoneCords[i].x + 1) &&
                    (playerPos.x + 0.2f > stoneCords[i].x) &&
                    (playerPos.y < stoneCords[i].y + 1) &&
                    (playerPos.y + 0.2f > stoneCords[i].y)) {

                    cout << endl << "Scorul tau este:" << score << endl;
                    run = false;
                }
            }

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(stoneCords[i].x, stoneCords[i].y - 4.0f, -6.0f));

            modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25f, 5, 0));
            RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, mapTextures["stone"], mapTextures["stone"], 0);
            modelMatrix = glm::mat4(1);
            modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1, 0, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(stoneCords[i].x, stoneCords[i].y - 4.0f, -6.0f));

            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.25f, 5, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
            RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, mapTextures["stone"], mapTextures["stone"], 0);
        }
    }

    {   

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, -10.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(40.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, angle + RADIANS(90), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.75f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 1.5f, 0.3f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["skier"], mapTextures["skier"], 0);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, -10.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(40.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, angle + RADIANS(90), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25f, 0,0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.1f, 2.0f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["ski"], mapTextures["ski"], 0);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, -10.0f));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(40.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, angle + RADIANS(90), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.25f, 0,0 ));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.1f, 2.0f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, mapTextures["ski"], mapTextures["ski"], 0);
    }
    
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.5f, -10.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(20));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(-50), glm::vec3(1,0,0));
        RenderSimpleMesh(meshes["square"], shaders["LabShader"], modelMatrix, mapTextures["snow"],mapTextures["snow"],1);
    }

}


void Tema3::FrameEnd()
{
    //DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2, int Earth, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_position, nr_lights, glm::value_ptr(lightPosition[0]));

    int light_position2 = glGetUniformLocation(shader->program, "light_color");
    glUniform3fv(light_position2, nr_lights, glm::value_ptr(lightColor[0]));

    int light_position3 = glGetUniformLocation(shader->program, "spotlight_on");
    glUniform1iv(light_position3, nr_lights, &spotlight[0]);

    int light_nrposition = glGetUniformLocation(shader->program, "light_nr");
    glUniform1i(light_nrposition, nr_lights);
    //cout << nr_lights;
    int light_direction = glGetUniformLocation(shader->program, "light_direction");

    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);



    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    //if (texture2)
    //{
    //    // TODO(student): Do these:
    //    // - activate texture location 1
    //    // - bind the texture2 ID
    //    // - send the uniform value
    //    glActiveTexture(GL_TEXTURE1);
    //    glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
    //    glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
    //}
    int location = glGetUniformLocation(shader->program, "Time");

    glUniform1f(location, time);

    int locationy = glGetUniformLocation(shader->program, "TimeY");

    glUniform1f(locationy, time_y);

    int location2 = glGetUniformLocation(shader->program, "Earth");
    glUniform1i(location2, Earth);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 256;
    }
    
    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);


    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);
    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    if ((key == GLFW_KEY_R) && (run == false)) {
        run = true;
        score = 0;


        treeCords = {};
        for (int i = 0; i < 5; i++) {
            int x = rand() % 30 - 15;
            int y = rand() % 24 - 3;
            treeCords.push_back({ x, y });
        }
        presentCords = {};
        for (int i = 0; i < 5; i++) {
            int x = rand() % 30 - 15;
            int y = rand() % 24 - 3;
            presentCords.push_back({ x, y });
        }
        poleCords = {};
        for (int i = 0; i < 3; i++) {
            int x = rand() % 30 - 15;
            int y = rand() % 24 - 3;
            poleCords.push_back({ x, y });
        }
        stoneCords = {};
        for (int i = 0; i < 3; i++) {
            int x = rand() % 30 - 15;
            int y = rand() % 24 - 3;
            stoneCords.push_back({ x, y });
        }

        nr_lights = 0;
        {
            lightPosition[0] = glm::vec3(0, -6, 0);
            lightColor[0] = glm::vec3(1, 0, 0);
            nr_lights++;

            {
                lightPosition[0] = glm::vec3(lightPosition[0].x, 8, lightPosition[0].y);
                float x = lightPosition[0].x;
                float y = lightPosition[0].y;
                float z = lightPosition[0].z;
                float xp = x;
                float yp = y * cos(RADIANS(-50.0f)) - z * sin(RADIANS(-50.0f));
                float zp = y * sin(RADIANS(-50.0f)) + z * cos(RADIANS(-50.0f));
                lightPosition[0] = glm::vec3(xp, yp, zp);
            }
            playerPos = glm::vec3(lightPosition[0].x, lightPosition[0].y + 7, lightPosition[0].z);

            // /* Debug coords*/
            for (int i = 0; i < treeCords.size(); i++) {
                lightPosition[nr_lights] = glm::vec3(treeCords[i].x, .5f, treeCords[i].y);
                lightColor[nr_lights] = glm::vec3(0, 1, 0);
                spotlight[nr_lights] = 0;
                nr_lights++;

            }
            for (int i = 0; i < presentCords.size(); i++) {
                lightPosition[nr_lights] = glm::vec3(presentCords[i].x, .5f, presentCords[i].y);
                lightColor[nr_lights] = glm::vec3(0, 0, 1);
                spotlight[nr_lights] = 0;
                nr_lights++;
            }
            for (int i = 0; i < poleCords.size(); i++) {
                lightPosition[nr_lights] = glm::vec3(poleCords[i].x - 1.0f, 4.0f, poleCords[i].y);
                lightColor[nr_lights] = glm::vec3(1, 1, 1);
                spotlight[nr_lights] = 1;
                nr_lights++;
                lightPosition[nr_lights] = glm::vec3(poleCords[i].x - 1.0f, 4.0f, poleCords[i].y);
                lightColor[nr_lights] = glm::vec3(1, 1, 1);
                spotlight[nr_lights] = 1;
                nr_lights++;
            }
        }


    }
    // Add key press event
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    mX = mouseX;
    mY = resy - mouseY;
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
