	#version 330

	layout(location=0) in vec3 vPos;
	layout(location=1) in vec3 vNormal;


	out vec4 ex_worldPos;
	out vec3 ex_worldNorm;

	uniform mat4 modelMatrix;
	uniform mat4 projectionMatrix;
	uniform mat4 viewMatrix;

	void main () {
		gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vPos, 1.0);
		ex_worldPos = modelMatrix *	vec4(vPos, 1.0);
		mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
		ex_worldNorm = normalMatrix * vNormal;
	}