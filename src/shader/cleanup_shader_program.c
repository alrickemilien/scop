#include "scop.h"

static void cleanup_shader(shader_program_t *p, shader_t *s)
{
    if (!s)
        return;

	glDetachShader(p->id, s->id);
    
    glDeleteShader(p->id);
    
    free(s->path);

#ifdef __APPLE__
    munmap(s->content, s->length);
#endif
#ifdef _MSC_VER
    free(s->content);
#endif

    free(s);
}

void cleanup_shader_program(shader_program_t *p)
{
    cleanup_shader(p, p->vertex_shader);
    
    cleanup_shader(p, p->fragment_shader);
    
    cleanup_shader(p, p->geometry_shader);
	
    glDeleteProgram(p->id);
}