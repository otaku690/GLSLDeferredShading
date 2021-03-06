#version 330

////////////////////////////
//       ENUMERATIONS
////////////////////////////

#define	DISPLAY_DEPTH 0
#define	DISPLAY_NORMAL 1
#define	DISPLAY_POSITION 2
#define	DISPLAY_COLOR 3
#define	DISPLAY_TOTAL 4
#define	DISPLAY_LIGHTS 5

#define SSAO_SAMPLE_SIZE 64
/////////////////////////////////////
// Uniforms, Attributes, and Outputs
////////////////////////////////////
uniform sampler2D u_Posttex;


in vec2 fs_Texcoord;
out vec4 out_Color;

///////////////////////////////////
// MAIN
//////////////////////////////////
void main() 
{
	out_Color = texture( u_Posttex, fs_Texcoord );
}

