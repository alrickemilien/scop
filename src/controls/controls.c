# include "scop.h"

extern t_software_environ *env;

typedef struct	s_keyboard_callback_map {
		int action;
		int key;
		void (*f)(t_software_environ *env, GLFWwindow* window);
}		t_keyboard_callback_map;

static const t_keyboard_callback_map g_keyboard_callback_map[] = {
	{ GLFW_PRESS, GLFW_KEY_ESCAPE, &close_window_callback },
	{ GLFW_PRESS, GLFW_KEY_KP_SUBTRACT, &scale_down },
	{ GLFW_PRESS, GLFW_KEY_KP_ADD, &scale_up },
	{ GLFW_PRESS, GLFW_KEY_R, &switch_render_style },
	{ GLFW_PRESS, GLFW_KEY_1, &reduce_ambient_lighting },
	{ GLFW_PRESS, GLFW_KEY_2, &increase_ambient_lighting },
	{ GLFW_PRESS, GLFW_KEY_N, &render_normals },
	{ GLFW_PRESS, GLFW_KEY_G, &render_greyscale },
	{ GLFW_PRESS, GLFW_KEY_T, &render_texture },
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	size_t i;

	(void)scancode;
	(void)mods;

	i = 0;
	while (sizeof(t_keyboard_callback_map) * i < sizeof(g_keyboard_callback_map)) {
		if (g_keyboard_callback_map[i].key == key
			&& g_keyboard_callback_map[i].action == action)
		{
			g_keyboard_callback_map[i].f(env, window);
			break;
		}
		i++;
	}
}

/*void		scroll_callback(GLFWwindow *window, double scroll_x, double scroll_y)
{
	matrix_scale_xyz(env->model_matrix, 1.0f + (float)scroll_y / 10);
	(void)scroll_x;
	(void)window;
}
*/