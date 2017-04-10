
#version 410

in vec3 Colour;
in vec2 Textcoord;

out vec4 FragmentColour;


void main(void)
{
    // write colour output without modification
    FragmentColour = vec4(Colour, 1.0);
}
