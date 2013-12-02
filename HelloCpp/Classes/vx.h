//
//  vx.h
//  HelloCpp
//
//  Created by apple on 13-11-23.
//
//

#ifndef __HelloCpp__vx__
#define __HelloCpp__vx__

#include <iostream>
class Cv4
{
public:
    float x,y,z,w;
    Cv4(){
        x=y=z=0;
        w=1;
    }
    Cv4(float _x,float _y,float _z,float _w){
        init(_x, _y, _z, _w);
    }
    void init(float _x,float _y,float _z,float _w){
        x=_x;
        y=_y;
        z=_z;
        w=_w;
    }
    bool isEqual(const Cv4 v){
        return (x==v.x&&y==v.y&&z==v.z&&w==v.w);
    
    }

};
#endif /* defined(__HelloCpp__vx__) */
