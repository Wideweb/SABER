#include "catch.hpp"

#include "mesh-normal.hpp"

#include <algorithm>
#include <array>

using namespace Saber;

const float c_Epsilon = 0.00001f;

inline bool isEqual(float x, float y) {
    const float epsilon = c_Epsilon;
    return std::abs(x - y) <= epsilon * std::abs(x);
}

inline bool isEqual(vec3 v1, vec3 v2) {
    return isEqual(v1.x, v2.x) && isEqual(v1.y, v2.y) && isEqual(v1.z, v2.z);
}

SCENARIO("Calculate smooth (average) per-vertex normals") {
    GIVEN("Right-handed coordinate system and vertices in counterclockwise "
          "order") {

        WHEN("triangle in the XY plane") {
            // clang-format off
            std::array<vec3, 3> normals = {};

            std::array<vec3, 3> verts = {{
                {-1.0f, -1.0f, 0.0f},
                {1.0f, -1.0f, 0.0f},
                {1.0f, 1.0f, 0.0f}
            }};

            std::array<int, 3> faces = {0, 1, 2};
            // clang-format on

            calc_mesh_normals(normals.data(), verts.data(), faces.data(), 3, 1);

            std::array<vec3, 3> expected = {{
                {0.0f, 0.0f, 1.0f},
                {0.0f, 0.0f, 1.0f},
                {0.0f, 0.0f, 1.0f},
            }};

            bool result =
                (std::equal(expected.begin(), expected.end(), normals.begin(),
                            [](vec3 v1, vec3 v2) { return isEqual(v1, v2); }));

            REQUIRE(result);
        }

        WHEN("triangle in the XZ plane") {
            // clang-format off
            std::array<vec3, 3> normals = {};

            std::array<vec3, 3> verts = {{
                {-1.0f, 0.0f, 1.0f},
                {1.0f, 0.0f, 1.0f},
                {1.0f, 0.0f, -1.0f}
            }};

            std::array<int, 3> faces = {0, 1, 2};
            // clang-format on

            calc_mesh_normals(normals.data(), verts.data(), faces.data(), 3, 1);

            std::array<vec3, 3> expected = {{
                {0.0f, 1.0f, 0.0f},
                {0.0f, 1.0f, 0.0f},
                {0.0f, 1.0f, 0.0f},
            }};

            bool result =
                (std::equal(expected.begin(), expected.end(), normals.begin(),
                            [](vec3 v1, vec3 v2) { return isEqual(v1, v2); }));

            REQUIRE(result);
        }

        WHEN("square in the XY plane") {
            // clang-format off
            std::array<vec3, 4> normals = {};

            std::array<vec3, 4> verts = {{
                {-1.0f, -1.0f, 0.0f},
                {1.0f, -1.0f, 0.0f},
                {1.0f, 1.0f, 0.0f},
                {-1.0f, 1.0f, 0.0f}
            }};

            std::array<int, 6> faces = {0, 1, 2, 0, 2, 3};
            // clang-format on

            calc_mesh_normals(normals.data(), verts.data(), faces.data(), 4, 2);

            std::array<vec3, 4> expected = {{
                {0.0f, 0.0f, 1.0f},
                {0.0f, 0.0f, 1.0f},
                {0.0f, 0.0f, 1.0f},
                {0.0f, 0.0f, 1.0f},
            }};

            bool result =
                (std::equal(expected.begin(), expected.end(), normals.begin(),
                            [](vec3 v1, vec3 v2) { return isEqual(v1, v2); }));

            REQUIRE(result);
        }

        WHEN("cube corner") {
            // clang-format off
            std::array<vec3, 4> normals = {};

            std::array<vec3, 4> verts = {{
                {-1.0f, -1.0f, 1.0f},
                {1.0f, -1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                {1.0f, -1.0f, -1.0f}
            }};

            std::array<int, 9> faces = {
                0, 1, 2,
                1, 3, 2,
                0, 1, 3
            };
            // clang-format on

            calc_mesh_normals(normals.data(), verts.data(), faces.data(), 4, 3);

            vec3 corner_vertex_normal = normals[1];
            vec3 expected_normal = normalize({1.0f, 1.0f, 1.0f});

            REQUIRE(isEqual(corner_vertex_normal, expected_normal));
        }
    }
}