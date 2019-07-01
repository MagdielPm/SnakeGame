<h1 align="center">
  <br>
  <img src="https://hackster.imgix.net/uploads/attachments/431013/snake_dvlfwCony2.png?auto=compress%2Cformat&w=900&h=675&fit=min" alt="Snake image" width="400">
  <br>
</h1>
<h1 align="center"> 🍎🐍 El juego de la culebrita en consola controlado con Kinect </h1>

## Descripción 👨🏽‍💻
 El proyecto es el juego de la culebrita en consola, para la materia de programación estructurada. Se buscó implementar los principios de la programación estructurada, al igual que se utilizaron las herramientas aprendidas en el curso como el manejo de funciones, la modularidad, apuntadores y manejo de ficheros.

### Acerca del Proyecto 
  Se quizo revivir la parte clásica del Snake Game, programado con una interfaz amigable desde la consola manejando una interfaz basada en los caracteres de la tabla ASCII 👾 y el posicionamiento de coordenadas del cursor dentro de la consola. 
  
  La idea era desarrollar una nueva experiencia en el juego, tomando recursos de un dispositivo Kinect v1 de Xbox 360, utilizando como herramienta Processing, con el cual se realizó un código para la lectura de los datos del kinect y para realizar el seguimiento de las articulaciones del usuario y con las mismas, poder definir los movimientos de la culebrita en consola 🕺🏻. 

## Diseño de la aplicación 👨🏽‍🎨
 El proyecto está separado por secciones en sus pantallas mostradas en consola, cada sección cuenta con su parte de vista y su controlador. Al ser un proyecto de programación estructurada, no se aplican conceptos tan estrictos de arquitectura de software. 
 Se pueden apreciar métodos que son específicamente para crear una vista, como toda la sección de *splash de carga*, la parte del controlador se aprecia mucho en la sección de *juego* y la parte del modelo, en la consulta de los puntajes con un archivo de texto. 


 ## Modularidad, alta cohesión y bajo acoplamiento 👨🏽‍🏫
  La modularidad está presente en cada método utilizado, pues la idea principal es divir el proyecto en tareas cada vez más pequeñas y de esta forma lograr identificar su secctor principal, si un método es para dibujar en consola, su único fin es ese, si un método sirve para modificar los valores de los puntajes, entonces su única labor es esa; cada método sigue un trabajo específico, por ejemplo, el método setCursorPosition(x,y) cumple con la finalidad de posicionar el cursor en la pantalla dado una par odernado. 

  Existen métodos como movimientoSerpiente(*x,*y, *direccion) que recibe como parámetro al dirección de memoria de las variables mencionadas en el prototipo, con el único fin de editar los valores específicos de esas variables dependiento de la posición del snake y su dirección. 

  La finalidad de separar la modularidad de las funciones, es poder identificar de manera clara de cierta forma el patrón de arquitectura mvc. 

  ## Instrucciones para compilar y ejecturar 👷🏽‍🛠

  Para ejecutar el proyecto comenzamos con lo siguiente: 

  Primero que nada, necesitas instalar git: 
  - <a href="https://git-scm.com/book/es/v1/Empezando-Instalando-Git">Instalar git ✅</a> 
  
  El proyecto está desarrollado con lenguaje C y Processing 3. 
  Se necesita contar con lo siguiente, pero antes clona SnakeGame desde la rama maestra de mi repositorio de Github

```bash
git clone https://github.com/MagdielPm/SnakeGame.git
```
 Para compilarlo vas a necesitar lo siguiente: 👇🏽
  - <a href="https://docs.microsoft.com/es-es/cpp/build/walkthrough-compile-a-c-program-on-the-command-line?view=vs-2019">Compilador de C o C++ ✅</a> 
  - <a href="https://visualstudio.microsoft.com/">IDE Visual Studio (De preferencia) ✅</a>  
  - <a href="https://www.oracle.com/technetwork/java/embedded/javame/javame-sdk/downloads/javamesdkdownloads-2166598.html">SDK de Java ✅</a>
  - <a href="https://processing.org/">Instalar processing ✅</a>
  - <a href="https://www.microsoft.com/en-us/download/details.aspx?id=44561">SDK Kinect de Windows ✅</a>
  - <a href="https://github.com/chungbwc/Kinect4WinSDK">SDK de processing para kinect ✅</a>
  - Kinect v1 ✅
  

   Y listo compilas y ejecutas el programa de C y posteriormente el de Processing para comenzar a jugar. 🕹
