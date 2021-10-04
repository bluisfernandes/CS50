// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3; //3
const int INDENT_LENGTH = 4; //4

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *pp = malloc(sizeof(person));

    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents
        printf("1");
        pp->parents[0] = create_family(generations - 1);
        printf("2");
        pp->parents[1] = create_family(generations - 1);
        printf("3");
        
        // TODO: Randomly assign child alleles based on parents
        //pp->alleles[0]= pp -> parents[0] -> alleles[0]; //rand()%2
        char allel;
        allel = pp -> parents[0] -> alleles[rand()%2];
        pp->alleles[0] = allel;
        
        allel = pp -> parents[1] -> alleles[rand()%2];
        pp->alleles[1] = allel;
        
        
        printf("_");
        //pp->alleles[0]= random_allele();
        printf("4");
        //pp->alleles[1]= random_allele();
        printf("5");
        
    }

    // Generation without parent data
    else
    {
        // TODO: Set parent pointers to NULL
        printf("a");
        pp -> parents[0] = NULL;
        pp -> parents[1] = NULL;
        printf("b");
        
        // TODO: Randomly assign alleles
        printf("c");
        pp -> alleles[0] = random_allele();
        pp -> alleles[1] = random_allele();
        printf("d\n");
        //print_family(pp, 0);
    }

    // TODO: Return newly created person
    return pp; 
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case

    // TODO: Free parents

    // TODO: Free child
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
