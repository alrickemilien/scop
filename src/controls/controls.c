# include "scop.h"

extern t_software_environ *env;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	(void)key;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
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
