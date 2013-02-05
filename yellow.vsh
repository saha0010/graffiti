// --------------------------------------------------------------------------
// $File$
// $Revision$
// $Date$
// --------------------------------------------------------------------------
// Fragment Shader "yellow"

uniform vec3  color;
void main(void)
{

    int x =  int(gl_FragCoord.x);
    int y =  int(gl_FragCoord.y);

    
if ( (x % 2 == 1) || ( y % 2 == 1 ) && !( x % 2 == 1 &&  y % 2 == 1))
    discard;
gl_FragColor = vec4(color[0],color[1],color[2],0.5);

}
