#include <stdio.h>
#include <string.h>
#include <math.h>

int main (void)
{
    const long N = pow(27,5);  //max 11letters = 27^11
    //const long N = 27.0*27*27*27*27*27*27*27*27*27*27*27;
    char *s = "aaaaazzzzzzzzzzzzzzzzzzzzzzzz";
    
    long double hash = 0;
    const int p = 27;
    long double p_pow = 1;
    printf("%ld\n", N);

    for (long i = 0, j = N; j > 1; j=j/p)
    {
        printf("%ld- ",i);
        
        if(s[i] == '\'')
        {
            printf("%c,%d\t\t",s[i],s[i]-'\'' + 26);
            hash = hash + p_pow * (s[i] - '\'' + 26);  
        }
        else
        {
            printf("%c,%d\t\t",s[i],s[i]-'a');
            hash = hash + p_pow * (s[i] - 'a');  
        }
        printf("hash = %Lf\t\t", hash);
        printf("p_pow = %Lf\n", p_pow);
        
        p_pow = p_pow * p;
        
    i++;   
    }
    
    
    printf("hash =           %Lf\n", hash);
    printf("(hash / N) =      %Lf\n", (hash / N)); 
    printf("round(hash / N) = %Lf\n", roundl(hash / N));
    printf("N*round(hashN) = %Lf\n", N * roundl(hash / (long double) N));
    
    //hash -= N * round(hash / N);
    hash = (long long) hash % N;
    
    printf("hash =                           %Lf\n", hash);
    printf("hash =                           %Lf\n", N-hash);
    
    
}