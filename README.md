# 😈Death Token😈
## Proyectos II 2024/2025 - 2ºV GDV
### Nombre del grupo: Ludopatiats
### Participantes:

Iván Palomino Rodríguez

Jule Page Galocha

Javier Gómez Zúñiga

Michel Herraiz Gurillo

Jaime Nieto Méndez

Ismael Ortega Sánchez

Sergio Naranjo Barroso

Daniel Ramos Sanchez-Manjavacas

## INDICE:
<details>
<summary> Descripción del juego </summary>

## Descripción del juego
### Sinopsis
Estás muerto. Ya no hay más vida para ti y ahora eres un alma errante que vaga por el infierno. Pero algo llama tu atención en el Casino de la Muerte.

Consiguiendo las suficientes fichas podrás conseguir una Guadaña  y convertirte en la nueva Parca. Así que decidirás explorar los juegos de cartas y fichas que se te ofrecen para lograr tu objetivo.

</details>

<details>
<summary> Jugabilidad </summary>

## Jugabilidad
### Victoria/Derrota
El objetivo del jugador es convertir su alma errante en la Muerte. Para ello, tendrá que conseguir suficientes fichas rojas para comprar la **Guadaña de la Muerte** o conseguirla en la ruleta del Casino.

Por el contrario, si el jugador pierde todas sus fichas de juego entra en bancarrota y pierde el juego.

