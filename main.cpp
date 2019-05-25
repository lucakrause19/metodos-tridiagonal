#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class matrixes
{
private:

  vector<int> a;
  vector<int> v;

public:
  /// Construtor default
  inline matrixes(): a(), v() {}

  /// Funcoes de consulta
  int getElementA (unsigned i, unsigned j) const;
  int getElementV (unsigned i) const;
  inline unsigned long size() const {return v.size();}

  /// Funcoes gerais
  void setLimits(int N);
};

int matrixes::getElementV (unsigned i) const
{
    return v[i];
}
int matrixes::getElementA(unsigned i, unsigned j) const{

    if (abs(i - j) == 0){
        return a[0];
    }
    if (abs(i - j) == 1){
        return a[1];
    }
    if (abs(i - j) > 1){
        return a[2];
    }
  }

void matrixes::setLimits(int N){

    a.push_back(4);
    a.push_back(-1);
    a.push_back(0);
    v.resize(N);
    srand(time(NULL));
        for (unsigned i = 0; i < N; i++){
        int aux = rand() % 2;
        if (aux == 0){
            v.push_back(1);
        }
        else if (aux == 1){
            v.push_back(-1);
        }
    }
  }


class vectorB
{
private:

  matrixes AV;
  vector<int> b;
  void generateB(unsigned N);

public:
  /// Construtores
  inline vectorB(): b(), AV() {}
  void generateB(unsigned N);

  /// Funcoes de consulta
  inline unsigned long size() const {return b.size();}
  int getElementB (unsigned i) const;

  /// Funcoes gerais
  ostream &print(ostream &O) const;
  void save(const char* fil) const;
};

int vectorB::getElementB (unsigned i) const
{
    return b[i];
}

void vectorB::generateB(unsigned N){

    if (N < 3){
    cerr << "Erro" << endl;
    }
    else {
        AV.setLimits(N);
        b.resize(N);
        for (unsigned i = 0; i < N; i++){
            for (unsigned j = 0; j < N; i++){
                b[i] += AV.getElementA(i,j)*AV.getElementV(j);
            }
        }
    }
}

ostream& vectorB::print(ostream &O) const{

    O << "Matriz A" << endl;
    for (unsigned i = 0; i < AV.size(); i++){
        for (unsigned j = 0; j < AV.size(); j++){
        O << AV.getElementA(i,j) << " ";
    }
    O << endl;
}
    O << endl;
    O << "Vetor V" << endl;
    for (unsigned k = 0; k < AV.size(); k++){
        O << AV.getElementV(k) << endl;
    }
    O << endl;
    O << "Vetor B" << endl;
    for (unsigned m = 0; m < AV.size(); m++){
        O << getElementB(m) << endl;
    }
    return O;

}

void vectorB::save(const char* fil) const{

    ofstream file(fil);
    if (file.is_open());
    {
        print(file);
    }
    file.close();
}


using namespace std;

int main()
{
    vectorB prov;
    int n = 5;
    prov.generateB(n);
    prov.save("paulomotta.txt");
}
