#version 430 core

in vec4 color;
out vec4 fColor;

#globalCode

void main()
{
    #mainCode
    
    fColor = color;
}

