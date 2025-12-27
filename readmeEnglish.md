# Modify Talkie HESENATE HT66 options

<h1>Disclaimer</h1>
In accordance with the telecommunications regulations of each country, the PMR446 standard limits transmission power to a maximum of 500 mW.
The responsibility for making this modification therefore lies with the user.<br>
The LPD 433 standard only allows a maximum power of 10 mW, so the 500 or 700 mW of power is a problem. 
<br><br>

<h1>Preparation</h1>
The HESENATE HT66 walkie-talkie is designed to comply with the PMR446 standard, so it comes with software that blocks the modification of the transmission power (low) to 500 mw.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewabout.gif'></center>
This software can be downloaded from: <a href='https://cps22.s3.amazonaws.com/HT66.exe'>https://cps22.s3.amazonaws.com/HT66.exe</a><br>
<br>
Or from: <a href='https://github.com/rpsubc8/hesenateHT66/tree/main/originalHT66'>https://github.com/rpsubc8/hesenateHT66/tree/main/originalHT66</a><br>
<br>
I have provided a portable version (portableHT66.zip) that does not require installation, with the power set to high by default:<br><br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66'>https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66</a>
<br><br>
Once the programme has been launched, it should show us the TX power in High on each channel:<br><br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewhighnarrow.gif'></center>
This way, once we send the data to the walkie-talkie, it will already be modified.<br>
The rest of the parameters can be modified, as usual.<br>
It should be remembered that the combination of RX Freq (MHz) and TX Freq (MHz) should not be modified, i.e. it should be left blank, as it is, since it corresponds to the default PMR frequencies. If it is modified, it will be outside the regulations.<br>
<br><br>


<h1>Explanation</h1>
If you do not wish to use the portable version, simply select the file (highnarrow.dat) from the menu (File-->Open):<br><br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66'>https://github.com/rpsubc8/hesenateHT66/tree/main/portableHT66</a>
<br><br>
The file is in ASCII format with hexadecimal content, with one entry per channel (01-16) per line (High Narrow):<br>
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

What we are interested in is the last byte of each line, which should be:
<pre>
 FF   --> High  Narrow 
</pre>
Or:
<pre>
 FB   --> High  Wide
 F3   --> Low  Wide
 F7   --> Low Narrow
</pre>

W/N refers to bandwidth expansion, which for PMR must be Narrow. Wide mode would be used when experimenting with digital modes in analogue mode, to avoid pre-emphasis and de-emphasis of the microphone and speaker input and output filters.


<br>
<h1>Help manual</h1>
I have left a manual in Spanish converted to OCR and PDF:<br><br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf'>https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf</a>
<br><br>


<h1>Frequencies</h1>
I have created an HTML5 utility to modify all locked parameters, including frequencies.<br><br>
<a href='https://rpsubc8.github.io/hesenateHT66/'>https://rpsubc8.github.io/hesenateHT66/</a><br><br>
There is a button to generate the .DAT file for the default frequencies for PMR 446 and LPD. Since there are 16 channels and 69 LPD channels, I have left several groups.<br>
The options are:<br><br>

| Button         | Action                             |
| -------------- | ---------------------------------- |
| PMR 446        | Generates the 16 PMR channels      |
| LPD(01-16)     | Generates channels 1 to 16 of LPD  |
| LPD(17-32)     | Generates channels 17 to 32 of LPD |
| LPD(33-48)     | Generates channels 33 to 48 of LPD |
| LPD(54-69)     | Generates channels 54 to 69 of LPD |
| FM(commercial) | A pair of FM chains                |
| Clear          | Delete everything                  |
| Save           | Save the file physically           |
| Browse         | Select file (does not read it)     |
| Load           | read the selected file             |
| Start          | Generate the file                  |


<br>
In the case of FM (commercial), care must be taken with the PTT during transmission, as it is not blocked by hardware and will transmit on FM at LOW power (500 or 700 mW), which is illegal, and is therefore only for experimental purposes. It is generated in WIDE mode.<br>

In the HT66 portable programme, I have modified the Setting.ini for a range of 87 MHz to 470 MHz, and we must always ensure that this combo is selected.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/preview87to470.gif'></center>
The steps to follow are to select that combo box, click NEW, and check that it is empty:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewclear87to470.gif'></center>
Next, we must load the data we have generated with the HTML utility from the menu.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewOpen.gif'></center>
Then we can generate the file from html5 by pressing the LPD button (01-16) to generate the first 16 LPD channels:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewhtml5lpd.gif'></center>
If we open the customLPD.dat file generated with the HTML utility with the LPD frequencies, we will see something similar to this:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewLPD.gif'></center>
The frequencies, which in this case for LPD are 433 MHz, will never be reflected in the programme, only the power and bandwidth, as this is a limitation of the programme. We must check that the frequencies are actually going to be recorded, i.e. that they have been read correctly. To do this, we must use the portable programme (not the html) from the menu, send it to be saved, for example with the name customLPDchk.dat, and check that both customLPD.dat and customLPDchk.dat are the same with a text editor, such as Notepad++.<br>
We must check that customLPDchk.dat file from the html5 utility using the browse button, and then clicking the Load button. If at any point we see that the frequencies are not correct, i.e. we expect 433 MHz and we get 153 MHz, as shown here:<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewhtml5lpderror.gif'></center>
Well, we will have to follow the same steps again in the portable programme, that is, reopen the customLPD.dat file and save it again as customLPDchk.dat, to check again that they are the same and that the correct frequencies are coming out of the html5. It usually works the first time, but sometimes you have to do these steps twice.<br>
This is important because in the programme we are blind to the issue of frequencies, as they are not displayed, and we rely on the HTML version to check. If it is not correct, we will appear with frequencies and powers that are not approved. It is ideal to have another good walkie-talkie, which also allows you to check that everything is correct.<br><br>

The HESENATE HT66 supports commercial FM, both reception and transmission, 136 MHz, 140 MHz and 400 MHz. Another thing is how it performs.
<br><br>
