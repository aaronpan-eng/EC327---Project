// Author: Patricia Terol (MODIFIED BY AARON PAN, VAIBHAVI HANSRAJANI, NOAH TANIGUCHI, KWADWO OSAFO, MELISSA GIBBLE)
// Course: CSE 2050 (MODIFIED FOR EC327 PROJECT AT BOSTON UNIVERISTY)
// Project: assign10
//********************************************************
//************MODIFIED FOR EC327 PROJECT******************
//********************************************************
//NOTES: - COMMENTS OF EDITS MADE IN ALL CAPS
//       - AS OF THIS VERSION: THIS CODE IS MADE TO COMPILE FOR XCODE ON MAC WITH THE 'OpenGL.Framework' AND 'GLUT.Framework'

//MAIN EDITS: - MADE GHOSTS USER CONTROLLED FOR MULTIPLAYER PACMAN
//            - ADDED POWERUPS SO PACMAN COULD EAT GHOSTS AND GHOSTS WOULD SLOW DOWN
//            - EDITED WELCOME SCREEN

#include <stdlib.h>
#include <vector>
#include <deque>
//#include <windows.h> //HAD TO COMMENT OUT FOR COMPILATION ON MAC
//#include <GL/glut.h> //HAD TO COMMENT OUT FOR COMPILATION ON MAC
#include <iostream>
#include <string>
#define GL_SILENCE_DEPRECATION
#define _USE_MATH_DEFINES
#include <math.h>
#include <OpenGL/gl.h> //THESE HEADER FILES FOR XCODE ON MAC
#include <OpenGL/glu.h> //THESE HEADER FILES FOR XCODE ON MAC
#include <OpenGL/glext.h> //THESE HEADER FILES FOR XCODE ON MAC
#include <GLUT/glut.h> //THESE HEADER FILES FOR XCODE ON MAC
using namespace std;

//POWER MODE COUNTER: 0 FOR NO POWERUP, ABOVE 0 FOR POWERUP ACTIVATED, SERVES AS TIMER AS WELL
static int powermode = 0;

//STATES FOR DISPLAYING THE GHOSTS; (TRUE -> DONT DISPLAY GHOST; FALSE -> DISPLAY GHOST)
static bool null1 = false; //SETS GHOST 1 TO DISPLAY
static bool null2 = false; //SETS GHOST 1 TO DISPLAY
static bool null3 = false; //SETS GHOST 1 TO DISPLAY


static bool replay = false; //check if starts a new game
static bool over = true; //check for the game to be over
static float squareSize = 50.0; //size of one square on the game
static float xIncrement = 0; // x movement on pacman
static float yIncrement = 0; // y movement on pacman
static int rotation = 0; // orientation of pacman

//USING 3 USER CONTROLLED GHOSTS (COMMENTED OUT THE 4TH)
float* monster1 = new float[3] {10.5, 8.5, 1.0}; //coordinates and direction of first monster
float* monster2 = new float[3] {13.5, 1.5, 2.0}; //coordinates and direction of second monster
float* monster3 = new float[3] {4.5, 6.5, 3.0}; //coordinates and direction of third monster
//float* monster4 = new float[3] {2.5, 13.5, 4.0}; //coordinates and direction of fourth monster
static vector<int> border = { 0, 0, 15, 1, 15, 15, 14, 1, 0, 14, 15, 15, 1, 14, 0, 0 }; //coordinates of the border walls

//coordinates of the obstacles (divided into 3 for clarity)
static vector<int> obstaclesTop = { 2, 2, 3, 6, 3, 6, 4, 5, 4, 2, 5, 4, 5, 3, 6, 5, 6, 1, 9, 2, 7, 2, 8, 5, 9, 5, 10, 3, 10, 4, 11, 2, 11, 5, 12, 6, 12, 6, 13, 2 };
static vector<int> obstaclesMiddle = { 2, 9, 3, 7, 3, 7, 4, 8, 4, 9, 5, 11, 5, 6, 6, 10, 6, 10, 7, 8, 7, 8, 8, 9, 6, 7, 7, 6, 8, 6, 9, 7, 10, 6, 9, 10, 9, 10, 8, 8, 11, 9, 10, 11, 11, 8, 12, 7, 12, 7, 13, 9 };
static vector<int> obstaclesBottom = { 2, 10, 3, 13, 3, 13, 4, 12, 5, 12, 6, 13, 6, 13, 7, 11, 8, 11, 9, 13, 9, 13, 10, 12, 11, 12, 12, 13, 12, 13, 13, 10 };
static deque<float> food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5};
static deque<float> powerup = {1.5, 13.5, 13.5, 1.5, 13.5, 13.5}; //COORDINATES FOR POWERUP FOOD
static vector<vector<bool>> bitmap; // 2d image of which squares are blocked and which are clear for pacman to move in
bool* keyStates = new bool[256]; // record of all keys pressed
int points = 0; // total points collected

