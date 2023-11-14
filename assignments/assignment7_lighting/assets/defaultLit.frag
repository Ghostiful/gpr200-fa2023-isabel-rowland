#version 450
out vec4 FragColor;

in Surface{
	vec2 UV;
	vec3 WorldPosition;
	vec3 WorldNormal;
}fs_in;

struct Material {
	float ambientK; //Ambient coefficient (0-1)
	float diffuseK; //Diffuse coefficient (0-1)
	float specular; //Specular coefficient (0-1)
	float shininess; //Shininess
};
struct Light {
	vec3 position;
	vec3 color;
};

#define MAX_LIGHTS 4

uniform sampler2D _Texture;
uniform Material _Material;
uniform Light _Lights[MAX_LIGHTS];
uniform vec3 _CameraPos;


void main(){
	vec3 normal = normalize(fs_in.WorldNormal);
	vec3 lightColor;
	
	int i;
	for (i = 0; i < MAX_LIGHTS; i++) {
		vec3 w = normalize(_Lights[i].position - fs_in.WorldPosition);
		vec3 h = normalize(w + normalize(_CameraPos - fs_in.WorldPosition));
		lightColor = _Lights[i].color * _Material.ambientK;
		lightColor += _Lights[i].color * _Material.diffuseK * max(dot(w, normal), 0);
		lightColor += _Lights[i].color * _Material.specular * pow(max(dot(h, normal), 0), _Material.shininess);
	}

	FragColor = vec4(lightColor, 1.0) * texture(_Texture,fs_in.UV);
}