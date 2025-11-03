1-Requisitos
---

Un sistema operativo como Windows , MacOS , Linux..
Instalar msys2.org 
<img width="1717" height="975" alt="image" src="https://github.com/user-attachments/assets/3778a482-7605-4752-8462-492bd84765f0" />


2-Una vez instalado, abre el menú Inicio y ejecuta:--
MSYS2 MinGW 64-bit
----
Instalar las herramientas de compilación:

pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make

OJO! VERIFICA QUE FUNCIONAN:
gcc --version
mingw32-make --version

3-COMPILAR
--
cd /c/Users/<tu_usuario>/Desktop/kernelsim
mingw32-make
kernelsim.exe

Deberías ver:
--
<img width="498" height="277" alt="image" src="https://github.com/user-attachments/assets/d9b2078e-ab90-4d42-a03d-71e49f1242b2" />
