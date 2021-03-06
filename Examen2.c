#include <18F4620.h>
#include <stdlib.h>
#include <include/serial.c>
#include <include/Timer.c>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

int contador=0, entero=0, flagTimer=0;
#int_timer0
void timer_0()
{
   flagTimer=1;
   output_d(0x01);
   contador++;
   set_timer0(126);
}
void main()
{
   char numero[2]={""};
   numero[1]="0x00";
   char palabra[11]={""};
   int indicador_numero=0;
   set_tris_c(0x80); 
   set_tris_d(0x01);
   //habilito mi interrupcion
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_BIT);//sino se agrega la linea RTCC_8_BIT TRABAJA A 16BITS
   set_timer0(126);
   enable_interrupts(int_timer0);
   enable_interrupts(global);
   printf("\nIngresar 3 a 10 caracteres un espacio y 3 numeros"); 
   while(TRUE)
   {
         if(flagEcho==1)
         {
            putc(caracter_recibido);
            flagEcho=0;
         }
         if(flagSerial == 1){
            Evalua(buffer, contador_buf, &caracter_recibido, &flagEnter);
         }
         if(flagSerial==1&&flagEnter==1)
         {
            for(int i=0;i<=16;i++)
            {
               if(buffer[i]!=0x32)
               {
                  palabra[i]=buffer[i];
               }
               if(buffer[i]==0x32)
               {
                  indicador_numero=i+3;
                  palabra[i]="0x00";
               }
            }
            numero[0]=buffer[indicador_numero];
            entero=atof(numero);
            if(flagTimer=1)
            {
               for(int repeticiones=entero;repeticiones>=1;repeticiones++)
               {
                  if(contador>=1)
                  {
                     printf(palabra);
                  }
               }
               flagTimer=0;
            }
   }

}
