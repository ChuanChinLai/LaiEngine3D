#version 330

in vec3 vertexNormal_worldSpace;
in vec3 vertexPosition_worldSpace;
in vec2 vertexUV;

out vec4 o_color;


//uniform vec3 cameraPosition_worldSpace;
//uniform vec3 lightPosition_worldSpace;


uniform sampler2D Ambient1;
uniform sampler2D Diffuse1;
uniform sampler2D Specular1;
uniform sampler2D Bump1;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 cameraPosition_worldSpace = vec3(0, 200.0f, 200.0f);
	vec3 lightPosition_worldSpace = vec3(0, 4.0f, 1.5f);
	
	
	// ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(vertexNormal_worldSpace);
    vec3 lightDir = normalize(lightPosition_worldSpace - vertexPosition_worldSpace);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5f;
    vec3 cameraDir = normalize(cameraPosition_worldSpace - vertexPosition_worldSpace);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
	
	
	vec3 result = (ambient + diffuse + specular) * vec3(1, 0, 0);
    o_color = vec4(result, 1.0);
	
//    o_color = texture(Diffuse1, vertexUV) + texture(Bump1, vertexUV);
//	o_color = vec4(1, 0, 0, 0);
}