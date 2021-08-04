#version 400

in vec4 position;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;

void main()
{
   gl_Position = mP*mV*mMposition;
}