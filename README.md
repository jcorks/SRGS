SRGS
====
Simple Raster Graphics Server
-----------------------------
Johnathan Corkery, 2020


SRGS is a simple implementation of baseline behavior expected of a 
graphics context. This is meant to be a 
simple starting point / option for low-resolution graphics 
in contexts where more advanced libraries tied to hardware 
(i.e. OpenGL / DirectX) are not available.


SRGS is meant to be a single-file implementation of graphics 
features that would normally be controlled by dedicated 
hardware. This API is designed to support hardware-accelerated
implementations, but such a thing is not required.
As it is, this library is purely a software rasterizer that is 
limited to only color and depth information with ONLY triangle
primitives. 

Features
--------
- Entire implementation is within a single .c and .h file
- No external dependencies outside the standard C library
- Supports texturing and RGBA image manipulation
- Linear algebra utilities included
- The framebuffer and depth buffer are treated as real textures, meaning features like "render to texture" are inherent.


The reason that the term "server" is used is due to the API 
organization. Note that no pointers are used outside of the 
context pointer and array buffers for bulk data (like 
vertex data), so an implementation with deferred processing
of graphics requests is easily achievable, with perhaps 
the graphics processor being not physically attached to the 
calling machine. And the lack of use of pointers and traditional
structures lends its implementation to be easily bound in 
other languages.


General notes:
--------------
- The origin is the "topleft" at 0, 0
- Once delivered to the renderer, coordinates will be interpreted as homogeneous coordinates. That is, coordiates within [-1, 1] for xyz.
- All pixel/texel information is in RGBA format, where each component is 1 byte.
- The depth buffer is 1 byte. This will likely change depending on how performant the implementation will be.
- Only one primitive is available: triangle.
