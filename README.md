# (L)inux (O)n (L)ua (A)utobuilder - LOLA
### by GiWiG (c) 2022
***
# :warning: !!!ВНИМАНИЕ!!!УВАГУ!!!УВАГI!!!
# Это начальная сборка и ещё не рабочая версия!!!
### Некоторые lua-функции в описании ниже могут не работать, так-как переделываю проект, для удобства в дальнейшей разработки.
***
# :warning: !!!ACHTUNG!!!ATTENTION!!!
***

В общем я брал, <b>как шаблон</b>, пакетный менеджер <b>'pacman'</b> и его скрипты для сборки пакетов.<BR/>

В первый раз, где-то в далёком 2017ом году я собрал сборщик линукса на чистом <b>BASH</b> и то 
приходилось ту или иную нужную мне функцию дописывать на Python или С/С++. Собрал с горем пополам и даже всё собиралось от
LFS до BLFS в XFCE4, но сейчас не хочу даже браться за эту кучу кода, который, что-бы обновить нужно практичкски всё переделывать.

Примерно в тоже время я начал изучать Python и примерно год назад снова пробовал создать свой сборщик. Теперь зная питон, 
я думал, что будет всё так просто. Но не тут-то было! Проблемы с правами пользователей, не говоря о <b>chroot</b> и всех <b>mount</b>-точках которые
нужно то соединять, то отсоединять.

Частично пытался делать сборщик ещё под <b>Docker</b>, но тоже обломался, потому-что что-бы сделать полную автоматизацию, надо капаться в
документации docker и управлять им как-то из питона или чего-то что может овладеть этим монстром, а иначе выйдет просто одноразовый сборщик.

В конце концов я вернулся к своему основному языку программирования С/С++. Так как все функции, которые требуются для автоматизации находятся в основном в
ядре, то и думать тут приходиться только о том как использовать ту или иную функцию. Как скриптовый язык для настройки, сборки системы и пакетов я выбрал
старый добрый <b>Lua</b>, который часто использовал уже ранее.


***
### TODO:
>
>    -   переработать этот файл 'README.md'.
>
>    -   изменить название проекта. сначала назвал mini-pacman, но теперь это LOLA или просто llbuilder.
>
>    -   поработать над структурой исходников и наиманованиями, что-бы было более понятно что и где находится.
>        Сейчас файлы с префиксом 'cpp_' содержат С/C++ функции.
>        Файлы с префиксом 'lua_' содержат функции, которые передаются в lua, для внутреннего использования.
>        Файлы с префиксом 'm_'   содержат главные функции программы, к томуже в этих файлах находятся вспомогательные классы, 
>        которые нужно   будет вынести под другой префикс типа 'plugin_'.
>
>    -   Как дополнение, можно нарисовать <b>UML</b> схему, как будет работать сам сборщик линуксов. Но пока-что попытаюсь описать это здесь в README.md
>
>    -   'tol_dir' стоит переименовать в 'build_dir' или что-то подобное.
>
>    -   Вынести функции в отдельную библиотеку , для привязки с другими языками типа Python итд...
>    -   Менее важно, но всё же: перевести на другие языки то, что я здесь написал :smiley:

***
### Как пользоваться <b>llbuilder</b>:
Установка программы в систему пока не проверял, так как я использую <b>cmake</b>, как сборщик и ещё руки не доросли до установки через <b>make install</b>
### Сборка проекта:

Запускаем в корне "run.sh"
```console
guest@porteus:~/eclipse-workspace/mini-pacman$ ./run.sh 
mkdir: created directory 'build'
mkdir: created directory 'build/default'
mkdir: created directory 'build/bin'
mkdir: created directory 'build/bin/lua'
 * Configure CMAKE files
-- The C compiler identification is GNU 10.3.0
-- The CXX compiler identification is GNU 10.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found PkgConfig: /usr/bin/pkg-config (found version "1.8.0") 
-- Checking for module 'lua'
--   Found lua, version 5.1.5
-- Configuring done
-- Generating done
-- Build files have been written to: /home/guest/eclipse-workspace/mini-pacman/build
 * Build project in /home/guest/eclipse-workspace/mini-pacman/build
[  8%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/m_lpac.cpp.o
[ 16%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/cpp_fs.cpp.o
[ 25%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/m_helper.cpp.o
[ 33%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/cpp_inet.cpp.o
[ 41%] Building CXX object CMakeFiles/llbuilder.dir/src/mini-pacman.cpp.o
[ 50%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/m_builder.cpp.o
[ 58%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/lua_filesystem.cpp.o
[ 66%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/lua_loop.cpp.o
[ 75%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/lua_envs.cpp.o
[ 83%] Building CXX object CMakeFiles/llbuilder.dir/src/inc/lua_child_process.cpp.o
[ 91%] Building CXX object CMakeFiles/llbuilder.dir/src/inc_3th/sha256.cpp.o
[100%] Linking CXX executable llbuilder
[100%] Built target llbuilder


(L)inux (O)n (L)ua (A)utobuilder:

guest@porteus:~/eclipse-workspace/mini-pacman$

```

