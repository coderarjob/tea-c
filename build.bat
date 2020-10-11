call "E:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

mkdir bin\win
cl /TC /Febin\win\ /Fobin\win\ main.c tea.c
pause