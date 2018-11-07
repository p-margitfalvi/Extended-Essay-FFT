//
//  Hartley.cpp
//  extendid esej
//
//  Created by Pavol Margitfalvi on 05/11/2018.
//  Copyright © 2018 Pavol Margitfalvi. All rights reserved.
//

#include "Hartley.hpp"

Hartley::Hartley(const string &name) : FFT(name){
    return;
}

void Hartley::separate(double* X, const long length) {
    double* b;
    b = new double [length/2];
    
    for (long i = 0; i < length / 2; i++) {
        b[i] = X[2*i + 1];
    }
    
    for (long i = 0; i < length / 2; i++) {
        X[i] = X[2*i];
    }
    
    for (long i = 0; i < length / 2; i++) {
        X[i + length / 2] = b[i];
    }
    
    delete [] b;
}

void Hartley::separate(complex<double>* X, const long length) {
    complex<double>* b;
    b = new complex<double> [length/2];
    
    for (long i = 0; i < length / 2; i++) {
        b[i] = X[2*i + 1];
    }
    
    for (long i = 0; i < length / 2; i++) {
        X[i] = X[2*i];
    }
    
    for (long i = 0; i < length / 2; i++) {
        X[i + length / 2] = b[i];
    }
    
    delete [] b;
}

void Hartley::compute(double* X, const long length) {
    if (length < 2) {
        return;
    } else {
        separate(X, length);
        
        compute(X, length / 2);
        compute(X + length / 2, length / 2);
        
        for(long i = 0; i < length/2; i++) {
            
            double e = X[i];
            double o = X[i + length/2];
            double z = X[length - 1 - i];
            
            double arg = (2*M_PI*i)/length;
            double w = o*cos(arg) + z*sin(arg);
            X[i] += e + w;
            X[i + length / 2] += e - w;
            
            /*
            double arg = 4*M_PI*i/length;
            double e = X[i];
            double o = X[i + length/2];
            double z = X[length - 1 - i];
            
            arg = 2*M_PI*i/length;
            double w = o*cos(arg) + z*sin(arg);
            
            X[i] = e + w;
             X[i + length/2] = e - w;
             */
        }
    }
    
}

void Hartley::discrete() {
    
    for (int k = 0; k < sampleCount; ++k) {
        
        for (int n = 0; n < sampleCount; ++n) {
            double arg = 2*M_PI*k*n/sampleCount;
            H[k] += samples[n].real()*(cos(arg) + sin(arg));
        }
        
    }
    
}

void Hartley::discreteHalved() {
    
    separate(samples, sampleCount);
    
    for (int k = 0; k < sampleCount / 2; ++k) {
        
        for (int n = 0; n < sampleCount / 2; ++n) {
            double arg = 4*M_PI*k*n/sampleCount;
            double backwardsArg = 4*M_PI*(sampleCount - k)*n/sampleCount;
            double Y = samples[n].real()*(cos(arg) + sin(arg));
            double Z = samples[sampleCount / 2 + n].real()*(cos(arg) + sin(arg));
            double backwardsZ = samples[sampleCount / 2 + n].real()*(cos(backwardsArg) + sin(backwardsArg));
            H[k] += Y + (cos((2*M_PI*k)/sampleCount)*Z + sin((2*M_PI*k)/sampleCount)*backwardsZ);
            H[sampleCount / 2 + k] += Y - (cos(2*M_PI*k/sampleCount)*Z + sin(2*M_PI*k/sampleCount)*backwardsZ);
        }
        
    }
    
}

void Hartley::pseudoversion(double* a, const long length, double* x) {
    double *b,*c,*s,*t;
    b = new double [length/2];
    c = new double [length/2];
    s = new double [length/2];
    t = new double [length/2];
    if (length == 1) {
        x[0] = a[0];
        return;
    }
    long lengthHalf = length / 2;
    
    for (long k = 0; k < lengthHalf; ++k) {
        s[k] = a[2*k];
        t[k] = a[2*k + 1];
    }
    
    pseudoversion(s, lengthHalf, b);
    pseudoversion(t, lengthHalf, c);
    
    hartleyShift(c, lengthHalf);
    
    for (long k = 0; k < lengthHalf; ++k) {
        x[k] = b[k] + c[k];
        x[k + lengthHalf] = b[k] - c[k];
    }
    
    
    delete [] b; delete [] c; delete [] s; delete [] t;
}

void Hartley::hartleyShift(double* c, const long length) {
    
    long j = length - 1;
    for (long k = 0; k < j; ++k, --j) {
        double arg = (2*M_PI*k)/length;
        double ck = c[k];
        double cj = c[j];
        c[k] = ck*cos(arg) + cj*sin(arg);
        c[j] = ck*sin(arg) - cj*cos(arg);
    }
    
}

void Hartley::computeDiscrete() {
    for (long k = 0; k < sampleCount; ++k) {
        H[k] = 0;
    }
    discrete();
    for (long i = 0; i < sampleCount; ++i) {
        output[i] = complex<double>((H[i] + H[sampleCount - i])/2, (H[i] - H[sampleCount - i])/2);
    }
}

