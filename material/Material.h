#pragma once

#include <memory>

#include "../Graphics.h"
#include "../util/PersistentWeakPointer.h"
#include "StandardAttributes.h"
#include "StandardUniforms.h"

namespace Core {

    // forward declarations
    class Shader;

    class Material {
    public:
        Material(WeakPointer<Graphics> graphics);
        Material(WeakPointer<Graphics> graphics, WeakPointer<Shader> shader);
        WeakPointer<Shader> getShader();
        
        virtual Bool build() = 0;
        virtual Int32 getShaderLocation(StandardAttribute attribute, UInt32 offset = 0) = 0;
        virtual Int32 getShaderLocation(StandardUniform uniform, UInt32 offset = 0) = 0;
        virtual void sendCustomUniformsToShader() = 0;
        virtual WeakPointer<Material> clone() = 0;
        virtual UInt32 textureCount();

    protected:
        Bool buildFromSource(const std::string& vertexSource, const std::string& fragmentSource);
        void setShader(WeakPointer<Shader> shader);

        PersistentWeakPointer<Graphics> graphics;
        PersistentWeakPointer<Shader> shader;
        Bool ready;
    };
}
