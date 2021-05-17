//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

in vec2 TexCoords;
//Uniform variable
uniform sampler2D image;
 
void main()
{
//Setting each vector component to uniform varaible then setting final colour
    fragcolor = texture2D(image, TexCoords);
}