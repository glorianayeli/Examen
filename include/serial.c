/*Necesaria para utilizar la salida serial para las impresiones*/
#use delay(clock=16000000)


//variables de interrupcion
int flagSerial=0,flagMostrar=1, flagEnter=0, flagEcho=0;
int contador_buf=0;

//declaracion de vectores
char buffer[17]={""};
char caracter_recibido;

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif
//declaracion de funciones
void Evalua(char buffer, int &contador_buf, char caracter_recibido, int *flagEnter);
//interrupcion Serial
void isrRDA (void)
{
   flagSerial=1;
   flagEcho=1;
   caracter_recibido = getc();  
   if(contador_buf<17)
   { 
      buffer[contador_buf]= caracter_recibido;
      contador_buf++; 
   }
}

void Evalua (char buffer[], int &contador_buf, char *caracter_recibido, int *flagEnter)
{
   if(*caracter_recibido==0x0D)
   {
      *flagEnter=1;
   }
   //valida backspaces  
   if(*caracter_recibido==0x08)
   {
      buffer[contador_buf-1]=0;
      buffer[contador_buf-2]=0;
      contador_buf-=2;
   }
}
