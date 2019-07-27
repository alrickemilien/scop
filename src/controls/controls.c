#include "scop.h"

extern t_software_environ               *env;

static const t_keyboard_callback_map    g_keyboard_callback_map[] = {
    {GLFW_PRESS, GLFW_KEY_ESCAPE, &close_window_callback},
    {GLFW_PRESS, GLFW_KEY_KP_SUBTRACT, &scale_down},
    {GLFW_PRESS, GLFW_KEY_KP_ADD, &scale_up},
    {GLFW_PRESS, GLFW_KEY_R, &switch_render_style},
    {GLFW_PRESS, GLFW_KEY_1, &reduce_ambient_lighting},
    {GLFW_PRESS, GLFW_KEY_2, &increase_ambient_lighting},
    {GLFW_PRESS, GLFW_KEY_N, &render_normals},
    {GLFW_PRESS, GLFW_KEY_G, &render_greyscale},
    {GLFW_PRESS, GLFW_KEY_T, &render_texture},

    // Lock/Unlock Z axis
    {GLFW_PRESS, GLFW_KEY_Z, &lock_z_axis},
    {GLFW_RELEASE, GLFW_KEY_Z, &unlock_z_axis},

    // Lock/Unlock Z axis
    {GLFW_PRESS, GLFW_KEY_Y, &lock_y_axis},
    {GLFW_RELEASE, GLFW_KEY_Y, &unlock_y_axis},

    // Lock/Unlock Z axis
    {GLFW_PRESS, GLFW_KEY_X, &lock_x_axis},
    {GLFW_RELEASE, GLFW_KEY_X, &unlock_x_axis},

    // Move axis
    {GLFW_PRESS, GLFW_KEY_UP, &move_forward_on_axis},
    {GLFW_RELEASE, GLFW_KEY_DOWN, &move_backward_on_axis},
};

void                                    key_callback(
    GLFWwindow *window,
    int key,
    int scancode,
    int action,
    int mods)
{
	size_t  i;

	(void)scancode;
	(void)mods;

	i = 0;
	while (sizeof(t_keyboard_callback_map) * i < sizeof(g_keyboard_callback_map))
	{
		if (g_keyboard_callback_map[i].key == key && g_keyboard_callback_map[i].action == action)
		{
			g_keyboard_callback_map[i].f(env, window);
			break;
		}
		i++;
	}
}