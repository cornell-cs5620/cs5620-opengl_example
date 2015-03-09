/*
 * transform.h
 *
 *  Created on: Mar 9, 2015
 *      Author: nbingham
 */

#ifndef transform_h
#define transform_h

#include "core/geometry.h"

using namespace core;

mat4f rotate(float angle, vec3f axis);
mat4f translate(vec3f direction);
mat4f scale(vec3f size);
mat4f perspective(float fovy, float aspect, float n, float f);
mat4f frustum(float l, float r, float b, float t, float n, float f);
mat4f ortho(float l, float r, float b, float t, float n, float f);
mat4f viewport(int left, int bottom, int right, int top);
mat4f look_at(vec3f eye, vec3f at, vec3f up);

#endif
