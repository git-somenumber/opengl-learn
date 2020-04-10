#version 330 core

in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D pikachu;
uniform vec4 adj;

void main(){
	FragColor = mix(texture(ourTexture, TexCoord), texture(pikachu, TexCoord),0.2);
	//FragColor = vec4(Color,1.0);
}

