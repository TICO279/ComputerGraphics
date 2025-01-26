#ifndef VEC3_H
#define VEC3_H
#include <ostream>

using namespace std;

class VEC3
{
    public:

        double x,y,z;

        VEC3();
        VEC3(double x, double y, double z);
        VEC3(const VEC3& v);
        virtual ~VEC3();
        void copia(VEC3 v);
        double norma();
        VEC3 unitario();
        void acumula(VEC3 v);

        friend std::ostream& operator << ( std::ostream&, VEC3&);

        friend VEC3 operator +(VEC3 a, VEC3 b);
        friend VEC3 operator -(VEC3 a, VEC3 b);
        friend VEC3 operator *(VEC3 v, double a);

    protected:


    private:
};



#endif // VEC3_H
