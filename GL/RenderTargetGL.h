#pragma once

#include "../common/gl.h"
#include "../common/types.h"
#include "../render/RenderTargetException.h"

namespace Core {

    class RenderTargetGL{
    public:
        RenderTargetGL();
        ~RenderTargetGL();
        GLuint getFBOID() const;

    protected:
        void destroy();
        void initFramebuffer();
        void completeFramebuffer();
        void initDepthStencilBufferCombo(UInt32 sizeX, UInt32 sizeY);

        // OpenGL Framebuffer Object ID.
        GLuint fboID;

    };
}