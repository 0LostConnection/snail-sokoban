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
file(GLOB MAIN_SOURCES "lib/*.h")

add_executable(snail_sokoban ${MAIN_SOURCES}
        src/map.c
        src/base.c)

# Adiciona uma regra personalizada para gerar os arquivos .dat das fases
add_custom_target(generate_maps ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Building map generators..."
)

# Para cada arquivo de fase, adicionamos uma regra para compilar e executá-lo
foreach(MAP_SOURCE ${MAP_SOURCES})
        get_filename_component(MAP_NAME ${MAP_SOURCE} NAME_WE)

        # Adiciona cada executável temporário para compilar e executar
        add_executable(${MAP_NAME}_gen ${MAP_SOURCE}
                lib/base.h
                src/main.c
                src/operation.c)
        add_dependencies(generate_maps ${MAP_NAME}_gen)

        # Adiciona o comando para gerar o arquivo .dat
        add_custom_command(TARGET ${MAP_NAME}_gen POST_BUILD
                COMMAND $<TARGET_FILE:${MAP_NAME}_gen>
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
                COMMENT "Generating map: ${MAP_NAME}.dat"
        )
endforeach()

# Alvo para deletar os executáveis temporários após gerar as fases
add_custom_target(clean_map_executables
        COMMAND ${CMAKE_COMMAND} -E echo "Cleaning map executables..."
)

# Comando para remover os executáveis temporários com compatibilidade para Windows e Linux
if(WIN32)
        # Adiciona os executáveis temporários à limpeza
        foreach(MAP_SOURCE ${MAP_SOURCES})
                get_filename_component(MAP_NAME ${MAP_SOURCE} NAME_WE)
                list(APPEND TEMP_EXECUTABLES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MAP_NAME}_gen.exe")
        endforeach()

        add_custom_command(TARGET clean_map_executables
                COMMAND ${CMAKE_COMMAND} -E echo "Cleaning map executables..."
                COMMAND ${CMAKE_COMMAND} -E rm -f ${TEMP_EXECUTABLES}
                COMMENT "Cleaning map executables..."
        )
else()
        # Adiciona os executáveis temporários à limpeza
        foreach(MAP_SOURCE ${MAP_SOURCES})
                get_filename_component(MAP_NAME ${MAP_SOURCE} NAME_WE)
                list(APPEND TEMP_EXECUTABLES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MAP_NAME}_gen)
        endforeach()

        add_custom_command(TARGET clean_map_executables
                COMMAND ${CMAKE_COMMAND} -E echo "Cleaning map executables..."
                COMMAND ${CMAKE_COMMAND} -E rm -f ${TEMP_EXECUTABLES}
                COMMENT "Cleaning map executables..."
        )
endif()

# Compila o jogo principal após gerar as fases e limpar os executáveis
add_dependencies(snail_sokoban clean_map_executables)
add_dependencies(clean_map_executables generate_maps)
