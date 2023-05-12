#include "CubeDemo/cubeDemo.h"
#include "LightingDemo/lightingDemo.h"
#include "ShadowDemo/shadowDemo.h"
#include "MorphDemo/morphDemo.h"

int
SDL_main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	cubeDemo(argc, argv);
	lightingDemo(argc, argv);
	shadowDemo(argc, argv);
	morphDemo(argc, argv);
	printf("exit successful");
	return 0;
}

#ifndef main
int
main(int argc, char** argv)
{
	return SDL_main(argc, argv);
}
#endif