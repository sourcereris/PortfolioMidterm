#include "raylib.h"
#include <cmath>

Vector4 MultiplyMatrices(float projMat[4][4],const Vector4 &vertices){
    Vector4 result;

    result.x = projMat[0][0] * vertices.x + projMat[0][1] * vertices.y + projMat[0][2] * vertices.z + projMat[0][3] * vertices.w;
    result.y = projMat[1][0] * vertices.x + projMat[1][1] * vertices.y + projMat[1][2] * vertices.z + projMat[1][3] * vertices.w;
    result.z = projMat[2][0] * vertices.x + projMat[2][1] * vertices.y + projMat[2][2] * vertices.z + projMat[2][3] * vertices.w;
    result.w = projMat[3][0] * vertices.x + projMat[3][1] * vertices.y + projMat[3][2] * vertices.z + projMat[3][3] * vertices.w;

    return result;
}

Vector4 Project(float projMat[4][4],const Vector4& vertices){
    Vector4 projection = MultiplyMatrices(projMat, vertices);

    if(projection.w != 0) {
        projection.x /= projection.w;
        projection.y /= projection.w;
        projection.z /= projection.w;
    }

    return projection;
}

void RotateX(float angle, float rotMatrix[4][4]){
        
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    
    rotMatrix[1][1] = cosAngle;
    rotMatrix[1][2] = -sinAngle;
    rotMatrix[2][1] = sinAngle;
    rotMatrix[2][2] = cosAngle;
    
}
void RotateY(float angle, float rotMatrix[4][4]){

    float sinAngle = sin(angle);
    float cosAngle = cos(angle);

    rotMatrix[0][0] = cosAngle;
    rotMatrix[0][2] = -sinAngle;
    rotMatrix[2][0] = sinAngle;
    rotMatrix[2][2] = cosAngle;
}

int main() {

    Vector4 cubeVertices[8] = {
        {-1.0f, 1.0f, 1.0f, 1.0f},
        { 1.0f, 1.0f, 1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f, 1.0f},
        { 1.0f,-1.0f, 1.0f, 1.0f},

        {-1.0f, 1.0f,-1.0f, 1.0f},
        { 1.0f, 1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f,-1.0f, 1.0f},
        { 1.0f,-1.0f,-1.0f, 1.0f}
    };

    float projectionMatrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 6, 0},
        {0, 0, -0.5, 2}
    };

    int lines[12][2] = {
        {0, 1}, {0, 2}, {1, 3},{2, 3},
        {4, 5}, {4, 6}, {5, 7},{6, 7},
        {0, 4}, {1, 5}, {2, 6},{3, 7}
    };

    Vector4 projectedVertices[8];

    InitWindow(800, 600, "Spinning Cube with X Rotation and Projection Matrix");
    SetTargetFPS(60);
    
    float angleX = 0;
    float angleY = 0;
    while (!WindowShouldClose()) {
        
        float scroll = GetMouseWheelMove();

        float rotationMatrixX[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        float rotationMatrixY[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };

        RotateX(angleX, rotationMatrixX);
        RotateY(angleY, rotationMatrixY);


        if(IsKeyDown(KEY_W)) angleX += 0.01f;
        if(IsKeyDown(KEY_S)) angleX -= 0.01f;
        if(IsKeyDown(KEY_A)) angleY += 0.01f;
        if(IsKeyDown(KEY_D)) angleY -= 0.01f;

        if(scroll > 0) projectionMatrix[3][3] += 0.1f;
        if(scroll < 0) projectionMatrix[3][3] -= 0.1f;

        if(IsKeyDown(KEY_Z)){ projectionMatrix[0][0] += 0.1f;projectionMatrix[1][1] += 0.1f;}
        if(IsKeyDown(KEY_X)){ projectionMatrix[0][0] -= 0.1f;projectionMatrix[1][1] -= 0.1f;}
        for(int i = 0; i < 8; i++){

            Vector4 rotatedVertex = Project(rotationMatrixX, cubeVertices[i]);
                    rotatedVertex = Project(rotationMatrixY, rotatedVertex);

            projectedVertices[i] = Project(projectionMatrix, rotatedVertex);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for(int i = 0; i < 12; i++){
            Vector4 v0 = projectedVertices[lines[i][0]];
            Vector4 v1 = projectedVertices[lines[i][1]];

            Vector2 startPos = {v0.x * 100 + 400, v0.y * 100 + 300};
            Vector2 endPos   = {v1.x * 100 + 400, v1.y * 100 + 300};

            DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, BLACK);

        }

        DrawText("Spinning Cube with X Rotation", 10, 10, 20, DARKGRAY);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
