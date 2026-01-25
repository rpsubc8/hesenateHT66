# Modify Talkie HESENATE HT66 options

<h1>Disclaimer</h1>
In accordance with the telecommunications regulations of each country, the PMR446 standard limits transmission power to a maximum of 500 mW.
The responsibility for making this modification therefore lies with the user.<br>
The LPD 433 standard only allows a maximum power of 10 mW, so the 500 or 700 mW of power is a problem.<br>
On commercial FM (87.5 MHz to 108.0 MHz), everything is prohibited.<br>
On CB 27 MHz, 4W is permitted for FM mode. Only the 40 channels of band D (26.965 MHz - 27.405 MHz) are registered. Bands A, B, C and E, depending on the country, will have regulations. In Spain, although it is not registered, it is considered free due to its age. Band F, from channel 12 (28.005 MHz) to 40 (28.305 MHz), requires amateur radio authorisation.<br>
PRS (409.750 MHz - 409.9875 MHz) is authorised for mainland China, Hong Kong and Macao.<br>
FRS 22 channels (462 MHz - 467 MHz), authorised for use in the United States and Mexico.<br>
Freenet 6 channels (149.0250 MHz - 149.1125 MHz), authorised for Germany.<br>
Hunter frequencies require authorisation.<br>
Marine frequencies (156 MHz - 174 MHz) require authorisation, as well as boat ownership, and direct A(terrestrial) B(terrestrial) communication is prohibited. At least one of the two points (A or B) must be a marine vessel.<br>
The remaining frequencies have their own regulations, both in amateur radio bands and for private use, which must be consulted individually.<br>
Ignorance of the law does not exempt one from compliance.
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
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf'>https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66SpanishOCR.pdf</a><br>
<br>
There is also a multilingual manual distributed by PTTalky for both the HT66 and Plus models:<br>
<br>
<a href='https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66HT66PLUSManual.pdf'>https://github.com/rpsubc8/hesenateHT66/tree/main/Manual/HT66HT66PLUSManual.pdf</a>

<br><br>


<h1>Frequencies</h1>
In the Portable programme, we already have the modified Setting.ini file, but if not, we will have to create an entry that extends the range from 1 to 590 MHz, instead of 446 MHz:<br>
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

If we do not have this Fqvalue1 entry, as well as the selected combo, the PMR filter will be applied, which, together with the programme's limitations, will ultimately result in a cut-off of frequencies to the default ones. In other words, it will assign the American PMR band (425 MHz), which has nothing to do with the European band (446 MHz). The same will happen if we start to change the frequency combo.<br>

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
| CB(01-16)      | Generates channels 1 to 16 of CB   |
| CB(17-32)      | Generates channels 17 to 32 of CB  |
| CB(25-40)      | Generates channels 25 to 40 of CB  |
| FM(commercial) | A pair of FM chains                |
| PRS 409(01-16) | Channels 1 to 16 PRS 409 Mhz       |
| PRS 409(05-20) | Channels 1 to 16 PRS 409 Mhz       |
| FRS22(01-16)   | Channels 1 to 16 FRS22 462 Mhz     |
| FRS22(07-22)   | Channels 7 to 22 FRS22 462 Mhz     |
| Freenet 159    | Channels 1 to 6 Freenet 159 Mhz    |
| Asturias       | Hunter Asturias 150 Mhz            |
| Cantabria      | Hunter Cantabria 150 Mhz           |
| Castilla Leon  | Hunter Castilla Leon 151 Mhz       |
| Marine(01-16)  | Marine channels 1 to 16 Spain      |
| Marine(17-63)  | Marine channels 1 to 16 Spain      |
| Marine(64-81)  | Marine channels 1 to 16 Spain      |
| Marine(71-88)  | Marine channels 1 to 16 Spain      |
| Marine(01-16)  | Marine channels 1 to 16 EEUU       |
| Marine(17-63)  | Marine channels 1 to 16 EEUU       |
| Marine(64-81)  | Marine channels 1 to 16 EEUU       |
| Marine(71-88)  | Marine channels 1 to 16 EEUU       |
| Clear          | Delete everything                  |
| Save           | Save the file physically           |
| Browse         | Select file (does not read it)     |
| Load           | read the selected file             |
| Start          | Generate the file                  |


<br>
In the case of FM (commercial), care must be taken with the PTT during transmission, as it is not blocked by hardware and will transmit on FM at LOW power (500 or 700 mW), which is illegal, and is therefore only for experimental purposes. It is generated in WIDE mode.<br>

In the HT66 portable programme, I have modified the Setting.ini for a range of 1 MHz to 590 MHz, and we must always ensure that this combo is selected.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/preview87to470.gif'></center>
Once again, we must double-check that we have the 1-590 MHz combo selected. The steps to follow are to select that combo box, click NEW, and check that it is empty:<br>
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

Once everything has been checked and is correct, we can send the data to the radio station.<br>

The HESENATE HT66 supports commercial FM, both reception and transmission, 136 MHz, 140 MHz and 400 MHz. Another thing is how it performs.<br>
It supports 11 metres (27 MHz) CB in FM mode, but with antenna limitations. With an Alan Midland 42 walkie-talkie at a distance of 1 metre, the signal for LOW mode is 3 out of 9, while for HIGH it is 5 out of 9. It is therefore suitable for simple tests.<br>
With the HTML5 utility, you can test the entire range of frequencies you want, simply by entering them manually and clicking start to generate the custom.dat file. This way, you can see the limits of the walkie-talkie.<br>

