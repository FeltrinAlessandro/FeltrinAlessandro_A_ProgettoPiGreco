#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int tempo;
int posPiGreco;
int posBomba;
int posVita;
int record;
int vita;
int punteggioAttuale;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  tempo = 5000;
  record = 0;

}

void loop() {
punteggioAttuale = 0;
HomeScreen();
}

void bottone (int pulsante)
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
    if(posVita!= -1 && digitalRead(posVita) == HIGH)//problema con i bottoni
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
    posVita=-1;
    posBomba=-1;
    posPiGreco=-1;
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
