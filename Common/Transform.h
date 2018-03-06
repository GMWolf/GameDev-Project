#pragma once
#include <Component.h>
#include <Matrix4.h>
#include <Entity.h>

COMPONENT(Transform, 128), Matrix4 {

	Transform() : Matrix4(Matrix4::Identity()), parent(-1){
	}

	Transform(Matrix4 matrix) : Matrix4(matrix), parent(-1){
	}

	Transform(Matrix4 matrix, Entity parent) : Matrix4(matrix),  parent(parent) {
	}

	Entity parent;
};