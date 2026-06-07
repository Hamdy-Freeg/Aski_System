# 1. أقل إصدار مطلوب من CMake
cmake_minimum_required(VERSION 3.10)

# 2. اسم المشروع
project(Aski_System)

# 3. بنقوله يستخدم C++ 17 (عشان الـ Features الحديثة لو احتجتها)
set(CMAKE_CXX_STANDARD 17)

# 4. بنحدد أماكن الكتالوجات (include folder)
include_directories(include)

# 5. بنجمع كل ملفات الـ cpp اللي في فولدر src
file(GLOB SOURCES "src/*.cpp")

# 6. بنقوله طلع لي ملف تشغيل اسمه AskFM من ملفات الـ SOURCES
add_executable(Aski_System ${SOURCES})