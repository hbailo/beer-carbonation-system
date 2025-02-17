# Sistema de carbonatación de cerveza

## Alumno
Hernán Leandro Bailo

## Resumen
Se describe el desarrollo de la automatización de un sistema de carbonatación de cerveza en barriles.

El sistema se basa en una placa de desarrollo NUCLEO-F429ZI y esta diseñado conforme a los patrones de
diseño de procesos modulares de ISA S88.

Entre sus funcionalidades principales se incluye el control mediante HMI de la receta de carbonatación, per-
mitiendo al operador iniciar, detener y reanudar su ejecución, el monitoreo y control mediante una computadora
de supervisión y el acceso a los datos de procesos desde un navegador web.

El sistema destaca por su capacidad para mejorar la consistencia en la calidad del producto final, optimizando
el tiempo de operación y minimizando la intervención manual. Su diseño modular y escalable lo convierte en una
solución adaptable para diferentes escalas de producción en la industria cervecera.

## Descripción del proceso
En el proceso de elaboración de cerveza una de las últimas etapas es la carbonatación, donde se incorpora
dióxido de carbono a lı́quido para crear efervescencia, realzar el sabor, conservar la cerveza y otros propósitos.
En el caso actual la carbonatación se realiza artificialmente mediante la incorporación forzada del gas.

El diagrama P&ID del sistema de carbonatación se muestra a continuación. Los tags utilizados están en formato IEC 81346 [1].

El sistema consiste en untanque de CO2 conectado a un barril de cerveza a través de la válvula solenoide
QMB1. El barril se encuentra montado sobre una criba vibratoria que se acciona mediante el motor eléctrico
MAA1. La presión interna del barril se mide con el transmisor BPA1.

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/architecture/process-and-instrumentation-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/architecture/process-and-instrumentation-diagram-light.png"> 
    <img alt="Shows the recipe state diagram." src="doc/architecture/process-and-instrumentation-diagram-light.png">
</picture>

### Fases del proceso
El procedimiento de carbonatación se basa en la iteración de las siguientes dos fases, estructuradas según el patrón de diseño ISA S88 [2]:

* Inyección de CO2: Accionando la válvula solenoide (normalmente cerrada) (QMB1) se inyecta CO2 al barril
de cerveza. La cantidad de gas inyectado se mide a través de la presión del barril (BPA1).

* Disolución del CO2: Encendiendo la criba vibratoria (MAA1) se agita la cerveza y se favorece la disolución
del CO2. El grado de disolución se mide indirectamente a través de la presión del barril (BPA1). A medida
que el CO2 se diluye en la cerveza BPA1 decrece y se establece en un determinado valor. Se asume que se
completó la disolución cuando dos muestras sucesivas de BPA1 con una separación de 1s difieren en menos
de 10 mbar.

### Receta de carbonatación
La receta que se requiere automatizar para lograr la carbonatación completa de un barril estándar se describe
a continuación en pasos numerados y se muestra gráficamente en el diagrama de flujo siguiente.

1. Se inyecta CO2 al barril accionando QMB1 hasta que BPA1 = 3 bar.
2. Se diluye el CO2 encendiendo la criba vibratoria. Si una vez diluido el gas se mide 0,9 bar < BPA1 < 1 bar
entonces se finaliza la receta con el barril correctamente carbonatado, sino si BPA1 < 0,9 bar se pasa al
paso 3.
3. Se inyecta CO2 al barril accionando QMB1 hasta que BPA1 = 2 bar.
4. Se diluye el CO2 y si 0,9 bar < BPA1 < 1 bar se finaliza satisfactoriamente la receta, sino si BPA1 < 0,9 bar
se pasa al paso 5.
5. Se inyecta CO2 al barril accionando QMB1 hasta que BPA1 = 1 bar.
6. Se diluye el CO2 y si 0,9 bar < BPA1 < 1 bar se finaliza satisfactoriamente la receta, sino si BPA1 < 0,9 bar
se repiten los pasos 5 y 6 indefinidamente.
En los pasos 2, 4 y 6 la condición BPA1 > 1 bar detiene la receta dado que no deberı́a producirse si el sistema
funciona adecuadamente. Se debe revisar el equipo.

