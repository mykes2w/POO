#include "Simulador.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "PlantaExotica.h"
#include "plantas/ErvaDaninha.h"
#include "plantas/Cacto.h"
#include "plantas/Roseira.h"
#include "ferramentas/Regador.h"
#include "ferramentas/Adubo.h"
#include "ferramentas/Tesoura.h"
#include "ferramentas/FerramentaZ.h"
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
        cout << "O jardim ainda nao foi criado. Use o comando 'jardim <l> <c>'" << endl;
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
        cout << "A terminar o simulador" << endl;
    } else {
        cout << "Comando '" << comando << "' desconhecido." << endl;
    }
}

bool Simulador::validarPosicao(const std::string& pos)
{
    if (pos.length() != 2 || !islower(pos[0]) || !islower(pos[1])) {
        cout << "Posicao invalida. Formato esperado: <l><c> (ex: 'ce')." << endl;
        return false;
    }
    return true;
}

bool Simulador::validarLixo(std::stringstream& ss)
{
    string lixo;
    if (ss >> lixo) {
        cout << "Parametros a mais no comando (a comecar por '" << lixo << "')." << endl;
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
        }
        if (lin < 1 || lin > 26 || col < 1 || col > 26) {
            cout << "As dimensoes devem estar entre 1x1 e 26x26." << endl;
            return;
        }
        jardim = new Jardim(lin, col);
        cout << "Jardim de " << lin << "x" << col << " criado com sucesso" << endl;
        jardim->desenhar(jardineiro);
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
    if (jardim == nullptr) {
        cout << "O jardim ainda nao foi criado." << endl;
        return;
    }
    int n=1;
    if (!(ss >> n)) {
        n = 1;
    }
    if (n <= 0) {
        cout << "Indique um numero de instantes positivo." << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        jardim->passarTempo();

        if (jardineiro->dentroJardim()) {
            Ferramenta* naMao = jardineiro->getFerramentaMao();
            if (naMao != nullptr) {
                Posicao* p = jardim->getPosicao(jardineiro->getLinha(), jardineiro->getColuna());

                if (naMao->usar(p)) {
                    cout << "Ferramenta " << naMao->getChar() << " foi utilizada automaticamente na posicao (" << (char)('a' + jardineiro->getLinha()) << (char)('a' + jardineiro->getColuna()) << ")" << endl;

                    if ((naMao->getChar() == 'g' || naMao->getChar() == 'a') && naMao->getQuantidade() <= 0) {
                        cout << "A ferramenta na mao esgotou-se e foi descartada!" << endl;
                        jardineiro->removerFerrGasta(naMao);
                    }
                }
            }
        }

        jardineiro->prepNovoTurno();
    }

    cout << "Avancaram " << n << " instante(s)." << endl;

    jardim->desenhar(jardineiro);
}

void Simulador::cmdPlanta(stringstream& ss)
{
    string pos;
    char tipo;
    if (!jardineiro->dentroJardim()) {
        cout << "Tens de entrar no jardim primeiro" << endl;
        return;
    }
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
        case 'x':
            novaPlanta = new PlantaExotica();
            break;
        default:
            cout << "Tipo de planta desconhecida" << endl;
            return;
    }

    if (jardineiro->getPlantacoes() >= Jardineiro::MAX_PLANTACOES) {
        cout << "Limite de plantacoes atingido (Max: " << Jardineiro::MAX_PLANTACOES << ")" << endl;
        return;
    }
    if (jardim->adicionarPlanta(l, c, novaPlanta)) {
        jardineiro->registarPlantacoes();
        cout << "Planta criada com sucesso!" << endl;
        jardim->desenhar(jardineiro);
    } else {
        cout << "Posicao ocupada." << endl;
        delete novaPlanta;
    }
}

void Simulador::cmdLplantas(stringstream &ss)
{
    if (jardim == nullptr) return;
    cout << "Lista de Plantas que estao no Jardim" << endl;
    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {
            Posicao* p = jardim->getPosicao(i, j);
            if (p->temPlanta()) {
                Planta* pl = p->getPlanta();
                cout << "[" << (char)('a'+i) << (char)('a'+j) << "] "
                     << "Tipo: " << pl->getChar() << " | Idade: " << pl->getIdade() << endl;
            }
        }
    }
}

