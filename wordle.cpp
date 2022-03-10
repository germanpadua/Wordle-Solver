#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Wordle
{
private:
    int colores[5];
    string palabra_anterior;
    string candidatas_1[1000];
    string candidatas_2[1000];
    string candidatas_3[1000];
    string candidatas_4[1000];
    string candidatas_5[1000];
    string candidatas_6[1000];
    string candidatas_7[1000];
    string candidatas_8[1000];

    int tamanio_candidatas_1;
    int tamanio_candidatas_2;
    int tamanio_candidatas_3;
    int tamanio_candidatas_4;
    int tamanio_candidatas_5;
    int tamanio_candidatas_6;
    int tamanio_candidatas_7;
    int tamanio_candidatas_8;

    void encontrar_verdes(int v[], int &tamanio)
    {
        tamanio = 0;
        int pos = 0;
        for (int i = 0; i < 5; i++)
        {
            if (colores[i] == 1)
            {
                v[pos] = i;
                tamanio++;
                pos++;
            }
        }
    }

    void encontrar_grises(int v[], int &tamanio)
    {
        tamanio = 0;
        int pos = 0;
        for (int i = 0; i < 5; i++)
        {
            if (colores[i] == 0)
            {
                v[pos] = i;
                tamanio++;
                pos++;
            }
        }
    }

    void encontrar_amarillos(int v[], int &tamanio)
    {
        tamanio = 0;
        int pos = 0;
        for (int i = 0; i < 5; i++)
        {
            if (colores[i] == 2)
            {
                v[pos] = i;
                tamanio++;
                pos++;
            }
        }
    }

public:
    Wordle()
    {
        ifstream in;
        //in.open("diccionario5Letras.txt");
        in.open("diccionario5Letras.txt");
        int i = 0;
        string palabra;
        tamanio_candidatas_1 = 0;
        tamanio_candidatas_2 = 0;
        tamanio_candidatas_3 = 0;
        tamanio_candidatas_4 = 0;
        tamanio_candidatas_5 = 0;
        tamanio_candidatas_6 = 0;
        tamanio_candidatas_7 = 0;
        tamanio_candidatas_8 = 0;

        while (!in.eof())
        {
            in >> palabra;

            if (tamanio_candidatas_1 < 1000)
            {
                candidatas_1[tamanio_candidatas_1] = palabra;
                tamanio_candidatas_1++;
            }
            else if (tamanio_candidatas_2 < 1000)
            {
                candidatas_2[tamanio_candidatas_2] = palabra;
                tamanio_candidatas_2++;
            }
            else if (tamanio_candidatas_3 < 1000)
            {
                candidatas_3[tamanio_candidatas_3] = palabra;
                tamanio_candidatas_3++;
            }
            else if (tamanio_candidatas_4 < 1000)
            {
                candidatas_4[tamanio_candidatas_4] = palabra;
                tamanio_candidatas_4++;
            }
            else if (tamanio_candidatas_5 < 1000)
            {
                candidatas_5[tamanio_candidatas_5] = palabra;
                tamanio_candidatas_5++;
            }
            else if (tamanio_candidatas_6 < 1000)
            {
                candidatas_6[tamanio_candidatas_6] = palabra;
                tamanio_candidatas_6++;
            }
            else if (tamanio_candidatas_7 < 1000)
            {
                candidatas_7[tamanio_candidatas_7] = palabra;
                tamanio_candidatas_7++;
            }
            else if (tamanio_candidatas_8 < 1000)
            {
                candidatas_8[tamanio_candidatas_8] = palabra;
                tamanio_candidatas_8++;
            }
        }

        in.close();

        for (int i = 0; i < 5; i++)
        {
            colores[i] = 0;
        }
    }

    void asignar_colores()
    {
        int a;
        cout << "Introduzca la palabra introducida: ";
        cin >> palabra_anterior;

        cout << "Introduzca los colores de la palabra (0 gris, 1 verde, 2 amarillo): ";

        for (int i = 0; i < 5; i++)
        {
            cin >> colores[i];
        }

        update();
    }

    void update_candidatas(string candidatas[], int &tam)
    {

        int verde[5], tamanio_verde;
        int gris[5], tamanio_gris;
        int amarillo[5], tamanio_amarillo;
        string aux;
        encontrar_verdes(verde, tamanio_verde);
        encontrar_grises(gris, tamanio_gris);
        encontrar_amarillos(amarillo, tamanio_amarillo);

        bool salir;
        bool esta_verde;
        bool esta_amarillo;
        bool esta_en_la_palabra;
        int pos_verde;

        for (int i = 0; i < tam; i++)
        {

            for (int j = 0; j < tamanio_verde; j++)
            {

                if (palabra_anterior[verde[j]] != (candidatas[i])[verde[j]])
                {
                    aux = candidatas[tam - 1];

                    candidatas[tam - 1] = candidatas[i];

                    candidatas[i] = aux;

                    tam--;

                    i--;

                    break;
                }
            }
        }

        for (int i = 0; i < tam; i++)
        {
            salir = false;

            for (int j = 0; j < tamanio_amarillo && !salir; j++)
            {
                esta_verde = false;

                pos_verde = -1;

                for (int l = 0; l < tamanio_verde && !esta_verde; l++)
                {
                    if (palabra_anterior[amarillo[j]] == palabra_anterior[verde[l]]){
                        esta_verde = true;
                        pos_verde = verde[l];
                    }
                }

                esta_en_la_palabra = false;
                 
                for (int l = 0; l < candidatas[i].size(); l++)
                {

                    if (candidatas[i][l] == palabra_anterior[amarillo[j]] && l != pos_verde && l != amarillo[j])
                    {
                        esta_en_la_palabra = true;
                    }
                }

                if (!esta_en_la_palabra)
                {

                    aux = candidatas[tam - 1];

                    candidatas[tam - 1] = candidatas[i];

                    candidatas[i] = aux;

                    tam--;

                    i--;
                    break;
                }
            }
        }

        for (int i = 0; i < tam; i++)
        {
            salir = false;

            for (int j = 0; j < tamanio_gris && !salir; j++)
            {

                for (int k = 0; k < candidatas[i].size() && !salir; k++)
                {
                    esta_verde = false;
                    esta_amarillo = false;
                    pos_verde = -1;

                    for (int l = 0; l < tamanio_verde && !esta_verde; l++)
                    {
                        if (candidatas[i][k] == palabra_anterior[verde[l]]){
                            esta_verde = true;
                            pos_verde = verde[l];
                        }  
                    }


                    for (int l = 0; l < tamanio_amarillo && !esta_amarillo; l++)
                    {
                        if (candidatas[i][k] == palabra_anterior[amarillo[l]])
                            esta_amarillo = true;
                    }

                    if ((candidatas[i]==palabra_anterior) || (candidatas[i][k] == palabra_anterior[gris[j]] && !esta_verde && !esta_amarillo) || (candidatas[i][k] == palabra_anterior[gris[j]] && esta_verde && !esta_amarillo && k != pos_verde))
                    {
                        aux = candidatas[tam - 1];

                        candidatas[tam - 1] = candidatas[i];

                        candidatas[i] = aux;

                        tam--;

                        i--;

                        salir = true;
                    }
                }
            }
        }
    }

    void update()
    {
        update_candidatas(candidatas_1, tamanio_candidatas_1);
        update_candidatas(candidatas_2, tamanio_candidatas_2);
        update_candidatas(candidatas_3, tamanio_candidatas_3);
        update_candidatas(candidatas_4, tamanio_candidatas_4);
        update_candidatas(candidatas_5, tamanio_candidatas_5);
        update_candidatas(candidatas_6, tamanio_candidatas_6);
        update_candidatas(candidatas_7, tamanio_candidatas_7);
        update_candidatas(candidatas_8, tamanio_candidatas_8);
    }

    string candidata()
    {
        if (tamanio_candidatas_1 > 0)
            return candidatas_1[0];
        else if (tamanio_candidatas_2 > 0)
            return candidatas_2[0];
        else if (tamanio_candidatas_3 > 0)
            return candidatas_3[0];
        else if (tamanio_candidatas_4 > 0)
            return candidatas_4[0];
        else if (tamanio_candidatas_5 > 0)
            return candidatas_5[0];
        else if (tamanio_candidatas_6 > 0)
            return candidatas_6[0];
        else if (tamanio_candidatas_7 > 0)
            return candidatas_7[0];
        else if (tamanio_candidatas_8 > 0)
            return candidatas_8[0];
        else
            return "no hay candidatas";
    }
};

void find_5_letter_words(vector<string> diccionario, vector<string> &resultado);

void quitar_tildes(const vector<string> diccionario, vector<string> &resultado);

int main()
{
    /*
    ifstream in;
    ofstream out;

    in.open("diccionarioIngles.txt");
    out.open("diccionarioIngles5Letras.txt");

    vector<string> diccionario;
    vector<string> palabras_5;

    string palabra;


    while (!in.eof())
    {
        in >> palabra;
        
        if (palabra.length() == 5 && palabra.find("á") == -1 && palabra.find("é") == -1 && palabra.find("í") == -1 && palabra.find("ó") == -1 && palabra.find("ú") == -1 && palabra.find("ñ") == -1)
        {
            out << palabra << endl;

        }
    }


    in.close();
    out.close();

    
*/
    Wordle juego;

    for (int i = 0; i < 5; i++)
    {

        juego.asignar_colores();

        cout << "Pruebe: " << juego.candidata() << endl;
    }
}
