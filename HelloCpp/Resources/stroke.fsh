

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;

uniform vec2 texSize;
uniform float r_stroke;
uniform vec4 strokeColor;

void main() {
    vec2 texCoord=vec2(v_texCoord.s,v_texCoord.t);
    //----add stroke
    vec2 curPixelPos=texCoord*texSize;//current pixel pos in local space, origin at LU
    //the alpha of current position is the sum of alpha of all positions which are not further than r
    float alpha=0.0;
    float r2_stroke=r_stroke*r_stroke;
    float _step=(r_stroke<=1.1?0.5:1.0);
    for(float x=curPixelPos.x-r_stroke;x<=curPixelPos.x+r_stroke+0.1;x+=_step){
        for(float y=curPixelPos.y-r_stroke;y<=curPixelPos.y+r_stroke+0.1;y+=_step){
            vec2 pixelPos=vec2(x,y);
            vec2 curPixelToPixel=pixelPos-curPixelPos;
            if(dot(curPixelToPixel,curPixelToPixel)<=r2_stroke){
                alpha+=texture2D(CC_Texture0,pixelPos/texSize).a;
                if(alpha>=1.0)break;
            }
        }
    }
    //--
   	gl_FragColor=vec4(strokeColor.rgb,alpha);
}

