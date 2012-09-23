@echo off
break off
title -----------------------Compilador Java-----------------------
color 02
path c:\Arquivos de Programas\Java\jdk1.6.0_16\bin
set path
cls
javac Main.java
jar cfvm Launcher.jar META-INF\Manifest.mf *.class
echo                        Terminado.
pause
exit
