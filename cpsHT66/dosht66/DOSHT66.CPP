//DOSHT66 by ackerman
//Borland TC 3.0

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COM1 0x3F8    // Dirección de E/S del puerto COM1
#define TIMEOUT 500   // Timeout en milisegundos (500 ms)



char paramPort[256]="14"; //COM14
char paramSendFile[256]="custom.dat";
unsigned char gb_do_dump=0;
unsigned char gb_do_send=0;
unsigned char gb_do_help=0;
char cHex[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char dataSendFile[1024];
unsigned short int gb_contDataSendFile=0;
char dataSendTX[20][64];

//HANDSHAKE BEGIN
char trama0[8]={0x02,0x54,0x39,0x39,0x39,0x52,0x41,0x4D}; //T999RAM
char trama1[1]={0x02};
char trama2[1]={0x06};
char trama3[1]={0x05};
char trama4[1]={0x06};
//HANDSHAKE END
//GET CHANNEL BEGIN
char trama5[4]={0x52,0x00,0x00,0x0D};
//GET CHANNEL END

unsigned char gb_error=0;
unsigned char gb_warn=0;
char cadOut[1024];
unsigned char gb_receiv[1024];
unsigned short int gb_receiv_cont=0;


// Configurar el puerto COM1 (9600 baudios, 8 bits de datos, sin paridad, 1 bit de parada)
void configurar_puerto_com1()
{
    // Divisor de baud rate (para 9600 baudios con 1.8432 MHz de frecuencia base)
    outportb(COM1 + 3, 0x80);  // Habilitar divisor
    outportb(COM1 + 0, 12);     // Divisor de baja (9600 baudios)
    outportb(COM1 + 1, 0);      // Divisor de alta
    outportb(COM1 + 3, 0x03);   // 8 bits de datos, sin paridad, 1 bit de parada
    outportb(COM1 + 2, 0xC7);   // Habilitar interrupciones FIFO
}

// Enviar un byte de datos por el puerto COM1
void enviar_dato(char dato)
{
    while ((inportb(COM1 + 5) & 0x20) == 0);  // Esperar hasta que el puerto esté listo
    outportb(COM1, dato);  // Enviar el dato
}


//****************************************************************
void sendData(const char* data,unsigned short int auxSize)
{
 unsigned char aux;
 unsigned short int i;

 for (i=0;i<auxSize;i++)
 {
  enviar_dato(data[i]);
 }

  printf("TX:");
  for (i=0;i<auxSize;i++)
  {
   aux= (unsigned char)data[i];
   printf("%02X ",aux);
  }
        
  printf("   TEXT:");
  for (i=0;i<auxSize;i++)
  {
   aux= (unsigned char)data[i];
   printf("%c",aux);
  }
  printf("\n");
//}
}



// Recibir un byte de datos desde el puerto COM1 con timeout
char recibir_dato_con_timeout()
{
 char aReturn=' ';

 unsigned long start_time = clock();  // Obtener el tiempo inicial
 unsigned long timeNow,auxTime;

 // Esperar hasta que haya datos disponibles o el timeout se alcance
 while ((inportb(COM1 + 5) & 0x01) == 0)
 {
  timeNow= clock();
  auxTime= (timeNow-start_time)*1000;
  auxTime= auxTime/CLOCKS_PER_SEC;

  if (auxTime > TIMEOUT)
  {
   // Si el tiempo de espera supera el timeout, retornar un valor especial
   //	    printf("Timeout alcanzado, no se recibieron datos\n");
   return -1;  // Devuelve -1 en caso de timeout
  }

 }

 aReturn= inportb(COM1);
 return aReturn;  // Leer el dato recibido
}



//****************************************************************
void receiveData(char expectedValue)
{
 unsigned char aux;
 char buffer[256]; 
 unsigned short int i;
 char isTimeOut=0;
 unsigned short int bytesRead=0;
    
 if (gb_error==1)
 {
  return;
 }

 for (i=0;i<sizeof(buffer);i++)
 {
  aux= recibir_dato_con_timeout();
  if (aux==-1) 
  {
   printf("\nTimeOut\n");
   return;
  }
  else
  {
   buffer[bytesRead]= aux;
   bytesRead++;
  }
 }
 
 printf("RX:");
 for (i=0;i<bytesRead;i++)
 {
  aux=(unsigned char)buffer[i];
  printf("%02X ",aux);
  gb_receiv[gb_receiv_cont]= aux;
  gb_receiv_cont++;	 
 }
 printf("\n"); 
 
/* 
 if (ReadFile(hComm, buffer, sizeof(buffer), &bytesRead, NULL))
 {
  if (bytesRead > 0)
  {
   buffer[bytesRead] = '\0';  //force null end
   printf("RX:");
   for (unsigned short int i=0;i<bytesRead;i++)
   {
    aux=(unsigned char)buffer[i];
    printf("%02X ",aux);
    gb_receiv[gb_receiv_cont]= aux;
    gb_receiv_cont++;
   }
   printf("\n");        
  }
  else
  {
   gb_error=1;            
   printf("ERROR!!! No data received.\n");
  }
 }
 else
 {
  gb_error=1;
  printf("ERROR!!! receiving data\n");
 }
 
 if (buffer[0]!=expectedValue)
 {
  gb_warn=1;
  printf("WARN!!! expected value %02X\n",expectedValue);
 }
*/ 
}


//********************************
void SendHandshake()
{
 gb_receiv_cont=0;
 //sendData("T999RAM");
 sendData(trama0,sizeof(trama0));
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
 

 sendData(trama1,sizeof(trama1));
 receiveData(0x06); //expected value 0600000000000000
 gb_receiv_cont=0;

 sendData(trama2,sizeof(trama2));
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;

 sendData(trama3,sizeof(trama3));
 receiveData(0xFF); //expected value FFFFFFFFFFFF
 gb_receiv_cont=0;

 sendData(trama4,sizeof(trama4));
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;

}



void DumpMemRadio()
{
 int auxContBytes=0;
 
// initSerialPort();  //Init serial
 
 SendHandshake();
  
 gb_receiv_cont=0;
 for (unsigned char i=0;i<18;i++)
 {
  sendData(trama5,sizeof(trama5));
  receiveData(0x57); //expected value 5700000D318DA802318DA802FFFFFFFFFF
  trama5[2]+=0x0D; //Add channel
 }

/*
 closeSerialPort();  //Close serial

 ShowOut();
 

 auxContBytes= (18+2); //Head [M31_Analog_Redio]
 auxContBytes+= (18*(17+2));
 ChkFileSize((gb_receiv_cont*2)+auxContBytes); //Check 974 bytes size
  
 if (gb_error==0)
 {
  SaveOut();
 }
 else
 {
  printf("ERROR!!! File dataload.dat not save\n");
 }
 */
}




int main(int argc, char **argv)
{
 char dato;

 //Configurar el puerto COM1
 configurar_puerto_com1();

 printf("Esperando datos en COM1...\n");

 DumpMemRadio();

/*
    while (1) {
	// Enviar datos al puerto COM1 si el usuario presiona una tecla
	if (kbhit()) {  // Si se presionó una tecla
	    dato = getch();  // Leer la tecla
	    printf("Enviando: %c\n", dato);
	    enviar_dato(dato);  // Enviar el dato por el puerto COM1
	}

	// Intentar recibir datos del puerto COM1
	dato = recibir_dato_con_timeout();  // Recibir un dato con timeout

	if (dato != -1) {  // Si se recibió un dato (no ocurrió un timeout)
	    printf("Recibido: %c\n", dato);
	} else {e
	    // No se recibió nada debido al timeout
	    // Se puede realizar otra acción si es necesario
	}
    }
*/

 while (!kbhit())
 {
 }

    return 0;
}