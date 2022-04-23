
pkgname="busybox"
pkgver="1.35.0"
pkgrel="0"
pkgsource={ 
	("https://busybox.net/downloads/"..pkgname.."-"..pkgver..".tar.bz2")
}
sha256sums={ 
	('faeeb244c35a348a334f4a59e44626ee870fb07b6884d68c10ae8bc19f83a694')
}


function pkg_prepare()

	local cmd = [[
		make defconfig
		make menuconfig
	]]
	--cpp_bash(cmd)

	print("\n\n")
	--[[
	for k, v in ipairs(env_global) do
		print(" -> " .. v)
		nstr = Split(v, "=")
		print(" *\t" .. nstr[1] .. " && " .. nstr[2])
		print(" * SYSTEM OUTPUT => " .. cpp_bash('echo -e ' .. nstr[2]))
		print("\n\n")
	end
	]]--
	loop_envs()

	print(" * tol_dir == " .. tol_dir)
	cpp_set_env("TOL_DIR", tol_dir, 1)
	--cpp_set_env("LFS_TGT","$(uname -m)-lfs-linux-gnu",1)	
	print(" * GET PATH   == " .. tostring( cpp_get_env("TOL_DIR") ) )
	--print(" * GET TARGET == " .. tostring( cpp_get_env("LFS_TGT") ) )
	cpp_bash('echo -e "$LFS_TGT"')
end


function pkg_build()

	local cmd = [[
		make -j8
	]]
	--cpp_bash(cmd)
end


function pkg_package()
	print(" * package => "..pkgname)
	local tmp = cpp_get_env("TOL_DIR")
	print(" * TOL_DIR[build] == " .. tmp )

	local cmd = [[
		[ -d $TOL_DIR/busybox ] && rm -r $TOL_DIR/busybox || echo -e "NOT FOUND $TOL_DIR"
	]]
	print(cpp_bash(cmd))

	local cmd = [[
		make CONFIG_PREFIX=]] .. tol_dir .. [[/busybox install
	]]
	--cpp_bash(cmd)

	local cmd = [[
		export
	]]
	print(cpp_bash(cmd))
	
end


