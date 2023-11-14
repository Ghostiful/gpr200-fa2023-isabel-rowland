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
uniform Light _Light;
uniform vec3 _CameraPos;


void main(){
	vec3 normal = normalize(fs_in.WorldNormal);
	vec3 w = normalize(_Light.position - fs_in.WorldPosition);
	int i;
	int numLights = 4;
	vec3 h = normalize(w + normalize(_CameraPos - fs_in.WorldPosition));
	vec3 lightColor = _Light.color * _Material.ambientK;
	lightColor += _Light.color * _Material.diffuseK * max(dot(w, normal), 0);
	lightColor += _Light.color * _Material.specular * max(dot(h, normal), 0);


	FragColor = texture(_Texture,fs_in.UV);
}