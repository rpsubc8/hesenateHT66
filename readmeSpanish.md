# Modificar opciones Talkie HESENATE HT66

<h1>Descargo de responsabilidad</h1>
De acuerdo a las normativas de Telecomunicaciones de cada pais, la normativa PMR446 obliga a una potencia máxima de 500 mw en transmisión.
Queda por tanto en manos del usuario la responsabilidad de dicha modificación.<br>
La normativa LPD 433 sólo permite 10 mw de potencia máxima, por lo que los 500 o 700 mw de potencia son un problema.<br>
En FM comercial (87.5 MHz a 108.0 MHz) está prohibido todo.<br>
En CB 27 mhz, se permite 4W para modo FM. Sólo está registrado los 40 canales de la banda D (26.965 Mhz - 27.405 Mhz). La banda A,B,C y E, dependiendo del Pais, tendrá unas normativas. En España, aunque no está registrado, por antigüedad se considera como si fuera libre. La banda F, del canal 12 (28.005 Mhz) al 40 (28.305 Mhz) requiere autorización de radioaficionado.<br>
PRS (409.750 Mhz - 409.9875 Mhz.), está autorizado para China continental, Hong Kong y Macao.<br>
FRS 22 canales (462 Mhz - 467 Mhz), está autorizado para Estados Unidos y México.<br>
Freenet 6 canales (149.0250 MHz - 149.1125 MHz), está autorizado para Alemania.<br>
Las frecuencias de cazador requieren autorización.<br>
Las frecuencias marinas (156 Mhz - 174 Mhz) requieren autorización, así como posesión de embarcación, quedando prohibida la comunicación A(terrestre) B(terreste) directa. Al menos uno de los 2 puntos (A o B), debe ser una embarcación marina.<br>
El resto de frecuencias tienen sus normativas, tanto en bandas de radioaficionado como de uso privado, que deben consultarse de manera individual.<br>
El desconocimiento de la ley no exime de su cumplimiento.<br>
<br><br>

<h1>Preparación</h1>
El talkie HESENATE HT66 está pensado para cumplir la norma PMR446, de manera que viene con un software que bloquea la modificación de la potencia de Transmisión (low) a 500 mw.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewabout.gif'></center>
Dicho software, se puede descargar desde: <a href='https://cps22.s3.amazonaws.com/HT66.exe'>https://cps22.s3.amazonaws.com/HT66.exe</a><br>
<br>
O desde: <a href='https://github.com/rpsubc8/hesenateHT66/tree/main/originalHT66'>https://github.com/rpsubc8/hesenateHT66/tree/main/originalHT66</a><br>
<br>
He dejado una versión portable (portableHT66.zip) sin falta de instalar, con la modificación de la potencia a high ya por defecto:<br><br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66'>https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66</a>
<br><br>
Una vez lanzado el programa, debería mostrarnos el TX power en High en cada canal:<br><br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewhighnarrow.gif'></center>
De esta forma, una vez que enviemos los datos al talkie, quedará ya modificado.<br>
El resto de parámetros pueden ser modificados, como siempre.<br>
Hay que recordar que el combo de RX Freq(mhz) y TX Freq(Mhz) no debería modificarse, es decir, debería dejarse vacio, tal y como está, dado que equivale a las frecuencias PMR por defecto. Si se modifica, se estará fuera de la normativa.<br>
<br><br>


