#include "scop.h"

#include <time.h>
#include <stdarg.h>

bool	restart_gl_log(void)
{
	FILE	*file;
	time_t	now;
	char	*date;

	if (!(file = fopen(GL_LOG_FILE, "w")))
	{
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE"
			" log file %s for writing\n",
			GL_LOG_FILE);
		return (false);
	}
	now = time(NULL);
	date = ctime(&now);
	fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
	fclose(file);
	return (true);
}

bool	gl_log(const char *message, ...)
{
	va_list	argptr;
	FILE	*file;

	if (!(file = fopen(GL_LOG_FILE, "a")))
	{
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE"
			" %s file for appending\n",
			GL_LOG_FILE);
		return (false);
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	fclose(file);
	return (true);
}

bool	gl_log_err(const char *message, ...)
{
	va_list	argptr;
	FILE	*file;

	if (!(file = fopen(GL_LOG_FILE, "a")))
	{
		fprintf(stderr,
				"ERROR: could not open GL_LOG_FILE"
				" %s file for appending\n",
				GL_LOG_FILE);
		return (false);
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	va_start(argptr, message);
	vfprintf(stderr, message, argptr);
	va_end(argptr);
	fclose(file);
	return (true);
}
