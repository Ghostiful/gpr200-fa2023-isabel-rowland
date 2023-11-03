#include "procGen.h"


ew::MeshData ir::createSphere(float radius, int numSegments)
{
	ew::MeshData newMesh;
	int i;
	float thetaStep = 2 * ew::PI / numSegments;
	float phiStep = ew::PI / numSegments;
	float theta, phi;
	int row, col;
	ew::Vertex v;

	for (row = 0; row <= numSegments; row++) {
		phi = row * phiStep;
		for (col = 0; col <= numSegments; col++) {
			theta = col * thetaStep;
			v.pos.x = radius * cos(theta) * sin(phi);
			v.pos.y = radius * cos(phi);
			v.pos.z = radius * sin(theta) * sin(phi);
			newMesh.vertices.push_back(v);
		}
	}
	int poleStart = 0;
	int sideStart = numSegments + 1;
	for (i = 0; i < numSegments; i++) {
		newMesh.indices.push_back(sideStart + i);
		newMesh.indices.push_back(poleStart + i);
		newMesh.indices.push_back(sideStart + i + 1);
	}


	return ew::MeshData();
}

ew::MeshData ir::createCylinder(float height, float radius, int numSegments)
{
	ew::MeshData newMesh;
	float topY, bottomY;
	int i;
	float thetaStep = 2 * ew::PI / numSegments;
	float theta;
	int columns = numSegments + 1;
	ew::Vertex v;

	topY = height / 2;
	bottomY = -topY;
	
	//Top center
	v.pos.x = 0;
	v.pos.y = topY;
	v.pos.z = 0;
	v.normal = ew::Vec3(0, 1, 0);
	v.uv = ew::Vec2(0.5, 0.5);
	newMesh.vertices.push_back(v);

	//Top ring
	for (i = 0; i <= numSegments; i++) {
		theta = i * thetaStep;
		v.pos.x = cos(theta) * radius;
		v.pos.z = sin(theta) * radius;
		v.pos.y = topY;
		v.normal = ew::Vec3(0, 1, 0);
		v.uv = ew::Vec2(cos(theta), sin(theta));
		v.uv = (v.uv + 1) / 2;

		newMesh.vertices.push_back(v);
	}
	//top side ring
	for (i = 0; i <= numSegments; i++) {
		theta = i * thetaStep;
		v.pos.x = cos(theta) * radius;
		v.pos.z = sin(theta) * radius;
		v.pos.y = topY;
		v.normal = ew::Vec3(cos(theta), 0, sin(theta));
		v.uv = ew::Vec2(1 / static_cast<float>(numSegments) * i, 1);

		newMesh.vertices.push_back(v);
	}
	//Bottom side ring
	for (i = 0; i <= numSegments; i++) {
		theta = i * thetaStep;
		v.pos.x = cos(theta) * radius;
		v.pos.z = sin(theta) * radius;
		v.pos.y = bottomY;
		v.normal = ew::Vec3(cos(theta), 0, sin(theta));
		v.uv = ew::Vec2(1 / static_cast<float>(numSegments) * i, 0);
		newMesh.vertices.push_back(v);
	}
	//Bottom ring
	for (i = 0; i <= numSegments; i++) {
		theta = i * thetaStep;
		v.pos.x = cos(theta) * radius;
		v.pos.z = sin(theta) * radius;
		v.pos.y = bottomY;
		v.normal = ew::Vec3(0, -1, 0);
		v.uv = ew::Vec2(cos(theta), sin(theta));
		newMesh.vertices.push_back(v);
	}
	//Bottom center
	v.pos.x = 0;
	v.pos.y = bottomY;
	v.pos.z = 0;
	v.normal = ew::Vec3(0, -1, 0);
	v.uv = ew::Vec2(0, 0);
	newMesh.vertices.push_back(v);

	//Top indices
	int start = 1;
	int center = 0;
	for (i = 0; i <= numSegments; i++) {
		newMesh.indices.push_back(start + i);
		newMesh.indices.push_back(center);
		newMesh.indices.push_back(start + i + 1);
	}
	//Side indices
	int sideStart = numSegments + 1;
	for (i = 0; i <= columns; i++) {
		start = sideStart + i;
		//Triangle 1
		newMesh.indices.push_back(start);
		newMesh.indices.push_back(start + 1);
		newMesh.indices.push_back(start + columns);
		//Triangle 2
		newMesh.indices.push_back(start + 1);
		newMesh.indices.push_back(start + columns + 1);
		newMesh.indices.push_back(start + columns);
	}
	
	center = newMesh.vertices.size() - 1;
	start = center - columns;
	for (i = 0; i <= numSegments; i++) {
		newMesh.indices.push_back(start + i);
		newMesh.indices.push_back(center);
		newMesh.indices.push_back(start + i + 1);
	}


	return newMesh;
}

ew::MeshData ir::createPlane(float size, int subdivisions)
{
	ew::MeshData newMesh;
	ew::Vertex v;

	int row, col;
	int columns = subdivisions + 1;
	int start;
	for (row = 0; row <= subdivisions; row++) {
		for (col = 0; col <= subdivisions; col++) {
			v.pos.x = size * (static_cast<float>(col) / subdivisions);
			v.pos.z = -size * (static_cast<float>(row) / subdivisions);
			v.normal = ew::Vec3(0, 1, 0);
			v.uv = ew::Vec2(size / subdivisions * row, size / subdivisions * col);
			newMesh.vertices.push_back(v);
		}
	}
	for (row = 0; row < subdivisions; row++) {
		for (col = 0; col < subdivisions; col++) {
			start = row * columns + col;
			// Bottom right triangle
			newMesh.indices.push_back(start);
			newMesh.indices.push_back(start + 1);
			newMesh.indices.push_back(start + columns + 1);
			// Top left triangle
			newMesh.indices.push_back(start);
			newMesh.indices.push_back(start + columns + 1);
			newMesh.indices.push_back(start + columns);
		}
	}
	
	return newMesh;
}