<h1>Explicación</h1>
Si no queremos usar la versión portable, tan sólo tenemos que elegir en el menú (File-->Open) el archivo (highnarrow.dat):<br><br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66'>https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66</a>
<br><br>
El archivo está en formato ASCII con contenido en hexadecimal, con una entrada por cada canal (01-16) por línea (High  Narrow):<br>
<pre>
[M31_Analog_Redio]
57 00 00 0D 31 8D A8 02 31 8D A8 02 FF FF FF FF FF 
57 00 0D 0D 13 92 A8 02 13 92 A8 02 FF FF FF FF FF 
57 00 1A 0D F5 96 A8 02 F5 96 A8 02 FF FF FF FF FF 
57 00 27 0D D7 9B A8 02 D7 9B A8 02 FF FF FF FF FF 
57 00 34 0D B9 A0 A8 02 B9 A0 A8 02 FF FF FF FF FF 
57 00 41 0D 9B A5 A8 02 9B A5 A8 02 FF FF FF FF FF 
57 00 4E 0D 7D AA A8 02 7D AA A8 02 FF FF FF FF FF 
57 00 5B 0D 5F AF A8 02 5F AF A8 02 FF FF FF FF FF 
57 00 68 0D 41 B4 A8 02 41 B4 A8 02 FF FF FF FF FF 
57 00 75 0D 23 B9 A8 02 23 B9 A8 02 FF FF FF FF FF 
57 00 82 0D 05 BE A8 02 05 BE A8 02 FF FF FF FF FF 
57 00 8F 0D E7 C2 A8 02 E7 C2 A8 02 FF FF FF FF FF 
57 00 9C 0D C9 C7 A8 02 C9 C7 A8 02 FF FF FF FF FF 
57 00 A9 0D AB CC A8 02 AB CC A8 02 FF FF FF FF FF 
57 00 B6 0D 8D D1 A8 02 8D D1 A8 02 FF FF FF FF FF 
57 00 C3 0D 6F D6 A8 02 6F D6 A8 02 FF FF FF FF FF 
57 00 D0 0D 18 01 06 00 00 F8 FF 00 FF FF FF E8 0E 
57 00 DD 0D FF FF FF FF FF FF FF FF FF FF FF FF FF 
</pre>

Lo que nos interesa en el último byte de cada línea, que debe ser:
<pre>
 FF   --> High  Narrow 
</pre>
O bien:
<pre>
 FB   --> High  Wide
 F3   --> Low  Wide
 F7   --> Low Narrow
</pre>

El W/N se refiere a la expansión de la banda, que para PMR tiene que ser Narrow. El modo Wide sería para el caso de experimentar con modos digitales en modo analógico, para evitar la pre-emphasis y de-emphasis de los filtros de entrada y salida de micrófono y altavoz.


<br>
<h1>Manual</h1>
He dejado un manual en español convertido a OCR y PDF:<br><br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf'>https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf</a><br>
<br>
También existe un manual multiidioma distribuido por la compañia PTTalky, tanto para el modelo HT66, como el Plus:<br>
<br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66HT66PLUSManual.pdf'>https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66HT66PLUSManual.pdf</a>


<br><br>
<h1>Frecuencias</h1>
En el programa Portable ya tenemos el archivo Setting.ini modificado, pero sino tendremos que crear una entrada que amplie el rango de 1 a 590 Mhz, en lugar de los 446 Mhz:<br>
<pre>
Language = English
Comport = 14
masterkey = 123456
RadioName = [M31_Analog_Redio]

[Frequency]
Fqvalue0 = [446-446.2MHz]
Datamin0 = 446
Datamax0 = 446.2

Fqvalue1 = [1-590MHz]
Datamin1 = 1
Datamax1 = 590

[Channel]
Channel = 16
Communication = TCOGRAM
</pre>

Si no tenemos esta entrada Fqvalue1, así como el combo seleccionado, se aplicará el filtro de PMR, que junto con las limitaciones del programa, al final se traducirá en un recorte de frecuencias a las de por defecto. Es decir, que asignará la banda PMR americana (425 Mhz), que nada tiene que ver con la Europea (446 Mhz). Lo mismo sucederá si empezamos a tocar el combo de frecuencias.<br>

