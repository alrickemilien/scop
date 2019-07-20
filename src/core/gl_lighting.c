#include "scop.h"

int gl_lighting(t_software_environ *env)
{
    printf("%s\n", "GL Lighting");

    env->light_position = (t_vec3){5.f, 5.f, 5.f};

    env->ambient_lighting_uni = glGetUniformLocation(env->object_shader_program.id, "ambient_light");

    env->specular_lighting_uni = glGetUniformLocation(env->object_shader_program.id, "specular_light");

    env->light_uni = glGetUniformLocation(env->object_shader_program.id, "light");

    env->is_texture_uni = glGetUniformLocation(env->object_shader_program.id, "is_texture_rendered");

    return (0);
}