@echo off
break off
title Launcher
echo ------------------------JAR-----------------------
color 70
path c:\Arquivos de Programas\Java\jdk1.6.0_16\bin
set path
jar
jar cfvm Forca.jar META-INF\Manifest.mf *.class
pause
exit