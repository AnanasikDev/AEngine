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

It has simple component system for built-in classes, namely Rigidbody, Collider and Renderer, making gameobjects customizable. More implementations of collider and renderer can be added (at the moment it's impossible without changing the engine core however).

## Games

- [Strike](https://github.com/AnanasikDev/AEngine/tree/main/Game) is a dynamic game about acceleration and control.

## Implementation notes for developers

### Rendering

`Renderer::distance` is distance to camera, i.e. Z coordinate or rendering order. When changed, active scene (which the object is attached to) has to update rendering queue by reordering renderers. It is done automatically in `Renderer::setDistance`. Default value is set to 64 in `static Renderer::defaultDistance`.

`Renderer::origin` is relative origin of the graphics, being a `Vectorf` from (0,0) to (1,1), where (0,0) is top-left corner of the graphics. It is relative (local) position of the origin with default value of (0.5f, 0.5f) (same as `Vectorf::half`) (set in `static Renderer::defaultRelativeOrigin`)

`static TextRenderer::loadFont` has to be called once anytime before rendering text.

`Camera::update` is called each frame right before rendering. It updates screen position of each gameobject (even if no change is registered). Thus, changing `Gameobject::screenPosition` anywhere manually is pointless. This value is relative to the top-left corner of camera, stored in `Camera::cornerPosition` and accessed via `Camera::getCornerPosition`. `Camera::size` is set to window size once in constructor and is never updated.

Engine does not support dynamic window resize at the moment.

### Events

There are two types of events - `Action` and `Func` (much like in C#). `Action` is an event which takes any number of arguments and returns `void` (no output), whereas `Func` is an event which returns a value of some type as well as takes any number of arguments. When implementing a `Func`, first type stands for output. Both classes are templates.

A function can be subscribed to an event using `Subscribe` method which returns a so called `backdrop` which is `unsigned int` standing for a unique subscription ID (GUID) which is incremented every time any event is being subscribed to. Later, this `backdrop` value can be passed to the `Unsubscribe` method of the same event (if there is no handler (i.e. function) subscribed to the event with such ID, nothing happens).

`Invoke` calls all handlers passing specified arguments.

For example, in UIElement:
```cpp
Action<> onLMBPressedEvent;
backdrop onLMBPressedBackdrop;
...
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

### Physics

`Collider` is an abstract class, providing virtual functions for checking collisions, updating, as well as events and settings. Only `RectCollider` and `CircleCollider` are implemented by default.

`Collider` already implements functions such as `isPointInside` and `getOverlap` by trying to cast the two given colliders to the derived classes. Thanks to that you don't need to worry about specifics of each collider when dealing with polymorphism. Because of that, however, adding support for more colliders is tedious and impractical.

`bounciness` of a `Collider` affects the gain of speed after each collision, set to 0.8 by default. It is only used by `Rigidbody`. Global default is set in `Collider::defaultBounciness` with the default value of 0.1f.

`stickiness` of a `Collider` defines a maximum speed below which the final velocity of collision becomes 0. It is only used by `Rigidbody`. Global default is set in `Collider::defaultStickiness` with the default value of 0.8f.

### Gameobjects

`Gameobject` is a class that unifies all objects which can be put on a scene (except for camera). `Gameobject` does not inherit from any other class and is not abstract, meaning it can be instantiated. The only correct way of doing so is via static function `Gameobject::instantiate` (although ther is a public constructor, it does not register the new object in the active scene, hence it will not be updated or rendered). There is a templated overload for this function which can instantiate a derived class from `Gameobject`. Statically asserting for type validity it produces errors on type mismatch.

Each `Gameobject` has a parent (may be nullptr and is by default) and a vector of children (may be empty and is by default). Parent can be set by `setParent` method and retrieved back using `getParent`.

All children gameobject are translated by default when changing gameobject position. All overloads of both `setPosition` and `translate` have an optional argument `includeChildren` set to `true` by default. When toggled off, parent gameobject can be moved freely without affecting its children.

`destroy` destroys the gameobject and all its children.

`getGameobject` can be used in derived classes to get the pointer to its `Gameobject` fields without casting it.

`setScale` rescales both renderer and collider (if present).

`setRenderer`, `setCollider` and `setRigidbody` are the go-to methods to assign components to new values. Statically asserting for type validity it produces errors on type mismatch.

`start` is called in scene `start` function (has to be called manually if needed).

### Global functions and variables

`context()` returns pointer to the currently active scene.

`window()` returns pointer to the window (not SFML window).

`INF` is a constexpr float set to 10e6f

`mainCamera` is same as `Camera::main`

### Core loop stages

Initialization

- program entry
- window init
- current scene init
- main camera init
- (optionally) random init
- (optionally) other inits (of game systems etc)

Main loop

- window.update
    - poll SFML events
    - read mouse position
    - scene.update
        - onBeforeUpdate
        - time update
            - timings calculated
            - coroutines execution
        - input update
            - mouse update
            - keys update
        - active* gameobjects update
            - rigidbody update
            - collider update
        - fixed update (if needed**)
            - gravity applied
            - air resistance applied
            - collisions checked
        - canvas update
            - UI elements updated
        - onAfterUpdate
- window.render
    - main camera update
    - window clear
    - active* gameobjects render
        - renderer update
        - renderer render
- window.display

(*) each gameobject can be enabled or disabled. If a gameobject is disabled, it is not updated or rendered.

(**) fixed update happens a fixed number of times per second which can differ from FPS (50 times per second, i.e. each 20 milliseconds by default).

## Examples

### Entry point

```cpp
gamemain.cpp:

#include "Core/Engine.h"
#include "GameController.h"

int main() {
	// setup window
	aengine::Window window(900, 900, "Game!");
	window.getWindow()->setFramerateLimit(60);
	
	// create new scene and set it to be active
	aengine::SceneManager::createScene("main", window.getWindow())->setBackgroundColor(sf::Color(220, 80, 80));
	aengine::SceneManager::setCurrentScene("main");
	
	// setup camera - when needed, call aengine::Camera::main() or aengine::mainCamera()
	aengine::Camera camera("main");

	// init game systems
	aengine::Random::initSeed();
	agame::GameController::init();

	while (window.isRunning()) {

		agame::GameController::preUpdate();
		window.update();
		agame::GameController::postUpdate();

		agame::GameController::preRender();
		window.render();
		agame::GameController::postRender();
		window.display();
	}

	return 0;
}
```

Here all game logic is moved out to the agame::GameController class, leaving gamemain.cpp with the most essential initialization of the engine and handling the main loop.

### Creating gameobjects

```cpp
// the only proper way to create a new gameobject. The only argument is name. Should but doesn't have to be unique.
aengine::Gameobject* obj = aengine::Gameobject::instantiate("myObj");
obj->setPosition(210, 100);

// ------ rendering ------
// optional

aengine::ShapeRenderer* rend = 
obj->setRenderer(
    std::make_unique<aengine::ShapeRenderer>
    (
        obj, // mandatory field, a renderer has to be attached to the gameobject. If you pass a nullptr, the program will crash.

        std::make_unique<sf::RectangleShape>(sf::Vector2f(90,90))
    )
);

// getShapeAs<> performs a static cast, thus it cannot handle cases of type mismatch
sf::RectangleShape* shape = rend->getShapeAs<sf::RectangleShape>();

// you may customize the SFML shape as you will
shape->setFillColor(sf::Color(200, 100, 90));

// comment these lines to have a shape with no outline
shape->setOutlineColor(sf::Color(40, 40, 40));
shape->setOutlineThickness(2);
// (more about shape customization in SFML on their website or other tutorials)

rend->setDistance(32); // set rendering order, i.e. distance to camera, default is 64
rend->setRelativeOrigin(aengine::Vectorf::half); // <-- set origin point, from (0,0) to (1,1). Vectorf::half is default value (hence this line can be omitted) and it is recommended to use it in most cases. Change it only if you know what you are doing.

// ------ physics ------
// optional

obj->setCollider(
    std::make_unique<aengine::RectCollider>
    (
        obj, // again, collider has to be attached to the gameobject
        aengine::Vectorf(90, 90) // size
    )
);

// rigidbody forces calculations so it's heavy in comparison to colliders. Do not use it for static colliders
obj->setRigidbody(std::make_unique<aengine::Rigidbody>(obj));

obj->rigidbody->makeKinematic(); // make it responsive to forces but ignore gravity
obj->rigidbody->setMass(3.f);
obj->rigidbody->addForce(aengine::Vectorf(40, 0));
```