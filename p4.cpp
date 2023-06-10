#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

// Définition de la classe Concursante
class Concursante {
    int id; // identificador del concursante
    int edad; 
    float peso;
    bool genero;
    float fuerza;

public:
    // Constructeur par défaut
    Concursante(){

    }

    // Constructeur
    Concursante(int id, int edad, float peso, bool genero) {
        this->id = id;
        this->edad = edad;
        this->peso = peso;
        this->genero = genero;
        fuerza = calculateFuerza();
    }

    // Constructeur de copie
    Concursante(const Concursante& other) {
        id = other.id;
        edad = other.edad;
        peso = other.peso;
        genero = other.genero;
        fuerza = other.fuerza;
    }

    // return el ID del concursante
    int getID(){
        return id;
    }

    // return el edad del concursante
    int getEdad(){
        return edad;
    }

    // return el peso del concursante
    float getPeso(){
        return peso;
    }

    // return el genero del concursante
    bool getGenero(){
        return genero;
    }

    // return la fuerza del concursante
    float getFuerza(){
        return fuerza;
    }

    // return la fuerza del concursante
    float calculateFuerza(){
        int new_edad = convertEdad();
        int new_peso = convertPeso();
        if(genero){
            return (1.0/new_edad)*(1.0/new_peso);
        }
        return (1.0/new_edad)*(1.0/new_peso)*1.3;
    }

    // Convert el edad entre 1 y 4
    int convertEdad(){
        if(edad < 30){
            return 1;
        }
        else if(edad >= 30 && edad < 45){
            return 2;
        }
        else if(edad >= 45 && edad < 60){
            return 3;
        }
        else{
            return 4;
        }
    }

    // Convert el peso entre 1 y 3
    int convertPeso(){
        if(peso >= 75){
            return 1;
        }
        else if(peso < 75 && peso >= 63){
            return 2;
        }
        else{
            return 3;
        }
    }
};

/*
void swap(Concursante& a, Concursante& b) {
    Concursante temp = a;
    a = b;
    b = temp;
}

int elegirConcursanteIndex(vector<Concursante>& concursantes, int endIndex) {
    int maxIndex = 0;
    float fuerza_max = -1;
    float fuerza;
    for (int i = 1; i <= endIndex; i++) {
        float fuerza = concursantes[i].getFuerza();
        if (fuerza > fuerza_max) {
            maxIndex = i;
            fuerza_max = fuerza;
        }
    }
    return maxIndex;
}

void trieConcursantes(vector<Concursante>& concursantes, int endIndex) {
    if (endIndex <= 0) {
        return;
    }
    int maxIndex = elegirConcursanteIndex(concursantes, endIndex);
    swap(concursantes[maxIndex], concursantes[endIndex]);
    trieConcursantes(concursantes, endIndex - 1);
}
*/

// le tri décroissant
bool triDecroissant(Concursante& a, Concursante& b) {
    return a.getFuerza() > b.getFuerza();
}

// Crear equipos equilibrados
void creaEquiposVoraz(vector<Concursante> concursantes, vector<Concursante>& equipo1, vector<Concursante>& equipo2){
    if(concursantes.size() < 2){
        cout << "No es possible de jugar con menos de 2 concursantes" << endl;
        return;
    }
    equipo1.push_back(concursantes[0]);
    equipo2.push_back(concursantes[1]);
    float fuerzaTotalEquipo1 = concursantes[0].getFuerza();
    float fuerzaTotalEquipo2 = concursantes[1].getFuerza();
    int i = 2;
    while(i < concursantes.size()){
        float fuerza = concursantes[i].getFuerza();

        if(fuerzaTotalEquipo2 <= fuerzaTotalEquipo1){
            equipo2.push_back(concursantes[i]);
            fuerzaTotalEquipo2 += concursantes[i].getFuerza();
        }
        else{
            equipo1.push_back(concursantes[i]);
            fuerzaTotalEquipo1 += concursantes[i].getFuerza();
        }
        i++;
    }
}

// Fonction principale
int main() {

    vector<Concursante> concursantes;
    vector<Concursante> equipo1;
    vector<Concursante> equipo2;

    // rellenamos nuestra lista de competidores
    concursantes.push_back(Concursante(1, 32, 70.5, true));
    concursantes.push_back(Concursante(2, 45, 68.2, false));
    concursantes.push_back(Concursante(3, 28, 80.3, true));
    concursantes.push_back(Concursante(4, 50, 65.7, false));
    concursantes.push_back(Concursante(5, 35, 72.1, true));
    concursantes.push_back(Concursante(6, 42, 69.8, false));
    concursantes.push_back(Concursante(7, 31, 73.6, true));
    concursantes.push_back(Concursante(8, 47, 66.4, false));
    concursantes.push_back(Concursante(9, 26, 78.9, true));
    concursantes.push_back(Concursante(10, 39, 71.2, false));


    // Ordenamos la lista de competidores por su fuerza, aquí he usado el método sort() porque era más rápido, 
    // pero también tengo la funcion trieConcursante con las funciónes elegirConcursanteIndex y swap para ordenar competidores sin usar la función sort().
    // trieConcursante(concursantes, concursantes.size());
    sort(concursantes.begin(), concursantes.end(), triDecroissant);

    // Ejecucion del algoritmo Greedy
    creaEquiposVoraz(concursantes, equipo1, equipo2);

    cout << "El tamano del equipo 1 es de " << equipo1.size() << endl;
    cout << "El tamano del equipo 2 es de " << equipo2.size() << endl;

    float fuerzaTotalEquipo1 = 0;
    float fuerzaTotalEquipo2 = 0;

    for(Concursante c: equipo1){
        fuerzaTotalEquipo1 += c.getFuerza();
    }
    cout << endl;
    for(Concursante c: equipo2){
        fuerzaTotalEquipo2 += c.getFuerza();
    }

    // Print de los resultados final para comparar la fuerza de los 2 equipos
    cout << "La fuerza total del equipo 1 es de: " << fuerzaTotalEquipo1 << endl;
    cout << "La fuerza total del equipo 2 es de: " << fuerzaTotalEquipo2 << endl;

    return 0;

    // 2 entités dans le problème: l'objet Personne représentant un joueur et un vecteur de Personne représentant une équipe.

    // Prendre le plus grand le mettre dans équipe 1
    // Prendre le plus grand suivant le mettre dans équipe 2
    // Prendre le plus grand suivant le mettre dans équipe 2
    // Si équipe 1 tjr plus fort
    // Mettre dans équipe 2
    // Sinon mettre dans équipe 1
    // On vérifie le résultat en comparant la force des deux équipes
}
