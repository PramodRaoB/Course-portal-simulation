#include <malloc.h>
#include <assert.h>
#include "lab.h"

Lab *all_labs;

void lab_init(int n) {
    all_labs = (Lab *) malloc(n * sizeof(Lab));
    assert(all_labs);
    for (int i = 0; i < n; i++) {
        all_labs[i].id = i;
        all_labs[i].name = (char *) malloc(MAX_LAB_NAME);
        assert(all_labs[i].name);
    }
}
