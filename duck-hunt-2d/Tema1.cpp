#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/Duck.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
    temptime = 0;
    sense = 1;
    start = 1;
    posx = 0;
    angle = 0;
    posy = 0;
    resx = 0;
    resy = 0;
    v = 200;
    vsense = 1;
    hsense = 1;
    turning = 0;
    ducksize = 250;
    duckL = 250;
    duckH = 50;
    angle90 = 0;
    angle = 0;
    duckState = 1;
    totalTime = 0;
    multiplier = 0;
    mX = 0;
    mY = 0;
    centerX = 0;
    centerY = 0;
    totalTimeSun = 0;
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;


    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    resx = resolution.x;
    resy = resolution.y;
    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;
    nrLives = 3;
    srand(time(NULL));
    bullets = 3;
    score = 0;


    {
       
        glm::vec3 brown = glm::vec3(0.2, 0.1, 0.1);
        glm::vec3 green = glm::vec3(0.2, 0.36, 0.2);
        glm::vec3 yellow = glm::vec3(0.89, 0.81, 0.03);

        xc = resolution.x / 2 - 100;;
        posx = resolution.x/2 -100;
        posy = 0;

        glm::vec3 g1 = glm::vec3(0.368, 0.549 ,0.192);
        glm::vec3 g2 = glm::vec3(0.160, 0.588, 0.090);
        glm::vec3 g3 = glm::vec3(0, 0.4, 0);
        glm::vec3 g4 = glm::vec3(0.89, 0.81, 0.03);

        glm::vec3 gray = glm::vec3(0.501, 0.501, 0.501);
      

        Mesh* click = Duck::CreateTriangle("click", glm::vec3(0, 0, 0), 20, glm::vec3(1, 0, 0), true);
        AddMeshToList(click);

        Mesh* duckCenter = Duck::CreateTriangle("duckCenter", glm::vec3(0, 0, 0), 20, glm::vec3(0, 0, 1), true);
        AddMeshToList(duckCenter);

        Mesh* body2 = Duck::CreateBody("body2", glm::vec3(0, 0, 0), 30, brown, gray, true);
        AddMeshToList(body2);
        Mesh* head2 = Duck::CreateHead("head2", glm::vec3(0, 0, 0), 30, green, true);
        AddMeshToList(head2);
        Mesh* beak2 = Duck::CreateBeak("beak2", glm::vec3(0, 0, 0), 30, yellow, true);
        AddMeshToList(beak2);
        Mesh* lwing = Duck::CreateLWing("lwing", glm::vec3(0, 0, 0), 30, green, brown, true);
        AddMeshToList(lwing);
        Mesh* rwing = Duck::CreateRWing("rwing", glm::vec3(0, 0, 0), 30, green, brown, true);
        AddMeshToList(rwing);
        Mesh* heart = Duck::CreateHeart("heart", glm::vec3(0, 0, 0), 30, glm::vec3(1, 0, 0), true);
        AddMeshToList(heart);
        Mesh* bullet = Duck::CreateBullet("bullet", glm::vec3(0, 0, 0), 30, yellow, true);
        AddMeshToList(bullet);
        Mesh* scoreFrame = Duck::CreateSquare("scoreFrame", glm::vec3(0, 0, 0), 30, glm::vec3(0,0,1), false);
        AddMeshToList(scoreFrame);
        Mesh* scorefill = Duck::CreateSquare("scorefill", glm::vec3(0, 0, 0), 30, glm::vec3(0, 0, 1), true);
        AddMeshToList(scorefill);
        Mesh* cursor = Duck::CreateCursor("cursor", glm::vec3(0, 0, 0), 30, glm::vec3(0, 0, 1), true);
        AddMeshToList(cursor);
        Mesh* gun = Duck::CreateGun("gun", glm::vec3(0, 0, 0), 30, brown, true);
        AddMeshToList(gun);

        Mesh* frontgrass = Duck::CreateFrontGrass("frontgrass", glm::vec3(0, 0, 0), 30, g2, g1, true);
        AddMeshToList(frontgrass);

        Mesh* behindgrass = Duck::CreateBehindGrass("behindgrass", glm::vec3(0, 0, 0), 30, g3, true);
        AddMeshToList(behindgrass);


        Mesh* sunray = Duck::CreateSunRay("sunray", glm::vec3(0, 0, 0), 30, yellow, true);
        AddMeshToList(sunray);
        Mesh* moonray = Duck::CreateMoonRay("moonray", glm::vec3(0, 0, 0), 30, glm::vec3(1, 1, 1), true);
        AddMeshToList(moonray);

        moves = glm::mat3(1);
        
        //moves *= transform2D::Translate(posx, posy) * transform2D::Rotate(3.14 / 2);
    }

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    if (totalTimeSun < 3.14) {
        glClearColor(0.3, 0.7, 1, 1);
    }
    if (totalTimeSun > 3.14) {
        glClearColor(0.019, 0.019, 0.168, 1);
    }
    if (totalTimeSun > 6.28) {
        totalTimeSun -= 6.28;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds) 
{


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    modelMatrix *= transform2D::Rotate(atan(mY/mX));
    modelMatrix *= transform2D::Scale(20, 20);
    RenderMesh2D(meshes["gun"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(mX - 17, mY - 20);
    modelMatrix *= transform2D::Scale(6, 6);
    RenderMesh2D(meshes["cursor"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(30, resy - 50);
    modelMatrix *= transform2D::Scale(10, 1);
    RenderMesh2D(meshes["scoreFrame"], shaders["VertexColor"], modelMatrix);
    modelMatrix = glm::mat3(1);
    for (int i = 0; i < score; i++) {
        modelMatrix = transform2D::Translate(30 + i * 30, resy - 50);
        modelMatrix *= transform2D::Scale(1, 1);
        RenderMesh2D(meshes["scorefill"], shaders["VertexColor"], modelMatrix);
    }




    modelMatrix = glm::mat3(1);
    for (int i = 0; i < 40; i++) {
        modelMatrix = transform2D::Translate(i * 100, 0)
            * transform2D::Scale(50, 50);
        RenderMesh2D(meshes["frontgrass"], shaders["VertexColor"], modelMatrix);
    }


    modelMatrix = glm::mat3(1);
    for (int i = 0; i < nrLives; i++) {
        modelMatrix = transform2D::Translate(resx - 200 + i * 60, resy - 70);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }
    modelMatrix = glm::mat3(1);
    for (int i = 0; i < bullets; i++) {
        modelMatrix = transform2D::Translate(resx - 190 + i * 60, resy - 130);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    

    if (angularStep > 0.5) {
        sense = -1;
        angularStep = 0.5;
    }
    if (angularStep < 0) {
        sense = 2;
        angularStep = 0;
    }

    



    if ((angle90 == 0)&&(duckState == 1)) {
        angle90 = (((rand() % 5) + 3) * 3.14 / 20);
        angle = angle90;
        if (rand() % 2 == 1) {
            angle = 3.14 - angle90;
        }


        if (angle > 3.14 / 2) {
            vsense = -1;
            hsense = 1;
        }
        else {
            vsense = 1;
            hsense = 1;
        }
        bullets = 3;
    }


   

    totalTime += deltaTimeSeconds;
    if ((totalTime > 5)&&(duckState == 1)) {
        duckState = 2;
        nrLives--;
    }

    v = deltaTimeSeconds * 400;
    v += (v * multiplier) / 5;

    if (duckState == 1) {

        if ((posx > resx - duckL / 2) && (vsense == 1)) {
            vsense = -vsense;
            posx = resx + duckL / 2;
            posy += duckH;
            angle = 3.14 - angle;
            if (angle > 6.28) {
                angle -= 6.28;
            }
            if (angle < 0) {
                angle += 6.28;
            }
        }
        if ((posx < duckL / 2) && (vsense == -1)) {
            vsense = -vsense;
            posx = -duckL / 2;
            posy -= duckH;
            angle = 3.14 - angle;
            if (angle > 6.28) {
                angle -= 6.28;
            }
            if (angle < 0) {
                angle += 6.28;
            }
        }

        if ((posy > resy - duckH / 2) && (hsense == 1)) {
            hsense = -hsense;
            posy = resy;
            angle = -angle;
            if (angle > 6.28) {
                angle -= 6.28;
            }
            if (angle < 0) {
                angle += 6.28;
            }
        }
        if ((posy < duckH / 2) && (hsense == -1)) {
            hsense = -hsense;
            posy = 0;
            angle = -angle;
            if (angle > 6.28) {
                angle -= 6.28;
            }
            if (angle < 0) {
                angle += 6.28;
            }
        }


        posx += (vsense * v) * cos(angle90);
        posy += (hsense * v) * sin(angle90);
    }


    else if (duckState == 2) {
        posx += 0;
        posy += v;
        angle = 3.14 / 2 + 0.2;

        if (posy > resy) {
            vsense = 1;
            hsense = 1;
            angle = 0.4;
            posx = xc;
            posy = 0;
            duckState = 1;
            totalTime = 0;
            angle = 0;
            angle90 = 0;
        }

    }
    else if (duckState == 3) {
        posx += 0;
        posy -= v;
        angle = -3.14 / 2;

        if (posy < 0) {
            vsense = 1;
            hsense = 1;
            angle = 0.4;
            posx = xc;
            posy = 0;
            duckState = 1;
            totalTime = 0;
            angle = 0;
            angle90 = 0;
            multiplier++;
        }

    }
    
    
   
    moves = transform2D::Translate(posx, posy) * transform2D::Rotate(angle);
    if ((angle > 3.14 / 2) && (angle < 3.14)) {
        moves *= transform2D::Scale(1, -1);
    }
    if ((angle > 3.14) && (angle < 3.14 * 3 / 2)) {
        moves *= transform2D::Scale(1, -1);
    }

    angularStep += sense * deltaTimeSeconds * (1 +multiplier / 5);
    

    modelMatrix = glm::mat3(1);
    modelMatrix *= moves * transform2D::Scale(10, 10);
    RenderMesh2D(meshes["body2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["head2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["beak2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= moves *
        transform2D::Scale(10, 10)
        * transform2D::Translate(12, 8)
        * transform2D::Rotate(angularStep)
        * transform2D::Translate(-12, -8);
    RenderMesh2D(meshes["lwing"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= moves *
        transform2D::Scale(10, 10)
        * transform2D::Translate(12, 8)
        * transform2D::Rotate(-angularStep)
        * transform2D::Translate(-12, -8);
    RenderMesh2D(meshes["rwing"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    for (int i = 0; i < 40; i++) {
        modelMatrix = transform2D::Translate(i * 50, 0)
            * transform2D::Scale(50, 50);
        RenderMesh2D(meshes["behindgrass"], shaders["VertexColor"], modelMatrix);
    }

    totalTimeSun += deltaTimeSeconds;
    


    modelMatrix = glm::mat3(1);
    for (int i = 0; i < 16; i++) {
        modelMatrix = transform2D::Translate(resx/2, 0) * transform2D::Rotate(totalTimeSun) * transform2D::Translate(resx/2, 0) * transform2D::Rotate(-RADIANS(i * 360 / 16))
            * transform2D::Scale(30, 30);
        RenderMesh2D(meshes["sunray"], shaders["VertexColor"], modelMatrix);

    }

    modelMatrix = glm::mat3(1);
    for (int i = 0; i < 10; i++) {
        modelMatrix = transform2D::Translate(resx / 2, 0) * transform2D::Rotate(totalTimeSun + M_PI) * transform2D::Translate(resx / 2, 0) * transform2D::Rotate(-RADIANS(i * 360 / 10))
            * transform2D::Scale(20, 20);
        RenderMesh2D(meshes["moonray"], shaders["VertexColor"], modelMatrix);

    }

    ///////////////////
    
    
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mX = mouseX;
    mY = resy - mouseY;
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    mX = mouseX;
    mY = resy - mouseY;

    float angle1 = atan(duckH/duckL);
    float angle2 = angle;
    float angleRes = angle1 + angle2;
    float R = sqrt(duckH * duckH + duckL * duckL) / 2;

    
    centerX = posx + (R * cos(angleRes));
    centerY = posy + (R * sin(angleRes));

    if ((duckState == 1)&&(bullets > 0)) {
             
            if ((mX > centerX - duckL/2)&& (mX < centerX + duckL / 2)&& (mY > centerY - duckL / 2) && (mY < centerY + duckL / 2)) {
                duckState = 3;
                score++;
            }
            
           /* if (abs(centerX - mX) * abs(centerX - mX) + abs(centerY - mY) * abs(centerY - mY) < R * R) {
                duckState = 3;
                score++;
            }*/
    }
    bullets--;
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
