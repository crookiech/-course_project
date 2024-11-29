#include <iostream>
#include "tinyxml2.h"

/// @brief Отображает содержимое XML-документа в структурированном виде
/// @param element указатель на текущий элемент 
/// @param depth глубина вхождения в корневой элемент
void printStructure(tinyxml2::XMLElement* element, int depth) {
    if (element == nullptr) return; // если указатель на текущий элемент нулевой, то структура полностью отображено
    // Вывод элемента
    for (int i = 0; i < depth; ++i) std::cout << "      "; // отступ
    std::cout << "Элемент: " << element->Name() << std::endl; // вывод в консоль названия элемента
    // Вывод атрибуты элемента
    const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); // указатель на первый атрибут элемента
    while (attr != nullptr) { // пока указатель на атрибут не нулевой
        for (int i = 0; i < depth; ++i) std::cout << "       "; // отступ
        std::cout << "Атрибут " << element->Name() << ": " << attr->Name() << " = " << attr->Value() << std::endl; // вывод в консоль названия атрибута и его значения
        attr = attr->Next(); // переход к следующему атрибуту
    }
    // Вывод текстовое содержимое элемента, если оно есть
    const char* text = element->GetText(); // текстовое содержимое элемента
    if (text != nullptr && strlen(text) > 0) { // если текст не нулевой и его длина больше нуля
        for (int i = 0; i < depth; ++i) std::cout << "       "; // отступ
        std::cout << "Значение " << element->Name() << ": " << text << std::endl; // вывод содержимого
    }
    // Рекурсивный вызов для дочерних элементов
    for (tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        printStructure(child, depth + 1); // обновление глубины вхождения в корневой элемент
    }
}

int main() {
    tinyxml2::XMLDocument XMLDocument; // создание XML-документа
    if (XMLDocument.LoadFile("C:/programming/course_project/myFirstXML.xml") != tinyxml2::XML_SUCCESS) { // загрузка XML-документа
        std::cerr << "Ошибка загрузки файла: " << XMLDocument.ErrorIDToName(XMLDocument.ErrorID()) << std::endl;
        return -1;
    }
    tinyxml2::XMLElement* root = XMLDocument.RootElement(); // корневой элемент
    printStructure(root, 0); // вывод в консоль структуры
    return 0;
}