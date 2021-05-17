
uniform vec3 lightColour;
uniform sampler2D texture;

in vec4 normal;
in vec2 textureCoords;
in vec3 lightDirection;

void main()
{
	float brightness;
	float lightLevels = 4.0;
	float lightLevel;
	vec4 color;

	brightness = dot(lightDirection, normal);
	lightLevel = floor(brightness * lightLevels);
	brightness = lightLevel/lightLevels;
	brightness = max(brightness, 0.15);

	color = brightness * vec4(lightColour,1.0);

	
	gl_FragColor = color * texture2D(texture, textureCoords);
}