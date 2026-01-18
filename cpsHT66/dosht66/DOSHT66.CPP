//DOSHT66 by ackerman
//MSDOS Borland TC 3.0
//DOSBOX
// COM1
// DOSBOX config (serial1=directserial realport:COMxx)

#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <bios.h>

#define COM1 0x3F8    // Dir E/S del puerto COM1

#define TIMEOUT 100   // Timeout en milisegundos (100 ms)
#define TIMETXDELAY 200
#define TIMETXDELAYCH 1000
#define TIMEINIT 1000
#define TIMETXRXDELAY 200


#define BIOS_COM1       0
#define BIOS_DATA_READY 0x0100
#define BIOS_SETTINGS   (0xE3) // 9600 baud, 8 bits, no parity, 1 stop bit

FILE * gb_serie;

//char paramPort[256]="1"; //COM1
char paramSendFile[256]="custom.dat";
unsigned char gb_do_dump=0;
unsigned char gb_do_send=0;
unsigned char gb_do_help=0;
unsigned char gb_do_wall= 1;
unsigned char gb_do_wopt= 0;
unsigned char gb_do_wch= 0;
unsigned char gb_do_pause=0;
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
//char cadOut[1024];
unsigned char gb_receiv[2048];
unsigned short int gb_receiv_cont=0;




void initSerialPort(void);
void sendData(const char* data,unsigned short int auxSize);
void receiveData(char expectedValue);
//void closeSerialPort(void);
void ShowOut(void);
void SaveOut(void);
void SendHandshake(void);
void DumpMemRadio(void);
void LoadSendFile(void);
void ShowSendFile(void);
void SendMemRadio(void);
void ClearBuffers(void);
void DoAction(int argc, char **argv);
void ChkFileSize(int aSize);
void GetParam(int argc, char **argv);
void ShowHelp(void);
unsigned char GetIdHex(char c);
void PrepareSendBytes(void);
void ShowDataSendTX(void);





//*******************************************
unsigned char GetIdHex(char c)
{
 unsigned char aReturn=0;
 
 for (unsigned char i=0;i<16;i++)
 {
  if (cHex[i]==c)
  {
   aReturn= i;
   break;
  }
 }
 
 return aReturn;
}



// Configurar el puerto COM1 (9600 baudios, 8 bits de datos, sin paridad, 1 bit de parada)
void initSerialPort()
{
 // Divisor de baud rate (para 9600 baudios con 1.8432 MHz de frecuencia base)
 outportb(COM1 + 3, 0x80);  // Habilitar divisor
 outportb(COM1 + 0, 12);     // Divisor de baja (9600 baudios)
 outportb(COM1 + 1, 0);      // Divisor de alta
 outportb(COM1 + 3, 0x03);   // 8 bits de datos, sin paridad, 1 bit de parada
 outportb(COM1 + 2, 0xC7);   // Habilitar interrupciones FIFO

// gb_serie = fopen("COM1", "wrb");

// bioscom(0, BIOS_SETTINGS, BIOS_COM1);

 printf("Serial port configured correctly\n");
}

// Enviar un byte de datos por el puerto COM1
void enviar_dato(unsigned char dato)
{
 while ((inportb(COM1 + 5) & 0x20) == 0);  // Esperar hasta que el puerto esté listo
 outportb(COM1, dato);  // Enviar el dato
}


//****************************************************************
void sendData(const char* data,unsigned short int auxSize)
{
 unsigned char aux;
 unsigned short int i;
 



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

/*
 fwrite(data,1,auxSize,gb_serie);
 fflush(gb_serie);
 */


 for (i=0;i<auxSize;i++)
 {
  enviar_dato(data[i]);
  //delay(1);
 }


}

//13000 - 1000
//x     - timeout


// Recibir un byte de datos desde el puerto COM1 con timeout
short int recibir_dato_con_timeout()
{
 unsigned char estado;
 char aReturn=' ';
 //unsigned short int contTimeOut=0;

 unsigned long start_time = clock();  // Obtener el tiempo inicial
 unsigned long start_time_out= start_time + ((CLOCKS_PER_SEC * TIMEOUT)/1000);

 // Esperar hasta que haya datos disponibles o el timeout se alcance 
 //estado= _bios_serialcom(_COM_STATUS, 0, 0);
 //estado= bioscom(3, 0, BIOS_COM1);
 //while ((estado & 0x01) == 0)
 //while ((estado & 0x01)==0)
 //while (!(estado & BIOS_DATA_READY))
 estado= inportb(COM1 + 5);
 while ((estado & 0x01)==0) 
 { 
  if (clock() >= start_time_out)
  {
   inportb(COM1);
   //bioscom(2, 0, BIOS_COM1);
   return -257;
  }
 }
 
 aReturn= inportb(COM1);
 //if ((aReturn=='\r')||(aReturn=='\n'))
 //{
 // return -2;
 //}
 //aReturn= _bios_serialcom(_COM_RECEIVE,0,0);
 //aReturn= bioscom(2, 0, BIOS_COM1);
 return aReturn;  // Leer el dato recibido
}



