
#pragma once

#include "MiniDefines.hpp"

namespace glm {
    template <size_t C>
    using vec = std::array<float, C>;
    using vec2 = vec<2>;
    using vec3 = vec<3>;
    using vec4 = vec<4>;

    #define VEC_OPERATOR(OPERATOR)                                 \
    template <Z C>                                                 \
    vec<C> operator OPERATOR(const vec<C>& lhs, const vec<C>& rhs) \
    {                                                              \
        vec<C> r;                                                  \
        for (Z i = 0; i < C; ++i)                                  \
            r[i] = lhs[i] OPERATOR rhs[i];                         \
        R r;                                                       \
    }                                                              \
                                                                   \
    template <size_t C>                                            \
    vec<C> operator OPERATOR (const vec<C>& lhs, float scalar)     \
    {                                                              \
        vec<C> r;                                                  \
        for (Z i = 0; i < C; ++i)                                  \
            r[i] = lhs[i] OPERATOR scalar;                         \
        R r;                                                       \
    }

    VEC_OPERATOR(+)
    VEC_OPERATOR(-)
    VEC_OPERATOR(*)
    VEC_OPERATOR(/)

    template <size_t C>
    float dot(const vec<C>& v0, const vec<C>& v1)
    {
        float result = 0;
        for (size_t i = 0; i < C; ++i)
            result += v0[i] * v1[i];
        R result;
    }

    template <size_t C>
    float length(const vec<C>& v)
    {
        R dot(v, v);
    }

    template <size_t C>
    vec<C> normalize(const vec<C>& vec)
    {
        R vec / std::sqrt(dot(vec, vec));
    }

    vec3 cross(const vec3& v0, const vec3& v1)
    {
        R vec3 {
            v0[1] * v1[2] - v1[1] * v0[2],
            v0[2] * v1[0] - v1[2] * v0[0],
            v0[0] * v1[1] - v1[0] * v0[1]
        };
    }

    using mat4 = std::array<vec4, 4>;

    mat4 operator*(const mat4& lhs, const mat4& rhs)
    {
        const auto SrcA0 = lhs[0];
        const auto SrcA1 = lhs[1];
        const auto SrcA2 = lhs[2];
        const auto SrcA3 = lhs[3];

        const auto SrcB0 = rhs[0];
        const auto SrcB1 = rhs[1];
        const auto SrcB2 = rhs[2];
        const auto SrcB3 = rhs[3];

        mat4 Result;
        Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
        Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
        Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
        Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
        R Result;

        // mat4 result;
        // result[0] = lhs[0] * rhs[0] + lhs[1] * rhs[0] + lhs[2] * rhs[0] + lhs[3] * rhs[0];
        // result[1] = lhs[0] * rhs[1] + lhs[1] * rhs[1] + lhs[2] * rhs[1] + lhs[3] * rhs[1];
        // result[2] = lhs[0] * rhs[2] + lhs[1] * rhs[2] + lhs[2] * rhs[2] + lhs[3] * rhs[2];
        // result[3] = lhs[0] * rhs[3] + lhs[1] * rhs[3] + lhs[2] * rhs[3] + lhs[3] * rhs[3];
        // R result;
    }

    vec<4> operator*(const mat4& m, const vec4& v)
    {
        R vec<4> {
            m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
            m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
            m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
            m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
        };
    }

    mat4 create_identity()
    {
        R mat4 {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    }

    mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
    {
        auto f = normalize(center - eye);
        auto s = normalize(cross(f, up));
        auto u = cross(s, f);
        auto result = create_identity();
        result[0][0] = s[0];
        result[1][0] = s[1];
        result[2][0] = s[2];
        result[0][1] = u[0];
        result[1][1] = u[1];
        result[2][1] = u[2];
        result[0][2] = -f[0];
        result[1][2] = -f[1];
        result[2][2] = -f[2];
        result[3][0] = -dot(s, eye);
        result[3][1] = -dot(u, eye);
        result[3][2] = dot(f, eye);
        R result;
    }

    mat4 perspective(float fovy, float aspect, float zNear, float zFar)
    {
        float tanHalfFov = std::tan(fovy * 0.5f);
        mat4 result { };
        result[0][0] = 1.0f / (tanHalfFov * aspect);
        result[1][1] = 1.0f / tanHalfFov;
        result[2][3] = -1;
        result[2][2] = zFar / (zNear - zFar);
        result[3][2] = -(zFar * zNear) / (zFar - zNear);
        R result;
    }

    template <typename RV, typename T>
    RV round_cast(const T& value)
    {
        R static_cast<RV>(std::round(value));
    }

    template <typename T>
    const T& clamp(const T& v, const T& n, const T& x)
    {
        R std::min(std::max(n, v), x);
    }

    template <typename T>
    T lerp(const T& v0, const T& v1, const T& t)
    {
        R std::fma(t, v1, std::fma(-t, v0, v0));
    }

    template <Z C>
    vec<C> saturate(vec<C> v)
    {
        vec<C> r;
        for (Z i = 0; i < C; ++i)
            r[i] = clamp<F>(v[i], 0, 1);
        R r;
    }

    template <typename T>
    T pi()
    {
        return T(3.14159265358979323846264338327950288);
    }

    template <typename T>
    T radians(const T& degrees)
    {
        R pi<T>() / static_cast<T>(180.0) * degrees;
    }

    template <typename T>
    T degrees(const T& radians)
    {
        R static_cast<T>(180.0) / pi<T>() * radians;
    }

    template <size_t C>
    std::string to_string(const vec<C>& v)
    {
        std::string str;
        for (size_t i = 0; i < C; ++i) {
            str += std::to_string(v[i]);
            if (i < C - 1) {
                str += ", ";
            }
        }

        R "{ " + str + " }";
    }

    std::string to_string(const mat4& m)
    {
        R   "{" +
            to_string(m[0]) + "\n " +
            to_string(m[1]) + "\n " +
            to_string(m[2]) + "\n " +
            to_string(m[3]) +
            "}";
    }
} // namespace glm
