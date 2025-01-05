# SFML C++ Game Engine

AEngine is a lightweight simple SFML-based 2D engine for C++ game development. It features:
1. Physics (forces, collisions, triggers)
2. Rendering (sprites, shapes, text)
3. Scene management
4. Camera
5. GUI (buttons, text)
6. Events
7. Debug (logging, gizmos)
8. Input
9. Random
10. Time (absolute, delta, scale, coroutines)

It has simple component system for built-in classes, namely Rigidbody, Collider and Renderer, making gameobjects customizable. Colliders and renderers can be implemented manually for specific needs (outside of the engine).

## Games

- [Strike]() is a dynamic game about acceleration and control.

## Implementation notes for developers

### Rendering

`Renderer::distance` is distance to camera, i.e. Z coordinate or rendering order. When changed, active scene (which the object is attached to) has to update rendering queue by reordering renderers. It is done automatically in `Renderer::setDistance`. Default value is set to 64 in `static Renderer::defaultDistance`.

`Renderer::origin` is relative origin of the graphics, being a `Vectorf` from (0,0) to (1,1), where (0,0) is top-left corner of the graphics. It is relative (local) position of the origin with default value of (0.5f, 0.5f) (same as `Vectorf::half`) (set in `static Renderer::defaultRelativeOrigin`)

`static TextRenderer::loadFont` has to be called once anytime before rendering text.

`Camera::update` is called each frame right before rendering. It updates screen position of each gameobject (even if no change is registered). Thus, changing `Gameobject::screenPosition` anywhere manually is pointless. This value is relative to the top-left corner of camera, stored in `Camera::cornerPosition` and accessed via `Camera::getCornerPosition`. `Camera::size` is set to window size once in constructor and is never updated.

Engine does not support dynamic window resize at the moment.