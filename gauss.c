#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//-----------------------------------------------------//
// Declaracion de funciones auxiliares                 //
//-----------------------------------------------------//

float *generatevector_empty(float *vector,int n);
float *generatevector_x(float *vector,float x0,float xf,int n);
float *generatevector_u_initial(float *vector,float *x,int n);
void MoreIterations(int n_time,float *u_new,float *u_now,float *u_last,float r,int n_points);
void copyvector(float *vectorfrom,float *vectorto,int n);
void escribirxy_txt(float *x,float *u,int n_points,int j);
void graficarGNUPLOT();
//-----------------------------------------------------//
// Declaracion de la funcion Main                      //
//-----------------------------------------------------//

int main(int argc, char **argv){
  int n_points=0,i=0;
  float delta_x=0.0,delta_t=0.0,c=0.0,r=0.0,x0=0.0,xf=0.0;   
  float*x=NULL,*u_initial=NULL,*u_new=NULL,*u_last=NULL,*u_now=NULL;
  int n_time=0,j=0,n_time_max=1000,nt=0.0;
  float alpha=0.0;
 
  //Fijar xcondiciones inciales//
  n_points=200;
  x0=-5.0;
  xf=5.0;
  nt=1000000;
  delta_t=30.0/(nt);
  delta_x=(xf-x0)/n_points;
  alpha=delta_t/(delta_x*delta_x);
  printf("%f", alpha);
 
  //Generar vectores vacios y mallocs
  u_initial=generatevector_empty(u_initial,n_points);
  u_new=generatevector_empty(u_new,n_points);
  u_last=generatevector_empty(u_last,n_points);
  x=generatevector_empty(x,n_points);
  u_now=generatevector_empty(u_now,n_points);
 
  for(j=0;j<11;j++){  
 
    n_time=10000*j;  
    // Carga el vector x usando x0 xf
    x=generatevector_x(x,x0,xf,n_points);
    u_initial=generatevector_u_initial(u_initial,x,n_points);
  
    r=alpha;
    copyvector(u_initial, u_now, n_points);
    copyvector(u_initial, u_new, n_points);
  
    MoreIterations(n_time,u_new,u_now,u_last,r,n_points);
    escribirxy_txt(x,u_now,n_points,j);
  }
   printf("Estamos en el seg %f",n_time*delta_t);
   graficarGNUPLOT();
  return 0;
}

float *generatevector_empty(float *vector,int n){
  int i=0;
  if(!(vector = malloc(sizeof(float)*n))){
    fprintf(stderr, "Problem with memory allocation");
  }
  for(i=0;i<n;i++){
    vector[i]=0.0;
  }
  return vector;
}

float *generatevector_x(float *vector,float x0,float xf,int n){
  float paso=0.0;
  int i=0;
  paso=(xf-x0)/n;
  vector[0]=x0;
  vector[n]=xf;
  for(i=1;i<n;i++){
    vector[i]=vector[i-1]+paso;
  }
  return vector;
}

float *generatevector_u_initial(float *vector,float *x,int n){
  int i=0;
  vector[0]=0.0;
  vector[n-1]=0.0;
  for(i=1;i<n-1;i++){
    vector[i]=exp(-x[i]*x[i]);
  }
  return vector;
}

void MoreIterations(int n_time,float *u_new,float *u_now,float *u_last,float r,int n_points){
  int i=0,j=0;
  for(j=0;j<n_time;j++){
    for(i=1;i<n_points-1;i++){
      u_new[i] = r*u_now[i+1] + (1.0-(2.0*r))*u_now[i] + r*u_now[i-1];
      
    }
    copyvector(u_new,u_now,n_points);
  }
}

void copyvector(float *vectorfrom,float *vectorto,int n){
  int i=0;
  for(i=0;i<n;i++){
    vectorto[i]=vectorfrom[i];
  }
}

void intToChar(int j,char indice[]){
  if(j==0){strcat(indice,"0.0");}
  if(j==1){strcat(indice,"0.3");}
  if(j==2){strcat(indice,"0.6");}
  if(j==3){strcat(indice,"0.9");}
  if(j==4){strcat(indice,"1.2");}
  if(j==5){strcat(indice,"1.5");}
  if(j==6){strcat(indice,"1.8");}
  if(j==7){strcat(indice,"2.1");}
  if(j==8){strcat(indice,"2.4");}
  if(j==9){strcat(indice,"2.7");}
  if(j==10){strcat(indice,"3.0");}
}

void escribirxy_txt(float *x,float *u,int n_points,int j){
  FILE *fileout;
  int i=0;
  char filename[26]="t";
  char indice[4]="";
  char format[5]=".txt";
 
  intToChar(j,indice);
 
  strcat(filename,indice);
  strcat(filename,format);
 
  fileout=fopen(filename,"w");
  for(i=0;i<(n_points);i++){
    // Usand el formato x u
    fprintf(fileout,"%f %f\n",x[i],u[i]);
  }
}
void  graficarGNUPLOT(){
 
  FILE *pipe = popen("gnuplot -persist","w");
 
  fprintf(pipe, "plot 't0.0.txt' ti 't0.0.txt'\n");
  fprintf(pipe, "replot 't0.3.txt' ti 't0.3.txt'\n");
  fprintf(pipe, "replot 't0.6.txt' ti 't0.6.txt'\n");
  fprintf(pipe, "replot 't0.9.txt' ti 't0.9.txt'\n");
  fprintf(pipe, "replot 't1.2.txt' ti 't1.2.txt'\n");
  fprintf(pipe, "replot 't1.5.txt' ti 't1.5.txt'\n");
  fprintf(pipe, "replot 't1.8.txt' ti 't1.8.txt'\n");
  fprintf(pipe, "replot 't2.1.txt' ti 't2.1.txt'\n");
  fprintf(pipe, "replot 't2.4.txt' ti 't2.4.txt'\n");
  fprintf(pipe, "replot 't2.7.txt' ti 't2.7.txt'\n");
  fprintf(pipe, "replot 't3.0.txt' ti 't3.0.txt \n");
  fprintf(pipe, "exit '\n");
  close(pipe);
}
