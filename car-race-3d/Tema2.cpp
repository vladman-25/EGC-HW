#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/Models.h"
#include "lab_m1/Tema2/transform3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

    angle = 0;
    float trackSize = 7.0f;
    
    {

        translateX = 0;
        translateY = 0.5f;
        translateZ = 0;

        angularStepOX = 0;
        angularStepOY = 0;
        angularStepOZ = 0;

        right = -2;
        left = 2;
        bottom = -1;
        top = 1;


        



        speed = 16.0f;
        unit = 0.075f;
        glm::vec3 color = glm::vec3(1, 0, 0);

        modelMatrix = glm::mat4(1);


        
        glm::vec3 trackColor = glm::vec3(0.156, 0.156, 0.156);
        glm::vec3 groundColor = glm::vec3(0.309, 0.474, 0.258);


        Mesh* car = Models::CreateCar("car", unit, color);
        AddMeshToList(car);

        Mesh* enemyCar1 = Models::CreateCar("enemyCar1", unit, glm::vec3(0, 0, 1));
        AddMeshToList(enemyCar1);

        Mesh* enemyCar2 = Models::CreateCar("enemyCar2", unit, glm::vec3(1, 0, 1));
        AddMeshToList(enemyCar2);

        Mesh* enemyCar3 = Models::CreateCar("enemyCar3", unit, glm::vec3(1, 0, 0.5));
        AddMeshToList(enemyCar3);

        Mesh* enemyCar4 = Models::CreateCar("enemyCar4", unit, glm::vec3(0.5, 0, 1));
        AddMeshToList(enemyCar4);

        Mesh* enemyCar5 = Models::CreateCar("enemyCar5", unit, glm::vec3(0.5, 0, 0.5));
        AddMeshToList(enemyCar5);
        
        Mesh* circuit = Models::CreateCircuit("circuit", trackSize, trackColor);
        AddMeshToList(circuit);

        Mesh* tree = Models::CreateTree("tree", 0.4f, glm::vec3(0, 0, 0));
        AddMeshToList(tree);

        Mesh* ground = Models::CreateGround("ground", 1.0f, groundColor);
        AddMeshToList(ground);

        Mesh* strips = Models::CreateStrips("strips", trackSize, glm::vec3(1, 1, 1));
        AddMeshToList(strips);

        treePos = Models::CreateTreePos(trackSize);
        carTraj = Models::CreateCarTraj(trackSize);
        carTraj_R = Models::CreateCarTraj_R(trackSize);
        circuitMiddle = Models::CreateCircuitMiddle(trackSize);


        
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;

        Shader* shader2 = new Shader("LabShader2");
        shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader2.glsl"), GL_VERTEX_SHADER);
        shader2->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader2->CreateAndLink();
        shaders[shader2->GetName()] = shader2;
    }
   

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(resolution.x - 300, resolution.y - 200, resolution.x / 5.f, resolution.y / 5.f);


   
    nr_enemies = carTraj.size()/2 - 2;
    int i = 0;
    for (int k = 0; k < nr_enemies; k++) {
        i += 2;
        checkpoint[k] = i;
        enemyX[k] = carTraj[i][0];
        enemyZ[k] = carTraj[i][2];
        enemyStepOY[k] = 0;
        float xs = carTraj[i + 1][0] - enemyX[k];
        float zs = carTraj[i + 1][2] - enemyZ[k];
        if (zs != 0) {
            enemyStepOY[k] = atan(xs / zs);
        }
        else {
            if (xs < 0) {
                enemyStepOY[k] -= RADIANS(180);
            }
        }

        if (zs > 0) {
            enemyStepOY[k] -= RADIANS(180);
        }
    }
    nr_enemies_R = carTraj.size()/2 - 2;
    i = 0;
    for (int k = 0; k < nr_enemies_R; k++) {
        i += 2;
        checkpoint_R[k] = i;
        enemyX_R[k] = carTraj_R[i][0];
        enemyZ_R[k] = carTraj_R[i][2];
        enemyStepOY_R[k] = 0;
        float xs = (carTraj_R[i - 1][0] - enemyX_R[k]);
        float zs = (carTraj_R[i - 1][2] - enemyZ_R[k]);
        if (zs != 0) {
            enemyStepOY_R[k] = atan(xs / zs);
        }
        else {
            if (xs < 0) {
                enemyStepOY_R[k] -= RADIANS(180);
            }
        }

        if (zs > 0) {
            enemyStepOY_R[k] -= RADIANS(180);
        }

    }

    translateX = carTraj[0][0];
    translateZ = carTraj[0][2];
    angularStepOY = enemyStepOY[0];

    camera = new testcamera::Camera();
    camera->Set(glm::vec3(carTraj[0][0] + 0, 2.0f, carTraj[0][2] + 4.0f), glm::vec3(carTraj[0][0], 1, carTraj[0][2]), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    camera->RotateThirdPerson_OY(angularStepOY);
}

