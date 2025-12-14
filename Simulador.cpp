#include "Simulador.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "plantas/ErvaDaninha.h"
#include "plantas/Cacto.h"
#include "plantas/Roseira.h"
#include "ferramentas/Regador.h"
#include "ferramentas/Adubo.h"
#include "ferramentas/Tesoura.h"
using namespace std;

Simulador::Simulador() :jardim(nullptr),jardineiro(nullptr),running(true) {
    jardineiro = new Jardineiro();
}

Simulador::~Simulador()
{
    delete jardim;
    delete jardineiro;
    for (auto par : saves) {
        delete par.second;
    }
    saves.clear();
}

void Simulador::iniciar()
{
    string linha;
    while (running)
    {
        cout << "> ";
        if (!getline(cin, linha)) {
            break;
        }
        if (linha.empty()) {
            continue;
        }
        processarComando(linha);
    }
}

void Simulador::processarComando(const string& linha)
{
    stringstream ss(linha);
    string comando;
    ss >> comando;

    if (jardim==nullptr && comando!="jardim" && comando!="executa" && comando!="fim")
    {
        cout << "ERRO: O jardim ainda nao foi criado. Use o comando 'jardim <l> <c>'" << endl;
        return;
    }
    if (comando == "jardim") {cmdJardim(ss);}
    else if (comando == "avanca") {cmdAvanca(ss);}
    else if (comando == "planta") {cmdPlanta(ss);}
    else if (comando=="move") {string direcao; ss >> direcao; cmdMove(direcao);}
    else if (comando == "lplantas") {cmdLplantas(ss);}
    else if (comando == "lplanta") {cmdLplanta(ss);}
    else if (comando == "larea") {cmdLarea(ss);}
    else if (comando == "lsolo") {cmdLsolo(ss);}
    else if (comando == "lferr") {cmdLferr(ss);}
    else if (comando == "colhe") {cmdColhe(ss);}
    else if (comando == "larga") {cmdLarga(ss);}
    else if (comando == "pega") {cmdPega(ss);}
    else if (comando == "usa") {
        int index;
        if (ss >> index) {
            cmdUsar(index);
        }else {
            cout << "Indica o numero da ferramenta (ex: usa 0)" << endl;
        }
    }
    else if (comando == "compra") {cmdCompra(ss);}
    else if (comando == "e" || comando == "d" || comando == "c" || comando == "b")
    {
        if (!validarLixo(ss)) return;
        cmdMove(comando);
    }
    else if (comando == "entra") {cmdEntra(ss);}
    else if (comando == "sai") {cmdSai(ss);}
    else if (comando == "grava") {cmdGrava(ss);}
    else if (comando == "recupera") {cmdRecupera(ss);}
    else if (comando == "apaga") {cmdApaga(ss);}
    else if (comando == "executa") {cmdExecuta(ss);}
    else if (comando == "fim")
    {
        running = false;
        cout << "A terminar o simulador..." << endl;
    } else {
        cout << "ERRO: Comando '" << comando << "' desconhecido." << endl;
    }
}

bool Simulador::validarPosicao(const std::string& pos)
{
    if (pos.length() != 2 || !islower(pos[0]) || !islower(pos[1])) {
        cout << "ERRO: Posicao invalida. Formato esperado: <l><c> (ex: 'ce')." << endl;
        return false;
    }
    return true;
}

bool Simulador::validarLixo(std::stringstream& ss)
{
    string lixo;
    if (ss >> lixo) {
        cout << "ERRO: Parametros a mais no comando (a comecar por '" << lixo << "')." << endl;
        return false;
    }
    return true;
}

void Simulador::cmdJardim(stringstream& ss)
{
    int lin,col;
    if (ss >> lin >> col) {
        if (jardim!=nullptr) {
            cout << "O jardim ja existe.  Faz 'jardim' para desenha lo " << endl;
        } else {
            jardim = new Jardim(lin,col);
            cout << "Jardim de " <<lin <<"x"<<col<<" criado com sucesso"<<endl;
            jardim->desenhar(jardineiro);
        }
    }else {
        if (jardim!=nullptr) {
            jardim->desenhar(jardineiro);
        }else {
            cout << "Jardim ainda nao foi criado , tens de criar um primeiro" << endl;
        }
    }
}
void Simulador::cmdAvanca(stringstream &ss)
{
    int n=1;
    ss>>n;

    if (jardim==nullptr)
    {
        cout <<"Cria o jardim primeiro." << endl;
        return;
    }
    for (int i=0;i<n;i++) {
        jardim->passarTempo();
    }
    cout << "O tempo avancou " << n << " instantes" << endl;
    jardim->desenhar(jardineiro);
}