We must ensure that the .DAT file is exactly 974 bytes in size.
<br><br>



<h1>Other Talkys</h1>
There are several talkies distributed by the company PTTalky that share features with the HT66:
<pre>
 HT66 Plus
 FR1 and FR1 Plus
 FR2 and FR2 Plus
 PR2 and PR2 Plus
</pre>
The CPS software is available:<br><br>
<a href='https://pttalky.com/pages/software'>https://pttalky.com/pages/software</a><br>
<br>
As they are similar, we could apply similar solutions, but there are certain problems.<br>
From what I have been able to ascertain, given that I only have the HT66, the FR1 software is the only one that can communicate with the PMR HT66 and read the data correctly. Unfortunately, when saving the file and sending it to the radio, it relies on the frequency combobox index, which in this case is the FRS22 standard, i.e. 469 MHz, so it never lets you save the frequency correctly. This software was interesting because it has the Power TX combo unlocked, given that the FRS standard allows a couple of channels in HIGH mode.
<br>
The PR2 is designed for PMR 446, and from what I have been able to ascertain, the file system does allow you to change frequencies, so it is possible that something similar will work.<br>
The rest have extra parameters in different positions in the file, which I suppose would need to be adapted.
<br><br>
<br>

<h1>HT66 Plus</h1>
The programme reads it, but I don't have the actual radio to test it.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewht66high.jpg'></center>
I have left the .dat files for the LOW, HIGH, NARROW, and WIDE settings:
<ul>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusLowNarrow.dat'>ht66plusLowNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusHighNarrow.dat'>ht66plusHighNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusLowWide.dat'>ht66plusLowWide.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/ht66plus/ht66plusHighWide.dat'>ht66plusHighWide.dat</li>
</ul>
<br><br>
<br>


<h1>PTTalky PR2</h1>
The programme reads it, but I don't have the actual radio to test it.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewpr2high.jpg'></center>
I have left the .dat files for the LOW, HIGH, NARROW, and WIDE settings:
<ul>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2lowNarrow.dat'>pr2lowNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2highNarrow.dat'>pr2highNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2lowWide.dat'>pr2lowWide.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2/pr2highWide.dat'>pr2highWide.dat</li>
</ul>
<br><br>


<h1>PTTalky PR2 Plus</h1>
The programme reads it, but I don't have the actual radio to test it.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewpr2plushigh.jpg'></center>
I have left the .dat files for the LOW, HIGH, NARROW, and WIDE settings:
<ul>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusLowNarrow.dat'>pr2plusLowNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusHighNarrow.dat'>pr2plusHighNarrow.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusLowWide.dat'>pr2plusLowWide.dat</li>
 <li><a href='http://rpsubc8.github.io/hesenateHT66/others/PTTalkyPR2Plus/pr2plusHighWide.dat'>pr2plusHighWide.dat</li>
</ul>


<br><br>
<h1>Custom CPS</h1>
I have created a simplified CPS to be able to perform the dump, as well as to be able to send the custom.dat files to the radio via USB serial port, without having to use the official HESENATE.<br>
It has no checks, and for now it is just for home use, but it allows you to send frequencies correctly and dump the current content of the radio.<br><br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewcpswinht66.gif'></center>
<a href='http://rpsubc8.github.io/hesenateHT66/cpsHT66/winht66/winht66.exe'>winht66.exe</a><br>
<br>
We can send all the channel and option information to the radio, or just one part of it, using the -wch or -wopt option. The options are VOX, squelch, battery saving, etc.<br>
If we wanted to read the contents of the radio on COM5:<br>
<pre>
 winht66 -p5 -d
</pre>
By default, when invoking the -d command, the data will be saved in the dataload.dat file.<br><br>
If we wanted to send the entire contents of a file (custom.dat), including all 16 channels and the options, to the radio on COM5 port:<br>
<pre>
 winht66 -p5 -scustom.dat
</pre>
<br>
I have also added a version for MSDOS with DOSBOX using the COM1 port.
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewcpsdosht66.gif'></center>
<a href='http://rpsubc8.github.io/hesenateHT66/cpsHT66/dosht66/DOSHT66.EXE'>DOSHT66.EXE</a><br>
<br>
The read option (-d) does not function very well, but sending data to the radio does, so it can be useful.<br>
In the DOSBOX configuration file, you must enable the directserial options and specify the actual physical port, which if it were COM14, would be:
<pre>
 serial1=directserial realport:COM14
</pre>
The tests I have carried out with VirtualBOX when reading from the serial port are much better, allowing DUMP from both Windows 98 and MSDOS mode.
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/virtualboxWin98.gif'></center>
We just need to redirect our actual physical port COM5 to COM1 on the emulator.
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/virtualboxConfig.gif'></center>
<br>
I have also added an HTML5 version with webserial in Google Chrome, Microsoft Edge, and Opera, accessible via the <b>back uart web</b> button.<br><br>
<a href='http://rpsubc8.github.io/hesenateHT66/uartht66.html'>UART HT66</a><br><br>
We just need to select the COM1 port from the browser:
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewUartSelectWebSerial.gif'></center>
Radio dumping is permitted, as well as sending channels and options:
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewUartDumpWebSerial.gif'></center>
It is advisable to reload the main page each time a read operation or radio transmission is performed to ensure that the UART port is not blocked or contains unusual data.<br>
At any time, we can return to the HTML5 frequencies from the <b>back frequencies web</b> button.