bool Tema2::CheckCircuit(float posx, float posz, std::vector<glm::vec3> circuitMiddle) {
    int count = 0;
    for (int i = 0; i < circuitMiddle.size() - 1; i++) {
        glm::vec3 P1 = circuitMiddle[i];
        glm::vec3 P2 = circuitMiddle[i+1];
        glm::vec3 P3 = glm::vec3(posx, 0, posz);

        float u = ((P3.x - P1.x) * (P2.x - P1.x) + (P3.z - P1.z) * (P2.z - P1.z)) / (distance(P1, P2) * distance(P1, P2));

        if ((u < -0.1f) || (u > 1.1f)) {
            continue;
        }

        float x = P1.x + u * (P2.x - P1.x);
        float z = P1.z + u * (P2.z - P1.z);

        float d = distance(glm::vec3(x, 0, z), P3);

        glm::vec3 D = P2 - P1;
        float d2 = distance(glm::vec3(0), D);
        glm::vec3 P = cross(D, glm::vec3(0, 1, 0));
        glm::vec3 R = P1 + 3.0f * P / d2;

        if (d < distance(R,P1)){
            count++;
        }
    }
    glm::vec3 P1 = circuitMiddle[circuitMiddle.size() - 1];
    glm::vec3 P2 = circuitMiddle[0];
    glm::vec3 P3 = glm::vec3(posx, 0, posz);

    float u = ((P3.x - P1.x) * (P2.x - P1.x) + (P3.z - P1.z) * (P2.z - P1.z)) / (distance(P1, P2) * distance(P1, P2));



    float x = P1.x + u * (P2.x - P1.x);
    float z = P1.z + u * (P2.z - P1.z);

    float d = distance(glm::vec3(x, 0, z), P3);

    glm::vec3 D = P2 - P1;
    float d2 = distance(glm::vec3(0), D);
    glm::vec3 P = cross(D, glm::vec3(0, 1, 0));
    glm::vec3 R = P1 + 3.0f * P / d2;

    if (d < distance(R, P1)) {
        if ((u < -0.1f) || (u > 1.1f)) {
            count+=0;
        }
        else {
            count++;
        }
    }


    if (count > 0) {
        return true;
    }
    else {
        return false;
    }

}

bool Tema2::CheckCars(float posx, float posz) {
    int count = 0;
    for (int i = 0; i < nr_enemies; i++) {
        int x = sqrt((posx - enemyX[i]) * (posx - enemyX[i]) + (posz - enemyZ[i]) * (posz - enemyZ[i]));
        if (x < 2 * 0.5f) {
            count++;
        }
    }
    for (int i = 0; i < nr_enemies_R; i++) {
        int x = sqrt((posx - enemyX_R[i]) * (posx - enemyX_R[i]) + (posz - enemyZ_R[i]) * (posz - enemyZ_R[i]));
        if (x < 2 * 0.5f) {
            count++;
        }
    }

    if (count > 0) {
        return false;
    }
    else {
        return true;
    }

}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;

    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));


    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;


    return meshes[name];
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    

}

