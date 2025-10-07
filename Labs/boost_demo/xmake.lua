add_rules("mode.debug", "mode.release")

add_requires("boost")

includes("boost_*")

add_includedirs("utils")

set_rundir("$(projectdir)")

if is_mode("debug") then
    add_defines("DEBUG_MODE")
end
