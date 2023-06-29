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

// Output
// TODO(student): Output values to fragment shader

out vec3 frag_color;
void main()
{
    // TODO(student): Send output to fragment shader

    frag_color = v_color;


    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