void Tema2::RenderScene(float deltaTimeSeconds) {
    {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
        modelMatrix *= transform3D::RotateOY(angularStepOY);
        modelMatrix *= transform3D::RotateOY(RADIANS(90));
        modelMatrix *= transform3D::Translate(6 * unit, 0, 0);
        RenderMesh(meshes["car"], shaders["LabShader"], modelMatrix);
    }
    { 
        for (int i = 0; i < nr_enemies; i++) {
            if (checkpoint[i] == carTraj.size() - 1) {
                if ((enemyX[i] < carTraj[0][0] + 0.2f) && (enemyX[i] > carTraj[0][0] - 0.2f) && (enemyZ[i] < carTraj[0][2] + 0.2f) && (enemyZ[i] > carTraj[0][2] - 0.2f)) {
                    checkpoint[i] = 0;

                    float xs = carTraj[1][0] - enemyX[i];
                    float zs = carTraj[1][2] - enemyZ[i];
                    enemyStepOY[i] = atan(xs / zs);

                    if ((xs > 0) && (zs > 0)) {
                        enemyStepOY[i] -= RADIANS(180);
                    }
                    if ((xs < 0) && (zs > 0)) {
                        enemyStepOY[i] -= RADIANS(180);
                    }
                }
            }
            else {
                if ((enemyX[i] < carTraj[checkpoint[i] + 1][0] + 0.2f) && (enemyX[i] > carTraj[checkpoint[i] + 1][0] - 0.2f) && (enemyZ[i] < carTraj[checkpoint[i] + 1][2] + 0.2f) && (enemyZ[i] > carTraj[checkpoint[i] + 1][2] - 0.2f)) {
                    checkpoint[i]++;
                    float xs, zs;

                    if (checkpoint[i] == carTraj.size() - 1) {
                        xs = carTraj[0][0] - enemyX[i];
                        zs = carTraj[0][2] - enemyZ[i];
                    }
                    else {
                        xs = carTraj[checkpoint[i] + 1][0] - enemyX[i];
                        zs = carTraj[checkpoint[i] + 1][2] - enemyZ[i];
                    }
                    enemyStepOY[i] = atan(xs / zs);


                    if ((xs > 0) && (zs > 0)) {
                        enemyStepOY[i] -= RADIANS(180);
                    }
                    if ((xs < 0) && (zs > 0)) {
                        enemyStepOY[i] -= RADIANS(180);
                    }
                }
            }
            enemyX[i] -= speed / 5 * deltaTimeSeconds * sin(enemyStepOY[i]);
            enemyZ[i] -= speed / 5 * deltaTimeSeconds * cos(enemyStepOY[i]);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(enemyX[i], translateY, enemyZ[i]);

            modelMatrix *= transform3D::RotateOY(enemyStepOY[i]);
            modelMatrix *= transform3D::RotateOY(RADIANS(90));
            modelMatrix *= transform3D::Translate(6 * unit, 0, 0);
            if (i % 5 == 0) {
                RenderMesh(meshes["enemyCar1"], shaders["LabShader"], modelMatrix);
            } else if (i % 5 == 1) {
                RenderMesh(meshes["enemyCar2"], shaders["LabShader"], modelMatrix);
            } else if (i % 5 == 2) {
                RenderMesh(meshes["enemyCar3"], shaders["LabShader"], modelMatrix);
            } else if (i % 5 == 3) {
                RenderMesh(meshes["enemyCar4"], shaders["LabShader"], modelMatrix);
            } else if (i % 5 == 4) {
                RenderMesh(meshes["enemyCar5"], shaders["LabShader"], modelMatrix);
            }
                
        }
        ///////////////////////////////////////////////
        for (int i = 0; i < nr_enemies_R; i++) {
            if (checkpoint_R[i] == 0) {
                if ((enemyX_R[i] < carTraj_R[carTraj_R.size() - 1][0] + 0.2f) && (enemyX_R[i] > carTraj_R[carTraj_R.size() - 1][0] - 0.2f) && (enemyZ_R[i] < carTraj_R[carTraj_R.size() - 1][2] + 0.2f) && (enemyZ_R[i] > carTraj_R[carTraj_R.size() - 1][2] - 0.2f)) {
                    checkpoint_R[i] = carTraj_R.size() - 1;
                    //cout << "hit car "<< i << endl;
                    float xs = -(carTraj_R[carTraj_R.size() - 2][0] - enemyX_R[i]);
                    float zs = -(carTraj_R[carTraj_R.size() - 2][2] - enemyZ_R[i]);
                    enemyStepOY_R[i] = atan(xs / zs);

                    if (zs < 0) {
                        enemyStepOY_R[i] -= RADIANS(180);
                    }
                }
            } else {
                if ((enemyX_R[i] < carTraj_R[checkpoint_R[i] - 1][0] + 0.2f) && (enemyX_R[i] > carTraj_R[checkpoint_R[i] - 1][0] - 0.2f) && (enemyZ_R[i] < carTraj_R[checkpoint_R[i] - 1][2] + 0.2f) && (enemyZ_R[i] > carTraj_R[checkpoint_R[i] - 1][2] - 0.2f)) {
                    //cout << "hit car " << i << " checkpoint" << checkpoint_R[i] - 1 << endl;
                    checkpoint_R[i]--;
                    float xs, zs;

                    if (checkpoint_R[i] == 0) {
                        xs = -(carTraj_R[carTraj_R.size() - 1][0] - enemyX_R[i]);
                        zs = -(carTraj_R[carTraj_R.size() - 1][2] - enemyZ_R[i]);
                    }
                    else {
                        xs = -(carTraj_R[checkpoint_R[i] - 1][0] - enemyX_R[i]);
                        zs = -(carTraj_R[checkpoint_R[i] - 1][2] - enemyZ_R[i]);
                    }
                    enemyStepOY_R[i] = atan(xs / zs);


                    if (zs < 0) {
                        enemyStepOY_R[i] -= RADIANS(180);
                    }
                }
                
            }
            enemyX_R[i] -= speed / 5 * deltaTimeSeconds * sin(enemyStepOY_R[i]);
            enemyZ_R[i] -= speed / 5 * deltaTimeSeconds * cos(enemyStepOY_R[i]);

            modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(enemyX_R[i], translateY, enemyZ_R[i]);
            modelMatrix *= transform3D::RotateOY(enemyStepOY_R[i]);
            modelMatrix *= transform3D::RotateOY(RADIANS(90));
            modelMatrix *= transform3D::Translate(6 * unit, 0, 0);
            if (i % 5 == 0) {
                RenderMesh(meshes["enemyCar1"], shaders["LabShader"], modelMatrix);
            }
            else if (i % 5 == 1) {
                RenderMesh(meshes["enemyCar2"], shaders["LabShader"], modelMatrix);
            }
            else if (i % 5 == 2) {
                RenderMesh(meshes["enemyCar3"], shaders["LabShader"], modelMatrix);
            }
            else if (i % 5 == 3) {
                RenderMesh(meshes["enemyCar4"], shaders["LabShader"], modelMatrix);
            }
            else if (i % 5 == 4) {
                RenderMesh(meshes["enemyCar5"], shaders["LabShader"], modelMatrix);
            }
            
        }
        //cout << " [" << enemyX_R[0] << ":" << enemyZ_R[0] << "] [" << carTraj_R[checkpoint_R[0] - 1][0] << ":" << carTraj_R[checkpoint_R[0] - 1][2] << endl;
    }
    /*{
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(enemyX + 2, translateY, enemyZ + 2);
        modelMatrix *= transform3D::RotateOY(enemyStepOY);
        modelMatrix *= transform3D::RotateOY(RADIANS(90));
        modelMatrix *= transform3D::Translate(6 * unit, 0, 0);
        RenderMesh(meshes["enemyCar2"], shaders["LabShader"], modelMatrix);
    }*/
    {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0, 0.1f, 0);
        RenderMesh(meshes["circuit"], shaders["LabShader"], modelMatrix);
    }
    {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0, -0.01f, 0);
        RenderMesh(meshes["ground"], shaders["LabShader"], modelMatrix);
    }
    {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0, 0.12f, 0);
        RenderMesh(meshes["strips"], shaders["LabShader"], modelMatrix);
    }
    {
        for (int i = 0; i < treePos.size(); i++) {
            modelMatrix = glm::mat4(1);
            modelMatrix *= transform3D::Translate(treePos[i][0], treePos[i][1], treePos[i][2]);
            RenderMesh(meshes["tree"], shaders["LabShader"], modelMatrix);
        }
    }
}


