#include <iostream>
#include <time.h>
#include <ruleta.h>

using namespace std;

//Funcion para realizar las tiradas de la ruleta
void tirada(vector<Jugador> &jugadores, Banca &casino, int resultado){
    int color{0};
    if(resultado==0){
        for(int i{0}; i < jugadores.size() ; i++){
            jugadores.at(i).dinero -=  jugadores.at(i).ap_dinero;
            jugadores.at(i).ap_dinero = 0;
        }
    }
    else if (resultado%2 == 0) {
        color = -1;
        calculos(jugadores,casino,resultado,color);
    }
    else if (resultado% 2 != 0) {
        color = -2;
        calculos(jugadores,casino,resultado,color);
    }
}

void ruleta(vector<Jugador> &jugadores, Banca &casino){
    int retirada;
    int resultado{0};
    int cont{0};
    srand (time(NULL));
    do {
        if(jugadores.size() == 0){
            break;
        }
        resultado = rand() % 37;
        if(resultado % 2==0){
            cout<<"\n";
            cout<<"Y la bola ha caido en el: "<<resultado<<" Y Rojo"<<endl;
        }
        else if(resultado%2 !=0){
            cout<<"\n";
            cout<<"Y la bola ha caido en el: "<<resultado<<" Y Negro"<<endl;
        }
        tirada(jugadores,casino,resultado);
        retirados(jugadores);
        dineros(jugadores);
        if(cont <jugadores.size() && retirada <jugadores.size() ){
            cont = 0;
            retirada = 0;
            apuesta(jugadores,casino);
            retirados(jugadores);
            dineros(jugadores);
        }
    }
    while(cont < jugadores.size() && retirada < jugadores.size());
    print_jugs(jugadores);
    cout<<"\n";
    print_banca(casino);
}

int main()
{
    int ini;
    vector<Jugador> jugadores;
    Banca casino;
    cout<<"---Bienvenidos a la ruleta :)"<<"\n"<<endl;
    switch (menu()) {
    case 1:
        cout<<"\n";
        cout<<"Deberas apostar cantidades que tengas a tu disposicion"<<endl;
        cout<<"Al hacer tu apuesta puedes apostar a: "<<endl;
        cout<<"\t"<<"Color o Rojo o Negro"<<endl;
        cout<<"\t"<<"Numeros del 1 al 36"<<endl;
        cout<<"Pulse 1 para volver al menu ";
        cin>>ini;
        system("CLS");
        if(ini==1){
            cout<<"\n";
            menu();
            system("CLS");
        }
    case 2:
        jugadores = add_players();
        posiciones(jugadores);
        apuesta(jugadores, casino);
        ruleta(jugadores, casino);
    }
}
