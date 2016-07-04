std::string render2d_gles2_vert = R"(
uniform mat4 projection;

attribute vec2 position;
attribute vec2 uv;
attribute vec4 color;

varying vec4 vColor;
varying vec2 vUV;

void main()
{
  gl_Position = projection * vec4(position, 0.0, 1.0);
  vUV = uv;
  vColor = color;
}
)";

std::string render2d_gles2_frag = R"(
uniform sampler2D tex;

varying vec4 vColor;
varying vec2 vUV;

void main()
{
  gl_FragColor = texture2D(tex, vUV) * vColor;
}
)";

std::string render2d_gl3_vert = R"(
uniform mat4 projection;

in vec2 position;
in vec2 uv;
in vec4 color;

out vec4 vColor;
out vec2 vUV;

void main()
{
  gl_Position = projection * vec4(position, 0.0, 1.0);
  vUV = uv;
  vColor = color;
}
)";

std::string render2d_gl3_frag = R"(
uniform sampler2D tex;

in vec4 vColor;
in vec2 vUV;

out vec4 fragColor;

void main()
{
  fragColor = texture(tex, vUV) * vColor;
}
)";
