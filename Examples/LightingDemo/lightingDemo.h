#include <VSR.h>
#include <cglm/cglm.h>
#include <stdio.h>

#include "../helpers.h"

typedef struct Light Light;
struct Light
{
	float x, y, z;
	uint32_t r, g, b, a;
};

static inline int
lightingDemo(int argc, char *argv[])
{
	// setup sdl
	SDL_Window* window = SDL_CreateWindow("TestWindow", 0,0,640,480, SDL_WINDOW_VULKAN);

	// setup renderer
	VSR_RendererCreateInfo* createInfo = VSR_RendererGenerateCreateInfo(window);
	VSR_RendererRequestDescriptor(createInfo, 0, sizeof(Light) * 4);

	Light lights[4];
	lights[0].x = 5;
	lights[0].y = 0;
	lights[0].z = 1.2f;
	lights[0].r = 255;
	lights[0].g = 245;
	lights[0].b = 255;
	lights[0].a = 255;
	VSR_Renderer* renderer = VSR_RendererCreate(createInfo);
	VSR_RendererWriteDescriptor(renderer, 0, 0, lights, sizeof(Light));

	Mesh jerry = loadObj("Assets/JerryTheOgre/bs_smile.obj",
						 "Assets/JerryTheOgre/");
	// create models
	VSR_Mesh* terryMesh = VSR_MeshCreate(
		jerry.numVertices,
		(const VSR_Vertex*) jerry.vertices,
		(const VSR_Vertex*) jerry.normals,
		(const VSR_UV*) jerry.texcoords,
		jerry.numIndices,
		(const VSR_Index*) jerry.indices
	);

	VSR_Model* terryModel = VSR_ModelCreate(renderer, terryMesh);
	mat4 terryPos;
	glm_mat4_identity(terryPos);

	// set images
	SDL_Surface* sur1 = SDL_LoadBMP("Assets/JerryTheOgre/diffuse.bmp");
	SDL_Surface* sur2 = SDL_LoadBMP("Assets/JerryTheOgre/normalmap.bmp");
	VSR_Sampler* sampler1 = VSR_SamplerCreate(renderer, 1, sur1, 0);
	VSR_SamplerCreate(renderer, 2, sur2, 0);

	// create and set pipeline
	VSR_GraphicsPipelineCreateInfo* pipelineCreateInfo = VSR_GraphicsPipelineGenerateCreateInfo(renderer);
	size_t n;
	uint8_t* bytes = loadShader("LightingDemo/vert.spv", &n);
	VSR_Shader* vert = VSR_ShaderCreate(renderer, n, bytes);
	VSR_GraphicsPipelineSetShader(pipelineCreateInfo, SHADER_STAGE_VERTEX, vert);

	bytes = loadShader("LightingDemo/frag.spv", &n);
	VSR_Shader* frag = VSR_ShaderCreate(renderer, n, bytes);
	VSR_GraphicsPipelineSetShader(pipelineCreateInfo, SHADER_STAGE_FRAGMENT, frag);


	VSR_GraphicsPipeline* pipeline = VSR_GraphicsPipelineCreate(renderer, pipelineCreateInfo);

	VSR_RendererSetPipeline(renderer, pipeline);

	mat4 mat;
	glm_mat4_identity(mat);
	glm_rotate(mat, 0.1f, (vec3){0.f, 0.f, 1.f});
	VSR_Mat4* terryPosition = VSR_Mat4Create(renderer, (float *) mat);


	/// setup projection ///
	mat4 view;
	vec3 eye = {0.f, 0.f, 5.f};
	vec3 center = {0.f, 0.f, 0.f};
	vec3 up = {0.f, 1.f, 0.f};

	glm_lookat(
		eye,
		center,
		up,
		view
	);

	float deg = 45.f;
	glm_make_rad(&deg);

	mat4 projection;
	glm_perspective(
		deg,
		640.f / 480.f,
		0.1f,
		400.f,
		projection);

	glm_mat4_mul(projection, view, view);
	view[1][1] *= -1;

	VSR_Mat4* viewMat = VSR_Mat4Create(renderer, view);
	VSR_PushConstants pushConstants;
	pushConstants.Projection =  &viewMat;
	pushConstants.bytes = SDL_malloc(64);
	VSR_GraphicsPipelineSetPushConstants(renderer, pipeline, &pushConstants);

	// renderloop
	int shouldQuit = 0;
	SDL_Event event;

	while(!shouldQuit)
	{

		glm_rotate(mat, 0.01f, (vec3){0.f, 0.f, 1.f});
		VSR_Mat4Update(renderer, terryPosition, (float *) mat);


		VSR_RendererBeginPass(renderer);
		VSR_RenderModels(renderer, terryModel, &terryPosition, &sampler1, 1);
		VSR_RendererEndPass(renderer);

		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT) {shouldQuit = 1;}

	}

	// cleanup
	SDL_DestroyWindow(window);
	SDL_free(pushConstants.bytes);
	VSR_SamplerFree(renderer, sampler1);
	VSR_MeshFree(terryMesh);
	VSR_ModelFree(renderer, terryModel);
	VSR_GraphicsPipelineCreateInfoFree(pipelineCreateInfo);
	VSR_GraphicsPipelineFree(renderer, pipeline);
	VSR_RendererFreeCreateInfo(createInfo);
	VSR_RendererFree(renderer);
	return 0;
}