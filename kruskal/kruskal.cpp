#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string> 
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include<string.h>

using namespace std;

class graph{
private:
    int vn,an;         

    
    vector<int> viz;
    vector<pair<int, pair<int,int>>>list;
    

public:
    graph(int vn, int an, vector<pair<int, pair<int,int>>>list){

        this->vn = vn;
        this->an = an;
        this->list = list;
    

    }
    
    
    void start(int vn){

        int i = 0;
        viz.resize(an);
        for(i=0; i<vn; i++){
            viz[i] = i;
            
        }
        
    }
    int find(int v1){
        
        if(v1 == viz[v1]){
            
            return v1;
        }
        else{
            
            return viz[v1] = find(viz[v1]);
        }
          
    }

    void Union(int v1, int v2){
        v1 = find(v1);
        v2 = find(v2);
        viz[v2] = v1;
    }

    
    int kruskal(int n, int exec){
        sort(list.begin(), list.end());
        start(n);
        int p, ans;
        p=0;
        ans=0;
        int comp;
        comp = n;
        pair<int,pair<int,int>>aux1;

        // cout<<comp<<" "<<p<<" "<<an;
        while(comp != 1 && p<an){
            pair<int,pair<int,int>>act = list[p];
            

            if(find(act.second.first) != find(act.second.second)){
                
                if(exec == 1) cout << act.second.first<<"<-"<<act.second.second<<endl;
                
                Union(act.second.first,act.second.second);
                ans = ans + act.first;
                comp--;
                
            }
            p++;

        }

        return ans;
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
            cout<<"---O algoritmo de Kruskal é utilizado para achar a arvore geradora mínima em um grafo"<<endl;
            cout<<"---Para uma execução correta do algoritmo deve ser passado o nome do arquivo contendo vertices e pesos"<<endl;
            cout<<"---Para especificar o arquivo use -f seguido do nome do arquivo que contém os vértices e pesos"<<endl;
            cout<<"---Um arquivo de exemplo já existe no diretório de cada algoritmo, e é nomeado como *nome_do_algoritmo.dat*"<<endl;
            cout<<"---Se apenas o arquivo de entrada for passado como argumento o algoritmo mostrará o custo da arvore geradora mínima"<<endl;
            cout<<"---Também é necessário fornecer um grafo conexo"<<endl;
            cout<<"---Caso o argumento -s seja especificado o algoritmo mostrará as arestas que formam a arvore geradora minima"<<endl;
            cout<<"\n";
            cout<<"\n";
            return 0;

        }
        

        if(!strcmp(argv[i], "-s")){

            
            flagv1 = true;
        
        }
        if(!strcmp(argv[i], "-f")){

            arquivo = argv[i+1];
            flagv2 = true;
        
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
        cout<<"Nao foi possivel abrir o arquivo que contem as arestas e pesos do grafo"<<endl;
        return 0;
    }

    
    file>>vn,file>>an;
    
    
    int j = 0;
    vector<pair<int, pair<int,int>>>list;
    list.resize(an);
    while(!file.eof()){
       

        if (j<an){
            if (numbs[j] < 5){
                file>>v1, file>>v2;
                p1=1;

                list[j] = {p1,{v1,v2}};
            }
            else{
                file>>v1, file>>v2, file>>p1;
                list[j] = {p1,{v1,v2}};
            }

        }
        j++;
        
    }
    graph grafo(vn,an, list);
    if(flagv1 == true){
        
    
        int b = grafo.kruskal(vn, 1);
    
    }
    else if(flagv2 == true){
        int a = grafo.kruskal(vn, 2);
        cout<<a<<endl;
        
    }

    
    
    // 

    return 0;
}

