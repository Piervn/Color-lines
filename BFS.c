#include "kulki.h"

bool isPath(int tab[N][N], int start, int dest)
{
    int arr[N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            arr[i][j]=tab[i][j];
        }
    }
    //KIERUNKI
    int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    queue* kolejka = createQueue(N*N);

    enqueue(kolejka, start);//PUNKT POCZATKOWY

    //DOPOKI KOLEJKA NIEPUSTA
    while(kolejka->size>0)
    {
        int s = dequeue(kolejka);

        if(s == dest)//CEL
        {
            free(kolejka);
            return true;
        }

        //4 kierunki
        for(int i=0; i<4 ;i++)
        {
            int a = s/N + dir[i][0];
            int b = s%N + dir[i][1];
            int x = a*N + b;

            //PRAWIDLOWOSC PUNKTU
            if(arr[a][b]==0 && a>=0 && b>=0 && a<N && b<N)
            {
                arr[a][b] = 1;
                enqueue(kolejka, x);
            }
        }
    }
    return false;
}
