//
// Created by Mark Kellogg on 12/15/17.
//

#include "MeshRenderer.h"
#include "../common/gl.h"

namespace MPM {

  MeshRenderer::MeshRenderer(std::shared_ptr<Material> material, std::shared_ptr<Object3D> owner):
      ObjectRenderer<Mesh>(owner), material(material) {

  }

  void MeshRenderer::renderObject(std::shared_ptr<Camera> camera, std::shared_ptr<Mesh> mesh) {
    glUseProgram(this->material->getShader()->getProgram());

    this->checkAndSetShaderAttribute(mesh, StandardAttributes::Position,
                                     mesh->getVertexPositions(), GL_FLOAT, GL_FALSE, 0, 0);
    this->checkAndSetShaderAttribute(mesh, StandardAttributes::Color, mesh->getVertexColors(),
                                     GL_FLOAT, GL_FALSE, 0, 0);
    this->checkAndSetShaderAttribute(mesh, StandardAttributes::UV, mesh->getVertexUVs(),
                                     GL_FLOAT, GL_FALSE, 0, 0);

    GLuint projectionLoc = this->material->getShaderLocation(
        StandardUniforms::ProjectionMatrix);
    GLuint viewMatrixLoc = this->material->getShaderLocation(StandardUniforms::ViewMatrix);

    if (projectionLoc >= 0) {
      const Matrix4x4 &matrix = camera->getProjectionMatrix();
      glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, matrix.getConstData());
    }

    if (viewMatrixLoc >= 0) {
      Matrix4x4 viewMatrix = camera->getLocalTransform().getMatrix();
      viewMatrix.invert();
      glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix.getConstData());
    }

    this->material->sendCustomUniformsToShader();

    if (mesh->isIndexed()) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
      glDrawElements(GL_TRIANGLES, mesh->getSize(), GL_UNSIGNED_INT, (void *) (0));
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    } else {
      glDrawArrays(GL_TRIANGLES, 0, mesh->getSize());
    }
  }

  void MeshRenderer::render(std::shared_ptr<Camera> camera) {
    for (auto mesh : this->owner->getRenderables<Mesh>()) {
      this->renderObject(camera, mesh);
    }
  }
}