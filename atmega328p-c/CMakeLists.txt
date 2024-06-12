# Wymagana minimalna wersja CMake
cmake_minimum_required(VERSION 3.16)

# Ustawienie pliku toolchain
set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")

# Nazwa projektu
project(atmega328p-c)

# Nazwa docelowego pliku wynikowego
set(TARGET ${CMAKE_PROJECT_NAME}.elf)

# Dodanie pliku źródłowego do kompilacji
add_executable(${TARGET}
  "src/main.c"
)

# Dodanie katalogu z plikami nagłówkowymi do ścieżki dołączania
target_include_directories(${TARGET} PRIVATE
  "include"
)

# Opcje kompilacji
target_compile_options(${TARGET} PRIVATE
  -Os                # Optymalizacja pod kątem rozmiaru
  -Wall              # Włączenie wszystkich ostrzeżeń
  -Wextra            # Włączenie dodatkowych ostrzeżeń
  -Wpedantic         # Włączenie restrykcyjnych ostrzeżeń
  -mmcu=atmega328p   # Docelowy mikrokontroler
)

# Definicje kompilacji
target_compile_definitions(${TARGET} PRIVATE
  F_CPU=16000000UL   # Częstotliwość zegara procesora
)

# Opcje linkowania
target_link_options(${TARGET} PRIVATE
  -Wl,-Map=${CMAKE_PROJECT_NAME}.map  # Generowanie pliku mapy
  -mmcu=atmega328p                    # Docelowy mikrokontroler
)

# Dodanie niestandardowych komend po budowie
add_custom_command(
  TARGET ${TARGET} POST_BUILD
  # Konwersja ELF na Intel HEX
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${CMAKE_PROJECT_NAME}.hex
  # Generowanie zrzutu kodu maszynowego
  COMMAND ${CMAKE_OBJDUMP} -j .text -D ${TARGET} > ${CMAKE_PROJECT_NAME}.dump
  # Wyświetlanie rozmiarów sekcji
  COMMAND ${CMAKE_SIZE} ${TARGET}
)

# Dodanie niestandardowego celu do flashowania pamięci mikrokontrolera
add_custom_target(flash
  # Flashowanie za pomocą avrdude
  avrdude -p m328p -c usbasp -e -U flash:w:${CMAKE_PROJECT_NAME}.hex:i
  DEPENDS ${TARGET}
)
