
//#include "linmath.h"
#include "VEC3.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace  std;

double G = 6.6743E-11; // Nw * m2 / Kg2

/*
struct VERTICE
{
    float x, y, z;
    float r, g, b;
};

*/

float o = 0.4f;

class Movil
{
    //private:

    public:
     string nombre;
     double masa;

     VEC3 r;
     VEC3 v;
     VEC3 a;
     VEC3 fza;

  Movil(string unNombre,double unaMasa, VEC3 pos, VEC3 vel)
  {
   nombre = unNombre;
   masa   = unaMasa;

   r.copia(pos);
   v.copia(vel);
  }

  ~Movil()
  {

  }

  Movil(const Movil& other)
  {
    //copy ctor
  }

  void limpiaFza()
  {
      fza.x = 0.0;
      fza.y = 0.0;
      fza.z = 0.0;
  }

  void interactua(Movil *movil)
  {
      VEC3 dr, u, fuerza;
      double mag_dr2, mag_dr, mag_fza;

      dr =  movil->r - this->r;
      u  = dr.unitario();
      mag_dr = dr.norma();
      mag_dr2 = mag_dr * mag_dr;

      mag_fza = G * masa * movil->masa / mag_dr2;

      fuerza = u * mag_fza;

      this->fza.acumula(fuerza);
      fuerza = fuerza * -1.0;
      movil->fza.acumula(fuerza);
  }

  void mueve(float deltaT)
  {
      VEC3 delta_v, delta_r;

      a = fza * (1.0/masa);
      delta_v = a * deltaT;
      v.acumula(delta_v);
      delta_r = v * deltaT;
      r.acumula(delta_r);
  }

  void impFza()
  {
      cout << nombre << ",    fuerza:["  << fza <<"]" << endl;
  }



  friend ostream& operator <<( ostream& s, Movil & m )
  {
    s << m.nombre << ", masa:" << m.masa
      << ", posicion:["  << m.r <<"]"
      << ", velocidad:[" << m.v <<"]";

    return s;
  }

};

/*

  VERTICE* creaTrayectoria(float a, int M, int N)
  {
      auto format = [](std::ostream& os) -> std::ostream&
          {
              return os << fixed << setprecision(2) << setw(9) << setfill(' ');
          };


      float x, y, z;
      float r_yz;

      VERTICE* vertices = (VERTICE*)malloc(M * sizeof(VERTICE));

      VEC3 pos_1 = { 0.0,0.0,0.0 };
      VEC3 vel_1 = { 0.0,0.0,0.0 };

      VEC3 pos_2 = { 384.403E6,0.0,0.0 };
      VEC3 vel_2 = { 0.0,946.6322,0.0 };

      double deltaT = 1.0 * 3600; //segundos en una hora
      double t_horas;

      Movil mov_1("Tierra", 5.9736E24, pos_1, vel_1);
      Movil mov_2("  Luna", 7.35E22, pos_2, vel_2);

      cout << mov_1 << endl;
      cout << mov_2 << endl;

      t_horas = 0.0f;
      int k = 0;
      while (t_horas / 24.0 < 29.6)
      {
          t_horas += deltaT / 3600;

          mov_1.limpiaFza();
          mov_2.limpiaFza();

          mov_1.interactua(&mov_2);

          mov_1.mueve(deltaT);
          mov_2.mueve(deltaT);

          x = (float)mov_2.r.x;
          y = (float)mov_2.r.y;
          z = (float)mov_2.r.z;

          //mov_2.impFza();

          VEC3 dr;
          float radio;
          dr = mov_2.r - mov_1.r;;
          radio = dr.norma();

          
          vertices[k].x = x*(1/4.20E8);
          vertices[k].y = y * (1 / 4.20E8);
          vertices[k].z = z * (1 / 4.20E8);

          vertices[k].r = 1.0; //((double) rand() / (RAND_MAX+1));
          vertices[k].g = 1.0; //((double) rand() / (RAND_MAX+1));
          vertices[k].b = 1.0; //((double) rand() / (RAND_MAX+1));
          
          cout << " Vertices " << format << t_horas / 24.0 << " ... " << mov_1.nombre << " Vertices:  " << " x:" << vertices[k].x << " y:" << vertices[k].y << " z: " << vertices[k].z << endl;

          k++;
          
         
          
          cout << " dias: " << format << t_horas / 24.0 << " ... " << mov_1.nombre << " ... " << " r:" << mov_1.r << " v:" << mov_1.v << " dr: " << dr << endl;
          cout << " dias: " << format << t_horas / 24.0 << " ... " << mov_2.nombre << " ... " << " r:" << mov_2.r << " v:" << mov_2.v << " radio: " << radio << endl;
          

      }
      cout << "Puntos totales:" << k << endl;


      return vertices;
  }
  */


//Este es el main antiguo

 /*
int main(int argc, char *arg[])
{

     auto format = [](std::ostream &os) -> std::ostream&
     {
        return os << fixed << setprecision(2) << setw(9) << setfill(' ');
     };

    cout << "Hola mundo..." << endl;

    VEC3 pos_1 = {0.0,0.0,0.0};
    VEC3 vel_1 = {0.0,0.0,0.0};

    VEC3 pos_2 = {384.403E6,0.0,0.0};
    VEC3 vel_2 = {0.0,946.6322,0.0};

    double deltaT =  1.0 * 3600; //segundos en una hora
    double t_horas;

    Movil mov_1("Tierra",  5.9736E24, pos_1, vel_1);
    Movil mov_2("  Luna"  ,7.35E22,   pos_2, vel_2);

    cout << mov_1 << endl;
    cout << mov_2 << endl;

    t_horas = 0.0f;
    while( t_horas / 24.0 < 29.6 )
    {
        t_horas += deltaT/3600;

        mov_1.limpiaFza();
        mov_2.limpiaFza();

        mov_1.interactua(&mov_2);

        mov_1.mueve(deltaT);
        mov_2.mueve(deltaT);

        //mov_2.impFza();

        VEC3 dr;
        float radio;
        dr = mov_2.r - mov_1.r;;
        radio = dr.norma();
        cout << " dias: " << format << t_horas/24.0 << " ... " << mov_1.nombre << " ... " << " r:" << mov_1.r << " v:" << mov_1.v << " dr: " << dr << endl;
        cout << " dias: " << format << t_horas/24.0 << " ... " << mov_2.nombre << " ... " << " r:" << mov_2.r << " v:" << mov_2.v << " radio: " << radio << endl;


    }



}
*/


  /*
int main(int argc, char* arg[])
{

    int N = 10;
    int M = 2000;

    VERTICE* vertices = creaTrayectoria(o, M, N);
}


*/


