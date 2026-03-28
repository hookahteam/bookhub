#!/bin/bash

echo "=== Исправляем структуру React-проекта ==="

# 1. Создаём нужные папки
mkdir -p src/components/Header
mkdir -p src/components/Footer
mkdir -p src/pages/Home
mkdir -p src/pages/About

# 2. Перемещаем компоненты (если они лежат не в своих папках)
# Если в папке components есть файл Header.jsx, перемещаем его в Header/
if [ -f src/components/Header.jsx ]; then
    mv src/components/Header.jsx src/components/Header/
fi
if [ -f src/components/Header.module.css ]; then
    mv src/components/Header.module.css src/components/Header/
fi
if [ -f src/components/Footer.jsx ]; then
    mv src/components/Footer.jsx src/components/Footer/
fi

# 3. Перемещаем страницы (если они лежат прямо в pages)
if [ -f src/pages/Home.jsx ]; then
    mv src/pages/Home.jsx src/pages/Home/
fi
if [ -f src/pages/About.jsx ]; then
    mv src/pages/About.jsx src/pages/About/
fi

# 4. Удаляем лишние стандартные файлы (не трогаем пользовательские)
rm -f src/App.test.js
rm -f src/setupTests.js
rm -f src/reportWebVitals.js
rm -f src/logo.svg
rm -f src/App.css   # если не нужен, можно оставить, но для чистоты удалим

# 5. Если есть и App.js, и App.jsx – удаляем App.js (оставляем App.jsx)
if [ -f src/App.js ] && [ -f src/App.jsx ]; then
    rm -f src/App.js
fi

# 6. Проверяем, что в index.js правильный импорт и нет дублирования App
# (делаем резервную копию, если надо)
if ! grep -q "import App from './App'" src/index.js; then
    echo "ВНИМАНИЕ: в index.js отсутствует импорт App. Исправляю..."
    # Создаём корректный index.js, сохраняя старый как index.js.bak
    cp src/index.js src/index.js.bak
    cat > src/index.js <<EOF
import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);
EOF
fi

# 7. Устанавливаем react-router-dom, если его нет
if ! grep -q "react-router-dom" package.json; then
    echo "Устанавливаем react-router-dom..."
    npm install react-router-dom
fi

# 8. Очищаем кэш и пересобираем
echo "Очищаем кэш сборки..."
rm -rf node_modules/.cache
rm -rf build

echo "=== Готово! ==="
echo "Теперь запустите npm start и проверьте страницу."