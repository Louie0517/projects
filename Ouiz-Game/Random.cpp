#include "raylib.h"
#include <vector>
#include <string>
#define STORE 50

using namespace std;

struct UserInfo{
    vector<string>name;
    vector<string>answer;
    vector<string>question;
    int score = 0;
};

class guessingGame{
protected:
    int numberOfUser = 0;
public:
    UserInfo info[STORE];
    int getNumberOfUser()const{
    return numberOfUser;
    }
};

 enum gameScreen {MENU, ROUND_1};

class levelByFunction : public guessingGame{
public:

gameScreen menu(UserInfo& info, int screenW);
void questions(UserInfo& info);
gameScreen roundOne();

};

void levelByFunction::questions(UserInfo& info){

info.question = {
    "BLUE", "BANANA", "AIRPLANE",
    "10", "TRIANGLE", "DOG"
    };

}
gameScreen levelByFunction::roundOne(){
    ClearBackground(RAYWHITE);
    DrawText("round one", 100, 340, 90, YELLOW);

    if(IsKeyPressed(KEY_ENTER)){
        return MENU;
    }
    return ROUND_1;

}
gameScreen levelByFunction::menu(UserInfo& info, int screenW){
    DrawText("Guessing Game!", screenW / 4, 100, 75, YELLOW);
    DrawRectangle(screenW / 4, 290, 590, STORE, WHITE);
    guessingGame guessGame;

    static string userInput = "";
    static bool isUserTyping = false;
    bool isPress = false;

     Rectangle userRec = {300, 290, 590, STORE};
     DrawRectangleRec(userRec, WHITE);
    if(userInput.empty()){
            DrawText("Enter name: ", userRec.x + 10, userRec.y + 10, 45, BLACK);
    } else {
            DrawText(userInput.c_str(), userRec.x + 10, userRec.y + 10, 45, BLACK);
    }
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), userRec)){
                isUserTyping = true;
            }

    if(isUserTyping){
        int userPressed = GetCharPressed();
        while(userPressed > 0){
            if((userPressed >= 32) && (userPressed <= 126)){
                userInput += (char)userPressed;
                }
                userPressed = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE) &&  !userInput.empty()){
                userInput.pop_back();
            }
            if(IsKeyPressed(KEY_ENTER) && !userInput.empty()){
               info.name.push_back(userInput);
               userInput = "";
               isUserTyping = false;
        }
    }

    Color hoverGreen = {0, 255, 0, 120};
    Rectangle rec = {300, 380, 200, 70};
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rec)){
        isPress = true;
        return ROUND_1;
    } else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), rec)){
              isPress = false;
    }
    DrawRectangleRounded(rec, 1, 10, isPress ? hoverGreen : GREEN);
    DrawText("Enter", 335, 395, 40, WHITE);

    return MENU;
}

int main(){

    int screenW = 1200;
    int screenH = 800;

    InitWindow(screenW, screenH, "Gussing Game");
    levelByFunction functions;
    guessingGame guessGame;

    SetTargetFPS(60);

    gameScreen currentScreenDisplay = MENU;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BROWN);
        switch(currentScreenDisplay){
        case MENU:
            functions.menu(guessGame.info[guessGame.getNumberOfUser()], screenW);
            break;
        case ROUND_1:
            currentScreenDisplay = functions.roundOne();
            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
