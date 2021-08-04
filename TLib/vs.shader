#version 400

in vec4 position;
uniform mat4 M;
uniform Mat4 V;
uniform mat4 P;

void main()
{
   gl_Position = P*V*M*position;
}