#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int mixed;

// Output
out vec2 texcoord;
out vec3 world_position;
out vec3 world_normal;

void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;
    world_position = (Model * vec4(v_position, 1)).xyz;
    world_normal = normalize((Model * vec4(v_normal, 1)).xyz);
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
