/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: dabra
 *
 * Created on 18 de agosto de 2022, 17:50
 */
#include <fstream>
#include <iostream>
#include <sstream> 
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "nlohmann\json.hpp"
// cambios realizados
using namespace nlohmann;
using namespace std;

/*
 * 
 */

typedef struct Usuario *nodoUS;
typedef struct Articulo *nodoArt;
typedef struct Rareza *nodoRar;
typedef struct Movimiento *nodoMov;
typedef struct Tutorial *nodoTut;


nodoUS listaUs = NULL;
nodoRar listaArt = NULL;
nodoUS ensesion = NULL;
nodoTut tutorial = NULL;

int tamUs = 0;

std::string operator*(const std::string& str, size_t times) {
    std::stringstream stream;
    for (size_t i = 0; i < times; i++) stream << str;
    return stream.str();
}

struct Movimiento {
    int x;
    int y;
};

struct Tutorial {
    int inicio;
    int fin;
    struct Movimiento *movs[1500];
};

struct Usuario {
public:
    string nick;
    string password;
    string edad;
    int monedas;
    struct Usuario *sig;
    struct Usuario *ant;
};

struct Articulo {
    int id;
    string categoria;
    string nombre;
    int precio;
    string src;
    struct Articulo *sig;
};

struct Rareza {
    string rareza;
    struct Articulo *sig;
    struct Rareza *cat;
};

nodoMov crear_nodo(int x, int y) {
    nodoMov nodo;
    nodo = new(struct Movimiento);
    nodo->x = x;
    nodo->y = y;
    return nodo;
}

nodoArt crear_nodo(int id, string categoria, string nombre, int precio, string src) {
    nodoArt nodo;
    nodo = new(struct Articulo);
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->categoria = categoria;
    nodo->precio = precio;
    nodo->src = src;
    nodo->sig = nullptr;

    return nodo;
}

nodoUS crear_nodo(string nick, string password, string edad, int monedas) {
    nodoUS nodo;
    nodo = new(struct Usuario);
    nodo->ant = nullptr;
    nodo->edad = edad;
    nodo->monedas = monedas;
    nodo->nick = nick;
    nodo->password = password;
    nodo->sig = nullptr;

    return nodo;
}

void enqueue(nodoTut &cola, nodoMov nodo) {
    cola->movs[++cola->fin] = nodo;
}

nodoMov dequeue(nodoTut &cola) {
    return cola->movs[cola->inicio++];
}

int poner_primeroUs(nodoUS &Lista, nodoUS us, int tam) {
    us->sig = us;
    us->ant = us;
    Lista = us;
    tam++;
    return tam;
}

int poner_ultimoUs(nodoUS &lista, nodoUS us, int tam) {
    nodoUS temp = new (struct Usuario);
    temp = lista;

    while (temp->sig != lista) {
        temp = temp->sig;
    }

    us->ant = temp;
    us->sig = lista;
    temp->sig = us;
    lista->ant = us;
    tam++;
    return tam;
}

nodoUS buscar(string Nombre) {
    nodoUS temp = new(struct Usuario);
    temp = listaUs;
    for (int i = 0; i < tamUs; i++) {
        if (temp->nick == Nombre) return temp;
        temp = temp->sig;
    }
    return NULL;
}

void ponerArt(nodoRar &lista, nodoArt art) {
    nodoArt temp = new(struct Articulo);

    if (lista->sig == NULL) {
        lista->sig = art;
    } else {
        temp = lista->sig;
        while (temp->sig != nullptr) {
            temp = temp->sig;
        }
        temp->sig = art;
    }

}

