include_guard(GLOBAL)

function(_riptide_attach_sources target scope)
    file(GLOB_RECURSE sources CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    file(GLOB_RECURSE modules CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/*.cppm")

    if(sources)
        target_sources(${target} PRIVATE ${sources})
    endif()
    if(modules)
        target_sources(${target}
            ${scope}
                FILE_SET modules TYPE CXX_MODULES
                BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/interfaces"
                FILES ${modules})
    endif()

    if(sources OR modules)
        set(_riptide_has_sources TRUE PARENT_SCOPE)
    else()
        set(_riptide_has_sources FALSE PARENT_SCOPE)
    endif()
endfunction()

function(riptide_add_library name)
    cmake_parse_arguments(ARG "" "" "DEPENDS" ${ARGN})
    set(target riptide_${name})

    add_library(${target})
    add_library(riptide::${name} ALIAS ${target})
    _riptide_attach_sources(${target} PUBLIC)

    if(NOT _riptide_has_sources)
        message(FATAL_ERROR
            "riptide_${name}: aucun fichier dans src/ ni interfaces/. "
            "Ajoutez-en un avant d'activer ce composant.")
    endif()

    target_compile_features(${target} PUBLIC cxx_std_26)
    target_link_libraries(${target}
        PRIVATE riptide_headers riptide_warnings riptide_reflection
        PUBLIC  ${ARG_DEPENDS})
endfunction()

function(riptide_add_executable name)
    cmake_parse_arguments(ARG "" "" "DEPENDS" ${ARGN})
    set(target riptide_${name})

    add_executable(${target})
    add_executable(riptide::${name} ALIAS ${target})
    _riptide_attach_sources(${target} PRIVATE)

    target_compile_features(${target} PRIVATE cxx_std_26)
    target_link_libraries(${target}
        PRIVATE riptide_warnings riptide_headers riptide_reflection ${ARG_DEPENDS})
endfunction()