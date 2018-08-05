#include "nRF24.h"

nRF24::nRF24(SPIClass* _spi, uint8_t _csn, uint8_t _ce) :
	_SPI(_spi), pinCSN(_csn), pinCE(_ce)
{
}

nRF24::nRF24(uint8_t _csn, uint8_t _ce) :
	nRF24(&SPI, _csn, _ce)
{
}

nRF24::~nRF24()
{
	this->end();
}

bool nRF24::begin() {
	pinMode(pinCSN, OUTPUT);
	pinMode(pinCE,  OUTPUT);
	digitalWrite(pinCSN, HIGH);
	digitalWrite(pinCE,  HIGH);
	_SPI->begin();
}

bool nRF24::end() {
	pinMode(pinCSN, INPUT);
	pinMode(pinCE,  INPUT);
}

bool nRF24::handle() {
	
}