void imprimir_tutorial() {
    nodoMov temp = new(struct Movimiento);
    int end = tutorial->fin;
    int ini = tutorial->inicio;
    int espacios;
    int espacios2;
    string esp = " ";

    cout << " <---";
    for (int i = ini; i < end + 1; i++) {
        temp = dequeue(tutorial);
        espacios = 6 - 2 - to_string(temp->x).length();
        if (espacios % 2 == 0) {
            espacios = espacios / 2;
            espacios2 = espacios;
        } else {
            espacios = (espacios + 1) / 2;
            espacios2 = espacios - 1;
        }
        cout << "|" << esp * espacios << "x:" << temp->x << esp * espacios2 << "|";
        enqueue(tutorial, temp);
    }
    cout << endl << "     ";
    end = tutorial->fin;
    ini = tutorial->inicio;
    for (int i = ini; i < end + 1; i++) {
        temp = dequeue(tutorial);
        espacios = 6 - 2 - to_string(temp->y).length();
        if (espacios % 2 == 0) {
            espacios = espacios / 2;
            espacios2 = espacios;
        } else {
            espacios = (espacios + 1) / 2;
            espacios2 = espacios - 1;
        }
        cout << "|" << esp * espacios << "y:" << temp->y << esp * espacios2 << "|";
        enqueue(tutorial, temp);
    }
    cout << "<--- ";
}

void imprimir_listaUs(nodoUS &lista, int tam) {
    nodoUS temp = new(struct Usuario);
    temp = lista;
    int espacios;
    int espacios2;
    string esp = " ";

    for (int i = 0; i < tam; i++) {
        espacios = 25 - 8 - temp->nick.length();    
        if (espacios % 2 == 0) {
            espacios = espacios / 2;
            espacios2 = espacios;
        } else {
            espacios = (espacios + 1) / 2;
            espacios2 = espacios - 1;
        }
        cout << "|" << esp * espacios << "Nombre: " << temp->nick << esp * espacios2 << "| -> ";
        temp = temp->sig;
    }
    espacios = 25 - 8 - temp->nick.length();
    if (espacios % 2 == 0) {
        espacios = espacios / 2;
        espacios2 = espacios;
    } else {
        espacios = (espacios + 1) / 2;
        espacios2 = espacios - 1;
    }
    cout << "|" << esp * espacios << "Nombre: " << temp->nick << esp * espacios2 << "|" << endl;

    temp = lista;
    for (int i = 0; i < tam; i++) {
        espacios = 25 - 10 - temp->password.length();
        if (espacios % 2 == 0) {
            espacios = espacios / 2;
            espacios2 = espacios;
        } else {
            espacios = (espacios + 1) / 2;
            espacios2 = espacios - 1;
        }
        cout << "|" << esp * espacios << "Password: " << temp->password << esp * espacios2 << "|    ";
        temp = temp->sig;
    }
    espacios = 25 - 10 - temp->password.length();
    if (espacios % 2 == 0) {
        espacios = espacios / 2;
        espacios2 = espacios;
    } else {
        espacios = (espacios + 1) / 2;
        espacios2 = espacios - 1;
    }
    cout << "|" << esp * espacios << "Password: " << temp->password << esp * espacios2 << "|" << endl;

    temp = lista;
    for (int i = 0; i < tam; i++) {
        espacios = 25 - 6 - temp->edad.length();
        if (espacios % 2 == 0) {
            espacios = espacios / 2;
            espacios2 = espacios;
        } else {
            espacios = (espacios + 1) / 2;
            espacios2 = espacios - 1;
        }
        cout << "|" << esp * espacios << "Edad: " << temp->edad << esp * espacios2 << "|    ";
        temp = temp->sig;
    }
    espacios = 25 - 6 - temp->edad.length();
    if (espacios % 2 == 0) {
        espacios = espacios / 2;
        espacios2 = espacios;
    } else {
        espacios = (espacios + 1) / 2;
        espacios2 = espacios - 1;
    }
    cout << "|" << esp * espacios << "Edad: " << temp->edad << esp * espacios2 << "|" << endl;

    temp = lista;
    for (int i = 0; i < tam; i++) {
        espacios = 25 - 9 - to_string(temp->monedas).length();
        if (espacios % 2 == 0) {
            espacios = espacios / 2;
            espacios2 = espacios;
        } else {
            espacios = (espacios + 1) / 2;
            espacios2 = espacios - 1;
        }
        cout << "|" << esp * espacios << "Monedas: " << temp->monedas << esp * espacios2 << "| <- ";
        temp = temp->sig;
    }
    espacios = 25 - 9 - to_string(temp->monedas).length();
    if (espacios % 2 == 0) {
        espacios = espacios / 2;
        espacios2 = espacios;
    } else {
        espacios = (espacios + 1) / 2;
        espacios2 = espacios - 1;
    }
    cout << "|" << esp * espacios << "Monedas: " << temp->monedas << esp * espacios2 << "|" << endl << endl;

}

