#include "calculator.h"
#include <string>
#include <sstream>
#include <iostream>

class DisplayFabricioFlavio: public Display{
  public:
    void addDigit(Digit number){
      switch(number){
        case ZERO: std::cout << 0; break;
        case ONE: std::cout << 1; break;
        case TWO: std::cout << 2; break;
        case THREE: std::cout << 3; break;
        case FOUR: std::cout << 4; break;
        case FIVE: std::cout << 5; break;
        case SIX: std::cout << 6; break;
        case SEVEN: std::cout << 7; break;
        case EIGHT: std::cout << 8; break;
        case NINE: std::cout << 9; break;
      }
    }

    void addDecimalSeparator(){
      std::cout << '.';
    }

    void setSignal(Signal signal){
      if(signal == NEGATIVE) std::cout << '-';
    }

    void clear(){
      std::cout << "\n";
    }
};

class CpuFabricioFlavio: public Cpu{
    Display *display;
    std::string stringValue = "";
    Operation lastOperation;
    float currentValue;      // Current value from the previous operations
    float newValue;          // New input
    int valuePosition = 0;   // Chooses if the current value is the first one
  public:
    void setDisplay(Display *display){this->display = display;}

    void receiveDigit(Digit digit){
      int temp;
      switch(digit){
        case ZERO:  temp = 0; break;
        case ONE:   temp = 1; break;
        case TWO:   temp = 2; break;
        case THREE: temp = 3; break;
        case FOUR:  temp = 4; break;
        case FIVE:  temp = 5; break;
        case SIX:   temp = 6; break;
        case SEVEN: temp = 7; break;
        case EIGHT: temp = 8; break;
        case NINE:  temp = 9; break;
      }
      std::string turnString = "";
      std::stringstream temporaryInteger;
      temporaryInteger << temp;
      temporaryInteger >> turnString;
      stringValue.append(turnString);
    }

    void receiveOperation(Operation operation){
      int turnInteger;

      sendToDisplay(stringValue);
      this->display->clear();

      std::stringstream temporaryString(stringValue);
      temporaryString >> turnInteger;
      stringValue.clear();

      // Checks if this is the first/second value
      if(valuePosition == 0) { 
        currentValue = turnInteger;
        valuePosition = 1;
      }
      else{
        newValue = turnInteger;
        doOperation(lastOperation);
        valuePosition = 1;
      }
      lastOperation = operation;
    }


    void doOperation(Operation operation){
    switch(operation){
      case EQUAL: 
        doOperation(lastOperation);
        valuePosition = 0;
        currentValue = 0;
        newValue = 0;
        break;
      case ADDITION: 
        currentValue += newValue;
        break;
      case SUBTRACTION:
        currentValue -= newValue;
        break;
      case MULTIPLICATION:
        currentValue *= newValue;
        break;
      case DIVISION:
        currentValue /= newValue;
        break;
      }
      if(operation != EQUAL){
        if(currentValue < 0) this->display->setSignal(NEGATIVE);
        std::string turnString = "";
        std::stringstream temporaryInteger;
        temporaryInteger << currentValue;
        temporaryInteger >> turnString;

        sendToDisplay(turnString);
        this->display->clear();
      }
    }

    void cancel(){
      newValue = 0;
      stringValue.clear();
      this->display->clear();
    }

    void reset(){
      valuePosition = 0;
      currentValue = 0;
      newValue = 0;
      stringValue.clear();
    }

    void sendToDisplay(std::string string){
      int i = 0;
      Digit digit;

      while(i < string.size()){
        switch(string[i]){
          case '0': digit = ZERO;
          break;
          case '1': digit = ONE;
          break;
          case '2': digit = TWO;
          break;
          case '3': digit = THREE;
          break;
          case '4': digit = FOUR;
          break;
          case '5': digit = FIVE;
          break;
          case '6': digit = SIX;
          break;
          case '7': digit = SEVEN;
          break;
          case '8': digit = EIGHT;
          break;
          case '9': digit = NINE;
          break;
        }
        this->display->addDigit(digit);
        i++;
      }
    }
};

class OperationKeyBoardFabricioFlavio: public OperationKeyBoard{
  Cpu *cpu;
  public:
    void setCpu(Cpu *cpu){this->cpu = cpu;}
    void pressAddition(){ this->cpu->receiveOperation(ADDITION);}
    void pressDivision(){ this->cpu->receiveOperation(DIVISION);}
    void pressMultiplication(){ this->cpu->receiveOperation(MULTIPLICATION);}
    void pressSubtraction(){ this->cpu->receiveOperation(SUBTRACTION);}
    void pressEquals(){ this->cpu->receiveOperation(EQUAL);}
};

class NumericKeyBoardFabricioFlavio: public NumericKeyBoard{
  Cpu *cpu;
  public:
    void setCpu(Cpu *cpu){this->cpu = cpu;}
    void pressZero(){ this->cpu->receiveDigit(ZERO);}
    void pressOne(){ this->cpu->receiveDigit(ONE);}
    void pressTwo(){ this->cpu->receiveDigit(TWO);}
    void pressThree(){ this->cpu->receiveDigit(THREE);}
    void pressFour(){ this->cpu->receiveDigit(FOUR);}
    void pressFive(){ this->cpu->receiveDigit(FIVE);}
    void pressSix(){ this->cpu->receiveDigit(SIX);}
    void pressSeven(){ this->cpu->receiveDigit(SEVEN);}
    void pressEight(){ this->cpu->receiveDigit(EIGHT);}
    void pressNine(){ this->cpu->receiveDigit(NINE);}
};

class CalculatorFabricioFlavio: public Calculator{
    Display* display;
    Cpu* cpu;
    NumericKeyBoard* numericKeyBoard; 
    OperationKeyBoard* operationKeyBoard;
  public:
    CalculatorFabricioFlavio(Cpu *cpu, Display *display, NumericKeyBoard *numericKeyBoard, OperationKeyBoard *operationKeyBoard){ 
      this->setCpu(cpu);
      this->setDisplay(display);
      this->setNumericKeyBoard(numericKeyBoard);
      this->setOperationKeyBoard(operationKeyBoard);

      this->cpu->setDisplay(display);
      this->numericKeyBoard->setCpu(cpu);
      this->operationKeyBoard->setCpu(cpu);
    }
    void setNumericKeyBoard(NumericKeyBoard* numericKeyBoard){
      this->numericKeyBoard = numericKeyBoard;
    }
    NumericKeyBoard* getNumericKeyBoard(){
      return this->numericKeyBoard;
    }
    
    void setOperationKeyBoard(OperationKeyBoard* operationKeyBoard){
      this->operationKeyBoard = operationKeyBoard;
    }
    OperationKeyBoard* getOperationKeyBoard(){
      return this->operationKeyBoard;
    }

    void setDisplay(Display* display){
      this->display = display;
    }
    Display* getDisplay(){
      return this->display;
    }

    void setCpu(Cpu* cpu){
      this->cpu = cpu;
    }
    Cpu* getCpu(){
      return this->cpu;
    }
};