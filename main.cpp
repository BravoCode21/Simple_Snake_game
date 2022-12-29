#include <iostream>
#include <conio.h>
using namespace std;

bool gameover;
const int width{40};
const int height{10};
//variables for head position abd fruit
int x, y, Fruitx, Fruity, score{0};

//arrays for tail
int tailX[100], tailY[100];
int nTail;

//use enumerators
//enum are user defined data types

enum eDirection{ STOP=0, LEFT, RIGHT, DOWN, UP};
eDirection dir;
void SetUp(){
    gameover=false;
    //snake not to move
    dir = STOP;
    //centers the snake
    x = width/2;
    y= height/2;
    //fruit is randomly placed
    Fruity = rand() % width;
    Fruitx = rand() % height;


}

void DrawNow(){
    //clear screen
    system("cls");
    //top border
    for (int i = 0; i<width; i++){
        cout<<"#";
    }
    cout<<endl;

    // Print the sides of the rectangle
    for(int i=0; i<height-1;i++){
        cout<<"#";
        for(int j = 0; j<width-2;j++){
            cout<<" ";
            //place the snake in the screen
            if(i == y && j ==x ){
                cout<<"0";
            }
            //Place fruit in the screen
            else if( i == Fruitx && j == Fruity)
                cout<<"F";
            else{
                bool print = false;
                for(int k =0; k <nTail; k++){

                    if (tailX[k] == j && tailY[k] == i){
                        cout<<"o";
                        print = true;
                    }
                    cout<<" ";
                }
            }
        }
        cout<<"#"<<endl;
    }
    //bottom border
    for (int i = 0; i<width; i++){
        cout<<"#";
    }
    cout<<endl;

    cout<<"Score"<<score<<endl;

}

void Input(){
    //we need to include the conio.h to handle cntrols

    if (_kbhit()){
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;

            case 'w':
                dir = UP;
                break;

            case 's':
                dir= DOWN;
                break;

            case 'q':
                gameover = true;
                break;


        }
    }

}

void Logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i =1; i<nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailY[i] = prevY;
        tailX[i] = prevX;
        prevX = prev2X;
        prevY = prev2Y;

    }

    switch (dir) {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;



    }
    //terminating game if it goes outside the logic

    if (x > width || x < 0 || y > height || y < 0)
        gameover = true;
    //check if we hit
    for(int i = 0; i<nTail; i++)
        if(tailX[i]==x && tailY[i]==y)
            gameover= true;

    //increasing the score when we eat the fruit

    if (x == Fruitx && y == Fruity){
        score +=10;
        Fruity = rand() % width;
        Fruitx = rand() % height;
        nTail++;


    }

}

int main() {
    SetUp();
    while(!gameover){
        DrawNow();
        Input();
        Logic();
    }
    return 0;

    }




