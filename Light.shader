//Shader para dibujar objetos iluminados desde varias luces
//se debe declarar la cantidad de luces y asignar a los structs

#version 330 core

out vec4 OutColor;

//struct material/textura
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

//struct luz direccional/sol
struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//struct luz puntual
struct PointLight {
    vec3 position;
    
    //valores de cuanto se atenua
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//struct luz dirigida/linterna
struct SpotLight {
    vec3 position;
    vec3 direction;

    //valores de angulo de la linterna
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

//valores de entrada
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//desafortunadamente, no pueden variar estas luces
#define NRO_LUCES 1

//valores a ser asignados
//IMPORTANTE: ASIGNAR CON UNIFORMS
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NRO_LUCES];
uniform SpotLight spotLight;
uniform Material material;
uniform bool flash; //si hay linterna o no
uniform bool UseSpec; //si hay specular map o no

//declaraciones de funciones
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    //Poner luz ambiental direccional/sol
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    //Poner luces puntuales
    for(int i = 0; i < NRO_LUCES; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);


    //Luz Linterna
    if (flash) 
    {
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);  
    }
    
    OutColor = vec4(result, 1.0);
}



//Calcula el color de la luz direccional ambiental
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    //sombreado difuso, dependiendo del angulo
    float diff = max(dot(normal, lightDir), 0.0);

    //componente especular reflejado
    vec3 reflectDir = vec3(0.0f);
    float spec = 0.0f;

    if (UseSpec) //solo si lo usamos
    {
        reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }

    //combinar y regresar componentes, con el material en la textura
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

//Calcula el color de una luz puntual
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //calcular direccion de la luz 
    vec3 lightDir = normalize(light.position - fragPos);

    //componente difuso
    float diff = max(dot(normal, lightDir), 0.0);

    //componente especular reflejado
    vec3 reflectDir = vec3(0.0f);
    float spec = 0.0f;

    if (UseSpec) //solo si lo usamos
    {
        reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    
    //atenuar segun distancia y constante cuadratica
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    //combinar con textura
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    vec3 specular = vec3(0.0f, 0.0f, 0.0f);
    if (UseSpec) specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    //aplicar valor de atenuacion y regresar
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

//Calcular color de luz linterna
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //calcular direccion de la luz
    vec3 lightDir = normalize(light.position - fragPos);

    //componente difuso
    float diff = max(dot(normal, lightDir), 0.0);

    //reflejo especular
    vec3 reflectDir = vec3(0.0f);
    float spec = 0.0f;

    if (UseSpec) //solo si lo usamos
    {
        reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }

    //atenuar, igual que arriba
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    //se aplica intensidad, segun el angulo de la linterna y la posicion del fragmento
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    //aplicar a textura
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    vec3 specular = vec3(0.0f, 0.0f, 0.0f);
    if (UseSpec) specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    //atenuar y regresar
    float ligthVal = attenuation * intensity;
    ambient *= ligthVal;
    diffuse *= ligthVal;
    specular *= ligthVal;

    return (ambient + diffuse + specular);
}
