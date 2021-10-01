#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair pairs_real[MAX * (MAX - 1) / 2];

int pair_count;
int pair_real_count;

int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);


void print_preferences(void);
void print_pairs(void);
void print_locked(void);

bool check( int n, int i, int j);

// int listi[]={0,1,3,2,1,2,0,0};
// int listj[]={1,3,0,3,2,0,3,2};

int listi[]={0,2,1,3,1,2,0,0};
int listj[]={1,3,3,0,2,0,3,2};

 
int main(int argc, string argv[])
{
    
    pair_count = 8;
    candidate_count = 4; 
    
    for(int i = 0; i < pair_count;i++ )
    {
        pairs[i].winner = listi[i];
        pairs[i].loser = listj[i];
        
    }
    pairs_real[0]=pairs[0];
    printf("pairs real: (%d,%d)\n",pairs[0].winner, pairs_real[0].loser);
    
    print_pairs(); 
    
    lock_pairs();
    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // if name is a valid vote, populate ranks
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // record all preferences of rank, 2 by 2.

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1 ; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Create a list of pairs with who lose and who wins. If a tie occurs, dont go to the list

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i]) 
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

        }
    }
   print_pairs();   //plot pairs DEL*******************************


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //temporary value to change the positiont in bubble sort
    pair change[1];

   //the lower value go to the end of the list.
    //of each 2 values, the position can be changed.
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            //array pairs is sorted by the respect value in preferences.
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser] )
            {
                change[0] = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = change[0];
            }
        }
    }
    //debug    *******************DEL
    print_pairs();
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (check(i, pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            pairs_real[i] = pairs[i];
            printf("\t\tpairs_real[%d] = (%d,%d)\n", i, pairs_real[i].winner, pairs_real[i].loser);
            
            printf("[%d] ok: (%d,%d)\n", i,pairs[i].winner, pairs[i].loser);
        }
        else
        {
            printf("[%d] ficou fora: (%d,%d)\n", i,pairs[i].winner, pairs[i].loser);
        }
    }

    print_locked();     //******************

    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner;
    // check the column of locked graph without true values. This candidate is the winner.
    for (int j = 0; j < candidate_count; j++)
    {
        winner = true;
        for (int i = 0; i < candidate_count; i++)
        {
            if(locked[i][j] == true)
            {
                winner = false;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[j]);
        }
    }
    return;
}

//plot the preferences DEBUG*****
void print_preferences(void)
{
    printf(" preferecences\n");
    for (int k = 0; k < candidate_count ; k++)
    {
        printf("|");
        for (int j = 0 ; j < candidate_count; j++)
        {
            //printf("(%d,%d)", k, j);
            printf(" %d ",preferences[k][j]);
        }
    printf("|\n");
    }
    return;
}

//plot the pairs with preference number DEBUG****
void print_pairs(void)
{
    printf("  pairs\n");
    for (int j = 0; j < pair_count; j++)
    {
        printf("[%d] %d  %d  (%d)\n", j, pairs[j].winner, pairs[j].loser, preferences[pairs[j].winner][pairs[j].loser]);
    }
    return;
}


//check if the pair can be putted in the locked graph****
bool check( int n, int i, int j)
{   
    //printf("_");
    for (int j0 = 0; j0 < n - 0; j0++)
    {
        //printf("%d,",j0);
        //printf("\tj0=%d (%d,%d)\n", j0, pairs[j0].winner, pairs[j0].loser); 
        if (pairs_real[j0].loser == i)
        {
            if (pairs_real[j0].winner == j) 
            {
                printf("(%d,%d) =\n", i, j);
                return false;
            }
            else if(check(n-1, pairs[j0].winner, j) == false)
            {
                //printf("(%d,%d) =\n", i, j);
                return false;
            }
        }
    }
    //printf("|");
    
    return true;
}


//print locked table DEBUG*****
void print_locked(void)
{
        //delete below: imprime tabela de preferencias
    printf(" locked\n");
    for (int k = 0; k < candidate_count ; k++)
    {
        printf("|");
        for (int j = 0 ; j < candidate_count; j++)
        {
            //printf("(%d,%d)", k, j);
            printf(" %d ",locked[k][j]);
            //printf(locked[k][j] ? " T " : " F ");
        }
    printf("|\n");
    }
    return;
}