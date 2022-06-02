## SERPIENTE 3D CON OPENGL Y C++

El juego de la serpiente 3D se elaboró como parte de un proyecto final de la materia de Graficacion en el Instituto Tecnologico de Oaxaca y se encuentra implementado en el lenguaje C++, usando visual studio como IDE y las librerias OpenGL y FreeGlut.

### Requisitos
------------
- OpenGL (GL, GLU, GLUT)
- Visual Studio 2015 o superior.

### Configuracion de Visual Studio
------------
- Descargar el kit de herramientas de OpenGL.
- Acceder a las propiedades del proyecto.
- Dirigirnos al apartado de C/C++ y posteriormente en en la sección de General y en la linea de Directorios de inclusion adicionales especificar la ruta del directorio de las librerias descargadas.
- Dirigirnos al apartado de Vinculador y posteriormente en la sección de General y en la linea de directorios de bibliotecas adicionales especificar la ruta del directorio de las bibliotecas descargadas.
- Dirigirnos dentro del mismo apartado Vinculador a la sección de Entrada y en la linea de dependencias adicionales agregar lo siguiente: glut32.lib

### Controles 
------------
> I - Comenzar el juego.
> 
> A - Girar serpiente a la izquierda.
> 
> D - Girar serpiente a la derecha.
> 
> Q - Finalizar el Juego.

### Reglas del Juego
------------
1. El juego comenzará en pausa, para poder iniciarlo deberas oprimir la tecla I.

2. La serpiente deberá buscar y comer comida en todo el escenario  y cuando  está encuentre su tamaño ira aumentando asi mismo su velocidad aumentara.

3. Si la serpiente llega a topar con el borde del escenario, automaticamente el juego finalizará y deberás comenzar desde el inicio.

4. Si la serpiente llega a topar con su propio cuerpo, de igual manera el juego finalizará y deberás comenzar desde el inicio.

### Visualización del Juego
------------
[![Snake3D](https://i.ibb.co/3fd86gM/dede.png "Snake3D")](https://i.ibb.co/3fd86gM/dede.png "Snake3D")
