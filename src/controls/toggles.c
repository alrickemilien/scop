#include "scop.h"

void		toggle_wireframe_mode(t_software_environ *env)
{
	if (env->wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	env->wireframe = !env->wireframe;
}

void		toggle_texturing(t_software_environ *env)
{
	env->texturing = !env->texturing;
}

void		toggle_lighting(t_software_environ *env)
{
	env->lighting = !env->lighting;
	glUniform1i(env->lighting_uni, env->lighting);
}

void		switch_clear_color(t_software_environ *env)
{
	if (env->clear_color.x < 1.0f)
	{
		env->clear_color.x += 0.35f;
		env->clear_color.y += 0.35f;
		env->clear_color.z += 0.35f;
	}
	else {
		vec3_set(&env->clear_color, 0, 0, 0);
	}

	glClearColor(env->clear_color.x, env->clear_color.y,
		env->clear_color.z, 1.0f);
}
