# Sistema de carbonatación de cerveza

## Alumno
Hernán Leandro Bailo

## Objetivo
Desarrollar un sistema de carbonatación de cerveza en barriles.

## Descripción
El sistema de carbonatación consiste en un tanque de CO2 conectado al barril de cerveza a través de una válvula solenoide, a continuación se muestra el P&ID del proceso.

![P&ID](doc/P&ID.png)

### Lógica secuencial del proceso
1. Se abre por primera vez la válvula PV01 y se cierra cuando PT01 = 3 bar.
2. Se activa el motor conectado al soporte agitador para que el CO2 se diluya.
3. Al diluirse el CO2, PT01 decrece y se establece en un valor. Se monitorea esta variable para detectar el estado estacionario y si 0.9 bar < PT01 < 1 bar entonces se pasa al paso 4. Sino se finaliza el proceso con el barril correctamente carbonatado.
4. Se abre por segunda vez la válvula PV01 y se cierra cuando PT01 = 2 bar.
5. Se activa el motor conectado al soporte agitador y se sensa por el estado estacionario de PT01.
6. Si 0.9 bar < PT01 < 1 bar entonces se pasa al paso 7. Sino se finaliza el proceso con el barril correctamente carbonatado.
7. Se abre por nuevamente la válvula PV01 y se cierra cuando PT01 = 1 bar.
8. Se activa el motor conectado al soporte agitador y se sensa por el estado estacionario de PT01.
9. Si 0.9 bar < PT01 < 1 bar entonces se repite el paso 7 hasta conseguir esta condición. Sino se finaliza el proceso con el barril correctamente carbonatado.

### Enclavamientos y alarmas
Si se detecta PT01 > 4 bar se detiene el proceso, se activa la sirena y se envía un mensaje de alarma a la PC.
Si se detecta PT01 cercano a 0 cuando el sistema está operativo, se activa la sirena y se envía un mensaje de alarma a la PC ya que es probable que se haya pinchado alguna manguera.

### Interfaz de usuario
El usuario debe poder monitorear y encender/apagar el proceso desde la PC.

Se visualiza en la PC:
* Mediciones de presión
* Tiempo empleado en el barril actual
* Alarmas

## Plataforma de desarrollo
NUCLEO-F429ZI

## Periféricos a utilizar
* DIGITAL OUT 1: Señal de actuación de la válvula solenoide PV01.
* DIGITAL OUT 2: Señal de actuación del motor M01 del agitador.
* DIGITAL OUT 3: Señal de alarma acústica.
* ANALOG IN 1: Medición de presión del sensor PT01.
* UART: Comunicación con PC para indicación y operación del sistema.

## Arquitectura del software

### Diagrama UML de clases

![UML](https://github.com/hbailo/Beer-Carbonation-System/blob/d4f6edefa25c21ac62fb0daf106ac1f02ebeeb73/docs/UML%20Class%20Diagram%20-%20overview.png)
