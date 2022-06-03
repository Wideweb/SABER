#pragma once

#include <cmath>

namespace Saber {

struct vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

vec3 operator+(vec3 v1, vec3 v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

vec3 &operator+=(vec3 &v1, vec3 v2) {
    v1 = v1 + v2;
    return v1;
}

vec3 operator-(vec3 v1, vec3 v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

vec3 operator/(vec3 v, float d) { return {v.x / d, v.y / d, v.z / d}; }

float length(vec3 v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

vec3 normalize(vec3 v) { return v / length(v); }

vec3 cross(vec3 v1, vec3 v2) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return {x, y, z};
}

void calc_mesh_normals(vec3 *normals, const vec3 *verts, const int *faces,
                       int nverts, int nfaces) {
    for (size_t i = 0; i < nfaces; i++) {
        int v_1 = faces[i * 3];
        int v_2 = faces[i * 3 + 1];
        int v_3 = faces[i * 3 + 2];

        vec3 edge_1 = verts[v_2] - verts[v_1];
        vec3 edge_2 = verts[v_3] - verts[v_1];

        vec3 normal = normalize(cross(edge_1, edge_2));

        normals[v_1] += normal;
        normals[v_2] += normal;
        normals[v_3] += normal;
    }

    for (size_t i = 0; i < nverts; i++) {
        normals[i] = normalize(normals[i]);
    }
}

} // namespace Saber