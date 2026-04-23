#include <raylib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <raymath.h>
#include <array>

using namespace std;

float projectionMatrix[4][4] = {
        {2, 0, 0, 5},
        {0, 2, 0, 5},
        {0, 0, 2, 5},
        {0, 0, 0, 1}
};

Vector4 MultiplyMatrices(Vector4 v, float (*m)[4]){
    Vector4 result;

    /*result.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3];
    result.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3];
    result.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + v.w * m[2][3];
    result.w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + v.w * m[3][3];*/

    result.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2];
    result.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2];
    result.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2];
    result.w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2];

    return result;
}

Vector4 Project(Vector4 v, float (*m)[4]){
    Vector4 projection = MultiplyMatrices(v, m);

    if(projection.w != 0) {
        projection.x /= projection.w;
        projection.y /= projection.w;
        projection.z /= projection.w;
    }

    return projection;
}

void multiply4x4Matrices(const float mat1[4][4]) {
    float rslt[4][4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                rslt[i][j] += projectionMatrix[k][j] * mat1[i][k];
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
           projectionMatrix[i][j] = rslt[i][j];
        }
    }
}

void rotateX(float angle, float (*matrix)[4]){
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    
    matrix[1][1] = cosAngle;
    matrix[1][2] = -sinAngle;
    matrix[2][1] = sinAngle;
    matrix[2][2] = cosAngle;
}
void rotateY(float angle, float (*matrix)[4]){
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    
    matrix[0][0] = cosAngle;
    matrix[0][2] = -sinAngle;
    matrix[2][0] = sinAngle;
    matrix[2][2] = cosAngle;
}
void rotateZ(float angle, float (*matrix)[4]){
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    
    matrix[0][0] = cosAngle;
    matrix[0][1] = -sinAngle;
    matrix[1][0] = sinAngle;
    matrix[1][1] = cosAngle;
}

std::vector<int> parseFace(const std::string& line) {
    std::vector<int> faceIndices;
    std::istringstream iss(line);
    std::string type, vertex;

    iss >> type;  // Ignore the "f"

    // Extract each vertex/texture/normal combination
    while (iss >> vertex) {
        std::string vertIndex = vertex.substr(0, vertex.find('/'));
        faceIndices.push_back(std::stoi(vertIndex) - 1);  // Convert vertex index to integer
    }

    return faceIndices;
}

int main()
{
    std::ifstream file("torus.obj");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }

    vector<Vector4> vec;
    vector<Vector4> projectedVertices;

    vector<vector<int>> faces;
    string line;

    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            Vector4 vertex;
            std::istringstream iss(line);
            std::string type;
            iss >> type >> vertex.x >> vertex.y >> vertex.z;
            vertex.x = vertex.x;
            vertex.y = vertex.y;
            vertex.z = vertex.z;
            vertex.w = 1.0f;
            vec.push_back(vertex);
        }
        else if (line.substr(0, 2) == "f ") {
            faces.push_back(parseFace(line));
        }
    }
    projectedVertices = vec;
    file.close();
    
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;

    float rotationX[4][4] = {{1, 0, 0, 0},
                             {0, 1, 0, 0},
                             {0, 0, 1, 0},
                             {0, 0, 0, 1}};

    float rotationY[4][4] = {{1, 0, 0, 0},
                             {0, 1, 0, 0},
                             {0, 0, 1, 0},
                             {0, 0, 0, 1}};
                             
    float rotationZ[4][4] = {{1, 0, 0, 0},
                             {0, 1, 0, 0},
                             {0, 0, 1, 0},
                             {0, 0, 0, 1}};

    InitWindow(600, 600, "raylib Tetris");
    SetTargetFPS(60);

    while(WindowShouldClose() == false){

        if(IsKeyDown(KEY_J))angleX += 1 * DEG2RAD;
        if(IsKeyDown(KEY_K))angleY += 1 * DEG2RAD;
        if(IsKeyDown(KEY_L))angleZ += 1 * DEG2RAD;

        BeginDrawing();
        ClearBackground(WHITE);

        rotateX(angleX, rotationX);
        rotateY(angleY, rotationY);
        rotateZ(angleZ, rotationZ);
        
        if(IsKeyDown(KEY_SPACE)){
            multiply4x4Matrices(rotationX);
            //angleX = 0;
        }

        int c = 0;
        for(Vector4 vertices : vec){
            vertices = MultiplyMatrices(vertices, rotationX);
            vertices = MultiplyMatrices(vertices, rotationY);
            vertices = MultiplyMatrices(vertices, rotationZ);
            projectedVertices[c] = (MultiplyMatrices(vertices, projectionMatrix));
            c++;
        }
        

        for(auto face : faces){
            DrawLine(projectedVertices[face[0]].x * 100 + 300, projectedVertices[face[0]].y * 100 + 300, projectedVertices[face[1]].x * 100 + 300, projectedVertices[face[1]].y * 100 + 300, BLACK);
            DrawLine(projectedVertices[face[1]].x * 100 + 300, projectedVertices[face[1]].y * 100 + 300, projectedVertices[face[2]].x * 100 + 300, projectedVertices[face[2]].y * 100 + 300, BLACK);
            DrawLine(projectedVertices[face[2]].x * 100 + 300, projectedVertices[face[2]].y * 100 + 300, projectedVertices[face[0]].x * 100 + 300, projectedVertices[face[0]].y * 100 + 300, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
   return 0;
}