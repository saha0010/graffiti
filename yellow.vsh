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
 
if ( (x % 4 == 0) || ( y % 4 == 2 ) && !( x % 4 == 0 &&  y % 4 == 2))
   gl_FragColor = vec4(color[0],color[1],color[2], 0.725);
   //discard;
   else
    gl_FragColor = vec4(color[0],color[1],color[2], 0.75);
    
}


