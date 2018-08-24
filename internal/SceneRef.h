#pragma once

#include <vector>

#include "BVHSplit.h"
#include "CoreRef.h"
#include "TextureAtlasRef.h"
#include "../SceneBase.h"

namespace Ray {
namespace ref2 {
template <int DimX, int DimY>
class RendererSIMD;
}
namespace Sse {
template <int DimX, int DimY>
class RendererSIMD;
}
namespace Avx {
template <int DimX, int DimY>
class RendererSIMD;
}

namespace Neon {
template <int DimX, int DimY>
class RendererSIMD;
}

namespace Ref {
class Renderer;

class Scene : public SceneBase {
protected:
    friend class Ref::Renderer;
    template <int DimX, int DimY>
    friend class Sse::RendererSIMD;
    template <int DimX, int DimY>
    friend class Avx::RendererSIMD;
	template <int DimX, int DimY>
    friend class Neon::RendererSIMD;

    std::vector<bvh_node_t> nodes_;
    std::vector<tri_accel_t> tris_;
    std::vector<uint32_t> tri_indices_;
    std::vector<transform_t> transforms_;
    std::vector<mesh_t> meshes_;
    std::vector<mesh_instance_t> mesh_instances_;
    std::vector<uint32_t> mi_indices_;
    std::vector<vertex_t> vertices_;
    std::vector<uint32_t> vtx_indices_;

    std::vector<material_t> materials_;
    std::vector<texture_t> textures_;
    TextureAtlas texture_atlas_;

    std::vector<light_t> lights_;
    std::vector<uint32_t> li_indices_;

    environment_t env_;

    uint32_t macro_nodes_start_ = 0, macro_nodes_count_ = 0;
    uint32_t light_nodes_start_ = 0, light_nodes_count_ = 0;

    uint32_t default_normals_texture_, default_env_texture_;

    void RemoveNodes(uint32_t node_index, uint32_t node_count);
    void RebuildMacroBVH();
    void RebuildLightBVH();
public:
    Scene();

    void GetEnvironment(environment_desc_t &env) override;
    void SetEnvironment(const environment_desc_t &env) override;

    uint32_t AddTexture(const tex_desc_t &t) override;
    void RemoveTexture(uint32_t) override {}

    uint32_t AddMaterial(const mat_desc_t &m) override;
    void RemoveMaterial(uint32_t) override {}

    uint32_t AddMesh(const mesh_desc_t &m) override;
    void RemoveMesh(uint32_t) override;

    uint32_t AddLight(const light_desc_t &l) override;
    void RemoveLight(uint32_t i) override;

    uint32_t AddMeshInstance(uint32_t m_index, const float *xform) override;
    void SetMeshInstanceTransform(uint32_t mi_index, const float *xform) override;
    void RemoveMeshInstance(uint32_t) override;

    uint32_t triangle_count() override {
        return (uint32_t)tris_.size();
    }
    uint32_t node_count() override {
        return (uint32_t)nodes_.size();
    }
};
}
}