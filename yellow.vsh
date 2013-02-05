// --------------------------------------------------------------------------
// $File$
// $Revision$
// $Date$
// --------------------------------------------------------------------------
// Fragment Shader "yellow"
void main(void)
{
    float x =  gl_FragCoord.x;
    float y =  gl_FragCoord.y;

    float xTemp = mod(x,2);
    float yTemp = mod(y,2);

    if ((xTemp == (float)1.0) || (yTemp == (float)1.0))
    {
        discard;    
        
    }

}
