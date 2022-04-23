-- File thats includes some functions


pkgname="m4"
pkgver="1.4.19"
pkgarch="x86_64"
pkgextra="base"
pkgrel="0"
pkgsource={ 
	"https://ftp.gnu.org/gnu/"..pkgname.."/" .. pkgname .. "-" .. pkgver .. ".tar.xz",
	"https://raw.githubusercontent.com/archlinuxarm/PKGBUILDs/master/core/pacman/add-flto-to-LDFLAGS-for-clang.patch"
	
}
sha256sums={ 
	'63aede5c6d33b6d9b13511cd0be2cac046f2e70fd0a07aa9573a04a82783af96', 
	'82ff91b85f4c6ceba19f9330437e2a22aabc966c2b9e2a20a53857f98a42c223' 
}

md5sums = {
	'SKIP'
}

function _pkg_download()
	print(" * LPAC's download function")
end

function pkg_prepare()

	
	--[[
	--print("=======================================================================")
	print(" * prepare => "..pkgname)
	cpp_bash("uname -a")
	local path = cpp_get_env("PATH")
	print("PATH == "..path)
	
	cpp_set_env("PATH", "/opt/lala:" .. path, 1)
	local path = cpp_get_env("PATH")
	print("PATH == "..path)
	
	
	print("=======================================================================")
	print(" * Download			=> " .. pkgname)
	print(" * src_dir			=> " .. src_dir)
	print(" * URL to download\t\t=> " .. pkgsource[1])
	print(" * File to download\t\t=> " .. cpp_url_get_filename(pkgsource[1]))

	print(" * Should be			=> " .. sha256sums[1])
	
	src_file = cpp_url_get_filename(pkgsource[1])
	src_file_path = src_dir .. "/" .. src_file
	print(" * Search in Source dir\t\t=> " .. src_file)
	if cpp_is_file(src_file_path) then
		print(" * Found file in Source dir\t=> " .. src_file_path)
		local hash = cpp_sha256file(src_file_path)
		print(" * Calculated now		=> " .. hash)
	else
		print(" * File in source not found ")
	end
	cpp_bash("ls -la")
	cpp_bash("echo -e $PWD")
	]]--
	
	local cmd = [[
		rm -r ]] .. tol_dir .. [[/ttt
		./configure --prefix=/usr			\
					--libdir=/usr/lib64		\
					--sysconfdir=/etc
	]]
	
	cpp_bash(cmd)
end


function pkg_build()
	print("\tbuild => "..pkgname)
	local cmd = [[
		make -j8
	]]
	
	cpp_bash(cmd)
	
end

function pkg_build()
	local cmd = [[
		make DESTDIR=]] .. tol_dir .. [[/ttt install
	]]
	
	cpp_bash(cmd)
end

function pkg_package()
	--print("=======================================================================")
	print(" * test package")
end


