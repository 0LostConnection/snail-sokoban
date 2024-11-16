@echo off
setlocal enabledelayedexpansion

:: Definindo diretórios
set BIN_DIR=%CD%\build\bin

:: Verificando se o jogo foi compilado
if not exist %BIN_DIR%\snail_sokoban.exe (
    echo "Jogo não encontrado. Certifique-se de que o build foi feito corretamente."
    exit /b
)

:: Iniciando o jogo
echo Iniciando o jogo...
pushd %BIN_DIR%
snail_sokoban.exe
popd

echo Jogo encerrado.
endlocal
