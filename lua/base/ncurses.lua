-- File thats includes some functions


pkgname="ncurses"
pkgver="6.3"
pkgrel="0"
pkgsource={
	("https://invisible-mirror.net/archives/"..pkgname.."/"..pkgname.."-"..pkgver..".tar.gz")
}
sha256sums={ 
	('97fc51ac2b085d4cde31ef4d2c3122c21abc217e9090a43a30fc5ec21684e059')
}


function pkg_prepare()
	
	cmd = [[
		./configure --prefix=/usr 		\
					--libdir=/usr/lib64 \
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