//Initializes the game with the appropiate information
void init(void){
    //clear screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    //reset all keys
    for (int i = 0; i < 256; i++){
        keyStates[i] = false;
    }
    //fill the bitmap with the obstacles
    bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
    bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
    bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
    bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true});
    bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true});
    bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true});
    bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true});
    bitmap.push_back({ true, true, true, true, true, false, false, false, true, false, false, false, false, false, true});
    bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
    bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
    bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
    bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
    bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
    bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
    bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
}

//Method to draw the obstacle course and the walls
void drawLaberynth(){
    glColor3f(1.0, 1.0, 1.0);
    //Border
    for (int i = 0; i < border.size(); i = i + 4){
        glRectf(border.at(i) * squareSize, border.at(i + 1)*squareSize, border.at(i + 2)*squareSize, border.at(i + 3)*squareSize);
    }

    //Obstacles
    for (int j = 0; j < obstaclesBottom.size(); j = j + 4){
        glRectf(obstaclesBottom.at(j) * squareSize, obstaclesBottom.at(j + 1)*squareSize, obstaclesBottom.at(j + 2)*squareSize, obstaclesBottom.at(j + 3)*squareSize);
    }
    for (int k = 0; k < obstaclesMiddle.size(); k = k + 4){
        glRectf(obstaclesMiddle.at(k) * squareSize, obstaclesMiddle.at(k + 1)*squareSize, obstaclesMiddle.at(k + 2)*squareSize, obstaclesMiddle.at(k + 3)*squareSize);
    }
    for (int p = 0; p < obstaclesTop.size(); p = p + 4){
        glRectf(obstaclesTop.at(p) * squareSize, obstaclesTop.at(p + 1)*squareSize, obstaclesTop.at(p + 2)*squareSize, obstaclesTop.at(p + 3)*squareSize);
    }
}

//Method to check if the food has been eaten
bool foodEaten(int x, int y, float pacmanX, float pacmanY){
    if (x >= pacmanX - 16.0 *cos(359 * M_PI / 180.0) && x <= pacmanX + 16.0*cos(359 * M_PI / 180.0)){
        if (y >= pacmanY - 16.0*cos(359 * M_PI / 180.0) && y <= pacmanY + 16.0*cos(359 * M_PI / 180.0)){
            return true;
        }
    }
    return false;
}

//Method to draw all the food left and delete the ate one
void drawFood(float pacmanX, float pacmanY){
    deque<float> temp;
    deque<float> Ptemp;

    //check if the food has not been eaten
    for (int i = 0; i < food.size(); i = i + 2){
        if (!foodEaten(food.at(i)*squareSize, food.at(i + 1)*squareSize, pacmanX, pacmanY)){
            temp.push_back(food.at(i));
            temp.push_back(food.at(i + 1));
        }
        else {
            points++;
        }
    }
    food.swap(temp);


    int powerupCount = powerup.size();
    
    //CHECK IF THE POWERUP FOOD HAS NOT BEEN EATEN
    for (int i = 0; i < powerup.size(); i = i + 2){
                if (!foodEaten(powerup.at(i)*squareSize, powerup.at(i + 1)*squareSize, pacmanX, pacmanY)){
                        Ptemp.push_back(powerup.at(i));
                        Ptemp.push_back(powerup.at(i + 1));
                }
                else {
                        points++;
                }
        }
        powerup.swap(Ptemp);

    //WHEN POWERUP FOOD IS EATEN
    if(powerupCount > powerup.size())
        powermode = 1000; //POWERMODE POSITIVE: POWERUP ACTIVATED
    
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    //draw all the food avilable
    for (int j = 0; j < food.size(); j = j + 2){
        glVertex2f(food.at(j)*squareSize, food.at(j + 1)*squareSize);
    }
    glEnd();

    //DISPLAYING POWERUP FOOD: BIG RED DOTS
    glPointSize(15.0);//RED POWERUP FOOD IS BIGGER THAN REGUALR FOOD
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);//RED COLOR (R,G,B)
    for(int i = 0; i < powerup.size(); i = i + 2){
        glVertex2f(powerup.at(i)*squareSize, powerup.at(i + 1)*squareSize);
    }

    glEnd();
}