Nota: en los pasos 2, 4 y 6 la condición BPA1 > 1 bar detiene la receta dado que no debería producirse si el sistema funciona adecuadamente. Se debe revisar el equipo.

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/CarbonationRecipe/recipe-flow-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/CarbonationRecipe/recipe-flow-diagram-light.png"> 
    <img alt="Shows the recipe flow diagram." src="doc/design/classes/CarbonationRecipe/recipe-flow-diagram-light.png">
</picture>

### Operación
La operación del sistema se basa en la ejecución de la receta de carbonatación, siguiendo el patrón de diseño de manufactura flexible ISA S88 [2].

El operador controla el estado de la receta a través de los siguientes comandos:

* Start:  inicia la receta.
* Stop:   detiene la receta.
* Hold:   pausa la receta.
* Resume: reanuda la receta.
* Reset:  reinicia la receta.

Los comandos se encuentran ligados con los estados de la receta de acuerdo al siguiente diagrama:

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/CarbonationRecipe/recipe-state-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/CarbonationRecipe/recipe-state-diagram-light.png"> 
    <img alt="Shows the recipe state diagram." src="doc/design/classes/CarbonationRecipe/recipe-state-diagram-light.png">
</picture>

### Alarmas y acciones de protección
* BPA1 > 4 bar: se detiene el proceso, se indica la alarma en el HMI, se activa la sirena y se envía un mensaje a la computadora de supervisión.

## Arquitectura de control
A continuación se muestra un esquemático de los módulos de hardware del sistema y se procede con las especificaciones de los mismos.

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/architecture/hardware-architecture-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/architecture/hardware-architecture-light.png"> 
    <img alt="Shows the hardware architecture." src="doc/architecture/hardware-architecture-light.png">
</picture>

### Microcontrolador
El control del sistema se realiza con una placa NUCLEO-F429ZI que posee el microcontrolador STM32F249ZI.

#### Periféricos
* DIGITAL OUT 1: Señal de actuación de la válvula solenoide QMB1.
* DIGITAL OUT 2: Señal de actuación del motor MAA1 de la criba vibratoria.
* DIGITAL OUT 3: Señal de actuación de la sirena.
* DIGITAL IN  1: Señal de display del HMI presionado. (XPT2046).
* ANALOG IN 1: Medición de presión del sensor BPA1.
* UART: Comunicación con la computadora de supervisión.
* SPI 1: Comunicación con el driver del display del HMI (ILI9341).
* SPI 2: Comunicación con el driver del touch del HMI (XPT2046).

### HMI
El operador puede monitorear y controlar el proceso desde el panel táctil.

La conexión con el microcontrolador se realiza a través de SPI. El LCD se controla a través del driver ILI9341 y la interfaz táctil con el driver XPT2046.

Se visualiza en el HMI:
* Estado actual de la receta.
* Paso actual de la receta.
* Presión interna del barril.
* Alarmas.
* Botones de comando.

Se comanda desde el HMI:
* Arranque, parada, reinicio, reanudación y pausa de la receta.
* Reconocimiento de alarmas.

### Computadora de supervisión
El operador puede obtener monitorear y controlar el proceso desde la computadora de supervisión.

La conexión se realiza a través de UART.

Datos monitoreables:
* Presión del barril.

NOTA: Los datos reportados se envían en formato JSON.

Comandos permitidos:
* Arranque, parada, reinicio, reanudación y pausa de la receta.
* Reconocimiento de alarmas.

## Software

### Arquitectura

#### Diagrama UML de clases

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/architecture/uml-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/architecture/uml-light.png"> 
    <img alt="Shows the UML class diagram of the architecture." src="doc/architecture/uml-light.png">
</picture>

#### Diagramas de estados
A continuación se muestran los principales diagramas de estados de las clases.

La clase CarbonationRecipe permite el control del estado de la receta de carbonatación implementando la siguiente máquina de estados:

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/CarbonationRecipe/recipe-state-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/CarbonationRecipe/recipe-state-diagram-light.png"> 
    <img alt="Shows the state diagram of the CarbonationRecipe class." src="doc/design/classes/CarbonationRecipe/recipe-state-diagram-light.png">
</picture>

Dentro del estado EXECUTING se encuentra la máquina de estados que implementa la receta por pasos:

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/CarbonationRecipe/recipe-step-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/CarbonationRecipe/recipe-step-diagram-light.png"> 
    <img alt="Shows the step state diagram of the CarbonationRecipe class." src="doc/design/classes/CarbonationRecipe/recipe-step-diagram-light.png">
</picture>

