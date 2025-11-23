# City Escape 3D - Implementation Plan

## Project Overview

**Game Title**: City Escape 3D
**Genre**: Driving and Navigation Game
**Platform**: Windows (OpenGL, GLUT)
**Development Timeline**: 5 Phases (5 weeks estimated)

---

## 1. Current State Analysis

### Available Resources

#### Lab 7 - 3D Model Loading (PRIMARY FOUNDATION)
- **Location**: `(_DMET502_) 4 - Lab 7 (Other)/`
- **Key Files**:
  - `OpenGLMeshLoader.cpp` - Main entry point with complete rendering pipeline
  - `Model_3DS.h/.cpp` - Fully functional 3DS model loader (1,147 lines)
  - `GLTexture.h/.cpp` - BMP/TGA texture loader (404 lines)
  - `TextureBuilder.h` - Texture helper functions
- **Features**:
  - ✅ 3DS model loading and rendering
  - ✅ Texture loading (BMP, TGA formats)
  - ✅ Basic lighting system
  - ✅ Ground plane rendering with textures
  - ✅ Skybox sphere implementation
  - ✅ Material system

#### Lab 6 Solution - Camera System
- **Location**: `(_DMET502_) 7 - Lab 6 solution (Other) (1)/`
- **Key File**: `Lab6_Solution.cpp`
- **Features**:
  - ✅ Vector3f class for 3D math
  - ✅ Camera class with moveX/Y/Z methods
  - ✅ Camera rotation (rotateX/Y)
  - ✅ WASD + Q/E movement controls
  - ✅ Arrow key rotation controls

#### Graphics Project Assets
- **Location**: `Graphics Project Assets/Graphics Project Assets/`
- **Models Available** (95% coverage):
  - Player: Jeep.3ds, sedan.obj, suv.obj, taxi.obj
  - Obstacles: barrel2.3DS, TrafficCone.3DS, cone.obj, box.obj
  - Collectibles: FeulCan.3DS
  - Environment: StreetLight2.3ds, PoliceCar.3DS
  - Extras: 30+ car models in ManyCars folder
- **Textures Available** (100% coverage):
  - blu-sky-3.bmp (skybox)
  - ground.bmp (ground texture)
  - CheckeredFlag.bmp (target area)
  - gold.bmp (collectibles)
  - redWarning.bmp, redWarning2.bmp (police lights)
  - yellowWarningStripes.bmp
  - metal.bmp, LEDneon.bmp, box.bmp

#### Libraries
- GLUT: glut.h, glut32.lib, glut32.dll
- GLAUX: glaux.h, glaux.lib, glaux.dll
- GLEW: glew.h, glew32.lib, glew32.dll

---

## 2. Project Requirements (from City Escape PDF)

### Gameplay Overview

**Controls**:
- W/A/S/D: Car movement (forward/back, turn left/right)
- Right-click: Switch between 1st person and 3rd person camera

**Objectives**:
- Avoid obstacles (collision reduces score)
- Collect items (increases score)
- Reach final target zone to complete level

**Scoring System**:
- +Points: Item collection
- -Points: Collisions with obstacles
- Display: On-screen HUD

### Level 1 - Daytime City Street

**Required Models** (7 total):
1. ✅ Player Car (controllable) - `Jeep.3ds`
2. ✅ Traffic Cone (obstacle) - `TrafficCone.3DS` / `cone.obj`
3. ✅ Barrel (obstacle) - `barrel2.3DS`
4. ✅ Fuel Can (collectible) - `FeulCan.3DS`
5. ✅ Street Light (obstacle + light source) - `StreetLight2.3ds`
6. ⚠️ Small Coin/Token (collectible) - **CREATE with glutSolidTorus + gold.bmp**
7. ⚠️ Checkpoint Gate (arch/fence) - **CREATE with primitives**

**Lighting Requirements**:
- Daylight intensity animation (morning → afternoon)
- Street light flickering (random intensity variation)

