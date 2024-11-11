cmake_minimum_required(VERSION 3.29)
project(snail_sokoban C)

set(CMAKE_C_STANDARD 11)

# Define o diretório de saída para os executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define o diretório de saída para os arquivos .dat
set(DAT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Localize os arquivos de fases na pasta maps
file(GLOB MAP_SOURCES "src/maps/*.c")
file(GLOB MAIN_SOURCES "src/*.c")

# Configura o jogo principal
add_executable(snail_sokoban.out ${MAIN_SOURCES})

# Adiciona uma regra personalizada para gerar os arquivos .dat das fases
add_custom_target(generate_maps ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Building map generators..."
)

# Para cada arquivo de fase, adicionamos uma regra para compilar e executá-lo
foreach(MAP_SOURCE ${MAP_SOURCES})
    get_filename_component(MAP_NAME ${MAP_SOURCE} NAME_WE)

    # Adiciona cada executável temporário para compilar e executar
    add_executable(${MAP_NAME}_gen ${MAP_SOURCE})
    add_dependencies(generate_maps ${MAP_NAME}_gen)

    # Adiciona o comando para gerar o arquivo .dat
    add_custom_command(TARGET ${MAP_NAME}_gen POST_BUILD
            COMMAND $<TARGET_FILE:${MAP_NAME}_gen> > ${DAT_OUTPUT_DIRECTORY}/${MAP_NAME}.dat
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            COMMENT "Generating map: ${MAP_NAME}.dat"
    )
endforeach()

# Alvo para deletar os executáveis temporários após gerar as fases
add_custom_target(clean_map_executables
        COMMAND ${CMAKE_COMMAND} -E echo "Cleaning map executables..."
)

# Adiciona os executáveis temporários à limpeza
foreach(MAP_SOURCE ${MAP_SOURCES})
    get_filename_component(MAP_NAME ${MAP_SOURCE} NAME_WE)
    list(APPEND TEMP_EXECUTABLES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MAP_NAME}_gen)
endforeach()

# Comando para remover os executáveis temporários
add_custom_command(TARGET clean_map_executables
        COMMAND ${CMAKE_COMMAND} -E rm -f ${TEMP_EXECUTABLES}
        COMMENT "Cleaning map executables..."
)

# Compila o jogo principal após gerar as fases e limpar os executáveis
add_dependencies(snail_sokoban.out clean_map_executables)
add_dependencies(clean_map_executables generate_maps)