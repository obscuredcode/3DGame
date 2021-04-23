//
// Created by mac on 5/3/20.
//

#include "physics/BB.h"

void BB::supportGlobal(const void *obj, const ccd_vec3_t *dir, ccd_vec3_t *vec) {
    BB* bb = (BB*)obj;
    bb->support(bb,dir,vec);
}
