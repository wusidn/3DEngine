#version 430 core

layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec4 vColor;

out vec4 color;

void main()
{
    #将黑色转为白色
    color = vColor == vec4(.0f, .0f, .0f, 1.0f) ? vec4(1.0f, 1.0f, 1.0f, 1.0f) : vColor;
    gl_Position = vPosition;
}