He creado una utilidad en HTML5 para poder modificar todos los parámetros bloqueados, en donde se encuentran también las frecuencias.<br><br>
<a href='https://rpsubc8.github.io/hesenateHT66/'>https://rpsubc8.github.io/hesenateHT66/</a><br><br>
Se dispone de un botón para generar el .DAT para las frecuencias por defecto para PMR 446, así como LPD. Dado que se tiene 16 canales y el LPD son 69, he dejado varios grupos.<br>
Las opciones son:<br><br>

| Botón          | Acción                         |
| -------------- | ------------------------------ |
| PMR 446        | Genera los 16 canales de PMR   |
| LPD(01-16)     | Genera canal 1 al 16 de LPD    |
| LPD(17-32)     | Genera canal 17 al 32 de LPD   |
| LPD(33-48)     | Genera canal 33 al 48 de LPD   |
| LPD(54-69)     | Genera canal 54 al 69 de LPD   |
| CB(01-16)      | Genera canal 1 al 16 de CB     |
| CB(17-32)      | Genera canal 17 al 32 de CB    |
| CB(25-40)      | Genera canal 25 al 40 de CB    |
| FM(comercial)  | Un par de cadenas FM           |
| PRS 409(01-16) | Canal 1 al 16 PRS 409 Mhz      |
| PRS 409(05-20) | Canal 1 al 16 PRS 409 Mhz      |
| FRS22(01-16)   | Canal 1 al 16 FRS22 462 Mhz    |
| FRS22(07-22)   | Canal 7 al 22 FRS22 462 Mhz    |
| Freenet 159    | Canal 1 al 6 Freenet 159 Mhz   |
| Asturias       | Caza Asturias 150 Mhz          |
| Cantabria      | Caza Cantabria 150 Mhz         |
| Castilla Leon  | Caza Castilla Leon 151 Mhz     |
| Marine(01-16)  | Marina Canal 1 al 16 España    |
| Marine(17-63)  | Marina Canal 1 al 16 España    |
| Marine(64-81)  | Marina Canal 1 al 16 España    |
| Marine(71-88)  | Marina Canal 1 al 16 España    |
| Marine(01-16)  | Marina Canal 1 al 16 EEUU      |
| Marine(17-63)  | Marina Canal 1 al 16 EEUU      |
| Marine(64-81)  | Marina Canal 1 al 16 EEUU      |
| Marine(71-88)  | Marina Canal 1 al 16 EEUU      |
| Clear          | Borra todo                     |
| Save           | Guarda el fichero fisicamente  |
| Examinar       | Selecciona fichero (no lo lee) |
| Load           | Lee el fichero seleccionado    |
| Start          | Genera el fichero              |


<br>
Para el caso de FM (comercial) hay que tener cuidado con el PTT en la transmisión, dado que no está bloqueada por hardware y transmitirá en FM en potencia LOW (500 o 700 mw), que es ilegal, por tanto es sólo para experimentación. Se genera con modo WIDE.<br>

