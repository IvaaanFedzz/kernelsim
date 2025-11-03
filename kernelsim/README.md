# KernelSim

KernelSim es un simulador educativo de un núcleo (kernel) escrito en C. 
Simula planificación de procesos, memoria virtual, sistema de archivos en memoria y dispositivos ficticios.
No ejecuta binarios reales ni accede al hardware.

## Contenido
- core/: tipos básicos y utilidades
- scheduler/: planificación Round-Robin
- memory/: memoria virtual por páginas
- fs/: sistema de archivos en memoria
- device/: drivers ficticios
- shell/: CLI interna
- main.c

## Cómo compilar (Linux)
```bash
make
./kernelsim
```

## Cómo compilar en Windows (MinGW)
Instala MinGW (gcc). Desde MSYS2/MinGW shell:
```bash
gcc -std=c11 -Wall -Wextra -g -o kernelsim.exe main.c core/core.c scheduler/scheduler.c memory/memory.c fs/fs.c device/device.c shell/shell.c
```

## Para crear un instalador .exe
1. Compilar `kernelsim.exe` con MinGW.
2. Usar NSIS para crear un instalador: escribir un script `.nsi` que copie el .exe.
(Se incluye un ejemplo de script nsi en `extras/`)

## Subir a GitHub
Se incluye un script `git_push.sh` que te ayudará a inicializar y subir el repo localmente. **No** puedo subir a tu GitHub; corre el script en tu máquina y sigue las instrucciones.

## Notas de seguridad
KernelSim no ejecuta procesos reales y no toca archivos del sistema fuera del directorio de trabajo.
