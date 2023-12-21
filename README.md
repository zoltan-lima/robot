## COMP0002 C Coursework Submission
#### Project Description
Implement a program that animates a robot moving around a grid of squares enclosed in a rectangular area.\
The robot must:
- Start at a home square.
- Search for markers within the area, and bring them back home.
- Navigate around obstacles.
- Have no knowledge of the layout of the grid and position or number of markers, however, it can know when it is on top of a marker and when a move is invalid.

#### Brief Overview
To accomplish this I chose to implement a DFS (Depth-First Search) algorithm with the use of my own implementations of a stack and a set.\
In order to implement a DFS algorithm, I used the following YouTube video:\
https://www.youtube.com/watch?v=PMMc4VsIacU

Due to the nature of this project, I chose to go for an iterative approach.\
The following GeeksForGeeks link also came in handy:\
https://www.geeksforgeeks.org/depth-first-traversal-dfs-on-a-2d-array/

In my program I have maintained the following rules:
- The grid is 10x10, each square is 75 pixels wide.
- There will be exactly 1 home and the robot will start at the home, facing north.
- The number of markers and obstacles will be specified by the user, through command-line arguments (more on the format later).
- The placement of the markers and obstacles is random on every run of the program.
- The program will terminate once every square has been searched for a marker, and the robot has returned home.

**LIMITATION:** It is possible for markers to be trapped by obstacles during map generation. In this case, the program will still terminate once the robot (finally) returns home -  this is because the robot has no knowledge of the grid or how many markers exist.

#### Files
There are numerous files, this is intended to seperate the different functionalities of the project.\
The header files give an insight to the structures of the different types I have implemented, such as a square type for each square in the grid.

`main.c`\
This file is used as the entry point of the program. It parses command-line arguments and initialises the window, map and robot. It also calls the `traverse` function which starts the robot's search for the markers.

`robot.c`\
Contains all the necessary functions pertaining to the robot's movement, traversal of the grid and picking up of the marker.

`animations.c`\
Contains all the necessary functions to move the robot on the graphical interface.

`map.c`\
Contains all the necessary functions to initialise the map, check if the current square is the home or a marker and if the next move is out of bounds.

`stack.c`\
Contains my basic implementation of a stack.

`set.c`\
Contains my basic implementation of a set.

#### Commands
To compile the program:
`gcc -o main main.c robot.c animations.c map.c stack.c set.c graphics.c`

**NOTE:** Before running the program, don't forget to drag your copies of: `drawapp-x.0.jar`,`graphics.c` and `graphics.h` into the working directory.

To run the program:
`./main {noOfMarkers} {noOfObstacles} | java -jar drawapp-x.0.jar`\
The noOfMarkers and noOfObstacles arguments accept exclusively positive integers that add up to 99. If your input is invalid, the default values (4 markers and 20 obstacles) will be set.