# 😈Death Token😈
## Proyectos II 2024/2025 - 2ºV GDV
### Nombre del grupo: Ludopatiats
#### Página Web
https://ucm-fdi-disia.github.io/DeathToken/

## INDICE:

<details>
<summary> Video Explicativo </summary>

## Vídeo explicativo
Video explicativo del proyecto para los profesores de la asignatura:
https://drive.google.com/drive/folders/10YtaE_d1bzrYI52ys3OvIVpFoekb12VE?usp=drive_link
</details>

<details>
<summary> GDD </summary>

<details>
<summary> Género y PEGI </summary>
	
## Género y PEGI
Se trata de un juego "theme park" o party games, donde puedes encontrar distintos minijuegos los cuales tienen en común un uso de una economía y sistema de camjeo para conseguir premios. El dinero se tiene que ganar apostando en los juegos y ganando.
Debido a las apuestas el PEGI del juego es **16**. Además, de que el publico objetivo de este juego son jóvenes y adultos.
</details>


<details>
<summary> Descripción del juego </summary>

## Descripción del juego
Death Token consiste en una colección de juegos de casino en los cual tendrás que probar suerte para conseguir el mayor número de fichas y así mejorar y acercarte al objetivo final. Cada juego tendrá su mecánica en la que tendrás que jugar con cartas, manejar apuestas y desarrollar apuestas ganadoras. Podrás hacer uso además de una ruleta de la suerte que te otorgue potenciadores y te ayude a obtener mejores beneficios. Uno de ellos será el **Modo Locura**, en el que cada juego se verá modificado con un giro inesperado. Si consigues ganar en este modo, otendrás un token especial llamado **alma roja**, que, consiguiendo suficientes, será el que te permita adquirir la victoria.
</details>

<details>
<summary> Jugabilidad </summary>

## Jugabilidad
### Victoria/Derrota
El objetivo del jugador es convertir su alma errante en la Muerte. Para ello, tendrá que conseguir suficientes fichas rojas (200) para comprar la **Guadaña de la Muerte** o conseguirla en la ruleta del Casino.

Por el contrario, si el jugador pierde todas sus fichas de juego entra en bancarrota y pierde el juego (te devuelve al menú inicial).

### Controles
Para poder moverse en los menús y el mapa se usarán las **flechas** o **WASD**, en teclado, el movimiento será cartesiano (x,y). Para seleccionar se usará la tecla **“E”**. Para las apuestas y demás botones en los juego se usará el click izquierdo del ratón.
### Cámara
En el **lobby**, la cámara mostrará un plano amplio **cenital** similar al de juegos como Pokémon o The Binding of Isaac para poder visualizar tanto al jugador como a la multitud de juegos que le rodean.

