project("TextToPDF")
set (CMAKE_CXX_STANDARD 11)
add_executable(bin/TextToPDF src/main.cpp src/EntryPoint.cpp src/Font.cpp src/Layout.cpp src/PageContent.cpp src/Page.cpp src/xref.cpp)
