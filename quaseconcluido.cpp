#include <iostream>
#include <cmath>]
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>

using namespace std;

///Obs: a sintaxe "type funcao(float x[])" indica uma função do tipo "type" que recebe como parâmetro um vetor de floats
///Obs2: a função de G-Seidel ainda não está funcionando corretamente
int elemento(int i,int j); ///Retorna o elemento correspondente no que seria a matriz A
void calcularB(float v[], float b[], int n); ///Calcula o vetor B (vetor dos resultados) fazendo o produto entre A e V
void gerarV(float v[], int n);///Gera o vetor V com números aleatórios (1 ou -1)
void imprimir(float v[], float b[], int n);///Imprime na tela a matriz A, o vetor V e o vetor B (só para tester)
void residuo(float result[], float b[], double resid[], int n);///Calcula o resíduo da iteração atual (r[k] = b - Ax[k])
double normaLinha(double resid[], int n);///Calcula norma linha de vetores (usa para achar a norma do resíduo)
bool comparar(float result[], float v[], int n);///Verifica se o resultado encontrado está de acordo com a solução esperada do sistema
void salvar(const char* arq,float b[], float v[], float s_inicial[], int n, int it);///Salva em arquivo na pasta em que está o programa
ostream &jacobi(ostream &O, float b[], float v[], float s_inicial[], int n, int it);///Resolve por Jacobi e salva o resultado numa ostream (variável de fluxo de dados)
ostream &gseidel(ostream &O, float b[], float v[], float s_inicial[], int n, int it);///Resolve por G-Seidel e salva o resultado numa ostream (variável de fluxo de dados)

#define TAM 10 ///Seta o tamanho das matrizes e vetores como 10

int main()
{
  float b[TAM];
  float v[TAM];
  float s_inicial[TAM];
  double resid[TAM];
  ///Todos vetores serão criados com o tamanho pre-definido

    gerarV(v,TAM);
    calcularB(v,b,TAM);
    ///imprimir(v,b,TAM);
    salvar("teste.txt",b,v,s_inicial,TAM,100);

    return 0;
}

int elemento(int i, int j){
    if(i == j) return 4;
    else if(abs(i-j) == 1) return -1;
    else return 0;
}

void gerarV(float v[], int n){
    int a;
    srand(time(NULL));
    for(int i = 0; i<n; i++){
        a = rand()%2;
        if(a == 0) v[i] = 1;
        else v[i] = -1;
    }
}

void calcularB(float v[], float b[], int n)
{
    for(int i = 0; i<n; i++)
    {
        b[i] = 0.0;
        for(int j = 0; j<n; j++)
        {
            b[i] += elemento(i,j) * v[j];
        }
    }
}

void imprimir(float v[], float b[], int n){

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

void residuo(float result[], float b[],double resid[], int n)
{
    float maximo = 0.0;

    for(int i=0;i<n;i++){
        resid[i] = b[i];
        for(int j=0;j<n;j++){
        resid[i] = resid[i] - (elemento(i,j)*result[j]);
        }
    }
    return;
}

double normaLinha(double resid[], int n)
{
    double prov_max = 0.0;
    for (int i=0;i<n;i++){
        resid[i] = abs(resid[i]);
    }
    for (int j=0;j<n;j++){
        if (resid[j]>prov_max) prov_max = resid[j];
    }
    return prov_max;
}

bool comparar(float result[], float v[], int n){

    for (int i=0;i<n;i++){
        if (result[i] = v[i]) return true;
        else return false;
    }
}

ostream &jacobi(ostream &O, float b[], float v[], float s_inicial[], int n, int it)
{
    for (int m=0;m<n;m++) s_inicial[m] = 0.0;
    float soma = 0.0;
    float result [n];
    double resid [n];
    double prov;
    O << "Tamanho da matriz: " << n << "x" << n << endl;
    O << "Método de Jacobi" << endl << endl;

    for(int k = 0; k<it; k++)
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                if(j != i) soma += elemento(i,j)*s_inicial[j];
            }
            result[i] = (b[i] - soma)/elemento(i,i);
        soma = 0.0;
        }
        for (int y=0;y<n;y++) s_inicial[y] = result[y];

    residuo(result,b, resid, n);
    prov = normaLinha(resid, n);
    O << k+1 <<": " << prov << endl;
    }
    if (comparar(result,v,n)) O << endl << "O resultado confere com o esperado." << endl;
}

ostream &gseidel(ostream &O, float b[], float v[], float s_inicial[], int n, int it)
{
    for (int m=0;m<n;m++) s_inicial[m] = 0.0;
    float soma = 0.0;
    float result [n];
    double resid [n];
    double prov;
    O << endl << "Método de Gauss-Seidel" << endl << endl;
    for(int k = 0; k<it; k++){
        for (int i = 0; i < n; i++){
            result[i] = (b[i] /elemento(i,i));
            for (int j = 0; j < n; j++){
                if (j == i) continue;
                result[i] = result[i] - ((elemento(i,j)/elemento(i,i))*s_inicial[j]);
                s_inicial[i] = result[i];
            }
      }
    residuo(result,b, resid, n);
    prov = normaLinha(resid, n);
    O << k+1 <<": " << prov << endl;
}
    if (comparar(result,v,n)) O << endl << "O resultado confere com o esperado." << endl;
}


void salvar(const char* arq,float b[], float v[], float s_inicial[], int n, int it)
{
    ofstream arquivo(arq);
    if (arquivo.is_open());
    {
        jacobi(arquivo,b,v,s_inicial,n,it);
        gseidel(arquivo,b,v,s_inicial,n,it);
    }
    arquivo.close();
}
