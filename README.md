# ComputerGraphics
# Earth-Moon Simulator

This project simulates the Earth-Moon system, including gravitational interactions and satellite trajectories, using OpenGL for rendering. It is implemented in C++ and demonstrates concepts like 3D transformations, object interaction, and camera movement.

## Features
- **Simulation**:
  - Models gravitational interactions between Earth, Moon, and a satellite.
  - Calculates orbital trajectories in real time.
- **Rendering**:
  - Uses OpenGL to display 3D objects (Earth, Moon, and satellite).
  - Supports textures for realistic visual effects.
  - Implements perspective projection and camera manipulation.
- **Camera**:
  - Free movement via keyboard and mouse controls.
  - Real-time adjustments to the viewing perspective.
- **Shaders**:
  - Vertex and fragment shaders written in GLSL for rendering.
  - Uniforms for matrix transformations and texture mapping.

## Setup Instructions
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/YourUsername/EarthMoonSimulator.git
   cd EarthMoonSimulator

2. **Install Dependencies**:
   Ensure you have the following libraries installed on your system:
   - `GLFW`: For creating windows, receiving input, and managing OpenGL contexts.
   - `GLAD`: For managing OpenGL function pointers.
   - `GLM`: For mathematics operations, such as matrix and vector manipulation.
   - `stb_image.h`: For loading image textures.

   On Linux, you can install them via:
   ```bash
   sudo apt-get install libglfw3 libglfw3-dev libglm-dev

3. **Set Up Textures**:
   Create a `resources/textures` folder in the project directory and place the following texture files:
   - `earthSpherical.jpg`: Texture for Earth.
   - `Moon_Spherical.jpg`: Texture for the Moon.
   - `marble.jpg`: Texture for the satellite.

4. **Compile the Code**:
   Use a compiler like `g++` or an IDE (e.g., Visual Studio) to compile the project. If using `g++`, run:
   ```bash
   g++ -o simulator main.cpp -lglfw -lGL -ldl -lGLU

5. **Run the Simulation**:
   After compiling, execute the program:
   ```bash
   ./simulator

## Notes and Limitations
- Ensure the required **resources** folder with textures is included in the project directory. Missing textures will result in rendering errors.
- The simulation assumes idealized orbital mechanics and ignores external forces like solar influence or atmospheric drag.
- The camera controls are basic and may need adjustment for smoother navigation.
- Compatibility:
  - The project is designed for **Linux** and **Windows** platforms.
  - Ensure OpenGL 3.3 or later is supported by your graphics hardware.
- Error handling for missing resources or incompatible environments is minimal.
- The program has been tested only with a fixed set of textures (`earthSpherical.jpg`, `Moon_Spherical.jpg`, `marble.jpg`); adding new textures may require code adjustments.
