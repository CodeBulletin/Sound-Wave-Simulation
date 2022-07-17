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

float max(float[16] list) {
	float m = -100000;
	for(int i = 0; i < 16; i++) {
		if(m < abs(list[i])){
			m = abs(list[i]);
		}
	}
	return m;
}

void main() {
	float netA = 0, net = 0;
	float[16] netL;
	int mode = 0;
	for(int i = 0; i < size; i++) {
		if(Points[i].z == 0){
			for(int j = 0; j < 16; j++) {
				netL[j] += AmpFreqPha[i].x*sin(AmpFreqPha[i].y * distance(Points[i].xy, gl_FragCoord.xy) - t - AmpFreqPha[i].z + j*PI/16);
			}
		} 
		else if(Points[i].z == 1) {
			for(int j = 0; j < 16; j++) {
				netL[j] += AmpFreqPha[i].x*sin(AmpFreqPha[i].y * abs(Points[i].y - gl_FragCoord.y) - t - AmpFreqPha[i].z + j*PI/16);
			}
		} 
		else if(Points[i].z == 2) {
			for(int j = 0; j < 16; j++) {
				netL[j] += AmpFreqPha[i].x*sin(AmpFreqPha[i].y * abs(Points[i].x - gl_FragCoord.x) - t - AmpFreqPha[i].z + j*PI/16);
			}
		}
		netA += AmpFreqPha[i].x;
	}
	net = max(netL);
	net /= size;
	netA /= size;
	FragColor = vec4(map(net, 0.0, netA, 0.0, 1.0), map(net, 0.0, netA, 0.0, 1.0), map(net, 0.0, netA, 0.0, 1.0), 1.0);
}