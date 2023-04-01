# Proyecto-Domino

_Este proyecto se basa en la creación de un juego de Domino para el curso de Sistemas Operativos de la carrera de Ingeniería en Sistemas (3 Nivel). El juego utiliza un sistema de hilos para cada jugador, haciendo que el juego sea automático_

## Comenzando 🚀

_Estas instrucciones te permitirán obtener un entorno de desarrollo Ubuntu completo en tu sistema Windows sin tener que hacer una instalación del mismo._


### Pre-requisitos 📋

* **Windows Subsystem for Linux (WSL):** _Tener activa la Virtualización en las Configuraciones del BIOS_
* **Visual Studio Code:** _Cumplir con los requisitos mínimos mencionados en [su página](https://code.visualstudio.com/Docs/supporting/requirements)_

### Instalación 🔧

**Windows Subsystem for Linux (WSL):** _El primer paso es instalar el entorno en el cual vamos a estar ejecutando nuestro código. Para esto, lo primero que debemos hacer es lo siguiente:_

1. Abre el menú de incio, busca ```cmd```, y ejecútalo como Administrador (Click Derecho >> Ejecutar como Administrador)

2. Una vez abierta la ventana asegúrate de que esta diga: ```C:\Windows\System32>```

3. Ahora instalamos WSL. Instalaremos de forma predeterminada la distro Ubuntu. Escribimos: ```wsl --install```. _Esperamos a que finalice la instalación. Una vez finalizada nos solicitará un usuario y contraseña, los cuales debemos recordar para más adelante._

4. Una vez instalado (y ejecutándose) Ubuntu, escribimos ```sudo su``` y escribimos nuestra contraseña. Una vez hecho esto escribimos los comandos ```apt-get update``` y ```apt-get upgrade```, para buscar e instalar actualizaciones respectivamente.

5. Por último, debemos escribir el comando _```sudo chown -R nombre_de_usuario /home/nombre_de_usuario/```_, cambiando _```nombre_de_usuario```_ por el nombre que hayan escogido al iniciar por primera vez. Con esto ya tendríamos Ubuntu actualizado y listo para trabajar.

**Compilador:** _Para instalar el compilador de C (GCC), sencillamente debemos de introducir el comando ```sudo apt install gcc```, y ya con esto estaría instalado._

**Visual Studio Code:**

1. Lo primero que debemos hacer es instalar el programa, para eso nos dirigimos a **_[su página](https://code.visualstudio.com/)_** y descargamos el programa y lo instalamos siguiendo sus indicaciones.

2. Una vez instalado, debemos dirigirnos al apartado de extensiones y buscar la extensión WSL, o puedes instalarla directamente desde **_[este enlace](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)_**.

3. Ya instalada la extensión, cerramos Visual Studio Code y abrimos Ubuntu (_aparece en el menú de Windows como una aplicación más_). Dentro de Ubuntu escribimos el comando _```code .```_ (_incluyendo el punto al final_) y esperamos a que descargue el servidor y arranque de nuevo Visual Studio Code.

Y listo, ya con esto tendríamos nuestro entorno desarrollo listo para trabajar.

## Ejecutando las pruebas ⚙️

_Explica como ejecutar las pruebas automatizadas para este sistema_

## Construido con 🛠️

_Menciona las herramientas que utilizaste para crear tu proyecto_

* [Visual Studio Code](https://code.visualstudio.com/) - El Editor Utilizado
* [Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/install) - Para la Ejecución del Código

## Autores ✒️

_Los integrantes que conforman el grupo son los siguientes:_

* **Isaac Herrera**  - *[Moshe9647](https://github.com/MOSHE9647)*
* **Melanie Oviedo** - *[Melanie_OM](#fulanito-de-tal)*
* **Jason Madrigal** - *[Jason_MO](#fulanito-de-tal)*
* **Gonzalo Dormos** - *[Gonzalo_D](#fulanito-de-tal)*

---
Escrito por [Moshe9647](https://github.com/MOSHE9647) 🔥