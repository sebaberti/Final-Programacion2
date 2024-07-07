#include<iostream>
#include <cstring>
#include <cstdlib>

using namespace std;



void cargarCadena(char *pal, int tam)
{
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Fecha
{
private:
    int dia,mes, anio;
public:
    void Cargar()
    {
        cout << endl;
        cout << "DIA: ";
        cin>>dia;
        cout << "MES: ";
        cin>>mes;
        cout << "ANIO: ";
        cin>>anio;
    }

    void Mostrar()
    {
        cout<<dia<<"/";
        cout<<mes<<"/";
        cout<<anio<<endl;
    }
    int getDia()
    {
        return dia;
    }
    int getMes()
    {
        return mes;
    }
    int getAnio()
    {
        return anio;
    }

    void setDia(int d)
    {
        dia=d;
    }
    void setMes(int m)
    {
        mes=m;
    }
    void setAnio(int a)
    {
        anio=a;
    }

};


class RecuLunes
{
private:
    int _codigo;
    char _nombreYapellido[30];
    int _dni;
    Fecha _fechaNacimiento;
    float _deuda;
    int _puesto; //(1 a 10)
    bool _estado;

public:

    int getCodigo() const
    {
        return _codigo;
    }

    const char* getNombreYApellido() const
    {
        return _nombreYapellido;
    }

    int getDni() const
    {
        return _dni;
    }

    Fecha getFechaNacimiento() const
    {
        return _fechaNacimiento;
    }

    float getDeuda() const
    {
        return _deuda;
    }

    int getPuesto() const
    {
        return _puesto;
    }

    bool getEstado() const
    {
        return _estado;
    }


    void setCodigo(int codigo)
    {
        _codigo = codigo;
    }

    void setNombreYApellido(const char* nombre)
    {
        strcpy(_nombreYapellido, nombre);
    }

    void setDni(int dni)
    {
        _dni = dni;
    }

    void setFechaNacimiento(Fecha fecha)
    {
        _fechaNacimiento = fecha;
    }

    void setDeuda(float deuda)
    {
        _deuda = deuda;
    }

    void setPuesto(int puesto)
    {

        if (puesto >= 1 && puesto <= 10)
        {
            _puesto = puesto;
        }
        else
        {
            cout << " El puesto debe estar entre 1 y 10" << endl;
        }
    }

    void setEstado(bool estado)
    {
        _estado = estado;
    }


    void Cargar(int cod)
    {
        if(cod == -1)
        {
            cout << "CODIGO: ";
            cin >> _codigo;
        }
        else
        {
            _codigo = cod;
        }
        cout<<"NOMBRE Y APELLIDO: ";
        cargarCadena(_nombreYapellido,29);
        cout<<"DNI: ";
        cin>>_dni;
        cout<<"FECHA: ";
        _fechaNacimiento.Cargar();
        cout<<"DEUDA: ";
        cin>>_deuda;
        cout<<"PUESTO: ";
        cin>>_puesto;
        while (_puesto < 1 || _puesto > 10)
        {
            cout << "El puesto debe estar entre 1 y 10" << endl;
            cout << "PUESTO: ";
            cin >> _puesto;
        }
        _estado=true;
    }

    void Mostrar()
    {
        cout<<_codigo<<endl;
        cout<<_nombreYapellido<<endl;
        cout<<_dni<<endl;
        _fechaNacimiento.Mostrar();
        cout<<_deuda<<endl;
        cout<<_puesto<<endl;
        if(_estado==false) cout<<"BORRADO"<<endl;
    }


    bool operator ==(int codigo) const
    {
        if(_codigo == codigo) return true;
        return false;
    }

};





class ArchivoRec
{
private:
    char nombre[30];
public:
    ArchivoRec(const char *n="reclunes.dat") ///cambiar las comillas si no compila!!!!!
    {
        strcpy(nombre, n);
    }

    RecuLunes leerRegistro(int pos)
    {
        RecuLunes reg;
        reg.setEstado(false);
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }

    int contarRegistros()
    {
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(RecuLunes);
    }

    bool grabarRegistro(RecuLunes reg)
    {
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        int escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }



    bool reemplazarRegistro(RecuLunes obj, int posAreeemplazar)
    {
        FILE *p;
        p = fopen("reclunes.dat","rb+");
        if(p==NULL)
        {
            cout << "No se pudo abrir el archivo " << endl;
            exit(1);
        }
        fseek(p, posAreeemplazar * sizeof obj, 0 );
        bool pudoEscribir = fwrite(&obj, sizeof obj,1,p);
        fclose(p);
        return pudoEscribir;
    }


    int buscarRegistro(int num)
    {
        FILE *p;
        RecuLunes obj;
        p = fopen("reclunes.dat","rb");
        int pos = 0;

        if(p == NULL)
        {
            return -1;
        }
        while(fread(&obj, sizeof obj, 1, p)== 1)
        {
            if(obj.getCodigo() == num )
            {
                fclose(p);
                return pos;
            }
            pos++;
        }
        fclose(p);
        return -2;
    }
};



void altaPaciente()
{
    RecuLunes reg;
    ArchivoRec archiPac("reclunes.dat");
    int cod,pos;

    cout << "INGRESE EL CODIGO: " <<endl;
    cin >> cod;

    pos = archiPac.buscarRegistro(cod);

    while(pos >= 0)
    {
        cout << "YA EXISTE UN REGISTRO CON ESE CODIGO, INGRESE OTRO:"<<endl;
        cout << "CODIGO: " << endl;
        cin >> cod;
        pos = archiPac.buscarRegistro(cod);
    }

    reg.Cargar(cod);
    archiPac.grabarRegistro(reg);
}

void modificarFecha()
{
    RecuLunes objPac;
    ArchivoRec objArRec("reclunes.dat");

    int tam = objArRec.contarRegistros();


    int _codigoModificar;
    cout << "Ingrese el ccdigo del paciente que desea modificar: ";
    cin >> _codigoModificar;


    for (int i = 0; i < tam; i++)
    {

        objPac = objArRec.leerRegistro(i);

        if (objPac == _codigoModificar)
        {
            Fecha nuevaFecha;
            cout << "Ingrese la neuva fecha: " <<endl;
            nuevaFecha.Cargar();

            objPac.setFechaNacimiento(nuevaFecha);

            if (objArRec.reemplazarRegistro(objPac, i))
            {
                cout << "se modico el registro del paciente " << objPac.getNombreYApellido() << endl;
            }
        }
    }

}


void mostrarConVector()
{
    ArchivoRec objArPac("reclunes.dat");


    int tam = objArPac.contarRegistros();


    if(tam <= 0 )
    {
        cout << "El archivo esta vacio" << endl;
        return;
    }

    RecuLunes *vectorDinamico = new RecuLunes[tam];

    if(vectorDinamico == NULL)
    {
        cout << "No se pudo asignar memoria" << endl;
        return exit(-1);
    }

    for(int i = 0; i < tam; i++)
    {
        vectorDinamico[i] = objArPac.leerRegistro(i);
    }


    for (int j = 0; j < tam; j++)
    {

        vectorDinamico[j].Mostrar();
        cout << endl;
    }

    delete []vectorDinamico;
}

void Menu()
{
    ArchivoRec objArPac("reclunes.dat");
    while(true)
    {
        int opc;
        system("cls");
        cout<<"MENU PRINCIPAL"<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<"1 -Dar de alta registro "<<endl;
        cout<<"2 -Modificar registro "<<endl;
        cout<<"3 -Listar archivo con vector dinamico  "<<endl;
        cout<<"----------------------------------------"<<endl;
        cout<<"INGRESE LA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc)
        {
        case 1:
            altaPaciente();
            break;
        case 2:
            modificarFecha();
            break;
        case 3:
            mostrarConVector();
            break;
        case 0:
            return ;
        default:
            cout<<"LA OPCION INGRESADA NO ES CORRECTA"<<endl;
            break;
        }
        system("pause");
    }
}



int main()
{
    Menu();
    return 0;
}
