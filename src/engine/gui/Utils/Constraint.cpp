#include "Constraint.h"

float CenterConstraint::get(float pPos, float pSize, float pos, float size) {
    return (pSize - size) / 2;
}

FixedConstraint::FixedConstraint(float pos) : pos(pos) {

}

float FixedConstraint::get(float pPos, float pSize, float pos, float size) {
    return this->pos;
}


RelativeConstraint::RelativeConstraint(float aspect) : aspect(aspect) {

}


float RelativeConstraint::get(float pPos, float pSize, float pos, float size) {
    return aspect * pSize;
}

FixedConstraint2::FixedConstraint2(float pos) : pos(pos) {

}

float FixedConstraint2::get(float pPos, float pSize, float pos, float size) {
    return this->pos;
}

//AspectConstraint::AspectConstraint(float aspect) : aspect(aspect) {
//
//}
//
//float AspectConstraint::get(float pPos, float pSize, float pos, float size) {
//    return pSize * aspect;
//}
