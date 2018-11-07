/* FHT/FFT performance comparison
 2    John Bryan 2017
 3    -lrt -lm -lfftw3 -O3
 4    gcc 4.6.3
 5 */

#include "fht.h"

#define BILLION 1000000000L
// rows is the number of lengths
#define rows 10
// columns is the number of iterations averaged
#define columns 1000

using namespace std;

double randf(void)
{
    //return random value between -1 and 1
    double low=-1.0, high=1.0;
    return (rand()/(double)(RAND_MAX))*abs(low-high)+low;
}


double dAvg(int array[], size_t length){
    // compute average
    size_t c;
    double sum = 0;
    for (c = 0; c < length; c++){ sum += array[c]; }
    return sum / (double) length;
}


int n_close(double A, double B, double maxDiff, double maxRelDiff)
{
    float diff = fabs(A - B);
    if (diff <= maxDiff)
    {return 0;}
    A = fabs(A);
    B = fabs(B);
    double largest = (double)(B > A) ? B : A;
    if (diff <= largest * maxRelDiff)
    {return 0;}
    assert(0);
}




void swap2 (double *x, int i, int j)
{
    // used in bitreversal2
    double temp;
    temp=x[i];
    x[i]=x[j];
    x[j]=temp;
}

double * bitreversal2(double *x, int N)
{
    // used just before fht
    int M=1,T,k,n,h,r[N];
    for (h=0;h<N;h++)
        r[h]=0;
    while (M<N)
    {
        k=0;
        while (k<M)
        {
            T= (int)(2*r[k]);
            r[k]=T;
            r[k+M]=T+1;
            k=k+1;
        }
        M = (int)(2*M);
    }
    n=1;
    while (n<(N-1)) {
        if (r[n]>n) swap2(x,n,r[n]);
        n=n+1;
    }
    return x;
}

double *  fht(double *x, double *xo, double *c, double *s,int N,int p)
{
    // fast hartley transform
    int Np=2,Npp=1,baseT=0,baseB=0,baseBB=0,Nmn=0,n=0,tf=0,Bp=N/2,tss=N/2,P=0,b=0;
    double xcs;
    for (P=0; P<p; P++)
    {
        Npp=Np/2;
        baseT=0;
        for (b=0; b<Bp; b++)
        {
            baseB=baseT+Npp;
            baseBB=baseT+Np;
            for (n=0;n<Npp;n++)
            {
                tf=n*tss;
                Nmn=(baseBB-n)%baseBB;
                if (P%2==0)
                {
                    if (n==0)
                        xcs=x[baseB+n];
                    else
                        xcs=(x[baseB+n]*c[tf])+(x[Nmn]*s[tf]);
                    xo[baseT+n]=x[baseT+n]+xcs;
                    xo[baseB+n]=x[baseT+n]-xcs;
                }
                else
                {
                    if (n==0)
                        xcs=xo[baseB+n];
                    else
                        xcs=(xo[baseB+n]*c[tf])+(xo[Nmn]*s[tf]);
                    x[baseT+n]=xo[baseT+n]+xcs;
                    x[baseB+n]=xo[baseT+n]-xcs;
                }
            }
            baseT=baseT+Np;
        }
        Bp=Bp/2;
        Np=Np*2;
        tss=tss/2;
    }
    if (p%2==0)
        return x;
    else
        return xo;
}

