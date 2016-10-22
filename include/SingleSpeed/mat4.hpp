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
      float m04, m05, m06, m07;
      float m08, m09, m10, m11;
      float m12, m13, m14, m15;
    };
  };

  static Mat4 mul(const Mat4& a, const Mat4& b)
  {
    Mat4 mat;

    mat.m00 = a.m00*b.m00 + a.m04*b.m01 + a.m08*b.m02 + a.m12*b.m03;
    mat.m01 = a.m01*b.m00 + a.m05*b.m01 + a.m09*b.m02 + a.m13*b.m03;
    mat.m02 = a.m02*b.m00 + a.m06*b.m01 + a.m10*b.m02 + a.m14*b.m03;
    mat.m03 = a.m03*b.m00 + a.m07*b.m01 + a.m11*b.m02 + a.m15*b.m03;

    mat.m04 = a.m00*b.m04 + a.m04*b.m05 + a.m08*b.m06 + a.m12*b.m07;
    mat.m05 = a.m01*b.m04 + a.m05*b.m05 + a.m09*b.m06 + a.m13*b.m07;
    mat.m06 = a.m02*b.m04 + a.m06*b.m05 + a.m10*b.m06 + a.m14*b.m07;
    mat.m07 = a.m03*b.m04 + a.m07*b.m05 + a.m11*b.m06 + a.m15*b.m07;

    mat.m08 = a.m00*b.m08 + a.m04*b.m09 + a.m08*b.m10 + a.m12*b.m11;
    mat.m09 = a.m01*b.m08 + a.m05*b.m09 + a.m09*b.m10 + a.m13*b.m11;
    mat.m10 = a.m02*b.m08 + a.m06*b.m09 + a.m10*b.m10 + a.m14*b.m11;
    mat.m11 = a.m03*b.m08 + a.m07*b.m09 + a.m11*b.m10 + a.m15*b.m11;

    mat.m12 = a.m00*b.m12 + a.m04*b.m13 + a.m08*b.m14 + a.m12*b.m15;
    mat.m13 = a.m01*b.m12 + a.m05*b.m13 + a.m09*b.m14 + a.m13*b.m15;
    mat.m14 = a.m02*b.m12 + a.m06*b.m13 + a.m10*b.m14 + a.m14*b.m15;
    mat.m15 = a.m03*b.m12 + a.m07*b.m13 + a.m11*b.m14 + a.m15*b.m15;

    return mat;
  }

  static Mat4 ortho(float left, float right, float bottom, float top, float z_near, float z_far)
  {
    float tx, ty, tz;
    tx = -(right+left)/(right-left);
    ty = -(top+bottom)/(top-bottom);
    tz = -(z_far+z_near)/(z_far-z_near);

    Mat4 mat;
    mat.m00 = 2.0f/(right-left);
    mat.m05 = 2.0f/(top-bottom);
    mat.m11 = -2.0f/(z_far-z_near);
    mat.m12 = tx;
    mat.m13 = ty;
    mat.m14 = tz;

    return mat;
  }

  static Mat4 perspective(float y_fov, float aspect, float z_near, float z_far)
  {
    y_fov = y_fov*(3.1415927f/180.0f);
    float a = 1.0f/tanf(y_fov/2.0f);

    Mat4 mat;
    mat.m00 = a/aspect;
    mat.m05 = a;
    mat.m10 = -((z_far+z_near)/(z_far-z_near));
    mat.m11 = -1.0f;
    mat.m14 = -((2.0f*z_far*z_near)/(z_far-z_near));
    mat.m15 = 0.0f;

    return mat;
  }
  
  static Mat4 look_at(Vec3 position, Vec3 target, Vec3 up)
  {
    Vec3 forward;
    forward = Vec3::normalize(Vec3::sub(target, position));

    Vec3 side;
    side = Vec3::normalize(Vec3::cross(forward, up));

    up = Vec3::cross(side, forward);

    Mat4 view;
    view.m00 = side.x;
    view.m04 = side.y;
    view.m08 = side.z;
    view.m01 = up.x;
    view.m05 = up.y;
    view.m09 = up.z;
    view.m02 = -forward.x;
    view.m06 = -forward.y;
    view.m10 = -forward.z;

    Mat4 trans;
    trans.m12 = -position.x;
    trans.m13 = -position.y;
    trans.m14 = -position.z;

    return Mat4::mul(view, trans);
  }

};


} // namespace ss