void imprimir_listaRar(nodoRar &lista) {
    nodoRar temp = new(struct Rareza);
    nodoArt temp2 = new(struct Articulo);
    temp = lista;
    while (temp != nullptr) {
        temp2 = temp->sig;
        cout << temp->rareza << " -> ";
        while (temp2->sig != nullptr) {
            cout << temp2->nombre << " -> ";
            temp2 = temp2->sig;
        }
        cout << temp2->nombre << endl;

        if (temp->cat != nullptr) {
            cout << "|" << endl << "v" << endl;
        }

        temp = temp->cat;
    }
}

void Carga() {
    cout << "\nCargando\n";
    string entrada;
    cout << "Escribe la direccion del archivo entrada: ";
    cin >> entrada;

    std::ifstream inFile;
    inFile.open(entrada); //open the input file

    std::stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    std::string str = strStream.str();

    auto informacion = json::parse(str);
    json usuarios = informacion.at("usuarios");
    json articulos = informacion.at("articulos");
    json tut = informacion.at("tutorial");
    json movimientos = tut.at("movimientos");

    for (int i = 0; i < usuarios.size(); i++) {
        string nombre = usuarios[i]["nick"].get<string>();
        string pass = usuarios[i]["password"].get<string>();
        string edad = usuarios[i]["edad"].get<string>();
        int monedas = std::stoi(usuarios[i]["monedas"].get<string>());

        nodoUS jug = crear_nodo(nombre, pass, edad, monedas);

        if (tamUs != 0) {
            tamUs = poner_ultimoUs(listaUs, jug, tamUs);
        } else {
            tamUs = poner_primeroUs(listaUs, jug, tamUs);
        }
    }

    for (int i = 0; i < articulos.size(); i++) {
        int id = std::stoi(articulos[i]["id"].get<string>());
        string categoria = articulos[i]["categoria"].get<string>();
        string nombre = articulos[i]["nombre"].get<string>();
        int precio = std::stoi(articulos[i]["precio"].get<string>());
        string src = articulos[i]["src"].get<string>();

        nodoArt art = crear_nodo(id, categoria, nombre, precio, src);

        if (listaArt == NULL) {
            listaArt = new(struct Rareza);
            listaArt->rareza = categoria;
            listaArt->sig = art;
            listaArt->cat = nullptr;
        } else {
            nodoRar temp = new(struct Rareza);
            temp = listaArt;
            bool rar_creada = false;

            while (temp->cat != nullptr) {
                if (categoria == temp->rareza) {
                    rar_creada = true;
                    break;
                }
                temp = temp->cat;
            }
            if (categoria == temp->rareza) {
                rar_creada = true;
            }
            if (rar_creada) {
                ponerArt(temp, art);
            } else {
                nodoRar nueva_rar = new(struct Rareza);
                nueva_rar->rareza = categoria;
                nueva_rar->sig = art;
                nueva_rar->cat = nullptr;
                temp->cat = nueva_rar;
            }
        }
    }

    nodoTut tuto = new(struct Tutorial);
    tuto->inicio = 0;
    tuto->fin = -1;
    tutorial = tuto;


    int ancho = std::stoi(tut["ancho"].get<string>());
    int alto = std::stoi(tut["alto"].get<string>());

    nodoMov temp_mov = crear_nodo(ancho, alto);

    enqueue(tuto, temp_mov);

    for (int i = 0; i < movimientos.size(); i++) {
        int x = std::stoi(movimientos[i]["x"].get<string>());
        int y = std::stoi(movimientos[i]["y"].get<string>());
        temp_mov = crear_nodo(x, y);
        enqueue(tuto, temp_mov);
    }
    cout << "\nSe han cargado todos los datos\n\n";
}

