-- File thats includes some functions


pkgname="coreutils"
pkgver="9.0"
pkgrel="0"
pkgsource={
	("https://ftp.gnu.org/gnu/"..pkgname.."/"..pkgname.."-"..pkgver..".tar.xz")
}
sha256sums={ 
	('ce30acdf4a41bc5bb30dd955e9eaa75fa216b4e3deb08889ed32433c7b3b97ce')
}


function pkg_prepare()

	cpp_bash("sudo rm -r " .. tol_dir .. "/aaa")

	cmd = [[
		./configure --prefix=/usr 						\
					--libdir=/usr/lib64 				\
					--sysconfdir=/etc					\
					--host=$(uname -m)-lfs-linux-gnu 	\
            		--build=$(build-aux/config.guess) 	\
            		--enable-install-program=hostname 	\
            		--enable-no-install-program=kill,uptime
	]]

	cpp_bash(cmd)

end



function build()
	print("\tbuild => "..pkgname)
	
	cpp_bash("make -j8")
	
end

function pkg_package()
	print(" * package => "..pkgname)
	cmd = [[
		make DESTDIR=]] .. tol_dir .. [[/aaa install
	]]
	cpp_bash(cmd)
end



