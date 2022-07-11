
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string> 
#include <vector>
#include <list>
#include <queue>
#include <string.h>
using namespace std;

class graph{
private:
    int vn;          
    list<pair<int, double>>* pont;

public:
    graph(int vn){

        this->vn = vn;

        pont = new list<pair<int, double>>[vn*2];

    }
    void make_edge(int v1, int v2, double w){

        pont[v1].push_back(make_pair(v2,w));
        pont[v2].push_back(make_pair(v1,w));
        // pont[v1].push_back({v2,w});
        // pont[v2].push_back({v1,w});
    }

    void prim(int v1, int exec){

        double dist[vn];
        

        priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int,double>>>pq;
        //priority_queue<pair<int,double>>pq;
        vector<int>visitados(vn, 0);

        
        visitados[v1] = 1;
        

        for(pair<int,int> aux: pont[v1]){
             pq.push(make_pair(aux.second,aux.first));
            //  pq.push({-aux.second,aux.first});

        }
        int sum = 0;


        while(!pq.empty()){

            pair<int,int>p = pq.top();
            pq.pop();
            
            
            if(visitados[p.second] == 1) continue;
            
            sum += p.first;
            
            visitados[p.second] = 1;

        for(pair<int,int> aux: pont[p.second]){
             pq.push(make_pair(aux.second,aux.first));
             
            // pq.push({-p.second,p.first});
        
            
        }        
        

        }
       
        
        cout<<sum<<endl; 

    }
};





int main(int argc, char *argv[]){

    int inicio;
    bool flagv1, flagv2 = false;
    string arquivo;

    for(int i =1; i<argc; i++){
        if(!strcmp(argv[i], "-h")){
            cout<<"\n";
            cout<<"\n";
            cout<<"---O algoritmo de Prim é utilizado para achar a arvore geradora mínima em um grafo"<<endl;
            cout<<"---Para uma execução correta do algoritmo deve ser passado o argumento -i seguido de um inteiro representando o vértice inicial"<<endl;
            cout<<"---Além disso, é preciso utilizar -f seguido do nome do arquivo que contém os vértices e pesos"<<endl;
            cout<<"---Um arquivo de exemplo já existe no diretório de cada algoritmo, e é nomeado como *nome_do_algoritmo.dat*"<<endl;
            cout<<"---Se apenas o vértice inicial for passado como argumento o algoritmo mostrará o custo da arvore geradora mínima"<<endl;
            cout<<"---Também é necessário fornecer um grafo conexo"<<endl;
            cout<<"---Caso o argumento -s seja especificado o algoritmo mostrará as arestas que formam a arvore geradora minima"<<endl;
            cout<<"\n";
            cout<<"\n";
            return 0;

        }
        if(!strcmp(argv[i], "-i")){

            inicio = stoi(argv[i+1]);
            flagv1 = true;
        
        }

        if(!strcmp(argv[i], "-s")){

            
            flagv2 = true;
        
        }
        if(!strcmp(argv[i], "-f")){

            arquivo = argv[i+1];
            
        
        }


        
    }
    


    ifstream file;
    file.open(arquivo, ios::in);
    if(!file){
        cout<<"Nao foi possivel abrir o arquivo que contem as arestas e pesos do grafo"<<endl;
        return 0;
    }
    

    string line;
    vector<int> numbs;
    int i = 0;
    int v1, v2;
    double p1;

    int vn, an;
    bool flag = false;

    
    while (getline(file,line)){
        
        if(flag == false){
            flag = true;
            continue;

        }
        else{
            numbs.push_back(line.length());
            
        }
    }
    file.close();
    

    file.open(arquivo, ios::in);
    if(!file){
        cout<<"Nao foi possivel abrir o arquivo que contem as arestas e pesos do grafo"<<endl;;
        return 0;
    }

    
    file>>vn,file>>an;
    
    graph grafo(vn);
    int j = 0;
    while(!file.eof()){
       

        if (j<an){
            if (numbs[j] < 5){
                file>>v1, file>>v2;
                p1=1;

                grafo.make_edge(v1, v2, p1);
            }
            else{
                file>>v1, file>>v2, file>>p1;
                grafo.make_edge(v1, v2, p1);
            }

        }
        j++;
        
    }
    if(flagv1 && !flagv2){

    grafo.prim(inicio,1);
    }
    else if(flagv1 && flagv1){
        
        grafo.prim(inicio, 2);
    }

    return 0;
}

