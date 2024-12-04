#include "mbed.h"
#include "Siren.h"

int main()
{

  Siren siren(PA_3, 1000);
  siren.activate();

  while (true) {
    ThisThread::sleep_for(1s);
    siren.deactivate();
    ThisThread::sleep_for(1s);
    siren.activate();
    siren.setToneFrequency(2000);
    ThisThread::sleep_for(1s);
    siren.deactivate();
    ThisThread::sleep_for(1s);
    siren.activate(); 
    siren.setToneFrequency(1000);
  }
  
}
