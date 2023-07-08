#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ostream>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::copy;
using std::fixed;
using std::ios;
using std::left;
using std::right;
using std::showpoint;

using std::setw;
using std::setprecision;

using std::string;

using std::fstream;

//Metodo de impresion
void impresion(int , string , string); 

//Clase Base
class PACIENTE{
    protected:
        char nombre[20];
        int edad;
        char especialidad[20];
        int relativo;
    
    public:
        // Métodos getters y setters

        void setRelativo(int nuevoRelativo){
            relativo = nuevoRelativo;
        }

        void setNombre (string Nombre){    // Ya que estamos trabajando con con archvos binarios, este metodo nos sirve para que los registros tengan el mismo tamano
            int longitud = Nombre.size();
            longitud = (longitud < 25 ? longitud : 24);
            Nombre.copy(nombre, longitud);
            Nombre[longitud] = '\0';
        }

        void setEspecialidad(string Especialidad){
            int longitud = Especialidad.size();
            longitud = (longitud < 25 ? longitud : 24);
            Especialidad.copy(especialidad, longitud);
            Especialidad[longitud] = '\0';
        }


        void setEdad(int nuevaEdad){
            nuevaEdad = edad;
        }

        
        int getRelativo() {
            return relativo;
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
        //Metodo Constructor de la clase base
        PACIENTE(int VRelativo = 0, string VNombre = "",  string VEspecialidad = "",int VEdad = 0 ){
            setRelativo(VRelativo);
            setNombre(VNombre);
            setEspecialidad(VEspecialidad);
            setEdad(VEdad);

        }

};

//Clases derivadas
class ATENCIONP : public PACIENTE{
    private: 
        bool preferencial;
    
    public: 
        ATENCIONP(int VRelativo , string VNombre ,  string VEspecialidad ,int VEdad , bool newPreferencial) : PACIENTE(VRelativo = 0, VNombre = "",VEspecialidad = "",VEdad = 0){
            preferencial = newPreferencial;
            cout << "Atencion preferencial!" << endl;
        }

};

class HISTORIAL : public PACIENTE{
    private:
        char folio[20];
    
    public:
        // Métodos set y get
        void setFolio(string nuevoFolio){
            int longitud = nuevoFolio.size();
            longitud = (longitud < 25 ? longitud : 24);
            nuevoFolio.copy(folio, longitud);
            nuevoFolio[longitud] = '\0';
        }

        string getFolio(){
            return folio;
        }


   
        HISTORIAL(int VRelativo, string VNombre,  string VEspecialidad, int VEdad, string VFolio) : PACIENTE(VRelativo = 0, VNombre = "",VEspecialidad = "",VEdad = 0){
            setFolio(folio);
            
        }

};

class CITAS : public PACIENTE{
    private:
        char turno[20];
        char fec_cita[20];
    
    public:
       
            void setTurno(string Turno){
                int longitud = Turno.size();
                longitud = (longitud < 25 ? longitud : 24);
                Turno.copy(turno, longitud);
                Turno[longitud] = '\0';
        }

            void setFecha(string Fecha){
                int longitud = Fecha.size();
                longitud = (longitud < 25 ? longitud : 24);
                Fecha.copy(fec_cita, longitud);
                Fecha[longitud] = '\0';
            }

            string getTurno(){
                return turno;
        }

            string getFecha(){
                return fec_cita;
            }