#### ./llbuilder -h или в корне ./run.sh -h

```console

(L)inux (O)n (L)ua (A)utobuilder:

Usage: ./llbuilder [flags optional] [path to build scripts]

	HELP:
	=====================================================
	-h			this help
	-v			version for ./llbuilder

	FLAGS:
	=====================================================
	-b [path to *.lpac]	File LPAC with configuration for system build
```

#### ./llbuilder <i>или в корне</i> ./run.sh -b lua/lfs.lpac запускает сборку системы.

***
# Описание файла LPAC:

### вырезка из lfs.lpac:
```lua

#!/usr/bin/lua -- это просто заголовок для распознования синтаксиса другими редакторами

package.path="lua/?.lua"

require "inc/env"

lpacs = {
	--"base/m4",
	"base/busybox", 
	--"base/ncurses",
	--"base/bash",
	--"base/coreutils",
	--"base/xz",
}

src_dir="/mnt/sda5/PROJECTS/os/plaxOS/src"
tol_dir="/tmp/cbuild"

-- нужно дописать resolver для переменных типа $PATH
env_global = {
	--"PATH="..tol_dir.."/x86_64-multilib-linux-gnu/bin/:"..tol_dir.."/tools/bin:$PATH",
	"LFS_TGT=$(uname -m)-lfs-linux-gnu",
	"VENDOR=GIWIG",
}
```

Файл 'LPAC' имеет в себе следующую структуру данных:

Главный файл lpac содержит в себе глобальные настройки для сборки системы. 

| Переменная | Статус | Описание |
| ---------- | -------- | -------- |
| src_dir       |:ok:|   папка куда загружаются исходники пакетов. |
| tol_dir       |:ok:|   папка где собираются пакеты. Например <b>/tmp/cbuild/</b><BR/>TODO: стоит переименовать в 'build_dir' или что-то подобное. |
| lpacs         |:ok:|   это список пакетов, которые собираются последовательно, по списку. |
| env_global    |:construction:|   переменные в среде 'Environment' для настройки сборки, типа LFS и LFS_TGT.|




### Переменные в пакетных файлах:

### Вырезка из пакета <b>xz.lua</b>:

```lua


-- общие переменные для настройки
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

```


| Переменная | Описание |
| ---------- | -------- |
| pkgname | имя пакета. Например 'm4'. |
| pkgver | версия пакета. |
| pkgrel | сборка пакета. |
| pkgsource | список с исходниками которые загружаются функцией 'pkg_download' в папку 'tol_dir'. |
| shaXXXsums, md5, ... | различные хэш-суммы нп. sha256, sha512, md5, ... |
        
### Функции для сборки пакетов:

Каждая из функция вызывается последовательно. Первые две функции pkg_download и pkg_extract
имеют внутринии аналоги и не нуждваются в вызове. Остальные функции просто вызываются последовательно.
        
| Функция | Статус | Описание |
| ------- | ------ | -------- |
| pkg_download | :ok: :construction: | функция для загрузки пакета. если функция была определена, то внутренея функция не используется.
| pkg_extract | :ok: :construction: | функция используется для распаковки пакета в папку, которая определена в переменной 'tol_dir'. Если переопределить эту функцию, то внутреняя функция не будет вызвана. |
| pkg_prepare | :ok: :construction: | функция для конфигурации пакета.|
| pkg_build | :ok: :construction: | функция для сборки пакета. |
| pkg_install | :ok: :construction: | функция для установки пакета в определённое место.|
| pkg_package | :construction: | функция для упаковки пакета.|

TODO: надо сделать общии функции для упаковки пакетов
        
# Вспомогательные lua-функции:
Коммандные функции:

| Функция | Статус | Описание |
| ------- | ------ | -------- |
| cpp_bash | :warning: :construction: | вызывает системную комманду 'system()'.|
| cpp_chroot | :construction: | переход в chroot() указанной папки.|
| cpp_ls | :warning: :construction: | дает список файлов в папке. очень помогает, так как в chroot() может не быть функции 'ls'. Возвращает назад список файлов и папок. |
| cpp_pwd | :warning: :construction: | возвращает назад папку, в которой мы сейчас находимся.|
| cpp_is_file | :warning: :construction: | проверят путь true  = файл; false = папка.|
| cpp_is_dir | :warning: :construction: | проверят путь false = файл; true  = папка.|
| cpp_set_env | :warning: :construction: | записывает переменную|
| cpp_get_env | :warning: :construction: | вычитывает переменную|
| cpp_del_env | :warning: :construction: | стирает переменную|
| cpp_clear_env | :warning: :construction: | стирает все вариаблы в списке.|
| cpp_sha256file | :warning: :construction: | хэш файла sha56|

#### Статусы
| Статус | Описание |
| ------ | -------- |
|:ok: | функция проверена и работает.|
|:warning: | присутствует, но работает не стабильно |
|:no_entry_sign: | отсутствует в данный момент |
|:construction: | функции могут не работать. Или отсутствовать вовсе (но только сейчас - в связи с переструктуризацией проекта )|






