#include "Arduino.h"
#include "X9C103S.h"

//************************************************************************************
// Funções Públicas

// Alterar a resistência
void X9C103S::Change(uint8_t direction, uint8_t amount) {
    amount = constrain(amount, 0, X9C103S_MAX_AMOUNT);
    digitalWrite(_udPin, direction);
    digitalWrite(_incPin, HIGH);
    digitalWrite(_csPin, LOW);

    for (uint8_t i=0; i<amount; i++) {
        digitalWrite(_incPin, LOW);
        delayMicroseconds(2);
        digitalWrite(_incPin, HIGH);
        delayMicroseconds(2);
        if (_currentValue != X9C103S_UNKNOWN) {
            _currentValue += (direction == X9C103S_UP ? 1 : -1);
            _currentValue = constrain(_currentValue, 0, X9C103S_MAX_AMOUNT);
        }
    }
    digitalWrite(_csPin, HIGH);
}

// Decremento da resistência
void X9C103S::Decrease(uint8_t amount) {
    amount = constrain(amount, 0, X9C103S_MAX_AMOUNT);
    Change(X9C103S_DOWN, amount);
}

// Ler valor atual da resistência
uint8_t X9C103S::Get() {
    return _currentValue;
}

// Incremento da resistência
void X9C103S::Increase(uint8_t amount) {
    amount = constrain(amount, 0, X9C103S_MAX_AMOUNT);
    Change(X9C103S_UP, amount);
}

// Reseta a resistência
void X9C103S::Reset() {
    Decrease(X9C103S_MAX_AMOUNT);
    _currentValue = 0;
}

// Definir a resistência
void X9C103S::Set(uint8_t value) {
    value = constrain(value, 0, X9C103S_MAX_AMOUNT);
    if (_currentValue == X9C103S_UNKNOWN) Reset();
    if (_currentValue > value) {
        Change(X9C103S_DOWN, _currentValue-value);
    } else if (_currentValue < value) {
        Change(X9C103S_UP, value-_currentValue);
    }
}

// Define automaticamente os pinos do módulo como IN/OUT
void X9C103S::SetPins(uint8_t csPin, uint8_t incPin, uint8_t udPin) {
    _incPin = incPin;
    _udPin  = udPin;
    _csPin  = csPin;
    _currentValue = X9C103S_UNKNOWN;

    pinMode(_incPin, OUTPUT);
    pinMode(_udPin,  OUTPUT);
    pinMode(_csPin,  OUTPUT);
    digitalWrite(_csPin, HIGH);

    Reset();
}