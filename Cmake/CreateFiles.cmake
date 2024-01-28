
set(ANIMATION_CONFIG_FILE "${RESOURCES_CONFIGFILES}/Assets/animationsConfig.txt")
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${ANIMATION_CONFIG_FILE}")
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/${ANIMATION_CONFIG_FILE}"
    "String  TextureName	 PlayerMovingExample\n"
    "Int     NumberOfFrames  2\n"
    "Int     AnimationSpeed  30\n"
    "End\n\n"
        
    "String  TextureName 	 EnemyMovingExample\n"
    "Int     NumberOfFrames  4\n"
    "Int     AnimationSpeed  20\n"
    "End\n\n"
    )
endif()

set(EXAMPLE_UNIFORM_FILE "${RESOURCES_CONFIGFILES}/Uniform/ExampleFileOfUniformForShaders.txt")
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_UNIFORM_FILE}")
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_UNIFORM_FILE}"
    "vec\t uName\t 2\t 1\t 2\n"
    "vec\t uColor\t 3\t 200\t 100\t 0\n"
    "vec\t uValue\t 4\t 100\t 0\t 100\t 0.5\n"
    "texture\t uTexture\t textureName\n"
    )
endif()
