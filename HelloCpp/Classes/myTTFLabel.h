

#ifndef __HelloCpp__myTTFLabel__
#define __HelloCpp__myTTFLabel__

#include <iostream>
#include "cocos2d.h"
#include "GLProgramWithMyUnifos.h"
#include "vx.h"
#include "myFunc.h"
using namespace cocos2d;
class CmyTTFLabel:public CCSprite
{
public:
    CmyTTFLabel(){
        rawTex=new CCSprite();rawTex->init();
        rawTexEx=new CCSprite();rawTexEx->init();
        effectTex=new CCSprite();effectTex->init();
        text="text";
        fontName="Arial-BoldMT";
        fontSize=50;
        r_stroke=2;
        r_shade=4;
        shadeDir=CCPoint(cosf(35*M_PI/180),sinf(35*M_PI/180));
        shadeColor.init(0.8, 0.4, 0, 1);
        fontColor.init(1, 1, 1, 1);
        strokeColor.init(0,0.5,0,1);
        
    }
    virtual ~CmyTTFLabel(){
        rawTex->release();
        rawTexEx->release();
        effectTex->release();
    }
    //because reset stroke width may cause recreation of label texture, so it is recommended give stroke width value at the initialization time.
    //anyhow, you can reset stroke width if you want.
    bool initWithString(const char *_text, const char *_fontName, float _fontSize,float _r_stroke);
    void draw();
public:
    void setFontSize(float value){
        if(fontSize!=value){//if font size changed, reinit *this
            fontSize=value;
            makeRawTex();
            makeRawTexEx();
            makeEffectTex();
            useTex(effectTex);
        }
    }
    void setFontColor(Cv4 _fontColor){
        if(fontColor.isEqual(_fontColor)==false){
            fontColor=_fontColor;
            makeEffectTex();
            useTex(effectTex);
        }
    }
    void setR_stroke(float value){
        if(r_stroke!=value){//if stroke width changed, reinit *this
            r_stroke=value;
            makeRawTexEx();
            makeEffectTex();
            useTex(effectTex);
        }
    }
    void setStrokeColor(Cv4 _strokeColor){
        if(strokeColor.isEqual(_strokeColor)==false){
            strokeColor=_strokeColor;
            makeEffectTex();
            useTex(effectTex);
        }
    }
    void setShadeColor(Cv4 _shadeColor){
        if(shadeColor.isEqual(_shadeColor)==false){
            shadeColor=_shadeColor;
            makeEffectTex();
            useTex(effectTex);
        }
    }
    void setR_shade(float value){
        if(r_shade!=value){
            r_shade=value;
            makeEffectTex();
            useTex(effectTex);
         }
    }
    void setShadeDir(CCPoint _shadeDir){
        if(!(shadeDir.x==_shadeDir.x&&shadeDir.y==shadeDir.y)){
            shadeDir=_shadeDir;
            makeEffectTex();
            useTex(effectTex);
        }
    }
    float getFontSize()const{return fontSize;}
    Cv4 getFontColor()const{return fontColor;}
    float getR_stroke()const{return r_stroke;}
    Cv4 getStrokeColor()const{return strokeColor;}
    float getR_shade()const{return r_shade;}
    CCPoint getShadeDir()const{return shadeDir;}
private:
    CCSprite*rawTex;//use sprite is better than use texture
    CCSprite*rawTexEx;
    CCSprite*effectTex;
    void makeRawTex();
    void makeRawTexEx();
    void makeEffectTex();
    void useTex(CCSprite*sprite);
private:
    string text;
    string fontName;
    float fontSize;
private:
    //font
    Cv4 fontColor;
    //stroke
    float r_stroke;//stroke width
    Cv4 strokeColor;
    //shade
    float r_shade;
    CCPoint shadeDir;
    Cv4 shadeColor;
private:
    static CGLProgramWithMyUnifos program_stroke;
    static CGLProgramWithMyUnifos program_shade;
    static void makeProgram_stroke();
    static void makeProgram_shade();

};

#endif /* defined(__HelloCpp__myTTFLabel__) */
