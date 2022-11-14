#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in mat3 TBNMat;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

struct Material 
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	float shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_DIR_LIGHTS ${NUM_DIR_LIGHTS}
uniform DirLight dirLights[NR_DIR_LIGHTS];
uniform int amountOfDirLights;

#define NR_POINT_LIGHTS ${NUM_POINT_LIGHTS}
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int amountOfPointLights;

#define NR_SPOT_LIGHTS ${NUM_SPOT_LIGHTS}
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform int amountOfSpotLights;

uniform vec3 viewPos;
uniform Material material;

// Lighting function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	// Properties
	vec3 norm = texture(material.texture_normal1, TexCoords).rgb;
	norm = normalize(norm * 2.0 - 1.0);
	vec3 viewDir = normalize(TangentViewPos - TangentFragPos);

	vec3 result = vec3(0.0, 0.0, 0.0);

	// Dir lights
	${HAS_DIR_LIGHT1}for(int i = 0; i < amountOfDirLights; i++)
		${HAS_DIR_LIGHT2}result += CalcDirLight(dirLights[i], norm, viewDir);

	// Point lights
	${HAS_POINT_LIGHT1}for(int i = 0; i < amountOfPointLights; i++)
		${HAS_POINT_LIGHT2}result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

	// Spot lights
	${HAS_SPOT_LIGHT1}for(int i = 0; i < amountOfSpotLights; i++)
		${HAS_SPOT_LIGHT2}result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

	FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	// Diffuse component
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular component
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Result
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 TangentLightPos = TBNMat * light.position;

	vec3 lightDir = normalize(TangentLightPos - TangentFragPos);

	// Diffuse component
	float diff = max(dot(normal, lightDir), 0.0);

	// Specular component
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// Calculate attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// Result
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	 vec3 TangentLightPos = TBNMat * light.position;

	 vec3 lightDir = normalize(TangentLightPos - TangentFragPos);

	 // Diffuse component
	 float diff = max(dot(normal, lightDir), 0.0);

	 // Specular component
	 vec3 reflectDir = reflect(-lightDir, normal);
	 float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	 // Calculate attenuation
	 float distance = length(light.position - fragPos);
	 float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	 // Spotlight intensity
	 float theta = dot(lightDir, normalize(-light.direction));
	 float epsilon = light.cutOff - light.outerCutOff;
	 float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	 // Result
	 vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	 vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
	 vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	 ambient *= attenuation * intensity;
	 diffuse *= attenuation * intensity;
	 specular *= attenuation * intensity;

	 return (ambient + diffuse + specular);
}