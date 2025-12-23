# Modify Talkie HESENATE HT66 options

<h1>Disclaimer</h1>
In accordance with the telecommunications regulations of each country, the PMR446 standard limits transmission power to a maximum of 500 mW.
The responsibility for making this modification therefore lies with the user.
<br><br>

<h1>Preparation</h1>
The HESENATE HT66 walkie-talkie is designed to comply with the PMR446 standard, so it comes with software that blocks the modification of the transmission power (low) to 500 mw.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/hesenateHT66/main/preview/previewabout.gif'></center>
This software can be downloaded from: <a href='https://cps22.s3.amazonaws.com/HT66.exe'>https://cps22.s3.amazonaws.com/HT66.exe</a><br>
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
</pre>

W/N refers to bandwidth expansion, which for PMR must be Narrow. Wide mode would be used when experimenting with digital modes in analogue mode, to avoid pre-emphasis and de-emphasis of the microphone and speaker input and output filters.
