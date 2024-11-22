@echo off
:: https://stackoverflow.com/questions/21660249/how-do-i-make-one-particular-line-of-a-batch-file-a-different-color-then-the-oth
setlocal enabledelayedexpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do     rem"') do (
  set "DEL=%%a"
)

:: Definindo diretórios
set BUILD_BIN_DIR=%CD%\build\bin
set BUILD_MAPS_DIR=%BUILD_BIN_DIR%\maps

set SRC_DIR=%CD%\src
set SRC_MAPS_DIR=%SRC_DIR%\maps

:: Criação dos diretórios bin e maps, caso não existam
if not exist %BUILD_BIN_DIR% (
    mkdir %BUILD_BIN_DIR%
)
if not exist %BUILD_MAPS_DIR% (
    mkdir %BUILD_MAPS_DIR%
)

:: Compilando os arquivos de fase
call :color 02 "[MAPAS] Compilando os geradores dos mapas..."
echo.
for %%F in (%SRC_MAPS_DIR%\*.c) do (
    set MAP_FILE=%%F
    set MAP_NAME=%%~nF
    call :color 09 "[MAPAS] Compilando !MAP_NAME!_gen..."
    echo.
    gcc -o %BUILD_MAPS_DIR%\!MAP_NAME!_gen !MAP_FILE!
)

:: Gerando os arquivos .dat com os executáveis das fases
echo.
call :color 02 "[MAPAS] Gerando os arquivos binarios dos mapas..."
echo.
for %%F in (%BUILD_MAPS_DIR%\*_gen.exe) do (
    if exist %%F (
        call :color 09 "[MAPAS] Rodando %%~nF para gerar o mapa..."
        echo.
        pushd %BUILD_MAPS_DIR%
        %%~nF
        popd
    )
)

:: Limpando os executáveis temporários
echo.
call :color 02 "[MAPAS] Limpando executaveis dos mapas..."
echo.
del %BUILD_MAPS_DIR%\*_gen.exe

:: Compilando o jogo
echo.
call :color 06 "[JOGO] Compilando snail_sokoban..."
echo.
gcc -o %BUILD_BIN_DIR%\snail_sokoban %SRC_DIR%\*.c my.res -lncurses

echo.
call :color 0F "Build finalizado!"
echo.

pause
exit

:color
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1i