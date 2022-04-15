#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;  

// texture samplers
uniform sampler2D texture1;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;  
uniform vec3 viewPos;


void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  


	vec3 result = (ambient + diffuse+ specular) * objectColor;

	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5)*vec4(ourColor,1.0);
	//FragColor = texture(texture1, TexCoord)*vec4(result, 1.0); 
	 FragColor = vec4(result, 1.0);
}