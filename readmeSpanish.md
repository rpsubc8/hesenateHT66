# Modificar opciones Talkie HESENATE HT66

<h1>Descargo de responsabilidad</h1>
De acuerdo a las normativas de Telecomunicaciones de cada pais, la normativa PMR446 obliga a una potencia máxima de 500 mw en transmisión.
Queda por tanto en manos del usuario la responsabilidad de dicha modificación.
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
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf'>https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf</a>


<br>
<h1>Frecuencias</h1>
<br><br>
He creado una utilidad en HTML5 para poder modificar todos los parámetros bloqueados, en donde se encuentran también las frecuencias.
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/html5/index.html'>https://github.com/rpsubc8/hesenateHT66/tree/main/html5/index.html</a>
