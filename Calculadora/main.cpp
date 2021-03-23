#include "calculator.h"
#include "calculatorTest.cpp"
#include "CalculatorFabricioFlavio.cpp"

int main(){
    Display* display = new DisplayFabricioFlavio();
    Cpu* cpu = new CpuFabricioFlavio();
    NumericKeyBoard* numericKeyBoard = new NumericKeyBoardFabricioFlavio(); 
    OperationKeyBoard* operationKeyBoard = new OperationKeyBoardFabricioFlavio();

    Calculator* calculator = new CalculatorFabricioFlavio(cpu, display, numericKeyBoard, operationKeyBoard);
    
    DisplayTest::run(display);
    CpuTest::run(cpu, display);
    CalculatorTest::run(calculator);

    return 0;
};