#include "Button.hpp"

Button::Button(Rectangle rec, std::string text) : buttonPossition(rec), text(text){}

void Button::draw()
{
    DrawRectangleRounded(buttonPossition, 0.5, 5, {94, 29, 52, 255});
    if(scoreToUpgrade <= score){
        DrawRectangleRounded(buttonPossition, 0.5, 5, {132, 40, 73, 255});
    }
    // if(mouseOnButton(GetMousePosition())){
    //     DrawRectangleRounded(buttonPossition, 0.5, 5, {132, 40, 73, 255});
    // }
    int x = buttonPossition.x + buttonPossition.width/2 - text.length()*5;
    int y = buttonPossition.y + buttonPossition.height/2 - 10;
    DrawText(text.c_str(), x, y, 20, WHITE);
    std::string scoreText = "Price  " + std::to_string(scoreToUpgrade);
    DrawText(scoreText.c_str(), x + 40, y + 20, 10, WHITE);
}

bool Button::clicked(Vector2 position)
{
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mouseOnButton(position) && scoreToUpgrade <= score){
        wasButtonPressed = true;
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && mouseOnButton(position) && wasButtonPressed){
            wasButtonPressed = false;
            if(scoreToUpgrade <= score) scoreToUpgrade = pow(ballCount, 2) * 5;
            return true;
    }

    else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        wasButtonPressed = false;
    }
    return false;
}

bool Button::mouseOnButton(Vector2 mousePossition)
{
    return CheckCollisionPointRec(mousePossition, buttonPossition);
}
