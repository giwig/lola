-- File thats includes some functions


pkgname="bash"
pkgver="5.1.16"
pkgrel="0"
pkgsource={
	("https://ftp.gnu.org/gnu/"..pkgname.."/"..pkgname.."-"..pkgver..".tar.gz")
}
sha256sums={ 
	('5bac17218d3911834520dad13cd1f85ab944e1c09ae1aba55906be1f8192f558')
}


function pkg_prepare()

	cpp_bash("sudo rm -r " .. tol_dir .. "/aaa")

	cmd = [[
		./configure --prefix=/usr 			\
					--libdir=/usr/lib64 	\
					--without-bash-malloc	\
					--sysconfdir=/etc
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



