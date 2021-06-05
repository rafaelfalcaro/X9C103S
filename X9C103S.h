#ifndef X9C103S_h
#define X9C103S_h

#include "Arduino.h"

// Definição das constantes
#define X9C103S_UP          HIGH
#define X9C103S_DOWN        LOW
#define X9C103S_MAX_AMOUNT  99
#define X9C103S_UNKNOWN     255

// Classe Principal
class X9C103S {
    public:
        // Método construtor
        X9C103S(uint8_t incPin, uint8_t udPin, uint8_t csPin);      
    
        // Funções
        void Change(uint8_t direction, uint8_t amount);             // Alterar a resistência
        void Decrease(uint8_t amount);                              // Decremento da resistência
        uint8_t Get();                                              // Ler valor atual da resistência
        void Increase(uint8_t amount);                              // Incremento da resistência
        void Reset();                                               // Reseta a resistência
        void Set(uint8_t value);                                    // Definir a resistência

    private:
        // Pinos do módulo X9C103S
        uint8_t _incPin;
        uint8_t _udPin;
        uint8_t _csPin;

        // Valor atual da resistência
        uint8_t _currentValue;
};

#endif