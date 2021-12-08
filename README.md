# EC327---Project
EC327 Introduction to Software Engineering - Fall 2021
Team Cilantro

Aaron Pan: apan18@bu.edu
Vaibhavi Hansrajani: vhansraj@bu.edu
Kwadwo Osafo: kosafo@bu.edu
Melissa Gibble: mgibble@bu.edu
Noah Taniguchi: ntanigu@bu.edu

Overview:
This program creates a multiplayer pacman game where both pacman and the ghosts are controlled by users. As in traditional pacman, if pacman eats all the food on the board, pacman wins, while if one of the ghosts catches pacman by touching him, the ghosts win. Pacman has powerups spread across the map that allows pacman to eat the ghosts for a short amount of time. Original code was adapted from Patricia Terol, GitHub username patriciateroltolsa.

Build Instructions:
On Windows, you must download GLUT, a toolkit from OpenGL. The zip file will contain 3 files, glut.h, glut.dll, and glut.lib. Copy glut.h into your compiler’s include directory, glut.lib into your build directory, and glut.dll into the executable directory. You can now compile the program using g++ -o nameOfExe.exe -Wall Pacman2.0.cpp -mwindows glut32.lib -lopengl32 -lglu32. Instructions for downloading and running OpenGL libraries adapted from James Madison University Computer Science Department, PDF of full instructions located in misc directory. 

For Mac, download the program and load on Xcode. You will need to add the OpenGL.framework and GLUT.framework libraries in order to make the code compile. Include the following header files,
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#define GL_SILENCE_DEPRECATION
Doing this will successfully create the build and load the game.
