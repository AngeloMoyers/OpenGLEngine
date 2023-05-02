#version 330 core
out vec4 FragColor;

struct Material
{
    float shininess;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D diffuseTexture1;
uniform sampler2D specularTexture1;

uniform vec3 uViewPosition;
uniform Material uMaterial;
uniform PointLight uPLight[1];
uniform int uPointLightCount;
uniform DirectionalLight uDLight;
uniform SpotLight uSLight;

in vec3 WorldPos;
in vec3 Normal;
in vec2 TexCoords;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    //diffuse
    float diff = max(dot(normal,lightDir), 0.0);
    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    //combine
    vec3 ambient = light.ambient * vec3(texture(diffuseTexture1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuseTexture1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(specularTexture1, TexCoords));

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(diffuseTexture1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseTexture1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(specularTexture1, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(diffuseTexture1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuseTexture1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(specularTexture1, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(uViewPosition - WorldPos);
    
    vec3 result = CalculateDirectionalLight(uDLight, norm, viewDir);
    
    for (int i = 0; i < uPointLightCount; i++)
    {
        result += CalcPointLight(uPLight[i], norm, WorldPos, viewDir);
    }

    result += CalcSpotLight(uSLight, norm, WorldPos, viewDir);
    
    FragColor = vec4(result, 1.0f);
}