#include "BasicTexturedMaterial.h"
#include "../material/Shader.h"
#include "../util/WeakPointer.h"
#include "StandardAttributes.h"
#include "StandardUniforms.h"
#include "../image/Texture.h"
#include "../Engine.h"
#include "../material/ShaderManager.h"

namespace Core {

    BasicTexturedMaterial::BasicTexturedMaterial(WeakPointer<Graphics> graphics): Material(graphics) {
    }

    Bool BasicTexturedMaterial::build() {
        WeakPointer<Graphics> graphics = Engine::instance()->getGraphicsSystem();
        ShaderManager& shaderDirectory = graphics->getShaderManager();
        const std::string& vertexSrc = shaderDirectory.getShader(Shader::ShaderType::Vertex, "BasicTextured");
        const std::string& fragmentSrc = shaderDirectory.getShader(Shader::ShaderType::Fragment, "BasicTextured");
        Bool ready = this->buildFromSource(vertexSrc, fragmentSrc);
        if (!ready) {
            return false;
        }
        this->bindShaderVarLocations();
        return true;
    }

    Int32 BasicTexturedMaterial::getShaderLocation(StandardAttribute attribute) {
        switch (attribute) {
            case StandardAttribute::Position:
                return this->positionLocation;
             case StandardAttribute::Normal:
                return this->normalLocation;
            case StandardAttribute::Color:
                return this->colorLocation;
            case StandardAttribute::UV0:
                return this->uvLocation;
            default:
                return -1;
        }
    }

    Int32 BasicTexturedMaterial::getShaderLocation(StandardUniform uniform) {
        switch (uniform) {
            case StandardUniform::ProjectionMatrix:
                return this->projectionMatrixLocation;
            case StandardUniform::ViewMatrix:
                return this->viewMatrixLocation;
            case StandardUniform::ModelMatrix:
                return this->modelMatrixLocation;
            case StandardUniform::Texture0:
                return this->textureLocation;
            default:
                return -1;
        }
    }

    void BasicTexturedMaterial::setTexture(WeakPointer<Texture> texture) {
        this->texture = texture;
    }

    void BasicTexturedMaterial::sendCustomUniformsToShader() {
        if (this->texture) {
            this->shader->setTexture2D(0, this->texture->getTextureID());
            this->shader->setUniform1i(textureLocation, 0);
        }
    }

    WeakPointer<Material> BasicTexturedMaterial::clone() {
        WeakPointer<BasicTexturedMaterial> newMaterial = Engine::instance()->createMaterial<BasicTexturedMaterial>(false);
        newMaterial->setShader(this->getShader());
        newMaterial->texture = this->texture;
        newMaterial->positionLocation = this->positionLocation;
        newMaterial->normalLocation = this->normalLocation;
        newMaterial->colorLocation = this->colorLocation;
        newMaterial->projectionMatrixLocation = this->projectionMatrixLocation;
        newMaterial->viewMatrixLocation = this->viewMatrixLocation;
        newMaterial->modelMatrixLocation = this->modelMatrixLocation;
        newMaterial->uvLocation = this->uvLocation;
        newMaterial->textureLocation = this->textureLocation;
        return newMaterial;
    }

    void BasicTexturedMaterial::bindShaderVarLocations() {
        this->positionLocation = this->shader->getAttributeLocation("pos");
        this->normalLocation = this->shader->getAttributeLocation("normal");
        this->colorLocation = this->shader->getAttributeLocation("color");
        this->textureLocation = this->shader->getAttributeLocation("textureA");
        this->uvLocation = this->shader->getAttributeLocation("uv");
        this->projectionMatrixLocation = this->shader->getUniformLocation("projection");
        this->viewMatrixLocation = this->shader->getUniformLocation("viewMatrix");
        this->modelMatrixLocation = this->shader->getUniformLocation("modelMatrix");
    }
}