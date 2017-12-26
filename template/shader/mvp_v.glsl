#version 430 core

uniform dmat4 transform;

attribute vec3 position;

void main()
{
    gl_Position = vec4(transform * dvec4(position, 1));
}