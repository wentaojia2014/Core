#pragma once

#include <memory>

#include "../util/WeakPointer.h"
#include "../Graphics.h"
#include "Shader.h"
#include "StandardAttributes.h"
#include "StandardUniforms.h"

namespace Core {
  class Material {
  public:
    Material(WeakPointer<Graphics> graphics);
    Material(WeakPointer<Graphics> graphics, WeakPointer<Shader> shader);
    WeakPointer<Shader> getShader();
    virtual Bool build() = 0;

    virtual Int32 getShaderLocation(StandardAttributes attribute) = 0;
    virtual Int32 getShaderLocation(StandardUniforms uniform) = 0;
    virtual void sendCustomUniformsToShader() = 0;

  protected:
    WeakPointer<Graphics> graphics;
    WeakPointer<Shader> shader;
    Bool ready;
    Bool buildFromSource(const std::string& vertexSource, const std::string& fragmentSource);
    void setShader(WeakPointer<Shader> shader);
  };
}
