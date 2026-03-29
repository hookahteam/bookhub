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
else
    echo "Ошибка: не поддерживаемый менеджер пакетов"
    exit 1
fi

# Функция проверки и установки пакета
check_install() {
    if ! command -v "$1" &>/dev/null; then
        echo "Установка $2..."
        sudo $PKG_MANAGER $INSTALL_CMD "$2"
    else
        echo "$1 уже установлен"
    fi
}

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


# Обновляем список пакетов
echo "Обновление информации о пакетах..."
sudo $PKG_MANAGER $UPDATE_CMD

# Проверяем и устанавливаем необходимые компоненты
check_install "g++" "g++"
check_install "make" "make"
check_install "cmake" "cmake"
check_install "git" "git"
check_install "npm" "npm"

echo "Готово!"
