@echo off
break off
path C:\Dev-Cpp\bin
set path
cls
g++ --version 
g++ -Wl -o Project  *.o
pause
exit