void Registrar() {
    cout << "\nRegistrando\n\n";
    string nombre, password, edad;
    cout << "Nombre: ";
    cin >> nombre;
    cout << "Edad: ";
    cin >> edad;
    cout << "password: ";
    cin >> password;
    nodoUS jug = crear_nodo(nombre, password, edad, 0);
    if (tamUs != 0) {
        tamUs = poner_ultimoUs(listaUs, jug, tamUs);
    } else {
        tamUs = poner_primeroUs(listaUs, jug, tamUs);
    }
    cout << endl << endl;
}

void Editar() {
    string usuario;
    string password;
    string edad;
    cout << "\nEditar\n\n";
    cout << "Nombre de Usuario: ";
    cin >> usuario;
    cout << "Password: ";
    cin >> password;
    cout << "Edad: ";
    cin >> edad;
    ensesion->edad = edad;
    ensesion->nick = usuario;
    ensesion->password = password;
    cout << "Usuario modificado exitosamente\n" << endl << endl;
}

bool Eliminar() {
    bool eliminado = false;
    string elec;
    cout << "En verdad quieres eliminar este usuario permanentemente? [y/n]: ";
    cin >> elec;
    if (elec == "y") {
        ensesion->sig->ant = ensesion->ant;
        ensesion->ant->sig = ensesion->sig;
        if (listaUs == ensesion) {
            listaUs = ensesion->sig;
        }
        free(ensesion);
        cout << "Se han eliminado todos los datos de este Usuario.\n";
        eliminado = true;
        tamUs--;
    }
    return eliminado;
}

void Tutorial() {
    nodoTut temp = new(struct Tutorial);
    nodoMov tempM = new(struct Movimiento);
    temp = tutorial;
    int end = temp->fin;
    tempM = dequeue(temp);
    int ini = tutorial->inicio;
    cout << "Tutorial\n" << "   Tablero:\n" << "       Ancho: " << tempM->x << endl << "       Alto: " << tempM->y << endl;
    enqueue(temp, tempM);
    cout << "   Movimientos:\n" << "        ";
    for (int i = ini; i < end; i++) {
        tempM = dequeue(temp);
        cout << "(" << tempM->x << ", " << tempM->y << ") ->";
        enqueue(tutorial, tempM);
    }
    tempM = dequeue(temp);
    cout << "(" << tempM->x << ", " << tempM->y << ")\n";
    enqueue(tutorial, tempM);
}

void Tienda() {

}

void Movimientos() {

}

void App() {
    string menu = "************** Menu **************\n* 1. Editar informacion          *\n* 2. Eliminar Cuenta             *\n* 3. Ver tutorial                *\n* 4. Ver tienda                  *\n* 5. Realizar movimientos        *\n* Salir al menu principal        *\n**********************************\n";
    cout << menu;
    int elec;

    cout << "Elige una opcion: ";
    cin >> elec;

    switch (elec) {
        case 1:
            Editar();
            App();
            break;
        case 2:
            if (!Eliminar()) App();
            break;
        case 3:
            Tutorial();
            App();
            break;
        case 4:
            Tienda();
            App();
            break;
        case 5:
            Movimientos();
            App();
            break;
        case 6:
            break;
        default:
            cout << "Seleccion no valida!\n";
            App();
    }
}