void Tema2::Update(float deltaTimeSeconds)
{

    glClearColor(0.52, 0.80, 0.92, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    /*camera->Set(glm::vec3(0, 2.0f, 4.0f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));*/
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    glViewport(0, 0, resolution.x, resolution.y);
    RenderScene(deltaTimeSeconds);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    glm::vec3 camPos = camera->position;
    glm::vec3 camFw = camera->forward;
    glm::vec3 camUp = camera->up;
    glm::vec3 camRi = camera->right;

    camera->Set(glm::vec3(translateX + 2.0f, 10.0f, translateZ + 1.0f), glm::vec3(translateX, 2, translateZ), glm::vec3(0, 1, 0));

    projectionMatrix = glm::ortho(-20.0f, 20.0f,-10.0f, 10.0f, 0.01f, 200.0f);
    RenderScene(deltaTimeSeconds);
    camera->position = camPos;
    camera->forward = camFw;
    camera->up = camUp;
    camera->right = camRi;
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);


}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    int location = glGetUniformLocation(shader->program, "Model");
    int location2 = glGetUniformLocation(shader->program, "View");
    int location3 = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int location4 = glGetUniformLocation(shader->program, "pos_car");
    glm::vec3 pos_car = glm::vec3(translateX, translateY, translateZ);
    glUniform3fv(location4, 1, glm::value_ptr(pos_car));

    mesh->Render();

}




