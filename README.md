2D Mechanical Clock Simulation
This is a C++ project that simulates a mechanical analog clock using the SFML library. It was developed for a Computer Graphics and Visualisation course to demonstrate real-time coordinate transformations and line-drawing algorithms.
+2


Features

Two Startup Options: Sync with your system's hardware clock or manually enter a custom starting time.

Manual Graphics: The clock face and hands are rendered using Mid-point circle logic and Bresenham’s line algorithm.

Real-Time Physics: Uses rotation matrices and trigonometry to calculate the exact hand positions every second.


How to Run

Prerequisites: Ensure you have the SFML development files installed on your system.

Compile: Open your terminal in the project folder and run the following command to link the graphics, window, and system modules:

Bash
g++ -std=c++20 main.cpp Menu.hpp Line.hpp Circle.hpp -o clock_simulation.exe -lsfml-graphics -lsfml-window -lsfml-system
Execute: Run the generated file to start the application:

Bash
./clock_simulation.exe
