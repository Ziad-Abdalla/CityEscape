# City Escape 3D - Game Development Project

## Project Overview

City Escape 3D is a driving and navigation game built with OpenGL, featuring two levels (daytime city and nighttime industrial zone). Players control a car, avoid obstacles, collect items, and reach target zones.

## Project Status

**Phase**: Foundation Complete ✓
**Version**: 0.1 - Basic Setup

### Completed
- ✅ Project structure created
- ✅ All core source files from Lab 7 integrated (Model_3DS, GLTexture, TextureBuilder)
- ✅ Camera system from Lab 6 Solution integrated
- ✅ Player and GameObject stub classes created
- ✅ Required 3D models copied (Jeep, barrels, fuel cans, etc.)
- ✅ All textures copied (ground, skybox, warning lights, etc.)
- ✅ Visual Studio project file configured
- ✅ Main game loop with basic rendering setup

### Next Steps (Phase 2 - Core Gameplay)
- ⬜ Implement player car movement (WASD controls)
- ⬜ Implement collision detection system
- ⬜ Add obstacles to scene (barrels, cones)
- ⬜ Add collectibles (fuel cans)
- ⬜ Implement scoring system
- ⬜ Camera following player (1st/3rd person views)

## Project Structure

```
CityEscape/
├── CityEscape.cpp          # Main game file
├── Camera.h/cpp            # Camera system (from Lab 6 Solution)
├── Player.h/cpp            # Player car class
├── GameObject.h/cpp        # Base game object classes
├── Model_3DS.h/cpp         # 3DS model loader (from Lab 7)
├── GLTexture.h/cpp         # Texture loader (from Lab 7)
├── TextureBuilder.h        # Texture helpers (from Lab 7)
├── CityEscape.vcxproj      # Visual Studio project file
├── glut.h, glut32.lib      # GLUT library files
├── glaux.h, glaux.lib/dll  # GLAUX library files
├── glew.h, glew32.lib/dll  # GLEW library files
├── models/                 # 3D models folder
│   ├── player/             # Player car (Jeep)
│   ├── obstacles/          # Barrels, cones, boxes, containers
│   ├── collectibles/       # Fuel cans
│   ├── environment/        # Street lights, police cars, arrows
│   └── primitives/         # For future generated models
├── textures/               # Texture files
│   ├── blu-sky-3.bmp       # Skybox texture
│   ├── ground.bmp          # Ground texture
│   ├── CheckeredFlag.bmp   # Target area texture
│   ├── gold.bmp            # Collectible texture
│   ├── redWarning.bmp      # Warning lights
│   └── ...                 # Other textures
└── sounds/                 # Sound files (to be added)
```

## Build Instructions

### Requirements
- **Visual Studio** (2019 or later recommended)
- **Windows** operating system
- **OpenGL** libraries (included in project)

### Building the Project

1. Open `CityEscape.vcxproj` in Visual Studio
2. Select **Debug** or **Release** configuration
3. Select **Win32** platform
4. Build → Build Solution (or press F7)
5. Run → Start Debugging (or press F5)

### Troubleshooting

**Problem**: "Cannot find glut32.dll"
- **Solution**: Copy `glut32.dll`, `glaux.dll`, and `glew32.dll` to the Debug/Release output folder

**Problem**: Models not loading
- **Solution**: Check that the working directory is set to the project folder (where models/ and textures/ folders are)

**Problem**: "legacy_stdio_definitions.lib not found"
- **Solution**: This is normal for newer Visual Studio versions. The linker should find it automatically.

## Controls (Current Implementation)

### Camera Controls
- **W**: Move camera forward
- **S**: Move camera backward
- **A**: Move camera left
- **D**: Move camera right
- **Q**: Move camera up
- **E**: Move camera down
- **Arrow Keys**: Rotate camera
- **Right Mouse Click**: Toggle camera view (placeholder)
- **ESC**: Exit game

### Future Controls (To Be Implemented)
- **W/S**: Car forward/backward
- **A/D**: Car turn left/right
- **Right Mouse Click**: Switch 1st/3rd person camera

## Current Features

### Implemented
- ✅ Basic 3D rendering pipeline
- ✅ 3DS model loading system
- ✅ Texture mapping
- ✅ Camera system with movement and rotation
- ✅ Ground plane rendering
- ✅ Skybox rendering
- ✅ Basic lighting (directional light)
- ✅ Player class structure (not yet controlling car)
- ✅ GameObject base classes (Obstacle, Collectible)

