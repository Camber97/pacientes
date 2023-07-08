#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cerr;
using std::ios;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;


class PACIENTE{
    protected:
        char nombre[20];
        int edad;
        char especialidad[20];
        int relativo;
    
    public:
        void setNombre (string Nombre){    
            int longitud = Nombre.size();
            longitud = (longitud < 25 ? longitud : 24);
            Nombre.copy(nombre, longitud);
            Nombre[longitud] = '\0';
        }

        void setEdad(int nuevaEdad){
            nuevaEdad = edad;
        }

        void setEspecialidad(string Especialidad){
            int longitud = Especialidad.size();
            longitud = (longitud < 25 ? longitud : 24);
            Especialidad.copy(especialidad, longitud);
            Especialidad[longitud] = '\0';
        }

        int getRelativo() {
            return relativo;
        }

        void setRelativo(int nuevoRelativo){
            relativo = nuevoRelativo;
        }

        string getNombre() {
            return nombre;
        }

        string getEspecialidad(){
            return especialidad;
        }

        int getEdad() {
            return edad;
        }

        PACIENTE(int VRelativo = 0, string VNombre = "", string VEspecialidad = "",int VEdad = 0 ){
            setRelativo(VRelativo);
            setNombre(VNombre);
            setEspecialidad(VEspecialidad);
            setEdad(VEdad);
            
            
        }

};


int main() {

    PACIENTE PacienteVacio(9999,"XXXX", "XXXX", 130);

    ofstream ListaPacientes("Pacientes.dat", ios::out | ios::binary);   

    if (!ListaPacientes) {
        cerr << "No se puede abrir el archivo!";
        return 1;
    }   
    
    for (int i=0; i< 100; i++) {
       
        ListaPacientes.write(reinterpret_cast <const char *>(&PacienteVacio), sizeof(PACIENTE));
    }

    ListaPacientes.close();
    cout << "Archivo binario cerrado " << endl;

    return 0;
} 