# (L)inux (O)n (L)ua (A)utobuilder - LOLA
###	by GiWiG (c) 2022
***

В общем я брал, <b>как шаблон</b>, пакетный менеджер <b>'pacman'</b> и его скрипты для сборки пакетов.<BR/>

В первый раз, где-то в далёком 2017ом году я собрал сборщик линукса на чистом <b>BASH</b> и то 
приходилось ту или иную нужную мне функцию дописывать на Python или С/С++. Собрал с горем пополам и даже всё собиралось от
LFS до BLFS в XFCE4, но сейчас не хочу даже браться за эту кучу кода, который, что-бы обновить нужно практичкски всё переделывать.

Примерно в тоже время я начал изучать Python и примерно год назад снова пробовал создать свой сборщик. Теперь зная питон, 
я думал, что будет всё так просто. Но не тут-то было! Проблемы с правами пользователей, не говоря о <b>chroot</b> и всех <b>mount</b>-точках которые
нужно то соединять, то отсоединять.

Частично пытался делать сборщик ещё под <b>Docker</b>, но тоже обломался, потому-что что-бы сделать полную автоматизацию, надо капаться в
документации docker и управлять им как-то из питона или чего-то что может овладеть этим монстром.
***

### TODO:

	*	переработать этот файл 'README.md'.

	*	поработать над структурой исходников и наиманованиями, что-бы было более понятно что и где находится.
		Сейчас файлы с префиксом 'cpp_' содержат С/C++ функции.
		Файлы с префиксом 'lua_' содержат функции, которые передаются в lua, для внутреннего использования.
		Файлы с префиксом 'm_'   содержат главные функции программы, к томуже в этих файлах находятся вспомогательные классы, которые нужно 			будет вынести под другой префикс типа 'plugin_'.
		
	*	Нужно нарисовать "UML" схему, как будет работать сам сборщик линуксов.

***
### Описание файла LPAC:
	Файл 'LPAC' имеет в себе следующую структуру данных. Внутри файла используется язык 'LUA'.
	
	Главный файл lpac содержит в себе глобальные настройки для сборки системы. 
	Например:
		'env_global'	-	переменные в среде 'Environment' для настройки сборки, типа LFS и LFS_TGT.
		'lpacs' 		-	это список пакетов, которые собираются последовательно, по списку.
		'src_dir'		-	папка куда загружаются исходники пакетов.
		'tol_dir'		-	папка где собираются пакеты.
			TODO		-	стоит переименовать в 'build_dir' или что-то подобное.


	Переменные в 'LUA'-файлах:
		- pkgname 	= имя пакета. Например 'm4'.
		- pkgver 	= версия пакета.
		- pkgrel	= сборка пакета.
		- pkgsource	= список с исходниками которые загружаются функцией 'pkg_download' в папку 'tol_dir'.
		- *sums*	= различные хэш-суммы нп. sha256, sha512, md5, ...
		
	Функции для сборки пакетов:
		Каждая из функция вызывается последовательно. Первые две функции pkg_download и pkg_extract
		имеют внутринии аналоги и не нуждваются в вызове. Остальные функции просто вызываются последовательно.
		
		- pkg_download		=	функция для загрузки пакета. если функция была определена, то внутренея функция
								не используется.
		- pkg_extract		=	функция используется для распаковки пакета в папку, которая 
								определена в переменной 'tol_dir'. Если переопределить эту функцию, то внутреняя
								функция не будет вызвана.
		- pkg_prepare		=	функция для конфигурации пакета.
		- pkg_build		=	функция для сборки пакета.
		- pkg_install		= 	функция для установки пакета в определённое место.
		- pkg_package		=	функция для упаковки пакета.
								TODO: надо сделать общии функции для упаковки пакетов
		
	Вспомогательные lua-функции:
		Коммандные функции:
			- cpp_bash			=	вызывает команду системную комманду 'system()'.
			- cpp_chroot		=	переход в chroot() указанной папки.
			- cpp_ls			= 	дает список файлов в папке. очень помогает, так как 
									в chroot() может не быть функции 'ls'. Возвращает назад список файлов и папок. 
			- cpp_pwd			=	возвращает назад папку, в которой мы сейчас находимся.
			- cpp_is_file		=	проверят путь true  = файл; false = папка.
			- cpp_is_dir		=	проверят путь false = файл; true  = папка.

			- cpp_set_env		=	записывает переменную
			- cpp_get_env		=	вычитывает переменную
			- cpp_del_env		=	стирает переменную
			- cpp_clear_env	=	стирает все вариаблы в списке.

			- cpp_sha256file	= 	хэш файла sha56