void Hartley::computeDiscreteHalved() {
    for (long k = 0; k < sampleCount; ++k) {
        H[k] = 0;
    }
    discreteHalved();
    for (long i = 0; i < sampleCount; ++i) {
        output[i] = complex<double>((H[i] + H[sampleCount - i])/2, (H[i] - H[sampleCount - i])/2);
    }
}

void Hartley::computePseudo() {
    double* b;
    b = new double[sampleCount];
    for (long k = 0; k < sampleCount; ++k) {
        H[k] = 0;
        b[k] = samples[k].real();
    }
    pseudoversion(b, sampleCount, H);
    for (long i = 0; i < sampleCount; ++i) {
        output[i] = complex<double>((H[i] + H[sampleCount - i])/2, (H[i] - H[sampleCount - i])/2);
    }
    delete [] b;
}

void Hartley::computeFourier() {
    compute(H, sampleCount);
    for (long i = 0; i < sampleCount; ++i) {
        //H[i] = output[i].real();
        output[i] = complex<double>((H[i] + H[sampleCount - i])/2, (H[i] - H[sampleCount - i])/2);
    }
    
}

void Hartley::toReal() {
    for (long i = 0; i < sampleCount; ++i) {
        H[i] = samples[i].real();
    }
}

void Hartley::generateSamples() {
    FFT::generateSamples();
    toReal();
}

double* Hartley::pyTransform(double* xvector, double* xarray, double* cosine, double* sine, long length, long log2length) {
    
    for (long i = 0; i < length; ++i) {
        xarray[i] = 0;
    }
    long b_p = length / 2;
    long n_p = 2;
    long tss = length / 2;
    for (long pvar = 0; pvar < log2length; ++pvar) {
        long npp = n_p/2;
        long baset = 0;
        for (long bvar = 0; bvar < b_p; ++bvar) {
            long baseb = baset + npp;
            long basebb = baset + n_p;
            for (long nvar = 0; nvar < npp; ++nvar) {
                long t_f = nvar*tss;
                long nmn = (basebb - nvar) % basebb;
                if (pvar % 2 == 0) {
                    double xcs;
                    if (nvar == 0) {
                        xcs = xvector[baseb + nvar];
                    } else {
                        xcs = xvector[baseb + nvar]*cosine[t_f] + xvector[nmn]*sine[t_f];
                    }
                    xarray[baset + nvar] = xvector[baset + nvar] + xcs;
                    xarray[baseb + nvar] = xvector[baset + nvar] - xcs;
                } else {
                    double xcs;
                    if (nvar == 0) {
                        xcs = xarray[baseb + nvar];
                    } else {
                        xcs = xarray[baseb + nvar]*cosine[t_f] + xarray[nmn]*sine[t_f];
                    }
                    xvector[baset + nvar] = xarray[baset + nvar] + xcs;
                    xvector[baseb + nvar] = xarray[baset + nvar] - xcs;
                }
            }
            baset = baset + n_p;
        }
        b_p = b_p / 2;
        n_p = n_p*2;
        tss = tss / 2;
    }
    if ((log2length - 1) % 2 == 0) {
        return xarray;
    } else {
        return xvector;
    }
    
}

void Hartley::swap(double* x, long i, long j) {
    double temp = x[i];
    x[i] = x[j];
    x[j] = temp;
}

double* Hartley::digitReversal(double* xarray, long length, long log2length) {
    int n1var;
    if (log2length % 2 == 0) {
        n1var = (int)sqrt(length);
    } else {
        n1var = (int)sqrt(length/2);
    }
    
    long* reverse = new long[n1var];
    for (long i = 0; i < n1var; ++i) {
        reverse[i] = 0;
    }
    reverse[1] = length/2;
    for (long i = 0; i < n1var/2; ++i) {
        reverse[2*i] = long(reverse[i]/2);
        reverse[2*i + 1] = reverse[2*i] + reverse[1];
    }
    // Algorithm 1
    for (long i = 0; i < n1var - 1; ++i) {
        for (long j = i + 1; j < n1var; ++j) {
            long uvar = i + reverse[j];
            long vvar = j + reverse[i];
            swap(xarray, uvar, vvar);
            if (log2length % 2 == 1) {
                uvar = i + reverse[j] + n1var;
                vvar = j + reverse[i] + n1var;
                swap(xarray, uvar, vvar);
            }
        }
    }
    
    
    delete [] reverse;
    return xarray;
}

void Hartley::computeTest() {
    
    double* xarray = new double[sampleCount];
    double* garray = new double[sampleCount];
    double* sine = new double[sampleCount];
    double* cosine = new double[sampleCount];
    
    for (long i  = 0; i < sampleCount; ++i) {
        xarray[i] = 0;
        sine[i] = sin(2*M_PI*i/sampleCount);
        cosine[i] = cos(2*M_PI*i/sampleCount);
    }
    garray = digitReversal(H, sampleCount, (long)log2(sampleCount));
    xarray = pyTransform(garray, xarray, cosine, sine, sampleCount, (long)log2(sampleCount));
    
    for (long i = 0; i < sampleCount; ++i) {
        //H[i] = output[i].real();
        output[i] = complex<double>((xarray[i] + xarray[sampleCount - i])/2, (xarray[i] - xarray[sampleCount - i])/2);
    }
    
    //delete [] xarray; delete [] garray; delete [] sine; delete [] cosine;
}
