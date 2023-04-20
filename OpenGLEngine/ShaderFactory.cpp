#include "ShaderFactory.h"

std::shared_ptr<Shader> ShaderFactory::LoadShader(const char* vertPath, const char* fragPath)
{
    if (vertPath == "")
        vertPath = "Shaders/simpleVertex.vert";
    if (fragPath == "")
        fragPath = "Shaders/errorShader.frag";

    Shader shader(vertPath, fragPath);
    return shader.IsValid() ? std::make_shared<Shader>(shader) : nullptr;
}
