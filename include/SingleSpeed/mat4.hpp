#pragma once

namespace ss {


struct Mat4 {

  // Column-Major
  union {
    float elements[16] = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };
    struct {
      float m00, m01, m02, m03;
      float m10, m11, m12, m13;
      float m20, m21, m22, m23;
      float m30, m31, m32, m33;
    };
  };

  static Mat4 ortho(float left, float right, float bottom, float top, float z_near, float z_far)
  {
    float tx, ty, tz;
    tx = -(right+left)/(right-left);
    ty = -(top+bottom)/(top-bottom);
    tz = -(z_far+z_near)/(z_far-z_near);

    Mat4 mat;
    mat.m00 = 2.0f/(right-left);
    mat.m11 = 2.0f/(top-bottom);
    mat.m22 = -2.0f/(z_far-z_near);
    mat.m30 = tx;
    mat.m31 = ty;
    mat.m32 = tz;

    return mat;
  }

};


} // namespace ss
