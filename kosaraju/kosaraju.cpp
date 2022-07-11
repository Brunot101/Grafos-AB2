#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <string.h>
using namespace std;
// Exemplo do grafo de exemplo contido no kosaraju.dat: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/strong-comps.html

class graph{
private:
    int vn;          
    list<int> * viz;

    void dfs1(int vn, int visitados[], stack<int> &stck){

        visitados[vn] = 1;
        
        list<int>::iterator pont;

        for (pont = viz[vn].begin(); pont != viz[vn].end(); pont++)
        {   
            
            if(visitados[*pont] == 0){
                
                dfs1(*pont, visitados, stck);
            
            } 
        }
        
        stck.push(vn);
    }

    void dfs2(int vn, int visitados[]){

        visitados[vn] = 1;
        cout<< vn <<" ";
        

         list<int>::iterator pont;
         for(pont = viz[vn].begin(); pont != viz[vn].end(); pont++){
            
            if(visitados[* pont] == 0){
                dfs2(*pont, visitados);
                
            }
         }  

    }

public:
    graph(int vn){

        this->vn = vn;

        viz = new list<int>[vn];

    }
    void make_edge(int v1, int v2){

        viz[v1].push_back(v2);
        
    
    }
    graph make_graphT(){

        graph graphT(vn);
        
        for(int i = 0; i<vn; i++){
            
            list<int>::iterator pont;
            for(pont = viz[i].begin(); pont!= viz[i].end(); pont++){
                graphT.viz[*pont].push_back(i);
                
            }
        }
        return graphT;

    }
    
    void print_componentes(){
        
        stack<int> stck;
        int * visitados = new int[vn];
        int i;
        for(i = 0; i<vn; i++){
            visitados[i] = 0;
            
        }
        
        for(i = 0; i<vn; i++){
            if(visitados[i] == 0){
                
                dfs1(i, visitados, stck);
                
                
            }
        }
        
        graph graphT = make_graphT();
        
        for(i = 0; i<vn; i++){
            visitados[i] = 0;
            
            
        }

        while(!stck.empty()){
            int aux;
            
            aux = stck.top();
            stck.pop();
            if (visitados[aux] == 0){
                
                graphT.dfs2(aux, visitados);
                cout<<"\n";
            }

        }

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
            cout<<"---O algoritmo de Kosaraju é utilizado para achar componentes fortemente conectadas de um grafo direcionado"<<endl;
            cout<<"---Para uma execução correta do algoritmo deve apenas ser passado o nome do arquivo"<<endl;
            cout<<"---Para especificar o arquivo use -f seguido do nome do arquivo que contém os vértices e pesos"<<endl;
            cout<<"--Assim, o algoritmo irá mostrar os vértices que formam as componentes fortemente conectadas (uma por linha)"<<endl;
            cout<<"---Um arquivo de exemplo já existe no diretório de cada algoritmo, e é nomeado como *nome_do_algoritmo.dat*"<<endl;
            cout<<"---Também é necessário fornecer um grafo conexo"<<endl;
            
            cout<<"\n";
            cout<<"\n";
            return 0;

        }
        

        
        if(!strcmp(argv[i], "-f")){

            arquivo = argv[i+1];
            flagv2 = true;
        
        }


        
    }



    ifstream file;
    file.open(arquivo, ios::in);
    if(!file){
        cout<<"Nao foi possivel abrir o arquivo que contem as arestas e pesos do grafo"<<endl;;
        return 0;
    }
    

    int vn, an;
    int v1, v2;

    file >> vn, file >>an;

    graph grafo(vn);

    while(!file.eof()){ 

        file>>v1, file>>v2;
        grafo.make_edge(v1, v2);
        
        
        
    }
    file.close();

    
    grafo.print_componentes();

    
    return 0;

}

