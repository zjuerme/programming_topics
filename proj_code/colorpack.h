#ifndef _COLORPACK_
#define _COLORPACK_
#include<extgraph.h>

void ImportColorPack(){
//libgraphics原生色	
DefineColor("Black", 0, 0, 0);
DefineColor("Dark Gray", .35, .35, .35);
DefineColor("Gray", .6, .6, .6);
DefineColor("Light Gray", .75, .75, .75);
DefineColor("White", 1, 1, 1);
DefineColor("Brown", .35, .20, .05);
DefineColor("Red", 1, 0, 0);
DefineColor("Yellow", 1, 1, 0);
DefineColor("Blue", 0, 0, 1);
DefineColor("Violet", .93, .5, .93);
DefineColor("Magenta", 1, 0, 1);
DefineColor("Cyan", 0, 1, 1);
	
//Red 	
DefineColor("IndianRed", 205.0/255, 92.0/255, 92.0/255);
DefineColor("LightCoral", 240.0/255, 0.5, 0.5);
DefineColor("Salmon", 250.0/255, 0.5, 114.0/255);
DefineColor("DarkSalmon", 1, 150.0/255, 122.0/255);
DefineColor("LightSalmon", 1, 160.0/255, 122.0/255);
DefineColor("Red", 1, 0, 0);
DefineColor("Crimson", 220.0/255, 20.0/255, 60.0/255);
DefineColor("FireBrick", 178.0/255, 34.0/255, 34.0/255);
DefineColor("DarkRed", 139.0/255, 0, 0);

//Pink
DefineColor("Pink", 1, 192/255, 203/255);
DefineColor("LightPink", 1, 182.0/255, 193.0/255);
DefineColor("HotPink", 1, 105.0/255, 180.0/255);
DefineColor("DeepPink", 1, 20.0/255, 147.0/255);
DefineColor("MediumVioletRed", 199.0/255, 21.0/255, 133.0/255);
DefineColor("PaleVioletRed", 219.0/255, 112.0/255, 147.0/255);

//Orange
DefineColor("Coral", 1, 160.0/255, 122.0/255);
DefineColor("Tomato", 1, 99/255, 71/255);
DefineColor("OrangeRed", 1, 69.0/255, 0);
DefineColor("DarkOrange", 1, 140.0/255, 0);
DefineColor("Orange", 1, 165.0/255, 0);

//Yellow
DefineColor("Gold", 1, 215.0/255, 0);
DefineColor("Yellow", 1,1, 0);
DefineColor("LightYellow", 1, 1, 224.0/255);
DefineColor("LemonChiffon", 1, 250.0/255, 205.0/255);
DefineColor("LightGoldenrodYellow", 250.0/255, 250.0/255, 210.0/255);
DefineColor("PapayaWhip", 1, 239.0/255, 213.0/255);
DefineColor("Moccasin", 1, 228.0/255, 181.0/255);
DefineColor("PeachPuff", 238.0/255, 218.0/255, 185.0/255);
DefineColor("PaleGoldenrod", 238.0/255, 232.0/255, 170.0/255);
DefineColor("Khaki", 240.0/255, 230.0/255, 140.0/255);
DefineColor("DarkKhaki", 189.0/255, 183.0/255, 107.0/255);

//Purple
DefineColor("Lavender", 230.0/255, 230.0/255, 250.0/255);
DefineColor("Thistle", 216.0/255, 191.0/255, 216.0/255);
DefineColor("Plum", 221.0/255, 160.0/255, 221.0/255);
DefineColor("Violet", 238.0/255, 130.0/255, 238.0/255);
DefineColor("Orchid", 218.0/255, 112.0/255, 214.0/255);
DefineColor("Fuchsia", 1, 0, 1);
DefineColor("Magenta", 1, 0, 1);
DefineColor("MediumOrchid", 186.0/255, 85.0/255, 221.0/255);
DefineColor("MediumPurple", 147.0/255, 112.0/255, 219.0/255);
DefineColor("BlueViolet", 138.0/255, 43.0/255, 226.0/255);
DefineColor("DarkViolet", 148.0/255, 0, 211.0/255);
DefineColor("DarkOchid", 153.0/255, 50.0/255, 204.0/255);
DefineColor("DarkMagenta", 139.0/255, 0, 139.0/255);
DefineColor("Purple", 128.0/255, 0, 128.0/255);
DefineColor("Indigo", 75.0/255, 0, 130.0/255);
DefineColor("DarkStateBlue", 72.0/255, 61.0/255, 139.0/255);
DefineColor("StateBlue", 106.0/255, 90.0/255, 205.0/255);
DefineColor("MediumSlateBlue", 123.0/255, 104.0/255, 238.0/255);

//Green
DefineColor("GreenYellow", 173.0/255, 1, 47.0/255);
DefineColor("Chartreuse", 127.0/255, 1, 0);
DefineColor("LawnGreen", 124.0/255, 252.0/255, 0);
DefineColor("Lime", 0, 1, 0);
DefineColor("LimeGreen", 50.0/255, 205.0/255, 50.0/255);
DefineColor("PaleGreen", 152.0/255, 251.0/255, 152.0/255);
DefineColor("LightGreen", 144.0/255, 238.0/255, 144.0/255);
DefineColor("MediumSpringGreen", 0, 250.0/255, 154.0/255);
DefineColor("SpringGreen", 0, 1, 127.0/255);
DefineColor("MediumSeaGreen", 60.0/255, 179.0/255, 113.0/255);
DefineColor("SeaGreen", 46.0/255, 139.0/255, 87.0/255);
DefineColor("ForestGreen", 34.0/255, 139.0/255, 34.0/255);
DefineColor("Green",0, 0.5, 0);
DefineColor("DarkGreen", 0, 100.0/255, 0);
DefineColor("YellowGreen",154.0/255, 205.0/255, 50.0/255);
DefineColor("OliveDrab",107.0/255, 142.0/255, 35.0/255);
DefineColor("Olive", 0.5, 0.5,0);
DefineColor("DarkOliveGreen",85.0/255, 107.0/255, 47.0/255);
DefineColor("MediumAquamarine",102.0/255, 205.0/255, 170.0/255);
DefineColor("DarkSeaGreen",143.0/255, 188.0/255, 143.0/255);
DefineColor("LightSeaGreen",32.0/255, 178.0/255, 170.0/255);
DefineColor("DarkCyan",0, 139.0/255, 139.0/255);
DefineColor("Teal", 0, 0.5, 0.5);

//Blue
DefineColor("Aqua",0, 1, 1);
DefineColor("Cyan",0, 1, 1);
DefineColor("LightCyan",224.0/255, 1, 1);
DefineColor("PaleTurquoise",175.0/255, 238.0/255, 238.0/255);
DefineColor("Aquamarine",127.0/255, 1, 212.0/255);
DefineColor("Turquoise",64.0/255, 224.0/255, 208.0/255);
DefineColor("MediumTurquoise",72.0/255, 209.0/255, 204.0/255);
DefineColor("DarkTurquoise",0, 206.0/255, 209.0/255);
DefineColor("CadetBlue",95.0/255, 158.0/255, 160.0/255);
DefineColor("SteelBlue",70.0/255, 130.0/255, 180.0/255);
DefineColor("LightSteelBlue",176.0/255, 196.0/255, 222.0/255);
DefineColor("PowderBlue",176.0/255, 224.0/255, 230.0/255);
DefineColor("LightBlue",173.0/255, 216.0/255, 230.0/255);
DefineColor("SkyBlue",135.0/255, 206.0/255, 235.0/255);
DefineColor("LightSkyBlue",135.0/255, 206.0/255, 250.0/255);
DefineColor("DeepSkyBlue",0, 191.0/255, 1);
DefineColor("DodgerBlue", 30.0/255, 144.0/255,1);
DefineColor("CornflowerBlue",100.0/255, 149.0/255, 237.0/255);
DefineColor("RoyalBlue",65.0/255, 105.0/255, 225.0/255);
DefineColor("Blue",0, 0, 1);
DefineColor("MediumBlue",0, 0, 205.0/255);
DefineColor("DarkBlue",0, 0, 139.0/255);
DefineColor("MidnightBlue",25.0/255, 25.0/255, 112.0/255);
DefineColor("Navy", 0, 0, 0.5);

//Brown
DefineColor("Cornsilk",1, 248.0/255, 220.0/255);
DefineColor("BlanchedAlmond",1, 235.0/255, 205.0/255);
DefineColor("Bisque",1, 228.0/255, 196.0/255);
DefineColor("NavajoWhite",1, 222.0/255, 173.0/255);
DefineColor("Wheat", 245.0/255, 222.0/255,179.0/255);
DefineColor("BurlyWood",222.0/255, 184.0/255, 135.0/255);
DefineColor("Tan",210.0/255, 180.0/255, 140.0/255);
DefineColor("RosyBrown",188.0/255, 143.0/255, 143.0/255);
DefineColor("Goldenrod",218.0/255, 165.0/255, 32.0/255);
DefineColor("SandyBrown", 244.0/255, 164.0/255, 96.0/255);
DefineColor("DarkGoldenrod",184.0/255, 134.0/255, 11.0/255);
DefineColor("Peru",205.0/255, 133.0/255, 63.0/255);
DefineColor("Chocolate",210.0/255, 105.0/255, 30.0/255);
DefineColor("SaddleBrown",139.0/255,69.0/255, 19.0/255);
DefineColor("Sienna",160.0/255, 82.0/255, 45.0/255);
DefineColor("Brown",165.0/255, 42.0/255, 42.0/255);
DefineColor("Maroon", 0.5, 0, 0);

//White
DefineColor("White",1, 1, 1);
DefineColor("Snow",1, 250.0/255, 250.0/255);
DefineColor("Honeydew", 240.0/255, 1,240.0/255);
DefineColor("MintCream",245.0/255, 1, 250.0/255);
DefineColor("Azure",240.0/255, 1, 1);
DefineColor("AliceBlue", 240.0/255, 248.0/255, 1);
DefineColor("GhostWhite",248.0/255, 248.0/255, 1);
DefineColor("WhiteSmoke",245.0/255, 245.0/255, 245.0/255);
DefineColor("Seashell", 1, 245.0/255, 238.0/255);
DefineColor("Beige",245.0/255, 245.0/255, 220.0/255);
DefineColor("OldLace",253.0/255, 245.0/255, 230.0/255);
DefineColor("FloralWhite",1, 250.0/255, 240.0/255);
DefineColor("Ivory", 1, 1, 240.0/255);
DefineColor("AntiqueWhite",250.0/255, 235.0/255, 215.0/255);
DefineColor("Linen",250.0/255, 235.0/255, 215.0/255);
DefineColor("LavenderBlush",1, 240.0/255, 245.0/255);
DefineColor("MistyRose", 1, 228.0/255, 225.0/255);

//Gray
DefineColor("Gainsboro",220.0/255, 220.0/255, 220.0/255);
DefineColor("LightGrey",211.0/255, 211.0/255, 211.0/255);
DefineColor("Sliver",192.0/255, 192.0/255, 192.0/255);
DefineColor("DarkGray",169.0/255, 169.0/255, 169.0/255);
DefineColor("Gray",0.5, 0.5, 0.5);
DefineColor("DimGray",105.0/255, 105.0/255, 105.0/255);
DefineColor("SlateGray",112.0/255,0.5, 144.0/255);
DefineColor("LightStateGray", 119.0/255, 136.0/255,153.0/255);
DefineColor("DarkSlateGray", 47.0/255, 79.0/255, 79.0/255);
DefineColor("Black",0, 0, 0);
}
//经典原色 
void Color_Oringal(){
	setTextBoxColors ("LightGrey","DarkGray","White","DarkSlateGray", 1);
	setButtonColors ("Gainsboro", "DimGray" , "Gray", "Black", 1);
	setMenuColors ("Gray","Light Gray","Black","Cyan", 1);
	SetPenColor("Black");
}
//清新水粉 
void Color_QingXing(){
	setTextBoxColors ("Ivory","Gold" ,"Moccasin" , "DarkKhaki", 1);
	setButtonColors ("Azure", "LightSteelBlue","LightSkyBlue", "Navy", 1);
	setMenuColors ("Honeydew","Lime", "SpringGreen", "Teal", 1);
	SetPenColor("MediumTurquoise");
}
//阳光明媚 
void Color_MingMei(){
	setTextBoxColors ("LightYellow","OrangeRed" ,"Moccasin" , "DarkKhaki", 1);
	setButtonColors ("LightPink", "HotPink","PowderBlue", "Navy", 1);
	setMenuColors ( "LightCoral","DarkRed","PaleVioletRed","IndianRed", 1);
	SetPenColor("Maroon");
}
//缤纷果盘 
void Color_BinFeng(){
	setTextBoxColors ("LavenderBlush","OrangeRed" ,"MistyRose" , "Cyan", 1);
	setButtonColors ("Plum", "White","MediumSlateBlue", "Navy", 1);
	setMenuColors ("LightSeaGreen","AliceBlue", "Olive","OliveDrab" , 1);
	SetPenColor("OrangeRed");
}
//摩登时代
void Color_Moden(){
	setTextBoxColors ("SlateGray","Khaki" , "DarkSlateGray","DarkKhaki" , 1);
	setButtonColors ("Sliver", "White","DimGray", "Beige", 1);
	setMenuColors ("LightSteelBlue","AliceBlue", "SteelBlue","LightCyan" , 1);
	SetPenColor("RosyBrown");
} 
#endif

