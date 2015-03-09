/*
 * transform.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: nbingham
 */

#include "transform.h"

/* rotate
 *
 * Multiply the active matrix by a rotation matrix.
 */
mat4f rotate(float angle, vec3f axis)
{
	float c = cos(angle);
	float s = sin(angle);
	return mat4f(axis[0]*axis[0]*(1.0-c) + c,         axis[0]*axis[1]*(1.0-c) - axis[2]*s, axis[0]*axis[2]*(1.0-c) + axis[1]*s, 0.0,
			     axis[1]*axis[0]*(1.0-c) + axis[2]*s, axis[1]*axis[1]*(1.0-c) + c,         axis[1]*axis[2]*(1.0-c) - axis[0]*s, 0.0,
			     axis[0]*axis[2]*(1.0-c) - axis[1]*s, axis[1]*axis[2]*(1.0-c) + axis[0]*s, axis[2]*axis[2]*(1.0-c) + c,         0.0,
			     0.0,                                 0.0,                                 0.0,                                 1.0);
}

/* translate
 *
 * Multiply the active matrix by a translation matrix.
 */
mat4f translate(vec3f direction)
{
	return mat4f(1.0, 0.0, 0.0, direction[0],
				 0.0, 1.0, 0.0, direction[1],
				 0.0, 0.0, 1.0, direction[2],
				 0.0, 0.0, 0.0, 1.0);
}

/* scale
 *
 * Multiply the active matrix by a scaling matrix.
 */
mat4f scale(vec3f size)
{
	return mat4f(size[0], 0.0, 0.0, 0.0,
				 0.0, size[1], 0.0, 0.0,
				 0.0, 0.0, size[2], 0.0,
				 0.0, 0.0, 0.0, 1.0);
}

/* perspective
 *
 * Multiply the active matrix by a perspective projection matrix.
 */
mat4f perspective(float fovy, float aspect, float n, float f)
{
	float x = tan(m_pi/2.0 - fovy/2);
	return mat4f(x/aspect, 0.0, 0.0, 0.0,
				 0.0, x, 0.0, 0.0,
				 0.0, 0.0, -(f+n)/(f-n), -2.0*f*n/(f-n),
				 0.0, 0.0, -1.0, 0.0);
}

/* frustum
 *
 * Multiply the active matrix by a frustum projection matrix.
 */
mat4f frustum(float l, float r, float b, float t, float n, float f)
{
	return mat4f(2.0*n/(r - l), 0.0, (r + l)/(r - l), 0.0,
				 0.0, 2.0*n/(t - b), (t + b)/(t - b), 0.0,
				 0.0, 0.0, -(f + n)/(f - n), -2.0*f*n/(f - n),
				 0.0, 0.0, -1.0, 0.0);
}

/* ortho
 *
 * Multiply the active matrix by an orthographic projection matrix.
 */
mat4f ortho(float l, float r, float b, float t, float n, float f)
{
	return mat4f(2.0/(r - l), 0.0, 0.0, -(r + l)/(r - l),
			     0.0, 2.0/(t - b), 0.0, -(t + b)/(t - b),
			     0.0, 0.0, -2.0/(f - n), -(f + n)/(f - n),
			     0.0, 0.0, 0.0, 1.0);
}

mat4f viewport(int left, int bottom, int right, int top)
{
	return mat4f((float)(right - left)/2.0, 0.0, 0.0, (float)(right + left)/2.0,
				 0.0, (float)(top - bottom)/2.0, 0.0, (float)(top + bottom)/2.0,
				 0.0, 0.0, (float)0.5, (float)0.5,
				 0.0, 0.0, 0.0, 1.0);
}

mat4f look_at(vec3f eye, vec3f at, vec3f up)
{
	vec3f f = norm(at - eye);
	up = norm(up);
	vec3f s = cross(f, up);
	vec3f u = cross(norm(s), f);
	return mat4f(s[0], s[1], s[2], 0.0,
				 u[0], u[1], u[2], 0.0,
				 -f[0], -f[1], -f[2], 0.0,
				 0.0, 0.0, 0.0, 1.0)*translate(-eye);
}