**Animations**:
- Collectible: Rotate and scale up before disappearing
- Collision: Car flashes red + camera shake
- Sound on collectible pickup

### Level 2 - Night-time Industrial Zone

**Required Models** (7 total):
1. ✅ Police Car (patrolling obstacle) - `PoliceCar.3DS` / `police.obj`
2. ✅ Barrel (reused from Level 1) - `barrel2.3DS`
3. ✅ Crate/Wooden Box (obstacle) - `box.obj`
4. ✅ Fuel Can (reused from Level 1) - `FeulCan.3DS`
5. ✅ Metal Container (obstacle) - Available in `ManyContainers/`
6. ⚠️ Warning Light (sphere with red texture) - **CREATE with glutSolidSphere + redWarning.bmp**
7. **Final Target Area**:
   - ✅ Landing Marker Circle - **CREATE textured plane with CheckeredFlag.bmp**
   - ✅ Large Arrow Sign - `arrow2.obj`, `arrow3.obj`, `arrow4.obj`
   - Checkpoint Gate (glowing) - **Reuse from Level 1**

**Lighting Requirements**:
- Dark ambient lighting (night-time)
- Police siren lights (alternating red/blue with glLightfv)
- Warning beacon lights (rotating + pulsing red)
- Target area glow effect (pulsing light intensity)

**Animations**:
- All Level 1 animations
- Police siren alternating colors
- Warning beacon rotation
- Target area pulse/glow

### Camera System Requirements

**First-Person POV**:
- Camera inside car (driver view)
- Forward-facing perspective
- HUD overlay visible

**Third-Person POV**:
- Camera behind and above car
- Follow car position and rotation
- Smooth tracking

**Switching**:
- Mouse right-click toggles between views
- Smooth transition (optional)

---

## 3. Project Architecture

### Proposed File Structure

```
CityEscape/
│
├── CityEscape.cpp                  [Main game loop, initialization, rendering]
├── CityEscape.vcxproj              [Visual Studio project file]
│
├── Model_3DS.h                     [3DS model loader header - FROM LAB 7]
├── Model_3DS.cpp                   [3DS model loader implementation - FROM LAB 7]
├── GLTexture.h                     [Texture loader header - FROM LAB 7]
├── GLTexture.cpp                   [Texture loader implementation - FROM LAB 7]
├── TextureBuilder.h                [Texture helpers - FROM LAB 7]
│
├── Camera.h                        [Camera class header - FROM LAB 6 SOLUTION]
├── Camera.cpp                      [Camera implementation - FROM LAB 6 SOLUTION]
│
├── Player.h                        [Player car class header - NEW]
├── Player.cpp                      [Player car implementation - NEW]
│
├── GameObject.h                    [Base game object class - NEW]
├── GameObject.cpp                  [Base implementation - NEW]
│
├── CollisionSystem.h               [Collision detection - NEW]
├── CollisionSystem.cpp             [Collision implementation - NEW]
│
├── Level.h                         [Level management - NEW]
├── Level.cpp                       [Level implementation - NEW]
│
├── Lighting.h                      [Advanced lighting animations - NEW]
├── Lighting.cpp                    [Lighting implementation - NEW]
│
├── Score.h                         [Score system and HUD - NEW]
├── Score.cpp                       [Score implementation - NEW]
│
├── glut.h, glut32.lib, glut32.dll  [GLUT library - FROM LAB 7]
├── glaux.h, glaux.lib, glaux.dll   [GLAUX library - FROM LAB 7]
├── glew.h, glew32.lib, glew32.dll  [GLEW library - FROM LAB 7]
│
├── models/                         [3D models folder]
│   ├── player/
│   │   ├── Jeep.3ds
│   │   └── Jeep_textures/
│   ├── obstacles/
│   │   ├── barrel2.3DS
│   │   ├── TrafficCone.3DS
│   │   ├── cone.obj
│   │   ├── box.obj
│   │   └── container.glb
│   ├── collectibles/
│   │   └── FeulCan.3DS
│   ├── environment/
│   │   ├── StreetLight2.3ds
│   │   ├── PoliceCar.3DS
│   │   ├── police.obj/mtl
│   │   ├── arrow2.obj
│   │   ├── arrow3.obj
│   │   └── arrow4.obj
│   └── primitives/
│       [For generated models: coins, gates, warning lights]
│
├── textures/                       [Texture files]
│   ├── blu-sky-3.bmp
│   ├── ground.bmp
│   ├── CheckeredFlag.bmp
│   ├── gold.bmp
│   ├── redWarning.bmp
│   ├── redWarning2.bmp
│   ├── yellowWarningStripes.bmp
│   ├── metal.bmp
│   ├── LEDneon.bmp
│   └── box.bmp
│
└── sounds/                         [Sound files - TO BE ADDED]
    ├── collectible.wav
    ├── collision.wav
    └── background.wav
```

