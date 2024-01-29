
set(EXAMPLE_UNIFORM_FILE "${RESOURCES_CONFIGFILES}/Uniform/ExampleFileOfUniformForShaders.txt")
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_UNIFORM_FILE}")
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_UNIFORM_FILE}"
    "vec\t uName\t 2\t 1\t 2\n"
    "vec\t uColor\t 3\t 200\t 100\t 0\n"
    "vec\t uValue\t 4\t 100\t 0\t 100\t 0.5\n"
    "texture\t uTexture\t textureName\n"
    )
endif()
