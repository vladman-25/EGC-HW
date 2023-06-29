#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_coord;
layout(location = 3) in vec3 v_color;
// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 pos_car;

out vec3 frag_color;

void main()
{

    //vec3 frag_position = v_position;
    vec3 world_v_pos = (Model * vec4(v_position, 1)).xyz;
    float dist = distance(pos_car, world_v_pos);
    world_v_pos.y -= dist * dist * 0.005;
    frag_color = v_color;

    gl_Position = Projection * View  * vec4(world_v_pos, 1.0);
}
