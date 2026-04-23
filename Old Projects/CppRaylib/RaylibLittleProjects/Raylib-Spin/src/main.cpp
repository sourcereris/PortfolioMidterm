#include "raylib.h"
#include <iostream>
#include <random>
#include <vector>
using namespace std;

#include "Dot.h"
#include "getColor.h"

float GetRandomFloat(float min, float max);
/*Color getColor(float distance, float maxDistance);

class Dot{
    public:
    Dot(){}
    Dot(float cx, float cy): x{cx}, y{cy}{
        

    }
    float x;
    float y;
    
    double distFromCent = sqrt(   pow((GetScreenWidth()/2-x), 2) + pow((GetScreenHeight()/2-y),2)  );
    float degreeInRad = atan2(y - GetScreenHeight()/2,x - GetScreenWidth()/2);

    Color color = getColor(distFromCent, 300);
    

    void move(){
        
        distFromCent = clampFunct(distFromCent, -0.1, -0.5);
        degreeInRad = clampFunct(degreeInRad, 0.01, 0.01);
        color = getColor(distFromCent, 300);

        x = GetScreenWidth()/2 + (distFromCent * cos(degreeInRad));
        y = GetScreenHeight()/2 + (distFromCent * sin(degreeInRad));
    }

    float clampFunct(float base, float multiplier, float fMultiplier){

        float distance = Clamp(distFromCent, 0, 400.0);
        float factor = distance / 400.0;
        return base += multiplier + fMultiplier * factor;
    }
};*/

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "Tornado");
    SetTargetFPS(60);

    vector<Dot> vec;
    while(WindowShouldClose() == false){

        BeginDrawing();
        ClearBackground(WHITE);

        vec.emplace_back(GetRandomFloat(0, 200), GetRandomFloat(0, 200));
        
        for(unsigned short i = 0; i < static_cast<unsigned short>(vec.size()); i++){

            DrawCircle(vec[i].x, vec[i].y, 5, vec[i].color);
            vec[i].move();

            if(( abs(GetScreenWidth()/2 - vec[i].x)) < 1 && abs((GetScreenHeight()/2 - vec[i].y)) < 1){
                vec.erase(vec.begin() + i);
                cout << vec.size() << endl;
            }
        }
        DrawCircle(300, 300, 20, (BLACK));

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}

/*Color getColor(float distance, float maxDistance) {
    // Clamp distance to a max value of 200 or maxDistance
    distance = Clamp(distance, 0, maxDistance);

    // Calculate the interpolation factor (0.0 to 1.0)
    float factor = distance / maxDistance;

    // Linearly interpolate the red and blue channels
    unsigned char red = (unsigned char)((1.0f - factor) * 255);   // Red increases as distance decreases
    unsigned char blue = (unsigned char)(factor * 255);           // Blue decreases as distance decreases

    // Return the color with full alpha (255) and no green (0)
    return (Color){red, 0, blue, 255};
}*/

float GetRandomFloat(float min, float max) {
    
    std::random_device rd;
    std::uniform_real_distribution<float> dist(min, max);

    return dist(rd);
}