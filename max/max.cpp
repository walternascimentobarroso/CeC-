#include "max.h"

void inicializa_hash() {
    for (int i = 0; i < HASHT; i++) {
        hash_table[i] = NULL;
    }
}

inteiro32 mapj(char *chave, int len) {
    inteiro32 hash;
    int i;
    for (hash = i = 0; i < len; i++) {
        hash += chave[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

inteiro32 indexh(string chave) {
    inteiro32 hash;
    inteiro32 indice;
    int tam = chave.size();
    char nchave[tam + 1];

    strcpy(nchave, chave.c_str());
    hash = mapj(nchave, tam);
    indice = hash % HASHT;

    return indice;
}

void aloca_vertice(string code, int tipo, int limite) {
    inteiro32 i = indexh(code);

    if (hash_table[i] == NULL) {
        No *new_no = new No;
        new_no->id = code;
        new_no->tipo = tipo;
        new_no->excesso_fluxo = 0;
        new_no->altura = 0;
        new_no->next = NULL;
        if (tipo == 0) {
            new_no->omega = limite;
        } else {
            new_no->omega = 1;
        }
        hash_table[i] = new Vertex;
        hash_table[i]->head = new_no;
        hash_table[i]->quantity = 1;
        nvertex++;
    } else {
        No *new_no = new No;
        new_no->id = code;
        new_no->tipo = tipo;
        new_no->excesso_fluxo = 0;
        new_no->altura = 0;
        new_no->next = NULL;
        if (tipo == 0) {
            new_no->omega = limite;
        } else {
            new_no->omega = 1;
        }
        new_no->next = hash_table[i]->head;
        hash_table[i]->head = new_no;
        hash_table[i]->quantity++;
        nvertex++;
    }
}

void aloca_aresta(string source, string target, int fluxo, int capacidade) {
    Aresta new_aresta;
    new_aresta.fluxo = fluxo;
    new_aresta.capacidade = capacidade;
    new_aresta.source = source;
    new_aresta.target = target;
    arestas.push_back(new_aresta);
}

string gasin(int tam, string line) {
    int i;
    int pos = 0;
    string newline = line.substr(0, line.size() - 1);

    for (i = tam - 2; i > 0; i--) {
        if ((newline.at(i) < '0' || newline.at(i) > '9') &&
                (newline.at(i) < 'A' || newline.at(i) > 'Z') &&
                (newline.at(i) < 'a' || newline.at(i) > 'z')) {
            pos = i;
            break;
        }
    }

    return line.substr(pos + 1);
}

int digito(int tam, string line, int ini) {
    int i;
    int begin = -1;
    int end = 0;

    for (i = ini; i < tam; i++) {
        if ((line.at(i) >= '0' && line.at(i) <= '9')) {
            if (begin < 0) begin = i;
        } else {
            if (begin > 0) {
                end = i;
                break;
            }
        }
    }
    string tmp = line.substr(begin, end - begin);
    return atoi(tmp.c_str());
}

string id(int tam, string line, int ini) {
    int i;
    int begin = -1;
    int end = 0;

    for (i = ini; i < tam; i++) {
        if ((line.at(i) >= '0' && line.at(i) <= '9') ||
                (line.at(i) >= 'A' && line.at(i) <= 'Z') ||
                (line.at(i) >= 'a' && line.at(i) <= 'z')) {
            if (begin < 0) begin = i;
        } else {
            if (begin > 0) {
                end = i;
                break;
            }
        }
    }
    return line.substr(begin, end - begin);
}

int cria_grafo(string base) {
    ifstream dataset(base, ios::in);
    if (!dataset) {
        ler_arquivo = 0;
        return 0;
    }
    int nro_line = 1;
    int nr_reviews = 0;
    int position = 0;
    ler_arquivo = 1;
    nvertex = 0;
    string line = "";
    string pattern = "";
    string asin = "";
    string idclient = "";

    int pj_global = INFINITO;

    inicializa_hash();

    while (!dataset.eof()) {
        getline(dataset, line);

        if (nro_line > 3) {
            if (line.size() > 0) {
                if (line.find("Id:") != string::npos) {
                    pattern = "Id:";
                    position = line.find(pattern);
                } else if (line.find("ASIN:") != string::npos) {

                    asin = gasin(line.size(), line);

                } else if (line.find("reviews:") != string::npos) {
                    pattern = "reviews: total:";
                    position = line.find(pattern);
                    nr_reviews = digito(line.size(), line, position + pattern.size());
                    if (nr_reviews >= 0) {
                        aloca_vertice(asin, 0, nr_reviews);
                        if (nr_reviews < pj_global) {
                            pj_global = nr_reviews;
                        }
                    }

                } else if (line.find("discontinued") != string::npos) {
                    nro_line++;
                    continue;

                } else if (line.find("cutomer:") != string::npos) {

                    pattern = "cutomer:";
                    position = line.find(pattern);
                    idclient = id(line.size(), line, position + pattern.size());
                    aloca_vertice(idclient, 1, 0);

                    if (setArestas.insert(asin + idclient).second) {
                        aloca_aresta(idclient, asin, 1, 1);
                    }
                }
            }
        }
        nro_line++;
    }
    dataset.close();
    setArestas.clear();
    return pj_global;
}

void remove_ruidos() {
    vector<string> toremove;

    //removendo ruidos
    toremove.push_back("ATVPDKIKX0DER");
    toremove.push_back("A3UN6WX5RRO2AG");

    int i;
    int len = toremove.size();
    No * anterior;
    No * atual;
    for (i = 0; i < len; i++) {
        inteiro32 index = indexh(toremove[i]);
        if (hash_table[index]) {
            anterior = hash_table[index]->head;
            atual = hash_table[index]->head;
            while (atual) {
                if (atual->id == toremove[i]) {
                    anterior->next = atual->next;
                    hash_table[index]->quantity--;
                    nvertex--;
                    break;
                }
                anterior = atual;
                atual = atual->next;
            }
        }
    }
    toremove.clear();
}

void add_grafico() {
    int i;
    inteiro32 index;
    No * no;
    int len = arestas.size();
    for (i = 0; i < len; i++) {
        if (arestas[i].source == "source") {
            index = indexh(arestas[i].target);
            arestas[i].fluxo = arestas[i].capacidade;
            no = hash_table[index]->head;
            while (no) {
                if (no->id == arestas[i].target) {
                    no->excesso_fluxo += arestas[i].fluxo;
                    break;
                }
                no = no->next;
            }

            aloca_aresta(arestas[i].target, "source", -arestas[i].fluxo, 0);
        }
    }
}

void inicializa_refluxo(int pj_global) {
    remove_ruidos();
    aloca_vertice("source", 2, 0);
    aloca_vertice("target", 2, 0);
    No * v;
    int j = 0;
    int k = 0;
    int ci_ = 0;
    int i;
    for (i = 0; i < HASHT; i++) {
        if (hash_table[i]) {
            v = hash_table[i]->head;
            while (v) {
                if (v->tipo == 0) {
                    aloca_aresta(v->id, "target", v->omega, pj_global);
                    j++;
                } else if (v->tipo == 1) {
                    ci_ = v->omega + (v->omega * 40 / 100);
                    aloca_aresta("source", v->id, v->omega, ci_);
                    k++;
                } else if (v->tipo == 2) {
                    if (v->id == "source") {
                        v->altura = nvertex;
                    }
                }
                v = v->next;
            }
        }
    }
    add_grafico();
}

string overfluxo() {
    int i;
    No * v;
    string id = "";
    for (i = 0; i < HASHT; i++) {
        if (hash_table[i] != NULL) {
            v = hash_table[i]->head;
            while (v) {
                if ((v->id != "source") &&
                        (v->id != "target") &&
                        v->excesso_fluxo > 0) {
                    id = v->id;
                    return id;
                }
                v = v->next;
            }
        }
    }
    return id;
}

int solve_max_fluxo() {
    int i;
    int max_fluxo = 0;
    int len = arestas.size();
    for (i = 0; i < len; i++) {
        if (arestas[i].target == "target") {
            max_fluxo += arestas[i].fluxo;
        }
    }
    return max_fluxo;
}

void relabel(string vertex_id) {
    int min_altura = 1000000;
    int i;
    No * vertex;
    No * v;
    No * u;
    inteiro32 index;
    int len = arestas.size();
    for (i = 0; i < len; i++) {
        if (arestas[i].source == vertex_id) {
            if (arestas[i].fluxo == arestas[i].capacidade)
                continue;

            index = indexh(vertex_id);
            vertex = hash_table[index]->head;
            while (vertex) {
                if (vertex->id == vertex_id) {
                    u = vertex;
                    break;
                }
                vertex = vertex->next;
            }

            index = indexh(arestas[i].target);
            vertex = hash_table[index]->head;
            while (vertex) {
                if (vertex->id == arestas[i].target) {
                    v = vertex;
                    break;
                }
                vertex = vertex->next;
            }
            if (v->altura < min_altura) {
                min_altura = v->altura;
                u->altura = min_altura + 1;
            }
        }
    }
}

void atualiza_aresta(int i, int fluxo) {
    string u = arestas[i].target, v = arestas[i].source;
    int j;
    int len = arestas.size();
    for (j = 0; j < len; j++) {
        if (arestas[j].target == v && arestas[j].source == u) {
            arestas[j].fluxo -= fluxo;
            return;
        }
    }
    aloca_aresta(u, v, 0, fluxo);
}

int push(string vertex_id) {
    inteiro32 index;
    int ok = 0;
    No * vertex;
    No * u;
    No * v;
    int fluxo;
    for (int i = 0; i < arestas.size(); i++) {
        if (arestas[i].source == vertex_id) {
            if (arestas[i].fluxo == arestas[i].capacidade)
                continue;

            index = indexh(vertex_id);
            vertex = hash_table[index]->head;
            while (vertex) {
                if (vertex->id == vertex_id) {
                    u = vertex;
                    break;
                }
                vertex = vertex->next;
            }
            index = indexh(arestas[i].target);
            vertex = hash_table[index]->head;
            while (vertex) {
                if (vertex->id == arestas[i].target) {
                    v = vertex;
                    break;
                }
                vertex = vertex->next;
            }

            fluxo = 0;
            if (u->altura > v->altura) {
                if ((arestas[i].capacidade - arestas[i].fluxo) < u->excesso_fluxo) {
                    fluxo = arestas[i].capacidade - arestas[i].fluxo;
                } else {
                    fluxo = u->excesso_fluxo;
                }
                u->excesso_fluxo -= fluxo;
                v->excesso_fluxo += fluxo;
                arestas[i].fluxo += fluxo;
                atualiza_aresta(i, fluxo);

                ok = 1;

                return ok;
            }
        }
    }
    return ok;
}

int push_relabel(int pj_global) {
    inicializa_refluxo(pj_global);

    string vertex_overfluxo = overfluxo();
    while (vertex_overfluxo != "") {
        if (!push(vertex_overfluxo))
            relabel(vertex_overfluxo);
        vertex_overfluxo = overfluxo();
    }

    return solve_max_fluxo();

}

int main() {
    int inicio_tempo, fim_tempo; //declaração de variaveis 
    double tempo_usado; //declaração de variaveis

    cout << "Criando o grafo a partir da Base ....\n" << endl;
    int pj = cria_grafo("amazon-meta.txt");
    cout << "Executando o fluxo maximo, Aguarde....\n" << endl;

    inicio_tempo = clock(); //iniciando a contagem do tempo
    int max_fluxo = push_relabel(pj);
    fim_tempo = clock(); //finalizando a contagem  do tempo
    tempo_usado = ((double) (fim_tempo - inicio_tempo)) / (double) CLOCKS_PER_SEC;

    cout << "Fluxo Maximo (pj'):" << max_fluxo << endl;
    cout << "Tempo do Fluxo Maximo: " << tempo_usado << "\n" << endl;

    return 0;
}