void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Add key press event

   
        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            float z = translateZ - deltaTime * speed * cos(angularStepOY);
            float x = translateX - deltaTime * speed * sin(angularStepOY);
            if ((CheckCircuit(x,z,circuitMiddle) == true)&&(CheckCars(x,z))) {
                camera->MoveForward(deltaTime * speed);
                translateZ -= deltaTime * speed * cos(angularStepOY);
                translateX -= deltaTime * speed * sin(angularStepOY);
            }
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            if (CheckCars(translateX, translateZ)) {
                angularStepOY += deltaTime;
                //camera->MoveForward(deltaTime * cameraSpeed);
                camera->RotateThirdPerson_OY(deltaTime);
            }
        }

        if (window->KeyHold(GLFW_KEY_S) == true) {
            // TODO(student): Translate the camera backward
            float z = translateZ + deltaTime * speed * cos(angularStepOY);
            float x = translateX + deltaTime * speed * sin(angularStepOY);
            if ((CheckCircuit(x, z, circuitMiddle) == true) && (CheckCars(x, z))) {
                camera->MoveForward(-deltaTime * speed);
                translateZ += deltaTime * speed * cos(angularStepOY);
                translateX += deltaTime * speed * sin(angularStepOY);
            }
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            if (CheckCars(translateX, translateZ)) {
                angularStepOY -= deltaTime;
                //camera->MoveForward(deltaTime * cameraSpeed);
                camera->RotateThirdPerson_OY(-deltaTime);
            }

        }
    
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
