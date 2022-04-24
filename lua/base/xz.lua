pkgname="xz"
pkgver="5.2.5"
pkgrel="0"
pkgsource={
	("https://tukaani.org/"..pkgname.."/"..pkgname.."-"..pkgver..".tar.xz")
}
sha256sums={ 
	('3e1e518ffc912f86608a8cb35e4bd41ad1aec210df2a47aaa1f95e7f5576ef56')
}


function pkg_prepare()

	print(cpp_bash("sudo rm -r " .. tol_dir .. "/aaa"))

	print(cpp_bash([[
		./configure --prefix=/usr 						\
					--libdir=/usr/lib64 				\
					--sysconfdir=/etc					\
					--host=$(uname -m)-lfs-linux-gnu 	\
            		--build=$(build-aux/config.guess) 	\
            		--disable-static  
	]]))
	
end



function build()

	cpp_bash("make -j8")
	
end

function pkg_package()

	cpp_bash([[
		make DESTDIR=]] .. tol_dir .. [[/aaa install
	]])

end



