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

static void	user_rotate(float pos_x, float pos_y)
{
	if (env->prev_mouse_pos.x < 0)
		return ;
	matrix_rotate_y(env->model_matrix,
		(env->prev_mouse_pos.x - pos_x) / 500.0f);
	matrix_rotate_x(env->model_matrix,
		(env->prev_mouse_pos.y - pos_y) / 500.0f);
}

void		mouse_move_callback(GLFWwindow *window, double pos_x, double pos_y)
{
	if (env->user_control == USER_CONTROL_NONE)
		return ;
	if (env->user_control == USER_CONTROL_ROTATE)
		user_rotate((float)pos_x, (float)pos_y);
	env->prev_mouse_pos.x = (float)pos_x;
	env->prev_mouse_pos.y = (float)pos_y;
	(void)window;
}

void		mouse_click_callback(GLFWwindow *window, int button, int action,
	int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		env->auto_rotate = 0;
		if (action == GLFW_PRESS)
			env->user_control = USER_CONTROL_ROTATE;
		else
		{
			env->user_control = USER_CONTROL_NONE;
			env->prev_mouse_pos.x = -1.0f;
			env->prev_mouse_pos.y = -1.0f;
		}
	}

	(void)window;
	(void)mods;
}*/
