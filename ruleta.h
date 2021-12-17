#ifndef RULETA_H
#define RULETA_H
#include <iostream>
#include <vector>
#include <functional>

using namespace std;


struct Banca{
    int dinero_ganado{0};
};

//Structura de Jugador que recoge el dinero la apuesta y la retirada del jugado a su vez recoge el dinero que ganara la banca
struct Jugador{
    int dinero {10}; //Int para llevar la cuenta del dinero de cada jugador
    int pos{0}; //Posicion para asignar a cada jugador una posicion, para ayudar a la hora de borrarlo
    int dinero_perdido{0}; //Int que nos ayudara a la hora de imprimir
    int ap_dinero{0}; //Int del dinero apostado por cada jugador
    int apuestas{0}; //Int de la apuesta de cada jugador si numero o color
    int retirada{0}; //Int que nos ayudara a la cuenta de las retiradas de cada jugador
    int salir_partida{0};//Int que ayudara a llevar la cuenta de los jugadores que se han retidado de la parte definitivamente
};

//Funcion que nos devuelve el menu
int menu(){
    int opc;
    cout<<"\n";
    cout<<"Introduce una de las opciones indicadas"<<endl;
    cout<<"1. Normas"<<endl;
    cout<<"2.Comenzar la partida"<<endl;
    cin>>opc;
    system("CLS");

    return opc;
}

//Funcion que guarda los jugadores en un vector de jugadores
function<vector<Jugador>()> add_players = [] (){
    struct Jugador j;
    vector<Jugador> jugadores;
    for(int i{0}; i<4; i++){
        jugadores.push_back(j);
    }
    return jugadores;
};

//F
function<vector<Jugador>(vector<Jugador> &jugadores)> posiciones = [] (vector<Jugador> &jugadores){
    for(int i{0}; i < jugadores.size() ; i++){
        jugadores.at(i).pos = i;
    }
    return jugadores;
};

//Funcion que comprueba si el dinero esta fuera del rango permitido
function<int(vector<Jugador> &jugadores,int &i , int &ap)> check_dinero = [] (vector<Jugador> &jugadores,int i,int ap){
    while(ap > jugadores.at(i).dinero){
        cout<<"Cantidad que desea apostar: ";
        cin>>ap;
    }
    return ap;
};

//Funcion que comprueba si el numero apostado esta dentro del rango permitido
function<int(int &num)> check_nums = [] (int &num){
    while (num <= 0 || num > 36 ) {
        cout<<"Numero incorrecto"<<endl;
        cout<<"Por favor introduzca un numero entre el 1 y el 36: ";
        cin>>num;
    }
    return num;
};

//Funcion que comprueba si el color apostado es correcto
function<char(char &color)> check_color = [] (char color){
    while (color != 'r' && color != 'n' && color != 'R' && color != 'N') {
        cout<<"Color incorrecto"<<endl;
        cout<<"Por favor introduzca un color correcto: ";
        cin>>color;
    }
    return color;
};

//Funcion que comprueba que la opcion no se encuentra fuera de rango
function<int(int &op)> check_opcion = [] (int &op){
    while (op != 1 && op !=2) {
        cout<<"Opcion incorrecta"<<endl;
        cout<<"Por favor introduzca una opcion correcta: ";
        cin>>op;
    }
    return op;
};

//Funcion que comprueba si la opcion de Apostar o Retirarse es correcta
function<int(int &opc)> check_tirada = [] (int &opc){
    while (opc != 1 && opc !=2 && opc !=3) {
        cout<<"Opcion incorrecta"<<endl;
        cout<<"Por favor introduzca una opcion correcta: ";
        cin>>opc;
    }
    return opc;
};

//Funcion que llevara la cuenta de los jugadores que se han retirado
function<int(vector<Jugador>&jugadores)> retirados = [] (vector<Jugador>&jugadores){
    int retirada{0};
    for(auto elem:jugadores){
        if(elem.salir_partida == 1){
            retirada++;
        }
    }
    return retirada;
};

//Funcion que lleva la cuenta de los jugadores que se han quedado sin dinero
function<int(vector<Jugador>&jugadores)> dineros = [] (vector<Jugador>&jugadores){
    int cont{0};
    for(auto elem:jugadores){
        if(elem.dinero == 0 ){
            cont++;
        }
    }
    return cont;
};



//Funcion que lleva la cuenta de los jugadores que se han quedado sin dinero
function<vector<Jugador>(vector<Jugador> &jugadores, Banca &casino, int &i)> delete_player = [] (vector<Jugador> &jugadores,Banca &casino, int &i){
      for(auto elem:jugadores){
        if(jugadores.at(i).dinero == 0){
            cout<<"\n";
            cout<<"No le queda dinero para seguir apostando"<<endl;
            cout<<"Dinero perdido: "<<elem.dinero_perdido;
            cout<<"\n";
            cout<<"Eliminando Jugador "<<jugadores.at(i).pos<<"..... ";
            jugadores.at(i).retirada = 0;
            jugadores.erase(jugadores.begin() + i);
            break;
        }
        else if(jugadores.at(i).salir_partida == 1){
            cout<<"\n";
            cout<<"Dinero del Jugador "<<jugadores.at(i).pos<<" : "<<jugadores.at(i).dinero;
            jugadores.erase(jugadores.begin() + i);
            break;
        }

      }

    return jugadores;
};

