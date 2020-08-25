#ifndef MATERIALS_H
#define MATERIALS_H

#include <engine/math/Vec3.h>

struct Material {
    const fVec3 ambient;
    const fVec3 diffuse;
    const fVec3 specular;
    const float shininess;

    Material(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const float shininess)
            : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
};

//http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
const Material EMERALD(fVec3(0.0215, 0.1745, 0.0215), fVec3(0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 76.8);//0.6);
//Material jade(fVec3(0.135, 0.2225, 0.1575), fVec3(0.54, 0.89, 0.63), fVec3(0.316228, 0.316228, 0.316228), 0.1);
//Material obsidian(fVec3(0.05375, 0.05, 0.06625), fVec3(0.18275, 0.17, 0.22525), fVec3(0.332741, 0.328634, 0.346435), 38.4);//0.3);
//Material pearl(fVec3(0.25, 0.20725, 0.20725), fVec3(1.0, 0.829, 0.829), fVec3(0.296648, 0.296648, 0.296648), 0.088);
//Material ruby(fVec3(0.1745, 0.01175, 0.01175), fVec3(0.61424, 0.04136, 0.04136), fVec3(0.727811, 0.626959, 0.626959), 0.6);
//Material turquoise(fVec3(0.1, 0.18725, 0.1745), fVec3(0.396, 0.74151, 0.69102), fVec3(0.297254, 0.30829, 0.306678), 0.1);
//Material brass(fVec3(0.329412, 0.223529, 0.027451), fVec3(0.780392, 0.568627, 0.113725), fVec3(0.992157, 0.941176, 0.807843), 0.21794872f);
//Material bronze(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material chrome(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material copper(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
const Material GOLD(fVec3(0.24725, 0.1995, 0.0745), fVec3(0.75164, 0.60648, 0.22648), fVec3(0.628281, 0.555802, 0.366065), 51.2);//0.4);
//Material silver(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material black_plastic(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material cyan_plastic(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material green_plastic(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material red_plastic(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material white_plastic(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material yellow_plastic(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material black_rubber(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material cyan_rubber(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material green_rubber(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material red_rubber(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material white_rubber(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);
//Material yellow_rubber(fVec3(0.0215, 0.1745, 0.0215), fVec3( 	0.07568, 0.61424, 0.07568), fVec3(0.633, 0.727811, 0.633), 0.6);

#endif // MATERIALS_H