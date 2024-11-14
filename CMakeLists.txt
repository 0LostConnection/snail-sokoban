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

add_compile_options(-Wall)

# Configuração manual para ncurses em Windows
if(WIN32)
        # Defina manualmente os diretórios de include e biblioteca de ncurses
        include_directories("C:/MinGW/include/ncurses")  # Altere para o caminho correto do seu ncurses
        link_directories("C:/MinGW/lib")  # Altere para o caminho correto da biblioteca ncurses
        set(CURSES_LIBRARIES ncurses)     # Defina o nome da biblioteca
else()
        # Linux ou outros sistemas podem usar o find_package normalmente
        find_package(Curses REQUIRED)
        include_directories(${CURSES_INCLUDE_DIR})
        set(CURSES_LIBRARIES ${CURSES_LIBRARIES})
endif()

# Adiciona o executável principal e linka com a biblioteca curses
add_executable(snail_sokoban ${MAIN_SOURCES})
target_link_libraries(snail_sokoban ${CURSES_LIBRARIES})


# Adiciona uma regra personalizada para gerar os arquivos .dat das fases
add_custom_target(generate_maps ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Building map generators..."
)

# Para cada arquivo de fase, adicionamos uma regra para compilar e executá-lo
foreach(MAP_SOURCE ${MAP_SOURCES})
        get_filename_component(MAP_NAME ${MAP_SOURCE} NAME_WE)
        add_executable(${MAP_NAME}_gen ${MAP_SOURCE})
        add_dependencies(generate_maps ${MAP_NAME}_gen)
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

add_dependencies(snail_sokoban clean_map_executables)
add_dependencies(clean_map_executables generate_maps)
