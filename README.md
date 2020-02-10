## LShape

This program is to drawing, translating and animating the LShape.


#### Dependencies
- Program should run in `win32` environment and needs `glut` and `opengl` libraries. Requires OpenGL version 3.1 and later. Program has been written with shaders(`glsl`) in modern OpenGL.

#### Program Modes:

**1.** When game is run, initial 'L' character is drawn where the lower left corner of its bounding rectangle
coincides with (0,0).

![LShape Initial Position](/Screenshots/LShapeInit.png)

**2.** On right click, you can switch to Single Rotation Mode. In single rotation mode, draw the character ’L’ rotated counterclockwise by angle Θ with its reference point located at (x, y)(Middle point of its bottom edge).If
the ’r’ key is pressed in this mode, the angle Θ is incremented by 5 degrees and the shape is redrawn accordingly. ’r’ can be pressed as many times as you want
when in this mode.

![LShape Single Rotation Mode](/Screenshots/LShapeSingleRotation.png)

**3.** When the key ’a’ is pressed, you can switch to animation mode.This mode produces an animation of drawings of the character ’L’ rolling around a circle of
radius 100 centered at (0,0). There will be n drawings in the animation. n is initially set to 8 but you can change it from the code.


![LShape Single Rotation Mode](/Screenshots/LShapeAnimation.png)

#### Yaşar Can Kakdaş
