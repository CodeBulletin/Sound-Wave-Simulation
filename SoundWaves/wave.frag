#version 130

uniform vec4[500] Points;
uniform vec3[500] AmpFreqPha;

uniform int size;
uniform float t;

in vec4 gl_FragCoord;

out vec4 FragColor;

#define PI 3.14159

float map(float value, float min, float max, float minRange, float maxRange) {
	return (minRange + (maxRange - minRange) * ((value - min) / (max - min)));
}

void main() {
	float netA = 0, net = 0;
	float[16] netL;
	int mode = 0;
	for(int i = 0; i < size; i++) {
		if(Points[i].z == 0){
			net += AmpFreqPha[i].x*sin(AmpFreqPha[i].y * distance(Points[i].xy, gl_FragCoord.xy) - t - AmpFreqPha[i].z);
		}
		else if(Points[i].z == 1) {
			net += AmpFreqPha[i].x*sin(AmpFreqPha[i].y * abs(Points[i].y - gl_FragCoord.y) - t - AmpFreqPha[i].z);
		}
		else if(Points[i].z == 2) {
			net += AmpFreqPha[i].x*sin(AmpFreqPha[i].y * abs(Points[i].x - gl_FragCoord.x) - t - AmpFreqPha[i].z);
		}
		netA += pow(AmpFreqPha[i].x, 2);
	}
	net /= size;
	netA /= size;
	FragColor = vec4(map(net, -netA, netA, 0.0, 1.0), map(net, -netA, netA, 0.0, 1.0), map(net, -netA, netA, 0.0, 1.0), 1.0);
}