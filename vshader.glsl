#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform vec3 translateToOrigin;
uniform vec3 translateToMouse;
uniform vec3 translateForAnimate;
uniform float theta;

void main() 
{

	float angle = radians(theta);
	float angleCos = cos(angle);
	float angleSin = sin(angle);
	
	mat4 translatetranslateToOriginMat = mat4(1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	translateToOrigin.x,translateToOrigin.y,translateToOrigin.z,1.0);
	
	mat4 rotateZ = mat4( angleCos, angleSin, 0.0, 0.0,
		    -angleSin,  angleCos, 0.0, 0.0,
		    0.0,  0.0, 1.0, 0.0,
		    0.0,  0.0, 0.0, 1.0 );
			
	mat4 translateToMouseMat = mat4(1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	translateToMouse.x,translateToMouse.y,translateToMouse.z,1.0);
	
	mat4 translateForAnimateMat = mat4(1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	translateForAnimate.x,translateForAnimate.y,translateForAnimate.z,1.0);
	
	
  gl_Position = translateToMouseMat* translateForAnimateMat *rotateZ*translatetranslateToOriginMat*vPosition;
  color = vColor;
}
