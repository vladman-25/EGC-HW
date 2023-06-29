#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform vec3 light_direction;
uniform int light_nr;
uniform vec3 light_position[200];
uniform vec3 light_color[200];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

uniform sampler2D texture_1;
uniform float Time;
uniform float TimeY;
uniform int Earth;
uniform int spotlight_on[200];
// TODO(student): Declare various other uniforms


// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec4 color1;

    if (Earth == 1) {
        vec2 tex = texcoord;
        tex.y += Time * 0.5;
        tex.x += TimeY * 0.35;
        color1 = texture2D(texture_1, tex); 
    } else {
        color1 = texture2D(texture_1, texcoord); 
    }
   
    vec4 color = color1;

    if (color.a < 0.5f) {
        discard;
    }
    //object_color = color.xyz

    float cut_off = radians(20.0);
    float spot_light_limit = cos(cut_off);
    vec3 V = normalize( eye_position - world_position );

    
    float spot_light[200];
    float factorAtenuare[200];
    vec3 L[200];
    vec3 H[200];
    vec3 R[200];
    float light_att_factor[200];

    float ambient_light[200];
    float diffuse_light[200];
    float specular_light[200];


    for(int i = 1; i < light_nr; i ++) {

        ambient_light[i] = 0.25;
        diffuse_light[i] = 0;
        specular_light[i] = 0;

       

        L[i] = normalize( light_position[i] - world_position );
        H[i] = normalize( L[i] + V );
        diffuse_light[i] = material_kd * max (dot(world_normal,L[i]), 0);
        R[i] = reflect (-L[i], world_normal);
        spot_light[i] = dot(-L[i], light_direction);

        if (spot_light[i] > cos(cut_off))
        {
	        float linear_att = (spot_light[i] - spot_light_limit) / (1.0f - spot_light_limit);
            light_att_factor[i] = pow(linear_att, 2);

        } else {
            light_att_factor[i] = 0;
        }
        if (diffuse_light[i] > 0)
        {
            specular_light[i] = material_ks * pow(max(dot(V, R[i]), 0), material_shininess);
        } else {
            specular_light[i] = 0;
        }
        float d = distance(light_position[i],world_position);
        factorAtenuare[i] = 1 / (d * d);
    }


    ambient_light[0] = 0.25;
    diffuse_light[0] = 0;
    specular_light[0] = 0;
    L[0] = vec3(0.0f, 0.0f,-1.0f);
    H[0] = normalize( L[0] + V );
    diffuse_light[0] = material_kd * max (dot(world_normal,L[0]), 0);
    R[0] = reflect (-L[0], world_normal);


    if (diffuse_light[0] > 0)
    {
        specular_light[0] = material_ks * pow(max(dot(V, R[0]), 0), material_shininess);
    } else {
        specular_light[0] = 0;
    }

    




    vec3 light;
    vec3 sum = vec3(0);

    for(int i = 1; i < light_nr; i++) {
        if (spotlight_on[i] == 1) {
            sum += 40 * light_att_factor[i] * factorAtenuare[i] * ( diffuse_light[i]*light_color[i] + specular_light[i]*light_color[i]);
        } else {
            sum += factorAtenuare[i] * ( diffuse_light[i]*light_color[i] + specular_light[i]*light_color[i]);
        }
    }

    sum += ( diffuse_light[0]*vec3(1,1,1) + specular_light[0]*vec3(1,1,1));

    light = ambient_light[1] + sum;

    

    // TODO(student): Calculate the out_color using the texture2D() function.
    

    out_color = color * vec4(light,1);

}
