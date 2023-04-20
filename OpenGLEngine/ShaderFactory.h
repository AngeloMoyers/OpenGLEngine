#pragma once

#include "Shader.h"

#include <memory>

class ShaderFactory
{
private:

public:
	static std::shared_ptr<Shader> LoadShader(const char* vertPath, const char* fragPath);
};