En los diferentes **juegos**, se mostrará un **plano frontal** de los mismos (Ver en las siguientes imágenes de referencia).
[Vista de las Slots](https://github.com/user-attachments/assets/8f7056ec-6b97-49d0-9db5-525e02cb1ad3)
[Vista de la ruleta](https://github.com/user-attachments/assets/f2737f54-3456-4d6c-8e47-5358e3c03781)

### Ciclo de juego y menús
El jugador iniciará el juego y se le presentará un **menú de inicio** donde aparecerá el título, una caja de texto para registrar tú usuario y unos botones para iniciar el juego y otro para salir, que brillarán amarillo cuando estén seleccionados. Al iniciar accederás al interior del casino.
Al entrar, el jugador con **sprite de fantasma** se encontrará en mitad de un **lobby con cuatro mesas de juegos** repartidas por el salón, junto con una **ruleta**.

Inicialmente el jugador iniciará con **2000 fichas** con las que apostar. El jugador se moverá por la zona y seleccionará el juego que quiere, acercándose a alguna de estas mesas, que se marcará con brillo amarillo indicando que puede seleccionarse.
Una vez finalizado el juego, el jugador puede salir del juego con **más monedas** si gana (multiplicando la apuesta por el **multiplicador obtenido**) o **perdiendo las monedas apostadas** si ha perdido. Cuando haya salido del juego podrá ir a la **ruleta**, moviéndose por el escenario y seleccionarla. En ella el jugador podrá **gastar fichas** a cambio de tiradas en las que podrá obtener **recompensas** que le ayuden a avanzar (o incluso lo perjudiquen).

En el momento en el que el jugador **consigue la “milestone”** ganará la partida, en el que se verá en una **pantalla de victoria** cómo se ha convertido en la nueva Muerte; **si pierde todas las monedas** la perderá y se verá una pantalla de **Game Over** con su alma errante vagando por el infierno. En cualquiera de las dos, podrá volver al inicio pulsando el botón de menú.

Si le das a la tecla **P** puedes acceder a un menú de pausa donde puedes volver al juego, volver al menú inicial o ir a ver el ranking global de jugadores.
</details>

<details>
<summary> Diseño del juego </summary>

## Diseño del juego
<details>
  <summary> Sistema de fichas y ruleta </summary>
	
### Sistema de fichas y Ruleta
En cada juego podrás apostar una cantidad de **fichas básicas**, que se verán multiplicadas o restadas según el resultado de la partida. Cuando consigas **2000** podrás realizar un **tiro en la Ruleta**, teniendo cuidado de no quedarte sin para seguir jugando. [Fichas](https://github.com/user-attachments/assets/6e74fa39-040a-4041-bf27-63ea778e95df)

Las **almas** son un token especial que funcionan como tickets de bolera; sirven para comprar la Guadaña a cambio de **200**. La forma de conseguir almas es jugando a los juegos en el modo Locura, explicado más adelante, o consiguiéndolas en la ruleta. [Almas rojas](https://github.com/user-attachments/assets/1eae08b4-7f11-42c6-9717-63d63d541c73)

La Ruleta contará con 2 modos, igual que el resto de juegos:
Modo normal:
  33% -> Ganar locura
  33% -> Ganar 4000 almas azules
  17% -> Nada
  17% -> Ganar 1 alma roja
Modo locura:
  2% -> Guadaña (Victoria instantánea)
  2% -> Muerte (Derrota instantánea)
  31% -> Nada
  31% -> Ganar 1 alma roja
  17% -> Ganar 20 almas rojas
  17% -> Perder almas rojas

</details>

<details>
<summary> Locura </summary>
	
### Locura
La locura es una mecánica que hará que se modifiquen los juegos, permitiendo un cambio drástico en la jugabilidad. Tras un spin de la ruleta existirá la posibilidad de conseguir locura. Una vez conseguida, se podrán invertir **10 jugadas** con locura en los juegos o en la ruleta.
Durante este estado, la apariencia y las mecánicas de los juegos se verán alteradas. Además por cada victoria el jugador recibirá una cantidad de almas rojas correspondiente al multiplicador obtenido, además de fichas.

</details>

<details>
<summary> Juegos </summary>
	
### Juegos
#### Slots: 
Utiliza la mecánica de los slots tradicionales: inicias con una apuesta y si consigues que tres figuras se alineen horizontalmente recuperarás el dinero multiplicado por la combinación ganadora.

Estéticamente, será una estructura 3x3 de celdas cuadradas con diferentes dibujos (número 6, araña, calavera, ojo, gato negro, diablillo, murciélago). El jugador activará la máquina insertando la apuesta en la ranura correspondiente, luego pulsar el botón "GO" y las tres columnas empezarán a 'girar' haciendo que los iconos vayas entrando por arriba y saliendo por abajo de manera cíclica. La freecuencia de aparición de los iconos es inversamente proporcional al multiplicador asociado, cuanto mayor es su recompensa, menos veces aparecen. El jugador parará las columnas con el botón correspondiente. Si se ha conseguido alguna alineación, se obtendrán las recompensas.

Las recompensas de las combinaciones serán:
- 2 Arañas: x2
- 3 Murciélagos: x3
- 3 Ojos: x5
- 3 Calavera: x10
- 3 Gatos negros: x50
- 3 Diablillos: x80
- Número 6: x120

[Slot](https://github.com/user-attachments/assets/570579ca-8f5c-4d4a-a46f-b2c67f030dea)

#### Modo Locura:

Aparecerá una cuarta columna y cuarta fila (ahora un 4x4) y ahora el juego consistirá en hacer un 3 en raya en las nuevas celdas, donde el jugador se enfrentará contra la máquina de slots (IA). En un recuadro adicional situado a la izquierda de la máquina aparecerá el icono a colocar, de entre los ya mencionados (con frecuencia inversamente proporcional a su multiplicador), y el jugador de ese turno decidirá cómo colocarlo. Para colocar los iconos el jugador solo deberá pulsar la celda vacía donde quiere poner el icono. La IA tendrá que evaluar qué casilla es la más óptima en función de si hay posibilidad de 3 en raya conectando con el símbolo que le haya tocado y de qué casillas estén libres. El turno de la IA se ve indicado con la celda adicional de color azul.

Cada vez que el tablero, al principio vacío, llene sus 16 celdas, se volverá a vaciar a vaciar el tablero y se seguirá jugando hasta que alguien consiga tres en raya.

El juego acaba cuando alguno de los adversarios consigue alinear 3 símbolos iguales como en el 3 en raya. Si el jugador gana, se obtendrá el mltiplicador asociado al icono que haya alineado (los mismo que en normal), y se mostrará el número de fichas y almas rojas que haya conseguido, correspondiente al multiplicador de la combinación de 3 que haya logrado.
			
#### Baccarat: 
Se reparten, una a una, cuatro cartas, dos para el jugador y dos para el banquero, sin embargo hay ocasiones en que se extrae una tercera. El juego comienza colocando una apuesta al jugador, al banquero o al empate. La mano que consiga o más se acerque al 9 gana. Cuando el jugador y el banquero totalizan el mismo puntaje, la mano es declarada en empate.
 
Las figuras y los dieces, valen cero, los ases valen 1, las restantes cartas conservan su valor. En el bacará no es posible superar el nueve porque solo se contabiliza la última cifra. Ejemplo: El jugador recibe un 4 y un 8. El total es 12, como únicamente se toma la última cifra, la mano vale 2. Ninguna mano tendrá más de 3 cartas.

El reparto de la tercera carta se rige según la siguiente tabla:
![normas](https://github.com/user-attachments/assets/8646cc70-422b-4744-bf5f-2eda24cf1460)

Las recompensas de las apuestas serán:
- Apuesta al jugador: x2
- Apuesta a la banca: x2
- Apuesta al empate: x8
		
#### Modo Locura:

De forma aleatoria podrás jugar a 3 juegos diferentes, siendo dos de éstos una modificación del Baccarat:

**1. BlackJack:** juego clásico del blackjack con una única apuesta a que ganas tú contra el banker. Consiste en ir pidiendo cartas hasta conseguir que su suma se acerque más a 21 sin pasarse.
**2. BaccaratFlipper:** modificación del Baccarat en la que, después de una ronda normal, te saldrán otras 3 cartas aleatorias boca abajo. Debes darle la vuelta a dos, la tercera permanecerá bocabajo. Una vez dadas la vuelta, deberás elegir si ponerlas en el montón del player o del banker teniendo en cuenta que siempre tendrás que dar una a cada uno, la tercera al que prefieras. El resto del juego es como el Baccarat.
**3.BaccaratBet:** modificación del Baccarat en la que en caso de que el jugador gane, tendrá que decidir si sigue apostando o termina la partida. Si sigue apostando, estará obligado a hacerlo con el dinero ganado en la anterior ronda, en caso de ganar la siguiente, sus ganancias no serán por dos sino por cuatro, y así sucesivamente. Pero si pierde, perderá todo lo ganado.

#### Canicas:
Se sacaránal azar 3 bolas de cuatro colores posibles. El objetivo del juego consiste en predecir de qué color van a salir las bolas de colores. Los colores son rojo, cian, verde y amarillo. Para decidir la apuesta, abajo de la pantalla habrá diferentes fichas con una cantidad de apuesta. Una vez seleccionada se pondrá en las diferentes casillas que el jugador quiera depositar la apuesta, estas casillas serán 4 casillas con 1 bola de cada color, 10 casillas con combinaciones de 2 colores y 20 casillas de combinaciones de 3 colores. Cuando ya se acabe la apuesta, se verán como salen 3 bolas de colores, revelando que combinación de colores es la ganadora. Si el jugador ha ganado, recibirá un mensaje de cuántas fichas ha obtenido.
		
Las diferentes apuestas y recompensas serán:	
- Apuesta 1 color: x2
- Apuesta 2 colores: x5
- Apuesta 3 colores: x20

#### Modo Locura:

Antes de que se muestran las bolas habrá un juego del trilero (vasos con canica debajo). En este se meterá una bola de un color aleatorio en un cubilete de tres posibles. El jugador deberá elegir dónde cree que está la bola. Si acierta, ese color será descartado de la apuesta. 

[Boceto de las apuesta y tablero](https://github.com/user-attachments/assets/b66c7004-7c0c-4365-bff1-7614b5f253b2)

#### Peleas Reanimadas:
El menú de inicio/panel de apuestas se mostrará cual es el combate que va a comenzar. En pantalla se mostrarán dos tarjetas de cada uno de los peleadores. En estas tarjetas aparecerán:
Nombre
Imagen
Cuota de apuesta: Calculada según la diferencia de habilidad entre los peleadores (Vida Max + Ataque * 1.3)
Ánimo: Reflejado en los perfiles de los luchadores con alguna palabra clave. Ej: Enfocado, descentrado, …
Fichas apostadas
Como antes mencionamos también aparecerá una descripción que aportará información sobre cómo suele desenvolverse ese combate. 
Además aparecerá una pequeña tabla con las normas de las acciones especiales y sus consecuencias para dar información al jugador de lo que podría pasar en el combate. 
En caso de necesitar más información dejaríamos una guía en un botón de ayuda. 
Al iniciar la apuesta iniciará el combate directamente. 
Como referencia dejamos una imagen de cómo debería ser.

En el combate irán pasando los turnos automáticamente donde el jugador estará participando como espectador y no podrá influenciar directamente en el combate. Aún así hay alguna circunstancias donde el jugador podrá aumentar su apuesta o perder una parte de ella. La pelea se ve modificada si durante el turno de los peleadores ocurre lo denominado como una acción especial. Cuando una de estas 3 acciones se desencadenan en la batalla las probabilidades de victoria se verán alteradas.

- Golpes críticos hacen el triple de daño y disminuye el ánimo al oponente mientras que sube el ánimo propio. 
- El ataque falla al tratar de golpear (Disminuye el ánimo propio )
- Se pegan a sí mismos sin querer (Disminuye el ánimo propio)
  
Al terminar la pelea se resuelve los cálculos de las fichas:
Se le quitan al jugador las invertidas en el perdedor multiplicadas por la cuota.
Se multiplican las fichas las invertidas en el personaje ganador por la cuota y se le dan al jugador.

#### Modo Locura: 

La locura es un juego del precio justo. Te enfrentas a un rival por saber cual es el precio de un objeto. 
Al inicio se dará una descripción con palabras clave que darán información sobre el posible precio del objeto. La primera parte de la descripción dará un rango de precios aproximado, mientras que la siguiente parte marcada nos marcará qué tanto vale dentro de su categoría. 
Ej: El pergamino del Dragón es un objeto único en el mundo, conservado en un estado deplorable. Pongamos que los objetos únicos en el mundo valen 100 - 200. Pues un estado deplorable nos informa de que el precio estará muy cerca de los 100.
Los objetos como máximo se generarán dentro de la cantidad máxima de fichas que tiene el jugador para que pueda ganar.
Después de la presentación del objeto el jugador escribirá el precio que creé tener el objeto.
Tras mostrar el precio elegido por el jugador y su oponente se señalará cuál de los precios está más cerca.
Si se acierta el precio exacto o se muestran 3 precios (Tres rondas se acaba el juego.) El que tenga la menor distancia al precio real entre los 3 intentos ganará 2 X precio del objeto (5 X Si aciertas el precio exacto).
Si pierdes perderás el precio más alto que hayas sugerido.

[Peleas Reanimadas 1 (Intro)](https://github.com/user-attachments/assets/edbf9d59-1986-45bc-9c6d-49bba4cda15a)

[Escenario pelea normal](https://github.com/user-attachments/assets/07b4ac54-db16-46a8-8ff8-df9ce52206a1)

</details>
</details>
<details>
	<summary> Sistema de inicio de sesión y tabla de clasificación </summary>
	
### Sistema de inicio de sesión y tabla de clasificación:
Al iniciar el juego en el menú principal, el jugador deberá poner un usuario en un recuadro, este se almacenará en una base de datos junto con el nº de fichas, almas y las tiradas . Si el usuario ya está registrado, entrará en el juego con todos su nº de valores que ya tenía en la sesión de antes. 
En el menú de pausa habrá un botón de **Rank** donde se mostrará, las almas y las fichas que tengan los 5 mejores jugadores registrados en la base de datos ordenado por mayor puntaje.
</details>

<details>
<summary> Hud </summary>
	
## Hud:
Los juegos, salvo determinadas variaciones, dispondrán de un hud en el que se mostrará un botón de **salida** para volver al lobby (esquina superior izquierda), un botón de **Go** para iniciar el juego (esquina inferior derecha), un botón de **info** para mostrar las instrucciones del juego actual, una colección de **fichas** con distinto valor para poder apostar (arrastrando la ficha a la casilla) y botones para borrar la apuesta o repetir la anterior. También habrá un **indicador** arriba a la derecha con las fichas actuales del jugador y la apuesta en juego.

Todos los **botones** del hud de los juegos funcionarán similares:
al pasar el cursor por encima cambiarán a un color mas oscuro y con un tamaño ligeramente más grande y al hacer click en ellos, se encogerán de tamaño para luego dar paso a su acción determinada. Las fichas para apostar simplemente se mostrarán algo elevadas cuando estén seleccionadas.

Los botones de los menús inicial, finales y pausa, brillará de un color amarillo cuando el ratón pase por encima.

En el menú del juego aparecerá siempre un **indicador** en la esquina superior derecha con la cantidad de **fichas** que tenga el jugador, y debajo, de la misma manera, aparecerá un **contador de almas**. La **barra de Locura**, de color amarillo, estará debajo de los contadores de ficha, y cuando se active el modo locura se llenará, mostrando la cantidad de tiradas en locura que quedan.

Las imágenes a continuación se corresponden con una idea de cómo se va a visualizar la interfaz y el juego.

Imagen 1) 
- La imagen superior se corresponde al lobby o zona de movimiento entre los distintos juegos. Ahí estarán los cuatro juegos y la ruleta de premios. También se pueden visualizar los distintos elementos de la interfaz.
- La imagen inferior se corresponde a una idea temprana de cómo se quiere el menú de inicio,con tres botones: uno de iniciar,otro de salir y otros de ajustes.
  [Imagen HUD 1](https://github.com/user-attachments/assets/7eebd677-ebf6-4f3c-aff2-0375c2d9fdda)
  
Imagen 2)
- La imagen corresponde a un mock-up de la interfaz en varios juegos (Slots en la superior y Bacará en la inferior).
  [Imagen HUD 2](https://github.com/user-attachments/assets/d1f3ee19-456c-4e36-b3da-7dfdc0c19c26)
  
Imagen 3)
- La imagen corresponde a la ruleta de premios, solo se podrá pulsar canjeando el número de fichas correspondiente y una vez finalizado recibirá el premio correspondiente.
  [Imagen HUD 3](https://github.com/user-attachments/assets/44b541ab-1cc4-4e90-b28d-c6caecce4057)

</details>


<details>
<summary> Música y arte </summary>
		
## Música y arte:
El juego presentará una estética inspirada en el **arte**, la **música** y las **animaciones** clásicas de Disney y producciones similares de los **años 20 y 30**, tomando inspiración de juegos como Cuphead.

El juego contará con la siguiente paleta de color:
![image9](https://github.com/user-attachments/assets/b32ee196-b15d-44e7-a843-6115c19349ce)

Diseño del jugador:
![IMG_0087](https://github.com/user-attachments/assets/13542bf3-9f31-4024-a636-2b18481ca5cc)

Contará con **sonidos** característicos de los **casinos** (giro de ruletas, el tintineo de monedas, eco de las máquinas tragamonedas…) todo con un **filtro antiguo** para acentuar la ambientación. La música ambiente será **alegre** reflejando la atmósfera del casino.

</details>

<details>
<summary> Lore </summary>

## Lore
Estás muerto. Ya no hay más vida para ti y ahora eres un alma errante que vaga por el infierno. Pero algo llama tu atención en el Infierno en el que te encuentras, en un gran edificio lleno de luces y colores llamádo el Casino de la Muerte.

Consiguiendo las suficientes fichas podrás hacerte con una Guadaña y convertirte en la nueva Parca. Así que decidirás explorar los juegos de cartas y fichas que se te ofrecen para lograr tu objetivo.

</details>
</details>

<details>
<summary> Arquitectura de juego </summary>

## Arquitectura de juego
El juego está organizado por medio de entities y herencia. Hay una clase game que se encarga de getionar el ciclo de juego y el cargado inical de todos los recursos necesarios, además de una generación de una *"seed"* e inclusión del usuario en la base de *"firebase"*.

Posteriormente tenemos estados de juego, los cuales corresponden a diversas escenas del juego. En este grupo tenemos: la pantalla principa,el tutorial,el lobby, todos los juegos, la pausa, las escenas de victoria y derrota.

El jugador es un objeto de escena movido por fisicas sencillas,las cuales permiten el cambio de escena entre los distintos juegos.
Sin embargo,la interfaz de usuario son objetos independientes,porque se encuentran en una "layer" distinta, no obstante siguen siendo objetos con funcionalidades y características concretas.

![image](https://github.com/user-attachments/assets/46bbb06a-6383-4f7c-809f-a5c65f046f34)
</details>

<details>
<summary> PlayTesting </summary>
	
## PlayTesting
<details>
	<summary> Objetivos del PlayTesting </summary>
	
### Objetivos del PlayTesting
**1.Comprensión de las mecánicas y controles principales del juego.**
¿El jugador comprende la economía del juego y como usar la “currency”?

¿El jugador sabe cuando puede iniciar una partida a cada uno de los juegos?

¿El jugador comprende que puede volver a jugar sin necesidad de salir del juego y como puedo hacerlo?

¿El jugador sabe cómo moverse y cómo acceder a los distintos juegos?

¿El jugador entiende las distintas mecánicas de cada juego y sabe cómo ganar?

**2.Comprobación de éxito y fracaso en cada uno de los juegos.**
¿El jugador gana mucho o poco?

¿El jugador sabe como ganar o establece algún tipo de estrategia?
</details>

<details>
	<summary> Duración de la prueba y desarrollo </summary>
	
### Duración de la prueba y desarrollo
La prueba consta de un tester y un mínimo de un evaluador por jugador/a. La duración será de unos 15-20 minutos: la explicación del evaluador serán 3-5 minutos; la partida donde el jugador deberá probar los distintos aspectos del juego en 10-15 minutos y el evaluador deberá preguntar en el tiempo restante. Al iniciar la partida se les dará una explicación/instrucciones de las acciones que deberán hacer, mientras tanto el evaluador deberá permanecer en silencio y no deberá interactuar en ningún momento con el/la jugador/a, de esta manera mantendremos la connotación de la prueba. Simultáneamente,durante la prueba el evaluador deberá tomar notas acerca de los aspectos a evaluar. Una vez terminado el tiempo, se pasará a un momento donde el tester dará sus opiniones y pensamientos acerca de su partida, o algún comentario que desee hacer. Posteriormente, el evaluador/desarrollador hará una serie de preguntas para conocer otro tipo de aspectos a evaluar.
</details>
<details>
	<summary> Comportamiento del tester </summary>

### Comportamiento del tester
Se colocará en el sitio donde se haga la prueba en frente de algún ordenador. Escuchará la explicación de los evaluadores y a continuación jugará la partida de manera natural. No habrá límite de intentos pues la evaluación se hará en función del tiempo, así la partida será más relajada para el tester y se podrá recoger más información. Una vez terminado los 10-15 minutos el tester dará su opinión y valoración de su experiencia de juego. Posteriormente, deberá responder con sinceridad cada pregunta que les diga el evaluador.
</details>

<details>
	<summary> Comportamiento del evaluador </summary>

### Comportamiento del evaluador
Una vez colocado el tester procederá a explicar en qué consistirá la prueba.

**Explicación:**
“(Saludo cordial hacia el tester), el juego que vas a probar es un “theme park”, donde tienes distintos juegos donde ganas recompensas y tienes que llegar a un número concreto de recompensas para ganar. Este juego trata de un casino en el infierno, donde nuestro protagonista debido a su vida ludópata y muerte repentina en un casino, acabó en ese lugar. El diablo le ofrece un trato, el cual si consigue recoger las suficientes almas se podrá volver la parca, en caso contrario se quedará en el infierno sufriendo. El objetivo del juego es ganar dinero para ganar almas y comprar la guadaña. 
Tu objetivo será jugar los distintos juegos del casino y ganar lo suficiente para ganar. Juega con normalidad y no temas a decir cosas en alto, nos ayuda a recoger más datos. Por desgracia no podremos resolver ninguna pregunta que nos hagáis durante la partida. Podeís empezar la partida”.
Una vez finalizada la explicación el evaluador deberá permanecer en silencio y apuntar los distintos aspectos en el gameplay del tester en algún lugar para posteriormente hacer un informe recogiendo los datos totales. Tras la partida escuchará al tester y  le hará unas preguntas más  concretas.

</details>
<details>
	<summary> Aspectos a observar/evaluar </summary>

 ###  Aspectos a observar/evaluar
El jugador sabe que debe introducir un nombre para poder iniciar la partida.
El jugador se mueve por el mapa y accede a los juegos usando las teclas correspondientes.
El jugador coloca las “chips”, intuye su funcionamiento (pueden ser arrastradas y colocadas para hacer la apuesta).
El jugador comprende que no puede iniciar una partida a menos que  haya alguna apuesta y sabe dónde debe darle para iniciar la partida.
El jugador comprende cuánto ganó tras la apuesta y cuánto le queda.
El jugador comprende que ha entrado en modo locura y que han cambiado los juegos.

**Slots:**
El jugador ve que la manera de apostar es distinta y debe darle a los multiplicadores antes de iniciar la partida.
El jugador ve que tiene que pulsar los botones en la zona inferior de cada “carrete” para hacerlo parar.
El jugador entiende si ha ganado o perdido una vez se hayan pulsado los tres botones.
El jugador entiende que en el modo locura debe pulsar las casillas para poner una ficha

**Canicas:**
El jugador comprende que debe arrastrar las “chips” para poder iniciar una apuesta y puede apostar en distintos huecos, pudiendo hacer apuesta múltiple.
El jugador comprende las distintas apuestas que se pueden hacer.
El jugador comprende que tras darle sabe si ha ganado o perdido, pudiendo apreciar que canicas han salido.
El jugador entiende que, en locura, debe seleccionar un vaso y se quita este de todas las canicas.

**Baccarat:**
El jugador comprende dónde debe colocar las “chips” para iniciar el juego y las distintas apuestas que hay.
El jugador entiende que tiene cartas y que tipo de cartas tiene, y está jugando contra una IA, para poder llegar a 9.
El jugador comprende como puede llegar a 9.21,etc.
El jugador entiende cuando ha ganado,empatado o perdido la apuesta.
El jugadro entiende que en locura hay tres juegos de cartas,y que se debe hacer en cada uno.

**Peleas reanimadas:**
El jugador entiende donde debe de hacer la apuesta
El jugador comprende lo que está sucediendo durante la apuesta.
El jugador comprende que ha ganado o perdido.
El jugador entiende que debe escribir para realizar una estimación del premio.

**Ruleta**
El jugador entiende el precio de la ruleta.
El jugador entiende los distintos premispo que hay.
El jugador comprende que debe conseguir unja cantidad de almas rojas para ganar.

</details>
<details>
	<summary> Material empleado </summary>

 ### Material empleado
Ordenador.
Algo para apuntar (cuaderno y boli/ portátil/etc.).
Las cuestiones a evaluar.
</details>
<details>
	<summary> Preguntas para el tester </summary>

 ### Preguntas para el tester
**¿Te ha resultado muy complicado entender las mecánicas de los juegos?
¿Sientes que has ganado más o perdido más?
¿Qué aspectos te ha costado entender?¿Qué aspectos has entendido mejor?¿Que te podría ayudar a entenderlo mejor?
¿Visualmente te parecía agradable?¿Los colores no eran muy fuertes,combinaban bien entre sí,etc?¿Qué crees que se podría añadir para que fuese más atractivo a la vista?
¿Qué juego ha resultado más complicado para ganar?¿Y el más fácil?**
</details>

<details>
	<summary> Resultados del PlayTest </summary>

## Resultados PlayTest
## _Total de testers:_ **15**
## **Conclusiones**
Menú inicial: es necesario poner de manera más visual que se encontraba en un menú de inicio e incluso hacer más estético la zona donde deben registrarse los jugadores.Lo entendieron 4/15 testers.

Pantalla de inicio: prácticamnete todos no comprendieron el movimiento y teclas que debían usar para navegar en el mapa y para acceder a los juegos,sai no se explicaba inicialmente no podrían haber probado el resto del juego. Lo entendieron 0/15 testers.

Apuestas (fichas): comprendieron que tenian fichas y que se podían arratrar o pulsar en la zona de apuesta para aplicar,admás,de que si no tienes suficiente dienro no puedes hacer esa apuesta. Lo entendieron 13/15 testers.

Apuestas (iniciar el juego): la mitad de los testers no comprendieron que no podían iniciar la partida a menso de que hubiese algun tipo de apuesta. Lo entendieron 7/15 testers.

Recompensa o perdida de fichas: una gran parte de los testers no sabían cuanto habían ganado, incluso comentando varios de ellos de que algún feedback visual *ayudaría*. Lo entendieron 3/15 testers.

Slots: la mayoría entendió que debían cuadrar en una misma linea tres simbolos iguales y qeu ganarían más en funcion del simbolo,no obstante,les costó ganar partidas. Lo entendieron 12/15 testers.

Slots(Locura): inicialmente les costó entender que debían pulsar en las casillas y que no tenían unas fichas propias,si no, que las compartían la IA y el tester. Lo entendieron 8/15 testers.

Canicas: una mayoría no entendió que podía apostar en distintas apuetas y que representaba cada una,los testers idearon planes para ganar más. Lo entendieron 5/15 testers.

Canicas(Locura): casi nadie comprendió que al elegir una canica en los vasos, esta se quitaba de la pool de canicas. Lo entendieron 2/15 testers.

Baccarat: todos entendieron que podían ganar,perder o empatar,sin embargo, muchos no lograron entender la combinación de cartas para formar 9. Lo entendieron 9/15 testers.

Baccarat(Locura): casi todos comprendieron que mecánicamente este juego funcionaba casi igual y que había un total de 3 variantes. Lo entendieron 10/15 testers.

Peleas: muchos entendieron que cada vez que entraban aparecía un luchar distinto y con distintas caracterísitcas al que debían apostar,los testers vieron este juego como una manera de ganar más fácil. Lo entendieron 13/15 testers.

Peleas(Locura): muchos testers no comprendieron que debían escribir algo para avanzar en el juego, incluso les costó seguir adivinar el precio. Lo entendieron 4/15 testers.

Ruleta: los jugadores comprendieron que cada color les dba un premio y cuanto costaba la ruleta, y que con esta se obtenía el modo locura. Lo entendieron 15/15 testers.

## **Respuestas**
**¿Te ha resultado muy complicado entender las mecánicas de los juegos?** 
La mayoría de respuestas decian que les costaba entender como funcionaba cada juego y que debían hacer en cada momento,además de que les faltaba algo que les ayudase a entenderlo.

**¿Sientes que has ganado más o perdido más?**
La mayoría contestó que perdían en algunos juegos, pero que podían recuperar ese dienro en otro juego.

**¿Qué aspectos te ha costado entender?¿Qué aspectos has entendido mejor?¿Que te podría ayudar a entenderlo mejor?** 
Lo que más les costóa fue el movimiento,la economía y conocimiento de victoria/derrrota. Lo que mejor entenideron fueron: slots,canicas y apostar. Y muchos pidieron tutoriales específicos.

**¿Visualmente te parecía agradable?¿Los colores no eran muy fuertes,combinaban bien entre sí,etc?¿Qué crees que se podría añadir para que fuese más atractivo a la vista?**
A todos les agradío el estilo visual,pero necesitaban un feedback sonoro,lo cual muchos recalcaron.

**¿Qué juego ha resultado más complicado para ganar?¿Y el más fácil?**
La mayoría coincidía que el más difícil era baccarat y el más fácil canicas.

## **Conclusión final**
Por medio de este playtesting sacamos una clara necesidad de tutoriales o explciaciones de todos los aspectos necesarios del juegos,posiblemete uno general para explicar mecáncias comunes a todos los juegos y tutroiales de cada juego inidvidual. además de que se necesita mucho feedback, visual y sonoro para: que se sepa mejor lo que está ocurriendo antes,durante y despues del juego. Tambien, hemos analizado en ajustar algunos valores aleatorios para que sea más frecuente ganar y que el jugador pueda diseñar una "estrategia" para poder alcanzar el objetivo del juego,estos valores pqeu hablamso son: velocidades(slots,baccarat),probabilidades de aparición(todos los juegos) o balanceado de ia (baccarat,peleas,slots). Y por ultimo, retocar un poco las ficsicas para que no se sintiesen ortopédicas.

</details>
</details>

<details>
<summary> Referencias </summary>
			
## Referencias:
Nuestra principal referencia ha sido la estética y la dinámica general de un casino clásico, buscando capturar su atmósfera.

Algunos juegos que han servido de inspiración en términos de mecánicas y estilo son:

- Cuphead, con su estética de dibujos animados de los años 30 y su exigente jugabilidad.

[Cuphead](https://github.com/user-attachments/assets/8b25dd1d-acf8-485f-9a34-c2b0eb177597)

- Balatro, que incorpora una ingeniosa combinación de estrategia y azar.

[Balatro](https://github.com/user-attachments/assets/c24e4e4c-d4ce-42f3-9485-36355d902337)

- Los minijuegos de Super Mario 64 DS, que aportan un enfoque dinámico y entretenido.

[Super Mario 64 DS](https://github.com/user-attachments/assets/d2a8af99-9e95-4be9-bb39-d680dc4a0c5d)

Además, para el diseño de personajes, nos hemos inspirado en el estilo y la ambientación de Soul Eater.

[Soul Eater](https://github.com/user-attachments/assets/f6d6a28e-9e56-467c-9c1c-8da3c2ec6864)

</details>
