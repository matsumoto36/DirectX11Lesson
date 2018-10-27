#include "Renderer.h"

ID3D11Device *Renderer::device = nullptr;
vector<reference_wrapper<Renderer>> *Renderer::rendererList = nullptr;
