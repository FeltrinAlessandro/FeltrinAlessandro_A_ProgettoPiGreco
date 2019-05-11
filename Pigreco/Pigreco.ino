#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int tempo;
int posPiGreco;
int posBomba;
int posVita;
int record;
int vita;
int punteggioAttuale;
int button1;
int button2;
int button3;
int button4;
int button5;
int buttonStart;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  int button1 = 2;
  int button2 = 3;
  int button3 = 4;
  int button4 = 5;
  int button5 = 6;
  int buttonStart = 7;
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
  pinMode(buttonStart,INPUT);
  record = 0;
}

void loop() {
tempo = 5000;
punteggioAttuale = 0;
HomeScreen();
Bottone(buttonStart);
Gioco(3);
}

void Bottone (int pulsante)
{
  bool finito = false;
  while(!finito)
  {
    if(digitalRead(pulsante) == HIGH)
    {
      finito=true;
    }
  }
}

void ControlloRisultato ()
{
  int tempoInizio = millis();
  int tempoSecondario;
  bool finito=false;
  while(!finito)
  {
    if(posVita!= -1 && digitalRead(posVita) == HIGH)
    {
      vita++;
      finito = true;
    }
    else if(posBomba != -1 && digitalRead(posBomba) == HIGH)
    {
      vita--;
      finito = true;
    }
    else if(posPiGreco!=-1 && digitalRead(posPiGreco) == HIGH) 
    {
      punteggioAttuale++;
      finito = true;
    }
    tempoSecondario = millis();
    if(tempoSecondario-tempoInizio>tempo)
    {
      finito = true;
    }

    if(tempo>2000)
    {
      tempo = tempo - 200;
    }
  }
  RefreshScreen();
}

void Gioco(int numeroVite)
{
  vita = numeroVite;
  bool finito = false;
  int valoreCasuale;
  RefreshScreen();
  while(!finito)
  {
    posVita = -1;
    posBomba = -1;
    posPiGreco = -1;
    valoreCasuale = random(1,11);
    if(valoreCasuale>=1 && valoreCasuale <=6)
    {
      posPiGreco = random(2,7);
      lcd.setCursor((posPiGreco-1)*3,1);
      lcd.print("π");
    }
    else if(valoreCasuale>=7 &&  valoreCasuale <=9)
    {
      posBomba = random(2,7);
      lcd.setCursor((posBomba-1)*3,1);
      lcd.print("◘");
    }
    else
    {
      posVita = random(2,7);
      lcd.setCursor((posVita-1)*3,1);
      lcd.print("♥");
    }
    ControlloRisultato();
    if(punteggioAttuale > record)
    {
      record = punteggioAttuale;
    }
    if(vita==0)
    {
      finito= true;
    }
  }
}

void RefreshScreen()
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Vite:"+String(vita));
  lcd.setCursor(10,0);
  lcd.print("Punteggio:"+String(punteggioAttuale));
}

void HomeScreen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Premere Start");
  lcd.setCursor(0,1);
  lcd.print("Record:"+String(record));
}
