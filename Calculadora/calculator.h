/**
 * This file defines the interfaces of a calculator and its components.
 * Author: Lucio Valentin
 * Version: 20210316
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

enum Digit{ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
enum Operation{ADDITION, SUBTRACTION, DIVISION, MULTIPLICATION, EQUAL};
enum Signal{POSITIVE, NEGATIVE};

class Display{
  public:
    virtual void addDigit(Digit number) = 0; // Adiciona um dígito na tela
    virtual void addDecimalSeparator() = 0; // Aciona o separador de casas decimais
    virtual void setSignal(Signal signal) = 0; // Define o sinal positivo ou negativo
    virtual void clear() = 0; // Limpa todos os dígitos
};

class Cpu{
  public:
    virtual void setDisplay(Display* display) = 0; // Conecta uma tela para a CPU
    
    virtual void receiveDigit(Digit digit) = 0; // Envia um dígito para o operando corrente
    virtual void receiveOperation(Operation operation) = 0; // Envia a operação e troca o operando corrente
    virtual void cancel() = 0; // Cancela os dígitos do operando corrente
    virtual void reset() = 0; // Cancela todos operandos e operação
};


class OperationKeyBoard{
  public:
    virtual void setCpu(Cpu *cpu) = 0;
    
    virtual void pressAddition() = 0;
    virtual void pressDivision() = 0;
    virtual void pressMultiplication() = 0;
    virtual void pressSubtraction() = 0;
    virtual void pressEquals() = 0;
};

class NumericKeyBoard{
  public:
    virtual void setCpu(Cpu *cpu) = 0;
    
    virtual void pressZero() = 0;
    virtual void pressOne() = 0;
    virtual void pressTwo() = 0;
    virtual void pressThree() = 0;
    virtual void pressFour() = 0;
    virtual void pressFive() = 0;
    virtual void pressSix() = 0;
    virtual void pressSeven() = 0;
    virtual void pressEight() = 0;
    virtual void pressNine() = 0;
};

class Calculator{
  public:
    virtual void setNumericKeyBoard(NumericKeyBoard* numericKeyBoard) = 0;
    virtual NumericKeyBoard* getNumericKeyBoard() = 0;
    
    virtual void setOperationKeyBoard(OperationKeyBoard* operationKeyBoard) = 0;
    virtual OperationKeyBoard* getOperationKeyBoard() = 0;

    virtual void setDisplay(Display* display) = 0;
    virtual Display* getDisplay() = 0;

    virtual void setCpu(Cpu* cpu) = 0;
    virtual Cpu* getCpu() = 0;
};

#endif
    

