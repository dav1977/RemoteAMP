

/*
//-----------------EEPROM-----------------------
unsigned char EEPROM_READ(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

unsigned char EEPROM_READ(unsigned int uiAddress)
{	while(EECR & (1<<EEWE));	// ��������  ���������� ���������� ������
	EEAR = uiAddress;			// ��������� ��������� �������� 
	EECR |= (1<<EERE);			// ���������� ������ �� ����� ����� ��������� EERE
	return EEDR;				// ������� ������ �� �������� ������ ������
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{	if ( EEPROM_READ(uiAddress)!=ucData)
	{	while(EECR & (1<<EEWE));	// ������� ��������� ���������� ������ 
		 __disable_interrupt(); 					// �������� ������ � ������ 
		EEAR = uiAddress;
		EEDR = ucData;
		EECR |= (1<<EEMWE);		// ������ ���. 1 �  EEMWE 
		EECR |= (1<<EEWE);			// ������ ������ � ������ ����� ��������� EEWE 
		 __enable_interrupt(); 
	}
}
*/