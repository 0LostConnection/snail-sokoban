@echo off
setlocal enabledelayedexpansion

:: Definindo diretórios
set BIN_DIR=%CD%\build\bin
set SRC_DIR=%CD%\src
set MAP_DIR=%SRC_DIR%\maps

:: Criação do diretório bin, caso não exista
if not exist %BIN_DIR% (
    mkdir %BIN_DIR%
)

:: Compilando os arquivos de fase
echo Compiling map generators...
for %%F in (%MAP_DIR%\*.c) do (
    set MAP_FILE=%%F
    set MAP_NAME=%%~nF
    echo Compiling !MAP_NAME!_gen...
    gcc -o %BIN_DIR%\!MAP_NAME!_gen !MAP_FILE! -lncurses
)

:: Gerando os arquivos .dat com os executáveis das fases
echo Generating map files...
for %%F in (%BIN_DIR%\* _gen) do (
    if exist %%F (
        echo Running %%F to generate the map...
        pushd %BIN_DIR%
        %%F
        popd
    )
)

:: Compilando o jogo
echo Compiling snail_sokoban...
gcc -o %BIN_DIR%\snail_sokoban %SRC_DIR%\*.c -lncurses

:: Limpando os executáveis temporários
echo Cleaning map executables...
del %BIN_DIR%\*_gen.exe

echo Build complete.
endlocal
