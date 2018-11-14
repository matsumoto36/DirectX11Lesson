#include "Renderer.h"

ID3D11Device *Renderer::_device = nullptr;
vector<reference_wrapper<Renderer>> *Renderer::_rendererList = nullptr;