void Simulador::cmdLplanta(stringstream &ss)
{
    string pos;
    if (!(ss>>pos)) {
        cout << "Sintaxe invalida. Uso: lplanta <lc>" << endl;
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
    if (jardim == nullptr) return;
    if (!validarLixo(ss)) return;

    cout << "Listagem da Area" << endl;
    bool encontrou = false;

    for (int i = 0; i < jardim->getLinhas(); i++) {
        for (int j = 0; j < jardim->getColunas(); j++) {
            Posicao* p = jardim->getPosicao(i, j);

            if (p->temPlanta() || p->temFerramenta()) {
                encontrou = true;
                cout << "[" << (char)('a' + i) << (char)('a' + j) << "]: ";

                if (p->temPlanta()) {
                    cout << "Planta: " << p->getPlanta()->getChar() << " ";
                }

                if (p->temFerramenta()) {
                    cout << "Ferramenta: " << p->getFerramenta()->getChar()
                         << " (ID: " << p->getFerramenta()->getId() << ") ";
                }
                cout << "| Solo (A:" << p->getAgua() << " N:" << p->getNutrientes() << ")" << endl;
            }
        }
    }

    if (!encontrou) {
        cout << "O solo do jardim esta atualmente limpo (sem plantas ou ferramentas)." << endl;
    }
}
void Simulador::cmdLsolo(stringstream &ss)
{
    string pos;
    int n=0;
    if (!(ss >> pos)) {
        cout << "Sintaxe invalida. Uso: lsolo <lc> [n]" << endl;
        return;
    }
    ss>>n;

    int l_origem = pos[0] - 'a';
    int c_origem = pos[1] - 'a';

    for (int i = l_origem - n; i <= l_origem + n; ++i) {
        for (int j = c_origem - n; j <= c_origem + n; ++j) {
            if (i >= 0 && i < jardim->getLinhas() && j >= 0 && j < jardim->getColunas()) {
                Posicao* p = jardim->getPosicao(i, j);
                cout << "Posicao [" << (char)('a'+i) << (char)('a'+j) << "]: ";
                cout << "Agua: " << p->getAgua() << " | Nutrientes: " << p->getNutrientes();
                if (p->temPlanta()) cout << " | Planta: " << p->getPlanta()->getChar();
                cout << endl;
            }
        }
    }
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
            cout << "ID: " << f->getId() << " | Tipo: " << f->getChar() << " | Carga/Quantidade: " << f->getQuantidade() << endl;
        }
    }
}

