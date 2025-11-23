# Incremental Build Plan - City Escape 3D

## Current Status

✅ **TestBasic.cpp** - Basic OpenGL rendering works perfectly
✅ **TestModel.cpp** - 3DS model loading works perfectly
❌ **CityEscape.cpp** - Full game has rendering bugs

## Strategy

Instead of debugging CityEscape.cpp, we'll **incrementally add features to TestModel.cpp** (which works).
This ensures we catch issues early and understand exactly what breaks rendering.

---

## Phase 1: Add Camera Class (Simple Integration)

**Goal**: Replace manual camera variables with Camera class

**Changes to TestModel.cpp**:
1. Include `Camera.h`
2. Replace `camX, camY, camZ, lookX, lookY, lookZ` with Camera object
3. Update keyboard controls to use `camera.moveX/Y/Z()`
4. Test: Should still render exactly the same

**Expected Result**: Green ground, red cube, Jeep model, same as before

**Validation**: Run and verify nothing broke

---

## Phase 2: Add Textured Ground

**Goal**: Add ground texture like CityEscape.cpp has

**Changes**:
1. Include `GLTexture.h` and `TextureBuilder.h`
2. Add `GLTexture tex_ground;`
3. In `loadModel()`, add: `tex_ground.Load("textures/ground.bmp");`
4. Replace simple green quad with `RenderGround()` function from CityEscape.cpp
5. Test rendering

**Expected Result**: Textured ground instead of green plane

**Validation**: Ground texture should be visible and tiled correctly

---

## Phase 3: Add Vector3f Class

**Goal**: Add 3D vector math foundation for Player class

**Changes**:
1. Copy Vector3f class definition from Camera.h into TestModel.cpp (or include Camera.h)
2. Test: No visible change, just adding infrastructure

**Expected Result**: Compiles successfully, no visual change

---

## Phase 4: Add Basic Player Class

**Goal**: Add Player class with model and position (no movement yet)

**Changes**:
1. Include `Player.h`
2. Create `Player* player = NULL;`
3. In loadModel(), create: `player = new Player(&testModel);`
4. In display(), replace direct model drawing with: `player->render();`
5. Test rendering

**Expected Result**: Jeep renders in exact same position, but through Player class

**Validation**: Should look identical to Phase 2

**⚠️ CRITICAL**: If rendering breaks here, we know Player::render() has issues

---

## Phase 5: Add Player Movement

**Goal**: Make the player car move with WASD

**Changes**:
1. Update keyboard handler to call player movement functions:
   - `'w'` → `player->moveForward(0.5f);`
   - `'s'` → `player->moveBackward(0.5f);`
   - `'a'` → `player->turnLeft(5.0f);`
   - `'d'` → `player->turnRight(5.0f);`
2. Add `glutTimerFunc()` to call `player->update(deltaTime)`
3. Test movement

**Expected Result**: Car moves and turns with WASD keys

**Validation**: Car should move smoothly without disappearing

**⚠️ CRITICAL**: If car disappears when moving, there's a transform issue in Player class

---

## Phase 6: Add Camera Following

**Goal**: Make camera follow the player car

**Changes**:
1. In display(), before `camera.look()`, add:
   ```cpp
   Vector3f thirdPersonPos = player->getThirdPersonCameraPos();
   Vector3f thirdPersonLookAt = player->getThirdPersonCameraLookAt();
   camera.eye = thirdPersonPos;
   camera.center = thirdPersonLookAt;
   ```
2. Test camera following

**Expected Result**: Camera follows car from behind and above

**Validation**: Camera should smoothly track car movement

**⚠️ CRITICAL**: If camera breaks, there's an issue in getThirdPersonCameraPos()

---

## Phase 7: Add Single Obstacle

**Goal**: Add one barrel obstacle (no collision yet)

**Changes**:
1. Include `GameObject.h`
2. Add `Model_3DS model_barrel;`
3. Load: `model_barrel.Load("models/obstacles/barrel2/barrel2.3DS");`
4. Create: `Obstacle* testObstacle = new Obstacle(&model_barrel, Vector3f(10, 0, 0), 10);`
5. In display(), call: `testObstacle->render();`
6. Test rendering

**Expected Result**: Barrel visible at position (10, 0, 0)

**Validation**: Barrel should be visible alongside the car

**⚠️ CRITICAL**: If barrel doesn't render, there's an issue in Obstacle::render()

---

## Phase 8: Add Single Collectible

**Goal**: Add one fuel can collectible (no collision yet)

**Changes**:
1. Add `Model_3DS model_fuelcan;`
2. Load: `model_fuelcan.Load("models/collectibles/FeulCan/FeulCan.3DS");`
3. Create: `Collectible* testCollectible = new Collectible(&model_fuelcan, Vector3f(-10, 0, 0), 10);`
4. In display(), call: `testCollectible->render();`
5. Test rendering

**Expected Result**: Fuel can visible at position (-10, 0, 0), possibly rotating

**Validation**: Fuel can should be visible and animating

**⚠️ CRITICAL**: If fuel can doesn't render, there's an issue in Collectible::render()

---

## Phase 9: Add Collision Detection

**Goal**: Detect when player hits obstacle or collectible