En el programa portable de HT66 he modificado el Setting.ini para un rango de 1 Mhz a 590 Mhz, que debemos siempre asegurarnos de que está seleccionado dicho combo.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/preview87to470.gif'></center>
Los pasos a seguir son seleccionar dicho combo, así como dar a NEW y ver que queda vacio:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewclear87to470.gif'></center>
Una vez más, debemos de volver a comprobar que tenemos el combo de 1-590 Mhz seleccionado. Después debemos de cargar el dat que hemos generado con la utilidad HTML, desde el menú.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewOpen.gif'></center>
Luego podemos generar el archivo desde el html5, pulsando el botón LPD(01-16) para generar los 16 primeros canales de LPD:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewhtml5lpd.gif'></center>
Si abrimos el archivo customLPD.dat generado con la utilidad HTML con las frecuencias LPD, nos aparecerá algo similar:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewLPD.gif'></center>
Las frecuencias, que en este caso para LPD son 433 Mhz, nunca se verán reflejadas en el programa, sólo la potencia y el ancho de banda, dado que es una limitación del programa. Debemos de chequear que realmente se van a grabar las frecuencias, es decir, que se ha leido bien. Para ello debemos desde el programa portable (no el html) desde el menú, mandar guardar, por ejemplo con el nombre customLPDchk.dat y contrastar que tanto customLPD.dat como customLPDchk.dat son iguales con un editor de textos, como puede ser el notepad++.<br>
Debemos chequear ese archivo customLPDchk.dat desde la utilidad html5 desde el botón examinar, y luego dando al botón Load. Si en algún momento, vemos que las frecuencias no son las correctas, es decir, que esperamos 433 Mhz y nos sale 153 Mhz, como aquí:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewhtml5lpderror.gif'></center>
Pues tendremos que volver a seguir los mismos pasos en el programa portable, es decir, volver abrir el archivo customLPD.dat y volver a guardarlo como customLPDchk.dat, para volver a chequear que son iguales y desde el html5 salen las frecuencias correctas. Suele salir a la primera, pero en ocasiones hay que realizar estos pasos 2 veces.<br>
Es importante, porque en el programa estamos ciegos en el tema de frecuencias, al no mostrarse, y dependemos de la versión html para contrastar. Si no es correcto, apareceremos por frecuencias y potencias que no están homologadas. Es ideal tener otro talkie de los buenos,que permita chequear también si todo es correcto.<br><br>

Una vez que el chequeo y todo es correcto, es cuando podemos darle a enviar los datos a la radio.<br>

El HESENATE HT66 soporta FM comercial, tanto recepción como transmisión, 136 Mhz, 140 Mhz y los 400 Mhz. Otra cosa distinta, es como se comporta.<br>
Soporta 11 metros (27 mhz) CB en modo FM, pero con la limitación de la antena. Con un talkie Alan Midland 42 a una distancia de 1 metro, la señal para modo LOW es de 3 sobre 9, mientras que con HIGH es de 5 sobre 9. Sirve por tanto, para pruebas simples.<br>
Con la utilidad en html5 se puede probar todo el rango de frecuencias que queramos, con tan sólo introducirlas a mano y darle a start para generar el custom.dat. De esta forma, podremos ver los límites del talkie.<br>

Debemos prestar atención que el archivo .DAT debe tener exactamente 974 bytes.
<br><br>



<h1>Otros Talkys</h1>
Existen varios talkys distribuidos por la compañía PTTalky, que comparten características con el HT66:
<pre>
 HT66 Plus
 FR1 y FR1 Plus
 FR2 y FR2 Plus
 PR2 y PR2 Plus
</pre>
El software cps se encuentra disponible:<br><br>
<a href='https://pttalky.com/pages/software'>https://pttalky.com/pages/software</a><br>
<br>
Al ser similares, podiamos aplicar soluciones similares, pero existen ciertos problemas.<br>
De lo que he podido comprobar, dado que sólo tengo el HT66, es que el software del FR1 es el único que consigue comunicarse con el PMR HT66 y lee los datos correctamente. Lamentablemente, a la hora de guardar el archivo, así como enviar a la radio, se basa en el índice del combobox de las frecuencias, que en este caso es la normativa FRS22, es decir, 469 Mhz, por tanto, nunca deja guardar la frecuencia bien. Este software era interesante, porque tiene desbloqueado el combo de Power TX, dado que la normativa FRS, permite un par de canales en modo HIGH.
<br>
El PR2 está pensado para PMR 446, y por lo que he podido comprobar, el sistema de archivos si deja cambiar frecuencias, así que es posible que funcione algo similar.<br>
El resto, tienen parámetros extras en diferentes posiciones del archivo, que supongo que habría que adaptar.<br>
<br><br>
<br>


<h1>HT66 Plus</h1>
El programa lo lee, pero no tengo la radio real para probar.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewht66high.jpg'></center>
He dejado los .dat de las configuraciones LOW, HIGH, NARROW y WIDE:
<ul>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusLowNarrow.dat'>ht66plusLowNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusHighNarrow.dat'>ht66plusHighNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusLowWide.dat'>ht66plusLowWide.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusHighWide.dat'>ht66plusHighWide.dat</li>
</ul>
<br><br>