De igual manera las clases CO2Dissolver y CO2Injector implementan la misma máquina de estados para controlar el equipo de acuerdo al estado de la receta pero cada una implementa en el estado EXECUTING el algoritmo correspondiente.

Para CO2Injector se implementa:

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/CO2Injector/flowchart-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/CO2Injector/flowchart-diagram-light.png"> 
    <img alt="Shows the flowchart of the CO2Injector phase logic." src="doc/design/classes/CO2Injector/flowchart-diagram-light.png">
</picture>

Para CO2Dissolver se implementa:

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/CO2Dissolver/flowchart-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/CO2Dissolver/flowchart-diagram-light.png"> 
    <img alt="Shows the flowchart of the CO2Dissolver phase logic." src="doc/design/classes/CO2Dissolver/flowchart-diagram-light.png">
</picture>

Las clases OnOffMotor y SolenoidValve son los módulos de control de los actuadores. Dado que se trata de controles on/off ambos módulos implementan la siguiente máquina de estados:

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/SolenoidValve/state-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/SolenoidValve/state-diagram-light.png"> 
    <img alt="Shows the SolenoidValve state diagram." src="doc/design/classes/SolenoidValve/state-diagram-light.png"> 
</picture>

La clase HMI se encarga de la interacción con el operador a través del display táctil. Para la gestión de la interfaz táctil implementa la máquina de estados del diagrama que se muestra a continuación. Las transiciones se basa en los eventos de pantalla presionada, pantalla liberada e interacción procesada.

<picture>
    <source media="(prefers-color-scheme: dark)" srcset="doc/design/classes/HMI/touch-state-diagram-dark.png">
    <source media="(prefers-color-scheme: light)" srcset="doc/design/classes/HMI/touch-state-diagram-light.png"> 
    <img alt="Shows the HMI touch state diagram." src="doc/design/classes/HMI/touch-state-diagram-light.png"> 
</picture>

### Documentación
La documentación del código se ha generado con Doxygen.

Prerequisistos:
* Doxygen >= 1.9.4

Para generar la documentación, ejecutar:

```console
    doxygen Doxyfile 
```

Los archivos generados se encuentran en la carpeta `doc/doxygen`. Para visualizar la documentación en el navegador web, abrir el archivo `index.html` en `doc/doxygen/html`.

### Compilación 
Prerequisitos:
* Git >= 2.39
* CMake >= 3.19
* Python >= 3.6
* Mbed CLI 2 (mbed-tools) >= 7.59
* Arm GNU toolchain >= 12.2

1. Clonar el repositorio:

```console
    git clone https://github.com/hbailo/beer-carbonation-system.git
```

2. Inicializar y actualizar la librería mbed-os configurada como submodulo del repositorio:

```console
    git submodule init
    git submodule update --depth 1
```

3. Configurar el proyecto de Mbed con el dispositivo NUCLEO-F429ZI, la toolchain Arm GNU y el perfil develop (o debug o release, de acuerdo a lo que se necesite):

```console
    mbed-tools configure --mbed-os-path lib/mbed-os -m NUCLEO_F429ZI -b develop -t GCC_ARM -o build/develop
```

4. Generar el build system del proyecto. En caso de necesitar utilizar un entorno virtual de python definir el directorio raíz de la instalación agregando la opción `-DPython3_ROOT_DIR=path/to/venv/bin` al comando.

```console
    cmake -S . -B build/develop
```

5. Construir el proyecto. Como resultado se obtiene el binario del proyecto `beer-carbonation-system.bin` en `build/develop`.

```console
    cmake --build build/develop -j 4
```

En caso de modificarse el archivo mbed_app.json se debe repetir del paso 3 en adelante. Para todo el resto de modificaciones basta con repetir los pasos 4 y 5. 

En el archivo Makefile se encuentra un script para simplificar el proceso reiterativo de compilación en caso de contar con el programa Make. Para configurar el proyecto, ejecute:

```console
    make configure
```

y luego para construir el proyecto:

```console
    make
```

El binario producido `beer-carbonation-system.bin` se encuentra en `build/develop`.


## Referencias
[1] International Electrotechnical Commission. *IEC 81346-2:2019: Industrial systems, installations and equipment and industrial products — Structuring principles and reference designations — Part 2: Classification of objects and codes for classes.* (IEC, 2019)

[2] Brandl, Dennis. *Design Patterns for Flexible Manufacturing.* (ISA, 2007)