**Changes**:
1. Add delta time tracking (like CityEscape.cpp)
2. Create update loop with `glutTimerFunc()`
3. Add collision detection code from CityEscape.cpp:
   ```cpp
   // Check distance between player and obstacle
   if (distance < player->radius + obstacle->radius)
       // Collision!
   ```
4. Print to console when collision occurs
5. Test collisions

**Expected Result**: Console prints "Collision!" when driving into barrel or fuel can

**Validation**: Collisions should be detected accurately

---

## Phase 10: Add Score System

**Goal**: Add score display and update on collisions/pickups

**Changes**:
1. Add `int score = 0;`
2. Implement `RenderHUD()` function from CityEscape.cpp
3. Call `RenderHUD()` at end of display()
4. Update score on collision (-10) and pickup (+10)
5. Test HUD rendering

**Expected Result**: Score displays in top-left corner, updates on events

**Validation**: Score should be visible and update correctly

**⚠️ CRITICAL**: If HUD doesn't render, there's an orthographic projection issue

---

## Phase 11: Add Multiple Objects

**Goal**: Add multiple obstacles and collectibles using vectors

**Changes**:
1. Add `std::vector<Obstacle*> obstacles;`
2. Add `std::vector<Collectible*> collectibles;`
3. Create 5-8 obstacles at different positions
4. Create 5 collectibles at different positions
5. Update display() to loop through vectors and render
6. Update collision detection to check all objects
7. Test with multiple objects

**Expected Result**: Multiple barrels, cones, and fuel cans visible and collidable

**Validation**: All objects should render without issues

**⚠️ CRITICAL**: If rendering slows down significantly, there's a performance issue

---

## Phase 12: Add Skybox

**Goal**: Add skybox sphere from CityEscape.cpp

**Changes**:
1. Add `GLuint tex;` for skybox texture
2. Load: `loadBMP(&tex, "textures/blu-sky-3.bmp", true);`
3. Add skybox rendering code from CityEscape.cpp (lines 338-352)
4. Test skybox rendering

**Expected Result**: Blue sky visible in background

**Validation**: Skybox should be visible and not obstruct other objects

---

## Phase 13: Add First-Person Camera Toggle

**Goal**: Add camera switching with right-click

**Changes**:
1. Add `bool firstPersonView = false;`
2. Implement `myMouse()` function from CityEscape.cpp
3. In display(), check `firstPersonView` and use appropriate camera position
4. Test camera switching

**Expected Result**: Right-click toggles between third-person and first-person views

**Validation**: Both camera views should work correctly

---

## Phase 14: Final Integration

**Goal**: Ensure everything works together

**Changes**:
1. Add any missing features (lighting adjustments, etc.)
2. Test complete gameplay loop:
   - Car movement
   - Camera following
   - Collision detection
   - Score updates
   - HUD display
   - Camera switching
3. Performance check

**Expected Result**: Fully functional game matching CityEscape.cpp requirements

**Validation**: Game should run smoothly at 30+ FPS

---

## Debugging Strategy

If rendering breaks at any phase:

1. **Revert to previous phase** - Go back to last working state
2. **Add debug output** - Print positions, rotations, scales
3. **Render bounding spheres** - Visualize collision boxes
4. **Check OpenGL errors** - Use `glGetError()` after each operation
5. **Simplify** - Remove complex features temporarily
6. **Compare with CityEscape.cpp** - Check for differences in implementation

## Critical Issues to Watch For

1. **Model not rendering**: Check file paths, model loading, glPushMatrix/glPopMatrix
2. **Black screen**: Check lighting setup, material properties, camera position
3. **Flickering**: Check depth buffer clearing, Z-fighting
4. **Wrong size/position**: Check scaling factors, coordinate systems
5. **Performance issues**: Check polygon count, light count, rendering efficiency

## Success Criteria

✅ Each phase builds on the previous without breaking it
✅ We can identify exactly where rendering breaks
✅ Final result matches CityEscape.cpp functionality
✅ Code is cleaner and better understood

---

## Testing Notes

**Environment**: This is a Windows Visual Studio project. Testing should be done on Windows with Visual Studio.

**How to Test Each Phase**:
1. Open `CityEscape.vcxproj` in Visual Studio
2. Set `TestModel.cpp` as the startup file (or create a separate project configuration)
3. Build and run
4. Verify expected results for each phase

---

## Implementation Progress

### ✅ Phase 1: Camera Class Integration (COMPLETED)

**Changes Made**:
- Added `#include "Camera.h"` to TestModel.cpp
- Replaced manual `camX, camY, camZ` variables with `Camera camera(0, 5, 20, 0, 0, 0, 0, 1, 0);`
- Updated `display()` to use `camera.look()` instead of `gluLookAt()`
- Updated `keyboard()` to use `camera.moveX/Y/Z()` methods
- Updated camera position printing to use `camera.eye.x/y/z`

**Expected Result**: Should render exactly the same as before - green ground, red cube, Jeep model

**Files Modified**: `TestModel.cpp`

**Testing**: Compile and run to verify rendering is identical to original

---

## Next Step

**Start with Phase 2**: Add textured ground to TestModel.cpp
