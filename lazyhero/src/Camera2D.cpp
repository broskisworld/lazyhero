#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;
#include "Camera2D.h"
Camera2D::Camera2D() {

}
void Camera2D::update() {
	pos.x = pos.x + (fixPoint.x - pos.x) / slow;
	pos.y = pos.y + (fixPoint.y - pos.y) / slow;
}
void Camera2D::setSlow(double set) {
	slow = set;
}
void Camera2D::setFixPoint(double x, double y) {
	fixPoint.x = -x;
	fixPoint.y = -y;
}
vec2 Camera2D::camToWorldPos(vec2 v) {
	return vec2((v.x - getWindowWidth() / 2 - pos.x) / scale, (v.y - getWindowHeight() / 2 - pos.y) / scale);
}
vec2 Camera2D::worldToCamPos(vec2 v) {
	return vec2(v.x * scale + getWindowWidth() / 2 + pos.x, v.y * scale + getWindowHeight() / 2 + pos.y);
}