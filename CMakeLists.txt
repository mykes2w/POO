cmake_minimum_required(VERSION 4.0)
project(TrabalhoPOO)

set(CMAKE_CXX_STANDARD 17)

add_executable(TrabalhoPOO
        main.cpp
        Simulador.cpp
        mundo/Jardim.cpp
        mundo/Posicao.cpp
        plantas/Cacto.cpp
        plantas/Roseira.cpp
        plantas/ErvaDaninha.cpp
        plantas/PlantaExotica.cpp
        ferramentas/Ferramenta.cpp
        ferramentas/Regador.cpp
        ferramentas/Adubo.cpp
        ferramentas/Tesoura.cpp
        ferramentas/FerramentaZ.cpp
        plantas/Planta.cpp
        Jardineiro.cpp
)

target_include_directories(TrabalhoPOO PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        mundo
        plantas
        ferramentas
)
