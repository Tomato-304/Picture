#include <stdio.h>
#include <string.h>

#define SIZE 30

int main()
{
    int start_option;
    char c[SIZE];
    char dist[SIZE + 1];
    scanf("%s", c);
    scanf("%d", &start_option);
    strncpy(dist, c + start_option, sizeof(dist) - 1);
    dist[sizeof(dist) - 1] = '\0';
    printf("%s\n", dist);
    return 0;
}