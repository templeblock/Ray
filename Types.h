#pragma once

#include <cstdint>
#if !defined(DISABLE_OCL)
#include <string>
#include <vector>
#endif

/**
  @file Types.h
*/

namespace Ray {
/// RGBA single precision f32 color
struct pixel_color_t {
    float r, g, b, a;
};
static_assert(sizeof(pixel_color_t) == 16, "!");

/// RGBA u8 color
struct pixel_color8_t {
    uint8_t r, g, b, a;
};
static_assert(sizeof(pixel_color8_t) == 4, "!");

struct shl1_data_t {
    float coeff_r[4], coeff_g[4], coeff_b[4];
};
static_assert(sizeof(shl1_data_t) == 48, "!");

/// Rectangle struct
struct rect_t { int x, y, w, h; };

enum eCamType { Persp, Ortho, Geo };

enum eFilterType { Box, Tent };

enum ePassFlags { SkipDirectLight = 1,
                  SkipIndirectLight = 2,
                  LightingOnly = 4,
                  NoBackground = 8,
                  Clamp = 16,
                  OutputSH = 32 };

struct pass_settings_t {
    uint8_t max_diff_depth,
            max_glossy_depth,
            max_refr_depth,
            max_transp_depth,
            max_total_depth;
    uint8_t pad[3];
    uint32_t flags;
};

struct camera_t {
    eCamType type;
    eFilterType filter;
    float fov, gamma;
    float focus_distance, focus_factor;
    float origin[3],
          fwd[3],
          side[3],
          up[3];
    uint32_t mi_index, uv_index;
    pass_settings_t pass_settings;
};

#if !defined(DISABLE_OCL)
namespace Ocl {
    struct Device {
        std::string name;
    };
    struct Platform {
        std::string vendor, name;
        std::vector<Device> devices;
    };
}
#endif
}