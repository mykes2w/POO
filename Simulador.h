#ifndef TRABALHOPOO_SIMULADOR_H
#define TRABALHOPOO_SIMULADOR_H
#include "mundo/Jardim.h"
#include <sstream>
#include <string>

#include "Jardineiro.h"
using namespace std;


class Simulador {
    Jardim* jardim;
    Jardineiro* jardineiro;
    bool running;

private:
    bool validarPosicao(const string & pos);
    bool validarLixo(stringstream& ss);

    void processarComando(const string& linha);

    void cmdJardim(stringstream& ss);
    void cmdAvanca(stringstream& ss);
    void cmdPlanta(stringstream& ss);

    void cmdLplantas(stringstream& ss);
    void cmdLplanta(stringstream& ss);
    void cmdLarea(stringstream& ss);
    void cmdLsolo(stringstream& ss);
    void cmdLferr(stringstream& ss);

    void cmdColhe(stringstream& ss);
    void cmdLarga(stringstream& ss);
    void cmdPega(stringstream& ss);
    void cmdCompra(stringstream& ss);
    void cmdUsar(int index);

    void cmdMove(const string& direcao);
    void cmdEntra(stringstream& ss);
    void cmdSai(stringstream& ss);

    void cmdGrava(stringstream& ss);
    void cmdRecupera(stringstream& ss);
    void cmdApaga(stringstream& ss);
    void cmdExecuta(stringstream& ss);


public:
    Simulador();
    ~Simulador();
    void iniciar();
};


#endif //TRABALHOPOO_SIMULADOR_H