### Controles
Para poder moverse en los menús y el mapa se usará el **joystick**, en mando, o **WASD**, en teclado, el movimiento será cartesiano (x,y). Para seleccionar se usará el botón **“B”** (XBox)/**“X”** (PlayStation)/**Click Izquierdo o Espacio**. Y la **cruceta** o las **flechas** para poder aumentar o disminuir la apuesta. 
### Cámara
En el **lobby**, la cámara mostrará un plano amplio **cenital** similar al de juegos como Pokémon o The Binding of Isaac para poder visualizar tanto al jugador como a la multitud de juegos que le rodean.

En los diferentes **juegos**, se mostrará un **plano frontal** de los mismos (Ver en las siguientes imágenes de referencia).
[Vista de las Slots](https://github.com/user-attachments/assets/8f7056ec-6b97-49d0-9db5-525e02cb1ad3)
[Vista de la ruleta](https://github.com/user-attachments/assets/f2737f54-3456-4d6c-8e47-5358e3c03781)

### Ciclo de juego y menús
El jugador iniciará el juego y se le presentará un **menú de inicio** donde aparecerá el título y unos botones para iniciar el juego y otro para salir, que brillarán verde cuando estén seleccionados. Al iniciar se verá una animación de apertura de puertas y accederás al interior del casino.
Al entrar, el jugador con **sprite de fantasma** se encontrará en mitad de un **lobby con cuatro mesas de juegos** repartidas por el salón, junto con una **ruleta** con premios arriba a la izquierda y un stand en el extremo superior con **la Guadaña**.

Inicialmente el jugador iniciará con **500 fichas** con las que apostar. El jugador se moverá por la zona y seleccionará el juego que quiere, acercándose a alguna de estas mesas, que se marcará con un reborde blanco indicando que puede seleccionarse.
Una vez finalizado el juego, el jugador puede salir del juego con **más monedas** si gana (multiplicando la apuesta por el **multiplicador obtenido**) o **perdiendo las monedas apostadas** si ha perdido. Cuando haya salido del juego podrá ir a la **ruleta**, moviéndose por el escenario y seleccionarla. En ella el jugador podrá **gastar fichas** a cambio de tiradas en las que podrá obtener **recompensas** que le ayuden a avanzar (o incluso lo perjudiquen).

En el momento en el que el jugador **consigue la “milestone”** ganará la partida, en el que se verá en una **pantalla de victoria** cómo se ha convertido en la nueva Muerte; **si pierde todas las monedas** la perderá y se verá una pantalla de **Game Over** con su alma errante vagando por el infierno. En cualquiera de las dos, podrá volver al inicio pulsando cualquier botón.

</details>

<details>
<summary> Diseño del juego </summary>

## Diseño del juego
<details>
  <summary> Sistema de fichas y ruleta </summary>
	
### Sistema de fichas y Ruleta
En cada juego podrás apostar una cantidad de **fichas básicas**, que se verán multiplicadas o restadas según el resultado de la partida. Cuando consigas **10.000** podrás realizar un **tiro en la Ruleta**, teniendo cuidado de no quedarte sin para seguir jugando. [Fichas](https://github.com/user-attachments/assets/6e74fa39-040a-4041-bf27-63ea778e95df)

Las **fichas rojas o almas** son un token especial que funcionan como tickets de bolera; sirven para comprar la Guadaña a cambio de **200** de estas. La forma de conseguir almas es jugando a los juegos en el modo Locura, explicado más adelante. [Almas rojas](https://github.com/user-attachments/assets/1eae08b4-7f11-42c6-9717-63d63d541c73)

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
La locura es una mecánica que hará que se modifiquen los juegos, permitiendo un cambio drástico en la jugabilidad. Esta se implementará mediante una barra que irá incrementando con cada partida que juegues (también afectada por el resultado de la ruleta). Tras un spin de la ruleta existirá la posibilidad de conseguir locura. Una vez conseguida, se podrán invertir **5 jugadas** con locura en los juegos o en la ruleta.
Durante este estado, la apariencia y las mecánicas de los juegos se verán alteradas. Además por cada victoria el jugador recibirá una cantidad de almas rojas correspondiente al multiplicador obtenido.
Durante este estado, la apariencia y las mecánicas de los juegos se verán alteradas.

Además por cada victoria el jugador recibirá una cantidad de **almas rojas** correspondiente al **multiplicador obtenido**.
</details>

<details>
<summary> Juegos </summary>
	
### Juegos
#### Slots: 
Utiliza la mecánica de los slots tradicionales: inicias con una apuesta y si consigues que tres figuras se alineen horizontalmente recuperarás el dinero multiplicado por la combinación ganadora.

Estéticamente, será una estructura 3x3 de celdas cuadradas con diferentes dibujos (número 6, telaraña, calavera, ojo, gato negro, diablillo, murciélago). El jugador activará la máquina pulsando en una palanca y las tres columnas empezarán a dar vueltas dan con una animación ‘cartoon’ donde las opciones rotan rápidamente. El jugador parará las columnas de izquierda a derecha con el botón correspondiente. Si se ha conseguido alguna alienación, las celdas involucradas brillarán en amarillo y se mostrará en mitad de la pantalla el multiplicador obtenido.

Valores a apostar:
- 10, 20, 50

Las recompensas de las combinaciones serán:
- 2 Telarañas: x1
- 3 Diablillos: x2
- 3 Telarañas x3
- 3 Murciélagos: x10
- 3 Ojos: x30
- 3 Calavera: x90
- 3 Gato Negro: x150
- Número 6: x3000

[Slot](https://github.com/user-attachments/assets/570579ca-8f5c-4d4a-a46f-b2c67f030dea)

#### Modo Locura:

Aparecerá una cuarta columna y cuarta fila (ahora un 4x4) y ahora el juego consistirá en hacer un 3 en raya en las nuevas celdas, donde el jugador se enfrentará contra la máquina de slots (IA). En un recuadro adicional situado a la izquierda de la máquina aparecerá el icono, de entre los ya mencionados (con frecuencia inversamente proporcional a su multiplicador), que se juega en cada momento, y el jugador de ese turno decidirá cómo colocarla. Para colocar las fichas el jugador solo deberá pulsar la celda vacía donde quiere poner el icono, que brillará de color blanco con el cursor encima (en caso de usar mando, brilla de blanco la celda en la que está posicionado, que mueve con el joystick, y coloca con el botón). La IA tendrá que evaluar qué casilla es la más óptima en función de si hay posibilidad de 3 en raya conectando con el símbolo que le haya tocado y de qué casillas estén libres.

Cada vez que el tablero, al principio vacío, llene sus 16 celdas, se ejecutará la animación de rodar de las columnas y se volverá a vaciar.

El juego acaba cuando alguno de los adversarios consigue alinear 3 símbolos iguales como en el 3 en raya, viéndose cómo las casillas alineadas brillan en amarillo (gana el jugador) o rojo (gana la IA). Si el jugador gana, se verá el multiplicador obtenido, igual que en el modo normal, y el número de almas rojas que haya conseguido, correspondiente al multiplicador de la combinación de 3 que haya logrado.
			
#### Bacará: 
Se reparten, una a una, cuatro cartas, dos para el jugador y dos para el banquero, sin embargo hay ocasiones en que se extrae una tercera. El juego comienza colocando una apuesta al jugador, al banquero o al empate. La mano que consiga o más se acerque al 9 gana. Cuando el jugador y el banquero totalizan el mismo puntaje, la mano es declarada en empate.
 
Las figuras, J, Q y K más los dieces, valen cero, los ases valen 1, las restantes cartas conservan su valor. En el bacará no es posible superar el nueve porque solo se contabiliza la última cifra. Ejemplo: El jugador recibe un 4 y un 8. El total es 12, como únicamente se toma la última cifra, la mano vale 2. Ninguna mano tendrá más de 3 cartas.

El reparto de la tercera carta se rige según la siguiente tabla:
![normas](https://github.com/user-attachments/assets/8646cc70-422b-4744-bf5f-2eda24cf1460)


Las diferentes apuestas:
- 20, 50 y 100

Las recompensas de las apuestas serán:
- Apuesta al jugador: x2
- Apuesta a la banca: x2
- Apuesta al empate: x8
		
#### Modo Locura:

Habrá una carta en la que saldrá un número aleatorio del uno al cuatro, dependiendo del número, se implementará una nueva mecánica al juego la cual afectará a las apuestas:

1. Cambio de cartas: Una vez repartidas las dos cartas para la banca y para el jugador, se cambiara la segunda carta del jugador por la segunda carta de la banca antes de darles la vuelta.
2. Dobles: si el jugador gana, gana el doble , si pierde, pierde el doble.
3. Tercera carta obligatoria: se repartirá la tercera carta a la vez que las otras dos de forma que tanto la banca como el jugador jugarán con tres cartas de golpe y no habrá una cuarta.
4. Acumulacion: en caso de que el jugador gane, tendrá que decidir si sigue apostando o termina la partida. Si sigue apostando, estará obligado a hacerlo con el dinero ganado en la anterior ronda, en caso de ganar la siguiente, sus ganancias no serán por dos sino por cuatro, y así sucesivamente. Pero si pierde, perderá todo lo ganado. En caso de ganar cinco veces seguidas se triplicara el multiplicador de apuesta en vez de duplicarlo, esto ocurrirá con cada cinco victorias.

#### Canicas:
Se sacarán de un saco 3 bolas de colores. El objetivo del juego consiste en predecir de qué color van a salir las bolas de colores. Los colores son rojo, cian, verde y amarillo. Para decidir la apuesta, abajo de la pantalla habrá diferentes fichas con una cantidad de apuesta(10, 20, 50 etc). Una vez seleccionada se pondrá en las diferentes casillas que el jugador quiera depositar la apuesta, estas casillas serán 4 casillas con 1 bola de cada color, 10 casillas con combinaciones de 2 colores y 20 casillas de combinaciones de 3 colores. Cuando ya se acabe la apuesta, se verán como salen 3 bolas de colores, revelando que combinación de colores es la ganadora. Si el jugador ha ganado, recibirá un mensaje de cuántas fichas ha obtenido.
		
Las diferentes apuestas y recompensas serán:	
- Apuesta 1 color: x2
- Apuesta 2 colores: x5
- Apuesta 3 colores: x20

#### Modo Locura:

Antes de que se muestran las bolas habrá un juego del trilero. En este se meterá una bola de un color aleatorio en un cubilete, al lado de este cubilete habrá otros dos. Se moverán los cubiletes entre sí para que el jugador no sepa dónde se sitúa la bola. Una vez terminado de mover los cubiletes el jugador deberá elegir dónde cree que está la bola, si acierta, ese color será descartado de la apuesta. 

[Boceto de las apuesta y tablero](https://github.com/user-attachments/assets/b66c7004-7c0c-4365-bff1-7614b5f253b2)

#### Peleas Reanimadas:
Las peleas reanimadas inician mostrando los perfiles de los peleadores. Estos perfiles se compondrán de nombre, apariencia (sprite) y cuota. En ese momento el jugador debe elegir su apuesta inicial. (Mirar Peleas Reanimadas 1 (Intro)).

La pelea se divide en turnos donde como en todos los combates por peleas se pega uno y luego el otro (Empieza siempre el que tenga mayor cuota). El giro es que una vez inicie la pelea el jugador NO tendrá control de los personajes peleando. Cada turno el jugador debe de elegir si aumenta la apuesta hacia alguno de los personajes o la reduce. En cada turno solo se puede hacer una de estas dos. Al reducir la apuesta es importante que sólo puedes retirar la mitad de las fichas apostadas a un personaje siempre que quede al menos la misma cantidad de fichas jugadas inicialmente.

Durante el turno de los personajes que pelean pueden ocurrir varios eventos que cambien el curso del combate.
- Golpes críticos hacen más daño
- El ataque falla al tratar de golpear
- Se pegan a sí mismos sin querer
- Se preparan para recibir un ataque y reducen el daño durante unos turnos.

Al terminar la pelea se resuelve los cálculos de las fichas:
- Se le quitan al jugador las invertidas en el perdedor
- Se multiplican las fichas las invertidas en el personaje ganador por la cuota y se le dan al jugador.

#### Modo Locura:

- La pelea es entre 4 personajes en vez de 2. Esto hace que los personajes eligen a quien atacan de forma aleatoria haciendo más difícil predecir qué va a pasar. De vez en cuando aparecerán espontáneos que intentarán interrumpir la pantalla y golpear a los luchadores. También intentarán modificar la apuesta. Para ello, el jugador deberá disparar (hacer click) en los fantasmas que supongan una amenaza para deshacerse de ellos y que el combate siga su curso natural. El movimiento de dichos espontáneos será independiente del transcurso de los turnos de los luchadores.
		
Ideas Extras (Si el tiempo lo permite):

- Los Personajes que pelean tienen un valor de ánimo que afecta a cómo se comportan. Este ánimo se refleja en pistas por un locutor que avisa de cómo se van a comportar los peleadores en cada turno. Este ánimo se establece a un valor aleatorio que sería reflejado en los perfiles de los luchadores con alguna palabra clave. Ej: Enfocado, descargando, derrotista, relajado, ...
- El ánimo sería un valor que se va modificando según un aumento o disminuya las apuestas o ocurran diferentes cosas en el combate. El locutor anunciará los cambios en las apuestas y de forma sutil los valores de ánimo de cada uno de los personajes.
Cuanto mayor sea el ánimo de un personaje, mayor será la probabilidad de que ocurran eventos positivos como críticos o que se preparen para recibir golpes. Por otro lado, si se reducen muchos las apuestas o el oponente recibe situaciones negativas, como que recibe un crítico o falla un golpe se reduce su ánimo. Aumentará la probabilidad de que falle, de que se distraiga o incluso en algunos casos llegar a que se puedan llegar a rendir sin acabar el combate.
- Que el valor de ánimo o la probabilidad de victoria cambie según quien se enfrente. Como puede ser de que vayan muy motivados contra ciertos rivales porque tienen alguna historia detrás, como podría ser un madrid vs barça. Esta historia corta de unas pocas líneas podría dar pistas de quién es más dado a ganar el enfrentamiento. 
- Ej: Goku en su larga carrera contra Naruto suele conectar golpes devastadores con una precisión impecable. Mientras que el pelo piña trata de seguirle el ritmo. ¿Acaso será otro día donde veremos como goku cena pizza con piña? 

[Peleas Reanimadas 1 (Intro)](https://github.com/user-attachments/assets/edbf9d59-1986-45bc-9c6d-49bba4cda15a)

[Escenario pelea normal](https://github.com/user-attachments/assets/07b4ac54-db16-46a8-8ff8-df9ce52206a1)

[Escenario pelea con Locura](https://github.com/user-attachments/assets/c29c9406-dbce-41fe-9a62-6b0f276d9147)
</details>
</details>

<details>
<summary> Hud </summary>
	
## Hud:
Todos los **botones** del juego funcionarán de la misma manera:
al pasar el cursor por encima cambiarán a un color determinado más brillante y al hacer click en ellos, se encogerán de tamaño para luego dar paso a su acción determinada.

En todas las pantallas del juego aparecerá siempre un **indicador** en la esquina superior izquierda con una ficha de poker al lado y a continuación la cantidad de **fichas** que tenga el jugador, y al lado, de la misma manera, aparecerá un **contador de almas**, pero con un símbolo de alma roja. La **barra de Locura**, de color morado, estará debajo de los contadores de ficha, y cuando se llene y se active el modo locura se volverá amarilla.

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

Contará con **sonidos** característicos de los **casinos** (giro de ruletas, el tintineo de monedas, eco de las máquinas tragamonedas…) todo con un **filtro antiguo** para acentuar la ambientación. La música ambiente será **alegre** reflejando la atmósfera del casino, pero se volverá **oscura y disonante** cuando se alcance el **modo Locura**.

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