//Funcion que imprime el dinero ganado por la banca
void print_banca(Banca &casino){
    cout<<"\n";
    cout<<"Dinero de la banca: "<<casino.dinero_ganado<<endl;
}


//Funcion que nos imprimira el dinero de cada jugador
void print_jugs(vector<Jugador> &jugadores){
    for(int i{0}; i < jugadores.size(); i++){
        if(jugadores.at(i).dinero == 0){
            cout<<"Dinero perdido por el  "<<"Jugador "<<jugadores.at(i).pos<<" : "<<jugadores.at(i).dinero_perdido<<endl;
        }
        else{
            cout<<"Dinero del "<<"Jugador "<<jugadores.at(i).pos<<" : "<<jugadores.at(i).dinero<<endl;
        }

    }
}

//Funcion para
//Usaremos un -1 cuando sea Rojo y un -2 cuando sea Negro
vector<Jugador> apuesta(vector<Jugador>&jugadores, Banca &casino){
    int ap{0};
    int op{0};
    int opc{0};
    int num{0};
    char color{0};
    int ap_color{0};
    int i{0};
    for(auto elem:jugadores){
        //cout<<jugadores.size();
        cout<<"\n";
        cout<<"\n"<<"Que desea hacer Jugador "<<jugadores.at(i).pos<<": "<<endl;
        cout<<"1 Apostar 2 Saltar la ronda(seguir jugando) 3 Retirarse de la partida: ";
        cin>>opc;
        opc = check_tirada(opc);
        jugadores.at(i).retirada = 0;
        if(jugadores.at(i).dinero == 0 && opc!=2){
            casino.dinero_ganado += jugadores.at(i).dinero_perdido;
            delete_player(jugadores,casino, i);
            //opc=2;
            i --;
        }

        else if(opc==1){
            cout<<"\n";
            cout<<"Dinero disponible: "<<jugadores.at(i).dinero;
            cout<<"\n";
            cout<<"Cantidad que desea apostar: ";
            cin>>ap;
            ap = check_dinero(jugadores,i,ap);
            jugadores.at(i).ap_dinero = ap;
            cout<<"\n";
            cout<<"A que quiere apostar a Color 1 o a numero 2: ";
            cin>>op;
            op = check_opcion(op);
            if(op==1){
                //Usaremos un -1 cuando sea R y un -2 cuando sea negro
                cout<<"A que color, Rojo R Negro N: ";
                cin>>color;
                color = check_color(color);
                if(color =='R'){
                    ap_color = -1;
                }
                else {
                    ap_color = -2;
                }
                jugadores.at(i).apuestas = ap_color;
            }
            else if(op==2){
                cout<<"\n";
                cout<<"A que Numero del 1 al 36: ";
                cin>>num;
                num = check_nums(num);
                jugadores.at(i).apuestas = num;
            }
            cout<<"\n";

        }
        else if(opc==2){
            jugadores.at(i).retirada = 1;
            cout<<"\n";
            cout<<"El Jugador no apuesta esta ronda :( "<<endl;
            cout<<"\n";
        }
        else if(opc==3){
            //jugadores.at(i).retirada = 1;
            jugadores.at(i).salir_partida = 1;
            cout<<"\n";
            cout<<"El Jugador "<<jugadores.at(i).pos<<" se ha retirado de la partida :( "<<endl;
            cout<<"Esperamos verte pronto";
            cout<<"\n";
            delete_player(jugadores,casino,i);
            i--;
        }
        int calcul{0};
        calcul  = jugadores.size() -1;
        if(i == calcul){
            break;
        }
        else{
            i++;
        }
    }
    return jugadores;
}

//Funcion que nos hace los calculos necesarios para cada jugador
vector<Jugador> calculos(vector<Jugador> &jugadores, Banca &casino, int resultado, int color){
    for(int i{0}; i < jugadores.size(); i++){
        if(resultado == jugadores.at(i).apuestas){
            jugadores.at(i).dinero -= jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero *= 35;
            jugadores.at(i).dinero += jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero=0;
        }
        else if(color == jugadores.at(i).apuestas){
            jugadores.at(i).dinero -= jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero *= 2;
            jugadores.at(i).dinero += jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero=0;
        }
        else if(resultado != jugadores.at(i).apuestas && jugadores.at(i).apuestas !=0){
            jugadores.at(i).dinero_perdido += jugadores.at(i).ap_dinero;
            jugadores.at(i).dinero -= jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero=0;
        }
        else if(color != jugadores.at(i).apuestas && jugadores.at(i).apuestas !=0){
            jugadores.at(i).dinero_perdido += jugadores.at(i).ap_dinero;
            jugadores.at(i).dinero -= jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero=0;
        }
    }
    return jugadores;
}

#endif // RULETA_H
