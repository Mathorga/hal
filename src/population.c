#include "population.h"

// ########################################## Initialization functions ##########################################

error_code_t p2d_init(population2d_t** population) {
    // Allocate the population.
    (*population) = (population2d_t *) malloc(sizeof(cortex2d_t));
    if ((*population) == NULL) {
        return ERROR_FAILED_ALLOC;
    }

    // Setup population properties.
    (*population)->size = DEFAULT_POPULATION_SIZE;
    (*population)->survivors_size = DEFAULT_SURVIVORS_SIZE;
    (*population)->parents_count = DEFAULT_PARENTS_COUNT;
    (*population)->mut_chance = DEFAULT_MUT_CHANCE;

    // Allocate cortexes.
    (*population)->cortexes = (cortex2d_t *) malloc((*population)->size * sizeof(cortex2d_t));
    if ((*population)->cortexes == NULL) {
        return ERROR_FAILED_ALLOC;
    }

    // Allocate fitnesses.
    (*population)->cortexes_fitness = (cortex_fitness_t *) malloc((*population)->size * sizeof(cortex_fitness_t));
    if ((*population)->cortexes_fitness == NULL) {
        return ERROR_FAILED_ALLOC;
    }

    // Allocate survivors.
    (*population)->survivors = (population_size_t *) malloc((*population)->survivors_size * sizeof(population_size_t));
    if ((*population)->survivors == NULL) {
        return ERROR_FAILED_ALLOC;
    }

    return ERROR_NONE;
}

// ########################################## Setter functions ##################################################

error_code_t p2d_set_mut_rate(population2d_t* population, chance_t mut_chance) {
    population->mut_chance = mut_chance;

    return ERROR_NONE;
}

// ########################################## Action functions ##################################################

error_code_t p2d_evaluate(population2d_t* population) {
    // Loop through all cortexes to evaluate each of them.
    for (int i = 0; i < population->size; i++) {
        // Evaluate the current cortex by using the population evaluation function.
        // The computed fitness is stored in the population itself.
        population->cortexes_fitness[i] = population->eval_function(&(population->cortexes[i]));
    }

    return ERROR_NONE;
}

error_code_t p2d_select(population2d_t* population) {
    // TODO Sort cortexes by fitness.
    population_size_t* sorted_indexes = (population_size_t*) malloc(population->size * sizeof(population_size_t));

    // Pick the best-fitting cortexes and store them as survivors.
    population->survivors = sorted_indexes;

    // Free up temp indexes array.
    free(sorted_indexes);

    return ERROR_NONE;
}