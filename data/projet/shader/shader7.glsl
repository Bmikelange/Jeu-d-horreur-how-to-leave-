#version 330


#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;
layout(location= 1) in vec2 texcoord;
layout(location= 2) in vec3 normal;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

out vec3 p;
out vec3 n;
out vec4 frag;
out vec2 vertex_texcoord;

void main()
{
    gl_Position= mvpMatrix * vec4(position, 1);
    
    p= vec3(modelMatrix * vec4(position, 1));
    n= mat3(modelMatrix) * normal;
    frag=gl_Position;
    vertex_texcoord=texcoord;
}
#endif

#ifdef FRAGMENT_SHADER
in vec3 p;
in vec3 n;
in vec4 frag;
in vec2 vertex_texcoord;

uniform mat4 viewInvMatrix;

//~ const vec3 source= vec3(0, 0, 0);   // source dans le repere du monde
const vec3 emission= vec3(1);
const float k= 3;
const float alpha=3;
const float PI= 3.14159265359;
const float h=3;
const float r=0.5;
float a=0.2;
float f=800;

uniform sampler2D diffuse_color;
uniform vec3 source;
uniform vec3 direction;
uniform int foudre;
uniform float time;

out vec4 fragment_color;


void main( )
{
    float flameVar= a*cos(2*PI*f*time);
    vec3 camera= vec3(viewInvMatrix * vec4(0, 0, 0, 1));        // position de la camera dans le repere du monde

    //vec3  colore = vec3(0,0,1);
    float cone_dist = dot(p - source,direction);
    float cone_radius = (cone_dist / h) * r;
    float orth_distance = length((p - source) - cone_dist * direction);
   
    float i=0.08;
    if(orth_distance<2*cone_radius+0.005)
    {
	    i=1.0-(orth_distance-cone_radius)/(2*cone_radius);
        if(i>=1.0)
        {
            i=1.0;
        }
    }
    float center_dist=length(p-source);
    if(center_dist>2+flameVar)
    {
	    i=i-(center_dist-(2+flameVar))/(2+flameVar);
        if(i<0.08)
        {
            i=0.08;
        }
    }
    if(foudre<=3000)
    {
	    i=1;
    }
    float circledist = length(p - source);
    if(circledist<0.4)
    {
        i=(0.4-circledist)/0.2;
	if(circledist<=0.01)
	{
		i=4;
	}
    }
    
    

        vec4 color= texture(diffuse_color, vertex_texcoord);
        vec3 colore = vec3(color);

        vec3 normal = normalize(n);
        vec3 lightColor = vec3(1.0);
        // ambient
        vec3 ambient = 0.5 * colore;
        // diffuse
        vec3 lightDir = normalize(-direction);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * lightColor;
        // specular
        vec3 viewDir = normalize(camera - p);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
        vec3 specular = spec * lightColor;    
        // calculate shadow     
        vec3 lighting;
	if( i==0.08)
	{
        	lighting = (ambient + (diffuse + specular)) * colore*i*vec3(0,0,1);
    	}
	else
	{
		if(foudre<=3000)
	        {
		     	lighting = (5* flameVar) * (ambient + (diffuse + specular)) * colore*i*vec3(0.2,0.2,1);
	        }
		else
		{
			lighting = (ambient + (diffuse + specular)) * colore*i;
		}
	}
        
        vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * lighting; 
        
        fragment_color= vec4(MaterialAmbientColor + lighting, 1);
}
#endif

