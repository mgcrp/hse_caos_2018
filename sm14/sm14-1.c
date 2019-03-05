#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv) {
	long long int answer = 0;

	DIR * current_dir = opendir(argv[1]);
	// Ошибка при загрузке директории
	if (!current_dir) {
		printf("0\n");
		return 0;
	}

	// Получение UID текущего пользователя
	uid_t current_user = getuid();
	// Чтение файлов внутри папки
	struct dirent * files;
	while (files = readdir(current)) {
		char * file_name = files->d_name;

		char file_path[PATH_MAX];
		snprintf(file_path, PATH_MAX, "%s/%s", argv[1], file_name);

		struct stat file_stats;
		int stat_ret = stat(full_path, &file_stats);

		// Ошибка при чтении stats
		if (stat_ret) {
			continue;
		}
		// Файл регулярный
		if (!S_ISREG(file_stats.st_mode)) {
			continue;
		}
		// Его владельцем является текущий пользователь
		if (current_user != file_stats.st_uid) {
			continue;
		}
		// Его имя начинается с заглавной латинской буквы
		if (!isupper(file_name[0])) {
			continue;
		}
		// Если все ок - размер файла можно прибавить к ответу
		answer += file_stats.st_size;
	}

	closedir(current_dir);
	printf("%lld\n", answer);
	return 0;
}
