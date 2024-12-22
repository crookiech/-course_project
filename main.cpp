#include <iostream>
#include <curl/curl.h>

// Функция обратного вызова для записи данных из ответа в строку
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb); // Добавляем полученные данные к строке
    return size * nmemb; // Возвращаем количество записанных байтов
}

int main() {
    std::cout<<std::endl;

    CURL* curl; // Указатель на объект CURL
    CURLcode res; // Код результата выполнения запроса
    std::string readBuffer; // Строка для хранения ответа сервера

    curl_global_init(CURL_GLOBAL_DEFAULT); // Инициализация библиотеки libcurl

    curl = curl_easy_init(); // Инициализация сессии curl
    if (!curl) { // Проверка на ошибки инициализации
        std::cerr << "curl_easy_init() failed" << std::endl;
        return 1; // Возврат кода ошибки
    }

    // GET-запрос
    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get"); // Устанавливаем URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Устанавливаем функцию обратного вызова для записи данных
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Устанавливаем указатель на буфер для записи данных

    res = curl_easy_perform(curl); // Выполнение запроса
    if (res != CURLE_OK) { // Проверка на ошибки
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl); // Очистка ресурсов curl
        curl_global_cleanup(); // Очистка глобальных ресурсов libcurl
        return 1; // Возврат кода ошибки
    } else {
        std::cout << "GET Ответ: " << readBuffer << std::endl; // Вывод ответа
    }
    readBuffer.clear(); // Очищаем буфер для следующего запроса


    // POST-запрос 

    struct curl_slist* headers = nullptr; // Список заголовков
    headers = curl_slist_append(headers, "User-Agent: MyAgent"); // Добавляем заголовок User-Agent
    headers = curl_slist_append(headers, "Accept-Language: ru-RU,ru;q=0.5"); // Добавляем заголовок Accept-Language

    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/post"); // Устанавливаем URL
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Устанавливаем заголовки
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=test_user &password=test_pass"); // Данные для отправки
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Функция обратного вызова для записи данных
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Указатель на буфер для записи данных

    res = curl_easy_perform(curl); // Выполнение запроса
    if (res != CURLE_OK) { // Проверка на ошибки
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "POST Ответ: " << readBuffer << std::endl; // Вывод ответа
    }
    curl_slist_free_all(headers); // Освобождение памяти, занятой списком заголовков
    

    curl_easy_cleanup(curl); // Очистка ресурсов curl
    curl_global_cleanup(); // Очистка глобальных ресурсов libcurl
    return 0; // Возврат кода успеха
}

