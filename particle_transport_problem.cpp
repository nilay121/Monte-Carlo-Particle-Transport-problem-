#include<iostream>
#include<cmath>
#include<time.h>
#define pi 3.14

using namespace std;

int main()
{
    srand(time(0));
    double mf_absorption,mf_scattering,mf_total,sigma_a,sigma_s,sigma_t;
    double dx,dy,dz,r,theta,phi;
    int Nparticles=3000;
    double x[Nparticles],y[Nparticles],z[Nparticles],total_distance=0;
    int particleDetected = 0; // particle detected by the detector
    int particleAbsSca=0;  // particles scattered or absorbed

    int absorbed;

    mf_absorption = 45;  //mean free path for scattering
    mf_scattering = 0.3; //mean free path for scattering

    sigma_a = 1/mf_absorption; //cross section for absorption
    sigma_s = 1/mf_scattering; //cross section for scattering
    sigma_t = sigma_a+sigma_s; //total cross section

    mf_total = 1/sigma_t;  //Total mean free path

    //Definition of shielding material, lets say it has thickness 8 units
    // So we need to count how many particles passes the material and its probability
    float material_thickness = 8;


    for(int i=0;i<Nparticles;i++)
    {
        x[i]=0;
        y[i]=0;
        z[i]=0;
        absorbed=0;
        while (absorbed!=1)
        {
            // Creating arbitrary starting position
            r = -mf_total*log((double) rand()/RAND_MAX);
            theta = asin(-1+2*((double) rand()/RAND_MAX));
            phi= 2*pi*((double) rand()/RAND_MAX);

            dx = r*cos(theta)*cos(phi);
            dy = r*cos(theta)* sin(phi);
            dz = r*sin(theta);

            x[i] = x[i]+dx;
            y[i] = y[i]+dy;
            z[i] = z[i]+dz;

            if ((sigma_a/sigma_t)>((double) rand()/RAND_MAX))
            {
                absorbed =1;
            }

        }
        total_distance = sqrt(x[i]*x[i]+y[i]*y[i]+z[i]*z[i]);

        if (total_distance > material_thickness)
        {
            particleDetected+=1;
        }
        else
        {
            particleAbsSca+=1;
        }
    }

    cout<<"The number of particles detected by the detector are :- "<<particleDetected<<endl;
    cout<<"The number of particles scattered or absorbed are :- "<<particleAbsSca<<endl;
    cout<<"/****************************************************************/"<<endl;
    cout<<"The probability that a fired particle will reach the detector is "<<(float) (particleDetected*100)/Nparticles<<"%";

    return 0;
}
