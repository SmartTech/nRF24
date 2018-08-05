#ifndef _NRF24_H_
#define _NRF24_H_

#include <Arduino.h>
#include <SPI.h>

#include "nRF24L01.h"

typedef enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } rf24_pa_dbm_e ;
typedef enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS }                              rf24_datarate_e;
typedef enum { RF24_CRC_DISABLED = 0, RF24_CRC_8, RF24_CRC_16 }                        rf24_crclength_e;

class nRF24 {
	
	private:
	
		uint8_t pinCSN = 255;
		uint8_t pinCE  = 255;
		
		SPIClass _SPI = nullptr;
		
		void csn(bool mode);
		void ce(bool level);
		
		uint8_t read_register(uint8_t reg, uint8_t* buf, uint8_t len);
		uint8_t read_register(uint8_t reg);	
		
		uint8_t write_register(uint8_t reg, const uint8_t* buf, uint8_t len);
		uint8_t write_register(uint8_t reg, uint8_t value);
		
		uint8_t read_payload(void* buf, uint8_t len);
  
		uint8_t write_payload(const void* buf, uint8_t len, const uint8_t writeType);
		
		uint8_t get_status(void);
		
		void print_status(uint8_t status);
		void print_observe_tx(uint8_t value);
		void print_byte_register(const char* name, uint8_t reg, uint8_t qty = 1);
		void print_address_register(const char* name, uint8_t reg, uint8_t qty = 1);
		
		void toggle_features(void);
		void errNotify(void);
		
		uint8_t spiTrans(uint8_t cmd);
	
	public :
	
		nRF24(SPIClass* _spi, uint8_t _csn, uint8_t _ce);
		nRF24(uint8_t _csn, uint8_t _ce);
		~nRF24();
		
		bool begin(void);
		bool end();
		bool handle();
		
		bool isChipConnected();
		void startListening(void);
		void stopListening(void);
		
		bool txStandBy();
		bool txStandBy(uint32_t timeout, bool startTx = 0);
		
		void powerDown(void);
		void powerUp(void);
  
		void printDetails(void);
		
		bool available(void);
		bool available(uint8_t* pipe_num);
  
		void openWritingPipe(const uint8_t *address);
		void openWritingPipe(uint64_t address);
		void openReadingPipe(uint8_t number, const uint8_t *address);
		void openReadingPipe(uint8_t number, uint64_t address);
		
		void closeReadingPipe( uint8_t pipe ) ;
		
		bool    rxFifoFull();
		uint8_t flush_tx(void);
		uint8_t flush_rx(void);
		
		void read( void* buf, uint8_t len );
		
		bool write( const void* buf, uint8_t len );
		bool write( const void* buf, uint8_t len, const bool multicast );
		bool writeFast( const void* buf, uint8_t len );
		bool writeFast( const void* buf, uint8_t len, const bool multicast );
		bool writeBlocking( const void* buf, uint8_t len, uint32_t timeout );
		
		void writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);
		
		bool isAckPayloadAvailable(void);
		
		void whatHappened(bool& tx_ok,bool& tx_fail,bool& rx_ready);
		
		void startFastWrite( const void* buf, uint8_t len, const bool multicast, bool startTx = 1 );
		void startWrite( const void* buf, uint8_t len, const bool multicast );
		
		void reUseTX();
		
		bool testCarrier(void);
		bool testRPD(void) ;
		
		bool isValid() { return ce_pin != 0xff && csn_pin != 0xff; }
	
		bool failureDetected; 
		
		void setAddressWidth(uint8_t a_width);
		void setRetries(uint8_t delay, uint8_t count);
		void setChannel(uint8_t channel);
		void setPALevel ( uint8_t level );
		bool setDataRate(rf24_datarate_e speed);
		void setPayloadSize(uint8_t size);
		void setAutoAck(bool enable);
		void setAutoAck( uint8_t pipe, bool enable ) ;
		void setCRCLength(rf24_crclength_e length);
		
		uint8_t getChannel(void);
		uint8_t getPALevel( void );
		uint8_t getPayloadSize(void);
		uint8_t getDynamicPayloadSize(void);
		rf24_datarate_e getDataRate( void ) ;
		rf24_crclength_e getCRCLength(void);
		
		void enableAckPayload(void);
		void enableDynamicPayloads(void);
		void enableDynamicAck();
		
		void disableDynamicPayloads(void);
		void disableCRC( void ) ;
  
		bool isPVariant(void) ;
		void maskIRQ(bool tx_ok,bool tx_fail,bool rx_ready);
		uint32_t txDelay;
		uint32_t csDelay;
}

#endif // _NRF24_H_