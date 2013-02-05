// --------------------------------------------------------------------------
// $File: //depot/vlg/Demos/GLSL/firstVertex/yellow.vsh $
// $Revision: #1 $
// $Date: 2012/02/09 $
// --------------------------------------------------------------------------
// Vertex Shader "yellow"
// ftransform == fixed function pipeline
void main(void)
{
   gl_FrontColor = vec4(1.0, 1.0, 0.0, 1.0);
   gl_Position = ftransform();
}
