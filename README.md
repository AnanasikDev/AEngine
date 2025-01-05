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

### Events

There are two types of events - `Action` and `Func` (much like in C#). `Action` is an event which takes any number of arguments and returns `void` (no output), whereas `Func` is an event which returns a value of some type as well as takes any number of arguments. When implementing a `Func`, first type stands for output.

A function can be subscribed to an event using `Subscribe` method which returns a so called `backdrop` which is `unsigned int` standing for a unique subscription ID (GUID) which is incremented every time any event is being subscribed to. Later, this `backdrop` value can be passed to an `Unsubscribed` method of the same event (if there is no handler (i.e. function) subscribed to the event with such ID, nothing happens).

`Invoke` calls all handlers passing specified arguments.

For example, in UIElement:
```cpp
Action<> onLMBPressedEvent;
backdrop onLMBPressedBackdrop;

onLMBPressedBackdrop = Input::Mouse::LMB.onPressed.Subscribe(
    [this]() {
        if (bounds.isPointInside(Input::getMousePosition())) {
            onLMBPressedEvent.Invoke();
            onLMBPressed();
        }
    } 
);

void UIElement::onLMBPressed() {
}

UIElement::~UIElement() {
    Input::Mouse::LMB.onPressed.Unsubscribe(onLMBPressedBackdrop);
}
```

### Math

All standard vector math functions are implemented (arithmetics, dot/cross product, comparison, magnitude, normalization, abs, distance) along with type conversion, importing from and exporting to sf::Vector2<>, serialization to string and console. There are 7 predefined static const vectors available (up, down, right, left, zero, half, one). Up and down are inverted to SFML directions, meaning the up vector has negative y direction, and down has positive.

`Line` class offers functions for calculating intersections and distances. A `Line` object can represent either a line (infinite) or a segment (limited) (depending on interpretation). Both endpoints can be equal and this case is handled in all calculations.

`Bounds` represents a box, defined by top-left and bottom-right points. There are functions to find an intersection bounds of two bounds objects, along with other useful functions, such as `isPointInside` and `extend`.

Both `Line` and `Bounds` have `render` functions. When rendering, all lines are treated as segments, and bounds are drawn as a wireframe (unfilled).

### Global functions and variables

`context()` returns pointer to the currently active scene.

`window()` returns pointer to the window (not SFML window).

`INF` is a constexpr float set to 10e6f

`mainCamera` is same as `Camera::main`