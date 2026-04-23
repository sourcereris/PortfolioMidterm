#include <raylib.h>
#include <math.h>
#include <iostream>
#include <vector>

int CIRCLESIZE = 12;
float G = 5;


//Vector2 obj = {450, 600};
Vector2 origin = {400, 400};

//Vector2 velocity = {0, 2};

//float xdiff, ydiff, force;

class Point{
private:
        float xdiff, ydiff, force;
        Vector2 obj;
        Vector2 velocity = {0, 2};
public:

    Point(Vector2 ob) {
        obj = ob;
    }

    void update(){
        xdiff = origin.x - obj.x;
        ydiff = origin.y - obj.y;

        force = G / (pow(xdiff, 2) + pow(ydiff, 2));

        velocity.x += xdiff * force;
        velocity.y += ydiff * force;

        obj.x += velocity.x;
        obj.y += velocity.y;

        DrawCircle(obj.x, obj.y, CIRCLESIZE, GRAY);
    }
};

/*void update(std::vector<Vector2>planets){

        xdiff = origin.x - obj.x;
        ydiff = origin.y - obj.y;
        
        force = G / (pow(xdiff, 2) + pow(ydiff, 2));

        velocity.x += xdiff * force;
        velocity.y += ydiff * force;

        obj.x += velocity.x;
        obj.y += velocity.y;

}*/

int main()
{

    InitWindow(800, 800, "Raylib G-Sim");
    SetTargetFPS(60);

    std::vector<Point> planets;
    
    while(WindowShouldClose() == false){
        
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawRectangle(40, 40, 720, 720, WHITE);

        DrawCircle(origin.x, origin.y, 7, DARKBLUE);
        //DrawCircle(obj.x, obj.y, CIRCLESIZE, GRAY);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            planets.push_back(GetMousePosition());
        }
        if(!planets.empty())
            for(int i = 0; i < planets.size(); i++){
                planets[i].update();
            }
        //update(planets);

        EndDrawing();
    }

    CloseWindow();
   return 0;
}