void Simulador::cmdPlanta(stringstream& ss)
{
    string pos;
    char tipo;
    if (!(ss >> pos >> tipo)) {
        cout << "ERRO: Sintaxe invalida. Uso: planta <lc> <tipo>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    if (!validarPosicao(pos)) return;

    int l=pos[0] - 'a';
    int c=pos[1] - 'a';

    Planta* novaPlanta =nullptr;

    switch (tipo) {
        case 'c':
            novaPlanta = new Cacto();
            break;
        case 'r':
            novaPlanta = new Roseira();
            break;
        case 'e':
            novaPlanta = new ErvaDaninha();
            break;
        default:
            cout << "Tipo de planta desconhecida" << endl;
            return;
    }

    if (jardim->adicionarPlanta(l, c, novaPlanta)) {
        cout << "Planta criada com sucesso!" << endl;
        jardim->desenhar(jardineiro);
    } else {
        cout << "ERRO: Posicao ocupada." << endl;
        delete novaPlanta;
    }
}

void Simulador::cmdLplantas(stringstream &ss)
{
    if (!validarLixo(ss)) return;
    cout << "Comando 'lplantas' validado." << endl;
}

void Simulador::cmdLplanta(stringstream &ss)
{
    string pos;
    if (!(ss>>pos)) {
        cout << "ERRO: Sintaxe invalida. Uso: lplanta <lc>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    if (!validarPosicao(pos)) return;
    int l = pos[0] - 'a';
    int c = pos[1] - 'a';

    if (jardim==nullptr) return;
    Posicao* p =jardim->getPosicao(l,c);
    if (p!=nullptr) {
        if (p->temPlanta()) {
            Planta* planta = p->getPlanta();
            cout << "Planta na posicao" << pos << endl;
            cout << "Tipo: " << planta->getChar() << endl;
            cout << "Idade: " << planta->getIdade() << endl;
            cout << "Agua interna: " << planta->getAgua() << endl;
            cout << "Nutrientes internos: " << planta->getNutrientes() << endl;
            if (planta->feia()) {
                cout << "Planta feia" << endl;
            }else {
                cout << "Planta Bonita" << endl;
            }
        }else {
            cout << "Nao existe nenhuma planta na posicao " << pos << endl;
        }
    }
}
void Simulador::cmdLarea(stringstream &ss) {
    if (!validarLixo(ss)) return;
    cout << "Comando 'larea' validado." << endl;
}
void Simulador::cmdLsolo(stringstream &ss)
{
    string pos;
    int n=0;
    if (!(ss >> pos)) {
        cout << "ERRO: Sintaxe invalida. Uso: lsolo <lc> [n]" << endl;
        return;
    }
    ss>>n;
    if (ss.fail() && !ss.eof()) {
        cout << "ERRO: 'n' (raio) deve ser um numero" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    if (!validarPosicao(pos)) return;
    cout << "Comando 'lsolo" <<pos <<" " << (n>0 ? n:0) << "' validado" <<endl;
}
void Simulador::cmdLferr(stringstream &ss)
{
    if (!validarLixo(ss)) return;
    if (jardineiro==nullptr) return;
    int tot=jardineiro->getNumFerramentas();
    cout << "A Mochila do Jardineiro tem " << tot<< " ferramentas"<< endl;

    for (int i=0;i<tot;i++) {
        Ferramenta* f=jardineiro->getFerramenta(i);
        if (f!=nullptr) {
            cout << i <<"Tipo="<< f->getChar() << " e Quantidade=" << f->getQuantidade() << endl;
        }
    }
}

void Simulador::cmdColhe(stringstream &ss)
{
    string pos;
    ss>>pos;

    if (pos.length()<2) return;
    int l=pos[0] - 'a';
    int c=pos[1] - 'a';

    if (jardineiro->getColheitas() >= Jardineiro::MAX_COLHEITAS) {
        cout << "Limite de colheitas atingidas neste turno." << endl;
        return;
    }
    Posicao* p=jardim->getPosicao(l,c);
    if (p!=nullptr && p->temPlanta()) {
        Planta* planta = p->getPlanta();
        int valor= planta->getPreco();
        jardineiro->receberDinheiro(valor);
        p->removerPlanta();
        jardineiro->registarColheitas();
        cout << "colheste a planta. Ganhaste " << valor << " euros" <<endl;
    }else {
        cout << "Nao ha nenhuma planta ai" << endl;
    }
}
void Simulador::cmdLarga(stringstream &ss)
{
    if (!validarLixo(ss)) return;
    cout <<"Comando 'larga' validado." << endl;
}
void Simulador::cmdPega(stringstream &ss) {
    int n;
    if (!(ss >> n) || n <=0) {
        cout << "ERRO: Sintaxe invalida. Uso pega <n>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    cout << "Comando 'pega" <<n<<"' validado." << endl;
}

void Simulador::cmdCompra(stringstream &ss)
{
    char tipo;
    if (!(ss >> tipo)) {
        cout << "Sintaxe invalida. Usa: compra <c>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    Ferramenta* f = nullptr;
    int custo=0;
    if (tipo == 'g')
    {
        custo = Regador::custo;
        f=new Regador();
        cout << "Compraste um regador" << endl;
    }else if (tipo == 'a') {
        custo = Adubo::custo;
        f=new Adubo();
        cout << "Compraste um saco deadubo" << endl;
    }else if (tipo=='t') {
        custo = Tesoura::custo;
        f=new Tesoura();
        cout << "Compraste um tesoura" << endl;
    }else {
        cout << "Essa ferramenta nao existe" << endl;
        return;
    }

   if (f!=nullptr) {
       if (jardineiro->getDinheiro()>=custo) {
           jardineiro->gastarDinheiro(custo);
           jardineiro->apanharFerramenta(f);
           cout << "Compraste esta ferramenta por "<<custo<< ". Saldo: "<<jardineiro->getDinheiro() << endl;
       }else {
           cout <<"Dinheiro insuficiente , tens " <<jardineiro->getDinheiro() << "mas custa " << custo << endl;
           delete f;
       }
   }

}
void Simulador::cmdMove(const string &direcao)
{
    if (jardim==nullptr) {
        cout <<"ERRO: Nenhum jardim criado." << endl;
        return;
    }
    if (jardineiro->getMov() >= Jardineiro::MAX_MOV) {
        cout << "O jardineiro esta cansado (Max " <<Jardineiro::MAX_MOV << " movimentos). Faz 'avanca'." <<endl;
        return;
    }

    int l = jardineiro->getLinha();
    int c = jardineiro->getColuna();

    if (direcao=="cima") {
        l--;
    }else if (direcao=="baixo") {
        l++;
    }else if (direcao=="esquerda") {
        c--;
    }else if (direcao=="direita") {
        c++;
    }else {
        cout << "Direcao invalida , tem de ser um destes 'cima' , 'baixo' , 'esquerda' , 'direita' " << endl;
        return;
    }

    if (l>=0 && l < jardim->getLinhas() && c >= 0 && c < jardim->getColunas()) {
        jardineiro->setPosicao(l,c);
        jardineiro->registarMov();
        cout << "Movimentos fietos. " <<jardineiro->getMov() << endl;
        cout << "Jardineiro foi para a " << l <<" "  << c << endl;
        jardim->desenhar(jardineiro);
    }else {
        cout << "Nao e possivel mover para ai" << endl;
    }
}
void Simulador::cmdEntra(stringstream &ss) {
    string pos;
    if (!(ss >> pos)) {
        cout << "ERRO: Sintaxe invalida. Uso: entra <lc>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    if (!validarPosicao(pos)) return;
    cout << "Comando 'entra" <<pos <<"'validado." << endl;
}
void Simulador::cmdSai(stringstream &ss) {
    if (!validarLixo(ss)) return;
    cout << "Comando 'sai' validado" << endl;
}
void Simulador::cmdGrava(stringstream &ss) {
    string nome;
    ss>>nome;

    if (jardim==nullptr) {
        cout <<"Nao ha jardim nenhum para gravar" <<endl;
        return;
    }
    if (saves.count(nome)) {
        delete saves[nome];
        saves.erase(nome);
    }
    saves[nome] = new Jardim(*jardim);
    cout<<"Jardim gravado com o nome '" << nome << "' " <<endl;
}
void Simulador::cmdRecupera(stringstream &ss) {
    string nome;
    ss>>nome;

    if (saves.find(nome)== saves.end()) {
        cout << "Save '" <<nome<< "' nao encontrado" << endl;
        return;
    }
    if (jardim!=nullptr) {
        delete jardim;
    }
    jardim = new Jardim(*saves[nome]);
    cout << "Jardim recuperado com o nome de '" <<nome<<"' " <<endl;
    jardim->desenhar(jardineiro);
}
void Simulador::cmdApaga(stringstream &ss) {
    string nome;
    if (!(ss >> nome)) {
        cout << "ERRO: Sintaxe invalida. Uso:apaga <nome>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    cout << "Comando 'apaga'" << nome <<"'validado." << endl;
}
void Simulador::cmdExecuta(stringstream &ss) {
    string nomeFicheiro;
    if (!(ss >> nomeFicheiro)) {
        cout << "ERRO: Sintaxe invalida. Uso:executa <nome-do-ficheiro>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    cout << "A executar comandos do ficheiro: "<<nomeFicheiro<<endl;
    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'" << endl;
        return;
    }

    string linha;
    while (getline(ficheiro,linha)) {
        if (linha.empty()) continue;
        cout << ">" << linha << endl;
        processarComando(linha);
        if (!running) break;
    }
    ficheiro.close();
    cout << "Fim da execucao do ficheiro" << endl;
}

void Simulador::cmdUsar(int index) {
    if (jardineiro==nullptr || jardim == nullptr) return;

    Ferramenta* f = jardineiro->getFerramenta(index);

    if (f==nullptr) {
        cout << "Nao tens nenhuma ferramenta no bolso " << index << "." << endl;
        return;
    }

    int l=jardineiro->getLinha();
    int c=jardineiro->getColuna();

    Posicao* p=jardim->getPosicao(l,c);

    if (p!=nullptr) {
        bool suc=f->usar(p);
        if (suc) {
            cout << "Usaste a ferramenta" << endl;
        }else {
            cout << "nao foi possivel usar a ferramenta" << endl;
        }
    }
}











