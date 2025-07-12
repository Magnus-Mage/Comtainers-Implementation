#include <stdio.h>
#include "vector.h"

int main() {
    IntVector vec;
    init_vector(&vec);

    for (int i = 0; i < 10; i++) {
        push_back(&vec, i * 10);
    }

    for (int i = 0; i < vec.size; i++) {
        printf("vec[%d] = %d\n", i, get(&vec, i));
    }

    pop_back(&vec);
    printf("After pop_back, size = %d\n", vec.size);

    set(&vec, 0, 999);
    printf("After set, vec[0] = %d\n", get(&vec, 0));

    free_vector(&vec);
    return 0;
}

