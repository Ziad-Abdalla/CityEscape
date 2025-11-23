# City Escape 3D - Technical Documentation

**Last Updated**: 2025-11-23
**Status**: Phase 1 Complete - Foundation Working
**Version**: 0.2 - Multi-Model Rendering Confirmed

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [Current Project Structure](#current-project-structure)
3. [What Currently Works](#what-currently-works)
4. [Key Technical Details](#key-technical-details)
5. [File Descriptions](#file-descriptions)
6. [Development History](#development-history)
7. [Next Steps](#next-steps)
8. [Future Implementation Plan](#future-implementation-plan)
9. [Known Issues & Solutions](#known-issues--solutions)

---

## Project Overview

City Escape 3D is a 3D driving game built with OpenGL where the player controls a car, avoids obstacles, collects items, and navigates through two levels (daytime city and nighttime industrial zone).

**Technologies:**
- OpenGL (Legacy Fixed Pipeline)
- GLUT (Windowing and Input)
- 3DS Model Loading (Custom Model_3DS class)
- C++ (Visual Studio 2019/2022)

**Target Platform:** Windows

**Project Requirements:** See `City Escape1 (1).pdf` in parent folder

**Full Roadmap:** See `plan.md` in parent folder

---

## Current Project Structure

```
CityEscape/
│
├── CityEscape.cpp                  [MAIN GAME FILE - CURRENTLY WORKING]
│   ├── Loads 5 different 3DS models
│   ├── Renders scene with proper scaling
│   ├── Basic camera movement (WASD/Q/E)
│   └── Reference cube for scale testing
│
├── TestBasic.cpp                   [SIMPLE TEST - REFERENCE ONLY]
│   └── Minimal OpenGL test with colored cubes (confirms OpenGL works)
│
├── Model_3DS.h / .cpp              [3DS MODEL LOADER - FROM LAB 7]
│   ├── Loads .3DS files with textures
│   ├── Handles multiple objects per model
│   ├── Material and texture support
│   └── Draw() method for rendering
│
├── GLTexture.h / .cpp              [TEXTURE LOADER - FROM LAB 7]
│   ├── Loads BMP and TGA files
│   ├── Texture binding and management
│   └── Used by Model_3DS for model textures
│
├── TextureBuilder.h                [TEXTURE HELPERS - FROM LAB 7]
│   └── loadBMP() function for standalone texture loading
│
├── Camera.h / .cpp                 [CAMERA SYSTEM - FROM LAB 6 SOLUTION]
│   ├── Vector3f class (3D vector math)
│   ├── Camera class (position, rotation, look())
│   ├── NOT YET INTEGRATED into main game
│   └── Ready to use for Phase 2
│
├── Player.h / .cpp                 [PLAYER CAR CLASS - STUB]
│   ├── Basic structure created
│   ├── NOT YET USED in main game
│   └── Ready for Phase 3 implementation
│
├── GameObject.h / .cpp             [GAME OBJECT CLASSES - STUB]
│   ├── Base GameObject class
│   ├── Obstacle derived class
│   ├── Collectible derived class
│   ├── NOT YET USED in main game
│   └── Ready for Phase 4 implementation
│
├── CityEscape.vcxproj              [VISUAL STUDIO PROJECT]
│   ├── Configured for Debug/Release x86
│   ├── Currently builds: CityEscape.cpp, Model_3DS, GLTexture
│   └── Links: glut32.lib, glaux.lib, legacy_stdio_definitions.lib
│
├── .gitignore                      [GIT IGNORE FILE]
│   └── Excludes .vs/, Debug/, Release/, *.exe, *.dll, etc.
│
├── glut.h, glut32.lib              [GLUT LIBRARY]
├── glaux.h, glaux.lib, glaux.dll   [GLAUX LIBRARY - DEPRECATED BUT FUNCTIONAL]
├── glew.h, glew32.lib, glew32.dll  [GLEW LIBRARY]
│
├── models/                         [3D MODELS FOLDER]
│   ├── player/
│   │   └── Jeep/Jeep.3ds          [Player car model - WORKING]
│   ├── obstacles/
│   │   ├── barrel2/barrel2.3DS     [Barrel obstacle - WORKING]
│   │   └── TrafficCone/TrafficCone.3DS [Traffic cone - WORKING]
│   ├── collectibles/
│   │   └── FeulCan/FeulCan.3DS    [Fuel can collectible - WORKING]
│   └── environment/
│       └── StreetLight2/StreetLight2.3ds [Street light - WORKING]
│
├── textures/                       [TEXTURE FILES FOLDER]
│   ├── blu-sky-3.bmp              [Skybox texture - NOT YET USED]
│   ├── ground.bmp                 [Ground texture - NOT YET USED]
│   └── [Other textures...]        [Various textures ready for use]
│
├── sounds/                         [SOUND FILES FOLDER - EMPTY]
│   └── [To be added in Phase 5]
│
├── plan.md                         [MASTER IMPLEMENTATION PLAN]
├── README.md                       [SETUP AND BUILD INSTRUCTIONS]
└── documentation.md                [THIS FILE]
```

---

## What Currently Works

### ✅ Confirmed Working (As of 2025-11-23)

**OpenGL Rendering:**
- ✅ Basic OpenGL initialization
- ✅ Depth testing
- ✅ Lighting (GL_LIGHT0 with ambient, diffuse, specular)
- ✅ Color materials
- ✅ Primitive rendering (cubes, quads)
- ✅ Green ground plane (solid color)
- ✅ Blue sky background (clear color)

**3DS Model Loading:**
- ✅ Model_3DS class loads .3DS files successfully
- ✅ Multiple models can be loaded simultaneously
- ✅ Models render with correct geometry
- ✅ Textures embedded in models display correctly
- ✅ 5 different models tested and working:
  1. Jeep (player car)
  2. Barrel (obstacle)
  3. Traffic Cone (obstacle)
  4. Fuel Can (collectible)
  5. Street Light (environment)

**Scaling:**
- ✅ Models scale correctly with glScalef()
- ✅ Proper scale factors determined:
  - Jeep: 0.05
  - Barrel: 0.05
  - Cone: 0.01 (originally larger)
  - Fuel Can: 0.01 (originally larger)
  - Street Light: 0.01 (originally larger)

**Camera Control:**
- ✅ Simple camera movement with WASD keys (moves camera, not car)
- ✅ Q/E for vertical movement
- ✅ Camera position and look-at working correctly

**Build System:**
- ✅ Visual Studio project compiles successfully
- ✅ All library dependencies resolved
- ✅ Debug build working (x86 platform)

### ❌ Not Yet Implemented

**Gameplay:**
- ❌ Player car movement (WASD should move car, not camera)
- ❌ Collision detection
- ❌ Scoring system
- ❌ HUD display

**Camera:**
- ❌ Camera class from Lab 6 not integrated yet
- ❌ First-person view (inside car)
- ❌ Third-person view (following car)
- ❌ Camera switching (right-click)

**Graphics:**
- ❌ Textured ground (using solid green for now)
- ❌ Skybox sphere (using clear color for now)
- ❌ Advanced lighting (flickering, dynamic, etc.)
- ❌ Animations (rotating collectibles, flashing car, etc.)

**Level Design:**
- ❌ Level 1 layout (daytime city)
- ❌ Level 2 layout (nighttime industrial)
- ❌ Level switching
- ❌ Multiple obstacles/collectibles placed

**Sound:**
- ❌ Sound system
- ❌ Sound effects
- ❌ Background music

---

## Key Technical Details

### Model Scale Reference

All models are loaded at different native scales. These scale factors make them proportional:

```cpp
float jeepScale = 0.05f;       // Player car
float barrelScale = 0.05f;     // Obstacles
float coneScale = 0.01f;       // Obstacles (originally 5x larger)
float fuelCanScale = 0.01f;    // Collectibles (originally 5x larger)
float lampScale = 0.01f;       // Environment (originally 5x larger)
```

**Reference:** Red cube is 2 units tall (drawn at position y=1 with size 2.0)

### Camera System (Simple)

Current implementation in CityEscape.cpp:

```cpp
float camX = 0, camY = 5, camZ = 20;  // Camera position
float lookX = 0, lookY = 0, lookZ = 0; // Look-at point

// In display():
gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0, 1, 0);
```

**Controls:**
- W: Move camera forward (camZ -= 1)
- S: Move camera backward (camZ += 1)
- A: Move camera left (camX -= 1)
- D: Move camera right (camX += 1)
- Q: Move camera up (camY += 1)
- E: Move camera down (camY -= 1)

### Lighting Setup

```cpp
GLfloat ambient[] = { 0.3, 0.3, 0.3, 1.0 };     // Dim ambient
GLfloat diffuse[] = { 0.7, 0.7, 0.7, 1.0 };     // Bright diffuse
GLfloat pos[] = { 0.0, 10.0, 0.0, 1.0 };        // Above scene
```

### Model Loading Pattern

```cpp
Model_3DS modelName;

void loadModel() {
    modelName.Load("models/path/to/model.3ds");
}

void display() {
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(scale, scale, scale);
        modelName.Draw();
    glPopMatrix();
}
```

---

## File Descriptions

### CityEscape.cpp (Main Game File)

**Purpose:** Main game loop, rendering, and model management

**Current Contents:**
- Window initialization (1280x720)
- OpenGL state setup
- 5 Model_3DS instances (jeep, barrel, cone, fuelCan, streetLight)
- Simple camera variables
- `init()` - OpenGL initialization
- `loadModel()` - Loads all 5 models
- `display()` - Renders scene with all models
- `keyboard()` - WASD/Q/E camera movement
- `main()` - GLUT setup and main loop

**Lines of Code:** ~197

**Dependencies:** Model_3DS.h, GLTexture.h (via Model_3DS), glut.h

### Model_3DS.h / .cpp

**Purpose:** Load and render .3DS model files

**Source:** Lab 7 (unmodified)

**Key Methods:**
- `Load(const char* filename)` - Load .3DS file
- `Draw()` - Render the model
- Handles materials, textures, multiple objects

**Lines of Code:** ~1400 (cpp)

### GLTexture.h / .cpp

**Purpose:** Load and manage textures

**Source:** Lab 7 (unmodified)

**Key Methods:**
- `Load(const char* filename)` - Load BMP or TGA
- Supports mipmapping
- Automatic texture coordinate generation

**Lines of Code:** ~400 (cpp)

### Camera.h / .cpp

**Purpose:** Advanced camera system with Vector3f math

**Source:** Lab 6 Solution (extracted, not yet used)

**Key Features:**
- Vector3f class with operator overloading
- Camera class with eye/center/up vectors
- moveX/Y/Z() methods
- rotateX/Y() methods
- look() method (calls gluLookAt)

**Status:** Ready to integrate in Phase 2

### Player.h / .cpp

**Purpose:** Player car class

**Status:** Stub implementation, not yet used

**Planned Features:**
- Car position and rotation
- moveForward/Backward()
- turnLeft/Right()
- Camera position getters (1st/3rd person)
- Collision flash effect

### GameObject.h / .cpp

**Purpose:** Base class for game objects

**Status:** Stub implementation, not yet used

**Class Hierarchy:**
```
GameObject (abstract base)
├── Obstacle (barrels, cones, etc.)
├── Collectible (fuel cans, coins, etc.)
└── Environment (street lights, etc.)
```

**Planned Features:**
- Position, rotation, scale
- Bounding sphere collision
- update() and render() methods

---

## Development History

### Phase 0: Initial Setup (Complete)

**Goal:** Get Lab 7 code running as base

**Actions:**
- Created CityEscape project folder
- Copied Model_3DS, GLTexture from Lab 7
- Copied Camera class from Lab 6 Solution
- Created Player and GameObject stub files
- Set up Visual Studio project
- Copied all models and textures from assets folder

**Result:** Project compiles but initial implementation had rendering bugs

### Phase 1: Debugging & Foundation (Complete)

**Problem:** Initial CityEscape.cpp showed "green chaos" - models not rendering correctly

**Diagnosis Process:**
1. Created TestBasic.cpp - confirmed OpenGL works (colored cubes displayed)
2. Created TestModel.cpp - confirmed single model loading works (Jeep displayed)
3. Added multiple models - confirmed multi-model rendering works
4. Identified problem: Original implementation had issues (likely in game logic, not rendering)

**Solution:**
- Deleted broken original CityEscape.cpp
- Renamed TestModel.cpp → CityEscape.cpp
- Now have working foundation with 5 models rendering correctly

**Key Discovery:** Model scaling is critical - different models have vastly different native scales (5x difference!)

**Outcome:** ✅ Stable base to build upon

### Current Status: Ready for Phase 2

We now have a **proven working renderer** with:
- ✅ Multiple 3DS models loading and displaying
- ✅ Proper scaling determined
- ✅ Basic camera control
- ✅ Clean, simple codebase (~200 lines)

---

## Next Steps

### Immediate (Phase 2): Integrate Camera Class

**Goal:** Replace simple camera with Lab 6 Camera class

**Tasks:**
1. Include Camera.h in CityEscape.cpp
2. Replace camera variables with Camera instance
3. Update keyboard handler to use Camera methods
4. Test WASD movement still works
5. Test arrow key rotation

**Expected Time:** 1-2 hours

**Why Important:** Needed for car-following camera in Phase 3

### Phase 3: Player Car Movement

**Goal:** Make car drivable with WASD

**Tasks:**
1. Create Player instance with Jeep model
2. Implement Player::moveForward/Backward()
3. Implement Player::turnLeft/Right()
4. Update keyboard to control Player instead of Camera
5. Update Camera to follow Player (third-person)
6. Add first-person camera position inside car
7. Add right-click to toggle views

**Expected Time:** 4-6 hours

**Why Important:** Core gameplay mechanic

### Phase 4: Collision & Objects

**Goal:** Add obstacles and collectibles with collision

**Tasks:**
1. Create Obstacle instances (barrels, cones)
2. Create Collectible instances (fuel cans)
3. Implement bounding sphere collision
4. Add collision detection loop in update()
5. Test player vs obstacle collision
6. Test player vs collectible collision
7. Add basic scoring system
8. Display score with glutBitmapCharacter

**Expected Time:** 6-8 hours

**Why Important:** Makes it a game, not a tech demo

### Phase 5: Level 1 Complete

**Goal:** Daytime city level with all features

**Tasks:**
1. Add textured ground (ground.bmp)
2. Add skybox sphere (blu-sky-3.bmp)
3. Place ~20 obstacles in level layout
4. Place ~10 collectibles in level layout
5. Add rotating animation to collectibles
6. Add collision flash to player car
7. Add camera shake on collision
8. Add street light flickering
9. Add daylight intensity animation
10. Test full Level 1 gameplay loop

**Expected Time:** 8-12 hours

**Why Important:** First complete level

### Phase 6: Level 2 & Polish

**Goal:** Night-time industrial level + final polish

**Tasks:**
1. Create Level class for level management
2. Implement level switching
3. Design Level 2 layout (industrial theme)
4. Add police cars with siren lights
5. Add warning beacons with rotation
6. Add target area with glow effect
7. Implement night-time lighting
8. Add sound system (if time permits)
9. Bug fixes and optimization
10. Final testing

**Expected Time:** 12-16 hours

**Why Important:** Project completion

---

## Future Implementation Plan

### Detailed Task Breakdown

See `plan.md` for complete 5-phase roadmap with:
- Detailed task lists
- Technical specifications
- Code patterns to reuse
- Success criteria
- Time estimates

### Architecture Evolution

**Current (Phase 1):**
```
CityEscape.cpp
└── Directly renders 5 models with simple camera
```

**Phase 2:**
```
CityEscape.cpp
└── Uses Camera class for movement
```

**Phase 3:**
```
CityEscape.cpp
├── Player instance (controls Jeep)
└── Camera follows Player
```

**Phase 4:**
```
CityEscape.cpp
├── Player
├── vector<Obstacle*> obstacles
├── vector<Collectible*> collectibles
└── Collision detection loop
```

**Phase 5:**
```
CityEscape.cpp
├── Player
├── GameObject collections
├── GLTexture instances (ground, skybox)
├── Animation system
└── Level 1 layout
```

**Phase 6:**
```
CityEscape.cpp
├── Level* currentLevel
│   ├── Level1 (daytime city)
│   └── Level2 (nighttime industrial)
├── Player
├── Score/HUD system
├── Sound system
└── Complete game loop
```

---

## Known Issues & Solutions

### Issue 1: Models Have Different Native Scales

**Problem:** Some models (cone, fuel can, lamp) are 5x larger than others (jeep, barrel)

**Solution:** Use model-specific scale factors (see Key Technical Details)

**Status:** ✅ Solved

### Issue 2: GLUT Exit Function Not Available

**Problem:** `glutLeaveMainLoop()` not defined in this GLUT version

**Solution:** Use standard `exit(0)` instead

**Status:** ✅ Solved

### Issue 3: Model_3DS::Load() Returns Void

**Problem:** Cannot check if model loading succeeded

**Solution:** Assume success, models will be empty if load fails (visible in render)

**Status:** ✅ Workaround in place

### Issue 4: Old GLAUX Dependency

**Problem:** GLAUX is deprecated but Model_3DS uses it for texture loading

**Solution:** Keep using it (works fine), or refactor to use STB_image in future

**Status:** ⚠️ Acceptable for now, low priority to fix

### Issue 5: Visual Studio Cache Files in Git

**Problem:** `.vs/` folder causing permission errors in git

**Solution:** Added `.gitignore` to exclude build artifacts

**Status:** ✅ Solved

---

## Build & Run Guide

### Prerequisites
- Visual Studio 2019 or later
- Windows OS
- OpenGL drivers installed

### Build Steps
1. Open `CityEscape.vcxproj` in Visual Studio
2. Select **Debug** configuration
3. Select **x86** platform (or x64 if configured)
4. Press **Ctrl + Shift + B** to build
5. Press **Ctrl + F5** to run

### Expected Output
- Console window showing model loading progress
- Game window (1280x720) with:
  - Light blue sky
  - Green ground
  - Red reference cube at origin
  - 1 Jeep (center back)
  - 2 Barrels (left side)
  - 2 Traffic Cones (right side)
  - 2 Fuel Cans (front)
  - 2 Street Lights (back)

### Controls (Current)
- **W/S** - Move camera forward/backward
- **A/D** - Move camera left/right
- **Q/E** - Move camera up/down
- **R** - Reload models
- **ESC** - Exit

---

## Reference Documents

- `plan.md` - Complete 5-phase implementation plan
- `README.md` - Setup and build instructions
- `City Escape1 (1).pdf` - Project requirements (in parent folder)
- Lab 7 code - Reference for Model_3DS usage
- Lab 6 Solution - Reference for Camera class
- `D:\Work stash\tes\GraphicsGame2\` - Working reference implementation

---

## Contributing / Handoff Notes

If passing this project to another developer:

1. **Start Here:** Read this documentation.md first
2. **Then:** Read plan.md for detailed roadmap
3. **Current State:** CityEscape.cpp is the main file, it's working and simple
4. **Next Task:** Phase 2 - Integrate Camera class (see Next Steps)
5. **Don't:** Try to fix the old broken code - it's deleted
6. **Do:** Build incrementally on the current working base
7. **Test Often:** Ctrl+F5 after each small change to catch issues early

---

**End of Documentation**

*Generated: 2025-11-23*
*Project: City Escape 3D*
*Status: Phase 1 Complete - Ready for Phase 2*
