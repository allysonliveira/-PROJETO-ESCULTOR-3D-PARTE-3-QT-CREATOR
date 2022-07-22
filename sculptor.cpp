#include "sculptor.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx; ny = _ny; nz = _nz;


    if (nx <= 0 || ny <= 0 || nz <= 0){
        nx = ny = nz = 0;
    }

    v = new Voxel**[nz];

    v[0] = new Voxel*[nz*nx];

    for (int z=1; z<nz; z++){
        v[z] = v[z-1] + nx;
    }

    v[0][0] = new Voxel[nz*nx*ny];


    int n = 0;
    for (int z=0; z<nz; z++){
        for(int x=0; x<nx; x++){
            v[z][x] = v[0][0] + n*ny;
            n++;
        }
    }
}


Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

void Sculptor::setColor(float vermelho, float verde, float azul, float alpha){
   r = vermelho;
   g = verde;
   b = azul;
   a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z){

    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}


void Sculptor::cutVoxel(int x, int y, int z){
v[x][y][z].isOn = false;
}



void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for(int z=z0; z<=z1; z++){
        for(int y=y0; y<=y1; y++){
            for(int x=x0; x<=x1; x++){

                putVoxel(x,y,z);

            }
        }
    }

}


void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for(int z=z0; z<=z1; z++){
        for(int x=x0; x<=x1; x++){
            for(int y=y0; y<=y1; y++){
                cutVoxel(x,y,z);
            }
        }
    }

}


void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){

    double distancia;

    for(int z=0; z<=nz; z++){
        for(int y=0; y<=ny; y++){
            for(int x=0; x<=nz; x++){

                distancia = pow(x - xcenter, 2) + pow(y - ycenter, 2) + pow(z - zcenter, 2) ;
                if(distancia <= pow(radius,2) ){

                    putVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){

    double distancia;

    for(int z=0; z<=nz; z++){
        for(int y=0; y<=ny; y++){
            for(int x=0; x<=nx; x++){

                distancia = pow(x - xcenter, 2) + pow(y - ycenter, 2) + pow(z - zcenter, 2) ;
                if(distancia <= pow(radius,2) ){

                    cutVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

    double distancia;

    if(rx == 0){
        for(int z=0; z<=nz; z++){
            for(int y=0; y<=ny; y++){

                distancia = pow(y - ycenter, 2)/pow(ry, 2) + pow(z - zcenter, 2)/pow(rz, 2);

                if(distancia <=1){

                    putVoxel(xcenter, y, z);
                }

            }
         }

    }else if(ry == 0){

        for(int z=0; z<=nz; z++){
            for(int x=0; x<=nx; x++){

                distancia = pow(x - xcenter, 2)/pow(rx, 2) + pow(z - zcenter, 2)/pow(rz, 2);

                if(distancia <=1){

                    putVoxel(x, ycenter, z);
                }

            }
         }

    }else if(rz == 0){

        for(int x=0; x<=nx; x++){
            for(int y=0; x<=ny; y++){

                distancia = pow(x - xcenter, 2)/pow(rx, 2) + pow(y - ycenter, 2)/pow(ry, 2);

                if(distancia <=1){

                    putVoxel(x, y, zcenter);
                }

            }
         }

    }else{

        for(int z=0; z<=nz; z++){
            for(int y=0; y<=ny; y++){
                for(int x=0; x<=ny; x++){

                    distancia = pow(x - xcenter, 2)/pow(rx, 2) + pow(y - ycenter, 2)/pow(rz, 2) + pow(z - zcenter, 2)/pow(rz, 2);
                    if(distancia <= 1){

                        putVoxel(x, y, z);

                    }
                }
            }
        }
    }

}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

    double distancia;

    if(rx == 0){
        for(int z=0; z<=nz; z++){
            for(int y=0; y<=ny; y++){

                distancia = pow(y - ycenter, 2)/pow(ry, 2) + pow(z - zcenter, 2)/pow(rz, 2);

                if(distancia <=1){

                    cutVoxel(xcenter, y, z);
                }

            }
         }

    }else if(ry == 0){

        for(int z=0; z<=nz; z++){
            for(int x=0; x<=nx; x++){

                distancia = pow(x - xcenter, 2)/pow(rx, 2) + pow(z - zcenter, 2)/pow(rz, 2);

                if(distancia <=1){

                    cutVoxel(x, ycenter, z);
                }

            }
         }

    }else if(rz == 0){

        for(int x=0; x<=nx; x++){
            for(int y=0; x<=ny; y++){

                distancia = pow(x - xcenter, 2)/pow(rx, 2) + pow(y - ycenter, 2)/pow(ry, 2);

                if(distancia <=1){

                    cutVoxel(x, y, zcenter);
                }

            }
         }

    }else{

        for(int z=0; z<=nz; z++){
            for(int x=0; x<=nx; x++){
                for(int y=0; y<=ny; y++){

                    distancia = pow(x - xcenter, 2)/pow(rx, 2) + pow(y - ycenter, 2)/pow(rz, 2) + pow(z - zcenter, 2)/pow(rz, 2);
                    if(distancia <= 1){

                        cutVoxel(x, y, z);

                    }
                }
            }
        }
    }

}


void Sculptor::writeOFF(char* filename){
    ofstream fout;

    fixed(fout);
    int Nvertices=0;
    int Nfaces=0;
    int aux=0;
    fout.open(filename);

    if(fout.is_open()){
        cout << "Salvando o arquivo OFF.\n";
    }
    else{
        cout << "Arquivo nao foi aberto\n";
        exit(1);
    }

    fout<<"OFF"<<endl;

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].isOn){
                    Nvertices=Nvertices+8;
                    Nfaces=Nfaces+6;
                }
            }
        }
    }

    fout<<Nvertices<<" "<<Nfaces<<" "<<0<<endl;


    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].isOn){


                        fout<<i-0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout<<i-0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout<<i+0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout<<i+0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout<<i-0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                        fout<<i-0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout<<i+0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout<<i+0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;

                }
            }
        }
    }

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].isOn){
                    fout<<4<<" "<<aux+0<<" "<<aux+3<<" "<<aux+2<<" "<<aux+1<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+4<<" "<<aux+5<<" "<<aux+6<<" "<<aux+7<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+0<<" "<<aux+1<<" "<<aux+5<<" "<<aux+4<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+0<<" "<<aux+4<<" "<<aux+7<<" "<<aux+3<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+3<<" "<<aux+7<<" "<<aux+6<<" "<<aux+2<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    fout<<4<<" "<<aux+1<<" "<<aux+2<<" "<<aux+6<<" "<<aux+5<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                    aux=aux+8;
                }
            }
        }
    }

    if(fout.is_open()){
        cout << "Salvo com sucesso!"<<endl;
    }

}
//.