### Class Architecture

#### Camera Class (from Lab 6 Solution)
```cpp
class Vector3f {
public:
    float x, y, z;
    Vector3f(float x = 0, float y = 0, float z = 0);
    Vector3f operator+(Vector3f& v);
    Vector3f operator-(Vector3f& v);
    Vector3f operator*(float n);
    Vector3f unit();
    Vector3f cross(Vector3f v);
};

class Camera {
public:
    Vector3f eye, center, up;
    Camera(float eyeX, float eyeY, float eyeZ, ...);
    void moveX(float d);
    void moveY(float d);
    void moveZ(float d);
    void rotateX(float a);
    void rotateY(float a);
    void look();
};
```

#### Player Class (NEW)
```cpp
class Player {
private:
    Vector3f position;
    Vector3f rotation;
    float speed;
    float turnSpeed;
    Model_3DS* carModel;

public:
    Player(Model_3DS* model);
    void update(float deltaTime);
    void handleInput(unsigned char key);
    void moveForward(float amount);
    void moveBackward(float amount);
    void turnLeft(float amount);
    void turnRight(float amount);
    void render();
    Vector3f getPosition();
    Vector3f getRotation();
    Vector3f getFirstPersonCameraPos();
    Vector3f getThirdPersonCameraPos();
};
```

#### GameObject Class (NEW - Base)
```cpp
enum ObjectType {
    OBSTACLE,
    COLLECTIBLE,
    ENVIRONMENT
};

class GameObject {
protected:
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;
    Model_3DS* model;
    ObjectType type;
    bool isActive;
    float boundingRadius;

public:
    GameObject(Model_3DS* model, ObjectType type);
    virtual void update(float deltaTime) = 0;
    virtual void render();
    virtual void onCollision();
    bool checkCollision(GameObject* other);
    Vector3f getPosition();
    float getBoundingRadius();
    bool getActive();
    void setActive(bool active);
};
```

#### Obstacle Class (NEW - Derived)
```cpp
class Obstacle : public GameObject {
private:
    int scorepenalty;

public:
    Obstacle(Model_3DS* model, Vector3f position);
    void update(float deltaTime) override;
    void onCollision() override;
};
```

#### Collectible Class (NEW - Derived)
```cpp
class Collectible : public GameObject {
private:
    int scoreValue;
    float rotationSpeed;
    float currentRotation;
    bool isBeingCollected;
    float collectionTime;

public:
    Collectible(Model_3DS* model, Vector3f position, int score);
    void update(float deltaTime) override;
    void onCollision() override;
    void playCollectionAnimation();
};
```

---

## 4. Implementation Roadmap

### Phase 1: Foundation (Week 1)

**Goal**: Set up project structure and basic rendering

**Tasks**:
1. ✅ Create CityEscape project folder
2. ✅ Copy Lab 7 files (Model_3DS, GLTexture, TextureBuilder, main structure)
3. ✅ Copy Lab 6 Solution Camera class to separate files
4. ✅ Copy all required models and textures
5. ✅ Copy library files (GLUT, GLAUX, GLEW)
6. ✅ Set up Visual Studio project
7. ⬜ Load and render player car model (Jeep.3ds)
8. ⬜ Implement basic ground plane rendering
9. ⬜ Implement skybox rendering
10. ⬜ Integrate Camera class with basic movement
11. ⬜ Test basic WASD camera movement