### In Development
- 🔨 Player car movement
- 🔨 Collision detection
- 🔨 Score system
- 🔨 HUD display
- 🔨 Camera following player

## Technical Details

### Libraries Used
- **GLUT**: Windowing and input handling
- **GLAUX**: Texture loading (deprecated but functional)
- **GLEW**: OpenGL extension loading
- **OpenGL**: 3D graphics rendering

### Model Format
- **Primary**: .3DS files (using Model_3DS loader from Lab 7)
- **Secondary**: .OBJ files (for some assets)

### Texture Format
- **BMP**: Primary texture format
- **TGA**: Secondary format (supported by GLTexture)

### Coordinate System
- **Ground Level**: Y = 0
- **Camera Start**: (20, 5, 20) looking at (0, 0, 0)
- **Player Start**: (0, 0, 0)

## Game Design (Planned)

### Level 1: Daytime City Street
- Player car (Jeep)
- Traffic cones and barrels (obstacles)
- Fuel cans and coins (collectibles)
- Street lights (environment + light sources)
- Checkpoint gate (level end)
- Dynamic daylight intensity

### Level 2: Nighttime Industrial Zone
- Police cars (obstacles)
- Crates and containers (obstacles)
- Warning lights (pulsing red beacons)
- Target area with arrows
- Police siren lights (alternating red/blue)
- Dark ambient lighting

## Code Architecture

### Class Hierarchy

```
Camera (Vector3f-based camera system)
  - moveX/Y/Z()
  - rotateX/Y()
  - look()

Player
  - position, rotation
  - moveForward/Backward()
  - turnLeft/Right()
  - render()
  - getCameraPositions()

GameObject (Base class)
  ├── Obstacle
  │   - scorePenalty
  │   - onCollision()
  ├── Collectible
  │   - scoreValue
  │   - rotationAnimation()
  │   - collectionAnimation()
  └── Environment
      - (future)
```

### Rendering Pipeline

1. **Initialization** (`myInit()`):
   - Set up projection matrix
   - Initialize lighting
   - Initialize materials
   - Load camera position

2. **Asset Loading** (`LoadAssets()`):
   - Load 3D models
   - Load textures
   - Initialize player

3. **Display Loop** (`myDisplay()`):
   - Clear buffers
   - Setup camera view
   - Update lighting
   - Render ground
   - Render player
   - Render game objects
   - Render skybox
   - Swap buffers

4. **Input Handling**:
   - Keyboard: WASD, Q/E for camera movement
   - Special keys: Arrow keys for camera rotation
   - Mouse: Right-click for camera switching

## Development Roadmap

See `plan.md` for detailed implementation roadmap.

### Phase 1: Foundation ✅ (Complete)
- Project setup
- Asset integration
- Basic rendering

### Phase 2: Core Gameplay (In Progress)
- Car controls
- Collision detection
- Scoring

### Phase 3: Level 1
- Complete daytime level
- All animations
- Lighting effects

### Phase 4: Level 2
- Nighttime level
- Advanced lighting
- Police car effects

### Phase 5: Polish
- Sound integration
- HUD improvements
- Performance optimization

## Credits

**Base Code**:
- Lab 7: Model_3DS, GLTexture, TextureBuilder classes
- Lab 6 Solution: Camera and Vector3f classes

**Assets**:
- Graphics Project Assets folder (models and textures)

**Development**:
- Based on DMET502 course materials
- City Escape project requirements

## License

Educational project for DMET502 course.

## Notes for Developers

### Current State
The project is in a "compilable foundation" state. The basic rendering pipeline works, models load, and the camera can move freely. The next major step is implementing player car control and collision detection.

### Known Issues
- Player class exists but doesn't control car movement yet
- Camera doesn't follow player (uses free camera from Lab 6)
- No collision detection implemented
- No scoring system
- GameObject classes are stubs

### Quick Start Development
1. Test that project compiles and runs
2. Verify models and textures load correctly
3. Start implementing Phase 2 tasks (see plan.md)
4. Test each feature individually before moving on

### Tips
- Use `printf()` for debugging (shows in console)
- Test with wireframe mode by uncommenting polygon mode toggle
- Camera position is crucial for seeing your scene correctly
- Model scales may need adjustment (use glScalef)

---

**Last Updated**: 2025-11-23
**Status**: Foundation Complete, Ready for Phase 2
