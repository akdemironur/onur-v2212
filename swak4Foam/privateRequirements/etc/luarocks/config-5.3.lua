-- LuaRocks configuration

rocks_trees = {
   { name = "user", root = home .. "/.luarocks" };
   { name = "system", root = "/home/onur/OpenFOAM/onur-v2212/swak4Foam/privateRequirements" };
}
lua_interpreter = "lua";
variables = {
   LUA_DIR = "/home/onur/OpenFOAM/onur-v2212/swak4Foam/privateRequirements";
   LUA_BINDIR = "/home/onur/OpenFOAM/onur-v2212/swak4Foam/privateRequirements/bin";
}