//****************************************************************
void receiveData(char expectedValue)
{
 unsigned char aux;
 char buffer[256];
 unsigned short int i;
 short int isTimeOut=0;
 unsigned short int bytesRead=0; 
 unsigned short int cont=0;
 unsigned short int topeReceived= sizeof(gb_receiv);

    
 if (gb_error==1)
 {
  return;
 }
 
// for (i=0;i<sizeof(buffer);i++)
// {
//  buffer[i]=0;
// }


 for (i=0;i<sizeof(buffer);i++)
 {	 
  isTimeOut= recibir_dato_con_timeout();
  cont++;
  if (isTimeOut==-257)
  {
   //printf("\nTimeOut\n");
   //return;
   break;
  }
  else
  {
   buffer[bytesRead]= (char)isTimeOut;
   bytesRead++;
   //delay(1);
  }
 }



 //bytesRead = fread(buffer, 1, 32, gb_serie);


 printf("RX(%d %d):",bytesRead,cont);
 for (i=0;i<bytesRead;i++)
 {
  aux=(unsigned char)buffer[i];
  printf("%02X ",aux);
  if (gb_receiv_cont<topeReceived)
  {
   gb_receiv[gb_receiv_cont]= aux;
   gb_receiv_cont++;
  }
 }
 printf("\n"); 
 
 if (buffer[0]!=expectedValue)
 {
  gb_warn=1;
  printf("WARN!!! expected value %02X\n",expectedValue);
 }

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

//**************************************************
void ShowOut()
{
 unsigned char contLine=0;
 printf("\n\n");
 printf("Total:%d\n",gb_receiv_cont);
 
 printf("[M31_Analog_Redio]\r\n");
 
 for (unsigned short int i=0; i<gb_receiv_cont;i++)
 {
  printf("%02X ",gb_receiv[i]);
  
  contLine++;
  if(contLine>=17)
  {
   printf(" \r\n"); 
   contLine=0;
  }
 }
}

//********************************************
void SaveOut()
{
 unsigned char contLine=0;
 FILE *fOut;
 
 fOut = fopen("dataload.dat","w");
 if (fOut!=NULL)
 { 
  fprintf(fOut,"[M31_Analog_Redio]\n");
 
  for (unsigned short int i=0; i<gb_receiv_cont;i++)
  {
   fprintf(fOut,"%02X ",gb_receiv[i]);
   
   contLine++;
   if(contLine>=17)
   {
    fprintf(fOut,"\n");
    contLine=0;
   }
  }     
  fclose(fOut);
 }
 else 
 {
  printf("ERROR!!! Write dump file\n");
 }
}


//***************************************
void DoAction(int argc, char **argv)
{
 if (gb_do_help==1)
 {
  ShowHelp();
  return;
 }
 
 if (gb_do_dump==1)
 {
  DumpMemRadio();
 }
 
 if (gb_do_send==1)
 {
  SendMemRadio();
 }
 
 if(gb_warn==1)
 {
  printf("WARN!!! Warning ocurred\n");
 }
 
 if(gb_error==1)
 {
  printf("ERROR!!! ERROR ocurred\n");
 } 
}

//***************************************
void ChkFileSize(int aSize)
{
 printf("Check file size(974 bytes):%d\n",aSize);
 if (aSize<974)
 {
  printf("ERROR!!! The file is not 974 bytes in size\n");
  gb_error= 1;
 }
}


//******************************************
void ClearBuffers()
{
 unsigned short i,j;
 
 //for (i=0;i<sizeof(cadOut);i++){ cadOut[i]=' '; }
 //cadOut[0]='\0';
 
 for (i=0;i<sizeof(gb_receiv);i++){ gb_receiv[i]=0; }     

 for (i=0;i<sizeof(dataSendFile);i++){ dataSendFile[i]=0; }     
 dataSendFile[0]='\0';
 
 for (j=0;j<20;j++)
 {
  for (i=0;i<64;i++)
  {
   dataSendTX[j][i]=' ';
  }
  dataSendTX[j][0]='\0';
 }
 
 gb_error=0;
 gb_warn=0;
 gb_receiv_cont= 0;
}

//********************************
void SendHandshake()
{
 gb_receiv_cont=0;
 //sendData("T999RAM");
 sendData(trama0,sizeof(trama0));
 delay(TIMETXRXDELAY);
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
 delay(TIMETXDELAY);
 gb_receiv_cont=0;
 

 sendData(trama1,sizeof(trama1));
 delay(TIMETXRXDELAY);
 receiveData(0x06); //expected value 0600000000000000
 gb_receiv_cont=0;
 delay(TIMETXDELAY);
 gb_receiv_cont=0;

 sendData(trama2,sizeof(trama2));
 delay(TIMETXRXDELAY);
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
 delay(TIMETXDELAY);
 gb_receiv_cont=0;

 sendData(trama3,sizeof(trama3));
 delay(TIMETXRXDELAY);
 receiveData(0xFF); //expected value FFFFFFFFFFFF
 gb_receiv_cont=0;
 delay(TIMETXDELAY);
 gb_receiv_cont=0;

 sendData(trama4,sizeof(trama4));
 delay(TIMETXRXDELAY);
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
 delay(TIMETXDELAY);
 gb_receiv_cont=0;

}


//***************************************************
void DumpMemRadio()
{
 int auxContBytes=0;

 initSerialPort();  //Init serial
 delay(TIMEINIT);

 SendHandshake(); 


 gb_receiv_cont=0;
 //for (unsigned char i=0;i<2;i++)
 for (unsigned char i=0;i<18;i++) 
 {
  sendData(trama5,sizeof(trama5));
  delay(TIMETXRXDELAY);  
  receiveData(0x57); //expected value 5700000D318DA802318DA802FFFFFFFFFF
  trama5[2]+=0x0D; //Add channel
  
  delay(TIMETXDELAYCH);
 }

 //closeSerialPort();  //Close serial

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
 
}

//******************************************
void PrepareSendBytes()
{
 unsigned char contRead=0;
 unsigned char contWrite=0;
 char carHex=' ';
 unsigned char highByte=0;
 unsigned char lowByte=0;
 unsigned char auxByte=0;
 unsigned short int tot=0;
 
 for (unsigned char canal=0;canal<18;canal++)
 {
  contRead=0;
  contWrite=0;  
  tot= strlen(dataSendTX[canal]);
  while (contRead<tot)
  {
   carHex= dataSendTX[canal][contRead];
   highByte= GetIdHex(carHex);
   contRead++;
   carHex= dataSendTX[canal][contRead];
   lowByte= GetIdHex(carHex);  
   contRead++;
  
   auxByte= (highByte<<4)|lowByte;
   dataSendTX[canal][contWrite]= auxByte;
   dataSendTX[canal][(contWrite+1)]='\0';
   contWrite++;
  }
 }
}

//******************************************
void ShowDataSendTX()
{
 printf("\n"); 
 for (unsigned char canal=0;canal<18;canal++)     
 {
  for (unsigned short int i=0;i<34;i++)
  {
   printf("%c",dataSendTX[canal][i]);  
  }
  printf("\n");
 }
}

//******************************************
void LoadSendFile()
{
 int c=0;
 unsigned short int cntLine=0;
 long int sizeFile=-1;
 
 gb_contDataSendFile=0; 
 
 FILE *f= fopen(paramSendFile,"r");
 if (f!=NULL)
 {
  fseek(f,0,SEEK_END);
  sizeFile= ftell(f);
  fseek(f,0, SEEK_SET);
  
  if (sizeFile<974)
  {
   gb_error=1;
   printf("ERROR!!! The file is not 974 bytes in size\n");
   fclose(f);
   return;
  }    
  
  while ((c= fgetc(f))!= EOF)
  {
   if (c=='\n')
   {                 
    cntLine++; 
    //printf("\n"); 
   }
   else
   {
    if (cntLine>0)
    {
     for (unsigned char i=0;i<16;i++)
     {
      if (c==cHex[i])
      {
       //printf("%c",c);
       dataSendFile[gb_contDataSendFile]=c;
       gb_contDataSendFile++;
      }
     }
    }
   }
  }//fin while
  
  fclose(f);
 }
 else
 {
  gb_error=1;
  printf("ERROR!!! File %s not load\n",paramSendFile);
 }
}

//******************************************
void ShowSendFile()
{
 unsigned char contLine=0;
 unsigned char canal=0;
 
 for (unsigned short i=0;i<gb_contDataSendFile;i++)
 {
  printf("%c",dataSendFile[i]);
  dataSendTX[canal][contLine]= dataSendFile[i];
  dataSendTX[canal][(contLine+1)]='\0';
  
  contLine++;
  if (contLine>=34)
  {//17x2
   printf("\n");
   contLine=0;  
   canal++; 
  }
 }
}

//******************************************
void SendMemRadio()
{
 gb_error=0;
 gb_warn=0;
 
 LoadSendFile();
 if(gb_error==1){ return; }
 ShowSendFile();
 if(gb_error==1) { return;}
 PrepareSendBytes();
 ShowDataSendTX();
     

 gb_error=0;     
 initSerialPort();  //Init serial
 if (gb_error==0)
 {  
  SendHandshake();
 
  gb_receiv_cont=0;
  for (unsigned char i=0;i<18;i++)
  {
   if (gb_do_wall==1)
   {
   }
   else
   {
    if (
        ((gb_do_wch==1)&&(i>=16)&&(i<18))
        ||
        ((gb_do_wopt==1)&&(i>=0)&&(i<16))
       )
    {//only send channel, skip options
     continue;
    }
   }

   sendData(dataSendTX[i],34);
   delay(TIMETXRXDELAY);  
   receiveData(0x06);  //expected value 06
   delay(TIMETXDELAYCH);
  }
 }

 //closeSerialPort();  //Close serial     
 
}

//***************************************
void GetParam(int argc, char **argv)
{
 gb_do_dump=0;     
 gb_do_send=0;
 gb_do_wall= 1;
 gb_do_wopt= 0;
 gb_do_wch= 0; 
 
 const char *cad; 
 
 for (unsigned short int i=1;i<argc;i++)
 {
  //printf("%d %s\n",i,argv[i]);
  if (strstr(argv[i],"-p")!=NULL)
  {  
//   cad= argv[i];
//   cad+=2;
//   //printf("%s\n",cad);
//   sprintf(paramPort,"%s",cad);
  }
  else
  {
   if (strstr(argv[i],"-d")!=NULL)
   {
    gb_do_dump=1;
   }
   else
   {
    if (strstr(argv[i],"-s")!=NULL)
    {
     cad= argv[i];
     cad+=2;
     //printf("%s\n",cad);
     sprintf(paramSendFile,"%s",cad);                               
     gb_do_send=1;
    }
    else
    {
     if (strstr(argv[i],"-wch")!=NULL)
     {
      gb_do_wall= 0;
      gb_do_wopt= 0;
      gb_do_wch= 1;
     }
     else
     {
      if (strstr(argv[i],"-wopt")!=NULL)
      {
       gb_do_wall= 0;
       gb_do_wopt= 1;
       gb_do_wch= 0;
      }         
      else
      {
       if (strstr(argv[i],"-wait")!=NULL)
       {
        gb_do_pause=1;
       }
       else
       {       
        if (strstr(argv[i],"-?")!=NULL)        
        {
         gb_do_help=1;
        }
       }
      }
     }
    }
   }
  }
 }
 
 //printf("Param Port:%s\n",paramPort);
 if (gb_do_dump==1)
 {
  printf("Param Dump\n");
 }
 if (gb_do_send==1)
 {
  printf("Param Send:%s\n",paramSendFile);
 }
 
 if (gb_do_wall==1)
 {
  printf("Write channels and options\n");
 }
 if (gb_do_wch==1)
 {
  printf("Write only channels\n");
 }
 if (gb_do_wopt==1)
 {
  printf("Write only options\n");
 } 
 
 if(gb_do_pause==1)
 {
  printf("Pause\n");
 }
 
 //system("PAUSE");
}


//***************************************
void ShowHelp()
{
 printf(" DOSHT66 by ackerman                            2026/01/18\n");
 printf(" ----------------------------------------------------------\n"); 
 printf("  -d              -- receive dump mem radio in dataload.dat\n");
 printf("  -s(file.ext)    -- send to radio file file.ext\n");
 printf("  -wch            -- send to radio only channels\n");
 printf("  -wopt           -- send to radio only options\n");
 printf("  -wait           -- when finished, wait to press the key\n");
 printf("  -?              -- show help\n");
 printf("\n");
 printf(" Example dump memory radio from COM1 in dataload.dat:\n");
 printf("   dosht66 -d\n");
 printf("\n");
 printf(" Example send custom.dat to memory radio from COM1:\n");
 printf("   dosht66 -scustom.dat\n");
 printf("\n");
 printf(" Example send custom.dat to memory radio only options from COM1:\n");
 printf("   dosht66 -scustom.dat -wopt\n");
 printf("\n");
 printf(" Example send custom.dat to memory radio only channels from COM1:\n");
 printf("   dosht66 -scustom.dat -wch\n");
 printf("\n"); 
}










int main(int argc, char **argv)
{
 //char dato;
 
 
 ClearBuffers();
 if (argc<2)
 {  
  ShowHelp();
 }
 else
 {
  GetParam(argc,argv);
  DoAction(argc,argv);
 } 

 if (gb_do_pause==1)
 {
//  system("PAUSE");
  while (!kbhit()){ }
 }
 return 0; 
 
 
 
 
 /*
 initSerialPort(); //Port serial config

 printf("CLOCKS_PER_SEC:%d\n",CLOCKS_PER_SEC);
 
 printf("Esperando datos en COM1...\n");

 delay(TIMEINIT);

 DumpMemRadio();
*/ 

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

// while (!kbhit())
// {
// }


  //fclose(gb_serie);

//    return 0;
}