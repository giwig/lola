# (L)inux (O)n (L)ua (A)utobuilder - LOLA
### by GiWiG (c) 2022
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

    cpp_bash("sudo rm -r " .. tol_dir .. "/aaa")

    local cmd = [[
        ./configure     --prefix=/usr                       \
                        --libdir=/usr/lib64                 \
                        --sysconfdir=/etc                   \
                        --host=$LFS_TGT # $(uname -m)-lfs-linux-gnu    \
                        --build=$(build-aux/config.guess)   \
                        --disable-static  
    ]]
    
    --cmd = "./configure --help"
    
    cpp_bash(cmd)

end



function build()

    cpp_bash("make -j8")

end

function pkg_package()

    cmd = [[
        make DESTDIR=]] .. tol_dir .. [[/aaa install
    ]]

    cpp_bash(cmd)

end


```

***
### TODO:
>
>    -   переработать этот файл 'README.md'.
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

***
### Как пользоваться <b>llbuilder</b>:
#### ./llbuilder -h или в корне ./run -h
___
<code>
(L)inux (O)n (L)ua (A)utobuilder:

Usage: ./llbuilder [flags optional] [path to build scripts]

	HELP:
	=====================================================
	-h			this help
	-v			version for ./llbuilder

	FLAGS:
	=====================================================
	-b [path to *.lpac]	File LPAC with configuration for system build
</code>

***
### Описание файла LPAC:
Файл 'LPAC' имеет в себе следующую структуру данных:

### вырезка из lfs.lpac:
```lua

#!/usr/bin/lua
-- это просто заголовок для распознования синтаксиса другими редакторами


--package.path="lua/?.lua;lua/base/?.lua;lua/toolchain/?.lua"
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

env_global = {
	--"PATH="..tol_dir.."/x86_64-multilib-linux-gnu/bin/:"..tol_dir.."/tools/bin:$PATH",
	"LFS_TGT=$(uname -m)-lfs-linux-gnu",
	"VENDOR=GIWIG",
}


```

Главный файл lpac содержит в себе глобальные настройки для сборки системы. 

| Переменная | Описание |
| ---------- | -------- |
| env_global    |   переменные в среде 'Environment' для настройки сборки, типа LFS и LFS_TGT.|
| lpacs         |   это список пакетов, которые собираются последовательно, по списку. |
| src_dir       |   папка куда загружаются исходники пакетов. |
| tol_dir       |   папка где собираются пакеты. Например <b>/tmp/cbuild/</b><BR/>TODO: стоит переименовать в 'build_dir' или что-то подобное. |




    Переменные в 'LUA'-файлах:
        - pkgname   = имя пакета. Например 'm4'.
        - pkgver    = версия пакета.
        - pkgrel    = сборка пакета.
        - pkgsource = список с исходниками которые загружаются функцией 'pkg_download' в папку 'tol_dir'.
        - *sums*    = различные хэш-суммы нп. sha256, sha512, md5, ...
        
    Функции для сборки пакетов:
        Каждая из функция вызывается последовательно. Первые две функции pkg_download и pkg_extract
        имеют внутринии аналоги и не нуждваются в вызове. Остальные функции просто вызываются последовательно.
        
        - pkg_download      =   функция для загрузки пакета. если функция была определена, то внутренея функция
                                не используется.
        - pkg_extract       =   функция используется для распаковки пакета в папку, которая 
                                определена в переменной 'tol_dir'. Если переопределить эту функцию, то внутреняя
                                функция не будет вызвана.
        - pkg_prepare       =   функция для конфигурации пакета.
        - pkg_build     =   функция для сборки пакета.
        - pkg_install       =   функция для установки пакета в определённое место.
        - pkg_package       =   функция для упаковки пакета.
                                TODO: надо сделать общии функции для упаковки пакетов
        
    Вспомогательные lua-функции:
        Коммандные функции:
            - cpp_bash          =   вызывает команду системную комманду 'system()'.
            - cpp_chroot        =   переход в chroot() указанной папки.
            - cpp_ls            =   дает список файлов в папке. очень помогает, так как 
                                    в chroot() может не быть функции 'ls'. Возвращает назад список файлов и папок. 
            - cpp_pwd           =   возвращает назад папку, в которой мы сейчас находимся.
            - cpp_is_file       =   проверят путь true  = файл; false = папка.
            - cpp_is_dir        =   проверят путь false = файл; true  = папка.

            - cpp_set_env       =   записывает переменную
            - cpp_get_env       =   вычитывает переменную
            - cpp_del_env       =   стирает переменную
            - cpp_clear_env =   стирает все вариаблы в списке.

            - cpp_sha256file    =   хэш файла sha56