**Success Criteria**:
- Project compiles without errors
- Jeep model loads and renders correctly
- Ground and skybox visible
- Camera moves with WASD keys

**Estimated Time**: 8-12 hours

---

### Phase 2: Core Gameplay (Week 2)

**Goal**: Implement player car control and collision detection

**Tasks**:
1. ⬜ Create Player class (Player.h/.cpp)
2. ⬜ Implement car movement (forward/backward)
3. ⬜ Implement car turning (left/right)
4. ⬜ Make car responsive to WASD keys
5. ⬜ Create GameObject base class
6. ⬜ Create Obstacle derived class
7. ⬜ Create Collectible derived class
8. ⬜ Load obstacle models (barrel, traffic cone)
9. ⬜ Load collectible model (fuel can)
10. ⬜ Place test obstacles in scene
11. ⬜ Place test collectibles in scene
12. ⬜ Implement bounding sphere collision detection
13. ⬜ Test collision between player and obstacles
14. ⬜ Test collision between player and collectibles
15. ⬜ Create Score class for HUD
16. ⬜ Display score on screen with glutBitmapCharacter
17. ⬜ Update score on collectible pickup
18. ⬜ Update score on obstacle collision

**Success Criteria**:
- Car moves forward/backward with W/S
- Car turns left/right with A/D
- Collision detection works (console log for now)
- Score displays and updates correctly
- Collectibles disappear when collected

**Estimated Time**: 16-20 hours

---

### Phase 3: Camera System & Level 1 (Week 3)

**Goal**: Implement camera switching and complete Level 1

**Tasks**:

**Camera System**:
1. ⬜ Adapt Camera class to follow player car
2. ⬜ Implement first-person camera position (inside car)
3. ⬜ Implement third-person camera position (behind/above car)
4. ⬜ Add mouse right-click detection
5. ⬜ Implement camera mode switching
6. ⬜ Test smooth camera transitions

**Level 1 Layout**:
7. ⬜ Design Level 1 street layout on paper
8. ⬜ Place traffic cones along road edges
9. ⬜ Place barrels as obstacles
10. ⬜ Place street lights with proper spacing
11. ⬜ Place fuel can collectibles strategically
12. ⬜ Create coin/token model (glutSolidTorus + gold texture)
13. ⬜ Place coins throughout level
14. ⬜ Create checkpoint gate model (primitives)
15. ⬜ Place checkpoint gate at level end

**Lighting**:
16. ⬜ Set up directional daylight (GL_LIGHT0)
17. ⬜ Implement daylight intensity animation (time-based)
18. ⬜ Add point lights to street lights (GL_LIGHT1-7)
19. ⬜ Implement street light flickering (random intensity)

**Animations**:
20. ⬜ Implement collectible rotation animation
21. ⬜ Implement collectible scale-up on collection
22. ⬜ Implement car red flash on collision (material color change)
23. ⬜ Implement camera shake on collision (position jitter)
24. ⬜ Add timer-based animation system

**Polish**:
25. ⬜ Adjust lighting parameters for daytime look
26. ⬜ Fine-tune collision detection
27. ⬜ Balance score values
28. ⬜ Test complete Level 1 gameplay loop

**Success Criteria**:
- Camera switches between 1st/3rd person with right-click
- First-person view is inside car looking forward
- Third-person view follows car smoothly
- All Level 1 models placed and textured
- Daylight intensity changes over time
- Street lights flicker randomly
- Collectibles rotate and animate on pickup
- Car flashes red and camera shakes on collision
- Level 1 is playable start to finish

**Estimated Time**: 20-24 hours

---

### Phase 4: Level 2 - Night-time Industrial (Week 4)

**Goal**: Create Level 2 with advanced lighting

**Tasks**:

**Level Management**:
1. ⬜ Create Level class (Level.h/.cpp)
2. ⬜ Implement level loading system
3. ⬜ Implement level switching logic
4. ⬜ Add level completion detection (checkpoint gate)
5. ⬜ Reset player position on level switch

**Level 2 Layout**:
6. ⬜ Design Level 2 industrial layout
7. ⬜ Place police cars as obstacles
8. ⬜ Place barrels (reused from Level 1)
9. ⬜ Place crates/boxes as obstacles
10. ⬜ Place metal containers as obstacles
11. ⬜ Create warning light model (glutSolidSphere + redWarning texture)
12. ⬜ Place warning lights throughout level
13. ⬜ Create landing marker circle (textured plane + CheckeredFlag.bmp)
14. ⬜ Place arrow models around target area
15. ⬜ Place final checkpoint gate (glowing)

**Night-time Lighting**:
16. ⬜ Reduce ambient lighting for night-time
17. ⬜ Add spot lights to police cars
18. ⬜ Implement police siren lights (alternating red/blue)
19. ⬜ Use glLightfv to change light colors dynamically
20. ⬜ Implement warning beacon rotation (light position rotation)
21. ⬜ Implement warning beacon pulsing (intensity sine wave)
22. ⬜ Add glow effect to target area (pulsing light)
23. ⬜ Adjust material properties for night visibility

**Advanced Animations**:
24. ⬜ Police siren color alternation (timer-based)
25. ⬜ Warning beacon rotation around Y-axis
26. ⬜ Warning beacon intensity pulsing
27. ⬜ Target area glow pulsing (scale + light intensity)

**Testing**:
28. ⬜ Test Level 1 → Level 2 transition
29. ⬜ Test Level 2 completion
30. ⬜ Verify all lighting animations work
31. ⬜ Check performance (frame rate)

**Success Criteria**:
- Level 1 transitions to Level 2 on completion
- Night-time lighting creates dark atmosphere
- Police cars have alternating red/blue siren lights
- Warning beacons rotate and pulse red
- Target area glows and pulses
- Level 2 is playable start to finish
- Both levels work correctly in sequence

**Estimated Time**: 20-24 hours

---

### Phase 5: Polish & Sound (Week 5)

**Goal**: Add sound, improve visuals, optimize

**Tasks**:

**Sound Integration** (Optional - if time permits):
1. ⬜ Choose sound library (OpenAL or FMOD)
2. ⬜ Find/create sound effects (collectible, collision, background)
3. ⬜ Integrate sound library
4. ⬜ Add collectible pickup sound
5. ⬜ Add collision sound
6. ⬜ Add background music (different for each level)
7. ⬜ Test sound timing and volume

**Visual Polish**:
8. ⬜ Add fog for depth perception (optional)
9. ⬜ Improve HUD design (score, level indicator)
10. ⬜ Add particle effects for collisions (optional)
11. ⬜ Improve skybox textures if needed
12. ⬜ Add shadows (basic shadow mapping - optional)

**Gameplay Refinement**:
13. ⬜ Balance difficulty (obstacle placement)
14. ⬜ Adjust car speed and handling
15. ⬜ Fine-tune collision detection (reduce false positives)
16. ⬜ Adjust camera distances for better view
17. ⬜ Add game over / level complete screens
18. ⬜ Add restart functionality

**Optimization**:
19. ⬜ Profile frame rate
20. ⬜ Optimize rendering (frustum culling if needed)
21. ⬜ Reduce polygon count of complex models if lagging
22. ⬜ Optimize collision detection (spatial partitioning if needed)

**Bug Fixes**:
23. ⬜ Fix any reported bugs
24. ⬜ Test edge cases (car getting stuck, etc.)
25. ⬜ Memory leak testing

**Documentation**:
26. ⬜ Create README.md with build instructions
27. ⬜ Document controls in-game or in README
28. ⬜ Add code comments for complex sections

**Success Criteria**:
- Game runs smoothly (30+ FPS)
- Sound effects work correctly
- HUD is clear and readable
- Game is fun to play
- No major bugs
- Documentation is complete

