add_executable(eosio.arb.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.arb.cpp)
target_include_directories(eosio.arb.wasm
   PUBLIC 
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.system.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/abi/eosio.arb.abi" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${WASM_ROOT}/eosio.wasmsdk/include)
