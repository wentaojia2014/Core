#pragma once

#include "Material.h"
#include "../image/Texture.h"

namespace Core {
  class BasicMaterial : public Material {
    GLint positionLocation;
    GLint colorLocation;
    GLint uvLocation;
    GLint projectionMatrixLocation;
    GLint viewMatrixLocation;
  public:
    BasicMaterial();
    virtual Bool build() override;
    virtual GLint getShaderLocation(StandardAttributes attribute) override;
    virtual GLint getShaderLocation(StandardUniforms uniform) override;
    virtual void sendCustomUniformsToShader() override;
  };
}
