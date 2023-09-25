#include <LiquidCrystal.h>
LiquidCrystal lcd(1,2,4,5,6,7);
bool scris = false;
short rpm=0;
unsigned int time_wind = 0;
unsigned int time_termo = 0;
unsigned int time_lux =0;
short last=1023;

void wind()
{
  int s_val = analogRead(3);
  if((last-s_val)>4 || s_val-last>6)
  {
    last=s_val;
    rpm++;
  }
  if(millis()-time_wind>1000)
  {
    lcd.setCursor(0,1);
    lcd.print(rpm/6*2*3.62*3.14*0.036);
    lcd.print("km/h");
    rpm=0;
    time_wind+=998;
  }
}

void termometru(unsigned char poz)
{
  if((millis()-time_termo)>3000)
  {
    time_termo+=2985;
    if(poz < 11 || poz > 245)
    {
      if(poz > 245)
      {
        if(int(analogRead(1)/1024.0*5000/10) < 10)
        {
          lcd.setCursor(~poz,1);
          lcd.print(" "); 
          lcd.print(analogRead(0)/1024.0*5000/10); 
          lcd.print(char(223));
          lcd.print("C");  
        }
        else
        {
          lcd.setCursor(~poz,1);
          lcd.print(analogRead(0)/1024.0*5000/10);
          lcd.print(char(223));
          lcd.print("C");
        }
      }
      
      else if(poz < 11)
      {
        if(int(analogRead(1)/1024.0*5000/10) < 10)
        {
          lcd.setCursor(poz-1,0);
          lcd.print(" "); 
          lcd.print(analogRead(0)/1024.0*5000/10); 
          lcd.print(char(223));
          lcd.print("C");  
        }
        else
        {
          lcd.setCursor(poz-1,0);
          lcd.print(analogRead(1)/1024.0*5000/10);
          lcd.print(char(223));
          lcd.print("C");
        }
      } 
    }
  }
}


void luxmetter(unsigned char poz)
{
  if(millis()-time_lux>2000)
  {
    time_lux+=1990;
    short int lux = int(12518931*pow(((5.0-float(analogRead(0))/1023*5.0)/(float(analogRead(0))/1023*5.0)*2500),-1.405));
    if(poz < 11 || poz > 245)
      {
        if(poz > 247)
          { 
             
              lcd.setCursor(~poz,1);
              lcd.print(lux);
              lcd.print("lux");
              lcd.print("   ");
          }
      
        else if(poz < 10)
          {
              lcd.setCursor(poz-1,0);
              lcd.print(lux);
              lcd.print("lux");
              lcd.print("   ");
          }
     }
  }
}



void setup()
{
  lcd.begin(16,2);
  pinMode(3,INPUT);
}


void loop()
{
  if(!scris)
  {
    lcd.clear();
    lcd.setCursor(9,1);
    lcd.print("Edy&Sev");
    scris=true;
  }
  termometru(0);
  luxmetter(9);
  wind();


}
