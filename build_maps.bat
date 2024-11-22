@echo off
setlocal enabledelayedexpansion
:: https://stackoverflow.com/questions/21660249/how-do-i-make-one-particular-line-of-a-batch-file-a-different-color-then-the-oth
setlocal enabledelayedexpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do     rem"') do (
  set "DEL=%%a"
)
color 0F

:: Definindo diretórios
set BUILD_BIN_DIR=%CD%\build\bin
set BUILD_MAPS_DIR=%BUILD_BIN_DIR%\maps

set SRC_DIR=%CD%\src
set SRC_MAPS_DIR=%SRC_DIR%\maps

:: Solicitar o número da fase ao usuário
set /p PHASE="Digite o numero da fase (1-10): "

:: Verificar se o número da fase é válido
if %PHASE% lss 1 (
    call :color 0C "Numero invalido, precisa ser entre 1 e 10!"
    echo.
    goto :end
)

if %PHASE% gtr 10 (
    call :color 0C "Numero invalido, precisa ser entre 1 e 10!"
    echo.
    goto :end
)

echo.
:: Mapear o nome do arquivo da fase
set /a PHASE_INDEX=%PHASE%-1
set MAP_FILE=%SRC_MAPS_DIR%\fase%PHASE_INDEX%.c
set MAP_NAME=fase%PHASE_INDEX%

if not exist !MAP_FILE! (
    call :color 0C "O arquivo de mapa !MAP_FILE! não existe!"
    echo.
    goto :end
)

:: Criação dos diretórios bin e maps, caso não existam
if not exist %BUILD_BIN_DIR% (
    mkdir %BUILD_BIN_DIR%
)
if not exist %BUILD_MAPS_DIR% (
    mkdir %BUILD_MAPS_DIR%
)

:: Compilar o arquivo da fase selecionada

call :color 02 "Compilando !MAP_NAME!_gen..."
echo.
gcc -o %BUILD_MAPS_DIR%\!MAP_NAME!_gen !MAP_FILE! -lncurses

:: Executar o gerador da fase
if exist %BUILD_MAPS_DIR%\!MAP_NAME!_gen.exe (
    call :color 09 "Rodando !MAP_NAME!_gen para gerar o mapa..."
    echo.
    pushd %BUILD_MAPS_DIR%
    !MAP_NAME!_gen
    popd
) else (
    call :color 0C "Falha ao compilar ou encontrar !MAP_NAME!_gen"
    echo.
    goto :end
)

:: Limpar o executável temporário da fase
call :color 02 "Limpando executavel do mapa..."
echo.
del %BUILD_MAPS_DIR%\!MAP_NAME!_gen.exe

echo.
call :color 06 "Mapa para a fase %PHASE% gerado"
echo.

:end
pause
exit

:color
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1i