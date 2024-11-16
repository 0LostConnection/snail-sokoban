# snail-sokoban
 Implementação de um jogo do gênero Sokoban em C.

Adicionar que no inicio, toda vez que desenhava o novo estado da tela, o código limpava toda a tela, isso dava "flickering". Agora o jogo só desenha o novo estado da tela, sobrepondo o estado anterior. https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
show_cursor https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt#:~:text=You%20can%20hide%20the%20cursor%20by%20calling%20SetConsoleCursorInfo.,showFlag%3B%20%2F%2F%20set%20the%20cursor%20visibility%20SetConsoleCursorInfo%28out%2C%20%26cursorInfo%29%3B