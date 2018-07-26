#ifndef MAX_H
#define MAX_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>

#define INFINITO 1000000

#define HASHT INFINITO

using namespace std;

typedef uint32_t inteiro32;

typedef struct no {
    string id;
    int tipo, omega, excesso_fluxo, altura;
    struct no * next;
} No;

typedef struct vertex {
    int quantity;
    No * head;
} Vertex;

typedef struct aresta {
    int fluxo, capacidade;
    string source, target;
} Aresta;

vector<Vertex*> hash_table(HASHT);
vector<Aresta> arestas;

set<string> setArestas;

int nvertex;
int ler_arquivo;


void aloca_vertice(string code, int tipo, int limite);
void aloca_aresta(string source, string target, int fluxo, int capacidade);
string gasin(int tam, string line);
void inicializa_hash();

string id(int tam, string line, int ini);

int digito(int tam, string line, int ini);


void remove_ruidos();
int cria_grafo(string base);
void add_grafico();

string overfluxo();
void inicializa_refluxo(int pj_global);
void atualiza_aresta(int i, int fluxo);

int solve_max_fluxo();
void relabel(string vertex_id);
int push(string vertex_id);
int push_relabel(int pj_global);

#endif // MAX_H