void Login() {
    string usuario;
    string password;
    nodoUS us;
    cout << "Login\n\n";
    cout << "Nombre de Usuario: ";
    cin >> usuario;
    us = buscar(usuario);
    if (us == NULL) {
        cout << "No se ha encontrado el Usuario\n\n";
    } else {
        cout << "Password: ";
        cin >> password;

        if (password == us->password) {
            ensesion = us;
            App();
        } else {
            cout << "El usuario y contraseña no coinciden\n\n";
        }
    }
}

void ordenarUsuarios() {
    nodoUS tmp = new(struct Usuario);
    nodoUS tmp2 = new(struct Usuario);
    nodoUS listaord = new(struct Usuario);
    tmp = listaUs;
    
    nodoUS jug = crear_nodo(tmp->nick, tmp->password, tmp->edad, tmp->monedas);
    poner_primeroUs(listaord, jug, 0);
    tmp = tmp->sig;
    
    for(int i = 0; i<tamUs-1; i++){
        jug = crear_nodo(tmp->nick, tmp->password, tmp->edad, tmp->monedas);
        poner_ultimoUs(listaord, jug, 0);
        tmp = tmp->sig;
    }
    
    
    bool cambio = false;
    
    while(!cambio){
        cambio = false;
        tmp = listaord;
        for(int i = 0; i<tamUs; i++){
            tmp2 = tmp->sig;
            if (std::stoi(tmp->edad) < std::stoi(tmp2->edad)) {
                tmp->ant->sig = tmp2;
                tmp2->ant = tmp->ant;
                tmp2->sig->ant = tmp;
                tmp->ant = tmp2;
                tmp->sig = tmp2->sig;
                tmp2->sig = tmp;
                cambio = true;
            }
            if(cambio){
                tmp=tmp;
            }else{
                tmp = tmp2;
            }
        }
    }
    
    tmp = listaord;
    for(int i = 0; i<tamUs; i++){
        int max = stoi(tmp->edad);
        if(stoi(tmp->sig->edad) > max){
            max = stoi(tmp->sig->edad);
            listaord = tmp->sig;
        }
        tmp = tmp->sig;
    }
    
    tmp = listaord;
    for(int i = 1; i<tamUs+1; i++){
        cout << i << ".- " << "Nombre: " << tmp->nick << ", Edad: " << tmp->edad << ", Password: " << tmp->password << ", Monedas: " << tmp->monedas << endl;
        tmp = tmp->sig;
    }
}

void Reportes() {
    cout << "Reportando\n\n";
    cout << "---------------------------------Reporte de Usuarios---------------------------------\n\n";
    imprimir_listaUs(listaUs, tamUs);
    cout << "---------------------------------Reporte de Articulos---------------------------------\n\n";
    imprimir_listaRar(listaArt);
    cout << "\n---------------------------------Reporte de Tutorial---------------------------------\n\n";
    imprimir_tutorial();
    cout << "\n\n---------------------------------Usuarios descendente---------------------------------\n\n";
    ordenarUsuarios();
    cout << endl << endl;
}

void Menu() {
    string menu = "************** Menu **************\n* 1. Carga Masiva                *\n* 2. Registrar Usuario           *\n* 3. Login                       *\n* 4. Reportes                    *\n* Salir del Juego                *\n**********************************\n";

    cout << menu;

    int elec;

    cout << "Elige una opcion: ";
    cin >> elec;
    switch (elec) {
        case 1:
            Carga();
            Menu();
            break;
        case 2:
            Registrar();
            Menu();
            break;
        case 3:
            Login();
            Menu();
            break;
        case 4:
            Reportes();
            Menu();
            break;
        case 5:
            break;
        default:
            cout << "Seleccion no valida!\n";
            Menu();
            break;
    }

}

int main() {
    Menu();
    return 0;
}

