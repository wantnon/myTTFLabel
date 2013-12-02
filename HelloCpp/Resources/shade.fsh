

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;
uniform float r_shade;
uniform vec2 texSize;
uniform vec2 shadeDir;
uniform vec4 shadeColor;
uniform vec4 fontColor;


void main() {
    vec2 texCoord=vec2(v_texCoord.s,v_texCoord.t);
    //----add shade
    float shade=0.0;
    vec2 curPixelPos=texCoord*texSize;//current pixel pos in local space, origin at LU
    float count=0.0;
    vec2 shadeDir=vec2(shadeDir.x,-shadeDir.y);//because origin at LU, so the angle is the neg of math angle, so angle's cos is the same but sin is the neg.
    for(float r=0.0;r<=r_shade+0.1;r++){
        vec2 pixelPos=curPixelPos-shadeDir*r;
        float a=texture2D(CC_Texture0,pixelPos/texSize).a;
        shade+=a;
        count+=1.0;
    }
    shade=shade/count;
    //----calculate a color between shadeColor and fontColor using shade as weight
    vec4 color=shadeColor*(1.0-shade)+fontColor*shade;
    //--
    float alpha=texture2D(CC_Texture0,texCoord).a;
   	gl_FragColor=vec4(color.rgb,alpha);
}

