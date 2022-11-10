#include 

#define TONO_ERROR 600

#define TIME_INTERVAL 3000


LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 


int led = 5; //alarme

int horas = 0; //mostra as horas

int minutos = 0; //mostra segundos

int segundos = 0; //mostra segundos

int segundostotal = 0; //tempo total

int msg = 0; //Barrera para el mensaje de bienvenida


int start = A1; //iniciador

int começar = 1024; //Variável para armazenamento do botão iniciar

int buth = A5; //Botão de Horas

int butm = A4; //Botão de Minutos

int buts = A3; //Botão de segundos


int varbuth = 0; //Variável para armazenar o valor do botão de hora

int varbutm = 0; //Variável para armazenar o valor do botão de minutos

int varbuts = 0; //Variável para armazenar o valor do botão de segundos


void setup()

{

lcd.begin(16, 2); // Configuramos o número de colunas e linhas do LCD..



pinMode(led, OUTPUT); //Pin de alarme --> Salida

pinMode(buth, INPUT); //pino de botão horas --> Entrada

pinMode(butm, INPUT); //pino de botão minutos --> Entrada

pinMode(buts, INPUT); //pino de botão segundos --> Entrada

pinMode(start, INPUT); //pino de botão iniciar --> Entrada



msg = 0; //mensagem de boas-vindas

começar = 1024; 



varbuth = 1;

varbutm = 1;

varbuts = 1;



Serial.begin(9600);

}


void loop()

{

if(msg==0) //Mostra a mensagem de boas vindas apenas uma vez

{

lcd.setCursor(0,0);

lcd.print("Temporizador ");

lcd.setCursor(1,1);

lcd.print("Projeto HP ");

delay(2500);

msg = 1;

lcd.clear();

}

// LEITURA DOS BOTÕES E ESCOLHA DA HORA, NÃO SAI DO LOOP ATÉ QUE PRESS.

// O BOTÃO INICIAR

do

{



varbuth = analogRead(buth); //lemos o botão de horas

varbutm = analogRead(butm); //lemos o botão de minutos

varbuts = analogRead(buts); //lemos o botão de segundos



if(varbuth > 0) //Se o botão foi pressionado, aumentamos as horas em uma unidade

{

horas = horas + 1 ;

delay(250);

}



if(varbutm > 0) //Se o botão foi pressionado, aumentamos os minutos em uma unidade

{

minutos = minutos + 1;

if(minutos == 60) minutos = 0;

delay(250);

}



if(varbuts > 0) //Se o botão foi pressionado, aumentamos os segundos em uma unidade

{

segundos = segundos + 1;

if(segundos == 60) segundos = 0;

delay(250);

}



lcd.setCursor(0,0);

lcd.print("tempo"); //Mostrar mensagem e o HH:MM:SS que estamos aumentando




lcd.setCursor(4,1);


if (horas < 10) lcd.print("0"); //  Se as horas forem menores que 10, coloque um "0" na frente.

lcd.print(horas); // é exibido assim: H:M:S (1:M:S)

lcd.print(":");


if (minutos < 10) lcd.print("0"); //  Se os minutos forem menores que 10, coloque um "0" na frente.

lcd.print(minutos); // Sem este código, ele é exibido assim: H:M:S (H:1:S)


lcd.print(":");

if (segundos < 10) lcd.print("0"); // Se os segundos forem inferiores a 10, coloque um "0" na frente.

lcd.print(segundos); // Sem este código, ele é exibido assim: H:M:S (H:M:1)





} while(analogRead(start) == 0);// O menu de escolha do tempo é repetido até pressionarmos o botão iniciar.




segundostotal = segundos + (minutos * 60) + (horas * 60 * 60); //Converte o tempo escolhido em segundos!!

// UMA VEZ QUE O BOTÃO INICIAR É PRESSIONADO E O TEMPO ACUMULADO, ENTRA NO PRÓXIMO ENQUANTO

// E NÃO TERMINA ATÉ QUE A CONTAGEM TERMINE.

while (segundostotal > 0)

{

delay (1000); // Descontamos em períodos de 1 segundo


segundostotal--;



horas = ((segundostotal / 60)/ 60); // Convertemos o total de segundos em horas

minutos = (segundostotal / 60) % 60; // Convertemos o total de segundos em minutos

segundos = segundostotal % 60;  // Convertemos o total de segundos em períodos de 60 segundos


lcd.setCursor(0,0);

lcd.print("tempo restante"); /// Mostra a mensagem de tempo restante



lcd.setCursor(4,1);

if (horas < 10) lcd.print("0"); // Se as horas forem inferiores a 10, coloque um "0" na frente.

lcd.print(horas); // Sem este código, é exibido assim: H:M:S (1:M:S)

lcd.print(":");


if (minutos < 10) lcd.print("0"); // Se os minutos forem menores que 10, coloque um "0" na frente.

lcd.print(minutos); // Sem este código, ele é exibido assim: H:M:S (H:1:S)


lcd.print(":");

if (segundos < 10) lcd.print("0"); // se o segundo valor for inferior a 9 (unidade) coloca um zero antes

lcd.print(segundos); // Sem este código, ele é exibido assim: H:M:S (H:M:1)



if (segundostotal == 0) //Se o tempo acabar
// desliga o motor

{

while(1) // Loop infinito mostrando mensagem e campainha soando intermitentemente

{

lcd.clear();

lcd.setCursor(5,0);

lcd.print("tempo");

lcd.setCursor(3,1);

lcd.print("finalizado");





sonarTono(TONO_ERROR,TIME_INTERVAL);

exit(0);

}

}

}



}


//------------------------------------

//liga led 


//------------------------------------

void sonarTono(int tono, int duracion)

{

tone(led,tono,duracion);
digitalWrite(led, HIGH);
delay(duracion);

}