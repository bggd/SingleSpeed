#pragma once

namespace ss {


struct Vec3 {

  union {
    float axis[3] = {0.0f, 0.0f, 0.0f};
    struct {
      float x;
      float y;
      float z;
    };
  };

  Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
  Vec3(float x, float y, float z) : axis{x,y,z} {}

  static Vec3 add(Vec3 a, Vec3 b)
  {
    return {a.x+b.x, a.y+b.y, a.z+b.z};
  }

  static Vec3 sub(Vec3 a, Vec3 b)
  {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
  }

  static float length(Vec3 v)
  {
    return sqrtf(Vec3::dot(v, v));
  }

  static Vec3 normalize(Vec3 v)
  {
    float len;
    len = 1.0f/Vec3::length(v);
    return {v.x*len, v.y*len, v.z*len};
  }

  static float dot(Vec3 a, Vec3 b)
  {
    return a.x*b.x+a.y*b.y+a.z*b.z;
  }

  static Vec3 cross(Vec3 a, Vec3 b)
  {
    return {
      a.y*b.z-a.z*b.y, 
      a.z*b.x-a.x*b.z,
      a.x*b.y-a.y*b.x
    };
  }
};


} // namespace ss
