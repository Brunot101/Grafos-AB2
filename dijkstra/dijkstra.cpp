#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string> 
#include <vector>
#include <list>
#include <queue>
#include <string.h>
#define MAX 5000000
using namespace std;

// Grafo presente no arquivo dijkstra.dat https://rosalind.info/problems/dij/
class graph{
private:
    int vn;          
    list<pair<int, double>>* pont;

public:
    graph(int vn){

        this->vn = vn;

        pont = new list<pair<int, double>>[vn];

    }
    void make_edge(int v1, int v2, double w){

        pont[v1].push_back(make_pair(v2,w));
    }

    void dijkstra(int v1, int v2,int exec){

        double dist[vn];
        int expandidos[vn];

        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double,int>>>q;

        for (int i = 0; i < vn; i++)
        {
            dist[i] = MAX;
            expandidos[i] = 0;
            
        }
        dist[v1] = 0;
        q.push(make_pair(dist[v1],v1));

        while(!q.empty()){
            pair<double, int>p = q.top();
            int v = p.second;
            q.pop();

            if(expandidos[v] == 0){

                expandidos[v] == 1;

                list<pair<int,double>>::iterator aux;

                for (aux = pont[v].begin(); aux != pont[v].end(); aux++)
                {
                    int va = aux->first;
                    double wa = aux->second;

                    if(dist[va] > (dist[v] + wa)){

                        dist[va] = dist[v] + wa;
                        q.push(make_pair(dist[va], va));
                    } 
                }
                

            }

        }
        
        if(exec == 1){

        cout<< dist[v2]<<endl;
        }
        else if(exec == 2){
            int j =1;
            for(int i = 0; i<vn; i++){
                cout<<j<<":"<<dist[i]<<" ";
                j++;
            }
        }
        cout<<endl;

        
        
    }
};





int main(int argc, char *argv[]){

    int inicio, fim;
    bool flagv1 = false;
    bool flagv2 = false;
    string arquivo;

    for(int i =1; i<argc; i++){
        if(!strcmp(argv[i], "-h")){
            cout<<"\n";
            cout<<"\n";
            cout<<"---O algoritmo de Dijkstra é utilizado para achar o caminho de custo mínimo entre os vértices de um grafo"<<endl;
            cout<<"---Para uma execução correta do algoritmo deve ser passado o argumento -i seguido de um inteiro representando o vértice inicial"<<endl;
            cout<<"---Além disso, é preciso utilizar -f seguido do nome do arquivo que contém os vértices e pesos"<<endl;
            cout<<"---Um arquivo de exemplo já existe no diretório de cada algoritmo, e é nomeado como *nome_do_algoritmo.dat*"<<endl;
            cout<<"---Se apenas o vértice inicial for passado como argumento o algoritmo mostrará o custo do mesmo para os outros vértices do grafo"<<endl;
            cout<<"---Caso o vertice final também seja especificado através do argumento -l o algoritmo mostrará o custo entre os vértices inicial e final"<<endl;
            cout<<"\n";
            cout<<"\n";
            return 0;

        }
        if(!strcmp(argv[i], "-i")){

            inicio = stoi(argv[i+1]);
            flagv1 = true;
        
        }

        if(!strcmp(argv[i], "-l")){

            fim = stoi(argv[i+1]);
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
    int vn, an;
    bool flag = false;
    int i =0;
    
    while (getline(file,line)){
        
        if(flag == false){
            flag = true;
            continue;

        }
        else{
            numbs.push_back(line.length());
            i++;
        }
        
    }
    file.close();
    

    file.open(arquivo, ios::in);
    if(!file){
        cout<<"Nao foi possivel abrir o arquivo que contem as arestas e pesos do grafo"<<endl;
        return 0;
    }

    
    file>>vn,file>>an;
    
    int v1,v2;
    double p1;
    
    graph grafo(vn);
    int j = 0;
    while(!file.eof()){
        

        if (j<i){
            if (numbs[j] < 5){
                file>>v1, file>>v2;
                v1--;v2--;
                p1=1;

                grafo.make_edge(v1, v2, p1);
            }
            else{
                file>>v1, file>>v2, file>>p1;
                v1--;v2--;
                grafo.make_edge(v1, v2, p1);
            }

        }
        j++;
        
    }
    if(flagv1 && flagv2){
        inicio--;
        fim--;
        grafo.dijkstra(inicio,fim,1);
    }
    else if(flagv1){
        inicio--;
        fim--;
        
        grafo.dijkstra(inicio,i,2);
            
            

        
    }
    
    

    return 0;
}

