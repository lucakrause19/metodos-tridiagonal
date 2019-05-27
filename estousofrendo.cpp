#include <iostream>
#include <cmath>]
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>

using namespace std;

int elemento(int i,int j);
void calcS(float v[], float b[], int n);
void gerarV(float v[], int n);
void print(float v[], float b[], int n);
void printS(float s[], int n);
float error(float s[], float result[], int n);
ostream &imprimir(ostream &O, float v[], float b[], int n);
void salvar(const char* arq, float v[], float b[], int n) ;
void jacobi(float b[], float v[], float s[], int n, int it, float erro);
#define TAM 4
int main()
{
   float b[TAM] = {0,0,0,0};
  //  float v[TAM] = {-1,1,-1,-1,-1,-1,1,-1};  // vetor  usado no exemplo do projeto
  float v[TAM];
  float s[TAM] = {0,0,0,0};
    srand(time(NULL));
    gerarV(v,TAM);
    calcS(v,b,TAM);
    print(v,b,TAM);
    salvar("paulomotta.txt",v,b,TAM);
    jacobi(b,v,s,TAM,1000,0.05);

    return 0;
}

int elemento(int i, int j){
    if(i == j) return 4;
    else if(abs(i-j) == 1) return -1;
    else return 0;
}

void calcS(float v[], float b[], int n)
{

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            b[i] += elemento(i,j) * v[j];
        }

    }
}

float error(float s[], float result[], int n)
{
    float prov;
    float max_r = 0.0;
    float max_s = 0.0;
    float prov1[n];
    float prov2[n];
    for(int i=0;i<n;i++)
    {
        prov1[i] = abs(result[i]);
        prov2[i] = abs(s[i]);
    }
    for(int j=0;j<n;j++)
    {
        if (prov1[j]> max_r) max_r = prov1[j];
        if (prov2[j]> max_s) max_s = prov2[j];
    }

    prov = (max_r - max_s)/max_r;
    return prov;
}

void jacobi(float b[], float v[], float s[], int n, int it, float erro)
{
    if (erro > 1) cerr << "Errou rude" << endl;
    else{
    float soma = 0.0;
    float result [TAM];
    for(int k = 0; k<it; k++)
    {
        soma = 0.0;
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                if(j != i) soma += elemento(i,j)*s[j];
            }
            result[i] = (b[i] - soma)/elemento(i,i);
        }
        if (error(result, s, n) < erro){
            cout << "Solução encontrada na iteração: " << it << endl;
            printS(result, n);
        }
        else{
            for (int m=0;m<n;m++){
                s[m] = result[m];
        }
        }
        }
    }
}



void gerarV(float v[], int n){
    int a;

    for(int i = 0; i<n; i++){
        a = rand()%2;
        if(a == 0) v[i] = 1;
        else v[i] = -1;
    }

}

void printS(float s[], int n)
{
    cout << endl  << "{" ;
    for(int i =0 ; i<n;i++){
    cout << s[i] << " ";
}
    cout << "}" << endl;

}

void print(float v[], float b[], int n){

    cout << "Matriz A" << endl;
for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
    int prov = elemento(i,j);
    cout << prov << " ";
}
    cout << endl;
}
    cout << endl << "Vetor v" << endl << "{" ;
for(int i =0 ; i<n;i++){
    cout << v[i] << " ";

}
cout << "}" << endl << endl;

cout << "Vetor b " << endl << "{";
    for(int i = 0; i<n; i++)
    {
    cout << b[i] << " ";
    }
    cout << "}" << endl << endl;


}

ostream &imprimir(ostream &O, float v[],float b[], int n)
{
     O << "Matriz A" << endl;
for (int i=0;i<n;i++){
    for (int j=0;j<n;j++){
    int prov = elemento(i,j);
    O << prov << " ";
}
    O << endl;
}
    O << endl << "Vetor v" << endl << "{" ;
for(int i =0 ; i<n;i++){
    O << v[i] << " ";

}
O << "}" << endl << endl;

O << "Vetor b " << endl << "{";
    for(int i = 0; i<n; i++)
    {
    O << b[i] << " ";
    }
    O << "}" << endl << endl;

}

void salvar(const char* arq,float v[],float b[], int n)
{
    ofstream arquivo(arq);
    if (arquivo.is_open());
    {
        imprimir(arquivo,v, b,n);
    }
    arquivo.close();
}

