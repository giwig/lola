
function loop_envs()
	for k, v in ipairs(env_global) do
		print(" -> " .. v)
		nstr = Split(v, "=")
		print(" *\t" .. nstr[1] .. " && " .. nstr[2])
		print(" * SYSTEM OUTPUT => " .. cpp_bash('echo -e ' .. nstr[2]))
		print("\n\n")
	end
end


function Split(s, delimiter)
    result = {};
    for match in (s..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match);
    end
    return result;
end

