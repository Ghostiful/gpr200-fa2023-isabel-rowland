//fragmentShader.frag
#version 450
out vec4 FragColor;
in vec2 UV;
uniform vec3 _Color;
uniform float _Brightness;
uniform float iTime;
uniform vec2 iResolution;

float circleSDF(vec2 p, float r)
{
	return length(p)-r;
}

void main(){
	
	vec2 uv = UV;
    
    float weight = abs(sin(iTime-3.14/2.0)*0.5-0.5) * uv.y;
    vec3 color = mix(vec3(0.9,0.0,0.5),vec3(0.0,0.0,1.0),weight);
    
    //Get 0-1 T value for hill shape
    float hills = 1.0 - step(sin(uv.x*6.0) * 0.2 + 0.3,uv.y);
    
    
    float hills2 = 1.0 - step(cos(uv.x*5.0) * 0.2 + 0.3, uv.y);
    
    
    
    
    // Switch to -1 to 1
    
    uv = (2.0*UV-iResolution.xy)/iResolution.y;
    
    // float edge = floor(iTime)*0.5 + 0.5;
    
    vec2 circlePos = vec2(0.0, abs(sin(iTime*0.5))*2.0-2.0);
    
    float sun = circleSDF(uv - circlePos,0.4);
    
    sun = -1.0 * smoothstep(-0.05,0.05,sun);
    
    vec4 sunColor = vec4(1.0,1.0,0.0,1.0);

    
    color = mix(color, sunColor.rgb, sun*sunColor.a);
    
    color = mix(color,vec3(0.2),hills);
    
    color = mix(color,vec3(0.5),hills2);

    
    FragColor = vec4(color, 1.0);

   
    
}
