#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Clase Rol
class Rol {
private:
    string descripcion;
    double cambioPago;
public:
    Rol(string desc, double cambio) : descripcion(desc), cambioPago(cambio) {}

    string getDescripcion() {
        return descripcion;
    }

    double getCambioPago() {
        return cambioPago;
    }
};

// Clase Empleado
class Empleado {
protected:
    string nombre;
    int edad;
    string genero;
    int numeroCelular;
    string domicilio;
    vector<Rol> roles;
    int aniosServicio;

public:
    Empleado(string nom, int ed, string gen, int cel, string dom) :
        nombre(nom), edad(ed), genero(gen), numeroCelular(cel), domicilio(dom) {
        // Generamos un número aleatorio entre 1 y 5 para los años de servicio
        aniosServicio = rand() % 5 + 1;
    }

    virtual double calcularSueldo() = 0;
    virtual string getPuesto() = 0;
    void agregarRol(Rol rol) {
        roles.push_back(rol);
    }

    int obtenerTiempoServicio() {
        return aniosServicio;
    }

    virtual string toString() {
        return "Nombre: " + nombre + "\nEdad: " + to_string(edad) + "\nGenero: " + genero +
               "\nAnios de Servicio: " + to_string(aniosServicio);
    }
};

// Clase EmpleadoComun
class EmpleadoComun : public Empleado {
private:
    double sueldoFijo;
    double bonoAnual;

public:
    EmpleadoComun(string nom, int ed, string gen, int cel, string dom, double sueldo, double bono) :
        Empleado(nom, ed, gen, cel, dom), sueldoFijo(sueldo), bonoAnual(bono) {}

    double calcularSueldo() override {
        return sueldoFijo + bonoAnual;
    }

    string getPuesto() override {
        return "Empleado Común";
    }

    string toString() override {
        return Empleado::toString() + "\nPuesto: " + getPuesto() + "\nSueldo: $" + to_string(calcularSueldo());
    }
};

// Clase Jornalero
class Jornalero : public Empleado {
private:
    int horasTrabajadas;
    int horasExtra;
    double valorHora;

public:
    Jornalero(string nom, int ed, string gen, int cel, string dom, int horas, int extra, double valor) :
        Empleado(nom, ed, gen, cel, dom), horasTrabajadas(horas), horasExtra(extra), valorHora(valor) {}

    double calcularSueldo() override {
        return horasTrabajadas * valorHora + calcularHorasExtra();
    }

    double calcularHorasExtra() {
        return horasExtra * valorHora * 1.5; // Asumiendo 1.5x para horas extra
    }

    string getPuesto() override {
        return "Jornalero";
    }

    string toString() override {
        return Empleado::toString() + "\nPuesto: " + getPuesto() + "\nSueldo: $" + to_string(calcularSueldo());
    }
};

// Clase OficialObra
class OficialObra : public Empleado {
private:
    int horasTrabajadas;
    double valorHora;

public:
    OficialObra(string nom, int ed, string gen, int cel, string dom, int horas, double valor) :
        Empleado(nom, ed, gen, cel, dom), horasTrabajadas(horas), valorHora(valor) {}

    double calcularSueldo() override {
        return horasTrabajadas * valorHora + calcularHorasExtra();
    }

    double calcularHorasExtra() {
        return horasTrabajadas * valorHora * 1.5; // Similar a Jornalero
    }

    string getPuesto() override {
        return "Oficial de Obra";
    }

    string toString() override {
        return Empleado::toString() + "\nPuesto: " + getPuesto() + "\nSueldo: $" + to_string(calcularSueldo());
    }
};

// Clase Supervisor
class Supervisor : public Empleado {
private:
    int horasTrabajadas;
    double valorHora;
    vector<Empleado*> empleadosSupervisados;

public:
    Supervisor(string nom, int ed, string gen, int cel, string dom, int horas, double valor) :
        Empleado(nom, ed, gen, cel, dom), horasTrabajadas(horas), valorHora(valor) {}

    double calcularSueldo() override {
        return horasTrabajadas * valorHora + calcularHorasExtra();
    }

    double calcularHorasExtra() {
        return horasTrabajadas * valorHora * 1.5;
    }

    string getPuesto() override {
        return "Supervisor";
    }

    void agregarEmpleadoSupervisado(Empleado* emp) {
        empleadosSupervisados.push_back(emp);
    }

    vector<Empleado*> obtenerSupervisados() {
        return empleadosSupervisados;
    }

    void imprimirSupervisados() {
        cout << "\nEmpleados Supervisados:\n";
        for (Empleado* emp : empleadosSupervisados) {
            cout << emp->toString() << endl;
        }
    }

    string toString() override {
        return Empleado::toString() + "\nPuesto: " + getPuesto() + "\nSueldo: $" + to_string(calcularSueldo());
    }
};

// Clase Empresa
class Empresa {
private:
    string nombre;
    string RUC;
    int numeroCelular;
    string domicilio;
    vector<Empleado*> empleados;

public:
    Empresa(string nom, string ruc, int cel, string dom) :
        nombre(nom), RUC(ruc), numeroCelular(cel), domicilio(dom) {}

    void agregarEmpleado(Empleado* emp) {
        empleados.push_back(emp);
    }

    string getNombre() {
        return nombre;
    }

    string getRUC() {
        return RUC;
    }

    int getNumeroCelular() {
        return numeroCelular;
    }

    string getDomicilio() {
        return domicilio;
    }

    void imprimirEmpleados() {
        cout << "\nEmpleados de la Empresa:\n";
        for (Empleado* emp : empleados) {
            cout << emp->toString() << endl;
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(0));
    Empresa empresa("Empresa Ejemplo", "123456789", 987654321, "Calle Falsa 123");
    EmpleadoComun empComun("Juan", 30, "Masculino", 123456789, "Calle 1", 1500, 500);
    Jornalero jornalero("Pedro", 25, "Masculino", 987654321, "Calle 2", 40, 10, 20);
    OficialObra oficial("Luis", 40, "Masculino", 123987456, "Calle 3", 50, 30);
    Supervisor supervisor("Maria", 35, "Femenino", 147852369, "Calle 4", 60, 50);
    supervisor.agregarEmpleadoSupervisado(&empComun);
    supervisor.agregarEmpleadoSupervisado(&jornalero);
    empresa.agregarEmpleado(&empComun);
    empresa.agregarEmpleado(&jornalero);
    empresa.agregarEmpleado(&oficial);
    empresa.agregarEmpleado(&supervisor);
    empresa.imprimirEmpleados();
    supervisor.imprimirSupervisados();
    return a.exec();
}

