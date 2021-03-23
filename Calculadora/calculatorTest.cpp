/**
 * This file defines test routines for a calculator and its components.
 * Author: Lucio Valentin
 * Version: 20210316
 */
#include "calculator.h"

class DisplayTest{
  public:
    static void run(Display* display){
        display->clear();
        display->addDigit(ZERO);
        display->addDigit(ONE);
        display->addDigit(TWO);
        display->addDigit(THREE);
        display->addDigit(FOUR);
        display->addDecimalSeparator();
        display->addDigit(FIVE);
        display->addDigit(SIX);
        display->addDigit(SEVEN);
        display->addDigit(EIGHT);
        display->addDigit(NINE);
    };
};


class CpuTest{
  public:
    static void run(Cpu* cpu, Display* display){
          cpu->setDisplay(display);
          
          cpu->receiveDigit(ONE);
          cpu->receiveDigit(TWO);
          cpu->receiveDigit(THREE);
          
          cpu->cancel();
          
          cpu->receiveDigit(ONE);
          cpu->receiveDigit(TWO);
          cpu->receiveDigit(THREE);
          
          cpu->receiveOperation(ADDITION);

          cpu->receiveDigit(FOUR);
          cpu->receiveDigit(FIVE);
          cpu->receiveDigit(SIX);
          
          cpu->receiveOperation(EQUAL);
          
          cpu->reset();
    };
};

class CalculatorTest{
    public:
      static void run(Calculator* calculator){
          DisplayTest::run(calculator->getDisplay());
          CpuTest::run(calculator->getCpu(), calculator->getDisplay());
      };
    
};