        CITAS(int VRelativo, string VNombre, string VEspecialidad,int VEdad, string VFec_cita) :  PACIENTE(VRelativo = 0, VNombre = "",VEspecialidad = "",VEdad = 0){
            setFecha(VFec_cita);
         }
           
        
};

int main() {
    int VRelativo, opcion, relativoBuscar, VEdad;
    string VNombre, VEspecialidad, VFec_cita, nuevaEspecialidad;
    char res = 'S', confirmacion;
    bool encontrado;

    fstream ListaPacientes("Pacientes.dat",  ios::in | ios::out | ios::binary);

   

    while ((res == 'S') || (res == 's')) {
        cout << " 1. Ingreso de pacientes" << endl;
        cout << " 2. Leer lista de pacientes" << endl;        
        cout << " 3. Informacion de pacientes" << endl;
        cout << " 4. Actualizacion de pacientes" << endl;
        cout << " 5. Borrado de pacientes" << endl;
        cout << " Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                {
                    cout << "=========================================" << endl;
                    
                    cout << "Ingrese relativo(codigo) del paciente: " ;
                    cin >> VRelativo;
                    cout << "\nIngrese nombre del paciente: ";
                    cin >> VNombre;
                    cout << "\nIngrese especialidad del paciente: ";
                    cin >> VEspecialidad;
                    cout << "\nIngrese la edad del paciente: ";
                    cin >> VEdad;

                    PACIENTE PaNuevo(VRelativo, VNombre, VEspecialidad, VEdad);

                    ListaPacientes.clear();
                    ListaPacientes.seekp(0, ios::beg);


                    ListaPacientes.seekp((PaNuevo.getRelativo()-1)*sizeof(PACIENTE), ios::beg);

                    ListaPacientes.write(reinterpret_cast <const char *>(&PaNuevo), sizeof(PACIENTE));
                    if (VEdad >= 65)
                    {
                        cout << " " << endl;
                        cout << "Atencion preferencial!!" << endl;

                    }else{
                        cout << " " << endl;
                        cout <<"No tiene atencion preferencial!!"<< endl;
                    }
                    cout << " " << endl;
                    cout << "Registro ingresado correctamente!!\n";

                }
                break;
            case 2:
                {
                    cout << " Leer lista de pacientes" << endl; 
                    cout << left << setw(10) << "Relativo" << setw(10) << "Nombre" << left << setw(10) << "Espacialidad" << endl;

                    PACIENTE pacienteLeer;                    

                    ListaPacientes.clear();
                    ListaPacientes.seekg(0, ios::beg);

                    ListaPacientes.read(reinterpret_cast <char *>(&pacienteLeer), sizeof(PACIENTE) );
                    int at_Pref = 0;
                    int no_pref = 0;
                    while (ListaPacientes && !ListaPacientes.eof()){
                        if (pacienteLeer.getRelativo() != 9999){                        
                        impresion(pacienteLeer.getRelativo(), pacienteLeer.getNombre(), pacienteLeer.getEspecialidad());
                        }
                        ListaPacientes.read(reinterpret_cast <char *>(&pacienteLeer), sizeof(PACIENTE) );                          
                        
                        if (VEdad>=65){ 
                           ((VEdad>=65) ? at_Pref++:no_pref++);                           
                        }

                    }
                    cout << "El total es de " << at_Pref << " pacientes para atencion preferencial!" << endl; 

                }
                break;                 
            case 3:
                {
                    cout << " Consulta de pacientes " << endl;
                    cout << "Ingrese el relativo a buscar: " << endl;
                    cin >> relativoBuscar;


                    PACIENTE PacienteBuscar;

                    ListaPacientes.clear();
                    ListaPacientes.seekg(0, ios::beg);

                    ListaPacientes.seekg((relativoBuscar-1)*sizeof(PACIENTE));
                    cout << fixed << showpoint;
                    ListaPacientes.read(reinterpret_cast <char *>(&PacienteBuscar), sizeof(PACIENTE) );          

                    

                    if(PacienteBuscar.getRelativo() == 9999){
                    cout << "No se ha almacenado informacion para ese relativo!" << endl;
                    }else{
                        cout << "Los datos son: " << endl;
                        impresion( PacienteBuscar.getRelativo(), PacienteBuscar.getNombre(), PacienteBuscar.getEspecialidad());
                    }
                    cout << "Fin de la busqueda!" << endl; 

                }
                break;                
            case 4:
                {
                    cout << " Actualizacion de paciente" << endl;    

                    cout << "Ingrese el relativo a buscar: " << endl;
                    cin >> relativoBuscar;


                    PACIENTE PacienteBuscar;

                    ListaPacientes.clear();
                    ListaPacientes.seekg(0, ios::beg);

                    ListaPacientes.seekg((relativoBuscar-1)*sizeof(PACIENTE));

                    cout << fixed << showpoint;
                    ListaPacientes.read(reinterpret_cast <char *>(&PacienteBuscar), sizeof(PACIENTE) );
                

                    cout << "Los datos son: " << endl;
                    if(PacienteBuscar.getRelativo() == 9999){
                    cout << "No se ha almacenado informacion para ese relativo!" << endl;
                    }
                    else{
                         impresion(PacienteBuscar.getRelativo(), PacienteBuscar.getNombre(), PacienteBuscar.getEspecialidad());
                         cout << "Ingrese la nueva especialidad: " ;
                         cin >> nuevaEspecialidad;
                         PacienteBuscar.setEspecialidad(nuevaEspecialidad);
                         ListaPacientes.seekp( (PacienteBuscar.getRelativo() - 1) * sizeof(PACIENTE));  
                         ListaPacientes.write(reinterpret_cast <const char *>(&PacienteBuscar), sizeof(PACIENTE));
                         cout << "Datos del paciente " << PacienteBuscar.getRelativo() << " han sido actualizados! " << endl;
                    }
                    


                }                    
                break;                
            case 5:
                {
                    cout << " Eliminacion de paciente" << endl; 

                    cout << "Ingrese el relativo del paciente a eliminar : " << endl;
                    cin >> relativoBuscar;

                    
                    ListaPacientes.clear();
                    ListaPacientes.seekg(0, ios::beg);

                    ListaPacientes.seekg((relativoBuscar-1)*sizeof(PACIENTE));

                    cout << fixed << showpoint;
                    PACIENTE PacienteBuscar;

                    ListaPacientes.read(reinterpret_cast <char *>(&PacienteBuscar), sizeof(PACIENTE) );

                    if (PacienteBuscar.getRelativo() == relativoBuscar) {
                        cout << "Los datos son: " << endl;
                        impresion(PacienteBuscar.getRelativo(), PacienteBuscar.getNombre(), PacienteBuscar.getEspecialidad());
                        encontrado = true;
                    }
                    else{
                        encontrado = false;
                    }

                    if(encontrado){
                        cout << "Seguro de confirmar la eliminacion (S/N) ? " ;
                        cin >> confirmacion;
                        if ((confirmacion == 'S') || (confirmacion == 's')) {
                            ListaPacientes.seekp( (relativoBuscar - 1) * sizeof(PACIENTE));
                             PACIENTE PacienteVacio(9999,"XXXX", "XXXX", 130);
                            ListaPacientes.write(reinterpret_cast <const char *>(&PacienteVacio), sizeof(PACIENTE));
                            cout << "\nPaciente ha sido eliminado!" << endl;
                        }
                        else{
                            cout << "\nPaciente no ha sido eliminado!" << endl;
                        }


                    }
                    else{
                        cout << " Registro no encontrado " << endl;
                    }
                }
                break;
            default:
                {
                    cout << "Opcion No Valida!" << endl;
                    res = 'S';
                }
                break;
        }

        if ((opcion >=1 ) && (opcion <= 5)) {
            cout << "Desea continuar? (S/N)" << endl;
            cin >> res;
        }

    }

    ListaPacientes.close();
    return 0;
}

void impresion(int relativoImprimir, string nombreImprimir, string especialidadImprimir) {
    cout << left << setw(10) << relativoImprimir  << setw(13) << nombreImprimir << setw(12) << setprecision(2) << left << especialidadImprimir << endl ;    
}
