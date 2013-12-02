

#include "myTTFLabel.h"
//static var member must redeclared in cpp, or there will be compiling error
CGLProgramWithMyUnifos CmyTTFLabel::program_stroke;
CGLProgramWithMyUnifos CmyTTFLabel::program_shade;
bool CmyTTFLabel::initWithString(const char *_text, const char *_fontName, float _fontSize,float _r_stroke)
{
    text=_text;
    fontName=_fontName;
    fontSize=_fontSize;
    r_stroke=_r_stroke;
  //  CCLOG("stroke width:%f",r_stroke);
    //----init programs
    //make static programs (lazy initialization, only initializate once)
    if(program_stroke.isNull())makeProgram_stroke();
    if(program_shade.isNull())makeProgram_shade();
    
    if(this->getTexture()==NULL){
        this->init();
    }
     //----make rawTex
        makeRawTex();

    
    //----make rawTexEx
        makeRawTexEx();

    
    //----make effectTex
    
        makeEffectTex();

    
    //----set effectTex to *this
    useTex(effectTex);
  //  CCLOG("contentSize:%f,%f",this->getContentSize().width,this->getContentSize().height);
    return true;
}
void CmyTTFLabel::useTex(CCSprite*sprite){
    setTexAndUseTheRect(this, sprite->getTexture());
}
void CmyTTFLabel::makeRawTex(){
    //temp label
    CCLabelTTF*label=new CCLabelTTF();
    label->autorelease();
    label->initWithString(text.c_str(), fontName.c_str(), fontSize);
    setTexAndUseTheRect(rawTex,label->getTexture());
    rawTex->getTexture()->setAntiAliasTexParameters();
}
void CmyTTFLabel::makeRawTexEx(){
    const int margin=2;
    //render rawTex to texture
    CCRenderTexture*rtt=new CCRenderTexture();
    rtt->initWithWidthAndHeight(rawTex->getContentSize().width+2*(ceil(r_stroke)+margin),
                                    rawTex->getContentSize().height+2*(ceil(r_stroke)+margin),
                                    kCCTexture2DPixelFormat_Default);
    rawTex->setPosition(ccp(rawTex->getContentSize().width/2+ceil(r_stroke)+margin,rawTex->getContentSize().height/2+ceil(r_stroke)+margin));
    float oldScaleY=rawTex->getScaleY();//store rawTex scaleY
    rawTex->setScaleY(-oldScaleY);
    rtt->begin();
    rawTex->visit();
    rtt->end();
    rawTex->setScaleY(oldScaleY);//restore rawTex scaleY
    setTexAndUseTheRect(rawTexEx, rtt->getSprite()->getTexture());//expanded rawTex
    rawTexEx->getTexture()->setAntiAliasTexParameters();
}
void CmyTTFLabel::makeEffectTex(){
    //set rawTexEx to *this
    setTexAndUseTheRect(this,rawTexEx->getTexture());
    //render *this to effectTex (reuse rtt, size is the same)
    CCRenderTexture*rtt=new CCRenderTexture();
    rtt->initWithWidthAndHeight(this->getContentSize().width,
                                this->getContentSize().height,
                                kCCTexture2DPixelFormat_Default);
    CCPoint oldPos=this->getPosition();//store *this position
    this->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
    float oldScaleY=this->getScaleY();//store *this scaleY
    this->setScaleY(-oldScaleY);
    rtt->begin();
    this->visit();
    rtt->end();
    this->setPosition(oldPos);//restore *this position
    this->setScaleY(oldScaleY);//restore *this scaleY
    setTexAndUseTheRect(effectTex, rtt->getSprite()->getTexture());
    effectTex->getTexture()->setAntiAliasTexParameters();
}
void CmyTTFLabel::draw(){
    if(this->getTexture()==rawTexEx->getTexture()){
        CCSize texSize=this->getContentSize();
        if(r_stroke!=0){
            //----change shader
            this->setShaderProgram(CmyTTFLabel::program_stroke.getProgram());
            ccGLEnable(m_eGLServerState);
            //pass values for cocos2d-x build-in uniforms
            getShaderProgram()->use();
            getShaderProgram()->setUniformsForBuiltins();
            //pass values for my own uniforms
            {
                float texSize_c[2]={texSize.width,texSize.height};
                glUniform2fv(program_stroke.myUnifoMap["texSize"],1,texSize_c);
                glUniform1f(program_stroke.myUnifoMap["r_stroke"], r_stroke);
                float strokeColor_c[4]={strokeColor.x,strokeColor.y,strokeColor.z,strokeColor.w};
                glUniform4fv(program_stroke.myUnifoMap["strokeColor"],1,strokeColor_c);
            }
            //call father draw
            CCSprite::draw();
        }
        if(r_shade!=0){
            //----change shader and draw agin
            this->setShaderProgram(CmyTTFLabel::program_shade.getProgram());
            ccGLEnable(m_eGLServerState);
            //pass values for cocos2d-x build-in uniforms
            getShaderProgram()->use();
            getShaderProgram()->setUniformsForBuiltins();
            //pass values for my own uniforms
            {
                float texSize_c[2]={texSize.width,texSize.height};
                glUniform2fv(program_shade.myUnifoMap["texSize"],1,texSize_c);
                glUniform1f(program_shade.myUnifoMap["r_shade"], r_shade);
                float shadeDir_c[2]={shadeDir.x,shadeDir.y};
                glUniform2fv(program_shade.myUnifoMap["shadeDir"],1,shadeDir_c);
                float shadeColor_c[4]={shadeColor.x,shadeColor.y,shadeColor.z,shadeColor.w};
                glUniform4fv(program_shade.myUnifoMap["shadeColor"],1,shadeColor_c);
                float fontColor_c[4]={fontColor.x,fontColor.y,fontColor.z,fontColor.w};
                glUniform4fv(CmyTTFLabel::program_shade.myUnifoMap["fontColor"],1,fontColor_c);
            }
            //call father draw
            CCSprite::draw();
        }else{
            setTexAndUseTheRect(this, rawTexEx->getTexture());
            //----change shader and draw agin
            this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
            ccGLEnable(m_eGLServerState);
            //pass values for cocos2d-x build-in uniforms
            getShaderProgram()->use();
            getShaderProgram()->setUniformsForBuiltins();
            //call father draw
            CCSprite::draw();
            
        }
    }else if(this->getTexture()==effectTex->getTexture()){
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
        ccGLEnable(m_eGLServerState);
        //pass values for cocos2d-x build-in uniforms
        getShaderProgram()->use();
        getShaderProgram()->setUniformsForBuiltins();
        //call father draw
        CCSprite::draw();
    }


}
void CmyTTFLabel::makeProgram_stroke(){
    
    if(program_stroke.isNull()==false)return;
    GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("stroke.fsh").c_str())->getCString();
    CCGLProgram* pProgram = new CCGLProgram();
    pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    //bind attribute
    pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    //link  (must after bindAttribute)
    pProgram->link();
    //get cocos2d-x build-in uniforms
    pProgram->updateUniforms();
    //get my own uniforms
    map<string,GLint> myUnifoMap;
    myUnifoMap["texSize"] = glGetUniformLocation(pProgram->getProgram(),"texSize");
    myUnifoMap["r_stroke"] = glGetUniformLocation(pProgram->getProgram(),"r_stroke");
    myUnifoMap["strokeColor"] = glGetUniformLocation(pProgram->getProgram(),"strokeColor");
    //make program
    program_stroke.myUnifoMap=myUnifoMap;
    program_stroke.setProgram(pProgram);
    //program can be released
    pProgram->release();
    //check gl error
    CHECK_GL_ERROR_DEBUG();
}
void CmyTTFLabel::makeProgram_shade(){
    
    if(program_shade.isNull()==false)return;
    GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("shade.fsh").c_str())->getCString();
    CCGLProgram* pProgram = new CCGLProgram();
    pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    //bind attribute
    pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    //link  (must after bindAttribute)
    pProgram->link();
    //get cocos2d-x build-in uniforms
    pProgram->updateUniforms();
    //get my own uniforms
    map<string,GLint> myUnifoMap;
    myUnifoMap["texSize"] = glGetUniformLocation(pProgram->getProgram(),"texSize");
    myUnifoMap["r_shade"] = glGetUniformLocation(pProgram->getProgram(),"r_shade");
    myUnifoMap["shadeDir"] = glGetUniformLocation(pProgram->getProgram(),"shadeDir");
    myUnifoMap["shadeColor"] = glGetUniformLocation(pProgram->getProgram(),"shadeColor");
    myUnifoMap["fontColor"] = glGetUniformLocation(pProgram->getProgram(),"fontColor");
    //make program
    program_shade.myUnifoMap=myUnifoMap;
    program_shade.setProgram(pProgram);
    //program can be released
    pProgram->release();
    //check gl error
    CHECK_GL_ERROR_DEBUG();
}