void Simulador::cmdColhe(stringstream &ss)
{
    string pos;
    ss>>pos;
    if (!jardineiro->dentroJardim()) {
        cout << "Tens de entrar no jardim primeiro" << endl;
        return;
    }
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
    if (jardineiro->getFerramentaMao()==nullptr) {
        cout << "Nao tens nada na mao para largar " << endl;
        return;
    }

    jardineiro->setFerramentaMao(nullptr);
    cout << "largaste a ferramenta, agora nao tens nada nas maos" << endl;
}
void Simulador::cmdPega(stringstream &ss) {
    int idAlvo;
    if (!(ss>>idAlvo)) {
        cout << "Indica o numero de serie. Exemplo: pega 1" << endl;
    }
    Ferramenta* f =jardineiro->procurarPorID(idAlvo);
    if (f!=nullptr) {
        jardineiro->setFerramentaMao(f);
        cout << "Agora tens a ferramenta" << idAlvo << " ["<<f->getChar()<<"] na mao " <<endl;
    }else {
        cout <<"Nao estas com nenhuma com esse ID " <<idAlvo <<endl;
    }
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
    }else if (tipo == 'z') {
        custo = FerramentaZ::custo;
        f = new FerramentaZ();
        cout << "Compraste a Ferramenta Especial Z" << endl;
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
    if (!jardineiro->dentroJardim()) {
        cout << "Tens de entrar no jardim primeiro" << endl;
        return;
    }
    if (jardim==nullptr) {
        cout <<"Nenhum jardim criado." << endl;
        return;
    }
    if (jardineiro->getMov() >= Jardineiro::MAX_MOV) {
        cout << "O jardineiro esta cansado (Max " <<Jardineiro::MAX_MOV << " movimentos). Faz 'avanca'." <<endl;
        return;
    }

    int l = jardineiro->getLinha();
    int c = jardineiro->getColuna();

    if (direcao=="c") {
        l--;
    }else if (direcao=="b") {
        l++;
    }else if (direcao=="e") {
        c--;
    }else if (direcao=="d") {
        c++;
    }else {
        cout << "Direcao invalida , tem de ser um destes 'c' , 'b' , 'e' , 'd' " << endl;
        return;
    }

    if (l>=0 && l < jardim->getLinhas() && c >= 0 && c < jardim->getColunas()) {
        jardineiro->setPosicao(l,c);
        jardineiro->registarMov();
        verificarApanharFerramenta();
        cout << "Movimentos feitos. " <<jardineiro->getMov() << endl;
        cout << "Jardineiro foi para a " << l <<" "  << c << endl;
        jardim->desenhar(jardineiro);
    }else {
        cout << "Nao e possivel mover para ai" << endl;
    }
}
void Simulador::cmdEntra(stringstream &ss) {
    if (jardim == nullptr) {
        cout << "O jardim ainda nao foi criado." << endl;
        return;
    }

    string pos;
    if (!(ss >> pos)) {
        cout << "Sintaxe: entra <lc> (ex: entra aa)" << endl;
        return;
    }

    if (jardineiro->getEntrouTurno()) {
        cout << "So podes entrar ou teletransportar-te uma vez por turno." << endl;
        return;
    }

    if (!validarPosicao(pos)) return;

    int l = pos[0] - 'a';
    int c = pos[1] - 'a';

    if (l >= 0 && l < jardim->getLinhas() && c >= 0 && c < jardim->getColunas()) {
        if (jardineiro->getEntrouTurno()) {
            cout << "So podes entrar/teletransportar uma vez por turno." << endl;
            return;
        }

        jardineiro->setPosicao(l, c);
        jardineiro->setDentro(true);
        jardineiro->setEntrouTurno(true);

        verificarApanharFerramenta();
        jardim->desenhar(jardineiro);
    } else {
        cout << "A posicao " << pos << " esta fora dos limites." << endl;
    }
}
void Simulador::cmdSai(stringstream &ss) {
    if (!jardineiro->dentroJardim()) {
        cout << "O jardineiro ja esta fora do jardim" << endl;
        return;
    }
    if (jardineiro->getSaiuTurno()) {
        cout << "O jardineiro so pode sair uma vez por turno." << endl;
        return;
    }
    jardineiro->setDentro(false);
    jardineiro->setSaiuTurno(true);
    cout << "O jardineiro saiu do jardim" << endl;
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
        jardim=nullptr;
    }
    jardim = new Jardim(*saves[nome]);
    cout << "Jardim recuperado com o nome de '" <<nome<<"' " <<endl;
    jardim->desenhar(jardineiro);
}
void Simulador::cmdApaga(stringstream &ss) {
    string nome;
    if (!(ss >> nome)) {
        cout << "Sintaxe invalida. Uso:apaga <nome>" << endl;
        return;
    }
    auto it = saves.find(nome);
    if (it != saves.end()) {
        delete it->second;
        saves.erase(it);
        cout << "Copia '" << nome << "' apagada com sucesso." << endl;
    } else {
        cout << "Nome de copia nao encontrado." << endl;
    }
}
void Simulador::cmdExecuta(stringstream &ss) {
    string nomeFicheiro;
    if (!(ss >> nomeFicheiro)) {
        cout << "Sintaxe invalida. Uso:executa <nome-do-ficheiro>" << endl;
        return;
    }
    if (!validarLixo(ss)) return;
    cout << "A executar comandos do ficheiro: "<<nomeFicheiro<<endl;
    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cout << "Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'" << endl;
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

    if (p == nullptr) {
        cout << "O jardineiro nao esta numa posicao valida para usar ferramentas." << endl;
        return;
    }

    if (f->usar(p)) {

        if ((f->getChar() == 'g' || f->getChar() == 'a') && f->getQuantidade() <= 0) {
            cout << "A ferramenta " << f->getChar() << " (ID: " << f->getId() << ") esgotou-se e o jardineiro descartou-a imediatamente!" << endl;
            jardineiro->removerFerrGasta(f);
        }

        jardim->desenhar(jardineiro);
    }
    else {
        if ((f->getChar() == 'g' || f->getChar() == 'a') && f->getQuantidade() <= 0) {
            cout << "Esta ferramenta esta vazia e sera removida do inventario." << endl;
            jardineiro->removerFerrGasta(f);
        }
    }
}

void Simulador::verificarApanharFerramenta() {
    if (jardim==nullptr || jardineiro==nullptr) return;

    Posicao* p= jardim->getPosicao(jardineiro->getLinha(),jardineiro->getColuna());

    if (p!=nullptr && p->temFerramenta()) {
        Ferramenta* f = p->retirarFerramenta();
        jardineiro->apanharFerramenta(f);

        cout << "Apanhaste automaticamente a ferramenta: " << f->getChar() << " (ID:" << f->getId() << ")" << endl;

        jardim->adicionarFerrRandom();
    }
}