**Estimated Time**: 16-20 hours

---

## 5. Technical Specifications

### Model Loading
- **Primary Format**: .3DS (using Lab 7's Model_3DS class)
- **Secondary Format**: .OBJ (if OBJ loader is added later)
- **Texture Format**: BMP (primary), TGA (secondary)
- **Model Scale**: Adjust with glScalef() as needed

### Collision Detection
- **Method**: Bounding sphere collision (simple, fast)
- **Formula**: `distance(A, B) < radiusA + radiusB`
- **Future**: Upgrade to AABB (Axis-Aligned Bounding Box) if needed

### Lighting System
- **GL_LIGHT0**: Directional sunlight (Level 1) / moonlight (Level 2)
- **GL_LIGHT1-3**: Street lights (Level 1)
- **GL_LIGHT4-6**: Police sirens and warning beacons (Level 2)
- **GL_LIGHT7**: Target area glow (Level 2)
- **Dynamic Updates**: Use glLightfv() in render loop for animations

### Camera System
- **First-Person**: Camera at (carX, carY + 1.5, carZ), looking at (carX + forward.x, carY + 1.5, carZ + forward.z)
- **Third-Person**: Camera at (carX - forward.x * 8, carY + 4, carZ - forward.z * 8), looking at car
- **Smooth Follow**: Interpolate camera position (optional)

### Animation System
- **Timer-Based**: Use glutGet(GLUT_ELAPSED_TIME) for time
- **Delta Time**: Calculate time since last frame for smooth animations
- **Interpolation**: Linear interpolation for smooth transitions

### Text Rendering (HUD)
- **Method**: glutBitmapCharacter() with GLUT_BITMAP_HELVETICA_18
- **Position**: Orthographic projection overlay
- **Content**: Score, level indicator, controls hint

### Input Handling
- **Keyboard**: glutKeyboardFunc() for W/A/S/D
- **Mouse**: glutMouseFunc() for right-click camera switch
- **Continuous Input**: Track key states for smooth movement

---

## 6. Code Reuse Strategy

### From Lab 7 (OpenGLMeshLoader.cpp)

**InitLightSource()** (Lines 52-76):
```cpp
// Use as template for basic lighting setup
// Modify ambient/diffuse/specular for day/night
```

**InitMaterial()** (Lines 81-97):
```cpp
// Use for default material properties
// Override for special effects (car flash)
```

**RenderGround()** (Lines 140-167):
```cpp
// Use directly for ground plane
// Adjust size for street layout
```

**LoadAssets()** (Lines 316-325):
```cpp
// Template for loading all models and textures
// Expand to load player, obstacles, collectibles
```

**Skybox Rendering** (Lines 130-138):
```cpp
// Use gluSphere for skybox
// Already working with blu-sky-3.bmp
```

### From Lab 6 Solution (Lab6_Solution.cpp)

**Vector3f Class** (Lines 9-56):
```cpp
// Use directly - complete 3D vector math
// Supports +, -, *, cross product, unit vector
```

**Camera Class** (Lines 58-94):
```cpp
// Extend for car-following behavior
// Add setPosition() and setLookAt() methods
```

**Keyboard Handler** (Lines 216-238):
```cpp
// Adapt for car controls instead of camera
// W/S for forward/back, A/D for turn
```

### From Model_3DS Class (Lab 7)

**Loading Models**:
```cpp
Model_3DS model;
model.Load("models/player/Jeep.3ds");
```

**Rendering Models**:
```cpp
glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angle, 0, 1, 0);
    glScalef(scale, scale, scale);
    model.Draw();
glPopMatrix();
```

---

## 7. Development Best Practices

### Version Control
- Commit after each major feature
- Use descriptive commit messages
- Keep Lab 7 files unchanged for reference

### Testing
- Test each feature in isolation before integrating
- Keep a test level with single objects
- Use console output (printf) for debugging

### Performance
- Monitor frame rate with FPS counter
- Limit number of active lights (max 8)
- Use frustum culling for off-screen objects (if needed)

### Code Organization
- One class per file pair (.h/.cpp)
- Use meaningful variable names
- Comment complex algorithms
- Keep functions small and focused

### Debugging Tips
- Use glGetError() to check OpenGL errors
- Render bounding spheres for collision debugging
- Print camera position/rotation for camera debugging
- Use wireframe mode (glPolygonMode) to debug models

---

## 8. Success Criteria Checklists

### Level 1 Complete Checklist

**Models & Rendering**:
- [ ] Player car loads and renders with correct texture
- [ ] Traffic cones placed and visible
- [ ] Barrels placed and visible
- [ ] Fuel cans placed and visible
- [ ] Street lights placed and visible
- [ ] Coins/tokens visible (primitive or model)
- [ ] Checkpoint gate at end of level
- [ ] Ground plane textured correctly
- [ ] Skybox visible and seamless

**Gameplay**:
- [ ] W/S moves car forward/backward
- [ ] A/D turns car left/right
- [ ] Car movement feels responsive
- [ ] Collision with obstacles stops car
- [ ] Collision with obstacles reduces score
- [ ] Collision with collectibles adds score
- [ ] Collectibles disappear when collected
- [ ] Can reach checkpoint gate

**Camera**:
- [ ] First-person view is inside car
- [ ] Third-person view is behind/above car
- [ ] Right-click switches between views
- [ ] Camera follows car in both modes
- [ ] Camera rotates with car in 3rd person

**Lighting & Animations**:
- [ ] Daylight intensity changes over time
- [ ] Street lights flicker randomly
- [ ] Collectibles rotate continuously
- [ ] Collectibles scale up when collected
- [ ] Car flashes red on collision
- [ ] Camera shakes on collision

**HUD**:
- [ ] Score displays on screen
- [ ] Score updates correctly
- [ ] Level indicator shows "Level 1"

**Sound** (Optional):
- [ ] Collectible pickup sound plays
- [ ] Collision sound plays
- [ ] Background music plays

---

### Level 2 Complete Checklist

**Models & Rendering**:
- [ ] Police cars placed and visible
- [ ] Barrels placed (reused)
- [ ] Crates/boxes placed and visible
- [ ] Metal containers placed and visible
- [ ] Warning lights placed and visible
- [ ] Landing marker circle textured correctly
- [ ] Arrow signs around target area
- [ ] Final checkpoint gate glowing
- [ ] Night-time atmosphere (dark)

**Gameplay**:
- [ ] Level 1 transitions to Level 2 correctly
- [ ] All Level 1 gameplay features work in Level 2
- [ ] Reaching target area completes level
- [ ] Can restart or return to Level 1

**Lighting**:
- [ ] Ambient lighting is darker (night-time)
- [ ] Police cars have red/blue alternating lights
- [ ] Siren lights illuminate surroundings
- [ ] Warning beacons emit pulsing red light
- [ ] Warning beacons rotate around axis
- [ ] Target area has pulsing glow effect
- [ ] All light animations are smooth

**Advanced Animations**:
- [ ] Police siren colors alternate (red ↔ blue)
- [ ] Warning beacons rotate visibly
- [ ] Warning beacon intensity pulses
- [ ] Target area scales and glows in rhythm

**Performance**:
- [ ] Frame rate stays above 30 FPS
- [ ] No stuttering during animations
- [ ] Level loads quickly

---

## 9. Risk Assessment & Mitigation

### High-Risk Items

**Risk**: OBJ model loading not working (if needed)
- **Mitigation**: Stick to .3DS files (Lab 7 loader proven)
- **Fallback**: Use primitive shapes (glutSolid*)

**Risk**: Collision detection too slow with many objects
- **Mitigation**: Implement spatial partitioning (grid-based)
- **Fallback**: Limit number of active collidable objects

**Risk**: Advanced lighting animations cause performance issues
- **Mitigation**: Optimize light count, use simpler animations
- **Fallback**: Make animations optional/toggleable

**Risk**: Sound integration is time-consuming
- **Mitigation**: Treat as optional bonus feature
- **Fallback**: Submit without sound, add later

### Medium-Risk Items

**Risk**: Camera switching feels jarring
- **Mitigation**: Add smooth interpolation between camera positions
- **Fallback**: Instant switching is acceptable per requirements

**Risk**: Car movement feels unresponsive or floaty
- **Mitigation**: Add acceleration/deceleration, tweak speed values
- **Fallback**: Keep simple direct control (acceptable)

**Risk**: Text rendering (HUD) is difficult
- **Mitigation**: Use glutBitmapCharacter (simple, proven)
- **Fallback**: Console output for debugging, add HUD later

---

## 10. Resources & References

### OpenGL Documentation
- **GLUT**: https://www.opengl.org/resources/libraries/glut/
- **Lighting**: https://www.khronos.org/opengl/wiki/Lighting
- **Textures**: https://www.khronos.org/opengl/wiki/Texture

### Tutorials
- NeHe OpenGL Tutorials (http://nehe.gamedev.net/)
  - Lesson 6: Texture Mapping
  - Lesson 7: Lighting
  - Lesson 10: 3D World
- OpenGL-Tutorial.org
  - Tutorial 5: Textured Cube
  - Tutorial 8: Basic Shading

### Math References
- 3D Vector Math: http://www.songho.ca/math/vector/vector.html
- Camera Systems: https://learnopengl.com/Getting-started/Camera

### Asset Creation
- Blender (free 3D modeling): https://www.blender.org/
- GIMP (free texture editing): https://www.gimp.org/
- Audacity (free sound editing): https://www.audacityteam.org/

---

## 11. Timeline Summary

| Phase | Duration | Focus | Deliverable |
|-------|----------|-------|-------------|
| Phase 1 | Week 1 (8-12h) | Foundation | Project compiles, basic rendering works |
| Phase 2 | Week 2 (16-20h) | Core Gameplay | Car controls, collision, scoring |
| Phase 3 | Week 3 (20-24h) | Level 1 | Complete Level 1 with all features |
| Phase 4 | Week 4 (20-24h) | Level 2 | Complete Level 2 with advanced lighting |
| Phase 5 | Week 5 (16-20h) | Polish | Sound, optimization, bug fixes |

**Total Estimated Time**: 80-100 hours (5 weeks @ 16-20 hours/week)

---

## 12. Next Steps (Immediate Actions)

1. ✅ **Create CityEscape project folder**
2. ✅ **Copy Lab 7 source files** (Model_3DS, GLTexture, TextureBuilder, main cpp)
3. ✅ **Extract Camera class** from Lab 6 Solution into separate files
4. ✅ **Copy all required models** from Graphics Project Assets
5. ✅ **Copy all textures** from Graphics Project Assets
6. ✅ **Copy library files** (GLUT, GLAUX, GLEW)
7. ✅ **Set up Visual Studio project file**
8. ⬜ **Compile and test** - ensure Lab 7 functionality works in new project
9. ⬜ **Load player car model** - replace Lab 7's house/tree with Jeep
10. ⬜ **Test basic rendering** - car, ground, skybox

---

## 13. Conclusion

This project is **highly feasible** with the available resources. The heavy lifting (3DS loading, texture management, basic lighting) is already done in Lab 7. The main development effort will focus on:

1. **Game Logic**: Player controls, collision detection, scoring
2. **Animation Systems**: Collectibles, lighting effects, camera shake
3. **Level Design**: Placing objects, designing layouts
4. **Polish**: HUD, sound, optimization

With a systematic approach following this 5-phase plan, the City Escape 3D game can be completed successfully within the estimated timeline.

**Critical Success Factors**:
- Leverage Lab 7's proven code (don't reinvent the wheel)
- Implement features incrementally (test each phase before moving on)
- Keep it simple (don't over-engineer)
- Focus on requirements (avoid scope creep)

Good luck with the implementation!
