//
// Created by Mark Kellogg on 12/19/17.
//

#include <memory>
#include <vector>
#include "../common/gl.h"
#include "CubeTexture.h"
#include "../common/assert.h"
#include "RawImage.h"

namespace Core {

  std::shared_ptr<CubeTexture> CubeTexture::createCubeTexture(RawImage *front, RawImage *back,
                                              RawImage *top, RawImage *bottom,
                                              RawImage *left, RawImage *right) {

    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    GLuint tex;

    // generate the OpenGL cube texture
    glGenTextures(1, &tex);
    ASSERT(tex > 0, "CubeTexture::createCubeTexture -> Unable to generate texture");
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    std::vector<RawImage *> images = {front, back, top, bottom, left, right};
    std::vector<GLuint> faces = {GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
                                 GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                 GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X};

    for(UInt32 i = 0; i < 6; i++) {
      glTexImage2D(faces[i], 0, GL_RGBA, images[i]->getWidth(), images[i]->getHeight(), 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, images[i]->getImageData());
    }

    // set the relevant texture properties
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    std::shared_ptr<CubeTexture> texture = std::make_shared<CubeTexture>();
    texture->textureId = tex;
    return texture;
  }
}