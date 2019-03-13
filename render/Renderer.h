#pragma once

#include "../common/complextypes.h"
#include "../common/debug.h"
#include "RenderBuffer.h"
#include "RenderState.h"
#include "../geometry/Vector2.h"
#include "../geometry/Vector4.h"
#include "../scene/Transform.h"
#include "../util/WeakPointer.h"
#include "../light/LightType.h"
#include "../base/BitMask.h"

namespace Core {

    // forward declaration
    class Object3D;
    class Scene;
    class Camera;
    class Light;
    class ViewDescriptor;
    class DepthOnlyMaterial;
    class DistanceOnlyMaterial;
    class TonemapMaterial;
    class Material;
    class RenderTarget;
    class RenderTarget2D;
    class Skybox;

    class Renderer {
    public:
        virtual ~Renderer();
        virtual Bool init();
        void renderScene(WeakPointer<Scene> scene, WeakPointer<Material> overrideMaterial = WeakPointer<Material>::nullPtr());
        void renderScene(WeakPointer<Object3D> rootObject, WeakPointer<Material> overrideMaterial = WeakPointer<Material>::nullPtr());
        void renderObjectBasic(WeakPointer<Object3D> rootObject, WeakPointer<Camera> camera, WeakPointer<Material> overrideMaterial = WeakPointer<Material>::nullPtr());
        void renderObjectDirect(WeakPointer<Object3D> object, WeakPointer<Camera> camera,
                                WeakPointer<Material> overrideMaterial = WeakPointer<Material>::nullPtr());
        void renderObjectDirect(WeakPointer<Object3D> object, WeakPointer<Camera> camera, std::vector<WeakPointer<Light>>& lightList,
                                WeakPointer<Material> overrideMaterial = WeakPointer<Material>::nullPtr());

    protected:
        Renderer();
        void renderStandard(WeakPointer<Camera> camera, std::vector<WeakPointer<Object3D>>& objects, 
                            std::vector<WeakPointer<Light>>& lights, WeakPointer<Material> overrideMaterial);
        void renderCube(WeakPointer<Camera> camera, std::vector<WeakPointer<Object3D>>& objects, 
                        std::vector<WeakPointer<Light>>& lights, WeakPointer<Material> overrideMaterial);
        void render(WeakPointer<Camera> camera, std::vector<WeakPointer<Object3D>>& objects, 
                    WeakPointer<Material> overrideMaterial);
        void render(WeakPointer<Camera> camera, std::vector<WeakPointer<Object3D>>& objects, 
                    std::vector<WeakPointer<Light>>& lights, WeakPointer<Material> overrideMaterial);
        void render(ViewDescriptor& viewDescriptor, std::vector<WeakPointer<Object3D>>& objectList, 
                    std::vector<WeakPointer<Light>>& lightList);
        void renderObjectDirect(WeakPointer<Object3D> object, ViewDescriptor& viewDescriptor, std::vector<WeakPointer<Light>>& lightList);
        void renderShadowMaps(std::vector<WeakPointer<Light>>& lights, LightType lightType, 
                              std::vector<WeakPointer<Object3D>>& objects, WeakPointer<Camera> renderCamera = WeakPointer<Camera>());
        void getViewDescriptorForCamera(WeakPointer<Camera> camera, ViewDescriptor& viewDescriptor);
        void getViewDescriptorTransformations(const Matrix4x4& worldMatrix, const Matrix4x4& projectionMatrix,
                               IntMask clearBuffers, ViewDescriptor& viewDescriptor);
        void processScene(WeakPointer<Scene> scene, std::vector<WeakPointer<Object3D>>& outObjects);
        void processScene(WeakPointer<Object3D> object, const Matrix4x4& curTransform,
                          std::vector<WeakPointer<Object3D>>& outObjects);
        void buildHDRRenderTarget(const Vector2u& size);
        
        static Bool isShadowCastingCapableLight(WeakPointer<Light> light);
        static Bool compareLights (WeakPointer<Light> a, WeakPointer<Light> b);

        WeakPointer<DepthOnlyMaterial> depthMaterial;
        WeakPointer<DistanceOnlyMaterial> distanceMaterial;
        WeakPointer<Object3D> reflectionProbeObject;
        WeakPointer<TonemapMaterial> tonemapMaterial;
    };
}
