cmake_minimum_required(VERSION 3.5.0)
project(proj VERSION 0.1.0 LANGUAGES C CXX)

# Поиск libcurl.  CMake автоматически ищет в стандартных местах.
find_package(CURL REQUIRED)

# Проверка, что libcurl найден
if(CURL_FOUND)
  # Создание исполняемого файла
  add_executable(proj main.cpp)

  # Подключение libcurl к исполняемому файлу
  target_link_libraries(proj ${CURL_LIBRARIES})
else()
  message(FATAL_ERROR "libcurl not found! Please install libcurl and make sure it's in your system's include and library paths.")
endif()