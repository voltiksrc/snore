set_project("snore")
set_version("0.1.0")

set_languages("c17")

target("snore")
set_kind("binary")
add_files("src/*.c")
set_warnings("all", "extra")