//Method to draw the pacman character through consicutive circle algorithm
void drawPacman(float positionX, float positionY, float rotation){
    int x, y;
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    for (int k = 0; k < 32; k++){
        x = (float)k / 2.0 * cos((30 + 90*rotation) * M_PI / 180.0) + (positionX*squareSize);
        y = (float)k / 2.0* sin((30 + 90 * rotation) * M_PI / 180.0) + (positionY*squareSize);
        for (int i = 30; i < 330; i++){
            glVertex2f(x, y);
            x = (float)k / 2.0 * cos((i + 90 * rotation) * M_PI / 180.0) + (positionX*squareSize);
            y = (float)k / 2.0* sin((i + 90 * rotation) * M_PI / 180.0) + (positionY*squareSize);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

//Method to draw the monster character through consecutive circles algorithm
void drawMonster(float positionX, float positionY, float r, float g, float b){
    int x, y;
    glBegin(GL_LINES);
    glColor3f(r, g, b);
    //draw the head
    for (int k = 0; k < 32; k++){
        x = (float)k / 2.0 * cos(360 * M_PI / 180.0) + (positionX*squareSize);
        y = (float)k / 2.0* sin(360 * M_PI / 180.0) + (positionY*squareSize);
        for (int i = 180; i <= 360; i++){
            glVertex2f(x, y);
            x = (float)k / 2.0 * cos(i * M_PI / 180.0) + (positionX*squareSize);
            y = (float)k / 2.0* sin(i * M_PI / 180.0) + (positionY*squareSize);
            glVertex2f(x, y);
        }
    }
    glEnd();
    //draw body
    glRectf((positionX*squareSize) - 17, positionY*squareSize, (positionX*squareSize) + 15, (positionY*squareSize) + 15);
    glBegin(GL_POINTS);
    glColor3f(0, 0.2, 0.4);
    //draw eyes and legs
    glVertex2f((positionX*squareSize) - 11, (positionY*squareSize) + 14); //legs
    glVertex2f((positionX*squareSize) - 1, (positionY*squareSize) + 14); //legs
    glVertex2f((positionX*squareSize) + 8, (positionY*squareSize) + 14); //legs
    glVertex2f((positionX*squareSize) + 4, (positionY*squareSize) - 3); //eyes
    glVertex2f((positionX*squareSize) - 7, (positionY*squareSize) - 3); //eyes
    glEnd();
}

//USER CONTROLLED GHOSTS WITH KEYS 'tfgh', 'ijkl', AND '1234'
void updateMonster(float* monster, int id){
    //find the current position of the monster
    int x1Quadrant = (int)((monster[0] - (2/squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    int x2Quadrant = (int)((monster[0] + (2/squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    int y1Quadrant = (int)((monster[1] - (2/squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    int y2Quadrant = (int)((monster[1] + (2/squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
    //CONTROLS FOR EACH GHOST
    if (monster[2] == 1)
    {
        if (keyStates['j']){
            if (!bitmap.at(x1Quadrant).at((int)monster[1])){
                    monster[0] -= 2 / squareSize; //LEFT
            }
        }
        if (keyStates['l']){
            if (!bitmap.at(x2Quadrant).at((int)monster[1])){
                    monster[0] += 2 / squareSize; //RIGHT
                }
        }
        if (keyStates['i']){
            if (!bitmap.at((int)monster[0]).at(y1Quadrant)){
                    monster[1] -= 2 / squareSize; //UP
                }
        }
        if (keyStates['k']){
            if (!bitmap.at((int)monster[0]).at(y2Quadrant)){
                    monster[1] += 2 / squareSize; //DOWN
                }
        }
    }
    else if (monster[2] == 2)
    {
        if (keyStates['f']){
            if (!bitmap.at(x1Quadrant).at((int)monster[1])){
                    monster[0] -= 2 / squareSize; //LEFT
            }
        }
        if (keyStates['h']){
            if (!bitmap.at(x2Quadrant).at((int)monster[1])){
                    monster[0] += 2 / squareSize; //RIGHT
                }
        }
        if (keyStates['t']){
            if (!bitmap.at((int)monster[0]).at(y1Quadrant)){
                    monster[1] -= 2 / squareSize; //UP
                }
        }
        if (keyStates['g']){
            if (!bitmap.at((int)monster[0]).at(y2Quadrant)){
                    monster[1] += 2 / squareSize; //DOWN
                }
        }
    }
    else if (monster[2] == 3)
    {
        if (keyStates[49]){
            if (!bitmap.at(x1Quadrant).at((int)monster[1])){
                    monster[0] -= 2 / squareSize; //LEFT
            }
        }
        if (keyStates[50]){
            if (!bitmap.at(x2Quadrant).at((int)monster[1])){
                    monster[0] += 2 / squareSize; //RIGHT
                }
        }
        if (keyStates[51]){
            if (!bitmap.at((int)monster[0]).at(y1Quadrant)){
                    monster[1] -= 2 / squareSize; //UP
                }
        }
        if (keyStates[52]){
            if (!bitmap.at((int)monster[0]).at(y2Quadrant)){
                    monster[1] += 2 / squareSize; //DOWN
                }
        }
    }
        //****COMMENTING OUT RANDOM GHOST MOVEMENT****
        //Method to update the position of the monsters randomly
        /*
        switch ((int)monster[2]){
        case 1:
            if (!bitmap.at(x1Quadrant).at((int)monster[1])){
                monster[0] -= 2 / squareSize;
            }else {
                int current = monster[2];
                do{
                    monster[2] =  (rand() % 4) + 1;
                } while (current == (int) monster[2]);
            }
            break;
        case 2:
            if (!bitmap.at(x2Quadrant).at((int)monster[1])){
                monster[0] += 2 / squareSize;
            }
            else {
                int current = monster[2];
                do{
                    monster[2] = (rand() % 4) + 1;
                } while (current == (int)monster[2]);
            }
            break;
        case 3:
            if (!bitmap.at((int)monster[0]).at(y1Quadrant)){
                monster[1] -= 2 / squareSize;
            }
            else {
                int current = monster[2];
                do{
                    monster[2] = (rand() % 4) + 1;
                } while (current == (int)monster[2]);
            }
            break;
        case 4:
            if (!bitmap.at((int)monster[0]).at(y2Quadrant)){
                monster[1] += 2 / squareSize;
            }
            else {
                int current = monster[2];
                do{
                    monster[2] = (rand() % 4) + 1;
                } while (current == (int)monster[2]);
            }
            break;
        default:
            break;
        }
        */
}

//Method to set the pressed key
void keyPressed(unsigned char key, int x, int y){
    keyStates[key] = true;
}

//Method to unset the released key
void keyUp(unsigned char key, int x, int y){
    keyStates[key] = false;
}

//Method to reset all the variable necessaries to start the game again
void resetGame(){
    over = false;
    xIncrement = 0;
    yIncrement = 0;
    rotation = 0;
    null1 = false; //SETS GHOST 1 TO DISPLAY
    null2 = false; //SETS GHOST 2 TO DISPLAY
    null3 = false; //SETS GHOST 3 TO DISPLAY

    //USING 3 USER CONTROLLED GHOSTS (COMMENTED OUT THE 4TH)
    monster1 = new float[3] {10.5, 8.5, 1.0};
    monster2 = new float[3] {13.5, 1.5, 2.0};
    monster3 = new float[3] {4.5, 6.5, 3.0};
    // monster4 = new float[3] {2.5, 13.5, 4.0};
    points = 0;
    for (int i = 0; i < 256; i++){
        keyStates[i] = false;
    }
    food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5};

    powerup = {1.5, 13.5, 13.5, 1.5, 13.5, 13.5};
}

//Method to update the movement of the pacman according to the movement keys pressed
void keyOperations(){
    //get current position OF PACMAN
    float  x = (1.5 + xIncrement) * squareSize;
    float y = (1.5 + yIncrement) * squareSize;

    if (keyStates['a']){
        x -= 2;
        int x1Quadrant = (int)((x - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at(x1Quadrant).at((int)y/squareSize)){
            xIncrement -= 2 / squareSize;
            rotation = 2;
        }
    }
    if (keyStates['d']){
        x += 2;
        int x2Quadrant = (int)((x + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at(x2Quadrant).at((int)y / squareSize)){
            xIncrement += 2 / squareSize;
            rotation = 0;
        }
    }
    if (keyStates['w']){
        y -= 2;
        int y1Quadrant = (int)((y - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at((int)x/squareSize).at(y1Quadrant)){
            yIncrement -= 2 / squareSize;
            rotation = 3;
        }
    }
    if (keyStates['s']){
        y += 2;
        int y2Quadrant = (int)((y + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
        if (!bitmap.at((int)x / squareSize).at(y2Quadrant)){
            yIncrement += 2 / squareSize;
            rotation = 1;
        }
    }
    if (keyStates[' ']){
        if (!replay && over){
            resetGame();
            replay = true;
        }
        else if (replay && over){
            replay = false;
        }
    }
}

//Method to check if the game is over
void gameOver(){
    int pacmanX = (int)(1.5 + xIncrement);
    int pacmanY = (int)(1.5 + yIncrement);
    //POSITION OF USER CONTORLLED GHOSTS (COMMENTED OUT THE 4TH)
    int monster1X = (int)(monster1[0]);
    int monster1Y = (int)(monster1[1]);
    int monster2X = (int)(monster2[0]);
    int monster2Y = (int)(monster2[1]);
    int monster3X = (int)(monster3[0]);
    int monster3Y = (int)(monster3[1]);
    //int monster4X = (int)(monster4[0]);
    //int monster4Y = (int)(monster4[1]);

    //CHECKING IF PACMAN TOUCHES A GHOST
    if(!powermode){
        if(!null1){
            if (pacmanX == monster1X && pacmanY == monster1Y){
                over = true; //GAME OVER
            }
        }
        if(!null2){
            if (pacmanX == monster2X && pacmanY == monster2Y){
                over = true; //GAME OVER
            }
        }
        if(!null3){
            if (pacmanX == monster3X && pacmanY == monster3Y){
                over = true; //GAME OVER
            }
        }
    
    }

    //ALLOWING PACMAN TO EAT GHOSTS WHEN POWERMODE IS ACTIVATED (POWERUP ACTIVATED)
    else{
        if (pacmanX == monster1X && pacmanY == monster1Y){
            null1 = true; // ERASE GHOST 1
        }
        if (pacmanX == monster2X && pacmanY == monster2Y){
            null2 = true; // ERASE GHOST 2
        }
        if (pacmanX == monster3X && pacmanY == monster3Y){
            null3 = true; // ERASE GHOST 3
                }
    
    }

    //IF PACMAN EATS ALL THE FOOD: WIN
    if (points == 106){
        over = true; //WIN
    }
}

//Method to display the results of the game at the ends
void resultsDisplay(){
    if (points == 106){
        //Won
        char* message = "*************************************";
        glRasterPos2f(170, 250);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "CONGRATULATIONS, YOU WON! ";
        glColor3f(1, 1, 1);
        glRasterPos2f(200, 300);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "*************************************";
        glRasterPos2f(170, 350);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "To start or restart the game, press the space key.";
        glRasterPos2f(170, 550);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    }else {
        //Lost
        char* message = "*************************";
        glRasterPos2f(210, 250);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "SORRY, YOU LOST ... ";
        glColor3f(1, 1, 1);
        glRasterPos2f(250, 300);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "*************************";
        glRasterPos2f(210, 350);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "You got: ";
        glRasterPos2f(260, 400);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        string result = to_string(points);
        message = (char*)result.c_str();
        glRasterPos2f(350, 400);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = " points!";
        glRasterPos2f(385, 400);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "To start or restart the game, press the space key.";
        glRasterPos2f(170, 550);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    }
}

//WELCOME SCREEN WTIH TEAM MEMBER NAMES AND USER CONTROL INSTRUCTIONS
void welcomeScreen(){
    glClearColor(0, 0.2, 0.4, 1.0);
    char* message = "*************************************"; //TEXT TO DISPLAY ON SCREEN
    glRasterPos2f(150, 200); //POSITIONING TEXT ON THE SCREEN
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++); //PRINTING MESSAGE ABOVE IN SPECIFIED FONT
    message = "PACMAN 2.0 "; //GAME NAME
    glColor3f(1, 1, 1);
    glRasterPos2f(300, 250);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "- by Aaron Pan, Vaibhavi Hansrajani, Kwadwo Osafo, Melissa Gibble, Noah Taniguchi"; //TEAM MEMBER NAMES
    glColor3f(1, 1, 1);
    glRasterPos2f(20, 300);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "*************************************";
    glRasterPos2f(150, 350);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "To control Pacman use A (left), D (right), W (up), and S (down)."; //PACMAN CONTOL INSTRUCTIONS
    glRasterPos2f(110, 400);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "To control Ghost 1 use F (left), H (right), T (up), and G (down)."; //GHOST 1 CONTROL INSTRUCTIONS
    glRasterPos2f(112, 450);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "To control Ghost 2 use J (left), L (right), I (up), and K (down)."; //GHOST 2 CONTROL INSTRUCTIONS
    glRasterPos2f(116, 500);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "To control Ghost 3 use 1 (left), 2 (right), 3 (up), and 4 (down)."; //GHOST 3 CONTROL INSTRUCTIONS
    glRasterPos2f(116, 550);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "To start or restart the game, press the space key."; //RESTART GAME CONTROL FUNCTIONS
    glRasterPos2f(170, 600);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
}

//Method to display the screen and its elements
void display(){
    if (points == 1){
        over = false;
    }
    keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);
    gameOver();
    if (replay){
        if (!over){
            drawLaberynth();
            drawFood((1.5 + xIncrement) * squareSize, (1.5 + yIncrement) * squareSize);
            drawPacman(1.5 + xIncrement, 1.5 + yIncrement, rotation);

            //UPDATING THE 3 USER CONTROLLED GHOSTS (COMMENTED OUT THE 4TH)
            updateMonster(monster1, 1);
            updateMonster(monster2, 2);
            updateMonster(monster3, 3);
            // updateMonster(monster4, 4);

            //GHOSTS TURN WHITE WHEN PACMAN POWERMODE ACTIVATED (POWERUP ACTIVATED)
            if(powermode){
                if(!null1)
                    drawMonster(monster1[0], monster1[1], 1.0, 1.0, 1.0); //ALL GHOSTS ARE WHITE WHEN POWERMODE ACTIVATED
                if(!null2)
                    drawMonster(monster2[0], monster2[1], 1.0, 1.0, 1.0);
                if(!null3)
                    drawMonster(monster3[0], monster3[1], 1.0, 1.0, 1.0);
                /*
                if(!null4)
                    drawMonster(monster4[0], monster4[1], 1.0, 1.0, 1.0);
                */
                powermode = powermode - 1;
            }
            //GHOSTS STAY THEIR DEFAULT COLOR WHEN POWERMODE NOT ACTIVATED (POWERUP NOT ACTIVATED)
            else{
                if(!null1)
                    drawMonster(monster1[0], monster1[1], 0.0, 1.0, 1.0); //cyan
                if(!null2)
                    drawMonster(monster2[0], monster2[1], 1.0, 0.0, 0.0); //red
                if(!null3)
                    drawMonster(monster3[0], monster3[1], 1.0, 0.0, 0.6); //magenta
                /*
                if(!null4)
                    drawMonster(monster4[0], monster4[1], 1.0, 0.3, 0.0); //orange
                */
            }
        }
        else {
            resultsDisplay();
        }
    }
    else {
        welcomeScreen();
    }
    glutSwapBuffers();
}

//Method to reshape the game is the screen size changes
void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glOrtho(0, 750, 750, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


//Main functions that controls the running of the game
int main(int argc, char** argv){
    //initialize and create the screen
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutInitWindowPosition(500, 50);
    glutCreateWindow("PACMAN 2.0");

    //define all the control functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp); //THIS FUNCTION DOES NOT COMPILE FOR SOME GLUT HEADER FILES ON WINDOWS

    //run the game
    init();
    glutMainLoop();
    return 0;
}
