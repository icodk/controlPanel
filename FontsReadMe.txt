How to add  new fonts 
(2021-10-20 15:23:53)
---------------------------------------------------
Example with 7 segments fonts from https://www.keshikan.net/fonts-e.html
Download the latest relaes fonts-DSEG_v046.zip and unzip it to get to the ttf files

1. Go to https://lvgl.io/tools/fontconverter15:23 
2. Enter name of fonts (ex.: DSEG7_classic_bold_25)
3. Enter size (Height in px) (25)
4. Select Bpp (4)
5. Select a ttf file (DSEG7Classic-bold.ttf)
6. Enter range (for digits, '.' and '-', enter: 0x30-0x39,0x2d,0x2e)
7. Click on Convert
8. Add the file to the project  at lvll\src\font
9. In the application  where the font is used add:  
    LV_FONT_DECLARE(DSEG7_classic_bold_25);
    at the top of the C file (just after the includes )
10. Use the fonts by calling: 
    lv_style_set_text_font(&style_data, &DSEG7_classic_bold_25);    
    