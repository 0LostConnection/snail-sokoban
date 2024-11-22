@echo off
setlocal enabledelayedexpansion

:: Definindo diretórios
set BIN_DIR=%CD%\build\bin
set SRC_DIR=%CD%\src
set MAP_DIR=%SRC_DIR%\maps

:: Solicitar o número da fase ao usuário
set /p PHASE="Enter the phase number to compile and execute (1-10): "

:: Verificar se o número da fase é válido
if %PHASE% lss 1 (
    echo Invalid phase number. Must be between 1 and 10.
    goto :end
)

if %PHASE% gtr 10 (
    echo Invalid phase number. Must be between 1 and 10.
    goto :end
)

:: Mapear o nome do arquivo da fase
set /a PHASE_INDEX=%PHASE%-1
set MAP_FILE=%MAP_DIR%\fase%PHASE_INDEX%.c
set MAP_NAME=fase%PHASE_INDEX%

if not exist !MAP_FILE! (
    echo Phase file !MAP_FILE! does not exist.
    goto :end
)

:: Criação do diretório bin, caso não exista
if not exist %BIN_DIR% (
    mkdir %BIN_DIR%
)

:: Compilar o arquivo da fase selecionada
echo Compiling !MAP_NAME!_gen...
gcc -o %BIN_DIR%\!MAP_NAME!_gen !MAP_FILE! -lncurses

:: Executar o gerador da fase
if exist %BIN_DIR%\!MAP_NAME!_gen.exe (
    echo Running !MAP_NAME!_gen to generate the map...
    pushd %BIN_DIR%
    !MAP_NAME!_gen
    popd
) else (
    echo Failed to compile or find !MAP_NAME!_gen.
    goto :end
)

:: Limpar o executável temporário da fase
echo Cleaning map executable...
del %BIN_DIR%\!MAP_NAME!_gen.exe

echo Build for phase %PHASE% complete.

:end
:: pause
endlocal
