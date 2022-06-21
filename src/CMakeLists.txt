project(wax)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( wax wax wax.cpp )
target_include_directories( wax PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( wax ${CMAKE_SOURCE_DIR}/../ricardian )