<h1>PTTalky PR2</h1>
El programa lo lee, pero no tengo la radio real para probar.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewpr2high.jpg'></center>
He dejado los .dat de las configuraciones LOW, HIGH, NARROW y WIDE:
<ul>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2lowNarrow.dat'>pr2lowNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2highNarrow.dat'>pr2highNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2lowWide.dat'>pr2lowWide.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2highWide.dat'>pr2highWide.dat</li>
</ul>
<br><br>

<h1>PTTalky PR2 Plus</h1>
El programa lo lee, pero no tengo la radio real para probar.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewpr2plushigh.jpg'></center>
He dejado los .dat de las configuraciones LOW, HIGH, NARROW y WIDE:
<ul>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusLowNarrow.dat'>pr2plusLowNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusHighNarrow.dat'>pr2plusHighNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusLowWide.dat'>pr2plusLowWide.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusHighWide.dat'>pr2plusHighWide.dat</li>
</ul>



<br><br>
<h1>Custom CPS</h1>
He creado un CPS simplificado para Windows (32 bits) para poder hacer el dump, así como poder enviar los custom.dat a la radio por puerto serie usb, sin necesidad de usar el oficial de HESENATE.<br>
No tiene chequeos, y por ahora es de andar por casa, pero permite enviar correctamente las frecuencias y hacer un dumpeado del contenido actual de la radio.<br><br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewcpswinht66.gif'></center>
<a href='http://rpsubc8.github.io/hesenateHT66/cpsHT66/winht66/winht66.exe'>winht66.exe</a><br>
<br>
Podemos enviar a la radio toda la información de los canales y opciones, o bien sólo una de las partes, con la opción -wch o -wopt. Las opciones son el VOX, squeltch, ahorro de batería, etc...<br>
Si quisieramos leer el contenido de la radio del puerto COM5:<br>
<pre>
 winht66 -p5 -d
</pre>
Por defecto, al invocar al comando -d los datos se guardarán en el archivo dataload.dat<br><br>
Si quisieramos enviar el contenido completo de un archivo (custom.dat), tanto de los 16 canales, como las opciones a la radio en el puerto COM5:<br>
<pre>
 winht66 -p5 -scustom.dat
</pre>
<br>
También he añadido una versión para MSDOS con DOSBOX usando el puerto COM1.
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewcpsdosht66.gif'></center>
<a href='http://rpsubc8.github.io/hesenateHT66/cpsHT66/dosht66/DOSHT66.EXE'>DOSHT66.EXE</a><br>
<br>
La opción de lectura (-d) no funciona muy bien en DOSBOX, pero el envio de datos hacia la radio, si, por lo que puede ser útil.<br>
En el fichero de configuración del DOSBOX se debe activar las opciones de directserial y especificar el puerto físico real, que si fuera el COM14,sería:
<pre>
 serial1=directserial realport:COM14
</pre>
<br>
También he añadido una versión para HTML5 con webserial en Google Chrome, Microsoft Edge y Opera, desde el botón <b>back uart web</b>.<br><br>
<a href='http://rpsubc8.github.io/hesenateHT66/uartht66.html'>UART HT66</a><br><br>
Tan sólo debemos seleccionar el puerto COM1 desde el navegador:
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewUartSelectWebSerial.gif'></center>
Se permite el dump de la radio, así como en elvío de los canales y las opciones:
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewUartDumpWebSerial.gif'></center>
Es recomendable volver a recargar la página principal, cada vez que se realiza una operación de lectura o envió a radio, para garantizar que el puerto UART no esté bloqueado o con datos raros.<br>
En cualquier momento, podemos volver al html5 de las frecuencias desde el botón <b>back frequencies web</b>.


