add_rules("mode.debug", "mode.release")

add_requires("boost")

target("boost_bimap", function ()
    set_kind("binary")
    add_files("boost_bimap/boost_bimap.cpp")
    add_packages("boost")
    set_languages("c++23")
end)
