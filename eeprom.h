

/*
//-----------------EEPROM-----------------------
unsigned char EEPROM_READ(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

unsigned char EEPROM_READ(unsigned int uiAddress)
{	while(EECR & (1<<EEWE));	// Ожидание  завершения предыдущей записи
	EEAR = uiAddress;			// Установка адресного регистра 
	EECR |= (1<<EERE);			// Разрешение чтения из ЭППЗУ путем установки EERE
	return EEDR;				// Возврат данных из регистра данных ЭСППЗУ
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{	if ( EEPROM_READ(uiAddress)!=ucData)
	{	while(EECR & (1<<EEWE));	// Ожидаем окончание предыдущей записи 
		 __disable_interrupt(); 					// Указание адреса и данных 
		EEAR = uiAddress;
		EEDR = ucData;
		EECR |= (1<<EEMWE);		// Запись лог. 1 в  EEMWE 
		EECR |= (1<<EEWE);			// Запуск записи в ЭСППЗУ путем установки EEWE 
		 __enable_interrupt(); 
	}
}
*/