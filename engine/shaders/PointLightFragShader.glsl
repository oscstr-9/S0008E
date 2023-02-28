#version 430

out vec3 finalOutputColor;

uniform sampler2D color;
uniform sampler2D normal;
uniform sampler2D worldPos;

uniform float width;
uniform float height;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float intensity;
uniform vec3 viewPos;
uniform float specIntensity;


void main()
{
	vec2 normalizedFragCoord = vec2(gl_FragCoord.x/width, gl_FragCoord.y/height);

	vec3 viewDir = normalize(texture(worldPos, normalizedFragCoord).xyz - viewPos);
	vec3 lightDir = normalize(lightPos - texture(worldPos, normalizedFragCoord).xyz);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	vec3 ambient = intensity * lightColor;

	float diff = max(dot(texture(normal,normalizedFragCoord).xyz, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float spec = pow(max(dot(texture(normal, normalizedFragCoord).xyz, halfwayDir), 0.0), 64);
	vec3 specular = lightColor * spec;

	vec3 toLight = lightPos - texture(worldPos, normalizedFragCoord).xyz;
	float d = length(toLight);
	float attenuation = clamp(10.0 / d, 0.0, 1.0);

	finalOutputColor = (texture(color, normalizedFragCoord) * (attenuation * vec4(ambient + diffuse + specular, 1.0))).xyz;
}