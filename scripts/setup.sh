#!/bin/bash

# Определяем менеджер пакетов
if command -v apt-get &>/dev/null; then
    PKG_MANAGER="apt-get"
    UPDATE_CMD="update"
    INSTALL_CMD="install -y"
elif command -v dnf &>/dev/null; then
    PKG_MANAGER="dnf"
    UPDATE_CMD="makecache"
    INSTALL_CMD="install -y"
elif command -v yum &>/dev/null; then
    PKG_MANAGER="yum"
    UPDATE_CMD="makecache"
    INSTALL_CMD="install -y"
elif command -v brew &>/dev/null; then
    PKG_MANAGER="brew"
    UPDATE_CMD="update"
    INSTALL_CMD="install"
else
    echo "Ошибка: не поддерживаемый менеджер пакетов"
    exit 1
fi

# Функция проверки и установки пакета
check_install() {
    if ! command -v "$1" &>/dev/null; then
        echo "Установка $1..."
        if [ "$PKG_MANAGER" = "brew" ]; then
            $PKG_MANAGER $INSTALL_CMD "$2"
        else
            sudo $PKG_MANAGER $INSTALL_CMD "$1"
        fi
    else
        echo "$1 уже установлен"
    fi
}

# Обновляем список пакетов
echo "Обновление информации о пакетах..."

if [ "$PKG_MANAGER" = "brew" ]; then
    $PKG_MANAGER $UPDATE_CMD
else
    sudo $PKG_MANAGER $UPDATE_CMD
fi

# Проверяем и устанавливаем необходимые компоненты
// аргумент 1 для linux pkg менеджеров, аргумент 2 для homebrew
check_install "g++" "g++" 
check_install "make" "make"
check_install "cmake" "cmake"
check_install "git" "git"
check_install "libpqxx-dev" "libpqxx"
check_install "npm" "npm"


# Установка зависимостей самого React-приложения
PROJECT_DIR="./frontend/my-react-app"

if [ -d "$PROJECT_DIR" ]; then
    echo "Переход в директорию проекта и установка библиотек..."
    cd "$PROJECT_DIR"
    sudo npm install -g n && sudo n lts
    hash -r
    # Устанавливаем все зависимости из package.json + конкретно роутер
    npm install
    npm install react-router-dom 
else
    echo "Предупреждение: Директория проекта $PROJECT_DIR не найдена. Пропустите установку npm-пакетов."
fi

echo "Готово!"
