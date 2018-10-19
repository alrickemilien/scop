#ifndef LIBMATRIX_H
# define LIBMATRIX_H

# include <stdint.h>
# include <stdbool.h>

/*
** A vector t_vec is simply a matrix 4x1
** It is the most simple way to
** describe a point, a position, a direction, etc 
*/

typedef struct  s_vec {
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t w;
}               t_vec;

typedef struct  s_matrix_4x4 {
        t_vec   first_row;
        t_vec   second_row;
        t_vec   third_row;
        t_vec   fourth_row;
}               t_matrix_4x4;

#endif