#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

typedef struct ThreadArgs
{
    char *X;
    char *Y;
    int start;
    int end;
    int n;
    int **dp;
    pthread_mutex_t *mutex;
} ThreadArgs;

void *thread_func(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    char *X = args->X;
    char *Y = args->Y;
    int start = args->start;
    int end = args->end;
    int n = args->n;
    int **dp = args->dp;
    pthread_mutex_t *mutex = args->mutex;

    for (int i = start; i < end; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            pthread_mutex_lock(mutex);
            if (X[i] == Y[j])
                dp[i + 1][j + 1] = dp[i][j] + 1;
            else
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            pthread_mutex_unlock(mutex);
        }
    }

    return NULL;
}

int pthread_lcs(char *X, char *Y)
{
    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; ++i)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = 0;
    }

    for (int i = 0; i <= n; ++i)
    {
        dp[0][i] = 0;
    }

    const int num_threads = 4;
    pthread_t threads[num_threads];
    ThreadArgs args[num_threads];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    int interval = m / num_threads;
    for (int i = 0; i < num_threads; ++i)
    {
        args[i].X = X;
        args[i].Y = Y;
        args[i].start = i * interval;
        args[i].end = (i == num_threads - 1) ? m : (i + 1) * interval;
        args[i].n = n;
        args[i].dp = dp;
        args[i].mutex = &mutex;

        pthread_create(&threads[i], NULL, thread_func, &args[i]);
    }

    for (int t = 0; t < num_threads; ++t)
    {
        pthread_join(threads[t], NULL);
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; ++i)
    {
        free(dp[i]);
    }
    free(dp);

    pthread_mutex_destroy(&mutex);

    return result;
}

int main()
{
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int lcs_length = pthread_lcs(X, Y);
    printf("Length of LCS is %d\n", lcs_length);

    return 0;
}