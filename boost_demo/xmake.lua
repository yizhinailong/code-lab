add_rules("mode.debug", "mode.release")

add_requires("boost")

includes("boost_*")

add_includedirs("utils")

set_rundir("$(projectdir)")
