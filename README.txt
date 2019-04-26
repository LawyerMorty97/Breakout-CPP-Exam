This project is using CLion (with MinGW, GNU 8.2.0)

Libraries Used:
- SDL2, SDL_ttf, SDL_image

When I started with the exam, my goal was to make it easy to manage objects and SDL in general.
I managed to accomplish this by creating higher level methods for creating surfaces and textures.

I believe my solution is good because it takes the SDL engine and creates a "wrapper" around it
which makes it easier for the programmer to play around with Images and Text and prototype something
easily. My solution is also great because a number of core classes are Singletons, which only instance
once and any class that would need something from the core could just include the class and then get the
running instance, which in my opinion is neat.

Problems:
I believe the actual gameplay of my solution is lacking as it's not polished enough.
Collisions is also a major issue in the solution, since it doesn't work perfectly.