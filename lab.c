#include <malloc.h>
#include <assert.h>
#include "lab.h"
#include "globals.h"

Lab *all_labs;

void lab_init(int n) {
    all_labs = (Lab *) malloc(n * sizeof(Lab));
    assert(all_labs);
    for (int i = 0; i < n; i++) {
        all_labs[i].id = i;
        all_labs[i].available = 1;
        all_labs[i].name = (char *) malloc(MAX_LAB_NAME);
        assert(all_labs[i].name);
    }
}

void *lab_process(void *input) {
    Lab *lab = (Lab *) input;
    int found = 1;
    while (found) {
        found = 0;
        for (int i = 0; i < lab->numTA; i++) {
            if (lab->taTimes[i] < lab->TALimit) {
                found = 1;
                break;
            }
        }
    }
    printf(C_LAB "Lab %s no longer has students available for TAship\n" RESET, lab->name);
    lab->available = 0;
    return NULL;
}
