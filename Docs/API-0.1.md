// Renderer
```c
VSR_RendererCreateInfo* VSR_RendererGenerateCreateInfo(SDL_Window* window);
```
Generate the create info for the renderer and populate it with the defaults
must be free'd when finished with
```c
void VSR_RendererFreeCreateInfo(VSR_RendererCreateInfo* rendererCreateInfo);
```

```c
VSR_RendererCreateInfo* VSR_RendererRequestTextureCount(VSR_RendererCreateInfo* createInfo, size_t count);
```
request an arbitrary size of the sampler texture array
returns NULL on failure
```c
VSR_RendererCreateInfo* VSR_RendererRequestDescriptor(VSR_RendererCreateInfo* createInfo, size_t index, size_t size);
```
request an arbitrary descriptor in set 2 at index of size bytes

```c
VSR_Renderer* VSR_RendererCreate(VSR_RendererCreateInfo* rendererCreateInfo);
```
create a renderer from the create info
```c
void VSR_RendererFree(VSR_Renderer* renderer);
```

```c
void VSR_RendererSetPipeline(VSR_Renderer* renderer, VSR_GraphicsPipeline* pipeline);
```
sets the pipeline that a renderer should draw with

```c
void VSR_RendererBeginPass(VSR_Renderer* renderer);
```
begins a render pass
```c
void VSR_RendererEndPass(VSR_Renderer* renderer);
```
ends a renderpass
```c
int VSR_RenderModels(VSR_Renderer* renderer, VSR_Model* models, VSR_Mat4** transforms, VSR_Sampler** samplers, size_t batchCount);
```
queues the Render of batchCount models, 
models transforms and samplers must be arrays of batchCount size
just because renders have been queued does not mean they are completed
if constants or descriptors are updated during a pass renders must be flushed.
```c
int VSR_RendererFlushQueuedModels(VSR_Renderer* renderer);
```
flushes queued renderers in the current pass

```c
void VSR_RendererWriteDescriptor(VSR_Renderer* renderer, size_t index, size_t offset, void* data, size_t len);
```
writes the len data at data + offset to the descriptor at index of set 2

```c
VSR_GraphicsPipelineCreateInfo* VSR_GraphicsPipelineGenerateCreateInfo(VSR_Renderer* renderer);
```

```c
void VSR_GraphicsPipelineCreateInfoFree(VSR_GraphicsPipelineCreateInfo* createInfo);
```

```c
VSR_GraphicsPipeline* VSR_GraphicsPipelineCreate(VSR_Renderer* renderer, VSR_GraphicsPipelineCreateInfo* createInfo);
```

```c
void VSR_GraphicsPipelineFree(VSR_Renderer* renderer, VSR_GraphicsPipeline* pipeline);
```

```c
void VSR_GraphicsPipelineSetShader(VSR_GraphicsPipelineCreateInfo* pipeline, VSR_ShaderStage stage, VSR_Shader* shader);
```
sets the shaders to be used by the pipeline during rendering
shaders can be destroyed once pipeline is created

```c
void VSR_GraphicsPipelineSetPushConstants(VSR_Renderer* renderer, VSR_GraphicsPipeline* pipeline, VSR_PushConstants const* pushConstants);
```
sets the push constants to be push at the start of a render on this pipeline

```c
int VSR_GraphicsPipelineSetRenderTarget(VSR_Renderer* renderer, VSR_GraphicsPipelineCreateInfo * pipeline, VSR_Sampler* sampler);
```
sets a sampler as the render target, 
all renders from this pipeline will be stored in the sampler
the contents of render target are undefined during it's renderpass 

```c
VSR_Shader* VSR_ShaderCreate(VSR_Renderer* renderer, size_t byteCount, const uint8_t* bytes);
```

```c
void VSR_ShaderDestroy(VSR_Renderer* renderer, VSR_Shader* shader);
```

```c
VSR_Mesh* VSR_MeshCreate(size_t vertexCount, VSR_Vertex const* vertices, VSR_Vertex const* normals, VSR_UV const* UVs, size_t indexCount, VSR_Index const* indices);
```

```c
void VSR_MeshFree(VSR_Mesh* model);
```

```c
VSR_Model* VSR_ModelCreate(VSR_Renderer* renderer, VSR_Mesh* mesh);
```

```c
void VSR_ModelFree(VSR_Renderer* renderer, VSR_Model* model);
```

```c
void VSR_ModelUpdate(VSR_Renderer* renderer, VSR_Model* model, VSR_Mesh* mesh);
```

```c
VSR_Sampler* VSR_SamplerCreate(VSR_Renderer* renderer, size_t index, SDL_Surface* sur, VSR_SamplerFlags flags);
```

```c
void VSR_SamplerFree(VSR_Renderer* renderer, VSR_Sampler* sampler);
```

```c
VSR_Mat4* VSR_Mat4Create(VSR_Renderer* renderer, float* m);
```

```c
void VSR_Mat4Update(VSR_Renderer* renderer, VSR_Mat4* mat4, float* m);
```

```c
void VSR_Mat4Destroy(VSR_Renderer* renderer, VSR_Mat4* mat4);
```