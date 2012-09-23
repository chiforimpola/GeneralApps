@echo off
break off
title -----------------------Compilador Java-----------------------
color 70
path c:\Arquivos de Programas\Java\jdk1.6.0_23\bin
set path
cls
javac *.java
jar cfvm Launcher.jar Manifest.mf *.class resource
echo                        Terminado.
pause
exit
